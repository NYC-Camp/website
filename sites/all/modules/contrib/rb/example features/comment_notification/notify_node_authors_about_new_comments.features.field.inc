<?php
/**
 * @file
 * notify_node_authors_about_new_comments.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function notify_node_authors_about_new_comments_field_default_fields() {
  $fields = array();

  // Exported field: 'user-user-field_user_comment_notify'
  $fields['user-user-field_user_comment_notify'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_user_comment_notify',
      'foreign keys' => array(),
      'indexes' => array(
        'value' => array(
          0 => 'value',
        ),
      ),
      'module' => 'list',
      'settings' => array(
        'allowed_values' => array(
          0 => 'Don\'t notify me',
          1 => 'Notify me when someone comments on my posts',
        ),
        'allowed_values_function' => '',
      ),
      'translatable' => '0',
      'type' => 'list_boolean',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => array(
        0 => array(
          'value' => 0,
        ),
      ),
      'deleted' => '0',
      'description' => 'Checking this option will give you e-mail notifications whenever someone posts comments to your content. (You won\'t get notifications for your own comments.)',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '1',
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_user_comment_notify',
      'label' => 'Comment notification',
      'required' => 0,
      'settings' => array(
        'user_register_form' => 0,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'options',
        'settings' => array(
          'display_label' => 0,
        ),
        'type' => 'options_onoff',
        'weight' => '1',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Checking this option will give you e-mail notifications whenever someone posts comments to your content. (You won\'t get notifications for your own comments.)');
  t('Comment notification');

  return $fields;
}
