<?php
/**
 * @file
 * cod_paid_events.features.inc
 */

/**
 * Implements hook_commerce_product_default_types().
 */
function cod_paid_events_commerce_product_default_types() {
  $items = array(
    'cod_paid_event' => array(
      'type' => 'cod_paid_event',
      'name' => 'Paid Event',
      'description' => 'A paid event product',
      'help' => '',
      'revision' => 1,
    ),
  );
  return $items;
}

/**
 * Implements hook_default_registration_type().
 */
function cod_paid_events_default_registration_type() {
  $items = array();
  $items['paid_event'] = entity_import('registration_type', '{
    "name" : "paid_event",
    "label" : "Paid Event",
    "locked" : "0",
    "weight" : "0",
    "data" : null
  }');
  return $items;
}
