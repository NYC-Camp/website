<?php
/**
 * @file
 * accommodations.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function accommodations_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function accommodations_node_info() {
  $items = array(
    'accomodation' => array(
      'name' => t('Accomodation'),
      'base' => 'node_content',
      'description' => t('A content type for <em>Accomodations<em>'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
