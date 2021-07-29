<?php

/**
 * @file
 * Bootstrap blazepro template.php.
 */
include_once dirname(__FILE__) . '/includes/common.inc';
function belltowers_theme(&$existing, $type, $theme, $path) {
  belltowers_include($theme, 'includes/registry.inc');
  return _belltowers_theme($existing, $type, $theme, $path);
}
belltowers_include('belltowers', 'includes/alter.inc');

/**
 * Implements hook_preprocess_page().
 *
 * @see page.tpl.php
 */
function belltowers_preprocess_page(&$variables) {
  if (!empty($variables['page']['sidebar_first']) && !empty($variables['page']['sidebar_second'])) {
    $variables['content_column_class'] = ' class="col-sm-6"';
  }
  elseif (!empty($variables['page']['sidebar_first']) || !empty($variables['page']['sidebar_second'])) {
    $variables['content_column_class'] = ' class="col-sm-9"';
  }
  else {
    $variables['content_column_class'] = ' class="col-sm-12"';
  }

  // Primary nav.
  $variables['primary_nav'] = FALSE;
  if ($variables['main_menu']) {
    // Build links.
    $variables['primary_nav'] = menu_tree(variable_get('menu_main_links_source', 'main-menu'));
    // Provide default theme wrapper function.
    $variables['primary_nav']['#theme_wrappers'] = array('menu_tree__primary');
  }

  // Secondary nav.
  $variables['secondary_nav'] = FALSE;
  if ($variables['secondary_menu']) {
    // Build links.
    $variables['secondary_nav'] = menu_tree(variable_get('menu_secondary_links_source', 'user-menu'));
    // Provide default theme wrapper function.
    $variables['secondary_nav']['#theme_wrappers'] = array('menu_tree__secondary');
  }

  $variables['navbar_classes_array'] = array('navbar');

  if (theme_get_setting('bootstrap_navbar_position') !== '') {
    $variables['navbar_classes_array'][] = 'navbar-' . theme_get_setting('bootstrap_navbar_position');
  }
  else {
    $variables['navbar_classes_array'][] = 'container';
  }
  if (theme_get_setting('bootstrap_navbar_inverse')) {
    $variables['navbar_classes_array'][] = 'navbar-inverse';
  }
  else {
    $variables['navbar_classes_array'][] = 'navbar-default';
  }
  if (($key = array_search('container', $variables['navbar_classes_array'])) !== FALSE) {
    unset($variables['navbar_classes_array'][$key]);
  }
  $variables['navbar_classes_array'][] = 'container-fluid';
  
  if(drupal_is_front_page()) {
    $vars['theme_hook_suggestions'][] = 'page__front';
    
  } elseif (isset($variables['node']->type) && !empty($variables['node']->type)) {
    $variables['theme_hook_suggestions'][] = 'page__node__' . $variables['node']->type;
  	
  } else  {
    $vars['theme_hook_suggestions'][] = 'page';
  }
  
}

/**
 * Implements hook_process_page().
 *
 * @see page.tpl.php
 */
function belltowers_process_page(&$variables) {
  $variables['navbar_classes'] = implode(' ', $variables['navbar_classes_array']);
}

$art_style = '';
$art_head = '';
function belltowers_process_html(&$variables) {
    global $art_style, $art_head;
	$themePath = base_path() . path_to_theme();
	$jqueryNoConflict = <<< EOT
<script>if ('undefined' != typeof jQuery) document._artxJQueryBackup = jQuery;</script>
<script type="text/javascript" src="$themePath/js/jquery.min.js"></script>
<script>jQuery.noConflict();</script>

$art_head
<script>if (document._artxJQueryBackup) jQuery = document._artxJQueryBackup;</script>
EOT;
	$variables['scripts'] .= $jqueryNoConflict;
}

/**
 * Implements hook_preprocess_html().
 *
 * @see html.tpl.php
 */
function belltowers_preprocess_html(&$variables) {
  switch (theme_get_setting('bootstrap_navbar_position')) {
    case 'fixed-top':
      $variables['classes_array'][] = 'navbar-is-fixed-top';
      break;

    case 'fixed-bottom':
      $variables['classes_array'][] = 'navbar-is-fixed-bottom';
      break;

    case 'static-top':
      $variables['classes_array'][] = 'navbar-is-static-top';
      break;
  }
  //if (($key = array_search('navbar-is-fixed-top', $variables['classes_array'])) !== FALSE) {
  //  unset($variables['classes_array'][$key]);
 // }
  $variables['attributes_array']['data-target'] = '.navbar-collapse';
  $variables['attributes_array']['data-spy'] = 'scroll';
  $variables['attributes_array']['id'] = 'page-top';
}

/**
 * Implements hook_process_html_tag().
 */
function belltowers_process_html_tag(&$variables) {
  $tag = &$variables['element'];
  if ($tag['#tag'] == 'style' || $tag['#tag'] == 'script') {
    // Remove redundant type attribute and CDATA comments.
    unset($tag['#attributes']['type'], $tag['#value_prefix'], $tag['#value_suffix']);
    // Remove media="all" but leave others unaffected.
    if (isset($tag['#attributes']['media']) && $tag['#attributes']['media'] === 'all') {
      unset($tag['#attributes']['media']);
    }
  }
}

/**
 * Implements hook_preprocess_block().
 *
 * @see block.tpl.php
 */
function belltowers_preprocess_block(&$variables) {
  $block = $variables['block'];

  // Create css id attribute based on the block's administrative name.
  if ($block->module == 'block') {
    $custom = block_custom_block_get($block->delta);

    $variables['block_html_id'] = drupal_html_id($custom['info']);
  }

}

/**
 * Implements theme_textarea().
 */
function belltowers_textarea($element) {
  // Drupal likes resizable text areas, we don't.
  $element['element']['#resizable'] = FALSE;
  return theme_textarea($element);
}
