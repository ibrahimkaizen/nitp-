<?php
$plugin = array(
  'label' => t('Value with tokens'),
);
/**
 * @class
 * Interface for EVI value.
 */

abstract class ViewsEviVisibilityTokenBase extends ViewsEviHandlerTokenBase implements ViewsEviHandlerTokenInterface, ViewsEviVisibilityInterface {
  public function getHandlerType() {
    return 'visibility';
  }
}