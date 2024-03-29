<?php
/**
 * @file   selby.inc
 * @date   Tue Dec 18 9:50:00 2012
 * @brief  The panels layout plugin for the selby  panels layout.
 *
 *
 */

// Plugin definition
$plugin = array(
  'title' => t('Selby'),
  'icon' => 'selby.png',
  'category' => t('Panopoly'),
  'theme' => 'selby',
  'css' => 'selby.css',
  'regions' => array(
    'sidebar' => t('Sidebar'),
    'contentheader' => t('Content Header'),
    'contentcolumn1' => t('Content Column 1'),
    'contentcolumn2' => t('Content Column 2'),
    'contentfooter' => t('Content Footer'),
  ),
);
