<?php
/**
 * @file
 * organization.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function organization_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function organization_node_info() {
  $items = array(
    'organization' => array(
      'name' => t('Organization'),
      'base' => 'node_content',
      'description' => t('Organization or Company, capable of purchasing Sponsorships.'),
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  return $items;
}
