<?php 
/**
 * @file
 * Variable Email module hook implementations
 */

/**
 * Implements hook_variable_type_info().
 */
function variable_email_variable_type_info() {
  $type['mail_html'] = array(
    'title' => t('Mail HTML'),
    'multiple' => array('subject' => t('Subject'), 'body' => t('Body')),
    'build callback' => 'variable_email_build_mail_html',
    'localize' => TRUE,
    'type' => 'multiple',
  );
  return $type;
}

/**
 * Build multiple mail variable
 */
function variable_email_build_mail_html($variable, $options = array()) {
  $name = str_replace('[mail_part]', '', $variable['name']);
  // For mail text, children have different types
  $variable['children'][$name . 'subject']['type'] = 'string';
  $variable['children'][$name . 'body']['type'] = 'text_format';
  $variable = variable_build_multiple($variable, $options);
  return $variable;
}

/**
 * Format mail variable
 */
function variable_email_format_mail_html($variable, $options = array()) {
  return 'Mail HTML'; //check_plain($variable['value']['subject']);
}

