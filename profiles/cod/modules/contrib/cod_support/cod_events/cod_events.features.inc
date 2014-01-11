<?php
/**
 * @file
 * cod_events.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cod_events_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  if ($module == "panels" && $api == "layouts") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cod_events_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function cod_events_flag_default_flags() {
  $flags = array();
  // Exported flag: "Default Event".
  $flags['default_event'] = array(
    'content_type' => 'node',
    'title' => 'Default Event',
    'global' => 1,
    'types' => array(
      0 => 'event',
    ),
    'flag_short' => 'Set as default event',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Remove default event',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'normal',
    'roles' => array(
      'flag' => array(
        0 => 2,
      ),
      'unflag' => array(
        0 => 2,
      ),
    ),
    'weight' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_on_page' => 1,
    'show_on_teaser' => 1,
    'show_contextual_link' => 0,
    'i18n' => 0,
    'module' => 'cod_events',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 2,
  );
  return $flags;

}

/**
 * Implements hook_node_info().
 */
function cod_events_node_info() {
  $items = array(
    'event' => array(
      'name' => t('Event'),
      'base' => 'node_content',
      'description' => t('Provides free and paid event registration on the Event content type.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implements hook_default_registration_type().
 */
function cod_events_default_registration_type() {
  $items = array();
  $items['free_event'] = entity_import('registration_type', '{
    "name" : "free_event",
    "label" : "Free Event",
    "locked" : "0",
    "weight" : "0",
    "data" : null
  }');
  return $items;
}
