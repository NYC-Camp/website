<?php

/**
 * @file
 * Default rule configurations for Commerce Invoice Email.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_invoice_email_default_rules_configuration() {
  
  $rules = array();
  
  // Add a reaction rule to send invoice e-mail when invoice is generated.
  $rule = rules_reaction_rule();

  $rule->label = t('Send an invoice notification e-mail (HTML)');
  $rule->active = TRUE;
  
  $rule
    ->event('commerce_invoice_insert')
    ->action('variable_email_mail', array(
      'to' => '[commerce-invoice:order:mail]',
      'variable' => 'commerce_invoice_email_invoice_[mail_part]', 
    ));
    
  $rule->weight = 9;

  $rules['commerce_invoice_email_invoice_html'] = $rule;
  
  // Add a reaction rule to send invoice e-mail to administrator when invoice is generated
  $rule = rules_reaction_rule();

  $rule->label = t('Send an invoice notification e-mail to administrator (HTML)');
  $rule->active = TRUE;
  
  $rule
    ->event('commerce_invoice_insert')
    ->action('variable_email_mail', array(
      'to:select' => 'site:mail',
      'variable' => 'commerce_invoice_email_admin_invoice_[mail_part]', 
    ));
  
  $rules['commerce_invoice_email_admin_invoice_html'] = $rule;

  return $rules;
}
