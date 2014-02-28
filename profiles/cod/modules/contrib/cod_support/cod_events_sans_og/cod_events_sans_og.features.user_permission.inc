<?php
/**
 * @file
 * cod_events_sans_og.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cod_events_sans_og_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer registration'.
  $permissions['administer registration'] = array(
    'name' => 'administer registration',
    'roles' => array(
      'site admin' => 'site admin',
      'summit organizer' => 'summit organizer',
    ),
    'module' => 'registration',
  );

  // Exported permission: 'administer registration states'.
  $permissions['administer registration states'] = array(
    'name' => 'administer registration states',
    'roles' => array(
      'site admin' => 'site admin',
      'summit organizer' => 'summit organizer',
    ),
    'module' => 'registration',
  );

  // Exported permission: 'administer registration types'.
  $permissions['administer registration types'] = array(
    'name' => 'administer registration types',
    'roles' => array(
      'site admin' => 'site admin',
      'summit organizer' => 'summit organizer',
    ),
    'module' => 'registration',
  );

  return $permissions;
}
