<?php
/**
 * @file
 * alter.inc
 *
 * Contains various implementations of hook_*_alter().
 */

/**
 * Implements hook_element_info_alter().
 */
function belltowers_element_info_alter(&$elements) {
  foreach ($elements as &$element) {
    // Process all elements.
    $element['#process'][] = '_belltowers_process_element';
    // Process input elements.
    if (!empty($element['#input'])) {
      $element['#process'][] = '_belltowers_process_input';
    }
    // Process core's fieldset element.
    if (!empty($element['#type']) && $element['#type'] === 'fieldset') {
      $element['#theme_wrappers'] = array('bootstrap_panel');
    }
    if (!empty($element['#theme']) && $element['#theme'] === 'fieldset') {
      $element['#theme'] = 'bootstrap_panel';
    }
    // Replace #process function.
    if (!empty($element['#process']) && ($key = array_search('form_process_fieldset', $element['#process'])) !== FALSE) {
      $element['#process'][$key] = '_belltowers_process_fieldset';
    }
    // Replace #pre_render function.
    if (!empty($element['#pre_render']) && ($key = array_search('form_pre_render_fieldset', $element['#pre_render'])) !== FALSE) {
      $element['#pre_render'][$key] = '_belltowers_pre_render_fieldset';
    }
    // Replace #theme_wrappers function.
    if (!empty($element['#theme_wrappers']) && ($key = array_search('fieldset', $element['#theme_wrappers'])) !== FALSE) {
      $element['#theme_wrappers'][$key] = 'bootstrap_panel';
    }
  }
}

/**
 * Implements hook_form_alter().
 */
function belltowers_form_alter(array &$form, array &$form_state = array(), $form_id = NULL) {
  if ($form_id) {

    $form_ids = array(
      'node_form',
      'system_site_information_settings',
      'user_profile_form',
      'node_delete_confirm',
    );
    // Only wrap in container for certain form.
    if (!in_array($form_id, $form_ids) && !isset($form['#node_edit_form']) && isset($form['actions']) && isset($form['actions']['#type']) && ($form['actions']['#type'] == 'actions')) {
      $form['actions']['#theme_wrappers'] = array();
    }

    switch ($form_id) {   
      case 'search_form':
        // Add a clearfix class so the results don't overflow onto the form.
        $form['#attributes']['class'][] = 'clearfix';

        // Remove container-inline from the container classes.
        $form['basic']['#attributes']['class'] = array();

        // Hide the default button from display.
        $form['basic']['submit']['#attributes']['class'][] = 'element-invisible';

        // Implement a theme wrapper to add a submit button containing a search
        // icon directly after the input element.
        $form['basic']['keys']['#theme_wrappers'] = array('bootstrap_search_form_wrapper');
        $form['basic']['keys']['#title'] = '';
        $form['basic']['keys']['#attributes']['placeholder'] = t('Search');
        break;

      case 'search_block_form':
        $form['#attributes']['class'][] = 'form-search';

        $form['search_block_form']['#title'] = '';
        $form['search_block_form']['#attributes']['placeholder'] = t('Search');

        // Hide the default button from display and implement a theme wrapper
        // to add a submit button containing a search icon directly after the
        // input element.
        $form['actions']['submit']['#attributes']['class'][] = 'element-invisible';
        $form['search_block_form']['#theme_wrappers'] = array('bootstrap_search_form_wrapper');

        // Apply a clearfix so the results don't overflow onto the form.
        $form['#attributes']['class'][] = 'content-search';
        break;
    }

  }
}

/**
 * Implements hook_css_alter().
 */
function belltowers_css_alter(&$css) {
  $theme_path = drupal_get_path('theme', 'belltowers');
  $excludes = belltowers_get_theme_info(NULL, 'exclude][css');  
  if (!empty($excludes)) {
    $css = array_diff_key($css, drupal_map_assoc($excludes));
  }
}

/**
 * Implements hook_js_alter().
 */
function belltowers_js_alter(&$js) {
  $excludes = belltowers_get_theme_info(NULL, 'exclude][js');
  $theme_path = drupal_get_path('theme', 'belltowers');

  $files = file_scan_directory($theme_path . '/js', '/\.js$/');
  foreach ($files as $file) {
    $path = str_replace($theme_path . '/js/', '', $file->uri);
    // Detect if this is a replacement file.
    $replace = FALSE;
    if (preg_match('/^[_]/', $file->filename)) {
      $replace = TRUE;
      $path = dirname($path) . '/' . preg_replace('/^[_]/', '', $file->filename);
    }
    $matches = array();
    if (preg_match('/^modules\/([^\/]*)/', $path, $matches)) {
      if (!module_exists($matches[1])) {
        continue;
      }
      else {
        $path = str_replace('modules/' . $matches[1], drupal_get_path('module', $matches[1]), $path);
      }
    }
    // Path should always exist to either add or replace JavaScript file.
    if (!empty($js[$path])) {
      // Replace file.
      if ($replace) {
        $js[$file->uri] = $js[$path];
        $js[$file->uri]['data'] = $file->uri;
        unset($js[$path]);
      }
      // Add file.
      else {
        $js[$file->uri] = drupal_js_defaults($file->uri);
        $js[$file->uri]['group'] = JS_THEME;
      }
    }
  }
  $bootstrap = $theme_path . '/js/bootstrap.integration.js';
  $js[$bootstrap] = drupal_js_defaults($bootstrap);
  $js[$bootstrap]['group'] = JS_THEME;
  $js[$bootstrap]['scope'] = 'footer';

  if (!empty($excludes)) {
    $js = array_diff_key($js, drupal_map_assoc($excludes));
  }

  // Add Bootstrap settings.
  $js['settings']['data'][]['bootstrap'] = array(
    'anchorsFix' => theme_get_setting('bootstrap_anchors_fix'),
    'anchorsSmoothScrolling' => theme_get_setting('bootstrap_anchors_smooth_scrolling'),
    'popoverEnabled' => theme_get_setting('bootstrap_popover_enabled'),
    'popoverOptions' => array(
      'animation' => (int) theme_get_setting('bootstrap_popover_animation'),
      'html' => (int) theme_get_setting('bootstrap_popover_html'),
      'placement' => theme_get_setting('bootstrap_popover_placement'),
      'selector' => theme_get_setting('bootstrap_popover_selector'),
      'trigger' => implode(' ', array_filter(array_values((array) theme_get_setting('bootstrap_popover_trigger')))),
      'title' => theme_get_setting('bootstrap_popover_title'),
      'content' => theme_get_setting('bootstrap_popover_content'),
      'delay' => (int) theme_get_setting('bootstrap_popover_delay'),
      'container' => theme_get_setting('bootstrap_popover_container'),
    ),
    'tooltipEnabled' => theme_get_setting('bootstrap_tooltip_enabled'),
    'tooltipOptions' => array(
      'animation' => (int) theme_get_setting('bootstrap_tooltip_animation'),
      'html' => (int) theme_get_setting('bootstrap_tooltip_html'),
      'placement' => theme_get_setting('bootstrap_tooltip_placement'),
      'selector' => theme_get_setting('bootstrap_tooltip_selector'),
      'trigger' => implode(' ', array_filter(array_values((array) theme_get_setting('bootstrap_tooltip_trigger')))),
      'delay' => (int) theme_get_setting('bootstrap_tooltip_delay'),
      'container' => theme_get_setting('bootstrap_tooltip_container'),
    ),
  );

}

belltowers_include('belltowers', 'includes/pre-render.inc');
belltowers_include('belltowers', 'includes/process.inc');
