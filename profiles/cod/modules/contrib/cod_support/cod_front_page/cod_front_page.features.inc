<?php
/**
 * @file
 * cod_front_page.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cod_front_page_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}
