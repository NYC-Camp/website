<?php
/**
 * Contains the duration field handler.
 */

class timefield_handler_sort_timefield_duration extends views_handler_sort {
  function query() {
    $this->ensure_my_table();

    // Get the Field API field name from the definition.
    $field_name = $this->definition['field_name'];
    // Create our formula: value2 - value is the duration in seconds.
    $formula = $field_name . '_value2' . ' - ' . $field_name . '_value';
    // Add our expression to the query.

    $this->query->add_orderby(NULL, $formula, $this->options['order'], $this->table_alias . '_duration');
  }

}
