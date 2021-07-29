<?php

function nitp_rules_action_info() {
  $actions = [];
  
  $actions['redirect_to_flutter'] = array(
      'label' => t('Redirect to flutterwave'),
      'group' => t('Custom'),
      'base' => 'rules_action_redirect_to_flutter',
      'parameter' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('Node'),
        ),
        'redirect_url' => array(
            'type' => 'text',
            'label' => t('Redirect URL'),
        ),
      ),
  );
  
  $actions['compute_bill'] = array(
      'label' => t('Compute Bill'),
      'group' => t('Custom'),
      'base' => 'rules_action_compute_bill',
      'parameter' => array(
        'amount' => array(
          'type' => 'decimal',
          'label' => t('Amount'),
        ),
        'currency' => array(
            'type' => 'integer',
            'label' => t('Currency Key'),
        ),
      ),
      'provides' => array(
        'variable_added' => array(
          'type' => 'decimal',
          'label' => t('Added variable'),
        ),
      ),
  );

    $actions["nitp_action_get_system_variable"] = array(
      'label' => t("Get system variable"),
      'group' => t('Custom'),
      'parameter' => array(
        'variable' => array(
          'type' => 'text',
          'label' => t('Variable'),
          'description' => t('Type in the variable name. e.g nitp_stamp_duty, nitp_dollar_rate, nitp_gbp_rate, nitp_euro_rate'),
        ),
      ),
      'base' => "nitp_action_get_system_variable",
      'provides' => array(
        'variable_added' => array(
          'type' => 'text',
          'label' => t('Added variable'),
        ),
      ),
    );
  

  return $actions;
}


function rules_action_redirect_to_flutter($node, $redirect_url) {
    $link = get_flutterwave_link($node, $redirect_url);
    
    if ($link) {
        $wrapper = entity_metadata_wrapper('node', $node);
        db_delete('sms_codes')
          ->condition('phone', $wrapper->field_phone_number->value())
          ->condition('code', $wrapper->field_phone_verification_code->value())
          ->execute();
  
        drupal_goto($link);
        
    } else {
        drupal_goto($redirect_url);
    }
    
  
}


function rules_action_compute_bill($amount, $currency){
    $test_fee = get_nitp_test_fee($amount, $currency);
    
    if ($currency == 1) {
        $processing = variable_get('nitp_naira_card_processing') * $test_fee;
        $stamp = variable_get('nitp_stamp_duty');
    }else {
        $processing = variable_get('nitp_other_card_processing') * $test_fee;
        $stamp = variable_get('nitp_stamp_duty_others');
        
    }
    
    $total = $test_fee + $processing + $stamp;
    
    return array('variable_added' => $total);

}

/**
 * Fetch variable of type text.
 */
function nitp_action_get_system_variable($variable) {
  return array('variable_added' => variable_get($variable));
}
