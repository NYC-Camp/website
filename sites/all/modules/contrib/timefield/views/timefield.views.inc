<?php


/**
 * @file
 *   Default views hooks.
 */

/**
 * Implements hook_views_plugins().
 */
function timefield_views_plugins() {
  $plugins = array(
    'module' => 'timefield',
    'style' => array(
      'timefield_minical' => array(
        'title' => t('Timefield MiniCal'),
        'help' => t('Displays a Mini Summary of Timefield.'),
        'handler' => 'TimefieldPluginStyleMinical',
        'theme' => 'timefield_minical',
        'theme path' => drupal_get_path('module', 'timefield') . '/views',
        'path' => drupal_get_path('module', 'timefield') . '/views',
        'uses fields' => TRUE,
        'uses row plugin' => FALSE,
        'uses options' => TRUE,
        'uses grouping' => FALSE,
        'type' => 'normal',
        'even empty' => TRUE,
      ),
    ),
  );

  return $plugins;
}

/**
 * Implements hook_field_views_data_views_data_alter().
 *
 * Add extra fake field data for duration to the Views data for each
 * timefield field where there are 2 value properties.
 *
 * Convert Day switches to booleans.
 */
function timefield_field_views_data_views_data_alter(&$data, $field) {

  $field_name = $field['field_name'];
  $data_key = 'field_data_' . $field_name;
  $additional_fields = $data[$data_key][$field_name . '_value']['argument']['additional fields'];

  // Add special handler to base field
  $data[$data_key][$field_name]['field']['handler'] = 'TimefieldHanlderFieldTimefield';

  // If the timefield has a value2 column, add duration option.
  if (isset($data[$data_key][$field_name . '_value2'])) {
    $data[$data_key]['timefield_duration'] = array(
      'group'       => $data[$data_key][$field_name]['group'],
      'title'       => $data[$data_key][$field_name]['title'] . ': ' . t('Duration'),
      'title short' => $data[$data_key][$field_name]['title short'],
      'help'        => $data[$data_key][$field_name]['help'],
    );
    $data[$data_key]['timefield_duration']['field'] = array(
      'table' => $data[$data_key][$field_name]['field']['table'],
      'field_name' => $data[$data_key][$field_name]['field']['field_name'],
      'handler' => 'timefield_handler_field_timefield_duration',
    );
    $data[$data_key]['timefield_duration']['sort'] = array(
      'table' => $data[$data_key][$field_name]['field']['table'],
      'field_name' => $data[$data_key][$field_name]['field']['field_name'],
      'handler' => 'timefield_handler_sort_timefield_duration',
    );
    $data[$data_key]['timefield_duration']['filter'] = array(
      'table' => $data[$data_key][$field_name]['field']['table'],
      'field_name' => $data[$data_key][$field_name]['field']['field_name'],
      'handler' => 'timefield_handler_filter_timefield_duration',
    );
  }

  // If the timefield has a day property make filter and argument handlers for
  // booleans.
  if (isset($data[$data_key][$field_name . '_mon'])) {
    foreach(_timefield_weekly_summary_days() as $day => $day_name) {
      $title = t('Occurs on !day', array('!day' => $day_name));
      $data[$data_key][$field_name . '_' . $day]['title'] = $title;
      $data[$data_key][$field_name . '_' . $day]['filter'] = array(
        'handler' => 'views_handler_filter_boolean_operator',
        'label' => $title,
        'type' => 'yes-no',
      );
      // Sorting does not make sense in this context
      unset($data[$data_key][$field_name . '_' . $day]['sort']);
    }
  }
}
