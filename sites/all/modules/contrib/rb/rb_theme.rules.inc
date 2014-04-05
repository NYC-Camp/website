<?php
/**
 * @file
 * Rules actions to modify the theme. Plus some helper functions.
 */

/**
 * Implements hook_rules_action_info().
 */
function rb_theme_rules_action_info() {
  // Add actions that depend on required modules only.
  $actions = array(
    'rb_theme_action_set_head_title' => array(
      'label' => t('Set head title'),
      'parameter' => array(
        'head_title' => array(
          'type' => 'text',
          'label' => t('Title to set'),
          'description' => t('Choose which head title should be set on this action. This is the title element in the HTML document'),
        ),
      ),
      'group' => t('Rules Bonus: Theme'),
    ),
    'rb_theme_action_set_body_class' => array(
      'label' => t('Set body classes'),
      'parameter' => array(
        'classes' => array(
          'type' => 'text',
          'label' => t('Body classes to set'),
          'description' => t('Classes to be added to body. Write each class on a new line. Each class will be sanitized to be only lowercase with dashes.'),
        ),
      ),
      'group' => t('Rules Bonus: Theme'),
    ),
  );

  return $actions;
}

/**
 * The 'rb_misc_action_set_head_title' action.
 */
function rb_theme_action_set_head_title($head_title) {
  // Store the value in a static variable that we can use in our
  // implementation of hook_preprocess_html()
  rb_theme_static('head_title', $head_title);
}

/**
 * The 'rb_misc_action_set_body_class' action.
 */
function rb_theme_action_set_body_class($classes) {
  // Store the value in a static variable that we can use in our
  // implementation of hook_preprocess_html()
  rb_theme_static('classes_array', $classes);
}
