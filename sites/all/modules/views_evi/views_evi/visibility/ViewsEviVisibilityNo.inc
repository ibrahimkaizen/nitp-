<?php
$plugin = array(
  'label' => t('Invisible'),
);
/**
 * @class
 * Interface for EVI visibility.
 */

class ViewsEviVisibilityNo extends ViewsEviVisibilityBase implements ViewsEviVisibilityInterface {
  public function getVisibility(&$form){
    return FALSE;
  }
}