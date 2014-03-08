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
        'value' => '[mobilecode #preset="small"][current-user:field-profile-first][/mobilecode]',
        'format' => 'mobile_codes_formatting',
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
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 24,
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
      'text_processing' => 1,
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 9,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Mobile Code');

  return $field_instances;
}
