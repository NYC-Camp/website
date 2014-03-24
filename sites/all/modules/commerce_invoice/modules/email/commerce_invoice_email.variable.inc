<?php

/**
 * Variable definition
 */

/**
 * Implements hook_variable_info().
 */
function commerce_invoice_email_variable_info($options) {
 
  $variable['commerce_invoice_email_invoice_[mail_part]'] = array(
    'title' => t('Invoice Email'),
    'type' => 'mail_html',
    'description' => t('Template for the invoice email sent out to the customer.'),
    'children' => array(
      'commerce_invoice_email_invoice_subject' => array(
        'default' => 'Invoice [commerce-invoice:invoice-number] at [site:name]',
      ),
      'commerce_invoice_email_invoice_body' => array(
        'default' => '<p>Please find below the invoice related to your order [commerce-invoice:order:order-number] at [site:name].</p><p><strong>Invoice number</strong>: [commerce-invoice:invoice-number]</p><p>[commerce-invoice:order:commerce-email-order-items]</p><p>You can view your invoices at any time by logging into our website at: [site:login-url]</p><p>You can find the current invoice at: [site:url]user/[commerce-invoice:uid]/invoices/[commerce-invoice:invoice-id]</p><p>Please contact us if you have any questions about your invoice.</p>'
      ),
    ),
    'group' => 'commerce_email',
  );
  
  $variable['commerce_invoice_email_admin_invoice_[mail_part]'] = array(
    'title' => t('Admin Invoice Email'),
    'type' => 'mail_html',
    'description' => t('Template for the invoice email sent out to the administrator.'),
    'children' => array(
      'commerce_invoice_email_admin_invoice_subject' => array(
        'default' => 'Customer Invoice [commerce-invoice:invoice-number] from [site:name]',
      ),
      'commerce_invoice_email_admin_invoice_body' => array(
        'default' => '<p>A customer at [site:name] has just received an invoice.</p><p><strong>Invoice number</strong>: [commerce-invoice:invoice-number]</p><p><strong>Customer</strong>: [commerce-invoice:order:commerce-customer-billing:commerce_customer_address]</p><p>[commerce-invoice:order:commerce-email-order-items]</p><p>You can view the complete invoice at:&nbsp;[site:url]admin/commerce/orders/[commerce-invoice:order:order-id]/invoice</p>'
      ),
    ),
    'group' => 'commerce_email',
  );

  return $variable;
}  
