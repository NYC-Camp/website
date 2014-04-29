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

  // Exported permission: 'administer barcodes'.
  $permissions['administer barcodes'] = array(
    'name' => 'administer barcodes',
    'roles' => array(
      'site admin' => 'site admin',
    ),
    'module' => 'barcode',
  );

  return $permissions;
}
