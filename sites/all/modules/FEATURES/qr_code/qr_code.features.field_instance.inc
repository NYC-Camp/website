<?php
/**
 * @file
 * qr_code.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function qr_code_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'user-user-field_mobile_code'
  $field_instances['user-user-field_mobile_code'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => '[current-user:field-profile-first] [current-user:field-profile-last]
[current-user:field_profile_org]',
      ),
    ),
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'attendee' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 24,
      ),
      'grid' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'listing' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'organizer' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_mobile_code',
    'label' => 'Mobile Code',
    'required' => 0,
    'settings' => array(
      'barcode_height' => 200,
      'barcode_image_format' => 'jpg',
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'barcode',
      'settings' => array(),
      'type' => 'barcode_textarea',
      'weight' => 9,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Mobile Code');

  return $field_instances;
}
