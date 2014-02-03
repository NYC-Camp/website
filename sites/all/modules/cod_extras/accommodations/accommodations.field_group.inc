<?php
/**
 * @file
 * accommodations.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function accommodations_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_accommodation_genera|node|accomodation|form';
  $field_group->group_name = 'group_accommodation_genera';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'accomodation';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'General',
    'weight' => '0',
    'children' => array(
      0 => 'field_accomodation_description',
      1 => 'field_accomodation_image',
      2 => 'field_accomodation_website',
      3 => 'field_acommodation_teaser',
      4 => 'field_accommodation_location',
      5 => 'title',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-accommodation-genera field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_accommodation_genera|node|accomodation|form'] = $field_group;

  return $export;
}
