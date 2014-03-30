<?php

/**
 * @file
 * Rules plugins related to Views.
 */

/**
 * Implements hook_rules_data_info().
 */
function rb_views_rules_data_info() {
  return array(
    'rb_views_view' => array(
      'label' => t('view display'),
      'wrap' => TRUE,
      'property info' => _rb_views_views_display_info(),
      // @TODO: Create a UI to allow manual loading of views, too. See the
      // description of 'ui class' property in rules.api.php.
    ),
  );
}

/**
 * Defines the properties of the views display data structures.
 *
 * @return
 *   An array with the properties of view representations.
 */
function _rb_views_views_display_info($process_step = NULL) {
  $data_info = array(
    'machine_name' => array(
      'type' => 'text',
      'label' => t('Machine name'),
      'sanitized' => TRUE,
    ),
    'human_name' => array(
      'type' => 'text',
      'label' => t('Human-readable name'),
      'sanitized' => TRUE,
    ),
    'display' => array(
      'type' => 'text',
      'label' => t('Current display'),
      'sanitized' => TRUE,
    ),
    'base_table' => array(
      'type' => 'text',
      'label' => t('Base table'),
    ),
    'args' => array(
      'type' => 'list<text>',
      'label' => t('Arguments'),
      'setter callback' => 'entity_property_verbatim_set',
    ),
    'current_page' => array(
      'type' => 'integer',
      'label' => t('Current page'),
      'description' => t('Note that the page numbering starts on zero.'),
      'setter callback' => 'entity_property_verbatim_set',
    ),
    'items_per_page' => array(
      'type' => 'integer',
      'label' => t('Items per page'),
      'setter callback' => 'entity_property_verbatim_set',
    ),
    'offset' => array(
      'type' => 'integer',
      'label' => t('Offset'),
      'description' => t('Note that this is actually starting item, meaning that you have to enter "2" to skip the first item.'),
      'setter callback' => 'entity_property_verbatim_set',
    ),
    'total_rows' => array(
      'type' => 'integer',
      'label' => t('Number of results'),
    ),
    'output' => array(
      'type' => 'text',
      'label' => t('View output'),
      'sanitized' => TRUE,
    ),
  );

  // Add all handlers to the data structure as well.
  // @TODO: Make a separate data type for handlers as well.
  foreach (rb_views_get_views_handlers() as $handler_type => $handler_label) {
    $data_info[$handler_type] = array(
      'type' => 'list<text>',
      'label' => t('@handler alias', array('@handler' => $handler_label)),
    );
  }

  return $data_info;
}

function rb_views_rules_event_info() {
  $events = array(
    'rb_views_event_view_execute' => array(
      'label' => t('Before a view is being built'),
      'group' => t('Rules Bonus: Views'),
      'variables' => array(
        'view' => array(
          'type' => 'rb_views_view',
          'label' => t('Views display'),
        ),
      ),
    ),
    'rb_views_event_view_render' => array(
      'label' => t('After a view has been built'),
      'group' => t('Rules Bonus: Views'),
      'variables' => array(
        'view' => array(
          'type' => 'rb_views_view',
          'label' => t('Views display'),
        ),
      ),
    ),
    'rb_views_event_view_complete' => array(
      'label' => t('After a view has been rendered'),
      'group' => t('Rules Bonus: Views'),
      'variables' => array(
        'view' => array(
          'type' => 'rb_views_view',
          'label' => t('Views display'),
        ),
      ),
    ),
  );

  return $events;
}

/**
 * Implements hook_rules_action_info().
 */
function rb_views_rules_action_info() {
  $actions = array(
    'rb_views_handler_remove' => array(
      'label' => t('Unset a view handler'),
      'group' => t('Rules Bonus: Views'),
      'parameter' => array(
        'view' => array(
          'type' => 'rb_views_view',
          'label' => t('View'),
          'restriction' => 'select',
        ),
        'handler' => array(
          'type' => 'text',
          'label' => t('Handler type'),
          'options list' => 'rb_views_get_views_handlers',
          'restriction' => 'input',
        ),
        'alias' => array(
          'type' => 'text',
          'label' => t('Handler alias'),
        ),
      ),
    ),
  );

  // @TODO: Create actions to build, execute and render a view. But for that to
  // make sense, it must be possible to load a view manually.
  return $actions;
}

/**
 * Callback for the rb_views_handler_remove action.
 *
 * Removes a selected handler instance from a view.
 */
function rb_views_handler_remove($view, $handler, $alias) {
  // Find the handler alias in the view representation – these are keyed by
  // numbers, and not by alias.
  $key = array_search($alias, $view->$handler);
  if ($key !== FALSE) {
    // If the alias is found, remove it and return the updated view repr.
    unset($view->{$handler}[$key]);
    return array('view' => $view);
  }
}

function rb_views_rules_plugin_info() {
  // Most of this is just copy-pasted from the rule set component.
  return array(
    'views argument validator' => array(
      'label' => t('Views argument validator'),
      'module' => 'rb_views',
      'class' => 'RbViewsArgumentValidator',
      'component' => TRUE,
      'embeddable' => FALSE,
      'extenders' => array(
        'RulesPluginUIInterface' => array(
          'class' => 'RbViewsArgumentValidatorUI',
        ),
      ),
    ),
  );
}
