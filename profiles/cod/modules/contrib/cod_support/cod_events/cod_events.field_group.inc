<?php
/**
 * @file
 * cod_events.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function cod_events_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_event_type|node|event|form';
  $field_group->group_name = 'group_event_type';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'event';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_info_tabs';
  $field_group->data = array(
    'label' => 'General ',
    'weight' => '4',
    'children' => array(
      0 => 'body',
      1 => 'field_event_image',
      2 => 'group_group',
      3 => 'field_event_type',
      4 => 'field_session_topics',
      5 => 'field_speakers',
      6 => 'field_event_subtitle',
      7 => 'field_topic',
      8 => 'group_register',
      9 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-event-type field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_event_type|node|event|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_info_tabs|node|event|form';
  $field_group->group_name = 'group_info_tabs';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'tab group',
    'weight' => '0',
    'children' => array(
      0 => 'group_event_type',
      1 => 'group_schedule_info',
    ),
    'format_type' => 'tabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => ' group-info-tabs field-group-tabs',
      ),
    ),
  );
  $export['group_info_tabs|node|event|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_schedule_info|node|event|form';
  $field_group->group_name = 'group_schedule_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'event';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_info_tabs';
  $field_group->data = array(
    'label' => 'Schedule Info',
    'weight' => '5',
    'children' => array(
      0 => 'field_dates',
      1 => 'field_registration',
      2 => 'field_which_day',
      3 => 'field_session_timeslot',
      4 => 'field_room_assignment',
      5 => 'field_accepted',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-schedule-info field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_schedule_info|node|event|form'] = $field_group;

  return $export;
}
