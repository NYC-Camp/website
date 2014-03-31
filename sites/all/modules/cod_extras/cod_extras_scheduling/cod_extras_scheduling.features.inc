<?php
/**
 * @file
 * cod_extras_scheduling.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cod_extras_scheduling_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cod_extras_scheduling_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function cod_extras_scheduling_node_info() {
  $items = array(
    'schedule_conference_day' => array(
      'name' => t('Schedule Conference Day'),
      'base' => 'node_content',
      'description' => t('A content type for <em>Days<em> of a Conference'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'schedule_slot' => array(
      'name' => t('Schedule Slot'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'schedule_time_slot' => array(
      'name' => t('Schedule Time Slot'),
      'base' => 'node_content',
      'description' => t('A <em>Time Slot<em> to be used for scheduling Events, Sessions and Schedule Items for the Event'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
