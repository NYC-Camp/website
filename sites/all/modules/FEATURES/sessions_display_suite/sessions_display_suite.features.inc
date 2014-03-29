<?php
/**
 * @file
 * sessions_display_suite.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function sessions_display_suite_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function sessions_display_suite_image_default_styles() {
  $styles = array();

  // Exported image style: user_picture_display_suite.
  $styles['user_picture_display_suite'] = array(
    'name' => 'user_picture_display_suite',
    'effects' => array(
      20 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 110,
          'height' => 110,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
