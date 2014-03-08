<?php
/**
 * @file
 * qr_code.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function qr_code_filter_default_formats() {
  $formats = array();

  // Exported format: Mobile Codes Formatting.
  $formats['mobile_codes_formatting'] = array(
    'format' => 'mobile_codes_formatting',
    'name' => 'Mobile Codes Formatting',
    'cache' => 0,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_tokens' => array(
        'weight' => -50,
        'status' => 1,
        'settings' => array(),
      ),
      'mobile_codes' => array(
        'weight' => -49,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
