<?php
/*
 * Prefix your custom functions with porto_sub. For example:
 * porto_sub_form_alter(&$form, &$form_state, $form_id) { ... }
 */





function porto_sub_node_preview($variables) { 
    $node = $variables['node'];
    
    drupal_set_title('');

    $wrapper = entity_metadata_wrapper('node', $node);
  
    $output = '<div class="mypreview row"><div class="col-sm-6 col-sm-offset-3">';
    
    $output .= '<div><h2 class="text-center">Confirm & Pay Online Now</h2></div>';
    
    if (in_array($node->type, ['nitp_form', 'outbound']) ){
        $arrival_location_id = $wrapper->field_arrival_location->value()->tid;
        $currency_id = $wrapper->field_preferred_currency->value();
        
        $arrival_location = get_taxonomy($arrival_location_id);
        $day2 = $arrival_location->field_day_2_amount->value();
        $day7 = $arrival_location->field_day_7_amount->value();
        
        $symbol = get_nitp_currency_symbol($currency_id);
        $stamp_fee = get_nitp_stamp_fee($currency_id);
    }

    if ($node->type == 'nitp_form') {
        $hotel_id = $wrapper->field_hotel_isolation_center->value()->tid;
        $country_id = $wrapper->field_country_of_first_departur2->value()->tid;
        $bits = explode(",", variable_get('nitp_bit_countries'));
        $lagos = 14034;
        $in_bit = in_array($country_id, $bits);
        
        if ($hotel_id) {
            $hotel = get_taxonomy($hotel_id);
            $hotel_fee = $hotel->field_amount->value() * 14;
        }else {
            $hotel = 0;
        }
        
        if ($in_bit){
            $amount =  $hotel_fee + $day2 + $day7;
        } else {
            if($arrival_location_id == $lagos){
                $amount = $day2;
            }else{
                $amount = $wrapper->field_state_in_nigeria->value()->field_amount['und'][0]['value'];
            }
        }
    }
    
    if ($node->type == 'outbound') {
        $amount = $day2;
    }
    
    if (in_array($node->type, ['nitp_form', 'outbound']) ){
        $test_fee = get_nitp_test_fee($amount, $currency_id);
        $processing_fee = get_nitp_processing_fee($test_fee, $currency_id);
        $payment_method = $wrapper->field_mode_of_payment->value();
        if ($payment_method == 1){
            $total = $test_fee;
        }else{
            $total = $test_fee + $processing_fee + $stamp_fee;
        }
        
        
        $output .= '<div class="row"><div class="col-xs-6"><h4><span class="mypreview-label">Name </span></h4></div><div class="col-xs-6"><h4>'. $wrapper->field_name_of_patient->value() . ' ' . $wrapper->field_surname->value() . '</h4></div></div>';
        $output .= '<div class="row"><div class="col-sm-6"><h4><span class="mypreview-label">Phone Number</span> <br>'. $wrapper->field_phone_number->value() . '</h4></div><div class="col-sm-6"><h4><span class="mypreview-label">Email Address</span><br>'. $wrapper->field_email->value() . '</h4></div></div><hr>';
        
        $output .= '<div class="row"><div class="col-xs-6"><h4><span class="mypreview-label">Fee</span></h4></div><div class="col-xs-6"><h4>' . $symbol . number_format($test_fee,2) . '</h4></div></div>';
        
        if ($payment_method == 2){
            $output .= '<div class="row"><div class="col-xs-6"><h4><span class="mypreview-label">Card Processing Fee</span></h4></div><div class="col-xs-6"><h4>' . $symbol . number_format($processing_fee,2) . '</h4></div></div>';
            
            $output .= '<div class="row"><div class="col-xs-6"><h4><span class="mypreview-label">Stamp Duty</span></h4></div><div class="col-xs-6"><h4>' . $symbol . $stamp_fee . '</h4></div></div>';
        }
        
        $output .= '<div class="row"><div class="col-xs-6"><h4><span class="mypreview-label">Total Amount Due</span></h4></div><div class="col-xs-6"><h4>' . $symbol . number_format($total,2) . '</h4></div></div>';
        if ($in_bit) {
            $output .= '<div class="row"><div class="col-sm-12"><i>Note: The "Fee" above includes the cost of the first test, second test and hotel fees.</i></div></div><br><br>';
        }
    }
    
    
    
    $output .= '<div class="text-center"><a href="#edit-submit" class="btn btn-success btn-lg">Proceed to Confirm & Pay </a></div><br><br>';

    $output .= "</div></div>\n";

    return $output;
}