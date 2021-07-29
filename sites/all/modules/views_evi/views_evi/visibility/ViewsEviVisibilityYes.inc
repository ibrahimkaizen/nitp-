<?php
$plugin = array(
  'label' => t('Visible'),
);
/**
 * @class
 * Interface for EVI visibility.
 */

class ViewsEviVisibilityYes extends ViewsEviVisibilityBase implements ViewsEviVisibilityInterface {
  public function getVisibility(&$form){
    return TRUE;
  }
}