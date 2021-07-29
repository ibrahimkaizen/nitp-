<?php
/**
 * @file
 * Contains the class for Views EVI.
 */

/**
 * Provides the settings to inject values into exposed filters.
 *
 * @ingroup views_display_plugins
 */
class ViewsEviDisplayExtender extends views_plugin_display_extender {
  /**
   * Proxied pre-view hook. Pre-execute is too late.
   *
   * Populate $view->exposed_input before $view->get_exposed_input() does.
   */
  function viewsEviPreView() {
    /** @var views_plugin_display $display_handler */
    $display_handler = $this->display;
    /** @var view $view */
    $view = $display_handler->view;

    $input = $view->get_exposed_input();

    foreach($this->getViewsEviFilterWrappers() as $filter_wrapper) {
      $input_override = $filter_wrapper->getValue();
      if (isset($input_override)) {
        $input = drupal_array_merge_deep($input, $input_override);
      }
    }
    $view->set_exposed_input($input);
    // Also fix sleep deprived merlin https://drupal.org/node/1407044
    if (!isset($view->exposed_data)) {$view->exposed_data = array();}
    $view->exposed_data = $input + $view->exposed_data;
    if (!isset($view->exposed_raw_input)) {$view->exposed_raw_input = array();}
    $view->exposed_raw_input = $input + $view->exposed_raw_input;
  }

  /**
   * Proxied form_alter hook.
   *
   * @param $form
   * @param $form_state
   */
  function viewsEviExposedFormAlter(&$form, &$form_state) {
    // Go through exposed filters and set exposed widget visibility
    $form_empty = TRUE;
    foreach ($this->getViewsEviFilterWrappers() as $filter_wrapper) {
      $identifier = $filter_wrapper->getIdentifier();
      $id = $filter_wrapper->getId();
      $visibility = $filter_wrapper->getVisibility($form);
      if (isset($visibility) && !$visibility) {
        // This is needed to kill the label too.
        unset($form['#info']["filter-$id"]);
        // Hide the widget, just in case we get no input override.
        $form[$identifier]['#access'] = FALSE;
        // Exposed form rendering builds and submits this, so fake the value
        $input_override = $filter_wrapper->getValue();
        foreach ($input_override as $identifier => $value) {
          $form[$identifier] = array(
            '#type' => 'value',
            '#value' => $value,
          );
        }
      }
      else {
        $form_empty = FALSE;
      }
    }
    if ($form_empty) {
      $form['#access'] = FALSE;
    }
  }

  /**
   * Alters display options. Any option will be be visible as form section.
   */
  function options_definition_alter(&$options) {
    $options['views_evi_plugins'] = array('default' => array());
    $options['views_evi_settings'] = array('default' => array());
    $options['defaults']['default']['views_evi_plugins'] = TRUE;
    $options['defaults']['default']['views_evi_settings'] = TRUE;
  }

  function defaultable_sections(&$sections, $section = NULL) {
    $sections['views_evi_plugins'] = array('views_evi_plugins', 'views_evi_settings');
    $sections['views_evi_settings'] = array('views_evi_plugins', 'views_evi_settings');
  }

  /**
   * Summarizes settings.
   */
  function options_summary(&$categories, &$options) {
    parent::options_summary($categories, $options);
    $options['views_evi_plugins'] = array(
      'category' => 'other',
      'title' => t('Views EVI'),
      'value' => t('Plugins'),
      'desc' => t('Choose plugins.'),
    );
    $options['views_evi_settings'] = array(
      'category' => 'other',
      'title' => t('Views EVI'),
      'value' => t('Settings'),
      'desc' => t('Configure plugin settings if needed.'),
    );
  }

  /**
   * Provides the settings form.
   */
  function options_form(&$form, &$form_state) {

    parent::options_form($form, $form_state);
    $section = $form_state['section'];
    $is_plugins = $section == 'views_evi_plugins';
    $is_settings = $section == 'views_evi_settings';

    if ($is_plugins || $is_settings) {
      views_ui_standard_display_dropdown($form, $form_state, $section);
      $form[$section] = array(
        '#tree' => TRUE,
      );
      $form['#title'] .= $is_settings ? t('Views EVI settings') : t('Views EVI plugins');
    }

    // Iterate filters.
    foreach ($this->getViewsEviFilterWrappers() as $filter_id => $filter_wrapper) {
      $filter_settings_form = array();
      // Iterate plugin types.
      foreach(views_evi_plugin_types() as $plugin_type => $plugin_info) {

        // Plugins: Dropdown,
        if ($is_plugins) {
          $plugin_class = $filter_wrapper->getPluginClass($plugin_type);
          $filter_settings_form[$plugin_type]['class'] = array(
            '#type' => 'select',
            '#title' => $plugin_info['label'],
            '#default_value' => $plugin_class,
            '#options' => views_evi_plugin_labels($plugin_type),
          );
        }

        // Settings: Delegate to plugins.
        if ($is_settings) {
          $plugin = $filter_wrapper->getPlugin($plugin_type);
          $settings = $filter_wrapper->getPluginSettings($plugin_type);
          $plugin_settings_form = $plugin->settingsForm($settings, $form);
          if ($plugin_settings_form) {
            $filter_settings_form[$plugin_type] = $plugin_settings_form;
          }
        }

      }

      // We only need a fieldset if there are settings.
      if ($filter_settings_form) {
        // Label is already sanitized.
        $evi_label = t('Settings for !label', array('!label' => $filter_wrapper->GetEviLabel()));
        $form[$section]['filters'][$filter_id] = $filter_settings_form + array(
          '#type' => 'fieldset',
          '#title' => $evi_label,
          '#collapsible' => FALSE,
          '#collapsed' => FALSE,
        );
      }
    }
  }

  /**
   * Validates settings.
   */
  function options_validate(&$form, &$form_state) {
    parent::options_validate($form, $form_state);
    $section = $form_state['section'];
    $is_plugins = $section == 'views_evi_plugins';
    $is_settings = $section == 'views_evi_settings';

    // Plugins: Nothing to do.
    // Settings: Delegate to plugins.
    if ($is_settings) {
      $values = &$form_state['values'];
      // Iterate filters.
      foreach ($this->getViewsEviFilterWrappers() as $filter_id => $filter_wrapper) {
        // Iterate plugin types.
        foreach(views_evi_plugin_types() as $plugin_type => $plugin_info) {
          $plugin = $filter_wrapper->getPlugin($plugin_type);
          $settings = &$filter_wrapper->getPluginSettingsRef($plugin_type, $values);
          $plugin->settingsFormValidate($settings);
        }
      }
    }
  }

  /**
   * Saves settings into the view display.
   */
  function options_submit(&$form, &$form_state) {
    parent::options_submit($form, $form_state);
    $section = $form_state['section'];
    $is_plugins = $section == 'views_evi_plugins';
    $is_settings = $section == 'views_evi_settings';


    $values = &$form_state['values'];
    // Iterate filters.
    foreach ($this->getViewsEviFilterWrappers() as $filter_id => $filter_wrapper) {
      // Iterate plugin types.
      foreach(views_evi_plugin_types() as $plugin_type => $plugin_info) {

        // Plugins: Save class.
        if ($is_plugins) {
          $plugin_class = $form_state['values'][$section]['filters'][$filter_id][$plugin_type]['class'];
          $filter_wrapper->setPluginClass($plugin_type, $plugin_class);
        }

        // Settings: Delegate to plugins.
        if ($is_settings) {
          $plugin = $filter_wrapper->getPlugin($plugin_type);
          $plugin_form_values = &$filter_wrapper->getPluginSettingsRef($plugin_type, $values);
          $plugin_settings = $plugin->settingsFormSubmit($plugin_form_values);
          $filter_wrapper->setPluginSettings($plugin_type, $plugin_settings);
        }

      }
    }

  }

  /**
   * Get filter wrappers for all exposed filters of this view.
   *
   * @return ViewsEviFilterWrapper[]
   */
  public function getViewsEviFilterWrappers() {
    /** @var views_plugin_display $display */
    $display = $this->display;
    $all_filter_handlers = $display->get_handlers('filter');

    $filter_is_exposed = function($filter_handler) {
      return !empty($filter_handler->options['exposed']);
    };
    $filter_handlers = array_filter($all_filter_handlers, $filter_is_exposed);

    $wrap_filter = function($filter_handler) {
      return new ViewsEviFilterWrapper($filter_handler);
    };
    $filter_wrappers = array_map($wrap_filter, $filter_handlers);

    return $filter_wrappers;
  }

  /** @var array $cache */
  private $cache;

  /**
   * Allow our friends to get their EVI_global cache values.
   *
   * @see ViewsEviValueToken
   *
   * @param string $class
   * @param string $key
   * @return mixed
   */
  public function getViewsEviCache($class, $key) {
    return @$this->cache["$class-$key"];
  }

  /**
   * Allow our friends to set their EVI_global cache values.
   *
   * @see ViewsEviValueToken
   *
   * @param string $class
   * @param string $key
   * @param mixed $value
   */
  public function setViewsEviCache($class, $key, $value) {
    $this->cache["$class-$key"] = $value;
  }

}
