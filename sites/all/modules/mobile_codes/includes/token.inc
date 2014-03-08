<?php
/**
 * @file
 * Token module integration.
 */

/**
 * Implements hook_mobile_codes_form_ctools_export_ui_edit_item_form_alter().
 */
function token_mobile_codes_form_ctools_export_ui_edit_item_form_alter(&$form, $form_state) {
  if ($form_state['plugin']['schema'] == 'mobile_codes_blocks') {
    $form['tokens'] = array(
      '#type' => 'container',
      'list' => array(
        '#markup' => theme('token_tree_link'),
      ),
      '#states' => array(
        'visible' => array(
          ':input[name="data[type]"]' => array('value' => 'raw'),
        ),
      ),
    );
  }
}
