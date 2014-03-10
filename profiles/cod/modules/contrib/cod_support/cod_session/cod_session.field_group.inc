<?php
/**
 * @file
 * cod_session.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function cod_session_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_audience|node|session|default';
  $field_group->group_name = 'group_audience';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'session';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Audience',
    'weight' => '15',
    'children' => array(),
    'format_type' => 'hidden',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'show_label' => 1,
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
        'classes' => ' group-audience field-group-hidden',
      ),
    ),
  );
  $export['group_audience|node|session|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_audience|node|session|form';
  $field_group->group_name = 'group_audience';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'session';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_session_tabs';
  $field_group->data = array(
    'label' => 'Audience',
    'weight' => '49',
    'children' => array(
      0 => 'field_experience',
      1 => 'field_track',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-audience field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_audience|node|session|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gen_info|node|session|form';
  $field_group->group_name = 'group_gen_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'session';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_session_tabs';
  $field_group->data = array(
    'label' => 'General info',
    'weight' => '48',
    'children' => array(
      0 => 'field_running_time',
      1 => 'field_presenters',
      2 => 'field_session_other_info',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-gen-info field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_gen_info|node|session|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_intended_audience|node|session|form';
  $field_group->group_name = 'group_intended_audience';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'session';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_session_tabs';
  $field_group->data = array(
    'label' => 'Audience',
    'weight' => '49',
    'children' => array(
      0 => 'field_experience',
      1 => 'field_session_topics',
      2 => 'field_session_track',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Audience',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-intended-audience field-group-tab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_intended_audience|node|session|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_page_general|node|page|form';
  $field_group->group_name = 'group_page_general';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'General ',
    'weight' => '0',
    'children' => array(
      0 => 'field_page_background',
      1 => 'field_page_body',
      2 => 'field_page_subtitle',
      3 => 'field_page_image',
      4 => 'field_page_files',
      5 => 'field_page_links',
      6 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-page-general field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_page_general|node|page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_schedule_info|node|schedule_item|default';
  $field_group->group_name = 'group_schedule_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'schedule_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Schedule info',
    'weight' => '1',
    'children' => array(
      0 => 'field_accepted',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-schedule-info field-group-fieldset',
      ),
    ),
  );
  $export['group_schedule_info|node|schedule_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_schedule_info|node|session|default';
  $field_group->group_name = 'group_schedule_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'session';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Schedule info',
    'weight' => '14',
    'children' => array(
      0 => 'field_accepted',
      1 => 'field_which_day',
    ),
    'format_type' => 'hidden',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-schedule-info field-group-hidden',
      ),
    ),
  );
  $export['group_schedule_info|node|session|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_schedule_tab|node|page|form';
  $field_group->group_name = 'group_schedule_tab';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Schedule Info',
    'weight' => '2',
    'children' => array(
      0 => 'field_event_type',
      1 => 'field_session_timeslot',
      2 => 'field_organizer_info_',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-schedule-tab field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_schedule_tab|node|page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_schedule|node|schedule_item|form';
  $field_group->group_name = 'group_schedule';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'schedule_item';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Schedule Info',
    'weight' => '1',
    'children' => array(
      0 => 'field_accepted',
      1 => 'field_session_timeslot',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Schedule Info',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => ' group-schedule field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_schedule|node|schedule_item|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_schedule|node|session|form';
  $field_group->group_name = 'group_schedule';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'session';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_session_tabs';
  $field_group->data = array(
    'label' => 'Schedule Info',
    'weight' => '51',
    'children' => array(
      0 => 'field_accepted',
      1 => 'field_session_timeslot',
      2 => 'field_room_assignment',
      3 => 'field_summit_session',
      4 => 'field_session_time',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Schedule Info',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => ' group-schedule field-group-tab',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_schedule|node|session|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_session_admin_fields|node|session|form';
  $field_group->group_name = 'group_session_admin_fields';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'session';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_session_tabs';
  $field_group->data = array(
    'label' => 'Admin',
    'weight' => '52',
    'children' => array(
      0 => 'field_which_day',
      1 => 'path',
      2 => 'redirect',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-session-admin-fields field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_session_admin_fields|node|session|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_session_tabs|node|session|form';
  $field_group->group_name = 'group_session_tabs';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'session';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Session tab group',
    'weight' => '2',
    'children' => array(
      0 => 'group_gen_info',
      1 => 'group_intended_audience',
      2 => 'group_schedule',
      3 => 'group_session_admin_fields',
    ),
    'format_type' => 'tabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => ' group-session-tabs field-group-tabs',
      ),
    ),
  );
  $export['group_session_tabs|node|session|form'] = $field_group;

  return $export;
}
