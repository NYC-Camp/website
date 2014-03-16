<?php
/**
 * @file
 * CTools module integration.
 */

// Dynamically generate 'mobile_codes_block_DELTA_view' functions.
function ctools_mobile_codes_init() {
  ctools_include('export');
  $blocks = ctools_export_crud_load_all('mobile_codes_blocks');
  if (!empty($blocks)) {
    $code = '';
    foreach ($blocks as $block) {
      $code .= "function mobile_codes_block_block_{$block->name}_view() { return mobile_codes_ctools_block_view('{$block->name}'); }";
    }
    eval($code);
  }
}

/**
 * Implements hook_ctools_plugin_api().
 */
function mobile_codes_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "mobile_codes" && in_array($api, array("default_mobile_codes_blocks", "default_mobile_codes_presets", "default_mobile_codes_providers"))) {
    return array("version" => 2);
  }
}

/**
 * Implements hook_ctools_plugin_directory().
 */
function mobile_codes_ctools_plugin_directory($module, $plugin) {
  if ($module == 'ctools' && $plugin == 'export_ui') {
    return "plugins/{$plugin}";
  }
}

/**
 * Implements hook_mobile_codes_theme_alter() on behalf of ctools.module.
 */
function ctools_mobile_codes_theme_alter(&$items) {
  $items['mobile_codes_providers_export_ui_form_parameters'] = array(
    'render element' => 'element',
    'file' => 'plugins/export_ui/mobile_codes_providers.inc',
  );
}

/**
 * Implements hook_mobile_codes_block_info_alter() on behalf of ctools.module.
 */
function ctools_mobile_codes_block_info_alter(&$blocks) {
  ctools_include('export');
  $items = ctools_export_crud_load_all('mobile_codes_blocks');
  foreach ($items as $block) {
    if (!isset($block->disabled) || !$block->disabled) {
      $blocks["block_{$block->name}"] = array(
        'info' => $block->label,
      );
    }
  }
}

/**
 * Mobile Codes blocks view callback.
 */
function mobile_codes_ctools_block_view($delta) {
  ctools_include('export');
  $block = ctools_export_crud_load('mobile_codes_blocks', $delta);

  $data = '';
  switch ($block->data['type']) {
    case 'raw':
      $data = token_replace($block->data['content']);
      break;

    case 'php':
      if (module_exists('php')) {
        $data = php_eval($block->data['content']);
        break;
      }

      watchdog('mobile_codes', "Mobile Codes Block '%name' requires the PHP module.", array('%name' => $block->name), WATCHDOG_ERROR);
      return FALSE;
  }

  return array(
    'subject' => $block->label,
    'content' => theme('mobilecode', array(
      'data' => $data,
      'attributes' => array('#preset' => $block->preset)
    )),
  );
}
