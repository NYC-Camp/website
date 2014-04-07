<?php
/**
 * @file
 * personal_schedule.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function personal_schedule_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: main-menu_my-registrations:menutoken/533f43bf08a2f
  $menu_links['main-menu_my-registrations:menutoken/533f43bf08a2f'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'menutoken/533f43bf08a2f',
    'router_path' => 'menutoken/%',
    'link_title' => 'My Registrations',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
      'menu_token_link_path' => 'user/[current-user:uid]/my-registration',
      'menu_token_data' => array(
        'user' => array(
          'type' => 'user',
          'plugin' => 'user_context',
          'options' => array(),
        ),
      ),
      'menu_token_options' => array(
        'clear' => 0,
      ),
      'identifier' => 'main-menu_my-registrations:menutoken/533f43bf08a2f',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'main-menu_my-profile:user',
  );
  // Exported menu link: main-menu_my-sessions:menutoken/533f43ef3078e
  $menu_links['main-menu_my-sessions:menutoken/533f43ef3078e'] = array(
    'menu_name' => 'main-menu',
    'link_path' => 'menutoken/533f43ef3078e',
    'router_path' => 'menutoken/%',
    'link_title' => 'My Sessions',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
      'alter' => TRUE,
      'menu_token_link_path' => 'user/[current-user:uid]/my-sessions',
      'menu_token_data' => array(
        'user' => array(
          'type' => 'user',
          'plugin' => 'user_context',
          'options' => array(),
        ),
      ),
      'menu_token_options' => array(
        'clear' => 0,
      ),
      'identifier' => 'main-menu_my-sessions:menutoken/533f43ef3078e',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'main-menu_my-profile:user',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('My Registrations');
  t('My Sessions');


  return $menu_links;
}
