<?php
/**
 * @class
 * Interface for EVI visibility.
 */

interface ViewsEviVisibilityInterface extends ViewsEviHandlerInterface {
  /**
   * @return bool|null
   */
  public function getVisibility(&$form);
}