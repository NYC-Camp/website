<?php

/**
 * @file
 * Description and documentation of API functions included in rb_misc.
 */

/**
 * Adds node properties that should be reset when cloning nodes with rb_misc.
 *
 * This hook is useful for removing node properties set by contrib modules, that
 * should be cleaned up when cloning a node to avoid weird effects. For example,
 * 'nid' is removed this way (by rb_misc itself).
 *
 * @param <array> $properties_to_alter
 *   An array containing the node properties to remove. All properties should be
 *   represented by a value in $node->{property}. This property will be set to
 *   NULL, if it exists.
 */
function hook_rb_misc_node_clone_reset_properties_alter(&$properties_to_alter) {
  // Remove any time stamp for recent comments.
  $properties_to_alter += array('last_comment_timestamp');
}
