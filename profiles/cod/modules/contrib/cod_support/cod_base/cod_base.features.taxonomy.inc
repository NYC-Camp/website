<?php
/**
 * @file
 * cod_base.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function cod_base_taxonomy_default_vocabularies() {
  return array(
    'interests' => array(
      'name' => 'Interests',
      'machine_name' => 'interests',
      'description' => 'User Profile Interests',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'jobs' => array(
      'name' => 'Job Titles',
      'machine_name' => 'jobs',
      'description' => NULL,
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
