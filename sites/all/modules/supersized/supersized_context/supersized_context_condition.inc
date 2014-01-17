<?php

/**
 * @file
 * Condition class of supersized.
 *
 * Determine if there are any Supersized assigned.
 */

class supersized_context_condition extends context_condition {
  /**
   * Override condition_values().
   */
  function condition_values() {
    return array(1 => t('Active if no supersized assigned either in the node or by context.'));
  }
  /**
   * Override editor_form().
   */
  function editor_form($context = NULL) {
    $form = parent::editor_form($context);
    $form[1]['#title'] = t('Active if no supersized assigned either in the node or by context.');
    $form['#weight'] = -10;
    return $form;
  }
  /**
   * Override execute().
   */
  function execute() {
    foreach ($this->get_contexts() as $context) {
      $node = NULL;
      // Get node by page.
      if (empty($node)) {
        if (arg(2) !== 'edit') {
          $node = menu_get_object();
        }
      }
      if ($node) {
        $field = supersized_get_supersized_field($node);
        $supersized = $field['items'];
        if (empty($supersized)) {
          $this->condition_met($context);
        }
      }
      else {
        $this->condition_met($context);
      }
    }
  }
}
