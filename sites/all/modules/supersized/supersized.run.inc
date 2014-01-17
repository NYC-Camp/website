<?php

/**
 * @file
 * Supersize run file.
 *
 * This file contain the code that startup Supersized on a page.
 */

/**
 * Start supersized with Supersized plugin.
 */
function supersized_run($node, &$page) {

  // Check if supersized field exists.
  $field = supersized_get_supersized_field($node);
  if (empty($field)) {
    return;
  }

  // Get Supersized info.
  $items = $field['items'];
  $instance = $field['instance'];

  // Exit if no items found.
  if (empty($items)) {
    return;
  }

  // Try to find if there's a specific settings for this particular node.
  $settings = supersized_get_node_settings($node);
  if (empty($settings)) {
    $settings = $field['instance']['settings'];
  }

  // Check mobile device.
  if (isset($settings['mobile_disabled']) && $settings['mobile_disabled'] === 1 && module_exists('browscap')) {
    $browser = browscap_get_browser();
    if ($browser['ismobiledevice'] == 'true') {
      return;
    }
  }

  // Detect library.
  $library = libraries_load('supersized');
  if (empty($library['loaded'])) {
    $info = supersized_libraries_info();
    $info = $info['supersized'];
    $url = l(t('here'), $info['download url']);
    $message = t('Install version 3.2.8 of the Supersized (from @url) in a libraries directory such as "sites/all/libraries."', array('@url' => $url));
    drupal_set_message($message, 'error');
    return FALSE;
  }

  // Construct image objects.
  $images = array();
  foreach ($items as $key => $item) {
    $image = new stdClass();
    if (!empty($item['title'])) {
      $image->title = $item['title'];
    }
    if (!empty($item['description'])) {
      $image->body = $item['description'];
    }
    if (!empty($item['link'])) {
      $image->url = $item['link'];
    }
    $image->thumb = image_style_url($instance['widget']['settings']['preview_image_style'], $item['uri']);
    if (isset($instance['display']['full'])) {
      if (isset($instance['display']['full']['settings']['image_style']) && !empty($instance['display']['full']['settings']['image_style'])) {
        $image->image = image_style_url($instance['display']['full']['settings']['image_style'], $item['uri']);
      }
      else {
        $image->image = file_create_url($item['uri']);
      }
    }
    else {
      if (isset($instance['display']['default']['settings']['image_style']) && !empty($instance['display']['default']['settings']['image_style'])) {
        $image->image = image_style_url($instance['display']['default']['settings']['image_style'], $item['uri']);
      }
      else {
        $image->image = file_create_url($item['uri']);
      }
    }
    $images[] = $image;
  }

  // Image path.
  $image_path = $GLOBALS['base_path'] . $library['library path'] . '/slideshow/img/';
  if (is_dir(path_to_theme() . '/images/supersized')) {
    $image_path = $GLOBALS['base_path'] . path_to_theme() . '/images/supersized/';
  }

  // Add neccessary JS and CSS files.
  drupal_add_css(drupal_get_path('module', 'supersized') . '/css/supersized-default.css');
  drupal_add_js(drupal_get_path('module', 'supersized') . '/js/supersized.js');
  drupal_add_js(array(
    'supersized' => array(
      'autoplay' => $settings['functionalities']['autoplay'],
      'start_slide' => $settings['functionalities']['start_slide'],
      'stop_loop' => $settings['functionalities']['stop_loop'],
      'random' => $settings['functionalities']['random'],
      'slide_interval' => $settings['functionalities']['slide_interval'],
      'transition' => $settings['functionalities']['transition'],
      'transition_speed' => $settings['functionalities']['transition_speed'],
      'new_window' => $settings['functionalities']['new_window'],
      'pause_hover' => $settings['functionalities']['pause_hover'],
      'keyboard_nav' => $settings['functionalities']['keyboard_nav'],
      'performance' => $settings['functionalities']['performance'],
      'image_protect' => $settings['functionalities']['image_protect'],
      'on_new_slide' => $settings['functionalities']['on_new_slide'],
      'min_width' => $settings['dimension']['min_width'],
      'min_height' => $settings['dimension']['min_height'],
      'vertical_center' => $settings['dimension']['vertical_center'],
      'horizontal_center' => $settings['dimension']['horizontal_center'],
      'fit_always' => $settings['dimension']['fit_always'],
      'fit_portrait' => $settings['dimension']['fit_portrait'],
      'fit_landscape' => $settings['dimension']['fit_landscape'],
      'slide_links' => $settings['components']['slide_links'],
      'thumbnail_navigation' => $settings['components']['thumbnail_navigation'],
      'thumb_links' => $settings['components']['thumb_links'],
      'progress_bar' => $settings['components']['progress_bar'],
      'mouse_scrub' => $settings['components']['mouse_scrub'],
      'slides' => $images,
      'image_path' => $image_path,
    )), 'setting'
  );

  // Add overlay.
  if (isset($settings['functionalities']['overlay']) && $settings['functionalities']['overlay'] != 'none') {
    $page['page_bottom']['supersized']['overlay'] = array(
      '#type' => 'markup',
      '#markup' => theme('supersized_overlay', array('overlay_key' => $settings['functionalities']['overlay'])),
    );
  }

  // Add arrow navigation markup.
  if ($settings['components']['arrow_nav']) {
    $page['page_bottom']['supersized']['arrow_nav'] = array(
      '#type' => 'markup',
      '#markup' => theme('supersized_arrow_nav'),
    );
  }

  // Add progress bar.
  if ($settings['components']['progress_bar']) {
    $page['page_bottom']['supersized']['progress_bar'] = array(
      '#type' => 'markup',
      '#markup' => theme('supersized_progress_bar'),
    );
  }

  // Add thumb nav.
  if ($settings['components']['thumbnail_navigation']) {
    $page['page_bottom']['supersized']['thumbnail_navigation'] = array(
      '#type' => 'markup',
      '#markup' => theme('supersized_thumbnail_navigation'),
    );
  }

  // Add thumb links.
  if ($settings['components']['thumb_links']) {
    $page['page_bottom']['supersized']['thumb_tray'] = array(
      '#type' => 'markup',
      '#markup' => theme('supersized_thumb_links'),
    );
  }

  // Control bar.
  if ($settings['components']['control_bar']) {
    $page['page_bottom']['supersized']['control_bar'] = array(
      '#type' => 'markup',
      '#markup' => theme('supersized_control_bar'),
    );
  }

}
