<?php

/**
 * @file
 *
 * Helper functions for Queues.
 *
 * Separating them out for simpler unit test.
 */

/**
 * Helper function for getting the name of a entityreference field.
 *
 * @param string $entity_type
 *   A Drupal entity type.
 *
 * @return string
 *   The name of the entityreference field for the given entity type.
 */
function _queues_get_target_field_name($entity_type) {
  // Avoid drupal_strlen on purpose.
  if (strlen($entity_type) <= 23) {
    return 'field_qt_' . $entity_type;
  }
  else {
    // Field names cannot be longer than 32 characters, so have to use a hashing
    // trick in order to get a human-readable field name for long entity types.
    return 'field_qt_' . substr($entity_type, 0, 15) . '_' . substr(md5($entity_type), 0, 7);
  }
}
