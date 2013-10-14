<?php
/**
 * @file
 * Plugin to provide access control based upon premium status and access.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Premium access'),
  'description' => t('Control access based on Premium level access.'),
  'callback' => 'premium_access_ctools_access_check',
  'default' => array('type' => 'view'),
  'settings form' => 'premium_access_ctools_access_settings',
  'settings form submit' => 'premium_access_ctools_access_settings_submit',
  'summary' => 'premium_access_ctools_access_summary',
  'required context' => array(
    new ctools_context_required(t('User'), 'user'),
    new ctools_context_required(t('Node'), 'node'),
  ),
);

/**
 * Settings form for the 'by node_access' access plugin
 */
function premium_access_ctools_access_settings(&$form, &$form_state, $conf) {
  $form['placeholder'] = array(
    '#value' => t('No configurable settings for Premium access yet.'),
  );
}

/**
 * Check for access.
 */
function premium_access_ctools_access_check($conf, $context) {
  // As far as I know there should always be a context at this point, but this
  // is safe.
  list($user_context, $node_context) = $context;
  if (empty($node_context) || empty($node_context->data) || empty($node_context->data->type) ||
      empty($user_context) || empty($user_context->data)) {
    return FALSE;
  }

  return premium_user_content_access($node_context->data, $user_context->data);
}

/**
 * Provide a summary description based upon the checked node_accesss.
 */
function premium_access_ctools_access_summary($conf, $context) {
  list($user_context, $node_context) = $context;

  return t('@user has premium access to @node.', array(
    '@user' => $user_context->identifier,
    '@node' => $node_context->identifier,
  ));
}
