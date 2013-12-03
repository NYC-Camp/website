<?php
/**
 * @file
 * cod_events.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cod_events_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer free_event registration'.
  $permissions['administer free_event registration'] = array(
    'name' => 'administer free_event registration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'registration',
  );

  // Exported permission: 'create free_event registration'.
  $permissions['create free_event registration'] = array(
    'name' => 'create free_event registration',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'registration',
  );

  // Exported permission: 'create free_event registration other anonymous'.
  $permissions['create free_event registration other anonymous'] = array(
    'name' => 'create free_event registration other anonymous',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'registration',
  );

  // Exported permission: 'create free_event registration other users'.
  $permissions['create free_event registration other users'] = array(
    'name' => 'create free_event registration other users',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'registration',
  );

  // Exported permission: 'delete any free_event registration'.
  $permissions['delete any free_event registration'] = array(
    'name' => 'delete any free_event registration',
    'roles' => array(
      'administrator' => 'administrator',
      'attendee manager' => 'attendee manager',
    ),
    'module' => 'registration',
  );

  // Exported permission: 'delete own free_event registration'.
  $permissions['delete own free_event registration'] = array(
    'name' => 'delete own free_event registration',
    'roles' => array(
      'administrator' => 'administrator',
      'attendee manager' => 'attendee manager',
    ),
    'module' => 'registration',
  );

  // Exported permission: 'update any free_event registration'.
  $permissions['update any free_event registration'] = array(
    'name' => 'update any free_event registration',
    'roles' => array(
      'administrator' => 'administrator',
      'attendee manager' => 'attendee manager',
    ),
    'module' => 'registration',
  );

  // Exported permission: 'update own free_event registration'.
  $permissions['update own free_event registration'] = array(
    'name' => 'update own free_event registration',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'registration',
  );

  // Exported permission: 'view free_event registration'.
  $permissions['view free_event registration'] = array(
    'name' => 'view free_event registration',
    'roles' => array(
      'administrator' => 'administrator',
      'attendee manager' => 'attendee manager',
    ),
    'module' => 'registration',
  );

  // Exported permission: 'view own free_event registration'.
  $permissions['view own free_event registration'] = array(
    'name' => 'view own free_event registration',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'registration',
  );

  return $permissions;
}
