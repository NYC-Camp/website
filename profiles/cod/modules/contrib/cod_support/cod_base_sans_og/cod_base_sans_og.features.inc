<?php
/**
 * @file
 * cod_base_sans_og.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cod_base_sans_og_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
