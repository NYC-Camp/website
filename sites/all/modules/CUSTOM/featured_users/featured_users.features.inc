<?php
/**
 * @file
 * featured_users.features.inc
 */

/**
 * Implements hook_views_api().
 */
function featured_users_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_default_queues_type().
 */
function featured_users_default_queues_type() {
  $items = array();
  $items['featured_users'] = entity_import('queues_type', '{
    "label" : "Featured Users",
    "type" : "featured_users",
    "target" : "user",
    "settings" : { "entityreference_field" : { "cardinality" : "-1", "target_bundles" : { "user" : "user" } } },
    "rdf_mapping" : []
  }');
  return $items;
}
