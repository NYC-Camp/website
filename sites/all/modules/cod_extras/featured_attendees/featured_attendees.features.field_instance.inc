<?php
/**
 * @file
 * featured_attendees.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function featured_attendees_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'user-user-field_featured_attendee_blurb'
  $field_instances['user-user-field_featured_attendee_blurb'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'If this is a featured attendee, enter any additional information about them.',
    'display' => array(
      'attendee' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 22,
      ),
      'grid' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 9,
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
    'field_name' => 'field_featured_attendee_blurb',
    'label' => 'Featured Attendee Blurb',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'rows' => 5,
      ),
      'type' => 'text_textarea',
      'weight' => 53,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Featured Attendee Blurb');
  t('If this is a featured attendee, enter any additional information about them.');

  return $field_instances;
}
