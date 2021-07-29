<?php
$plugin = array(
  'label' => t('Value with tokens'),
);
/**
 * @class
 * Interface for EVI value.
 */

abstract class ViewsEviValueTokenBase extends ViewsEviHandlerTokenBase implements ViewsEviHandlerTokenInterface, ViewsEviValueInterface {
  public function getHandlerType() {
    return 'value';
  }
}