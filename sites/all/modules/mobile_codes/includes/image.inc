<?php
/**
 * @file
 * Image module integration.
 */

/**
 * Implements hook_mobile_codes_field_formatter_info() on behalf of image.module.
 */
function image_mobile_codes_field_formatter_info() {
  return array(
    'image' => array(
      'callback' => 'image_mobile_codes_field_formatter_data'
    ),
  );
}

/**
 * Callback for Image module Mobile Codes formatter.
 */
function image_mobile_codes_field_formatter_data($item) {
  return file_create_url($item['uri']);
}

/**
 * Implements hook_mobile_codes_presets_extras() on behalf of image.module.
 */
function image_mobile_codes_presets_extras($settings) {
  $extras = array();

  $options = array();
  foreach (array_keys(image_styles()) as $image_style) {
    $options[$image_style] = $image_style;
  }
  $extras['image_style'] = array(
    'form' => array(
      '#type' => 'select',
      '#title' => t('Image style'),
      '#empty_value' => '',
      '#options' => $options,
      '#default_value' => isset($settings['image_style']) ? $settings['image_style'] : '',
    ),
  );

  return $extras;
}

/**
 * Implements hook_mobile_codes_path_alter() on behalf of image.module.
 */
function image_mobile_codes_path_alter(&$path, $attributes) {
  if (isset($attributes['#preset']->extras['image_style']) && !empty($attributes['#preset']->extras['image_style'])) {
    $path = image_style_url($attributes['#preset']->extras['image_style'], $path);
  }
}
