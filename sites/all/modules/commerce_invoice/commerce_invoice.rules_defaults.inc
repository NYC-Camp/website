<?php

/**
 * @file
 * Default rule configurations for Commerce Invoice.
 */

/**
 * Implements hook_default_rules_configuration().
 */
function commerce_invoice_default_rules_configuration() {

  $rules = array();

  // Add a reaction rule to generate an invoice number
  // when an order is completed
  $rule = rules_reaction_rule();

  $rule->label = t('Generate invoice when order is completed');
  $rule->active = TRUE;

  $rule
    ->event('commerce_order_update')
    ->condition('data_is', array(
      'data:select' => 'commerce-order:status',
      'op' => '==',
      'value' => 'completed'
    ))
    ->condition(rules_condition('commerce_invoice_exists', array(
      'commerce_order:select' => 'commerce-order'
    ))->negate())
    ->action('commerce_invoice_generate', array(
      'commerce_order:select' => 'commerce-order',
    ));

  $rules['commerce_invoice_generate_when_completed'] = $rule;
  
  // Add a reaction rule to send invoice e-mail when a new commerce invoice is saved.
  $rule = rules_reaction_rule();

  $rule->label = t('Send an invoice notification e-mail');
  $rule->active = TRUE;

  $rule
    ->event('commerce_invoice_insert')
    ->action('mail', array(
      'to' => '[commerce-invoice:order:mail]',
      'subject' => t('Invoice [commerce-invoice:invoice-number] at [site:name]'),
      'message' => t("Your order [commerce-invoice:order:order-number] is now complete.\n\nYou will be able to find the invoice for your order at:\n\n[site:url]user/[commerce-invoice:uid]/invoices/[commerce-invoice:invoice-id]\n\nPlease contact us if you have any questions about your invoice."),
      'from' => '',
    ));

  $rules['commerce_invoice_email'] = $rule;

  return $rules;
}
