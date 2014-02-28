<?php
/**
 * @file
 * cod_sponsors_sans_og.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function cod_sponsors_sans_og_user_default_roles() {
  $roles = array();

  // Exported role: sponsor organizer.
  $roles['sponsor organizer'] = array(
    'name' => 'sponsor organizer',
    'weight' => 4,
  );

  return $roles;
}
