<?php
/**
 * @file
 * cod_session.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function cod_session_taxonomy_default_vocabularies() {
  return array(
    'session_tracks' => array(
      'name' => 'Session Tracks',
      'machine_name' => 'session_tracks',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
