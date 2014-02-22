<?php
/**
 * @file
 * Reaction class of supersized.
 *
 * To apply Supersized.
 */

class supersized_context_disable_reaction extends context_reaction {

  /**
   * Construct option form.
   */
  function options_form($context) {
    $values = $this->fetch_from_context($context);
    $form['#tree'] = TRUE;

    $form['disable_supersized'] = array(
      '#type' => 'checkbox',
      '#title' => t('Disable Supersized'),
      '#default_value' => $values ? $values['disable_supersized'] : NULL,
      '#description' => t('Check this checkbox if you would like to disable Supersized based on above condition.'),
    );

    return $form;
  }

  /**
   * See if context contains redirect reaction.
   */
  function execute() {
    $contexts = context_active_contexts();
    foreach ($contexts as $context) {
      if (!empty($context->reactions[$this->plugin])) {
        return TRUE;
      }
    }
  }
}
