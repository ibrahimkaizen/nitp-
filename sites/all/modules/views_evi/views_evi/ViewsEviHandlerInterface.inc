<?php
/**
 * @class
 * Interface for EVI value.
 */

interface ViewsEviHandlerInterface {
  /**
   * @param ViewsEviFilterWrapper $filter_wrapper
   */
  public function __construct(ViewsEviFilterWrapper $filter_wrapper);
  /**
   * @return string
   */
  public function getHandlerType();
  /**
   * @return \ViewsEviFilterWrapper
   */
  public function getFilterWrapper();

  /**
   * @param array $settings
   * @param array $form
   * @return array
   */
  public function settingsForm($settings, &$form);

  /**
   * @param array $form_values
   */
  public function settingsFormValidate(&$form_values);

  /**
   * @param array $form_values
   * @return array
   */
  public function settingsFormSubmit($form_values);

  /**
   * @return array
   */
  public function defaultSettings();
}