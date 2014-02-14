<?php
/**
 * @file
 * accommodations.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function accommodations_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'accomodation';
  $page->task = 'page';
  $page->admin_title = 'Accomodation';
  $page->admin_description = 'A page for Accommodations with an page intro, views listings, map of hotel listings and eventually some dynamic sidebars';
  $page->path = 'accomodations';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_accomodation_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'accomodation';
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
          2 => 2,
        ),
        'parent' => 'canvas',
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'body',
        ),
        'parent' => 'main',
      ),
      1 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'intro',
        ),
        'parent' => 'main',
        'class' => 'Intro',
      ),
      'intro' => array(
        'type' => 'region',
        'title' => 'Intro',
        'width' => 100,
        'width_type' => '%',
        'parent' => '1',
        'class' => '',
      ),
      'body' => array(
        'type' => 'region',
        'title' => 'Body',
        'width' => 100,
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => '',
      ),
      2 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'map',
        ),
        'parent' => 'main',
        'class' => '',
      ),
      'map' => array(
        'type' => 'region',
        'title' => 'Map',
        'width' => 100,
        'width_type' => '%',
        'parent' => '2',
        'class' => '',
      ),
    ),
  );
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'intro' => NULL,
      'body' => NULL,
      'map' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->uuid = 'fb22c802-aaa5-97e4-c15c-afe5a02c3a5e';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-03fa5ad5-0ce0-6bd4-e9ea-33076e1b3314';
    $pane->panel = 'body';
    $pane->type = 'views';
    $pane->subtype = 'accomodations_list';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '5',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block',
      'override_title' => 1,
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
    $pane->uuid = '03fa5ad5-0ce0-6bd4-e9ea-33076e1b3314';
    $display->content['new-03fa5ad5-0ce0-6bd4-e9ea-33076e1b3314'] = $pane;
    $display->panels['body'][0] = 'new-03fa5ad5-0ce0-6bd4-e9ea-33076e1b3314';
    $pane = new stdClass();
    $pane->pid = 'new-e8f9af96-83fa-7524-fde6-0139c940d4ed';
    $pane->panel = 'map';
    $pane->type = 'views';
    $pane->subtype = 'accommodations_map';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_pager_settings' => 0,
      'use_pager' => 0,
      'nodes_per_page' => '5',
      'pager_id' => '0',
      'offset' => '0',
      'more_link' => 0,
      'feed_icons' => 0,
      'panel_args' => 0,
      'link_to_view' => 0,
      'args' => '',
      'url' => '',
      'display' => 'block',
      'override_title' => 1,
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
    $pane->uuid = 'e8f9af96-83fa-7524-fde6-0139c940d4ed';
    $display->content['new-e8f9af96-83fa-7524-fde6-0139c940d4ed'] = $pane;
    $display->panels['map'][0] = 'new-e8f9af96-83fa-7524-fde6-0139c940d4ed';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = '0';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['accomodation'] = $page;

  return $pages;

}
