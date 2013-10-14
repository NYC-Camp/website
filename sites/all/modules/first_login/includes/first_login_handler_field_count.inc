<?php
/**
 * @file
 * The Views status field handler for first_login.
 */

/**
 * Field handler for first_login count field.
 */
class FirstLoginHandlerFieldCount extends views_handler_field_numeric {
  /**
   * Render method.
   */
  function render($values) {
    return first_login_get_data($values->uid, 'count');
  }
}
