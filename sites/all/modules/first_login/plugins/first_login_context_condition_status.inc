<?php
/**
 * @file
 * Context classes for first_login module.
 */

/**
 * Condition based on the user's first login status.
 */
class FirstLoginContextConditionStatus extends context_condition {

  /**
   * Set the available values in the form.
   */
  function condition_values() {
    return array('FALSE' => t('Inactive'), 'TRUE' => t('Active'));
  }

  /**
   * Modify the configuration form.
   */
  function condition_form($context) {
    $form = parent::condition_form($context);
    // Change the form element to select box.
    $form['#type'] = 'select';
    $form['#multiple'] = FALSE;
    return $form;
  }

  /**
   * Submit the values.
   */
  function condition_form_submit($values) {
    return array($values);
  }

  /**
   * Execute the plugin.
   */
  function execute($account) {
    // Get the current first_login status.
    $values = ($account->data['first_login']['status']) ? 'TRUE' : 'FALSE';

    foreach ($this->get_contexts($values) as $context) {
      $this->condition_met($context, $values);
    }
  }
}
