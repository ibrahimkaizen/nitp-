<?php
/**
 * @file   phelan.inc
 * @date   Tue Dec 18 9:50:00 2012
 * @brief  The panels layout plugin for the phelan panels layout.
 *
 *
 */

// Plugin definition
$plugin = array(
  'title' => t('Phelan'),
  'icon' => 'phelan.png',
  'category' => t('Panopoly'),
  'theme' => 'phelan',
  'css' => 'phelan.css',
  'regions' => array(
    'column1' => t('First Column'),
    'column2' => t('Second Column'),
  ),
);
