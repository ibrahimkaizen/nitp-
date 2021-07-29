<?php
/**
 * @class
 * Interface for EVI value.
 */

abstract class ViewsEviHandlerBase implements ViewsEviHandlerInterface {
  /** @var \ViewsEviFilterWrapper $filter_wrapper */
  private $filter_wrapper;

  public function __construct(ViewsEviFilterWrapper $filter_wrapper) {
    $this->filter_wrapper = $filter_wrapper;
  }
  /**
   * @return \ViewsEviFilterWrapper
   */
  public function getFilterWrapper() {
    return $this->filter_wrapper;
  }
  public function settingsForm($settings, &$form) {
    return array();
  }
  public function settingsFormValidate(&$form_values) {}
  public function settingsFormSubmit($form_values) {
    return $form_values;
  }
  public function defaultSettings() {
    return array();
  }
}
