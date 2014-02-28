<?php
/**
 * @file
 * cod_sponsor_sales.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cod_sponsor_sales_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'edit field_sponsorship_level'.
  $permissions['edit field_sponsorship_level'] = array(
    'name' => 'edit field_sponsorship_level',
    'roles' => array(
      'site admin' => 'site admin',
      'sponsor organizer' => 'sponsor organizer',
    ),
    'module' => 'field_permissions',
  );

  return $permissions;
}
