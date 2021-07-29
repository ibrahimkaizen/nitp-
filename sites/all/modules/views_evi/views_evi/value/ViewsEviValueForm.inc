<?php
$plugin = array(
  'label' => t('Exposed form'),
);
/**
 * @class
 * Interface for EVI value.
 */

class ViewsEviValueForm extends ViewsEviValueBase implements ViewsEviValueInterface {
  public function getValue() {
    return array();
  }
}