<?php
/**
 * @file
 * Node module integration.
 */

/**
 * Implements hook_mobile_codes_form_FORM_ID_alter() on behalf of node.module.
 */
function node_mobile_codes_form_node_type_form_alter(&$form, $form_state) {
  $settings = variable_get("mobile_codes_{$form['#node_type']->type}", array());

  $form['mobile_codes'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mobile Codes'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'additional_settings',
    '#tree' => TRUE,
  );

  $form['mobile_codes']['enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#description' => t('If enabled, a Mobile Codes pseudo field will be available on the Manage display page for this content type.'),
    '#default_value' => isset($settings['enabled']) ? $settings['enabled'] : FALSE,
  );

  $presets = array();
  foreach (mobile_codes_presets_load_all() as $preset) {
    $presets[$preset->name] = $preset->name;
  }
  $form['mobile_codes']['preset'] = array(
    '#type' => 'select',
    '#title' => t('Preset'),
    '#options' => $presets,
    '#default_value' => isset($settings['preset']) ? $settings['preset'] : NULL,
    '#states' => array(
      'invisible' => array(
        ':input[name="mobile_codes[enabled]"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['#submit'][] = 'mobile_codes_node_form_node_type_submit';
}

/**
 * Submit callback for Node type form alterations.
 */
function mobile_codes_node_form_node_type_submit($form, &$form_state) {
  variable_set("mobile_codes_{$form_state['values']['type']}", $form_state['values']['mobile_codes']);
}

/**
 * Implements hook_field_extra_fields().
 */
function mobile_codes_field_extra_fields() {
  $extra = array();

  foreach (node_type_get_types() as $type) {
    $settings = variable_get("mobile_codes_{$type->type}", array());
    if (!empty($settings['enabled'])) {
      $extra['node'][$type->type] = array(
        'display' => array(
          'mobile_codes' => array(
            'label' => t('Mobile codes: Node URL'),
            'description' => t('The URL of this node as a Mobile code.'),
            'weight' => 0,
          ),
        ),
      );
    }
  }

  return $extra;
}

/**
 * Implements hook_node_view().
 */
function mobile_codes_node_view($node, $view_mode, $langcode) {
  $settings = variable_get("mobile_codes_{$node->type}", array());
  if (!empty($settings['enabled'])) {
    $node->content['mobile_codes'] = array(
      '#theme' => 'mobilecode',
      '#data' => url("node/{$node->nid}"),
      '#attributes' => array(
        '#preset' => $settings['preset'],
      ),
    );
  }
}
