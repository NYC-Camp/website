<?php
/**
 * @file
 * cod_session.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cod_session_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create field_accepted'.
  $permissions['create field_accepted'] = array(
    'name' => 'create field_accepted',
    'roles' => array(
      'administrator' => 'administrator',
      'session organizer' => 'session organizer',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'create room content'.
  $permissions['create room content'] = array(
    'name' => 'create room content',
    'roles' => array(
      'administrator' => 'administrator',
      'session organizer' => 'session organizer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create schedule_item content'.
  $permissions['create schedule_item content'] = array(
    'name' => 'create schedule_item content',
    'roles' => array(
      'administrator' => 'administrator',
      'session organizer' => 'session organizer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create session content'.
  $permissions['create session content'] = array(
    'name' => 'create session content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create time_slot content'.
  $permissions['create time_slot content'] = array(
    'name' => 'create time_slot content',
    'roles' => array(
      'administrator' => 'administrator',
      'session organizer' => 'session organizer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any room content'.
  $permissions['delete any room content'] = array(
    'name' => 'delete any room content',
    'roles' => array(
      'administrator' => 'administrator',
      'session organizer' => 'session organizer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any schedule_item content'.
  $permissions['delete any schedule_item content'] = array(
    'name' => 'delete any schedule_item content',
    'roles' => array(
      'administrator' => 'administrator',
      'session organizer' => 'session organizer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any session content'.
  $permissions['delete any session content'] = array(
    'name' => 'delete any session content',
    'roles' => array(
      'administrator' => 'administrator',
      'session organizer' => 'session organizer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any time_slot content'.
  $permissions['delete any time_slot content'] = array(
    'name' => 'delete any time_slot content',
    'roles' => array(
      'administrator' => 'administrator',
      'session organizer' => 'session organizer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own session content'.
  $permissions['delete own session content'] = array(
    'name' => 'delete own session content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any room content'.
  $permissions['edit any room content'] = array(
    'name' => 'edit any room content',
    'roles' => array(
      'administrator' => 'administrator',
      'session organizer' => 'session organizer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any schedule_item content'.
  $permissions['edit any schedule_item content'] = array(
    'name' => 'edit any schedule_item content',
    'roles' => array(
      'administrator' => 'administrator',
      'session organizer' => 'session organizer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any session content'.
  $permissions['edit any session content'] = array(
    'name' => 'edit any session content',
    'roles' => array(
      'administrator' => 'administrator',
      'session organizer' => 'session organizer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any time_slot content'.
  $permissions['edit any time_slot content'] = array(
    'name' => 'edit any time_slot content',
    'roles' => array(
      'administrator' => 'administrator',
      'session organizer' => 'session organizer',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit field_accepted'.
  $permissions['edit field_accepted'] = array(
    'name' => 'edit field_accepted',
    'roles' => array(
      'administrator' => 'administrator',
      'session organizer' => 'session organizer',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own field_accepted'.
  $permissions['edit own field_accepted'] = array(
    'name' => 'edit own field_accepted',
    'roles' => array(
      'administrator' => 'administrator',
      'session organizer' => 'session organizer',
    ),
    'module' => 'field_permissions',
  );

  // Exported permission: 'edit own session content'.
  $permissions['edit own session content'] = array(
    'name' => 'edit own session content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view field_accepted'.
  $permissions['view field_accepted'] = array(
    'name' => 'view field_accepted',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'field_permissions',
  );

  return $permissions;
}
