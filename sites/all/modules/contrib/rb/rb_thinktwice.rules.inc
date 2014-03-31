<?php
/**
 * @file
 * Rules actions that you should think twice about. Plus some helper functions.
 */

/**
 * Implements hook_rules_action_info().
 */
function rb_thinktwice_rules_action_info() {
  // Add actions that depend on required modules only.
  $actions = array(
    'rb_thinktwice_action_enable_module' => array(
      'label' => t('Enable a module'),
      'access' => 'administer modules',
      'parameter' => array(
        'module' => array(
          'type' => 'text',
          'options list' => 'rb_thinktwice_action_module_list',
          'label' => t('Module'),
          'description' => t('Choose which module to enable. Automating module
            enabling may crash your site. Use at own risk.'),
          'restriction' => 'input',
        ),
      ),
      'help' => t('This is help text.'),
      'group' => t('Rules Bonus: Think twice'),
    ),
    'rb_thinktwice_action_disable_module' => array(
      'label' => t('Disable a module'),
      'access' => 'administer modules',
      'parameter' => array(
        'module' => array(
          'type' => 'text',
          'options list' => 'rb_thinktwice_action_module_list',
          'label' => t('Module'),
          'description' => t('Choose which module to disable. Automating module
            disabling may crash your site. Use at own risk.'),
          'restriction' => 'input',
        ),
      ),
      'group' => t('Rules Bonus: Think twice'),
    ),
    'rb_thinktwice_action_page_alter' => array(
      'label' => t('Modify $page'),
      'access' => 'administer site configuration',
      'parameter' => array(
        'property' => array(
          'label' => t('Property to modify'),
          'type' => 'text',
          'description' => t('Available values are Drupal render array key
            names, separated by a colon. For example: to modify
            <code>$page[\'footer\'][\'system_powered-by\'][\'#markup\']</code>,
            use <code>footer:system_powered-by:#markup</code>.'),
          'restriction' => 'input',
        ),
        'value' => array(
          'label' => t('Value to set'),
          'type' => 'text',
          'description' => t('Available values are any literal string, an
            integer, and true or false.'),
          'restriction' => 'input',
        ),
      ),
      'group' => t('Rules Bonus: Think twice'),
    ),
  );
  return $actions;
}

/**
 * Helper function to load a list of all available modules
 */
function rb_thinktwice_action_module_list() {
  // Get current list of modules.
  $files = system_rebuild_module_data();

  // Remove hidden modules from display list.
  $visible_files = $files;
  foreach ($visible_files as $filename => $file) {
    if (!empty($file->info['hidden'])) {
      unset($visible_files[$filename]);
    }
  }

  $modules = array();
  foreach ($visible_files as $module) {
    $modules[$module->name] =  $module->info['name'];
  }

  return $modules;
}

/**
 * The 'rb_thinktwice_action_enable_module' action.
 */
function rb_thinktwice_action_enable_module($module) {
  $module_list[] = $module;
  if (!module_exists($module)) {
    module_enable($module_list);
  }
}

/**
 * The 'rb_thinktwice_action_disable_module' action.
 */
function rb_thinktwice_action_disable_module($module) {
  $module_list[] = $module;
  module_disable($module_list);
}

/**
 * The 'rb_thinktwice_action_page_alter' action.
 */
function rb_thinktwice_action_page_alter($property, $value) {
  $alter = &drupal_static('rb_page_alter', array());

  // Type set.
  switch (trim(drupal_strtoupper($value))) {
    case 'TRUE':
      $value = (bool) TRUE;
    case 'FALSE':
      $value = (bool) FALSE;
      break;
    case ctype_digit($value):
      $value = (int) $value;
      break;
  }

  // To filter or not to filter, that is the question!
  $index['property'] = check_plain($property);
  $index['value'] = $value;

  // Populate $alter for rb_thinktwice_page_alter().
  $alter[] = $index;
}
