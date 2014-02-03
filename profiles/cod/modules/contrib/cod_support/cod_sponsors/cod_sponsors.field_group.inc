<?php
/**
 * @file
 * cod_sponsors.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function cod_sponsors_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_logo_tab|node|sponsor|form';
  $field_group->group_name = 'group_logo_tab';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'sponsor';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_sponsor_fields';
  $field_group->data = array(
    'label' => 'Sponsor Logo',
    'weight' => '3',
    'children' => array(
      0 => 'field_sponsor_logo',
      1 => 'field_sponsor_logo_vector_',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Sponsor Logo',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => ' group-logo-tab field-group-tab',
        'description' => 'Update the logo you would like displayed on the sponsor page and all collateral. 

If you have special graphic needs, please contact sponsorhip@nyccamp.org',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_logo_tab|node|sponsor|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sponsor_admin_info|node|sponsor|form';
  $field_group->group_name = 'group_sponsor_admin_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'sponsor';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Sponsor Admin Info',
    'weight' => '1',
    'children' => array(
      0 => 'field_sponsor_sponsorship_level',
      1 => 'field_sponsorship_level',
      2 => 'field_sponsor_sponsorship',
      3 => 'field_sponsor_sponsorship_event',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-sponsor-admin-info field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_sponsor_admin_info|node|sponsor|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sponsor_fields|node|sponsor|form';
  $field_group->group_name = 'group_sponsor_fields';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'sponsor';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Sponsor Fields',
    'weight' => '0',
    'children' => array(
      0 => 'group_sponsor_general',
      1 => 'group_sponsor_links',
      2 => 'group_logo_tab',
    ),
    'format_type' => 'tabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => ' group-sponsor-fields field-group-tabs',
      ),
    ),
  );
  $export['group_sponsor_fields|node|sponsor|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sponsor_general|node|sponsor|form';
  $field_group->group_name = 'group_sponsor_general';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'sponsor';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_sponsor_fields';
  $field_group->data = array(
    'label' => 'Sponsor Info',
    'weight' => '1',
    'children' => array(
      0 => 'field_sponsor_body',
      1 => 'field_sponsor_related_attendees',
      2 => 'field_association_membership',
      3 => 'field_my_drupal_module_s_',
      4 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Sponsor Info',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => ' group-sponsor-general field-group-tab',
        'description' => 'General information about your company that would like displayed as per benefits assigned to your sponsorship level. ',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_sponsor_general|node|sponsor|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sponsor_links|node|sponsor|form';
  $field_group->group_name = 'group_sponsor_links';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'sponsor';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_sponsor_fields';
  $field_group->data = array(
    'label' => 'Sponsor Links',
    'weight' => '2',
    'children' => array(
      0 => 'field_sponsor_url',
      1 => 'field_sponsor_twitter',
      2 => 'field_sponsor_facebook',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-sponsor-links field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_sponsor_links|node|sponsor|form'] = $field_group;

  return $export;
}
