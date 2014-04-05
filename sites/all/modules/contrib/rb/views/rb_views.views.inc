<?php

/**
 * @file
 * Declares Views plugins for Rules Bonus Pack: Views.
 */

function rb_views_views_plugins() {
  return array(
    'argument validator' => array(
      'rb_views_plugin_argument_validate_rules_component' => array(
        'title' => t('Rules validator plugin'),
        'handler' => 'rb_views_plugin_argument_validate_rules_component',
      ),
    ),
  );
}
