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
