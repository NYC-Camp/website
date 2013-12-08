<?php
/**
 * @file
 * podcasts.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function podcasts_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|podcast|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'podcast';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_podcast_date',
        1 => 'field_podcast_image',
        2 => 'field_podcast_description',
        3 => 'field_podcast_file',
      ),
    ),
    'fields' => array(
      'field_podcast_date' => 'ds_content',
      'field_podcast_image' => 'ds_content',
      'field_podcast_description' => 'ds_content',
      'field_podcast_file' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => FALSE,
  );
  $export['node|podcast|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|podcast|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'podcast';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_podcast_date',
        1 => 'field_podcast_image',
        2 => 'field_podcast_intro',
        3 => 'field_podcast_file',
        4 => 'field_podcast_description',
      ),
    ),
    'fields' => array(
      'field_podcast_date' => 'ds_content',
      'field_podcast_image' => 'ds_content',
      'field_podcast_intro' => 'ds_content',
      'field_podcast_file' => 'ds_content',
      'field_podcast_description' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 0,
  );
  $export['node|podcast|full'] = $ds_layout;

  return $export;
}
