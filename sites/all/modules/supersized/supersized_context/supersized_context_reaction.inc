<?php
/**
 * @file
 * Reaction class of supersized.
 *
 * To apply Supersized.
 */

class supersized_context_reaction extends context_reaction {

  /**
   * Construct option form.
   */
  function options_form($context) {
    $values = $this->fetch_from_context($context);
    $form['#tree'] = TRUE;

    $form['nid'] = array(
      '#type' => 'textfield',
      '#title' => t('Content'),
      '#autocomplete_path' => 'supersized/autocomplete',
      '#maxlength' => 1024,
      '#default_value' => $values ? $values['nid'] : NULL,
      '#description' => t('Slides of the content will be used as the supersized.'),
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
        preg_match('/\[nid: (\d+)\]$/', $context->reactions[$this->plugin]['nid'], $matches);
        $nid = $matches[1];
        return $nid;
      }
    }
  }
}
