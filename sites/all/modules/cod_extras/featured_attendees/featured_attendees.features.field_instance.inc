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

  // Exported field_instance: 'user-user-field_my_drupal_org_profile'
  $field_instances['user-user-field_my_drupal_org_profile'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Please enter the link to your user profile on Drupal.org. ',
    'display' => array(
      'attendee' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 15,
      ),
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 22,
      ),
      'grid' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 28,
      ),
      'listing' => array(
        'label' => 'hidden',
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_default',
        'weight' => 3,
      ),
      'organizer' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_my_drupal_org_profile',
    'label' => 'My Drupal.org profile',
    'required' => 0,
    'settings' => array(
      'attributes' => array(
        'class' => '',
        'configurable_title' => 0,
        'rel' => '',
        'target' => '_blank',
        'title' => '',
      ),
      'display' => array(
        'url_cutoff' => 80,
      ),
      'enable_tokens' => 1,
      'rel_remove' => 'default',
      'title' => 'none',
      'title_maxlength' => 128,
      'title_value' => '',
      'url' => 0,
      'user_register_form' => 1,
      'validate_url' => 1,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'link',
      'settings' => array(),
      'type' => 'link_field',
      'weight' => 46,
    ),
  );

  // Exported field_instance: 'user-user-field_profile_irc'
  $field_instances['user-user-field_profile_irc'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Please enter your IRC',
    'display' => array(
      'attendee' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 13,
      ),
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 17,
      ),
      'grid' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 23,
      ),
      'listing' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 21,
      ),
      'organizer' => array(
        'label' => 'hidden',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 17,
      ),
    ),
    'entity_type' => 'user',
    'field_name' => 'field_profile_irc',
    'label' => 'IRC',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 47,
    ),
  );

  // Exported field_instance: 'user-user-field_user_featured_attendee'
  $field_instances['user-user-field_user_featured_attendee'] = array(
    'bundle' => 'user',
    'default_value' => array(
      0 => array(
        'value' => 0,
      ),
    ),
    'deleted' => 0,
    'description' => 'Please indicate if this User is a Featured Attendee',
    'display' => array(
      'attendee' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 0,
      ),
      'default' => array(
        'label' => 'above',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
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
    'field_name' => 'field_user_featured_attendee',
    'label' => 'Featured Attendee',
    'required' => 0,
    'settings' => array(
      'user_register_form' => 0,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'display_label' => 1,
      ),
      'type' => 'options_onoff',
      'weight' => 52,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Featured Attendee');
  t('Featured Attendee Blurb');
  t('IRC');
  t('If this is a featured attendee, enter any additional information about them.');
  t('My Drupal.org profile');
  t('Please enter the link to your user profile on Drupal.org. ');
  t('Please enter your IRC');
  t('Please indicate if this User is a Featured Attendee');

  return $field_instances;
}
