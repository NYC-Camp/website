<?php
/**
 * @file
 * qr_code.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function qr_code_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer mobile codes'.
  $permissions['administer mobile codes'] = array(
    'name' => 'administer mobile codes',
    'roles' => array(
      'site admin' => 'site admin',
    ),
    'module' => 'mobile_codes',
  );

  // Exported permission: 'use text format mobile_codes_formatting'.
  $permissions['use text format mobile_codes_formatting'] = array(
    'name' => 'use text format mobile_codes_formatting',
    'roles' => array(
      'site admin' => 'site admin',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
