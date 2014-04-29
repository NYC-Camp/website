<?php

/**
 * @file
 * Defines additional tokens for order email.
 */

/**
 * Implements hook_token_info_alter().
 */
function commerce_email_token_info_alter(&$data) {
  $data['tokens']['commerce-order']['commerce-email-order-items'] = array(
    'name' => t('Order Items'),
    'description' => t('A table containing order items.'),
  );
}

/**
 * Implements hook_tokens().
 */
function commerce_email_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $url_options = array('absolute' => TRUE);

  if (isset($options['language'])) {
    $url_options['language'] = $options['language'];
    $language_code = $options['language']->language;
  }
  else {
    $language_code = NULL;
  }

  $sanitize = !empty($options['sanitize']);

  $replacements = array();

  if ($type == 'commerce-order' && !empty($data['commerce-order'])) {
    $order = $data['commerce-order'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'commerce-email-order-items':
          $order_items = commerce_email_order_items($order);
          $replacements[$original] = $order_items;
          break;
      }
    }
  }
  return $replacements;
}
