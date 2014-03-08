<?php
/**
 * @file
 * Admin module integration.
 */

/**
 * Implements hook_mobile_codes_block_info_alter() on behalf of block.module.
 */
function admin_mobile_codes_block_info_alter(&$blocks) {
  $blocks['generate_code']['admin'] = TRUE;
}
