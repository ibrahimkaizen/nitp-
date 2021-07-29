<?php
/**
 * @file: md_slider.features.inc
 * @author: MegaDrupal
 */

/**
 * implements hook_features_export_option()
 */
function md_slider_features_export_options() {
  $options = array();
  foreach(MDSlider::get_all() as $slider){
    $options[$slider->machine_name] = $slider->title;
  }

  return $options;
}

/**
 * implements hook_features_export()
 */
function md_slider_features_export($data, &$export, $module_name) {
  $export["dependencies"]["media"] = "media";
  $export["dependencies"]["md_slider"] = "md_slider";

  foreach ($data as $slider) {
    $export["features"]["md_slider"][$slider] = $slider;
  }
}

/**
 * implements hook_features_export_render()
 */
function md_slider_features_export_render($module_name, $data, $export = NULL) {
  $code = array();

  $sliders = db_select("md_sliders", "mds")
    ->fields("mds")
    ->condition("machine_name", array_keys($data), "IN")
    ->execute()
    ->fetchAllAssoc("slid");
  
  // get all slides of each slider
  
  foreach($sliders as &$item){
    $item->slides = MDSlide::get_by_slider_id($item->slid);
  }
  
  $sliders_export = features_var_export($sliders);

  $code[] = "\$sliders = {$sliders_export};";
  $code[] = "foreach (\$sliders as \$slider) {
  \$slides = \$slider['slides'];
  unset(\$slider['slides']);
  ";
  $code[] = "\t\$slider = (object)\$slider;";
  $code[] = "\t\$slider = _md_slider_recast('MDSlider',\$slider);";
  $code[] = "\t\$slider->slid = NULL;\n";
  $code[] = "\tif (!MDSlider::get_by_machine_name(\$slider->machine_name))";
  $code[] = "\t\t\$slider->save();
    if(\$slider->slid){
      foreach(\$slides as \$slide){
        \$slide = (object) \$slide;
        \$slide = _md_slider_recast('MDSlide',\$slide);
        \$slide->sid = NULL;
        \$slide->slid = \$slider->slid;
        \$slide->save();
      }
    }";
  $code[] = "}";
  return array("install" => implode("\n", $code));
}