<?php
/**
 * @file
 * Mobile Codes module integration.
 */

/**
 * Implements hook_mobile_codes_settings_alter().
 */
function mobile_codes_mobile_codes_settings_alter(&$settings) {
  $settings['url']['alias'] = array(
    'label' => t('Use path alias'),
    'description' => t('Use a path alias if it exists (e.g. node/1 -> section/title)'),
  );

  $settings['general']['path'] = array(
    'label' => t('Storage directory'),
    'description' => t('Where the generated Mobile Codes should be stored.'),
    'form' => array(
      '#type' => 'textfield',
    ),
  );

  $settings['general']['flush'] = array(
    'label' => t('Delete files on flush cache?'),
    'description' => t(''),
  );
}

/**
 * Implements mobile_codes_data_TYPE_SETTING().
 */
function mobile_codes_data_url_alias(&$data) {
  global $base_url;
  $path = str_replace("{$base_url}/", '', $data);
  $alias = drupal_get_path_alias($path);
  $data = str_replace($path, $alias, $data);
}


/**
 * Implements hook_default_mobile_codes_preset().
 */
function mobile_codes_default_mobile_codes_block() {
  $export = array();
  drupal_alter('mobile_codes_default_mobile_codes_block', $export);
  return $export;
}

/**
 * Implements hook_default_mobile_codes_preset().
 */
function mobile_codes_default_mobile_codes_preset() {
  $export = array();
  drupal_alter('mobile_codes_default_mobile_codes_preset', $export);
  return $export;
}

/**
 * Implements hook_mobile_codes_token_info_alter_alter().
 */
function mobile_codes_mobile_codes_token_info_alter_alter(&$data) {
  $data['types']['mobile-codes'] = array(
    'name' => t('Mobile Codes'),
    'description' => t('Mobile Codes tokens.'),
    'needs-data' => 'mobile-codes-data',
    'field' => TRUE,
    'module' => 'mobile_codes',
  );

  $data['tokens']['mobile-codes']['image'] = array(
    'name' => t('Image'),
    'description' => t('The rendered Mobile Code image.'),
    'dynamic' => TRUE,
  );
  $data['tokens']['mobile-codes']['path'] = array(
    'name' => t('Path'),
    'description' => t('The location of the Mobile Code image relative to Drupal root.'),
    'dynamic' => TRUE,
  );
  $data['tokens']['mobile-codes']['url'] = array(
    'name' => t('URL'),
    'description' => t('The web-accessible URL for the Mobile Code image.'),
    'dynamic' => TRUE,
  );

  $data['tokens']['url']['mobile-codes'] = array(
    'name' => t('Mobile Code'),
    'description' => t('The URL as a Mobile Code'),
    'type' => 'mobile-codes'
  );
}

/**
 * Implements hook_mobile_codes_tokens_alter_alter().
 */
function mobile_codes_mobile_codes_tokens_alter_alter(&$replacements, $context) {
  $presets = mobile_codes_presets_load_all();

  // Mobile Codes tokens.
  if ($context['type'] == 'mobile-codes' && !empty($context['data']['mobile-codes-data'])) {
    // [image] dynamic tokens.
    if ($image_tokens = token_find_with_prefix($context['tokens'], 'image')) {
      foreach ($image_tokens as $preset => $token) {
        if (isset($presets[$preset])) {
          $replacements[$token] = theme('mobilecode', array('data' => $context['data']['mobile-codes-data'], 'attributes' => array('#preset' => $preset)));
        }
      }
    }

    // [path] dynamic tokens.
    if ($path_tokens = token_find_with_prefix($context['tokens'], 'path')) {
      foreach ($path_tokens as $preset => $token) {
        if (isset($presets[$preset])) {
          $attributes = array('#preset' => $preset);
          $request = mobile_codes_process_url($context['data']['mobile-codes-data'], $attributes);
          $replacements[$token] = mobile_codes_generate($request);
        }
      }
    }

    // [url] dynamic tokens.
    if ($url_tokens = token_find_with_prefix($context['tokens'], 'url')) {
      foreach ($url_tokens as $preset => $token) {
        if (isset($presets[$preset])) {
          $attributes = array('#preset' => $preset);
          $request = mobile_codes_process_url($context['data']['mobile-codes-data'], $attributes);
          $replacements[$token] = file_create_url(mobile_codes_generate($request));
        }
      }
    }
  }

  // URL tokens.
  if ($context['type'] == 'url' && !empty($context['data']['path'])) {
    $url = url($context['data']['path'], array('absolute' => TRUE));
    foreach ($context['tokens'] as $name => $original) {
      switch ($name) {
        case 'mobile-codes':
          $replacements[$original] = theme('mobilecode', array('data' => $url, 'attributes' => array('#preset' => key($presets))));
          break;
      }
    }

    if (($mobile_codes_tokens = token_find_with_prefix($context['tokens'], 'mobile-codes'))) {
      $replacements += token_generate('mobile-codes', $mobile_codes_tokens, array('mobile-codes-data' => $url));
    }
  }
}

/**
 * Implements hook_mobile_codes_default_mobile_codes_block_alter().
 */
function mobile_codes_mobile_codes_default_mobile_codes_block_alter(&$export) {
  $block = new stdClass();
  $block->disabled = TRUE; /* Edit this to true to make a default block disabled initially */
  $block->api_version = 2;
  $block->name = 'current_url';
  $block->label = 'Current URL';
  $block->preset = 'block_node_url';
  $block->data = array(
    'type' => 'raw',
    'content' => '[current-page:url:absolute]',
  );

  $export['current_url'] = $block;
}

/**
 * Implements hook_mobile_codes_default_mobile_codes_preset_alter().
 */
function mobile_codes_mobile_codes_default_mobile_codes_preset_alter(&$export) {
  $preset = new stdClass;
  $preset->disabled = FALSE; /* Edit this to true to make a default preset disabled initially */
  $preset->api_version = 2;
  $preset->name = 'large';
  $preset->provider = 'google';
  $preset->defaults = array(
    'width' => '400',
    'height' => '400',
    'output_encoding' => 'UTF-8',
  );
  $preset->extras = array();

  $export['large'] = $preset;
  $preset = new stdClass;
  $preset->disabled = FALSE; /* Edit this to true to make a default preset disabled initially */
  $preset->api_version = 2;
  $preset->name = 'medium';
  $preset->provider = 'google';
  $preset->defaults = array(
    'width' => '250',
    'height' => '250',
    'output_encoding' => 'UTF-8',
  );
  $preset->extras = array();

  $export['medium'] = $preset;
  $preset = new stdClass;
  $preset->disabled = FALSE; /* Edit this to true to make a default preset disabled initially */
  $preset->api_version = 2;
  $preset->name = 'small';
  $preset->provider = 'google';
  $preset->defaults = array(
    'width' => '150',
    'height' => '150',
    'output_encoding' => 'UTF-8',
  );
  $preset->extras = array();

  $export['small'] = $preset;
}

/**
 * Implements hook_default_mobile_codes_provider().
 */
function mobile_codes_default_mobile_codes_provider() {
  $export = array();
  drupal_alter('mobile_codes_default_mobile_codes_provider', $export);
  return $export;
}

/**
 * Implements hook_mobile_codes_default_mobile_codes_provider_alter().
 */
function mobile_codes_mobile_codes_default_mobile_codes_provider_alter(&$export) {
  $provider = new stdClass;
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 2;
  $provider->name = 'google';
  $provider->url = 'https://chart.googleapis.com/chart?chs=[width]x[height]&cht=qr&chl=[data]&choe=[output_encoding]';
  $provider->parameters = array(
    'width' => array(
      'token' => 'width',
      'label' => 'Width',
      'type' => 'text',
    ),
    'height' => array(
      'token' => 'height',
      'label' => 'Height',
      'type' => 'text',
    ),
    'data' => array(
      'token' => 'data',
      'type' => 'data',
    ),
    'output_encoding' => array(
      'token' => 'output_encoding',
      'label' => 'Output encoding',
      'type' => 'select',
      'value' => 'UTF-8
Shift_JIS
ISO-8859-1',
    ),
  );

  $export['google'] = $provider;
  $provider = new stdClass;
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 2;
  $provider->name = 'kaywa_dm';
  $provider->url = 'http://datamatrix.kaywa.com/img.php?s=[size]&d=[data]';
  $provider->parameters = array(
    'size' => array(
      'token' => 'size',
      'label' => 'Size',
      'type' => 'select',
      'value' => '5|Small
6|Medium
8|Large
12|Extra Large',
    ),
    'data' => array(
      'token' => 'data',
      'type' => 'data',
    ),
  );

  $export['kaywa_dm'] = $provider;
  $provider = new stdClass;
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 2;
  $provider->name = 'kaywa_qr';
  $provider->url = 'http://qrcode.kaywa.com/img.php?s=[size]&d=[data]';
  $provider->parameters = array(
    'size' => array(
      'token' => 'size',
      'label' => 'Size',
      'type' => 'select',
      'value' => '5|Small
6|Medium
8|Large
12|Extra Large',
    ),
    'data' => array(
      'token' => 'data',
      'type' => 'data',
    ),
  );

  $export['kaywa_qr'] = $provider;
  $provider = new stdClass;
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 2;
  $provider->name = 'nokia_dm';
  $provider->url = 'http://mobilecodes.nokia.com/dm?BARCODE=[data]&X=[size]&type=text';
  $provider->parameters = array(
    'data' => array(
      'token' => 'data',
      'type' => 'data',
    ),
    'size' => array(
      'token' => 'size',
      'label' => 'Size',
      'type' => 'select',
      'value' => '0.12|S
0.18|M
0.25|L',
    ),
  );

  $export['nokia_dm'] = $provider;
  $provider = new stdClass;
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 2;
  $provider->name = 'nokia_qr';
  $provider->url = 'http://mobilecodes.nokia.com/qr?DATA=[data]&MODULE_SIZE=[size]&MARGIN=2&ENCODING=BYTE&type=TEXT';
  $provider->parameters = array(
    'data' => array(
      'token' => 'data',
      'type' => 'data',
    ),
    'size' => array(
      'token' => 'size',
      'label' => 'Size',
      'type' => 'select',
      'value' => '2|S
4|M
6|L',
    ),
  );

  $export['nokia_qr'] = $provider;
  $provider = new stdClass;
  $provider->disabled = FALSE; /* Edit this to true to make a default provider disabled initially */
  $provider->api_version = 2;
  $provider->name = 'qrstuff';
  $provider->url = 'http://www.qrstuff.com/generate.generate?type=TEXT&text=[data]&foreground_color=[color]';
  $provider->parameters = array(
    'data' => array(
      'token' => 'data',
      'type' => 'data',
    ),
    'color' => array(
      'token' => 'color',
      'label' => 'Color',
      'type' => 'text',
    ),
  );

  $export['qrstuff'] = $provider;
}
