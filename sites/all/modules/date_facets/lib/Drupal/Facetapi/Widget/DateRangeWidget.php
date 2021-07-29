<?php

/**
 * @file
 * Contains Drupal_Apachesolr_Facetapi_QueryType_DateRangeQueryType
 */

/**
 * Date range widget that displays ranges similar to major search engines.
 *
 * There is a hack in place that only allows one item to be active at a time
 * since if would make sense to have multiple active values.
 */
class Drupal_Apachesolr_Facetapi_Widget_DateRangeWidget extends FacetapiWidgetLinks {

  /**
   * Overrides FacetapiWidget::settingsForm().
   */
  function settingsForm(&$form, &$form_state) {
    parent::settingsForm($form, $form_state);
    unset($form['widget']['widget_settings']['links'][$this->id]['soft_limit']);
    unset($form['widget']['widget_settings']['links'][$this->id]['show_expanded']);

    $form['widget']['widget_settings']['date_ranges'] = array(
      '#type' => 'fieldset',
      '#title' => t('Configured Date Ranges'),
      '#tree' => TRUE,
      '#attributes' => array('class' => array('clearfix')),
      '#states' => array(
        'visible' => array(
          array(
            array('select[name="widget"]' => array('value' => 'date_range')),
            'or',
            array('select[name="widget"]' => array('value' => 'date_range_checkboxes'))
          ),
        ),
      ),
    );
    $form['widget']['widget_settings']['ranges'] = array(
      '#type' => 'container',
      '#title' => t('Configured Date Ranges'),
      '#tree' => TRUE,
    );
    if (!isset($this->settings->settings['ranges'])) {
      $this->settings->settings['ranges'] = date_facets_default_ranges();
    }
    uasort($this->settings->settings['ranges'], 'drupal_sort_weight');
    foreach($this->settings->settings['ranges'] as $range_data) {
      $form['widget']['widget_settings']['ranges'][$range_data['machine_name']]['label'] = array(
        '#type' => 'textfield',
        '#title' => t('Label'),
        '#default_value' => (isset($range_data['label']) ? $range_data['label'] : NULL),
        '#size' => 40,
        '#tree' => TRUE,
      );
      $form['widget']['widget_settings']['ranges'][$range_data['machine_name']]['machine_name'] = array(
        '#type' => 'machine_name',
        '#default_value' => (isset($range_data['machine_name']) ? $range_data['machine_name'] : NULL),
        '#maxlength' => 20,
        '#machine_name' => array(
          'exists' => 'date_facets_date_range_exists',
          'source' => array('widget', 'widget_settings', 'ranges', $range_data['machine_name'], 'label'),
        ),
        '#tree' => TRUE,
      );
      $form['widget']['widget_settings']['ranges'][$range_data['machine_name']]['date_range_start_op'] = array(
        '#prefix' => t('FROM'),
        '#type' => 'select',
        '#title' => t('Date Range'),
        '#default_value' => (isset($range_data['date_range_start_op']) ? $range_data['date_range_start_op'] : NULL),
        '#options' => array(
          'NOW' => t('today'),
          '-' => t('past'),
          '+' => t('future'),
        ),
        '#tree' => TRUE,
      );
      $form['widget']['widget_settings']['ranges'][$range_data['machine_name']]['date_range_start_amount'] = array(
        '#type' => 'textfield',
        '#title' => t('Date Range'),
        '#default_value' => (isset($range_data['date_range_start_amount']) ? $range_data['date_range_start_amount'] : NULL),
        '#size' => 5,
        '#tree' => TRUE,
        '#states' => array(
          'invisible' => array(
            ':input[name*="' . $range_data['machine_name'] . '][date_range_start_op]"]' => array('value' => 'NOW'),
          ),
        ),
      );
      $form['widget']['widget_settings']['ranges'][$range_data['machine_name']]['date_range_start_unit'] = array(
        '#type' => 'select',
        '#title' => t('Date Range'),
        '#default_value' => (isset($range_data['date_range_start_unit']) ? $range_data['date_range_start_unit'] : NULL),
        '#options' => array(
          'HOUR' => t('hour'),
          'DAY' => t('day'),
          'MONTH' => t('month'),
          'YEAR' => t('year'),
        ),
        '#states' => array(
          'invisible' => array(
            ':input[name*="' . $range_data['machine_name'] . '][date_range_start_op]"]' => array('value' => 'NOW'),
          ),
        ),
        '#tree' => TRUE,
      );
      $form['widget']['widget_settings']['ranges'][$range_data['machine_name']]['date_range_end_op'] = array(
        '#prefix' => t('TO'),
        '#type' => 'select',
        '#title' => t('Date Range'),
        '#default_value' => (isset($range_data['date_range_end_op']) ? $range_data['date_range_end_op'] : NULL),
        '#options' => array(
          'NOW' => t('today'),
          '-' => t('past'),
          '+' => t('future'),
        ),
        '#tree' => TRUE,
      );
      $form['widget']['widget_settings']['ranges'][$range_data['machine_name']]['date_range_end_amount'] = array(
        '#type' => 'textfield',
        '#title' => t('Date Range'),
        '#default_value' => (isset($range_data['date_range_end_amount']) ? $range_data['date_range_end_amount'] : NULL),
        '#size' => 5,
        '#tree' => TRUE,
        '#states' => array(
          'invisible' => array(
            ':input[name*="' . $range_data['machine_name'] . '][date_range_end_op]"]' => array('value' => 'NOW'),
          ),
        ),
      );
      $form['widget']['widget_settings']['ranges'][$range_data['machine_name']]['date_range_end_unit'] = array(
        '#type' => 'select',
        '#title' => t('Date Range'),
        '#default_value' => (isset($range_data['date_range_end_unit']) ? $range_data['date_range_end_unit'] : NULL),
        '#options' => array(
          'HOUR' => t('hour'),
          'DAY' => t('day'),
          'MONTH' => t('month'),
          'YEAR' => t('year'),
        ),
        '#states' => array(
          'invisible' => array(
            ':input[name*="' . $range_data['machine_name'] . '][date_range_end_op]"]' => array('value' => 'NOW'),
          ),
        ),
        '#tree' => TRUE,
      );
      $form['widget']['widget_settings']['ranges'][$range_data['machine_name']]['weight'] = array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        '#default_value' => (isset($range_data['weight']) ? $range_data['weight'] : NULL),
        '#delta' => 10,
        '#attributes' => array('class' => array('date-range-weight')),
        '#tree' => TRUE,
      );
      $form['widget']['widget_settings']['ranges'][$range_data['machine_name']]['delete'] = array(
        '#type' => 'checkbox',
        '#title' => t('Delete'),
        '#tree' => TRUE,
      );
    }

    // The new range button
    if (isset($form_state['add_new_range']) && $form_state['add_new_range']) {
      $form_state['add_new_range'] = FALSE;
      $form['widget']['widget_settings']['ranges']['temp']['label'] = array(
        '#type' => 'textfield',
        '#title' => t('Label'),
        '#size' => 40,
        '#tree' => TRUE,
      );
      $form['widget']['widget_settings']['ranges']['temp']['machine_name'] = array(
        '#type' => 'machine_name',
        '#maxlength' => 20,
        '#machine_name' => array(
          'exists' => 'date_facets_date_range_exists',
          'source' => array('widget', 'widget_settings', 'ranges', 'temp', 'label'),
        ),
        '#tree' => TRUE,
      );
      $form['widget']['widget_settings']['ranges']['temp']['date_range_start_op'] = array(
        '#type' => 'select',
        '#title' => t('Date Range'),
        '#options' => array(
          'NOW' => t('today'),
          '-' => t('past'),
          '+' => t('future'),
        ),
        '#tree' => TRUE,
      );
      $form['widget']['widget_settings']['ranges']['temp']['date_range_start_amount'] = array(
        '#type' => 'textfield',
        '#title' => t('Date Range'),
        '#size' => 5,
        '#tree' => TRUE,
        '#states' => array(
          'invisible' => array(
            ':input[name*="temp][date_range_start_op]"]' => array('value' => 'NOW'),
          ),
        ),
      );
      $form['widget']['widget_settings']['ranges']['temp']['date_range_start_unit'] = array(
        '#type' => 'select',
        '#title' => t('Date Range'),
        '#options' => array(
          'HOUR' => t('hour'),
          'DAY' => t('day'),
          'MONTH' => t('month'),
          'YEAR' => t('year'),
        ),
        '#states' => array(
          'invisible' => array(
            ':input[name*="temp][date_range_start_op]"]' => array('value' => 'NOW'),
          ),
        ),
        '#tree' => TRUE,
      );
      $form['widget']['widget_settings']['ranges']['temp']['date_range_end_op'] = array(
        '#type' => 'select',
        '#title' => t('Date Range'),
        '#options' => array(
          'NOW' => t('today'),
          '-' => t('past'),
          '+' => t('future'),
        ),
        '#tree' => TRUE,
      );
      $form['widget']['widget_settings']['ranges']['temp']['date_range_end_amount'] = array(
        '#type' => 'textfield',
        '#title' => t('Date Range'),
        '#size' => 5,
        '#tree' => TRUE,
        '#states' => array(
          'invisible' => array(
            ':input[name*="temp][date_range_end_op]"]' => array('value' => 'NOW'),
          ),
        ),
      );
      $form['widget']['widget_settings']['ranges']['temp']['date_range_end_unit'] = array(
        '#type' => 'select',
        '#title' => t('Date Range'),
        '#options' => array(
          'HOUR' => t('hour'),
          'DAY' => t('day'),
          'MONTH' => t('month'),
          'YEAR' => t('year'),
        ),
        '#states' => array(
          'invisible' => array(
            ':input[name*="temp][date_range_end_op]"]' => array('value' => 'NOW'),
          ),
        ),
        '#tree' => TRUE,
      );
      $form['widget']['widget_settings']['ranges']['temp']['weight'] = array(
        '#type' => 'weight',
        '#title' => t('Weight'),
        '#delta' => 10,
        '#attributes' => array('class' => array('date-range-weight')),
        '#tree' => TRUE,
      );
      $form['widget']['widget_settings']['ranges']['temp']['delete'] = array(
        '#type' => 'checkbox',
        '#title' => t('Delete'),
        '#tree' => TRUE,
        '#states' => array(
          'checked' => array(
            ':input[name*="temp][label]"]' => array('value' => ''),
          ),
        ),
      );
    }
    else {
      $form['widget']['widget_settings']['date_ranges']['add_range'] = array(
        '#type' => 'button',
        '#executes_submit_callback' => FALSE,
        '#value' => t('Add a new date range'),
        '#limit_validation_errors' => array(),
        '#ajax' => array(
          'callback' => 'date_facets_tabledrag_form_new_range',
          'wrapper' => 'date_facets_facet_config_form',
          'method' => 'replace',
          'effect' => 'fade',
        ),
        '#weight' => 10,
      );
    }

    $form['#validate'] = empty($form['#validate']) ? array() : $form['#validate'];
    $form['#submit'] = empty($form['#submit']) ? array() : $form['#submit'];
    $form['#validate'][] = 'date_facets_tabledrag_form_validate';
    $form['#submit'][] = 'date_facets_facet_settings_form_submit';

    $form['#theme'] = 'date_facets_tabledrag_form';
    $form['#prefix'] = '<div id="date_facets_facet_config_form">';
    $form['#suffix'] = '</div>';
  }

  /**
   * Overrides FacetapiWidget::getDefaultSettings().
   */
  function getDefaultSettings() {
    return array(
      'nofollow' => 1,
    );
  }
}
