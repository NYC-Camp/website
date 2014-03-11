<?php

/**
 * @file
 * Definition of queues_views_handler_field_operations.
 */

/**
 * A handler to provide proper displays for the representative image.
 *
 * @ingroup views_field_handlers
 */
class queues_views_handler_publish_state extends views_handler_field {

  function query() {
    // Do nothing -- to override the parent query.
  }

  function get_value($values, $field = NULL) {
    if (isset($values->{$field})) {
      return $values->{$field};
    }
  }

  function render($values) {
    $output = '';
    $status = $this->get_value($values, 'queues_status');
    if ($status == 1) {
	  $output = t('Published');
    }
    else {
	  $output = t('Unpublished');
    }

    return $output;
  }
}
