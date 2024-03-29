<?php
/**
 * @class
 * Interface for EVI value.
 */

interface ViewsEviHandlerTokenInterface extends ViewsEviHandlerInterface {
  /**
   * Get token replacements.
   *
   * @param bool $ui
   *   Return token descriptions for the UI instead of values.
   * @return array
   */
  function getTokenReplacements($ui = FALSE);
}