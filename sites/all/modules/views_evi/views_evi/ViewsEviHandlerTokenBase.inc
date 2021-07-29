<?php
$plugin = array(
  'label' => t('Value with tokens'),
);
/**
 * @class
 * Interface for EVI value.
 */

abstract class ViewsEviHandlerTokenBase extends ViewsEviHandlerBase implements ViewsEviHandlerTokenInterface {
  public function settingsForm($settings, &$form) {
    // Add our tokens to the whole form.
    $tokens = $this->getTokenReplacements(TRUE);
    $items = array();
    foreach($tokens as $token => $description) {
      $item = format_string('!k: !v', array('!k' => filter_xss($token), '!v' => filter_xss($description)));
      $items[] = $item;
    }

    $form['views_evi']['tokens'] = array(
      '#type' => 'fieldset',
      '#title' => t('Replacement tokens'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#weight' => 99,
    );
    $form['views_evi']['tokens']['value'] = array(
      '#theme' => 'item_list',
      '#items' => $items,
    );
    return array();
  }

  /**
   * Get token replacements.
   *
   * With code from @see \views_handler_field::get_render_tokens()
   */
  function getTokenReplacements($ui = FALSE) {

    $our_filter_wrapper = $this->getFilterWrapper();
    $evi = $our_filter_wrapper->getEvi();
    $display_handler = $evi->display;
    /** @var views_plugin_display $display_handler */
    $view = $display_handler->view;

    if ($cached = $evi->getViewsEviCache('ViewsEviValueToken', "replacements-$ui")) {
      return $cached;
    }

    /** @var views_plugin_display $display_handler */
    $display_handler = $view->display_handler;
    if (!isset($display_handler->extender['views_evi'])) {
      return array();
    }
    /** @var ViewsEviDisplayExtender $views_evi */
    $views_evi = $display_handler->extender['views_evi'];

    $replacements = array();

    // Argument tokens might have been set in view::_build_arguments()
    if (!empty($view->build_info['substitutions'])) {
      $replacements = $view->build_info['substitutions'];
    }

    // As a fallback we do set argument tokens.
    $count = 0;
    $argument_handlers = $view->display_handler->get_handlers('argument');
    $arg_replacements = array();
    foreach ($argument_handlers as $arg => $handler) {
      $count += 1;
      $t_args = array('@count' => $count);
      if (isset($arg_replacements["%$count"])) {
        $arg_replacements["%count"] = $ui ? t('Title of argument @count', $t_args) : '';
      }
      // Use strip tags as there should never be HTML in the path. However, we need to preserve special characters like " that were removed by check_plain().
      $arg_replacements["!$count"] = $ui ?
        t('Value of argument @count', $t_args) :
        (isset($view->args[$count - 1]) ? strip_tags(decode_entities($view->args[$count - 1])) : '');
    }
    // Reverse so !10 is before !1
    $replacements += $arg_replacements;

    // Go through each filter and add options.
    foreach ($evi->getViewsEviFilterWrappers() as $filter_wrapper) {
      $identifier = $filter_wrapper->getIdentifier();
      $replacements["[form:$identifier]"] = $ui ?
        // Label is already sanitized.
        t('Exposed form value for !label', array('!label' => $filter_wrapper->GetEviLabel())) :
        @$_GET[$identifier];
    }

    $context = array(
      'view' => $view,
      'ui' => $ui,
    );
    drupal_alter('views_evi_tokens', $replacements, $context);

    $evi->setViewsEviCache('ViewsEviValueToken', "replacements-$ui", $replacements);

    return $replacements;
  }

}