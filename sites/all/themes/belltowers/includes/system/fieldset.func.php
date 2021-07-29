<?php
/**
 * @file
 * fieldset.func.php
 */

/**
 * Overrides theme_fieldset().
 */
function belltowers_fieldset($variables) {
  return theme('bootstrap_panel', $variables);
}
