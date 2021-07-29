<?php


function nitp_vars($form, &$form_state){
    $form['nitp_base_url'] = array(
         '#title' => 'Site Base URL',
        '#type' => 'textfield',
        '#default_value' => variable_get('nitp_base_url', 'https://projectdemo.com.ng/nitp/'),
        '#required' => TRUE,
        '#description' => 'Defaults to https://projectdemo.com.ng/nitp/',
    );
    $form['nitp_flutterwave_secret'] = array(
         '#title' => 'Flutterwave Secret key',
        '#type' => 'textfield',
        '#default_value' => variable_get('nitp_flutterwave_secret', 'FLWSECK_TEST-d260064bdfe5e85e06e62e8d87ad9cef-X'),
        '#required' => TRUE,
        '#description' => 'nitp_flutterwave_secret',
        '#attributes' => array('type'=>'password'),
    );
    $form['nitp_flutterwave_public'] = array(
         '#title' => 'Flutterwave Public key',
        '#type' => 'textfield',
        '#default_value' => variable_get('nitp_flutterwave_public', 'FLWPUBK_TEST-2004b47852414c176fecf07e6e33f663-X'),
        '#required' => TRUE,
        '#description' => 'nitp_flutterwave_public',
    );
    $form['nitp_dollar_rate'] = array(
         '#title' => 'Dollar Rate',
        '#type' => 'textfield',
        '#default_value' => variable_get('nitp_dollar_rate', '350'),
        '#required' => TRUE,
        '#description' => 'nitp_dollar_rate',
    );
    $form['nitp_gbp_rate'] = array(
         '#title' => 'GBP Rate',
        '#type' => 'textfield',
        '#default_value' => variable_get('nitp_gbp_rate', '350'),
        '#required' => TRUE,
        '#description' => 'nitp_gbp_rate',
    );
    $form['nitp_euro_rate'] = array(
         '#title' => 'Euro Rate',
        '#type' => 'textfield',
        '#default_value' => variable_get('nitp_euro_rate', '350'),
        '#required' => TRUE,
        '#description' => 'nitp_euro_rate',
    );
     
    $form['nitp_stamp_duty'] = array(
         '#title' => 'Stamp Duty NGN',
        '#type' => 'textfield',
        '#default_value' => variable_get('nitp_stamp_duty', '50'),
        '#required' => TRUE,
        '#description' => 'nitp_stamp_duty',
    );
    
    $form['nitp_stamp_duty_others'] = array(
         '#title' => 'Stamp Duty Others',
        '#type' => 'textfield',
        '#default_value' => variable_get('nitp_stamp_duty_others', '1'),
        '#required' => TRUE,
        '#description' => 'nitp_stamp_duty_others',
    );
    $form['nitp_naira_card_processing'] = array(
         '#title' => 'Naira Card Processing',
        '#type' => 'textfield',
        '#default_value' => variable_get('nitp_naira_card_processing', '1.5'),
        '#required' => TRUE,
        '#description' => 'nitp_naira_card_processing',
    );
    
    $form['nitp_other_card_processing'] = array(
         '#title' => 'Other Card processing',
        '#type' => 'textfield',
        '#default_value' => variable_get('nitp_other_card_processing', '4'),
        '#required' => TRUE,
        '#description' => 'nitp_other_card_processing',
    );
    
    $form['nitp_bit_countries'] = array(
         '#title' => 'BIT Countries TID',
        '#type' => 'textfield',
        '#default_value' => variable_get('nitp_bit_countries', ''),
        '#required' => TRUE,
        '#description' => 'nitp_bit_countries',
    );
      
    return system_settings_form($form);
}


function make_payment_page($nid) {
    $wrapper = entity_metadata_wrapper('node', $nid);
    $type = $wrapper->getBundle();
    
    $status = $wrapper->field_payment_status->value();
    
    if ($status == 1) {
        drupal_set_message('You have successfully made payment for this registration. Thank you');
        return '';
    }
   
    $currency_id = $wrapper->field_preferred_currency->value();

    $arrival_location_id = $wrapper->field_arrival_location->value()->tid;
    $arrival_location = get_taxonomy($arrival_location_id);
    $day2 = $arrival_location->field_day_2_amount->value();
    $symbol = get_nitp_currency_symbol($currency_id);
    
    if ($type == 'nitp_form') {
        $day7 = $arrival_location->field_day_7_amount->value();
 
        $country_id = $wrapper->field_country_of_first_departur2->value()->tid;
        $bits = explode(",", variable_get('nitp_bit_countries'));
        $lagos = 14034;
        $in_bit = in_array($country_id, $bits);
        
        $hotel_id = $wrapper->field_hotel_isolation_center->value()->tid;
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
    
    if ($type == 'outbound') {
        $amount = $day2;
    }
    
    $test_fee = get_nitp_test_fee($amount, $currency_id);
    $processing_fee = get_nitp_processing_fee($test_fee, $currency_id);
    $stamp_fee = get_nitp_stamp_fee($currency_id);
    $total = $test_fee + $processing_fee + $stamp_fee;
    

    $output = '<div class="mypreview row"><div class="col-sm-6 col-sm-offset-3">';
    
    $output .= '<div><h2 class="text-center">Confirm & Pay Online Now</h2></div>';

    $output .= '<div class="row"><div class="col-xs-6"><h4><span class="mypreview-label">Name </span></h4></div><div class="col-xs-6"><h4>'. $wrapper->field_name_of_patient->value() . ' ' . $wrapper->field_surname->value() . '</h4></div></div>';
    $output .= '<div class="row"><div class="col-sm-6"><h4><span class="mypreview-label">Phone Number</span> <br>'. $wrapper->field_phone_number->value() . '</h4></div><div class="col-sm-6"><h4><span class="mypreview-label">Email Address</span><br>'. $wrapper->field_email->value() . '</h4></div></div><hr>';
    
    $output .= '<div class="row"><div class="col-xs-6"><h4><span class="mypreview-label">Fee</span></h4></div><div class="col-xs-6"><h4>' . $symbol . number_format($test_fee,2) . '</h4></div></div>';
    
    $output .= '<div class="row"><div class="col-xs-6"><h4><span class="mypreview-label">Card Processing Fee</span></h4></div><div class="col-xs-6"><h4>' . $symbol . number_format($processing_fee,2) . '</h4></div></div>';
    
    $output .= '<div class="row"><div class="col-xs-6"><h4><span class="mypreview-label">Stamp Duty</span></h4></div><div class="col-xs-6"><h4>' . $symbol . $stamp_fee . '</h4></div></div>';
    $output .= '<div class="row"><div class="col-xs-6"><h4><span class="mypreview-label">Total Amount Due</span></h4></div><div class="col-xs-6"><h4>' . $symbol . number_format($total,2) . '</h4></div></div>';
    
    if ($in_bit) {
        $output .= '<div class="row"><div class="col-sm-12"><i>Note: The "Fee" above includes the cost of the first test, second test and hotel fees.</i></div></div><br><br>';
    }
    
    $redirect_link = BASE_URL . 'cvdform/complete/'. $nid;
    $retry_link = get_flutterwave_link(node_load($nid), $redirect_link);
    
    $output .= '<div class="text-center"><a href="' . $retry_link . '" class="btn btn-success btn-lg">Proceed to Confirm & Pay </a></div><br><br>';

    $output .= "</div></div>\n";

    return $output;
}


function paymentcomfirmed_pdfcontent($nid) {
    $node = entity_metadata_wrapper('node', $nid);
    
    $fullname = $node->field_surname->value() . ' ' . $node->field_name_of_patient->value();
    $phone = $node->field_phone_number->value();
    $sex = $node->field_gender2->label();
    $nationality = $node->field_nationality2->value()->name;
    $dob = $node->field_date_of_birth->value();
    $country = $node->field_country_of_residence2->value()->name;
    $flight_no = $node->field_flight_no->value();
    $post_date = $node->created->value();
    $qr_code = variable_get('nitp_base_url') . 'qrviewer/' . $nid;
    $departure_airport = $node->field_terminal2->value()->name;
    $departure_country = $node->field_country_of_first_departur2->value()->name;
    
    $v = $node->field_countries_visited_in_the_l->value();
    $visited = "";
    foreach($v as $key=>$val) {
        $visited .= $val->name . ", ";
    }
    
    $arrival_location = $node->field_arrival_location->value()->name;
    
    $destination_address = $node->field_destinations_in_nigeria[0]->field_enter_address->value();
    $destination_phone = $node->field_destinations_in_nigeria[0]->field_phone_dest->value();
    $destination_state = $node->field_destinations_in_nigeria[0]->field_state_in_nigeria->value()->name;
    $destination_city = $node->field_destinations_in_nigeria[0]->field_city->value();
    $destination_duration = $node->field_destinations_in_nigeria[0]->field_duration->value();
    
    $symptoms = "";
    
    if($node->field_fever->value() == 1){
        $symptoms .= "Fever, ";
    }
    if($node->field_cough->value() == 1){
        $symptoms .= "Cough, ";
    }
    if($node->field_difficulty_breathing_dyspn->value() == 1){
        $symptoms .= "Difficulty breathing, ";
    }
    if($node->field_fatigue_general_weakness->value() == 1){
        $symptoms .= "Fatigue & General Weakness, ";
    }
    if($node->field_runny_nose->value() == 1){
        $symptoms .= "Running nose, ";
    }
    if($node->field_other_symptoms_of_flu_or_c->value() == 1){
        $symptoms .= "Other symptoms of flu, ";
    }

    $sick_contact = "";
    
    if($node->field_headache->value() == 1){
        $sick_contact .= "Headache, ";
    }
    if($node->field_chest_pain->value() == 1){
        $sick_contact .= "Chest Pain, ";
    }
    if($node->field_nausea->value() == 1){
        $sick_contact .= "Nausea, ";
    }
    if($node->field_joint_pain_or_arthritis->value() == 1){
        $sick_contact .= "Joint pain or arthritis, ";
    }
    if($node->field_diarrhea->value() == 1){
        $sick_contact .= "Diarrhea, ";
    }
    if($node->field_abdominal_pain->value() == 1){
        $sick_contact .= "Abdominal pain, ";
    }
    if($node->field_confused_or_disoriented->value() == 1){
        $sick_contact .= "Confused or disoriented, ";
    }

    
    $medications = "";
    if($node->field_paracetamol_ibup->value() == 1){
        $medications .= "Paracetamol/Ibup, ";
    }
    if($node->field_antibiotics2->value() == 1){
        $medications .= "Antibiotics, ";
    }
    if($node->field_flu_or_com_cold_medicat->value() == 1){
        $medications .= "Flu or common cold medication, ";
    }
    if($node->field_antiviral_drugs2->value() == 1){
        $medications .= "Antiviral Drugs, ";
    }
    
    
    
    $emergency_name = $node->field_full_name->value();
    $emergency_address = $node->field_e_address->value();
    $emergency_phone = $node->field_e_phone_no->value();
    
    return drupal_json_output([
        "fullname" => $fullname,
        "phone" => $phone,
        "sex" => $sex,
        "nationality" => $nationality,
        "dob" => format_date($dob, 'custom', 'd/m/Y'),
        "country" => $country,
        "flight_no" => $flight_no,
        "post_date" => format_date($post_date, 'custom', 'd/m/Y'),
        "qr_code" => $qr_code,
        "visited" => $visited,
        
        "departure_airport" => $departure_airport,
        "arrival_location" => $arrival_location,
        
        "destination_address" => $destination_address,
        "destination_phone" => $destination_phone,
        "destination_city" => $destination_city . ', ' . $destination_state,
        "destination_duration" => $destination_duration,
        "emergency_name" => $emergency_name,
        "emergency_address" => $emergency_address,
        "emergency_phone" => $emergency_phone,
        
        "symptoms" => $symptoms,
        "sick" => $sick_contact,
        "medications" => $medications,
    ]);
}


function sms_webhook(){
    http_response_code(200);
  
    $request = file_get_contents('php://input');
    watchdog('nitp', $request);
}