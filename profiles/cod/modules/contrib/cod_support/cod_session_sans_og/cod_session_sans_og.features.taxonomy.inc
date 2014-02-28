<?php
/**
 * @file
 * cod_session_sans_og.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function cod_session_sans_og_taxonomy_default_vocabularies() {
  return array(
    'organizing' => array(
      'name' => 'Organizing',
      'machine_name' => 'organizing',
      'description' => 'Taxonomy for keeping organizer info, um, organized. ',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'session_tracks' => array(
      'name' => 'Session Tracks',
      'machine_name' => 'session_tracks',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'topics' => array(
      'name' => 'Topics',
      'machine_name' => 'topics',
      'description' => 'Get off the island - tech topics',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
