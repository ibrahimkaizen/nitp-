<?php 

/**
 * Page alter.
 */
function bootstrap_business_page_alter($page) {
	$mobileoptimized = array(
		'#type' => 'html_tag',
		'#tag' => 'meta',
		'#attributes' => array(
		'name' =>  'MobileOptimized',
		'content' =>  'width'
		)
	);
	$handheldfriendly = array(
		'#type' => 'html_tag',
		'#tag' => 'meta',
		'#attributes' => array(
		'name' =>  'HandheldFriendly',
		'content' =>  'true'
		)
	);
	$viewport = array(
		'#type' => 'html_tag',
		'#tag' => 'meta',
		'#attributes' => array(
		'name' =>  'viewport',
		'content' =>  'width=device-width, initial-scale=1'
		)
	);
	drupal_add_html_head($mobileoptimized, 'MobileOptimized');
	drupal_add_html_head($handheldfriendly, 'HandheldFriendly');
	drupal_add_html_head($viewport, 'viewport');
}

/**
 * Preprocess variables for html.tpl.php
 */
function bootstrap_business_preprocess_html(&$variables) {
	/**
	 * Add IE8 Support
	 */
	drupal_add_css(path_to_theme() . '/css/ie8.css', array('group' => CSS_THEME, 'browsers' => array('IE' => '(lt IE 9)', '!IE' => FALSE), 'preprocess' => FALSE));
    
	/**
	* Bootstrap CDN
	*/
    
    if (theme_get_setting('bootstrap_css_cdn', 'bootstrap_business')) {
        $cdn = '//maxcdn.bootstrapcdn.com/bootstrap/' . theme_get_setting('bootstrap_css_cdn', 'bootstrap_business')  . '/css/bootstrap.min.css';
        drupal_add_css($cdn, array('type' => 'external'));
    }
    
    if (theme_get_setting('bootstrap_js_cdn', 'bootstrap_business')) {
        $cdn = '//maxcdn.bootstrapcdn.com/bootstrap/' . theme_get_setting('bootstrap_js_cdn', 'bootstrap_business')  . '/js/bootstrap.min.js';
        drupal_add_js($cdn, array('type' => 'external'));
    }
	
	/**
	* Add Javascript for enable/disable scrollTop action
	*/
	if (theme_get_setting('scrolltop_display', 'bootstrap_business')) {

		drupal_add_js('jQuery(document).ready(function($) { 
		$(window).scroll(function() {
			if($(this).scrollTop() != 0) {
				$("#toTop").fadeIn();	
			} else {
				$("#toTop").fadeOut();
			}
		});
		
		$("#toTop").click(function() {
			$("body,html").animate({scrollTop:0},800);
		});	
		
		});',
		array('type' => 'inline', 'scope' => 'header'));
	}
	//EOF:Javascript
}

/**
 * Override or insert variables into the html template.
 */
function bootstrap_business_process_html(&$vars) {
	// Hook into color.module
	if (module_exists('color')) {
	_color_html_alter($vars);
	}
}

/**
 * Preprocess variables for page template.
 */
function bootstrap_business_preprocess_page(&$vars) {

	/**
	 * insert variables into page template.
	 */
	if($vars['page']['sidebar_first'] && $vars['page']['sidebar_second']) { 
		$vars['sidebar_grid_class'] = 'col-md-3';
		$vars['main_grid_class'] = 'col-md-6';
	} elseif ($vars['page']['sidebar_first'] || $vars['page']['sidebar_second']) {
		$vars['sidebar_grid_class'] = 'col-md-4';
		$vars['main_grid_class'] = 'col-md-8';		
	} else {
		$vars['main_grid_class'] = 'col-md-12';			
	}

	if($vars['page']['header_top_left'] && $vars['page']['header_top_right']) { 
		$vars['header_top_left_grid_class'] = 'col-md-8';
		$vars['header_top_right_grid_class'] = 'col-md-4';
	} elseif ($vars['page']['header_top_right'] || $vars['page']['header_top_left']) {
		$vars['header_top_left_grid_class'] = 'col-md-12';
		$vars['header_top_right_grid_class'] = 'col-md-12';		
	}

	/**
	 * Add Javascript
	 */
	if($vars['page']['pre_header_first'] || $vars['page']['pre_header_second'] || $vars['page']['pre_header_third']) { 
	drupal_add_js('
	function hidePreHeader(){
	jQuery(".toggle-control").html("<a href=\"javascript:showPreHeader()\"><span class=\"glyphicon glyphicon-plus\"></span></a>");
	jQuery("#pre-header-inside").slideUp("fast");
	}

	function showPreHeader() {
	jQuery(".toggle-control").html("<a href=\"javascript:hidePreHeader()\"><span class=\"glyphicon glyphicon-minus\"></span></a>");
	jQuery("#pre-header-inside").slideDown("fast");
	}
	',
	array('type' => 'inline', 'scope' => 'footer', 'weight' => 3));
	}
	//EOF:Javascript
}

/**
 * Override or insert variables into the page template.
 */
function bootstrap_business_process_page(&$variables) {
  // Hook into color.module.
  if (module_exists('color')) {
    _color_page_alter($variables);
  }
}

/**
 * Preprocess variables for block.tpl.php
 */
function bootstrap_business_preprocess_block(&$variables) {
	$variables['classes_array'][]='clearfix';
}

/**
 * Override theme_breadrumb().
 *
 * Print breadcrumbs as a list, with separators.
 */
function bootstrap_business_breadcrumb($variables) {
	$breadcrumb = $variables['breadcrumb'];

	if (!empty($breadcrumb)) {
		$breadcrumb[] = drupal_get_title();
		$breadcrumbs = '<ol class="breadcrumb">';

		$count = count($breadcrumb) - 1;
		foreach ($breadcrumb as $key => $value) {
		$breadcrumbs .= '<li>' . $value . '</li>';
		}
		$breadcrumbs .= '</ol>';

		return $breadcrumbs;
	}
}

/**
 * Search block form alter.
 */
function bootstrap_business_form_alter(&$form, &$form_state, $form_id) {
	if ($form_id == 'search_block_form') {
	    unset($form['search_block_form']['#title']);
	    $form['search_block_form']['#title_display'] = 'invisible';
		$form_default = t('Search this website...');
	    $form['search_block_form']['#default_value'] = $form_default;

		$form['actions']['submit']['#attributes']['value'][] = '';

	 	$form['search_block_form']['#attributes'] = array('onblur' => "if (this.value == '') {this.value = '{$form_default}';}", 'onfocus' => "if (this.value == '{$form_default}') {this.value = '';}" );
	}
}


function bootstrap_business_node_preview($variables) { 
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
        $in_bit = in_array($country_id, [8905, 8974, 9092] );
        
        if ($hotel_id) {
            $hotel = get_taxonomy($hotel_id);
            $hotel_fee = $hotel->field_amount->value() * 14;
        }else {
            $hotel = 0;
        }
        
        if ($in_bit){
            $amount =  $hotel_fee + $day2 + $day7;
        } else {
            $amount = $day2;
        }
    }
    
    if ($node->type == 'outbound') {
        $amount = $day2;
    }
    
    if (in_array($node->type, ['nitp_form', 'outbound']) ){
        $test_fee = get_nitp_test_fee($amount, $currency_id);
        $processing_fee = get_nitp_processing_fee($test_fee, $currency_id);
        $total = $test_fee + $processing_fee + $stamp_fee;
        
        $output .= '<div class="row"><div class="col-xs-6"><h4><span class="mypreview-label">Name </span></h4></div><div class="col-xs-6"><h4>'. $wrapper->field_name_of_patient->value() . ' ' . $wrapper->field_surname->value() . '</h4></div></div>';
        $output .= '<div class="row"><div class="col-sm-6"><h4><span class="mypreview-label">Phone Number</span> <br>'. $wrapper->field_phone_number->value() . '</h4></div><div class="col-sm-6"><h4><span class="mypreview-label">Email Address</span><br>'. $wrapper->field_email->value() . '</h4></div></div><hr>';
        
        $output .= '<div class="row"><div class="col-xs-6"><h4><span class="mypreview-label">Fee</span></h4></div><div class="col-xs-6"><h4>' . $symbol . number_format($test_fee,2) . '</h4></div></div>';
        
        $output .= '<div class="row"><div class="col-xs-6"><h4><span class="mypreview-label">Card Processing Fee</span></h4></div><div class="col-xs-6"><h4>' . $symbol . number_format($processing_fee,2) . '</h4></div></div>';
        
        $output .= '<div class="row"><div class="col-xs-6"><h4><span class="mypreview-label">Stamp Duty</span></h4></div><div class="col-xs-6"><h4>' . $symbol . $stamp_fee . '</h4></div></div>';
        $output .= '<div class="row"><div class="col-xs-6"><h4><span class="mypreview-label">Total Amount Due</span></h4></div><div class="col-xs-6"><h4>' . $symbol . number_format($total,2) . '</h4></div></div>';
        if ($in_bit) {
            $output .= '<div class="row"><div class="col-sm-12"><i>Note: The "Fee" above includes the cost of the first test, second test and hotel fees.</i></div></div><br><br>';
        }
    }
    
    
    
    $output .= '<div class="text-center"><a href="#edit-submit" class="btn btn-success btn-lg">Proceed to Confirm & Pay </a></div><br><br>';

    $output .= "</div></div>\n";

    return $output;
}