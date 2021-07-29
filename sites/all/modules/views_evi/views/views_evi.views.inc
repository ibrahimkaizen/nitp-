<?php
/**
 * @file
 * Implements the display extender for Views EVI.
 */

/**
 * Implements hook_views_plugins
 */
function views_evi_views_plugins() {
  $plugins = array();
  $plugins['display_extender']['views_evi'] = array(
    'title' => t('Views EVI'),
    'help' => t('Inject values to exposed filters.'),
    'handler' => 'ViewsEviDisplayExtender',
    'enabled' => TRUE,
  );

  return $plugins;
}
