<?php
/**
 * @file
 * The Views status field handler for first_login.
 */

/**
 * Field handler for first_login status field.
 */
class FirstLoginHandlerFieldStatus extends views_handler_field_boolean {
  /**
   * Render method.
   */
  function render($values) {
    // Get the current first login status.
    $value = first_login_get_data($values->uid, 'status');

    if (isset($value)) {
      if (!empty($this->options['not'])) {
        $value = !$value;
      }
      // Set the available option labels.
      switch ($this->options['type']) {
        case 'yes-no':
        default:
          return $value ? t('Yes') : t('No');
        case 'true-false':
          return $value ? t('True') : t('False');
        case 'on-off':
          return $value ? t('On') : t('Off');
        case 'active-inactive':
          return $value ? t('Active') : t('Inactive');
      }
    }
  }
}
