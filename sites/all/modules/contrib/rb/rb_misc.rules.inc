<?php
/**
 * @file
 * Miscellaneous conditions and actions for Rules.
 */

/**
 * Implements hook_rules_condition_info().
 */
function rb_misc_rules_condition_info() {
  // Add conditions that depend on required modules only.
  $conditions = array(
    'rb_misc_condition_is_numeric' => array(
      'label' => t('String contains number'),
      'group' => t('Rules Bonus: Miscellaneous'),
      'parameter' => array(
        'string' => array(
          'type' => 'text',
          'label' => t('String to check'),
        ),
      ),
    ),
    'rb_misc_condition_user_has_permission' => array(
      'label' => t('User has permission(s)'),
      'parameter' => array(
        'account' => array('type' => 'user', 'label' => t('User')),
        'permissions' => array(
          'type' => 'list<text>',
          'label' => t('Permissions'),
          'multiple' => TRUE,
          'options list' => 'rb_misc_user_permissions_options_list',
        ),
        'operation' => array(
          'type' => 'text',
          'label' => t('Match permissions'),
          'options list' => 'rules_user_condition_operations',
          'restriction' => 'input',
          'optional' => TRUE,
          'default value' => 'AND',
          'description' => t('If matching against all selected permissions, the user must have <em>all</em> the permissions selected.'),
        ),
      ),
      'group' => t('Rules Bonus: Miscellaneous'),
      'access callback' => 'rules_user_integration_access',
    ),
  );

  // Add conditions that depend on non-required modules.
  if (module_exists('views')) {
    $conditions['rb_misc_action_views_result_count'] = array(
      'label' => t('Check number of results from a view'),
      'parameter' => array(
        'view' => array(
          'type' => 'text',
          'label' => t('View and display'),
          'options list' => 'rb_misc_views_list',
          'description' => t('Select the view and display you want to check'),
          'restriction' => 'input',
        ),
        'args' => array(
          'type' => 'text',
          'label' => t('Arguments'),
          'description' => t('Any arguments to pass to the view, one per line.
            You may use token replacement patterns.'),
          'optional' => TRUE,
        ),
        'minimum' => array(
          'type' => 'integer',
          'label' => t('Minimum number of results'),
          'description' => t('This condition returns TRUE if the view has at
            least the given number of results.'),
        ),
      ),
      'group' => t('Rules Bonus: Miscellaneous'),
    );
  }

  // Automatic nodetitles.
  if (module_exists('auto_nodetitle')) {
    $conditions['rb_misc_condition_auto_nodetitle_is_needed'] = array(
      'label' => t('Automatic Nodetitle is needed'),
      'group' => t('Rules Bonus: Miscellaneous'),
      'parameter' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('Node'),
        ),
      ),
    );
  }

  return $conditions;
}

/**
 * User has permission condition help callback.
 */
function rb_misc_condition_user_has_permission_help() {
  return t('Whether the user has the selected permission(s).');
}

/**
 * Implements hook_rules_action_info().
 */
function rb_misc_rules_action_info() {
  // Add actions that depend on required modules only.
  $actions = array(
    'rb_misc_action_set_title' => array(
      'label' => t('Set page title'),
      'parameter' => array(
        'page_title' => array(
          'type' => 'text',
          'label' => t('Title to set'),
          'description' => t('Choose which page title should be set on this action. This title is set as $title in page.tpl.php'),
        ),
      ),
      'group' => t('Rules Bonus: Miscellaneous'),
    ),
    'rb_misc_action_node_clone' => array(
      'label' => t('Clone a node'),
      'parameter' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('Node to clone'),
          'description' => t('All properties except node ID, version ID and
            a few other meta data will be cloned. Use the node save action
            to provide the new node with a node ID.'),
        ),
      ),
      'provides' => array(
        'cloned_node' => array(
          'type' => 'node',
          'label' => t('Cloned node'),
          'save' => TRUE,
        ),
      ),
      'group' => t('Rules Bonus: Miscellaneous'),
    ),
    'rb_misc_action_integer_to_date' => array(
      'label' => t('Create a date from a number'),
      'parameter' => array(
        'integer' => array(
          'type' => 'integer',
          'label' => t('Integer number'),
        ),
      ),
      'provides' => array(
        'date' => array(
          'type' => 'date',
          'label' => t('Date'),
        ),
      ),
      'group' => t('Rules Bonus: Miscellaneous'),
    ),
    'rb_misc_action_concatenate_strings' => array(
      'label' => t('Merge two strings'),
      'parameter' => array(
        'string1' => array(
          'type' => 'text',
          'label' => t('First text string'),
        ),
        'string2' => array(
          'type' => 'text',
          'label' => t('Second text string'),
        ),
      ),
      'provides' => array(
        'string' => array(
          'type' => 'text',
          'label' => t('Merged string'),
        ),
      ),
      'group' => t('Rules Bonus: Miscellaneous'),
    ),
    'rb_misc_action_string_to_integer' => array(
      'label' => t('Get integer from string'),
      'parameter' => array(
        'string' => array(
          'type' => 'text',
          'label' => t('String'),
          'description' => t('If the string is not numeric, 0 will be returned.'),
        ),
      ),
      'provides' => array(
        'integer' => array(
          'type' => 'integer',
          'label' => t('Integer'),
        ),
      ),
      'group' => t('Rules Bonus: Miscellaneous'),
    ),
  );

  // Add actions that depend on non-required modules.
  if (module_exists('views')) {
    $actions['rb_misc_action_views_load_list'] = array(
      'label' => t('Load a node list with Views'),
      'parameter' => array(
        'view' => array(
          'type' => 'text',
          'label' => t('View and display'),
          'options list' => 'rb_misc_views_list_node',
          'description' => t('Select the view and display you want to use to
            create a list.'),
          'restriction' => 'input',
        ),
        'args' => array(
          'type' => 'text',
          'label' => t('Arguments'),
          'description' => t('Any arguments to pass to the view, one per line.
            You may use token replacement patterns.'),
          'optional' => TRUE,
        ),
      ),
      'provides' => array(
        'node_list' => array(
          'type' => 'list<node>',
          'label' => t('View node list'),
        ),
      ),
    'group' => t('Rules Bonus: Miscellaneous'),
    );
    $actions['rb_misc_action_views_load_user_list'] = array(
      'label' => t('Load a user list with Views'),
      'parameter' => array(
        'view' => array(
          'type' => 'text',
          'label' => t('View and display'),
          'options list' => 'rb_misc_views_list_user',
          'description' => t('Select the view and display you want to use to
            create a list.'),
          'restriction' => 'input',
        ),
        'args' => array(
          'type' => 'text',
          'label' => t('Arguments'),
          'description' => t('Any arguments to pass to the view, one per line.
            You may use token replacement patterns.'),
          'optional' => TRUE,
        ),
      ),
      'provides' => array(
        'user_list' => array(
          'type' => 'list<user>',
          'label' => t('View user list'),
        ),
      ),
      'group' => t('Rules Bonus: Miscellaneous'),
    );
    $actions['rb_misc_action_views_load_node'] = array(
      'label' => t('Load the first node in a Views list'),
      'parameter' => array(
        'view' => array(
          'type' => 'text',
          'label' => t('View and display'),
          'options list' => 'rb_misc_views_list_node',
          'description' => t('Select the view and display you want to use to
            load a node.'),
          'restriction' => 'input',
        ),
        'args' => array(
          'type' => 'text',
          'label' => t('Arguments'),
          'description' => t('Any arguments to pass to the view, one per line.
            You may use token replacement patterns.'),
          'optional' => TRUE,
        ),
      ),
    'provides' => array(
      'node' => array(
        'type' => 'node',
        'label' => t('Node from Views'),
      ),
    ),
    'group' => t('Rules Bonus: Miscellaneous'),
    );
    // Note that the following if statement *should* be inside the Views if
    // statement.
    if (module_exists('comment')) {
      $actions['rb_misc_action_views_load_comment_list'] = array(
        'label' => t('Load a comment list with Views'),
        'parameter' => array(
          'view' => array(
            'type' => 'text',
            'label' => t('View and display'),
            'options list' => 'rb_misc_views_list_comment',
            'description' => t('Select the view and display you want to use to
              create a list.'),
            'restriction' => 'input',
          ),
          'args' => array(
            'type' => 'text',
            'label' => t('Arguments'),
            'description' => t('Any arguments to pass to the view, one per line.
              You may use token replacement patterns.'),
            'optional' => TRUE,
          ),
        ),
      'provides' => array(
        'comment_list' => array(
          'type' => 'list<comment>',
          'label' => t('View comment list'),
        ),
      ),
      'group' => t('Rules Bonus: Miscellaneous'),
      );
    }
  }
  if (module_exists('menu') && module_exists('menu_position')) {
    $actions['rb_misc_action_set_active_menu_item'] = array(
      'label' => t('Set the active menu item'),
      'parameter' => array(
        'menu_item' => array(
          'type' => 'text',
          'label' => t('Menu item'),
          'options list' => 'rb_misc_action_set_active_menu_item_list',
          'restriction' => 'input',
          'description' => t('Select the menu item that should be marked active.'),
        ),
      ),
      'group' => t('Rules Bonus: Miscellaneous'),
    );
  }
  if (module_exists('path')) {
    $actions['rb_misc_action_get_path_alias'] = array(
      'label' => t('Load a path alias'),
      'parameter' => array(
        'path' => array(
          'type' => 'text',
          'label' => t('Internal path to fetch alias for'),
          'description' => t('If multiple aliases exist, only the first will be fetched.'),
        ),
        'language' => array(
          'type' => 'token',
          'label' => t('Language'),
          'description' => t('The language for which the URL alias applies, if any.'),
          'options list' => 'entity_metadata_language_list',
          'optional' => TRUE,
          'default value' => LANGUAGE_NONE,
        ),
      ),
      'provides' => array(
        'alias' => array(
          'type' => 'text',
          'label' => t('Path alias'),
          'save' => TRUE,
        ),
      ),
    'group' => t('Rules Bonus: Miscellaneous'),
    );
  }

  // Automatic Nodetitles.
  if (module_exists('auto_nodetitle')) {
    $actions['rb_misc_action_auto_nodetitle'] = array(
      'label' => t('Set auto nodetitle'),
      'parameter' => array(
        'node' => array(
          'type' => 'node',
          'label' => t('Content'),
          'save' => TRUE,
        ),
      ),
      'access callback' => 'rules_node_admin_access',
      'group' => t('Rules Bonus: Miscellaneous'),
    );
  }

  return $actions;
}

/**
 * Options list callback for user permissions.
 */
function rb_misc_user_permissions_options_list($element) {
  // Get a list of all the modules implementing a hook_permission() and sort by
  // display name.
  $modules = $permissions = array();
  $module_info = system_get_info('module');

  foreach (module_implements('permission') as $module) {
    $modules[$module] = $module_info[$module]['name'];
  }
  asort($modules);

  foreach ($modules as $module => $display_name) {
    if ($perms = module_invoke($module, 'permission')) {
      foreach ($perms as $perm => $perm_item) {
        $permissions[$display_name][$perm] = strip_tags($perm_item['title']);
      }
    }
  }

  return $permissions;
}


/**
 * Implements hook_rules_event_info().
 */
function rb_misc_rules_event_info() {
  // Add events that depend on required modules only.
  $events = array();

  // Add actions that depend on non-required modules.
  if (module_exists('page_manager')) {
    // First, and so far only case, optionally provide events for when variants
    // in Page manager's custom pages are displayed/executed.

    // Loop through all the variants for custom pages defined on the site.
    foreach (page_manager_get_tasks_by_type('page') as $task => $task_info) {
      foreach (page_manager_load_task_handlers($task_info) as $name => $variant) {
        // If the variant is enabled as a Rules trigger, declare a Rules event
        // based on the name of the variant and its included context objects.
        if (isset($variant->conf['rb_misc_trigger'])
          && $variant->conf['rb_misc_trigger']) {

          $subtask = page_manager_page_subtask($task, $variant->subtask);
          _rb_misc_add_variant_render_events($events, $task_info, $subtask, $variant);
        }
      }

      // Some variantes might be exported in hook_default_page_manager_pages().
      foreach (page_manager_get_task_subtasks($task_info) as $name => $page) {
        $subtask = isset($page['subtask']) ? $page['subtask'] : NULL;
        if (isset($subtask->default_handlers)) {
          foreach ($subtask->default_handlers as $variant_name => $variant) {
            if (isset($variant->conf['rb_misc_trigger']) && $variant->conf['rb_misc_trigger']) {
              _rb_misc_add_variant_render_events($events, $task_info, $page, $variant);
            }
          }
        }
      }
    }
  }

  return $events;
}

/**
 * Helper function that adds event information for Page manager page variants.
 */
function _rb_misc_add_variant_render_events(&$events, $task_info, $subtask, $variant) {
  $rules_info = rb_misc_list_variant_context_entities($task_info, $subtask, $variant);
  $events['rb_misc_trigger_' . $variant->name] = array(
    'group' => t('Rules Bonus: Miscellaneous'),
    'label' => t('Variant @name is rendered', array('@name' => $variant->conf['title'])),
    'variables' => $rules_info,
  );
}
/**
 * Helper function that lists all available views with their displays.
 *
 * I wish I found a way to call this function with an argument, directly from
 * the declaration of the action.
 *
 * @tables array
 *   An array containing any restrictions on which Views base tables should be
 *   accepted. If empty, all base tables will be returned.
 * @return array
 *   An array of all views and their displays on the form 'view|display',
 *   formatted to be used as an select list.
 */
function rb_misc_views_list_restrictions($tables = array()) {
  $selectable_displays = array();
  foreach (views_get_all_views() as $view_name => $view) {
    if (count($tables) == 0 || in_array($view->base_table, $tables)) {
      foreach ($view->display as $display_name => $display) {
        $selectable_displays[$view_name . '|' . $display_name] =
          check_plain($view->human_name) . '|' . check_plain($display->display_title);
      }
    }
  }

  return $selectable_displays;
}

/**
 * Helper function that lists all available views with their displays.
 */
function rb_misc_views_list() {
  return rb_misc_views_list_restrictions();
}

/**
 * Helper function that lists all available node views with their displays.
 */
function rb_misc_views_list_node() {
  return rb_misc_views_list_restrictions(array('node'));
}

/**
 * Helper function that lists all available user views with their displays.
 */
function rb_misc_views_list_user() {
  return rb_misc_views_list_restrictions(array('users'));
}

/**
 * Helper function that lists all available comment views with their displays.
 */
function rb_misc_views_list_comment() {
  return rb_misc_views_list_restrictions(array('comment'));
}

/**
 * The 'rb_misc_condition_is_numeric' condition.
 */
function rb_misc_condition_is_numeric($string) {
  return (is_numeric($string));
}

/**
 * The 'rb_misc_condition_user_has_permission' permission.
 */
function rb_misc_condition_user_has_permission($account, $permissions, $operation = 'AND') {
  switch ($operation) {
    case 'OR':
      foreach ($permissions as $perm) {
        if (user_access($perm, $account)) {
          return TRUE;
        }
      }
      return FALSE;

    case 'AND':
      foreach ($permissions as $perm) {
        if (!user_access($perm, $account)) {
          return FALSE;
        }
      }
      return TRUE;
  }
}

/**
 * The 'rb_misc_condition_auto_nodetitle_is_needed' condition.
 */
function rb_misc_condition_auto_nodetitle_is_needed($node) {
  return auto_nodetitle_is_needed($node);
}

/**
 * The 'rb_misc_action_views_result_count' condition.
 */
function rb_misc_action_views_result_count($view, $args, $minimum) {
  // Prepare some data about the view.
  $views_settings = explode('|', $view);
  $view_name = $views_settings[0];
  $display_name = $views_settings[1];
  $view_arguments = explode("\r", $args);

  // Load the view and set the properties.
  $view = views_get_view($view_name);

  $view->set_display($display_name);
  $view->set_arguments($view_arguments);
  $view->set_items_per_page(0);

  // Get the results of the view and return TRUE or FALSE depending the number
  // of hits.
  $view->execute();
  $results = $view->result;
  return (count($results) >= $minimum);
}

/**
 * The 'rb_misc_action_views_load_list' action.
 */
function rb_misc_action_views_load_list($view, $args) {
  // Prepare some data about the view.
  $views_settings = explode('|', $view);
  $view_name = $views_settings[0];
  $display_name = $views_settings[1];
  $view_arguments = explode("\r", $args);

  // Load the view and set the properties.
  $view = views_get_view($view_name);

  $view->set_display($display_name);
  $view->set_arguments($view_arguments);
  $view->set_items_per_page(0);
  $view->execute();

  // Rules expects a list of fully loaded nodes, so we have to loop through this
  // list and finally do a heck of a lot of node loads. :-(
  $nids = array();
  foreach ($view->result as $row) {
    $nids[] = $row->nid;
  }

  // Load the nodes, and return them.
  return (array('node_list' => node_load_multiple($nids)));
}

/**
 * The 'rb_misc_action_views_load_list_user' action.
 */
function rb_misc_action_views_load_user_list($view, $args) {
  // Prepare some data about the view.
  $views_settings = explode('|', $view);
  $view_name = $views_settings[0];
  $display_name = $views_settings[1];
  $view_arguments = explode("\r", $args);

  // Load the view and set the properties.
  $view = views_get_view($view_name);

  $view->set_display($display_name);
  $view->set_arguments($view_arguments);
  $view->set_items_per_page(0);
  $view->execute();

  // Rules expects a list of fully loaded nodes, so we have to loop through this
  // list and finally do a heck of a lot of node loads. :-(
  $nids = array();
  foreach ($view->result as $row) {
    $uids[] = $row->uid;
  }

  // Load the nodes, and return them.
  return (array('user_list' => user_load_multiple($uids)));
}

/**
 * The 'rb_misc_action_set_title' action.
 */
function rb_misc_action_set_title($page_title) {
  drupal_set_title($page_title);
}

/**
 * The 'rb_misc_action_set_title' action.
 */
function rb_misc_action_set_active_menu_item($mlid) {
  // 90 percent of the code below is shamelessly stolen from the menu_position
  // module, by JohnAlbin (http://drupal.org/user/32095). Cred to him!

  // Retrieve menu item specified in the settings.
  $menu_item = menu_link_load($mlid);

  // Clone the original router item, but insert our menu_position path.
  $original_router_item = menu_get_item();
  $router_item = $original_router_item;
  $router_item['href'] = $menu_item['link_path'];
  $router_item['menu_name'] = $menu_item['menu_name'];

  // Even if we are denied access to the page, we still want to show the
  // navigational paths to the page.
  $router_item['access'] = TRUE;

  // Temporarily override the original router item.
  menu_set_item(NULL, $router_item);

  // The magic goes here. Cred to JohnAlbin.
  menu_position_precache_tree($router_item, $original_router_item, $menu_item['menu_name']);

  // Also store the new, faked active mlid tree in drupal_static, for use by
  // other modules (such as Views menu support).
  $faked_tree = &drupal_static('rb_misc_mlid_trail');
  foreach (range(1, 9) as $index) {
    if ($menu_item['p' . $index]) {
      $faked_tree[] = $menu_item['p' . $index];
    }
  }

  // Restore the original router item.
  menu_set_item(NULL, $original_router_item);
}

/**
 * Helper function to show all menus and their menu items
 */
function rb_misc_action_set_active_menu_item_list() {
  $menus = menu_parent_options(menu_get_menus(), array('mlid' => 0));
  $root_menus = array();
  foreach ($menus as $key => $name) {
    $id = explode(':', $key);
    if ($id[1] == '0') {
      $root_menus[$id[0]] = check_plain($name);
    }
    else {
      $link = menu_link_load($id[1]);
      $identifier = $link['mlid'];
      $root_menu = $root_menus[$id[0]];
      while (isset($menus[$root_menu][$identifier])) {
        $identifier .= "'";
      }
      $menus[$root_menu][$identifier] = $name;
    }
    unset($menus[$key]);
  }
  return $menus;
}

/**
 * The 'rb_misc_action_node_clone' action.
 */
function rb_misc_action_node_clone($node) {
  $cloned_node = clone $node;

  // Reset a few basic values for the clone.
  $properties_to_reset = array();

  // Let any other modules make changes to the array of properties to reset.
  // (This is done by implementing hook_rb_misc_clone_reset_properties_alter.)
  drupal_alter('rb_misc_node_clone_reset_properties', $properties_to_reset);

  foreach ($properties_to_reset as &$property) {
    if (isset($cloned_node->{$property})) {
      $cloned_node->{$property} = NULL;
    }
  }
  // Remove the lingering reference to the foreach-by-reference above.
  unset($property);

  // Add an extra property as a flag.
  $cloned_node->clone_from_original_nid = $node->nid;

  // Set the cloned node as new.
  $cloned_node->is_new = TRUE;

  return array('cloned_node' => $cloned_node);
}

/**
 * Implements hook_rb_misc_clone_reset_properties_alter().
 */
function rb_misc_rb_misc_node_clone_reset_properties_alter(&$properties_to_reset) {
  $properties_to_reset += array('nid', 'vid', 'tnid', 'created', 'menu', 'book',
    'path', 'last_comment_timestamp', 'last_comment_name', 'last_comment_uid');
}

/**
 * The 'rb_misc_action_views_load_node' action.
 */
function rb_misc_action_views_load_node($view, $args) {
  // Prepare some data about the view.
  $views_settings = explode('|', $view);
  $view_name = $views_settings[0];
  $display_name = $views_settings[1];
  $view_arguments = explode("\r", $args);

  // Load the view and set the properties.
  $view = views_get_view($view_name);

  $view->set_display($display_name);
  $view->set_arguments($view_arguments);
  $view->set_items_per_page(1);
  $view->execute();

  // Check if we have any results from the view, if so return the first one.
  if (count($view->result)) {
    $first_result = $view->result[0];
    $node = node_load($first_result->nid);
    return array('node' => $node);
  }
  else {
    // No results. :-(
    return;
  }
}

/**
 * The 'rb_misc_action_views_load_comment_list' action.
 */
function rb_misc_action_views_load_comment_list($view, $args) {
  // Prepare some data about the view.
  $views_settings = explode('|', $view);
  $view_name = $views_settings[0];
  $display_name = $views_settings[1];
  $view_arguments = explode("\r", $args);

  // Load the view and set the properties.
  $view = views_get_view($view_name);

  $view->set_display($display_name);
  $view->set_arguments($view_arguments);
  $view->set_items_per_page(0);
  $view->execute();

  // Rules expects a list of fully loaded nodes, so we have to loop through this
  // list and finally do a heck of a lot of node loads. :-(
  $nids = array();
  foreach ($view->result as $row) {
    $cids[] = $row->cid;
  }

  // Load the nodes, and return them.
  return (array('comment_list' => comment_load_multiple($cids)));
}

/**
 * The 'rb_misc_action_integer_to_date' action.
 */
function rb_misc_action_integer_to_date($integer) {
  // Possibly simplest action so far!
  return (array('date' => $integer));
}

/**
 * The 'rb_misc_action_get_path_alias' action.
 */
function rb_misc_action_get_path_alias($path, $language = LANGUAGE_NONE) {
  // Fetch the relevant alias, for the relevant language.
  $alias = path_load(array('source' => $path, 'language' => $language));
  return (array('alias' => $alias['alias']));
}

/**
 * The 'rb_misc_action_auto_nodetitle' action.
 */
function rb_misc_action_auto_nodetitle($node) {
  auto_nodetitle_set_title($node);
}

/**
 * The 'rb_misc_action_concatenate_strings' action.
 */
function rb_misc_action_concatenate_strings($string1, $string2) {
  // It feels silly to not solve this action in a more general way, but that
  // will have to be for some other time. Blame @Itangalo.
  return (array('string' => $string1 . $string2));
}

/**
 * The 'rb_misc_action_string_to_integer' action.
 */
function rb_misc_action_string_to_integer($string) {
  return (array('integer' => $string));
}
