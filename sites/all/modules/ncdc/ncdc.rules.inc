<?php

function ncdc_rules_action_info() {
  $items = array(
    'send_request_to_ncdc' => array(
      'label' => t('Send Request to NCDC'),
      'group' => t('Custom'),
      'base' => 'rules_action_send_request_to_ncdc',
      'parameter' => array(
        'body' => array(
          'type' => 'text',
          'label' => t('Body'),
        ),
        'sampledate' => array(
          'type' => 'text',
          'label' => t('Sample Date'),
        ),
      ),

      'provides' => array(
        'response_is_success' => array(
          'type' => 'text',
          'label' => t('Is Success'),
        ),
        'response_feedback' => array(
          'type' => 'text',
          'label' => t('Feedback'),
        ),
        'response_text_id' => array(
          'type' => 'text',
          'label' => t('Test ID'),
        ),
        'response_qrcode' => array(
          'type' => 'text',
          'label' => t('QR Code'),
        ),
      )
    ),
  );

  return $items;
}


function rules_action_send_request_to_ncdc($body, $sampledate) {
  $lines = explode(",", $body);
  $array = array();
  

  $date = substr($sampledate, 0, -8);
  $date = substr($date, 5);
  $date = str_replace('/', '-', $date);

  $sampledate_timestamp = strtotime($date);
  $new_date = date('Y-m-d', $sampledate_timestamp);

  foreach ($lines as $value) {
    $new = explode("=", trim($value));
    if ($new[1]) {
      $array[trim($new[0])] = trim($new[1]);
    } 
  }
  $array['sampling_date']=$new_date;
  
  $url = "https://rv.ncdc.gov.ng/Verify/PushResult";

  $request = drupal_http_request(
    $url,
    array(
      'method' => 'POST',
      'data' => json_encode($array),
      'headers' => array(
        'Content-Type' => 'application/json',
      ),
    )
  );

  if ($request && $request->code == 200) {

    $response = json_decode($request->data, true);

    return array(
      'response_is_success' => $response['test_id'],
      'response_text_id' =>  $response['test_id'],
      'response_qrcode' =>  $response['qr_code'],
      'response_feedback' =>  $response['feedback'],
    );
  }

  
}