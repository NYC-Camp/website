<?php
/**
 * @file
 * example_rule_promotion_syncronization.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function example_rule_promotion_syncronization_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function example_rule_promotion_syncronization_node_info() {
  $items = array(
    'article_promotion' => array(
      'name' => t('Article promotion'),
      'base' => 'node_content',
      'description' => t('Article promotions are used to promote articles in list pages and in sidebars. Each promotion refers to exactly one article.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
