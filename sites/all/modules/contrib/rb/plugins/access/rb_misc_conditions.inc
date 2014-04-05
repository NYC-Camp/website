<?php
/**
 * @file
 * Plugin to create access plugins from Rules condition components.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Rules condition component'),
  'description' => t('Use one of your configured Rules condition components'),
  'callback' => 'rb_misc_conditions_evaluate',
  'default' => array('type' => array()),
  'settings form' => 'rb_misc_conditions_form',
  'get child' => 'rb_misc_conditions_get_child',
  'get children' => 'rb_misc_conditions_get_children',
  'summary' => 'rb_misc_conditions_summary',
);

/**
 * Helper function building required CTools contexts for each Rules condition.
 *
 * @param $component
 *   The condition component. (These are actually entities!)
 *
 * @return ctools_context_required
 *   An array of ctools_context_required objects, as used by CTools access
 *   plugins.
 */
function rb_misc_conditions_build_required_contexts($component) {
  // If there was an entry in the returned components, get the first (and
  // hopefully only) one.
  $parameters = $component->parameterInfo();

  // Build an array on the form used by CTools to declare required contexts.
  $required_contexts = array();
  foreach ($parameters as $parameter) {
    $required_contexts[] = new ctools_context_required(check_plain($parameter['label']), $parameter['type']);
  }

  return $required_contexts;
}

/**
 * Configuration form for selecting condition component and its input data.
 */
function rb_misc_conditions_form($form, &$form_state, $conf) {
  // Fetch the name of the rules component. We will need this when evaluating,
  // to know which condition component to load.
  $plugin_name = explode(':', $form_state['plugin']['name']);

  // Set a non-visible value in the form. Then carry on.
  $form['settings']['component_name'] = array(
    '#type' => 'value',
    '#value' => $plugin_name[1],
  );

  return $form;
}

/**
 * Describe a single plugin.
 *
 * This function is stolen straight off from entity_bundle.inc.
 */
function rb_misc_conditions_get_child($plugin, $parent, $child) {
  // Get the component from cache to speed up evaluation.
  $component = rules_get_cache('comp_' . $child);
  if ($component) {
    return rb_misc_condition_get_plugin_info($parent, $child, $component);
  }
}

/**
 * Describe all child plugins this pluing provides.
 *
 * This function collects all condition components created in Rules, and exposes
 * them as CTools access plugins.
 */
function rb_misc_conditions_get_children($plugin, $parent) {
  // Get all Rules condition components.
  $components = rules_get_components(FALSE, 'condition');

  // Build information about each component, in a way interpretable by CTools.
  $plugins = array();
  foreach ($components as $name => $component) {
    $plugins['rb_misc_conditions:' . $name] = rb_misc_condition_get_plugin_info($parent, $name, $component);
  }
  return $plugins;
}

/**
* Gets plugin information for a single component.
*/
function rb_misc_condition_get_plugin_info($parent, $name, $component) {
  return array(
    'title' => t("Rules: @label", array('@label' => $component->label())),
    'name' => $parent . ':' . $name,
    'callback' => 'rb_misc_conditions_evaluate',
    'settings form' => 'rb_misc_conditions_form',
    'summary' => 'rb_misc_conditions_summary',
    'keyword' => $component->name,
    'required context' => rb_misc_conditions_build_required_contexts($component),
  );
}

/**
 * Check for access.
 */
function rb_misc_conditions_evaluate($conf, $context) {
  // For evaluating the component make use of the condition rules provides
  // for it, as it loads the component from cache.
  $condition = rules_condition('component_' . $conf['component_name']);

  // In case no component can be loaded, return FALSE to signal that somethis
  // is wrong.
  if (!$condition) {
    return FALSE;
  }

  // Get the name of the parameters required by the component.
  $parameters = $condition->parameterInfo();

  // Get the argument value for each parameter from the context object. (It
  // already contains the parameter names expected by Rules.)
  $arguments = array();
  foreach ($parameters as $name => $parameter) {
    $arguments[$name] = array_shift($context)->data;
  }

  // Evaluate the condition component and return the result.
  return $condition->executeByArgs($arguments);
}

/**
 * Provide a summary description.
 */
function rb_misc_conditions_summary($conf, $context) {
  $name = $conf['component_name'];
  $component = rules_config_load($name);
  if (module_exists('rules_admin')) {
    return t('Rules condition component (%type): <a href="!edit-url" target="_blank">%label</a>', array('%type' => drupal_strtoupper($component->plugin()), '!edit-url' => url(RulesPluginUI::path($component->name)), '%label' => $component->label()));
  }
  return t('Rules condition component %type: %label', array('%type' => $component->plugin(), '%label' => $component->label()));
}
