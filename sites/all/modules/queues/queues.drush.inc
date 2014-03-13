<?php

/**
 * Implements hook_drush_command().
 */
function queues_drush_command() {
  $items = array();

  $items['generate-queues'] = array(
    'description' => 'Create queues.',
    'arguments' => array(
      'number_queues' => 'Number of queues to generate.',
    ),
    'options' => array(
      'kill' => 'Delete all queues before generating new queues.',
      'types' => 'A comma delimited list of queue types to create.',
    ),
    'aliases' => array('genq'),
  );

  return $items;
}

/**
 * Command callback to generate queues.
 */
function drush_queues_generate_queues($num_queues = NULL) {
  if (!function_exists('drush_generate_include_devel')) {
    return drush_set_error('DEVEL_GENERATE_MISSING', t('Devel Generate is missing. Install the devel module to generate queues.'));
  }

  if (drush_generate_is_number($num_queues) == FALSE) {
    return drush_set_error('DEVEL_GENERATE_INVALID_INPUT', t('Invalid number of queues.'));
  }

  $types_option = drush_get_option('types', NULL);
  if (!empty($types_option)) {
    $types = drupal_map_assoc(explode(',', $types_option));
  }
  else {
    $info = entity_get_info('queues');
    $types = array_keys($info['bundles']);
  }

  drush_generate_include_devel();
  module_load_include('inc', 'queues', 'queues.devel_generate');
  queues_generate_queues($num_queues, drush_get_option('kill'), $types);
}

