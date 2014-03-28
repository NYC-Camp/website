<?php

/**
 * @file
 * Rules integration for invoices.
 *
 * @addtogroup rules
 * @{
 */
 
/**
 * Implements hook_rules_condition_info()
 */
function commerce_invoice_rules_condition_info() {
  $items = array();
  $items['commerce_invoice_exists'] = array(
    'label' => t('Invoice exists for Order'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Order to check'),
      ),
    ),
    'group' => t('Commerce Invoice'),
    'callbacks' => array(
      'execute' => 'commerce_invoice_rules_condition_exists'
    )
  );
  return $items;
}

function commerce_invoice_rules_condition_exists($order) {
  $order_id = $order->order_id;
  $query = new EntityFieldQuery();
  $results = $query
    ->entityCondition('entity_type', 'commerce_invoice')
    ->propertyCondition('order_id', $order_id, '=')
    ->execute();
  if (isset($results['commerce_invoice'])) {
    return TRUE;
  }
  else {
    return FALSE;
  }
}
 
/**
 * Implements hook_rules_action_info().
 */
function commerce_invoice_rules_action_info() {
  $actions = array();

  $actions['commerce_invoice_generate'] = array(
    'label' => t('Generate invoice'),
    'parameter' => array(
      'commerce_order' => array(
        'type' => 'commerce_order',
        'label' => t('Order to update'),
      ),
    ),
    'group' => t('Commerce Invoice'),
    'callbacks' => array(
      'execute' => 'commerce_invoice_rules_generate',
    ),
  );
  
  return $actions;
}

function commerce_invoice_rules_generate($order) {
  $invoice = commerce_invoice_new($order->uid, $order->order_id);
  commerce_invoice_save($invoice);
}

  
