<?php

/**
 * Filter by order type
 */
class commerce_invoice_handler_filter_invoice_type extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('Type');
      $this->value_options = commerce_invoice_type_get_name();
    }
  }
}
