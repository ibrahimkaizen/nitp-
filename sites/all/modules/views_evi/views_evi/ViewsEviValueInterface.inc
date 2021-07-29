<?php
/**
 * @class
 * Interface for EVI value.
 */

interface ViewsEviValueInterface extends ViewsEviHandlerInterface {
  /**
   * @param ViewsEviFilterWrapper $filter_wrapper
   * @return array
   */
  public function getValue();
}