<?php
/**
 * @file
 * featured_attendees.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function featured_attendees_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_drupal_info|user|user|form';
  $field_group->group_name = 'group_drupal_info';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_organizer_contact';
  $field_group->data = array(
    'label' => 'Drupal Info',
    'weight' => '3',
    'children' => array(
      0 => 'field_profile_github',
      1 => 'field_profile_irc',
      2 => 'field_my_drupal_org_profile',
      3 => 'field_skill_level',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Drupal Info',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'profile-fieldgroup',
        'description' => '',
        'show_label' => '1',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_drupal_info|user|user|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_organizer_contact|user|user|form';
  $field_group->group_name = 'group_organizer_contact';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Profile',
    'weight' => '0',
    'children' => array(
      0 => 'group_volunteer_info',
      1 => 'group_profile_info',
      2 => 'group_drupal_info',
      3 => 'group_socai_media',
      4 => 'group_info_tabs',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Profile',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => '',
        'description' => '',
        'show_label' => '1',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_organizer_contact|user|user|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_profile_info|user|user|form';
  $field_group->group_name = 'group_profile_info';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_organizer_contact';
  $field_group->data = array(
    'label' => 'Profile Info',
    'weight' => '2',
    'children' => array(
      0 => 'field_profile_first',
      1 => 'field_profile_last',
      2 => 'field_profile_org',
      3 => 'field_bio',
      4 => 'field_profile_org_skype',
      5 => 'field_org_phone',
      6 => 'field_profile_interests',
      7 => 'field_profile_job_title',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Profile Info',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'profile-fieldgroup',
        'description' => '',
        'show_label' => '1',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_profile_info|user|user|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_profile_other|user|user|form';
  $field_group->group_name = 'group_profile_other';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Other',
    'weight' => '1',
    'children' => array(
      0 => 'field_featured_attendee_',
      1 => 'field_featured_attendee_blurb',
      2 => 'field_user_featured_attendee',
      3 => 'googleanalytics',
      4 => 'timezone',
      5 => 'wysiwyg',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'formatter' => 'open',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'classes' => '',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_profile_other|user|user|form'] = $field_group;

  return $export;
}
