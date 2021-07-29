<?php
/**
 * @class
 * Interface for EVI value.
 */

abstract class ViewsEviValueBase extends ViewsEviHandlerBase implements ViewsEviValueInterface {
  public function getHandlerType() {
    return 'value';
  }
}