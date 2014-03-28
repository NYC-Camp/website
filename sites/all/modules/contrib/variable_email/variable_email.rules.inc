<?php

/**
 * @file
 * Defines rules for variable email functionality.
 */

 /**
 * Implements hook_rules_action_info().
 */
function variable_email_rules_action_info() {
  $actions = array();

  $actions['variable_email_mail'] = array(
    'label' => t('Send mail with Variable'),
    'parameter' => array(
      'to' => array(
        'type' => 'text',
        'label' => t('To'),
        'description' => t('The e-mail address or addresses where the message will be sent to. The formatting of this string must comply with RFC 2822.'),
      ),
      'variable' => array(
        'type' => 'text',
        'label' => t('Variable'),
        'options list' => 'variable_email_variables_list',
        'description' => t('Select the variable which should be used as a template.'),
      ),
      'language' => array(
        'type' => 'token',
        'label' => t('Language'),
        'description' => t('Select the language of the variable. You will need to have the <em>Variable translation</em> module enabled for this to work'),
        'options list' => 'variable_email_rules_language_list',
        'default value' => 'default',
      ),
      'from' => array(
        'type' => 'text',
        'label' => t('From'),
        'description' => t("The mail's from address. Leave it empty to use the site-wide configured address."),
        'optional' => TRUE,
      ),
    ),
    'group' => t('Variable Email'),
    'callbacks' => array(
      'execute' => 'variable_email_action_mail',
    ),
  );
  
  return $actions;
}

function variable_email_rules_language_list() {
  $list = language_list();
  $out = array();
  $out['default'] = t('Site Default Language');
  foreach ($list as $key => $language) {
    $out[$key] = $language->native;
  }
  return $out;
}

/**
 * Action Implementation: Send mail.
 */
function variable_email_action_mail($to, $variable, $language = 'default', $from = NULL, $settings, RulesState $state, RulesPlugin $element) {
  $subject_variable_name = str_replace('[mail_part]', 'subject', $variable);
  $body_variable_name = str_replace('[mail_part]', 'body', $variable);
  if (module_exists('i18n_variable')) {
    if ($language == 'default') {
      $language = language_default();
      $language = $language->language;
    }
    $subject = i18n_variable_get($subject_variable_name, $language, variable_get_value($subject_variable_name));
    $message = i18n_variable_get($body_variable_name, $language, variable_get_value($body_variable_name));
  }
  else {
    $subject = variable_get_value($subject_variable_name);
    $message = variable_get_value($body_variable_name);
  }
  
  // If it's an HTML Mail, make sure we are sending the message content and not an array
  if (is_array($message)) {
    if ($message['format'] == 'php_code') {
      // Execute php
      module_load_include('inc', 'rules', 'modules/php.eval');
      $message = rules_php_eval($message['value'], rules_unwrap_data($state->variables));
    }
    else {
      $message = $message['value'];
    }
  }
  
  $to = str_replace(array("\r", "\n"), '', $to);
  $from = !empty($from) ? str_replace(array("\r", "\n"), '', $from) : NULL;
  $params = array(
    'subject' => _variable_email_evaluate_token($subject, array(), $state),
    'message' => _variable_email_evaluate_token($message, array(), $state),
  );
  // Set a unique key for this mail using variable name
  $key = str_replace('_[mail_part]', '', $variable);

  $message = drupal_mail('variable_email', $key, $to, language_default(), $params, $from);
  if ($message['result']) {
    watchdog('variable_email', 'Successfully sent email to %recipient', array('%recipient' => $to));
  }
}

/**
 * Function used for token replacements
 * TODO: find a better way to do this
 */
function _variable_email_evaluate_token($text, $options, RulesState $state) {
  module_load_include('inc', 'rules', 'modules/system.eval');
  $var_info = $state->varInfo();
  $options += array('sanitize' => FALSE);

  $replacements = array();
  $data = array();
  // We also support replacing tokens in a list of textual values.
  $whole_text = is_array($text) ? implode('', $text) : $text;
  foreach (token_scan($whole_text) as $var_name => $tokens) {
    $var_name = str_replace('-', '_', $var_name);
    if (isset($var_info[$var_name]) && ($token_type = _rules_system_token_map_type($var_info[$var_name]['type']))) {
      // We have to key $data with the type token uses for the variable.
      $data = rules_unwrap_data(array($token_type => $state->get($var_name)), array($token_type => $var_info[$var_name]));
      $replacements += token_generate($token_type, $tokens, $data, $options);
      // TODO: this code needs to be removed at some point
      // See http://drupal.org/node/1289898
      // Add restricted user tokens (one-time-login-url and cancel-url).
      // For now, it is left commented out
      /*if ($token_type == 'user') {
        user_mail_tokens($replacements, $data, $options);
      }*/
    }
    else {
      $replacements += token_generate($var_name, $tokens, array(), $options);
    }
  }

  // Optionally clean the list of replacement values.
  if (!empty($options['callback']) && function_exists($options['callback'])) {
    $function = $options['callback'];
    $function($replacements, $data, $options);
  }

  // Actually apply the replacements.
  $tokens = array_keys($replacements);
  $values = array_values($replacements);
  if (is_array($text)) {
    foreach ($text as $i => $text_item) {
      $text[$i] = str_replace($tokens, $values, $text_item);
    }
    return $text;
  }
  return str_replace($tokens, $values, $text);
}
