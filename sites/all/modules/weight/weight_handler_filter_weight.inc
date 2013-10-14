<?php

/**
 * @file
 * Filter handler for Weight module.
 */

class weight_handler_filter_weight extends views_handler_filter_numeric {
  function op_between($field) {
    // convert min value 
    $this->value['min'] = -($this->value['min'] + 100);
    
    // convert max value
    $this->value['max'] = -($this->value['max'] + 100);
    
    // swap min and max
    $tmp = $this->value['max'];
    $this->value['max'] = $this->value['min'];
    $this->value['min'] = $tmp;
    unset($tmp);
    
    if ($this->operator == 'between') {
      $this->query->add_where($this->options['group'], $field, array($this->value['min'], $this->value['max']), 'BETWEEN');
    }
    else {
      $this->query->add_where($this->options['group'], db_or()->condition($field, $this->value['min'], '<=')->condition($field, $this->value['max'], '>='));
    }
  }
  
  function op_simple($field) {
    // convert value
    $this->value['value'] = -($this->value['value'] + 100);
    
    // reverse the operator because we use the sticky field backwards
    if (strpos($this->operator, '<') !== FALSE) {
      $this->operator = str_replace('<', '>', $this->operator);
    }
    elseif (strpos($this->operator, '>') !== FALSE) {
      $this->operator = str_replace('>', '<', $this->operator);
    }
    
    $this->query->add_where($this->options['group'], $field, $this->value['value'], $this->operator);
  }
}
