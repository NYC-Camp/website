<?php
/**
 * @file
 * qr_code.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function qr_code_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_mobile_code'
  $field_bases['field_mobile_code'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_mobile_code',
    'field_permissions' => array(
      'type' => 0,
    ),
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'barcode',
    'settings' => array(
      'dbsize' => 512,
      'encoding' => 'QRCODE',
    ),
    'translatable' => 0,
    'type' => 'barcode_field',
  );

  return $field_bases;
}
