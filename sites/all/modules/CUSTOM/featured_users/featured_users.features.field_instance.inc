<?php
/**
 * @file
 * featured_users.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function featured_users_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'queues-featured_users-field_qt_featured_users'
  $field_instances['queues-featured_users-field_qt_featured_users'] = array(
    'bundle' => 'featured_users',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'queues',
    'field_name' => 'field_qt_featured_users',
    'label' => 'Queue items',
    'required' => 0,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 0,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Queue items');

  return $field_instances;
}
