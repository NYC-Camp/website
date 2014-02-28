<?php
/**
 * @file
 * cod_base_sans_og.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function cod_base_sans_og_user_default_roles() {
  $roles = array();

  // Exported role: content editor.
  $roles['content editor'] = array(
    'name' => 'content editor',
    'weight' => 10,
  );

  return $roles;
}
