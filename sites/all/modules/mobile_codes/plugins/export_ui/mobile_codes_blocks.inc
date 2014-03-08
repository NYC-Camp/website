<?php
/**
 * @file
 */

/**
 * CTools Export UI required function for plugin definition
 */
function mobile_codes_mobile_codes_blocks_ctools_export_ui() {
  return array(
    'schema' => 'mobile_codes_blocks',
    'access' => 'administer mobile codes',
    'menu' => array(
      'menu prefix' => 'admin/config/content/mobile_codes',
      'menu item' => 'blocks',
      'menu title' => 'Blocks',
      'menu description' => 'Administer Mobile Codes blocks.',
    ),
    'title singular' => t('block'),
    'title singular proper' => t('Block'),
    'title plural' => t('blocks'),
    'title plural proper' => t('Blocks'),
    'form' => array(
      'settings' => 'mobile_codes_blocks_export_ui_form',
      'submit' => 'mobile_codes_blocks_export_ui_form_submit',
    ),
    'export' => array(
      'admin_title' => 'label',
    ),
  );
}

/**
 * Blocks form.
 */
function mobile_codes_blocks_export_ui_form(&$form, &$form_state) {
  $item = $form_state['item'];
  $presets = ctools_export_crud_load_all('mobile_codes_presets');

  $options = array();
  foreach ($presets as $preset) {
    $options[$preset->name] = $preset->name;
  }
  $form['preset'] = array(
    '#type' => 'select',
    '#title' => t('Preset'),
    '#options' => $options,
    '#default_value' => isset($options[$item->preset]) ? $item->preset : key($options),
  );

  $form['data'] = array(
    '#type' => 'container',
    '#tree' => TRUE,
  );

  $options = array(
    'raw' => t('Raw'),
  );
  if (module_exists('php')) {
    $options['php'] = t('PHP');
  }
  $form['data']['type'] = array(
    '#type' => 'select',
    '#title' => t('Data type'),
    '#options' => $options,
    '#default_value' => isset($options[$item->data['type']]) ? $item->data['type'] : key($options),
  );

  $form['data']['content'] = array(
    '#type' => 'textarea',
    '#title' => t('Data'),
    '#default_value' => $item->data['content'],
  );
}

/**
 * Blocks form submit callback.
 */
function mobile_codes_blocks_export_ui_form_submit(&$form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

