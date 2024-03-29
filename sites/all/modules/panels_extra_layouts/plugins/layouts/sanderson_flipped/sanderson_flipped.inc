<?php
/**
 * @file   sanderson_flipped.inc
 * @date   Tue Dec 18 9:41:00 2012
 * @brief  The panels layout plugin for the sanderson flipped panels layout.
 *
 *
 */

// Plugin definition
$plugin = array(
  'title' => t('Sanderson Flipped'),
  'icon' => 'sanderson-flipped.png',
  'category' => t('Panopoly'),
  'theme' => 'sanderson_flipped',
  'css' => 'sanderson-flipped.css',
  'regions' => array(
    'column1' => t('Row 1: First Column'),
    'column2' => t('Row 1: Second Column'),
    'column3' => t('Row 1: Third Column'),
    'secondarycolumn1' => t('Row 2: First Column'),
    'secondarycolumn2' => t('Row 2: Second Column'),
  ),
);
