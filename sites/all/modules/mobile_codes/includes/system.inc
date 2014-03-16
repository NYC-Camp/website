<?php
/**
 * @file
 * System module integration.
 */

/**
 * Implements hook_menu().
 */
function mobile_codes_menu() {
  $items = array();
  drupal_alter('mobile_codes_menu', $items);
  return $items;
}

/**
 * Implements hook_theme().
 */
function mobile_codes_theme() {
  $items = array();
  drupal_alter('mobile_codes_theme', $items);
  return $items;
}

/**
 * Implements hook_form_alter().
 */
function mobile_codes_form_alter(&$form, $form_state, $form_id) {
  drupal_alter('mobile_codes_form', $form, $form_state, $form_id);
  drupal_alter("mobile_codes_form_{$form_id}", $form, $form_state);
}

/**
 * Implements hook_token_info_alter().
 */
function mobile_codes_token_info_alter(&$data) {
  drupal_alter('mobile_codes_token_info_alter', $data);
}

/**
 * Implements hook_tokens_alter().
 */
function mobile_codes_tokens_alter(array &$replacements, array $context) {
  drupal_alter('mobile_codes_tokens_alter', $replacements, $context);
}
