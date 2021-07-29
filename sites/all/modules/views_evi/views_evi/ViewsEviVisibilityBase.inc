<?php
/**
 * @class
 * Interface for EVI value.
 */

abstract class ViewsEviVisibilityBase extends ViewsEviHandlerBase implements ViewsEviVisibilityInterface {
  public function getHandlerType() {
    return 'visibility';
  }
}