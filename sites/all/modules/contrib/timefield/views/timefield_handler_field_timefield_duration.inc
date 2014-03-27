<?php
/**
 * Contains the duration field handler.
 */

class timefield_handler_field_timefield_duration extends views_handler_field {
  function query() {
    $this->ensure_my_table();

    // Get the Field API field name from the definition.
    $field_name = $this->definition['field_name'];
    // Create our formula: value2 - value is the duration in seconds.
    $formula = $field_name . '_value2' . ' - ' . $field_name . '_value';
    // Add our expression to the query.
    $this->name_alias = $this->query->add_field(NULL, $formula, $this->table_alias . '_duration');
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['duration_format'] = array('default' => 'hours');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // @TODO: when we improve duration formatting options, utilize a helper
    // function to return a form for settings these values here and in the main
    // display formatter settings in the module.
    $form['duration_format'] = array(
      '#title' => t('Time Duration Format'),
      '#type' => 'select',
      '#options' => _timefield_duration_options(),
      '#default_value' => $this->options['duration_format'],
      '#required' => TRUE,
    );

    return $form;
  }


  function render($values) {
    $value = $values->{$this->name_alias};

    if (!empty($value) && !empty($this->options['duration_format'])) {
      $value = timefield_integer_to_duration($value, $this->options['duration_format']);
    }

    return $value;
  }
}
