<?php
/**
 * Contains the duration filter handler.
 */

class timefield_handler_filter_timefield_duration extends views_handler_filter_numeric {

  var $duration_unit = 'seconds';

  function init(&$view, &$options) {
    parent::init($view, $options);
    $this->duration_unit = $this->options['duration_unit'];
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['duration_unit'] = array('default' => 'seconds');
    return $options;
  }
  /*
   * Add duration selection to the options form.
   */
  function options_form(&$form, &$form_state) {
     parent::options_form($form, $form_state);

     $opts = _timefield_duration_options();
     array_pop($opts);

     $form['duration_unit'] = array(
      '#title' => t('Unit of Filter Value'),
      '#type' => 'select',
      '#options' => $opts,
      '#default_value' => $this->duration_unit,
      '#description' => t('This will be the unit of filtering everywhere it is used on this filter.'),
      '#weight' => -100,
    );

  }

  /*
   * Override operators to exclude regexes
   */
  function operators() {
    $operators = parent::operators();
    unset($operators['regular_expression']);
    return $operators;
  }

  /*
   * This is where the magic happens.
   */
  function query() {
    $this->ensure_my_table();

    // Get the Field API field name from the definition.
    $field_name = $this->definition['field_name'];
    $formula = $field_name . '_value2' . ' - ' . $field_name . '_value';

    switch ($this->operator) {
      case 'between':
        $value_min = empty($this->value['min']) ? 0 : $this->value['min'];
        $value_max = empty($this->value['max']) ? 0 : $this->value['max'];
        $op = $formula . ' BETWEEN :value_min AND :value_max';
        $this->query->add_where_expression($this->options['group'], $op, array(':value_min' => $this->filterSelectionToSeconds($value_min), ':value_max' => $this->filterSelectionToSeconds($value_max)));
        break;
      case 'not between':
        $value_min = empty($this->value['min']) ? 0 : $this->value['min'];
        $value_max = empty($this->value['max']) ? 0 : $this->value['max'];
        $op = $formula . ' BETWEEN :value_min AND :value_max';
        $this->query->add_where_expression($this->options['group'], $formula . ' <= :value_min', array(':value_min' => $this->filterSelectionToSeconds($value_min)));
        $this->query->add_where_expression($this->options['group'], $formula . ' >= :value_max', array(':value_max' => $this->filterSelectionToSeconds($value_max)));
        break;
      default:
        $value = empty($this->value['value']) ? 0 : $this->value['value'];
        $op = $formula . ' ' . $this->operator . ' :value';
        $this->query->add_where_expression($this->options['group'], $op, array(':value' => $this->filterSelectionToSeconds($value)));
        break;
    }
  }

   function filterSelectionToSeconds($value) {

     switch($this->duration_unit) {
       case 'seconds':
         return $value;
         break;
       case 'minutes':
         return $value * 60;
         break;
       case 'hours':
         return $value * 60 * 60;
         break;
     }
   }

   function admin_summary() {
    if (!empty($this->options['exposed'])) {
      return t('exposed');
    }

    $options = $this->operator_options('short');
    $output = check_plain($options[$this->operator]);
    if (in_array($this->operator, $this->operator_values(2))) {
      $output .= ' ' . t('@min and @max', array('@min' => $this->value['min'], '@max' => $this->value['max']));
    }
    elseif (in_array($this->operator, $this->operator_values(1))) {
      $output .= ' ' . check_plain($this->value['value']);
    }

    return $output . ' ' . ucfirst($this->duration_unit);
  }

}
