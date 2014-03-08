<?php
/**
 * @file
 * Text module integration.
 */

/**
 * Implements hook_mobile_codes_field_formatter_info() on behalf of text.module.
 */
function text_mobile_codes_field_formatter_info() {
  return array(
    'text' => array(
      'callback' => 'text_mobile_codes_field_formatter_data'
    ),
  );
}

/**
 * Implements hook_mobile_codes_token_info_alter_alter() on behalf of text.module.
 */
function text_mobile_codes_token_info_alter_alter(&$data) {
  if (isset($data['tokens']['text-field-value'])) {
    $data['tokens']['text-field-value']['mobile-codes'] = array(
      'name' => t('Mobile Code'),
      'description' => t('The text field value as a Mobile Code'),
      'type' => 'mobile-codes'
    );
  }
}

/**
 * Implements hook_mobile_codes_tokens_alter_alter() on behalf of text.module.
 */
function text_mobile_codes_tokens_alter_alter(&$replacements, $context) {
  $presets = mobile_codes_presets_load_all();
  if ($context['type'] == 'text-field-value' && !empty($context['data']['item'])) {
    foreach ($context['tokens'] as $name => $original) {
      switch ($name) {
        case 'mobile-codes':
          $replacements[$original] = theme('mobilecode', array('data' => $context['data']['item']['value'], 'attributes' => array('#preset' => key($presets))));
          break;
      }
    }

    if (($mobile_codes_tokens = token_find_with_prefix($context['tokens'], 'mobile-codes'))) {
      $replacements += token_generate('mobile-codes', $mobile_codes_tokens, array('mobile-codes-data' => $context['data']['item']['value']));
    }
  }
}

/**
 * Callback for Text module Mobile Codes formatter.
 */
function text_mobile_codes_field_formatter_data($item) {
  return $item['safe_value'];
}
