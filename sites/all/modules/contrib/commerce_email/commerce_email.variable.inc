<?php

/**
 * Variable definition
 */

/**
 * Implements hook_variable_group_info()
 */
function commerce_email_variable_group_info() {
  // Group for variable that have no group
  $groups['commerce_email'] = array(
    'title' => t('Commerce Email'),
    'description' => t("Emails used in Drupal Commerce."),
  );
  return $groups;
}

/**
 * Implements hook_variable_info().
 */
function commerce_email_variable_info($options) {
 
  $variable['commerce_email_order_[mail_part]'] = array(
    'title' => t('Order Email'),
    'type' => 'mail_html',
    'description' => t('Template for the order email sent out to the customer.'),
    'children' => array(
      'commerce_email_order_subject' => array(
        'default' => 'Order [commerce-order:order-number] at [site:name]',
      ),
      'commerce_email_order_body' => array(
        'default' => '<p>Thanks for your order [commerce-order:order-number] at [site:name].</p><p>[commerce-order:commerce-email-order-items]</p><p>If this is your first order with us, you will receive a separate e-mail with login instructions.</p><p>You can view your order history with us at any time by logging into our website at: <a href="[site:login-url]">[site:login-url]</a></p><p>You can view the status of your current order at: <a href="[site:url]user/[commerce-order:uid]/orders/[commerce-order:order-id]">[site:url]user/[commerce-order:uid]/orders/[commerce-order:order-id]</a></p><p>Please contact us if you have any questions about your order.</p>'
      ),
    ),
    'group' => 'commerce_email',
  );
  
  $variable['commerce_email_admin_order_[mail_part]'] = array(
    'title' => t('Admin Order Email'),
    'type' => 'mail_html',
    'description' => t('Template for the order email sent out to the administrator.'),
    'children' => array(
      'commerce_email_admin_order_subject' => array(
        'default' => 'Customer Order [commerce-order:order-number] from [site:name]',
      ),
      'commerce_email_admin_order_body' => array(
        'default' => '<p>A customer at [site:name] has just placed an order.</p><p>[commerce-order:commerce-email-order-items]</p><p>You can view the complete order at: <a href="[site:url]admin/commerce/orders/[commerce-order:order-id]">[site:url]admin/commerce/orders/[commerce-order:order-id]</a></p>'
      ),
    ),
    'group' => 'commerce_email',
  );
  
  $variable['commerce_email_account_[mail_part]'] = array(
    'title' => t('Account Email'),
    'type' => 'mail_html',
    'description' => t('Template for the account email sent out to the anonymous user.'),
    'children' => array(
      'commerce_email_account_subject' => array(
        'default' => 'Your account at [site:name]',
      ),
      'commerce_email_account_body' => array(
        'default' => '<p>An account was created for you after your order at [site:name].</p><p>You may now log in by clicking this link or copying and pasting it to your browser:</p><p><a href="[user:one-time-login-url]">[user:one-time-login-url]</a></p><p>This link can only be used once to log in and will lead you to a page where you can set your password.</p><p>After setting your password, you will be able to log in at <a href="[site:login-url]">[site:login-url]</a> in the future using:</p><p>username: [user:name]</p><p>password: Your password</p>'
      ),
    ),
    'group' => 'commerce_email',
  );

  return $variable;
}  
