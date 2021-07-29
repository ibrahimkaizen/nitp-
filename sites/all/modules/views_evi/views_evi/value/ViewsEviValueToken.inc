<?php
$plugin = array(
  'label' => t('Value with tokens'),
);
/**
 * @class
 * Interface for EVI value.
 */

class ViewsEviValueToken extends ViewsEviValueTokenBase implements ViewsEviHandlerTokenInterface, ViewsEviValueInterface {
  public function settingsForm($settings, &$form) {

    $settings_form = parent::settingsForm($settings, $form);

    // Return our plugin settings form.
    $settings_form['value'] = array(
      '#type' => 'textfield',
      '#title' => t('Filter value'),
      '#description' => t('You can use replacement tokens as listed below. This is known not to work for nested values like date and price field filters.'),
      '#default_value' => $settings['value'],
    );
    return $settings_form;
  }

  public function defaultSettings() {
    $filter_identifier = $this->getFilterWrapper()->getIdentifier();
    return array('value' => "[form:$filter_identifier]");
  }

  public function getValue() {
    $settings = $this->getFilterWrapper()->getPluginSettings('value');
    $value_with_tokens = $settings['value'];

    $token_replacements = $this->getTokenReplacements();
    $value = strtr($value_with_tokens, $token_replacements);
    $identifier = $this->getFilterWrapper()->getIdentifier();

    return $value !== '' ? array($identifier => $value) : array();
  }

}