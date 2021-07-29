<?php
$plugin = array(
  'label' => t('Visible if no value'),
);
/**
 * @class
 * Interface for EVI visibility.
 */

class ViewsEviVisibilityFallback extends ViewsEviVisibilityTokenBase implements ViewsEviHandlerTokenInterface, ViewsEviVisibilityInterface {

  public function settingsForm($settings, &$form) {

    $settings_form = parent::settingsForm($settings, $form);

    // Return our plugin settings form.
    $settings_form['value'] = array(
      '#type' => 'textfield',
      '#title' => t('Visibility inhibiting value'),
      '#description' => t('Form element will be visible if result value is empty. You can use replacement tokens as listed below.'),
      '#default_value' => $settings['value'],
    );
    return $settings_form;
  }

  public function defaultSettings() {
    $filter_identifier = $this->getFilterWrapper()->getIdentifier();
    return array('value' => "[form:$filter_identifier]");
  }

  public function getVisibility(&$form){
    $settings = $this->getFilterWrapper()->getPluginSettings('visibility');
    $value_with_tokens = $settings['value'];

    $token_replacements = $this->getTokenReplacements();
    $value = strtr($value_with_tokens, $token_replacements);

    return $value == '';
  }
}