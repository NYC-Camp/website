<?php
/**
 * @file
 * Field handler for Weight module.
 */

class weight_handler_filter_sticky extends views_handler_filter_boolean_operator {
  function query() {
    $this->ensure_my_table();

    $where = "$this->table_alias.$this->real_field ";

    if (empty($this->value)) {
      $where .= '<= 0';
    }
    else {
      $where .= ' > 0';
    }
    $this->query->add_where($this->options['group'], $where);
  }
}
