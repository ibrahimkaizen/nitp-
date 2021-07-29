<?php

/**
 * Class ViewsEviFilterWrapper
 */
class ViewsEviFilterWrapper {
  /** @var  views_handler_filter $filter_handler */
  private $filter_handler;

  /**
   * @param \views_handler_filter $filter_handler
   */
  function __construct($filter_handler) {
    $this->filter_handler = $filter_handler;
  }

  /**
   * Get filter handler.
   *
   * @return \views_handler_filter
   */
  public function getFilterHandler() {
    return $this->filter_handler;
  }

  /**
   * Get filter ID.
   *
   * @return string
   */
  public function getId() {
    return $this->filter_handler->options['id'];
  }

  /**
   * Get filter identifier a.k.a. $_GET key.
   *
   * @return string
   */
  public function getIdentifier() {
    return !empty($this->filter_handler->options['is_grouped']) ?
      $this->filter_handler->options['group_info']['identifier'] :
      $this->filter_handler->options['expose']['identifier'];
  }

  /**
   * Get filter label as input by user.
   *
   * @return string
   */
  public function getLabel() {
    return isset($this->filter_handler->options['expose']['label']) ?
      $this->filter_handler->options['expose']['label'] : '';
  }

  /**
   * Get filter label for use within EVI.
   *
   * @return string
   */
  public function GetEviLabel() {
    // Provide label
    $identifier = $this->getIdentifier();
    $t_args = array('%identifier' => $identifier);
    $label = $this->getLabel();
    if ($label) {
      $t_args['%label'] = $label;
      $evi_label = format_string('%identifier (%label)', $t_args);
    }
    else {
      $evi_label = format_string('%identifier', $t_args);
    }
    return $evi_label;
  }

  /**
   * Get current display handler.
   *
   * @return views_plugin_display
   */
  public function getDisplayHandler() {
    $view = $this->filter_handler->view;
    $display_handler = $view->display[$view->current_display]->handler;
    return $display_handler;
  }

  /**
   * Get EVI display extender class.
   *
   * @return ViewsEviDisplayExtender
   */
  public function getEvi() {
    $display_handler = $this->getDisplayHandler();
    return $display_handler->extender['views_evi'];
  }

  /**
   * Get filter options.
   *
   * @param ViewsEviFilterWrapper $filter_wrapper
   * @return array
   */
  public function getEviFilterOptions($section) {
    /** @var views_plugin_display $display_handler */
    $display_handler = $this->getDisplayHandler();
    $section_options = $display_handler->get_option($section);
    $filter_id = $this->getId();

    $options = (array)@$section_options['filters'][$filter_id];
    return $options;
  }

  /**
   * Get plugin class name.
   *
   * @param string $plugin_type
   * @return string
   */
  public function getPluginClass($plugin_type) {
    $filter_options = $this->getEviFilterOptions('views_evi_plugins');
    $plugin_class = @$filter_options[$plugin_type] ?: $this->getDefaultPluginClass($plugin_type);
    return $plugin_class;
  }

  /** @var ViewsEviHandlerBase $plugin */
  private $plugin;

  /**
   * Get plugin.
   *
   * @param string $plugin_type
   * @return ViewsEviHandlerInterface
   */
  public function getPlugin($plugin_type) {
    $plugin_class = $this->getPluginClass($plugin_type);
    if (empty($this->plugin[$plugin_type])) {
      $this->plugin[$plugin_type] = new $plugin_class($this);
    }
    return $this->plugin[$plugin_type];
  }

  /**
   * Get default plugin class.
   *
   * @param string $plugin_type
   * @return string
   */
  public function getDefaultPluginClass($plugin_type) {
    $plugin_types = views_evi_plugin_types();
    return $plugin_types[$plugin_type]['default_class'];
  }

  /**
   * Get plugin settings.
   *
   * @param $plugin_type
   * @return array
   */
  public function getPluginSettings($plugin_type) {
    $filter_options = $this->getEviFilterOptions('views_evi_settings');
    $settings = @$filter_options[$plugin_type] ?: $this->getPlugin($plugin_type)->defaultSettings();
    return $settings;
  }

  /**
   * Get plugin settings by reference, for validating a partial array.
   *
   * @param string $plugin_type
   * @param array $all_options
   * @return array
   */
  public function &getPluginSettingsRef($plugin_type, &$all_options) {
    $filter_id = $this->getId();
    return $all_options['views_evi_settings']['filters'][$filter_id][$plugin_type];
  }

  /**
   * Set filter options.
   *
   * @param $section
   * @param array $filter_options
   * @return array
   */
  public function setEviFilterOptions($section, $filter_options) {
    /** @var views_plugin_display $display_handler */
    $display_handler = $this->getDisplayHandler();
    $section_options = $display_handler->get_option($section);
    $filter_id = $this->getId();
    $section_options['filters'][$filter_id] = $filter_options;
    $display_handler->set_option($section, $section_options);
  }

  /**
   * Set plugin class.
   *
   * @param string $plugin_type
   * @param string $plugin_class
   */
  public function setPluginClass($plugin_type, $plugin_class) {
    $filter_options = $this->getEviFilterOptions('views_evi_plugins');
    $filter_options[$plugin_type] = $plugin_class;
    $this->setEviFilterOptions('views_evi_plugins', $filter_options);
  }

  /**
   * Set plugin settings.
   *
   * @param string $plugin_type
   * @param array $settings
   */
  public function setPluginSettings($plugin_type, $settings) {
    $filter_options = $this->getEviFilterOptions('views_evi_settings');
    $filter_options[$plugin_type] = $settings;
    $this->setEviFilterOptions('views_evi_settings', $filter_options);
  }

  /**
   * @return bool
   */
  public function getVisibility(&$form) {
    /** @var ViewsEviVisibilityInterface $visibility_handler */
    $visibility_handler = $this->getPlugin('visibility');
    $visibility = $visibility_handler->getVisibility($form);
    return $visibility;
  }

  /**
   * @return string|null
   */
  public function getValue() {
    /** @var ViewsEviValueInterface $value_handler */
    $value_handler = $this->getPlugin('value');
    $value = $value_handler->getValue();
    return $value;
  }


}