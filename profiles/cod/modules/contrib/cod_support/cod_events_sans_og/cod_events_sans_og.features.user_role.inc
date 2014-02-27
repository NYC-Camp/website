<?php
/**
 * @file
 * cod_events_sans_og.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function cod_events_sans_og_user_default_roles() {
  $roles = array();

  // Exported role: attendee manager.
  $roles['attendee manager'] = array(
    'name' => 'attendee manager',
    'weight' => 5,
  );

  return $roles;
}
