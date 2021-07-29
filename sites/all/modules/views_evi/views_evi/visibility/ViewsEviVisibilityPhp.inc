<?php
$plugin = array(
  'label' => t('Visibility from PHP code'),
);
/**
 * @class
 * Interface for EVI value.
 */

class ViewsEviVisibilityPhp extends ViewsEviVisibilityTokenBase implements ViewsEviHandlerTokenInterface, ViewsEviVisibilityInterface {
  public function settingsForm($settings, &$form) {

    $settings_form = parent::settingsForm($settings, $form);

    // Return our plugin settings form.
    $access = user_access('use php for views_evi');
    $settings_form['php'] = array(
      '#type' => 'textarea',
      '#title' => t('Visibility PHP code'),
      '#description' => t('Do not use &lt;?php tags and return a boolean value. You can use $identifier, $view, $display_handler, $filter_handler$evi and $tokens. The brave even alter $form[$identifier] and $form[\'#info\']["filter-$id"].'),
      '#default_value' => $settings['php'],
      '#disabled' => !$access,
    );
    return $settings_form;
  }

  public function defaultSettings() {
    return array('php' => 'return empty($tokens[$identifier]);');
  }

  public function getVisibility(&$form) {
    $filter_wrapper = $this->getFilterWrapper();
    $settings = $filter_wrapper->getPluginSettings('visibility');
    $php_value = $settings['php'];
    $identifier = $filter_wrapper->getIdentifier();
    $id = $filter_wrapper->getId();
    $tokens = $this->getTokenReplacements();
    $display_handler = $filter_wrapper->getDisplayHandler();
    $filter_handler = $filter_wrapper->getFilterHandler();
    $evi = $filter_wrapper->getEvi();
    $view = $display_handler->view;

    $visibility = eval($php_value);
    return $visibility;
  }

}