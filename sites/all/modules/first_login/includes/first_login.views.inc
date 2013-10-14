<?php
/**
 * @file
 * Views support for first_login -module.
 */

/**
 * Implements hook_views_handlers().
 */
function first_login_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'first_login') . '/includes',
    ),
    'handlers' => array(
      'FirstLoginHandlerFieldStatus' => array(
        'parent' => 'views_handler_field_boolean',
      ),
      'FirstLoginHandlerFieldCount' => array(
        'parent' => 'views_handler_field_numeric',
      ),
    ),
  );
}

/**
 * Implements hook_views_data().
 */
function first_login_views_data() {

  // We're using a "fake" field since our data
  // doesn't come from a real database field,
  // but from the serialized data-field.
  // See http://drupal.org/node/763452#comment-2812692
  // for more info.
  // First login status.
  $data['users']['first_login_status'] = array(
    'title' => t('First login status'),
    'help' => t('Current first login status.'),
    'real field' => 'uid',
    'field' => array(
      'handler' => 'FirstLoginHandlerFieldStatus',
      'click sortable' => TRUE,
    ),
  );
  // First login count.
  $data['users']['first_login_count'] = array(
    'title' => t('First login count'),
    'help' => t('Number of "first logins" the user currently has.'),
    'real field' => 'uid',
    'field' => array(
      'handler' => 'FirstLoginHandlerFieldCount',
      'click sortable' => TRUE,
    ),
  );
  return $data;
}
