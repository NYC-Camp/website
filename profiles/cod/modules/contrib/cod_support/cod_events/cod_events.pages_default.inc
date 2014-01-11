<?php
/**
 * @file
 * cod_events.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function cod_events_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'events_dashboard';
  $page->task = 'page';
  $page->admin_title = 'Event Dashboard';
  $page->admin_description = '';
  $page->path = 'node/%node/dashboard';
  $page->access = array(
    'plugins' => array(
      0 => array(
        'name' => 'node_type',
        'settings' => array(
          'type' => array(
            'event' => 'event',
          ),
        ),
        'context' => 'argument_entity_id:node_1',
        'not' => FALSE,
      ),
      1 => array(
        'name' => 'role',
        'settings' => array(
          'rids' => array(
            0 => 3,
            1 => 4,
            2 => 5,
            3 => 7,
            4 => 6,
          ),
        ),
        'context' => 'logged-in-user',
        'not' => FALSE,
      ),
    ),
    'logic' => 'and',
    'type' => 'none',
    'settings' => NULL,
  );
  $page->menu = array(
    'type' => 'tab',
    'title' => 'Event Dashboard',
    'name' => 'navigation',
    'weight' => '0',
    'parent' => array(
      'type' => 'none',
      'title' => '',
      'name' => 'navigation',
      'weight' => '0',
    ),
  );
  $page->arguments = array(
    'node' => array(
      'id' => 1,
      'identifier' => 'Node: ID',
      'name' => 'entity_id:node',
      'settings' => array(),
    ),
  );
  $page->conf = array(
    'admin_paths' => TRUE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_events_dashboard_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'events_dashboard';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Event Dashboard',
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
  $display->layout = 'flexible:cod_events_dashboard_tabs';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'left' => NULL,
      'right' => NULL,
      'center' => NULL,
      'summary_left' => NULL,
      'summary_right' => NULL,
      'dashboard_tabs' => NULL,
    ),
    'dashboard_tabs' => array(
      'style' => 'tabs',
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'edfb94ed-488a-16b4-0177-22b058f43315';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-6d83b026-0e02-9ba4-d19e-c19cdbd3507c';
    $pane->panel = 'center';
    $pane->type = 'block';
    $pane->subtype = 'user-online';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
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
    $pane->uuid = '6d83b026-0e02-9ba4-d19e-c19cdbd3507c';
    $display->content['new-6d83b026-0e02-9ba4-d19e-c19cdbd3507c'] = $pane;
    $display->panels['center'][0] = 'new-6d83b026-0e02-9ba4-d19e-c19cdbd3507c';
    $pane = new stdClass();
    $pane->pid = 'new-c487f396-ec5e-93a4-fdae-8304d36735cf';
    $pane->panel = 'dashboard_tabs';
    $pane->type = 'cod_events_pane';
    $pane->subtype = 'cod_events_pane';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array();
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $pane->uuid = 'c487f396-ec5e-93a4-fdae-8304d36735cf';
    $display->content['new-c487f396-ec5e-93a4-fdae-8304d36735cf'] = $pane;
    $display->panels['dashboard_tabs'][0] = 'new-c487f396-ec5e-93a4-fdae-8304d36735cf';
    $pane = new stdClass();
    $pane->pid = 'new-639153bd-a7bf-9134-716e-6727868168d3';
    $pane->panel = 'summary_left';
    $pane->type = 'views';
    $pane->subtype = 'cod_schedule';
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
      'display' => 'page_1',
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
    $pane->uuid = '639153bd-a7bf-9134-716e-6727868168d3';
    $display->content['new-639153bd-a7bf-9134-716e-6727868168d3'] = $pane;
    $display->panels['summary_left'][0] = 'new-639153bd-a7bf-9134-716e-6727868168d3';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-639153bd-a7bf-9134-716e-6727868168d3';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['events_dashboard'] = $page;

  return $pages;

}
