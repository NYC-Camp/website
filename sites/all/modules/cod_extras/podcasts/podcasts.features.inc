<?php
/**
 * @file
 * podcasts.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function podcasts_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
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
function podcasts_node_info() {
  $items = array(
    'podcast' => array(
      'name' => t('Podcast'),
      'base' => 'node_content',
      'description' => t('A content type for podcasts'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
