<?php
/**
 * @file
 * Block module integration.
 */

/**
 * Implements hook_mobile_codes_default_mobile_codes_preset_alter() on behalf of block.module.
 */
function block_mobile_codes_default_mobile_codes_preset_alter(&$export) {
  $preset = new stdClass;
  $preset->disabled = FALSE; /* Edit this to true to make a default preset disabled initially */
  $preset->api_version = 2;
  $preset->name = 'block_node_url';
  $preset->provider = 'google';
  $preset->defaults = array(
    'width' => '180',
    'height' => '180',
    'output_encoding' => 'UTF-8',
  );
  $preset->extras = array();

  $export['block_node_url'] = $preset;
}

/**
 * Implements hook_block_info().
 */
function mobile_codes_block_info() {
  $blocks = array();
  drupal_alter('mobile_codes_block_info', $blocks);
  return $blocks;
}

/**
 * Implements hook_mobile_codes_block_info_alter() on behalf of block.module.
 */
function block_mobile_codes_block_info_alter(&$blocks) {
  $blocks['generate_code'] = array(
    'info' => t('Mobile Code generator'),
  );
}

/**
 * Implements hook_block_configure().
 */
function mobile_codes_block_configure($delta) {
  if (function_exists($function = "mobile_codes_block_{$delta}_configure")) {
    return $function();
  }
  return array();
}

/**
 * Implements hook_block_save().
 */
function mobile_codes_block_save($delta = 0, $edit = array()) {
  if (function_exists($function = "mobile_codes_block_{$delta}_save")) {
    $function($edit);
  }
}

/**
 * Implements hook_block_view().
 */
function mobile_codes_block_view($delta) {
  if (function_exists($function = "mobile_codes_block_{$delta}_view")) {
    return $function();
  }
  return array();
}

/**
 * Code generator block view callback.
 */
function mobile_codes_block_generate_code_view() {
  return array(
    'subject' => t('Mobile Code generator'),
    'content' => drupal_get_form('mobile_codes_block_generate_code_form'),
  );
}

/**
 * Code generator block form.
 */
function mobile_codes_block_generate_code_form($form, &$form_state) {
  $form = array();

  $form['mobile_code'] = array(
    '#type' => 'container',
  );

  if (isset($form_state['values'])) {
    $form['mobile_code'] = array(
      '#title' => t('Output'),
      '#type' => 'fieldset',
    );

    $form['mobile_code']['sample'] = array(
      '#markup' => theme('mobilecode', array('data' => $form_state['values']['text'], 'attributes' => array('#preset' => $form_state['values']['preset']))),
    );

    $form['mobile_code']['filter'] = array(
      '#type' => 'textfield',
      '#title' => t('Filter'),
      '#value' => "[mobilecode #preset='{$form_state['values']['preset']}']{$form_state['values']['text']}[/mobilecode]",
    );

    $form['mobile_code']['theme'] = array(
      '#type' => 'textfield',
      '#title' => t('Theme'),
      '#value' => "theme('mobilecode', array('data' => '{$form_state['values']['text']}', 'attributes' => array('#preset' => '{$form_state['values']['preset']}')));",
    );
  }

  $form['preset'] = array(
    '#type' => 'select',
    '#title' => t('Preset'),
    '#options' => array(),
    '#default_value' => isset($form_state['values']) ? $form_state['values']['preset'] : array(),
  );
  ctools_include('export');
  foreach (ctools_export_crud_load_all('mobile_codes_presets') as $preset) {
    if (!isset($preset->disabled) || !$preset->disabled) {
      $form['preset']['#options'][$preset->name] = $preset->name;
    }
  }

  $form['text'] = array(
    '#type' => 'textarea',
    '#title' => t('Data'),
    '#default_value' => isset($form_state['values']) ? $form_state['values']['text'] : '',
  );

  $form['generate'] = array(
    '#type' => 'submit',
    '#value' => t('Generate'),
    '#ajax' => array(
      'callback' => 'mobile_codes_block_generate_code_form_js',
      'wrapper' => 'edit-mobile-code',
    ),
  );

  return $form;
}

/**
 * Code generator block form AJAX callback.
 */
function mobile_codes_block_generate_code_form_js($form, $form_state) {
  return $form['mobile_code'];
}

/**
 * Code generator block form submit callback.
 */
function mobile_codes_block_generate_code_form_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}
