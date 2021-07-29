<?php
$plugin = array(
  'label' => t('Value from PHP code'),
);
/**
 * @class
 * Interface for EVI value.
 */

class ViewsEviValuePhp extends ViewsEviValueTokenBase implements ViewsEviHandlerTokenInterface, ViewsEviValueInterface {
  public function settingsForm($settings, &$form) {

    $settings_form = parent::settingsForm($settings, $form);

    // Return our plugin settings form.
    $access = user_access('use php for views_evi');
    $settings_form['php'] = array(
      '#type' => 'textarea',
      '#title' => t('Value PHP code'),
      '#description' => t('Do not use &lt;?php tags and return an array of input overrides. You can use $identifier, $view, $display_handler, $filter_handler, $evi and $tokens.'),
      '#default_value' => $settings['php'],
      '#disabled' => !$access,
    );
    return $settings_form;
  }

  public function defaultSettings() {
    return array('php' => 'return array($identifier => $tokens["[form:$identifier]"]);');
  }

  public function getValue() {
    $filter_wrapper = $this->getFilterWrapper();
    $settings = $filter_wrapper->getPluginSettings('value');
    $php_value = $settings['php'];
    $identifier = $filter_wrapper->getIdentifier();
    $id = $filter_wrapper->getId();
    $tokens = $this->getTokenReplacements();
    $display_handler = $filter_wrapper->getDisplayHandler();
    $filter_handler = $filter_wrapper->getFilterHandler();
    $evi = $filter_wrapper->getEvi();
    $view = $display_handler->view;
    $value = eval($php_value);
    return $value ?: array();
  }

}