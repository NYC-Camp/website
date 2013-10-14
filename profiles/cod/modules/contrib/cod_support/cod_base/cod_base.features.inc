<?php
/**
 * @file
 * cod_base.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cod_base_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_date_format_types().
 */
function cod_base_date_format_types() {
  $format_types = array();
  // Exported date format type: date_no_time_
  $format_types['date_no_time_'] = 'Date (no time)';
  return $format_types;
}
