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

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|sponsorship_option|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'sponsorship_option';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_sponsorship_description',
        1 => 'field_sponsorship_image',
        2 => 'field_sponsorship_price_language',
        3 => 'group_sponsorship_benefits',
        4 => 'field_sponsorship_ben_prog_cover',
        5 => 'field_sponsorship_ben_prog_list',
        6 => 'field_sponsorship_ben_sign_solo',
        7 => 'field_sponsorship_ben_sign_combo',
        8 => 'field_sponsorship_ben_job_fair',
        9 => 'field_sponsorship_ben_web_promo',
        10 => 'field_sponsorship_ben_keynote',
        11 => 'field_sponsorship_ben_social',
      ),
    ),
    'fields' => array(
      'field_sponsorship_description' => 'ds_content',
      'field_sponsorship_image' => 'ds_content',
      'field_sponsorship_price_language' => 'ds_content',
      'group_sponsorship_benefits' => 'ds_content',
      'field_sponsorship_ben_prog_cover' => 'ds_content',
      'field_sponsorship_ben_prog_list' => 'ds_content',
      'field_sponsorship_ben_sign_solo' => 'ds_content',
      'field_sponsorship_ben_sign_combo' => 'ds_content',
      'field_sponsorship_ben_job_fair' => 'ds_content',
      'field_sponsorship_ben_web_promo' => 'ds_content',
      'field_sponsorship_ben_keynote' => 'ds_content',
      'field_sponsorship_ben_social' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 0,
  );
  $export['node|sponsorship_option|full'] = $ds_layout;

  return $export;
}
