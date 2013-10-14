<?php
/**
 * @file
 * CTools export UI for Premium levels.
 */

/**
 * Define this Export UI plugin.
 */
$plugin = array(
  'schema' => 'premium_levels',
  'access' => 'administer premium content levels',
  'menu' => array(
    'menu item' => 'premium_levels',
    'menu title' => 'Premium content levels',
    'menu description' => 'Administer Premium content levels.',
  ),
  'title singular' => t('level'),
  'title plural' => t('levels'),
  'title singular proper' => t('Premium content level'),
  'title plural proper' => t('Premium content levels'),
  'export' => array(
    'admin_title' => 'name',
  ),
  'form' => array(
    'settings' => 'premium_levels_ctools_export_ui_form',
  ),
  'handler' => array(
    'class' => 'levels_export_ui',
    'parent' => 'ctools_export_ui',
  ),
);

/**
 * Form for editing Premium content levels.
 */
function premium_levels_ctools_export_ui_form(&$form, &$form_state) {
  $level = $form_state['item'];

  // We require a title, since it's used in select boxes in forms, etc.
  $form['info']['name']['#required'] = TRUE;

  $form['protection_type'] = array(
    '#type' => 'radios',
    '#title' => t('Protection type'),
    '#default_value' => $level->protection_type,
    '#options' => array(
      'all' => t('Premium items are permanently restricted'),
      'archive' => t('Protect archives only: Items switch to premium status after a specified period'),
      'latest' => t('Protect latest content only: Items switch to non-premium status after a specified period'),
    ),
  );

  $form['protection_duration'] = array(
    '#type' => 'fieldset',
    '#title' => t('Protection duration'),
  );

  $form['protection_duration']['duration'] = array(
    '#type' => 'select',
    '#default_value' => $level->duration,
    '#options' => drupal_map_assoc(range(1, 14)),
  );

  $form['protection_duration']['duration_unit'] = array(
    '#type' => 'select',
    '#default_value' => $level->duration_unit,
    '#options' => array(
      'D' => t('Days'),
      'W' => t('Weeks'),
      'M' => t('Months'),
      'Y' => t('Years'),
    ),
  );

  $form['denied_message_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Access denied message'),
    '#tree' => FALSE,
  );

  $form['denied_message_fieldset']['denied_message'] = array(
    '#type' => 'text_format',
    '#default_value' => $level->denied_message,
    '#format' => isset($level->denied_message_format) ? $level->denied_message_format : NULL,
    '#cols' => 60,
    '#rows' => 6,
    '#description' => t('When a visitor doesn\'t have access to an item at this level they will see this message instead of its full text'),
  );

  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save premium level'),
  );

  $form['#after_build'] = array('premium_levels_ctools_export_ui_form_jcss');
}

/**
 * After build function used to add a bit of css to the ui form
 */
function premium_levels_ctools_export_ui_form_jcss(&$form, &$form_state) {
  // Add a bit of css to create a clearning admin interface.
  drupal_add_css(drupal_get_path('module', 'premium') . '/css/premium.admin.css');
  // Add some JS to control visibility of duration selection. Since the form
  // is build with ctools, we can't easily use ajax here.
  drupal_add_js(drupal_get_path('module', 'premium') . '/js/premium.admin.js');
  return $form;
}

