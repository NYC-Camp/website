<?php

/**
 * @file
 * Implement an image field, based on the file module's file field.
 */

/**
 * Implements hook_field_info().
 */
function supersized_field_info() {
  return array(
    'supersized' => array(
      'label' => t('Supersized Slide'),
      'description' => t('A slide of the supersized'),
      'settings' => array(
        'uri_scheme' => variable_get('file_default_scheme', 'public'),
        'default_image' => 0,
      ),
      'instance_settings' => array(
        'file_extensions' => 'png gif jpg jpeg',
        'file_directory' => '',
        'max_filesize' => '',
        'alt_field' => 0,
        'title_field' => 0,
        'description_field' => 0,
        'link_field' => 0,
        'max_resolution' => '',
        'min_resolution' => '',
        'default_image' => 0,
        'mobile_disabled' => 1,
        'functionalities' => array(
          'autoplay' => supersized_default_settings('autoplay'),
          'start_slide' => supersized_default_settings('start_slide'),
          'stop_loop' => supersized_default_settings('stop_loop'),
          'random' => supersized_default_settings('random'),
          'slide_interval' => supersized_default_settings('slide_interval'),
          'transition' => supersized_default_settings('transition'),
          'transition_speed' => supersized_default_settings('transition_speed'),
          'new_window' => supersized_default_settings('new_window'),
          'pause_hover' => supersized_default_settings('pause_hover'),
          'keyboard_nav' => supersized_default_settings('keyboard_nav'),
          'performance' => supersized_default_settings('performance'),
          'image_protect' => supersized_default_settings('image_protect'),
          'on_new_slide' => supersized_default_settings('on_new_slide'),
          'overlay' => supersized_default_settings('overlay'),
        ),
        'dimension' => array(
          'min_width' => supersized_default_settings('min_width'),
          'min_height' => supersized_default_settings('min_height'),
          'vertical_center' => supersized_default_settings('vertical_center'),
          'horizontal_center' => supersized_default_settings('horizontal_center'),
          'fit_always' => supersized_default_settings('fit_always'),
          'fit_portrait' => supersized_default_settings('fit_portrait'),
          'fit_landscape' => supersized_default_settings('fit_landscape'),
        ),
        'components' => array(
          'arrow_nav' => supersized_default_settings('arrow_nav'),
          'slide_links' => supersized_default_settings('slide_links'),
          'thumb_links' => supersized_default_settings('thumb_links'),
          'thumbnail_navigation' => supersized_default_settings('thumbnail_navigation'),
          'progress_bar' => supersized_default_settings('progress_bar'),
          'mouse_scrub' => supersized_default_settings('mouse_scrub'),
          'control_bar' => supersized_default_settings('control_bar'),
        ),
      ),
      'default_widget' => 'supersized_slide',
      'default_formatter' => 'supersized',
    ),
  );
}

/**
 * A helper function to get supersized default settings.
 */
function supersized_default_settings($setting) {
  $settings = array(
    'autoplay' => 1,
    'start_slide' => 1,
    'stop_loop' => 0,
    'random' => 0,
    'slide_interval' => 4000,
    'transition' => 1,
    'transition_speed' => 750,
    'new_window' => 0,
    'pause_hover' => 0,
    'keyboard_nav' => 1,
    'performance' => 1,
    'image_protect' => 0,
    'on_new_slide' => 'on_new_slide_callback',
    'min_width' => 0,
    'min_height' => 0,
    'vertical_center' => 1,
    'horizontal_center' => 1,
    'fit_always' => 0,
    'fit_portrait' => 1,
    'fit_landscape' => 0,
    'arrow_nav' => 0,
    'slide_links' => 0,
    'thumb_links' => 1,
    'thumbnail_navigation' => 0,
    'progress_bar' => 1,
    'mouse_scrub' => 0,
    'control_bar' => 1,
    'mobile_disabled' => 1,
    'overlay' => 'none',
  );
  return (isset($settings[$setting])) ? $settings[$setting] : NULL;
}

/**
 * Implements hook_field_settings_form().
 */
function supersized_field_settings_form($field, $instance) {
  $form = image_field_settings_form($field, $instance);
  unset($form['default_image']);
  return $form;
}

/**
 * Implements hook_field_instance_settings_form().
 */
function supersized_field_instance_settings_form($field, $instance) {

  drupal_add_css(drupal_get_path('module', 'supersized') . '/css/supersized-default.css');

  // Take image form as basic.
  $form = image_field_instance_settings_form($field, $instance);

  $settings = $instance['settings'];

  // Add other configuration options.
  $url = l(t('Browscap'), 'http://drupal.org/project/browscap');
  $description = t('You may disable Supersized! if !url installed.', array('!url' => $url));
  if (module_exists('browscap')) {
    $form['mobile_disabled'] = array(
      '#type' => 'checkbox',
      '#title' => t('Disabled Supersized on mobile devices'),
      '#default_value' => isset($settings['mobile_disabled']) ? $settings['mobile_disabled'] : supersized_default_settings('mobile_disabled'),
    );
  }
  else {
    $form['mobile_disabled_tips'] = array(
      '#markup' => $description,
    );
  }

  // Get overlay options.
  $overlay_options = supersized_overlay_options();

  $form['description_field'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable <em>Description</em> field'),
    '#default_value' => $settings['description_field'],
    '#description' => t('The description of the slide.'),
    '#weight' => 10,
  );
  $form['link_field'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable <em>Link</em> field'),
    '#default_value' => $settings['link_field'],
    '#description' => t('The link of the slide.'),
    '#weight' => 11,
  );
  $form['functionalities'] = array(
    '#type' => 'fieldset',
    '#title' => t("Supersized functionality settings"),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['functionalities']['autoplay'] = array(
    '#type' => 'radios',
    '#title' => t('Auto play'),
    '#description' => t('Determines whether slideshow begins playing when page is loaded.'),
    '#options' => array(1 => t('Yes'), 0 => 'No'),
    '#default_value' => isset($settings['functionalities']['autoplay']) ? $settings['functionalities']['autoplay'] : supersized_default_settings('autoplay'),
    '#required' => TRUE,
  );
  $form['functionalities']['start_slide'] = array(
    '#type' => 'hidden',
    '#value' => 1,
  );
  $form['functionalities']['stop_loop'] = array(
    '#type' => 'radios',
    '#title' => t('Loop'),
    '#description' => t('Pauses slideshow upon reaching the last slide.'),
    '#options' => array(0 => t('Yes'), 1 => 'No'),
    '#default_value' => isset($settings['functionalities']['stop_loop']) ? $settings['functionalities']['stop_loop'] : supersized_default_settings('stop_loop'),
    '#required' => TRUE,
  );
  $form['functionalities']['random'] = array(
    '#type' => 'radios',
    '#title' => t('Random'),
    '#description' => t('Slides are shown in a random order.'),
    '#options' => array(1 => t('Yes'), 0 => 'No'),
    '#default_value' => isset($settings['functionalities']['random']) ? $settings['functionalities']['random'] : supersized_default_settings('random'),
    '#required' => TRUE,
  );
  $form['functionalities']['slide_interval'] = array(
    '#type' => 'textfield',
    '#title' => t('Slide interval'),
    '#description' => t('Time between slide changes in milliseconds.'),
    '#default_value' => isset($settings['functionalities']['slide_interval']) ? $settings['functionalities']['slide_interval'] : supersized_default_settings('slide_interval'),
    '#size' => 6,
    '#maxlength' => 6,
    '#required' => TRUE,
  );
  $form['functionalities']['transition'] = array(
    '#type' => 'select',
    '#title' => t('Transition'),
    '#descipion' => t('Controls which effect is used to transition between slides.'),
    '#options' => array(
      0 => t('None'),
      1 => t('Fade'),
      2 => t('Slide Top'),
      3 => t('Slide Right'),
      4 => t('Slide Bottom'),
      5 => t('Slide Left'),
      6 => t('Carousel Right'),
      7 => t('Carousel Left'),
    ),
    '#default_value' => isset($settings['functionalities']['transition']) ? $settings['functionalities']['transition'] : supersized_default_settings('transition'),
    '#required' => TRUE,
  );
  $form['functionalities']['transition_speed'] = array(
    '#type' => 'textfield',
    '#title' => t('Transition speed'),
    '#description' => t('Speed of transitions in milliseconds.'),
    '#default_value' => isset($settings['functionalities']['transition_speed']) ? $settings['functionalities']['transition_speed'] : supersized_default_settings('transition_speed'),
    '#size' => 6,
    '#maxlength' => 6,
    '#required' => TRUE,
  );
  $form['functionalities']['new_window'] = array(
    '#type' => 'radios',
    '#title' => t('New window'),
    '#description' => t('Slide links open in a new window.'),
    '#options' => array(1 => t('Yes'), 0 => 'No'),
    '#default_value' => isset($settings['functionalities']['new_window']) ? $settings['functionalities']['new_window'] : supersized_default_settings('new_window'),
    '#required' => TRUE,
  );
  $form['functionalities']['pause_hover'] = array(
    '#type' => 'radios',
    '#title' => t('Pause on hover'),
    '#description' => t('Pauses slideshow while current image hovered over.'),
    '#options' => array(1 => t('Yes'), 0 => 'No'),
    '#default_value' => isset($settings['functionalities']['pause_hover']) ? $settings['functionalities']['pause_hover'] : supersized_default_settings('pause_hover'),
    '#required' => TRUE,
  );
  $form['functionalities']['keyboard_nav'] = array(
    '#type' => 'hidden',
    '#value' => 1,
  );
  $form['functionalities']['performance'] = array(
    '#type' => 'hidden',
    '#value' => 1,
  );
  $form['functionalities']['image_protect'] = array(
    '#type' => 'hidden',
    '#value' => 1,
  );
  $form['functionalities']['on_new_slide'] = array(
    '#type' => 'hidden',
    '#value' => 'on_new_slide_callback',
  );
  $form['functionalities']['overlay'] = array(
    '#type' => 'radios',
    '#title' => t('Overylay'),
    '#description' => t('To add an overlay texture to the slide images.'),
    '#options' => $overlay_options,
    '#default_value' => isset($settings['functionalities']['overlay']) ? $settings['functionalities']['overlay'] : supersized_default_settings('overlay'),
    '#required' => TRUE,
    '#process' => array('supersized_form_process_radios'),
  );
  $form['dimension'] = array(
    '#type' => 'fieldset',
    '#title' => t("Supersized Dimension settings"),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['dimension']['min_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum width'),
    '#description' => t("Minimum width the image is allowed to be. If it is met, the image won't size down any further."),
    '#default_value' => isset($settings['dimension']['min_width']) ? $settings['dimension']['min_width'] : supersized_default_settings('min_width'),
    '#size' => 6,
    '#maxlength' => 6,
    '#required' => TRUE,
  );
  $form['dimension']['min_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Minimum height'),
    '#description' => t("Minimum height the image is allowed to be. If it is met, the image won't size down any further."),
    '#default_value' => isset($settings['dimension']['min_height']) ? $settings['dimension']['min_height'] : supersized_default_settings('min_height'),
    '#size' => 6,
    '#maxlength' => 6,
    '#required' => TRUE,
  );
  $form['dimension']['vertical_center'] = array(
    '#type' => 'hidden',
    '#value' => 1,
  );
  $form['dimension']['horizontal_center'] = array(
    '#type' => 'hidden',
    '#value' => 1,
  );
  $form['dimension']['fit_always'] = array(
    '#type' => 'radios',
    '#title' => t('Always fit'),
    '#description' => t('Prevents the image from ever being cropped. Ignores minimum width and height.'),
    '#options' => array(1 => t('Yes'), 0 => 'No'),
    '#default_value' => isset($settings['dimension']['fit_always']) ? $settings['dimension']['fit_always'] : supersized_default_settings('fit_always'),
    '#required' => TRUE,
  );
  $form['dimension']['fit_portrait'] = array(
    '#type' => 'radios',
    '#title' => t('Fit portrait'),
    '#description' => t('Prevents the image from being cropped by locking it at 100% height.'),
    '#options' => array(1 => t('Yes'), 0 => 'No'),
    '#default_value' => isset($settings['dimension']['fit_portrait']) ? $settings['dimension']['fit_portrait'] : supersized_default_settings('fit_portrait'),
    '#required' => TRUE,
  );
  $form['dimension']['fit_landscape'] = array(
    '#type' => 'radios',
    '#title' => t('Fit landscape'),
    '#description' => t('Prevents the image from being cropped by locking it at 100% width.'),
    '#options' => array(1 => t('Yes'), 0 => 'No'),
    '#default_value' => isset($settings['dimension']['fit_landscape']) ? $settings['dimension']['fit_landscape'] : supersized_default_settings('fit_landscape'),
    '#required' => TRUE,
  );
  $form['components'] = array(
    '#type' => 'fieldset',
    '#title' => t("Supersized component settings"),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['components']['arrow_nav'] = array(
    '#type' => 'radios',
    '#title' => t('Arrow navigation'),
    '#description' => t('Provide arrows for left and right navigation.'),
    '#options' => array(1 => t('Yes'), 0 => 'No'),
    '#default_value' => isset($settings['components']['arrow_nav']) ? $settings['components']['arrow_nav'] : supersized_default_settings('arrow_nav'),
    '#required' => TRUE,
  );
  $form['components']['slide_links'] = array(
    '#type' => 'select',
    '#title' => t('Slide links'),
    '#description' => t('Generates a list of links that jump to the corresponding slide.'),
    '#options' => array(
      0 => t('Disables slide links'),
      'num' => t('Numbers (Default)'),
      'name' => t('Title of slide'),
      'blank' => t('Links are empty. Allows for background sprites.'),
    ),
    '#default_value' => isset($settings['components']['slide_links']) ? $settings['components']['slide_links'] : supersized_default_settings('slide_links'),
    '#required' => TRUE,
  );
  $form['components']['thumb_links'] = array(
    '#type' => 'radios',
    '#title' => t('Thumb links'),
    '#description' => t('Individual thumb links for each slide.'),
    '#options' => array(1 => t('Yes'), 0 => 'No'),
    '#default_value' => isset($settings['components']['thumb_links']) ? $settings['components']['thumb_links'] : supersized_default_settings('thumb_links'),
    '#required' => TRUE,
  );
  $form['components']['thumbnail_navigation'] = array(
    '#type' => 'radios',
    '#title' => t('Thumbnail navigation'),
    '#description' => t("Toggles forward/backward thumbnail navigation. When on, thumbnails from the next/previous posts are generated and can be clicked to navigate. If the 'thumb' field for the slide is empty, it will simply scale down the full size image."),
    '#options' => array(1 => t('Yes'), 0 => 'No'),
    '#default_value' => isset($settings['components']['thumbnail_navigation']) ? $settings['components']['thumbnail_navigation'] : supersized_default_settings('thumbnail_navigation'),
    '#required' => TRUE,
  );
  $form['components']['progress_bar'] = array(
    '#type' => 'radios',
    '#title' => t('Progress bar'),
    '#description' => t('Progress bar that runs based on the the slide interval.'),
    '#options' => array(1 => t('Yes'), 0 => 'No'),
    '#default_value' => isset($settings['components']['progress_bar']) ? $settings['components']['progress_bar'] : supersized_default_settings('progress_bar'),
    '#required' => TRUE,
  );
  $form['components']['control_bar'] = array(
    '#type' => 'radios',
    '#title' => t('Control bar'),
    '#description' => t('Control bar that the slides.'),
    '#options' => array(1 => t('Yes'), 0 => 'No'),
    '#default_value' => isset($settings['components']['control_bar']) ? $settings['components']['control_bar'] : supersized_default_settings('control_bar'),
    '#required' => TRUE,
  );
  $form['components']['mouse_scrub'] = array(
    '#type' => 'hidden',
    '#value' => 0,
  );
  return $form;
}

/**
 * Implements hook_field_load().
 */
function supersized_field_load($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  image_field_load($entity_type, $entities, $field, $instances, $langcode, $items, $age);
}

/**
 * Implements hook_field_presave().
 */
function supersized_field_presave($entity_type, $entity, $field, $instance, $langcode, &$items) {
  image_field_presave($entity_type, $entity, $field, $instance, $langcode, $items);
}

/**
 * Implements hook_field_insert().
 */
function supersized_field_insert($entity_type, $entity, $field, $instance, $langcode, &$items) {
  image_field_insert($entity_type, $entity, $field, $instance, $langcode, $items);
}

/**
 * Implements hook_field_update().
 */
function supersized_field_update($entity_type, $entity, $field, $instance, $langcode, &$items) {
  image_field_update($entity_type, $entity, $field, $instance, $langcode, $items);
}

/**
 * Implements hook_field_delete().
 */
function supersized_field_delete($entity_type, $entity, $field, $instance, $langcode, &$items) {
  image_field_delete($entity_type, $entity, $field, $instance, $langcode, $items);
}

/**
 * Implements hook_field_delete_revision().
 */
function supersized_field_delete_revision($entity_type, $entity, $field, $instance, $langcode, &$items) {
  image_field_delete_revision($entity_type, $entity, $field, $instance, $langcode, $items);
}

/**
 * Implements hook_field_is_empty().
 */
function supersized_field_is_empty($item, $field) {
  return image_field_is_empty($item, $field);
}

/**
 * Implements hook_field_widget_info().
 */
function supersized_field_widget_info() {
  return array(
    'supersized_slide' => array(
      'label' => t('Slide'),
      'field types' => array('supersized'),
      'settings' => array(
        'progress_indicator' => 'throbber',
        'preview_image_style' => 'supersized-thumbnail',
      ),
      'behaviors' => array(
        'multiple values' => FIELD_BEHAVIOR_CUSTOM,
        'default value' => FIELD_BEHAVIOR_NONE,
      ),
    ),
  );
}

/**
 * Implements hook_field_widget_settings_form().
 */
function supersized_field_widget_settings_form($field, $instance) {
  $form = image_field_widget_settings_form($field, $instance);
  return $form;
}

/**
 * Implements hook_field_widget_form().
 */
function supersized_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  $elements = image_field_widget_form($form, $form_state, $field, $instance, $langcode, $items, $delta, $element);
  foreach (element_children($elements) as $delta) {
    $elements[$delta]['#process'][] = 'supersized_field_widget_process';
  }

  return $elements;
}

/**
 * An element #process callback for the image_image field type.
 *
 * Expands the image_image type to include the alt and title fields.
 */
function supersized_field_widget_process($element, &$form_state, $form) {
  $instance = field_widget_instance($element, $form_state);
  $settings = $instance['settings'];
  $widget_settings = $instance['widget']['settings'];
  $item = $element['#value'];
  $item['fid'] = $element['fid']['#value'];

  $element = image_field_widget_process($element, $form_state, $form);
  $element['description'] = array(
    '#title' => t('Desscription'),
    '#type' => 'textarea',
    '#default_value' => isset($item['description']) ? $item['description'] : '',
    '#description' => t('This will be display as the description of this slide.'),
    '#weight' => 0,
    '#access' => (bool) $item['fid'] && $settings['description_field'],
  );
  $element['link'] = array(
    '#type' => 'textfield',
    '#title' => t('Link'),
    '#default_value' => isset($item['link']) ? $item['link'] : '',
    '#description' => t('The link of the slide.'),
    '#maxlength' => 2048,
    '#weight' => 1,
    '#access' => (bool) $item['fid'] && $settings['link_field'],
  );

  return $element;
}

/**
 * Implements hook_field_formatter_info().
 */
function supersized_field_formatter_info() {
  $formatters = array(
    'supersized' => array(
      'label' => t('Supersized'),
      'field types' => array('supersized'),
      'settings' => array('image_style' => 'supersized'),
    ),
    'supersized_image' => array(
      'label' => t('Image'),
      'field types' => array('supersized'),
      'settings' => array('image_style' => ''),
    ),
  );

  return $formatters;
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function supersized_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];

  $image_styles = image_style_options(FALSE);
  $element['image_style'] = array(
    '#title' => t('Image style'),
    '#type' => 'select',
    '#default_value' => $settings['image_style'],
    '#empty_option' => t('None (original image)'),
    '#options' => $image_styles,
  );

  return $element;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function supersized_field_formatter_settings_summary($field, $instance, $view_mode) {
  $instance['display'][$view_mode]['settings']['image_link'] = 0;
  return image_field_formatter_settings_summary($field, $instance, $view_mode);
}

/**
 * Implements hook_field_formatter_view().
 */
function supersized_field_formatter_view($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $element = array();
  switch ($display['type']) {
    case 'supersized_image':
      foreach ($items as $delta => $item) {
        $element[$delta] = array(
          '#theme' => 'image_formatter',
          '#item' => $item,
          '#image_style' => $display['settings']['image_style'],
        );
      }
      break;
  }
  return $element;
}

/**
 * Implements hook_filefield_sources_widgets().
 */
function supersized_filefield_sources_widgets() {
  // Add any widgets that your module supports here.
  return array('supersized_slide');
}
