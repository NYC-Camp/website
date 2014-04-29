<?php

/**
 * @file
 * Rules actions to more or disable a Drupal block. Plus some helper functions.
 */

/**
 * Implements hook_rules_action_info().
 */
function rb_block_rules_action_info() {
  // Add actions that depend on required modules only.
  $actions = array(
    'rb_block_action_place_block' => array(
      'label' => t('Place a block'),
      'access' => 'administer blocks',
      'parameter' => array(
        'block' => array(
          'type' => 'text',
          'options list' => 'rb_block_block_list',
          'label' => t('Block'),
          'restriction' => 'input',
        ),
        'region' => array(
          'type' => 'text',
          'options list' => 'rb_block_region_list',
          'label' => t('New region'),
          'restriction' => 'input',
        ),
        'weight' => array(
          'type' => 'integer',
          'label' => t('Weight'),
        ),
      ),
      'group' => t('Rules Bonus: Block'),
    ),
    'rb_block_action_disable_block' => array(
      'label' => t('Disable a block'),
      'access' => 'administer blocks',
      'parameter' => array(
        'block' => array(
          'type' => 'text',
          'options list' => 'rb_block_block_list',
          'label' => t('Block'),
          'restriction' => 'input',
        ),
      ),
      'group' => t('Rules Bonus: Block'),
    ),
  );

  return $actions;
}

/**
 * Helper function that builds a select list of all blocks on the site.
 */
function rb_block_block_list() {
  // Get the list of blocks.
  global $theme;
  $path = drupal_get_path('module', 'block') . '/block.admin.inc';
  include_once $path;
  $blocks = block_admin_display_prepare_blocks($theme);

  // Format the list as a nice select array, with module and delta as keys.
  $select_list = array();
  foreach ($blocks as $block) {
    $select_list[$block['module'] . '-' . $block['delta']] = $block['info'];
  }

  return $select_list;
}

/**
 * Helper function that builds a select list of all regions in the current theme.
 */
function rb_block_region_list() {
  // Build a list of all available regions in all available themes.
  $regions = array();
  foreach (system_rebuild_theme_data() as $theme_name => $potential_theme) {
    if ($potential_theme->status) {
      foreach ($potential_theme->info['regions'] as $region_name => $region) {
        // The region name is also keyed by its theme, to make it possible to
        // enable blocks on selected themes only. (Yeah, this is a hack to
        // be able to send information about the theme to the action. It should
        // really have its own select list.)
        $regions[$theme_name][$theme_name . '-' . $region_name] = $region;
      }
    }
  }
  // Return the list of available regions.
  return ($regions);
}

/**
 * The 'rb_block_action_place_block' action.
 */
function rb_block_action_place_block($block, $region, $weight) {
  // Compare the region against the currently active theme – we only want to
  // insert blocks if the region matches this theme.
  global $theme;
  $region_info = explode('-', $region);
  if ($region_info[0] != $theme) {
    return;
  }
  else {
    // Ok, the theme is right. Change the $region variable to only contain the
    // actual region  name – not the theme name.
    $region = $region_info[1];
  }

  // Get block data.
  $block_info = explode('-', $block);
  $new_block = block_load($block_info[0], $block_info[1]);

  // Set the modified values for the block. Also assure that the block is set as
  // active.
  $new_block->region = $region;
  $new_block->weight = $weight;
  $new_block->theme  = $theme;
  $new_block->status = 1;

  // Set the block as a Drupal static, to allow it to be called from outside
  // this action (namely from hook_block_list_alter).
  $blocks = &drupal_static('rb_block_blocks');
  $blocks[$new_block->bid] = $new_block;
}

/**
 * The 'rb_block_action_disable_block' action.
 */
function rb_block_action_disable_block($block) {
  // Get block information.
  $block_info = explode('-', $block);
  $disabled_block = block_load($block_info[0], $block_info[1]);

  // Add the disabled block to a list in Drupal static, to allow it to be found
  // from hook_block_list_alter.
  $disabled_blocks = &drupal_static('rb_block_disabled');
  $disabled_blocks[$disabled_block->bid] = $disabled_block;
}
