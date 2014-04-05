<?php
/**
 * @file
 * Contains the plugin for validating a Views argument with rule sets.
 */

/**
 * Use a Rules component to validate a contextual filter value ('argument').
 *
 * This component allows using a Rules component for validation of Views
 * contextual filter values. The component must accept a text string as input
 * (parameter) – this is the contextual filter value from Views. (This value can
 * be altered by the component, if desired.) The component must return a string
 * and a boolean as output (provided). The string is the (altered) argument
 * value, and the boolean is the TRUE/FALSE outcome of the validation.
 *
 * @ingroup views_argument_validate_plugins
 */
class rb_views_plugin_argument_validate_rules_component extends views_plugin_argument_validate {
  function option_definition() {
    $options = parent::option_definition();
    $options['component'] = array('default' => '');

    return $options;
  }

  function options_form(&$form, &$form_state) {

    // Get all the relevant plugin instances.
    $components = (rules_get_components(TRUE, NULL, array('plugin' => 'views argument validator')));

    // Build the options form for the validator.
    $form['component'] = array(
      '#type' => 'select',
      '#title' => t('Choose validator component'),
      '#options' => $components,
      '#default_value' => $this->options['component'],
      '#description' => t('New argument validators can be set up using the Rules component interface.'),
    );
  }

  function validate_argument($argument) {
    // Run the rule set with the argument value as input.
    $result = rules_invoke_component($this->options['component'], &$this->argument->argument, $this->view->args);

    // Update the argument with the output from the rule set.
    $this->argument->argument = $result[0];
    $this->view->args = $result[1];
    // Return the validation boolean from the rule set.
    return $result[2];
  }
}
