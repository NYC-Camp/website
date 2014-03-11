<?php

/**
 * @file
 * Provide views data and handlers for queues.module.
 *
 * @ingroup views_module_handlers
 */

/**
 * Implements hook_views_default_views().
 */
function queues_views_default_views() {
  $views = array();

  $view = new view();
  $view->name = 'queues_listing';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'queues';
  $view->human_name = 'Queues Listing';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Queues Listing';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer queue';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'qid' => 'qid',
    'title_1' => 'title_1',
    'type' => 'type',
    'published' => 'published',
    'edit_link' => 'edit_link',
    'status' => 'status',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'qid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'published' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Queue: Queue ID */
  $handler->display->display_options['fields']['qid']['id'] = 'qid';
  $handler->display->display_options['fields']['qid']['table'] = 'queues';
  $handler->display->display_options['fields']['qid']['field'] = 'qid';
  $handler->display->display_options['fields']['qid']['exclude'] = TRUE;
  /* Field: Queue: Label */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'queues';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['label'] = 'Title';
  /* Field: Queue: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'queues';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  /* Field: Queue: Publish State */
  $handler->display->display_options['fields']['published']['id'] = 'published';
  $handler->display->display_options['fields']['published']['table'] = 'queues';
  $handler->display->display_options['fields']['published']['field'] = 'published';
  $handler->display->display_options['fields']['published']['label'] = 'Status';
  /* Field: Queue: Operation Links */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'queues';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['label'] = 'Operations';
  /* Field: Queue: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'queues';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['exclude'] = TRUE;
  /* Sort criterion: Queues revision: Qid */
  $handler->display->display_options['sorts']['qid']['id'] = 'qid';
  $handler->display->display_options['sorts']['qid']['table'] = 'queues_revision';
  $handler->display->display_options['sorts']['qid']['field'] = 'qid';
  $handler->display->display_options['sorts']['qid']['order'] = 'DESC';
  /* Filter criterion: Queue: Label */
  $handler->display->display_options['filters']['title_1']['id'] = 'title_1';
  $handler->display->display_options['filters']['title_1']['table'] = 'queues';
  $handler->display->display_options['filters']['title_1']['field'] = 'title';
  $handler->display->display_options['filters']['title_1']['operator'] = 'contains';
  $handler->display->display_options['filters']['title_1']['group'] = 1;
  $handler->display->display_options['filters']['title_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title_1']['expose']['operator_id'] = 'title_1_op';
  $handler->display->display_options['filters']['title_1']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title_1']['expose']['operator'] = 'title_1_op';
  $handler->display->display_options['filters']['title_1']['expose']['identifier'] = 'title_1';
  $handler->display->display_options['filters']['title_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
  );
  /* Filter criterion: Queue: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'queues';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['filters']['type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
    6 => 0,
    7 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/content/queues';
  $views['queues_listing'] = $view;

  return $views;
}

/**
 * Implements hook_views_data_alter().
 */
function queues_views_data_alter(&$data) {
  // We only add Revision support, The regular Table is handled by Entity API.

  // Define the base group of this table.
  $data['queues_revision']['table']['entity type'] = 'queues';
  $data['queues_revision']['table']['group']  = t('Queues revision');

  // Advertise this table as a possible base table
  $data['queues_revision']['table']['base'] = array(
    'field' => 'vid',
    'title' => t('Queues revision'),
    'help' => t('Queues revision is a history of changes to queues.'),
    'defaults' => array(
      'field' => 'title',
    ),
  );

  // For other base tables, explain how we join.
  $data['queues_revision']['table']['join'] = array(
    // Directly links to queue table.
    'queues' => array(
      'left_field' => 'vid',
      'field' => 'vid',
    ),
  );
  $data['queues_revision']['table']['default_relationship'] = array(
    'queues' => array(
      'table' => 'queues',
      'field' => 'qid',
    ),
  );

  // Queues qid.
  $data['queues_revision']['qid'] = array(
    'title' => t('Qid'),
    // The help that appears on the UI.
    'help' => t('The revision QID of the Queues revision.'),
    // Information for displaying the qid.
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'field' => array(
      'click sortable' => TRUE,
    ),
    // Information for accepting a qid as an argument.
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'click sortable' => TRUE,
      'numeric' => TRUE,
    ),
    // Information for accepting a qid as a filter.
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    // Information for sorting on a qid.
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'queues',
      'base field' => 'qid',
      'title' => t('Queues'),
      'label' => t('Get the actual queues from a queues revision.'),
    ),
  );

  // Queues vid.
  $data['queues_revision']['vid'] = array(
    'title' => t('Vid'),
    // The help that appears on the UI.
    'help' => t('The revision ID of the queues revision.'),
    // Information for displaying the vid.
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    // Information for accepting a vid as an argument.
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
      'click sortable' => TRUE,
      'numeric' => TRUE,
    ),
    // Information for accepting a vid as a filter.
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    // Information for sorting on a vid.
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'queues',
      'base field' => 'vid',
      'title' => t('Queues'),
      'label' => t('Get the actual Queue from a Queue revision.'),
    ),
  );

  // Queues title
  $data['queues_revision']['title'] = array(
    'title' => t('Title'), // The item it appears as on the UI,
    'help' => t('The content title.'), // The help that appears on the UI,
    // Information for displaying a title as a field
    'field' => array(
      'field' => 'title', // the real field
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['queues']['edit_link'] = array(
    'field' => array(
      'title' => t('Operation Links'),
      'help' => t('Provide an Operation link widget for Queues.'),
      'handler' => 'queues_views_handler_field_queue_operations',
    ),
  );

  $data['queues']['published'] = array(
    'field' => array(
      'title' => t('Publish State'),
      'help' => t('Published or unpublished?'),
      'handler' => 'queues_views_handler_publish_state',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  $data['queues_revision']['link'] = array(
    'field' => array(
      'title' => t('Revision Operation Links'),
      'help' => t('Provide an Operation link widget for Queues.'),
      'handler' => 'queues_views_handler_field_operations',
    ),
  );


  return $data;
}
