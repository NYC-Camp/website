<?php
/**
 * @file
 * queues_workbenchs.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function queues_workbench_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'queues_revision_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'queues_revision';
  $view->human_name = 'Queues Revision list';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Queues Revision list';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer queue';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['row_class'] = 'state-flow--is-published--[is_published_1] state-[state]';
  $handler->display->display_options['style_options']['columns'] = array(
    'vid' => 'vid',
    'title_1' => 'title_1',
    'state' => 'state',
    'timestamp' => 'timestamp',
    'log' => 'log',
    'history_list' => 'history_list',
    'link' => 'link',
    'state_flow_events_form' => 'state_flow_events_form',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'vid' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'state' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'timestamp' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'log' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'history_list' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'state_flow_events_form' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No revisions available.';
  $handler->display->display_options['empty']['area']['format'] = 'wysiwyg_mini';
  /* Relationship: Queues revision: Queues */
  $handler->display->display_options['relationships']['vid']['id'] = 'vid';
  $handler->display->display_options['relationships']['vid']['table'] = 'queues_revision';
  $handler->display->display_options['relationships']['vid']['field'] = 'vid';
  /* Relationship: State Flow States: State Flow History Entity */
  $handler->display->display_options['relationships']['hid']['id'] = 'hid';
  $handler->display->display_options['relationships']['hid']['table'] = 'state_flow_states';
  $handler->display->display_options['relationships']['hid']['field'] = 'hid';
  /* Field: Queues revision: Vid */
  $handler->display->display_options['fields']['vid']['id'] = 'vid';
  $handler->display->display_options['fields']['vid']['table'] = 'queues_revision';
  $handler->display->display_options['fields']['vid']['field'] = 'vid';
  /* Field: Queues revision: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'queues_revision';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['alter']['path'] = '/admin/content/queues/manage/[qid]';
  /* Field: State Flow History Record: State */
  $handler->display->display_options['fields']['state']['id'] = 'state';
  $handler->display->display_options['fields']['state']['table'] = 'state_flow_history';
  $handler->display->display_options['fields']['state']['field'] = 'state';
  $handler->display->display_options['fields']['state']['relationship'] = 'hid';
  $handler->display->display_options['fields']['state']['label'] = 'Status';
  $handler->display->display_options['fields']['state']['element_type'] = 'div';
  /* Field: State Flow History Record: Timestamp */
  $handler->display->display_options['fields']['timestamp_1']['id'] = 'timestamp_1';
  $handler->display->display_options['fields']['timestamp_1']['table'] = 'state_flow_history';
  $handler->display->display_options['fields']['timestamp_1']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp_1']['relationship'] = 'hid';
  $handler->display->display_options['fields']['timestamp_1']['label'] = 'last updated';
  $handler->display->display_options['fields']['timestamp_1']['date_format'] = 'edit_date';
  /* Field: State Flow History Record: State Change Log */
  $handler->display->display_options['fields']['log']['id'] = 'log';
  $handler->display->display_options['fields']['log']['table'] = 'state_flow_history';
  $handler->display->display_options['fields']['log']['field'] = 'log';
  $handler->display->display_options['fields']['log']['label'] = 'History';
  $handler->display->display_options['fields']['log']['exclude'] = TRUE;
  /* Field: State Flow States: History list */
  $handler->display->display_options['fields']['history_list']['id'] = 'history_list';
  $handler->display->display_options['fields']['history_list']['table'] = 'state_flow_states';
  $handler->display->display_options['fields']['history_list']['field'] = 'history_list';
  $handler->display->display_options['fields']['history_list']['label'] = 'History';
  $handler->display->display_options['fields']['history_list']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['history_list']['alter']['text'] = '[history_list]';
  /* Field: Queues revision: Revision Operation Links */
  $handler->display->display_options['fields']['link']['id'] = 'link';
  $handler->display->display_options['fields']['link']['table'] = 'queues_revision';
  $handler->display->display_options['fields']['link']['field'] = 'link';
  $handler->display->display_options['fields']['link']['label'] = 'Operations';
  $handler->display->display_options['fields']['link']['element_label_colon'] = FALSE;
  /* Field: State Flow States: state flow events form */
  $handler->display->display_options['fields']['state_flow_events_form']['id'] = 'state_flow_events_form';
  $handler->display->display_options['fields']['state_flow_events_form']['table'] = 'state_flow_states';
  $handler->display->display_options['fields']['state_flow_events_form']['field'] = 'state_flow_events_form';
  $handler->display->display_options['fields']['state_flow_events_form']['active_revision_handling'] = 'active';
  /* Sort criterion: State Flow States: Timestamp */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'state_flow_states';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
  /* Contextual filter: Queues revision: Qid */
  $handler->display->display_options['arguments']['qid']['id'] = 'qid';
  $handler->display->display_options['arguments']['qid']['table'] = 'queues_revision';
  $handler->display->display_options['arguments']['qid']['field'] = 'qid';
  $handler->display->display_options['arguments']['qid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['qid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['qid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['qid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['qid']['summary_options']['items_per_page'] = '25';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/content/queues/manage/%/revisions-state-flow-states';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Revisions';
  $handler->display->display_options['menu']['description'] = 'each vid and its state';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  $export['queues_revision_list'] = $view;

  return $export;
}
