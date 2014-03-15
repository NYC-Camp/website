<?php
/**
 * @file
 * featured_attendees.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function featured_attendees_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "flexslider" && $api == "flexslider_default_preset") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function featured_attendees_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
