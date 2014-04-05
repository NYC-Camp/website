<?php
/**
 * @file
 * cod_extras_scheduling.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function cod_extras_scheduling_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'dashboard_schedule_components';
  $page->task = 'page';
  $page->admin_title = 'Dashboard - Schedule Components';
  $page->admin_description = '';
  $page->path = '/admin/dashboard/schedule-components';
  $page->access = array();
  $page->menu = array(
    'type' => 'normal',
    'title' => 'Manage Schedule Components',
    'name' => 'management',
    'weight' => '0',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_dashboard_schedule_components_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'dashboard_schedule_components';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 'main',
        ),
        'parent' => NULL,
      ),
      'main' => array(
        'type' => 'column',
        'width' => 100,
        'width_type' => '%',
        'children' => array(
          0 => 1,
          1 => 'main-row',
        ),
        'parent' => 'canvas',
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'left',
          1 => 'center',
          2 => 'schedule_slots',
        ),
        'parent' => 'main',
      ),
      'center' => array(
        'type' => 'region',
        'title' => 'Center',
        'width' => '20.12140309699247',
        'width_type' => '%',
        'parent' => 'main-row',
      ),
      'left' => array(
        'type' => 'region',
        'title' => 'Left',
        'width' => '20.076756778495305',
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => '',
      ),
      1 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'intro',
        ),
        'parent' => 'main',
        'class' => '',
      ),
      'intro' => array(
        'type' => 'region',
        'title' => 'Intro',
        'width' => 100,
        'width_type' => '%',
        'parent' => '1',
        'class' => '',
      ),
      'schedule_slots' => array(
        'type' => 'region',
        'title' => 'Schedule Slots',
        'width' => '34.77586791456809',
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => '',
      ),
    ),
  );
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => array(
        'corner_location' => 'panel',
      ),
      'left' => array(
        'corner_location' => 'panel',
      ),
      'intro' => NULL,
      'right' => array(
        'corner_location' => 'panel',
      ),
      'schedule_slots' => array(
        'corner_location' => 'pane',
      ),
    ),
    'left' => array(
      'style' => 'rounded_corners',
    ),
    'right' => array(
      'style' => 'rounded_corners',
    ),
    'center' => array(
      'style' => 'rounded_corners',
    ),
    'schedule_slots' => array(
      'style' => 'rounded_corners',
    ),
  );
  $display->cache = array();
  $display->title = 'Manage Schedule Components';
  $display->uuid = 'cb742078-33bf-4c71-8d54-409f5ad3e57f';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-9faf4a4a-c36f-4175-b98d-33a02a986d5b';
    $pane->panel = 'center';
    $pane->type = 'views';
    $pane->subtype = 'admin_manage_rooms';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '0',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'default',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '9faf4a4a-c36f-4175-b98d-33a02a986d5b';
    $display->content['new-9faf4a4a-c36f-4175-b98d-33a02a986d5b'] = $pane;
    $display->panels['center'][0] = 'new-9faf4a4a-c36f-4175-b98d-33a02a986d5b';
    $pane = new stdClass();
    $pane->pid = 'new-d487c87e-5415-486a-acdd-4719758df9d7';
    $pane->panel = 'intro';
    $pane->type = 'fieldable_panels_pane';
    $pane->subtype = 'fpid:8';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'view_mode' => 'full',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'd487c87e-5415-486a-acdd-4719758df9d7';
    $display->content['new-d487c87e-5415-486a-acdd-4719758df9d7'] = $pane;
    $display->panels['intro'][0] = 'new-d487c87e-5415-486a-acdd-4719758df9d7';
    $pane = new stdClass();
    $pane->pid = 'new-41975948-1dfa-4914-8c1e-bc29288d0c1c';
    $pane->panel = 'left';
    $pane->type = 'views';
    $pane->subtype = 'admin_manage_schedule_time_slots';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '0',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'default',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '41975948-1dfa-4914-8c1e-bc29288d0c1c';
    $display->content['new-41975948-1dfa-4914-8c1e-bc29288d0c1c'] = $pane;
    $display->panels['left'][0] = 'new-41975948-1dfa-4914-8c1e-bc29288d0c1c';
    $pane = new stdClass();
    $pane->pid = 'new-1c2a0624-ec08-4008-bfbc-ef2fad736f75';
    $pane->panel = 'left';
    $pane->type = 'views';
    $pane->subtype = 'admin_manage_buildings';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '0',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'default',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $pane->uuid = '1c2a0624-ec08-4008-bfbc-ef2fad736f75';
    $display->content['new-1c2a0624-ec08-4008-bfbc-ef2fad736f75'] = $pane;
    $display->panels['left'][1] = 'new-1c2a0624-ec08-4008-bfbc-ef2fad736f75';
    $pane = new stdClass();
    $pane->pid = 'new-db16e038-4cdf-493b-8556-522ffc6f06cc';
    $pane->panel = 'left';
    $pane->type = 'views';
    $pane->subtype = 'admin_manage_venues';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '0',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'default',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 2;
    $pane->locks = array();
    $pane->uuid = 'db16e038-4cdf-493b-8556-522ffc6f06cc';
    $display->content['new-db16e038-4cdf-493b-8556-522ffc6f06cc'] = $pane;
    $display->panels['left'][2] = 'new-db16e038-4cdf-493b-8556-522ffc6f06cc';
    $pane = new stdClass();
    $pane->pid = 'new-73087266-e2e7-4f2d-944c-a8c34ad87959';
    $pane->panel = 'left';
    $pane->type = 'views';
    $pane->subtype = 'admin_manage_conferences';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '0',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'default',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 3;
    $pane->locks = array();
    $pane->uuid = '73087266-e2e7-4f2d-944c-a8c34ad87959';
    $display->content['new-73087266-e2e7-4f2d-944c-a8c34ad87959'] = $pane;
    $display->panels['left'][3] = 'new-73087266-e2e7-4f2d-944c-a8c34ad87959';
    $pane = new stdClass();
    $pane->pid = 'new-338b99c3-ae3a-423d-9532-8063df5cc2d2';
    $pane->panel = 'schedule_slots';
    $pane->type = 'views';
    $pane->subtype = 'admin_manage_schedule_slots';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '100',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'default',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '338b99c3-ae3a-423d-9532-8063df5cc2d2';
    $display->content['new-338b99c3-ae3a-423d-9532-8063df5cc2d2'] = $pane;
    $display->panels['schedule_slots'][0] = 'new-338b99c3-ae3a-423d-9532-8063df5cc2d2';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['dashboard_schedule_components'] = $page;

  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'dashboard_sessions_scheduling';
  $page->task = 'page';
  $page->admin_title = 'Dashboard - Sessions Scheduling';
  $page->admin_description = '';
  $page->path = 'admin/dashboard/sessions-scheduling';
  $page->access = array();
  $page->menu = array(
    'type' => 'normal',
    'title' => 'Manage Session Schedule',
    'name' => 'management',
    'weight' => '0',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_dashboard_sessions_scheduling_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'dashboard_sessions_scheduling';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 1,
          1 => 'main',
        ),
        'parent' => NULL,
      ),
      'main' => array(
        'type' => 'column',
        'width' => '74.922065748053',
        'width_type' => '%',
        'children' => array(
          0 => 'main-row',
        ),
        'parent' => 'canvas',
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'schedule',
        ),
        'parent' => 'main',
      ),
      1 => array(
        'type' => 'column',
        'width' => '25.077934251947003',
        'width_type' => '%',
        'parent' => 'canvas',
        'children' => array(
          0 => 2,
        ),
        'class' => '',
      ),
      2 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'sessions',
        ),
        'parent' => '1',
        'class' => '',
      ),
      'sessions' => array(
        'type' => 'region',
        'title' => 'Sessions',
        'width' => 100,
        'width_type' => '%',
        'parent' => '2',
        'class' => '',
      ),
      'schedule' => array(
        'type' => 'region',
        'title' => 'Schedule',
        'width' => 100,
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => '',
      ),
    ),
  );
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
      'sessions' => NULL,
      'schedule' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = '0c9cd148-fedc-4a0a-b029-e4f4d02c9b52';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-99518854-7000-4330-a520-01fbb8da69c0';
    $pane->panel = 'schedule';
    $pane->type = 'views';
    $pane->subtype = 'admin_schedling_slots';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '100',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'default',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '99518854-7000-4330-a520-01fbb8da69c0';
    $display->content['new-99518854-7000-4330-a520-01fbb8da69c0'] = $pane;
    $display->panels['schedule'][0] = 'new-99518854-7000-4330-a520-01fbb8da69c0';
    $pane = new stdClass();
    $pane->pid = 'new-17e5ddbe-f498-46d9-9b35-0a45ab998ce9';
    $pane->panel = 'sessions';
    $pane->type = 'views';
    $pane->subtype = 'admin_sessions_for_scheduling';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 1,
      'nodes_per_page' => '20',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'default',
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = '17e5ddbe-f498-46d9-9b35-0a45ab998ce9';
    $display->content['new-17e5ddbe-f498-46d9-9b35-0a45ab998ce9'] = $pane;
    $display->panels['sessions'][0] = 'new-17e5ddbe-f498-46d9-9b35-0a45ab998ce9';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['dashboard_sessions_scheduling'] = $page;

  return $pages;

}
