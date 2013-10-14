<?php
/**
 * @file
 * cod_bof.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cod_bof_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'cod_bof_schedule';
  $view->description = 'Conference Organizing Scheduler Admin View';
  $view->tag = 'cod';
  $view->base_table = 'node';
  $view->human_name = 'cod_bof_schedule';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'BoFs';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'quicktabs';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_slot_datetime',
      'rendered' => 1,
      'rendered_strip' => 1,
    ),
  );
  $handler->display->display_options['style_options']['tab_style'] = 'Zen';
  $handler->display->display_options['style_options']['tab_title_field'] = 'field_slot_datetime';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  /* Field: Content: Date and time */
  $handler->display->display_options['fields']['field_slot_datetime']['id'] = 'field_slot_datetime';
  $handler->display->display_options['fields']['field_slot_datetime']['table'] = 'field_data_field_slot_datetime';
  $handler->display->display_options['fields']['field_slot_datetime']['field'] = 'field_slot_datetime';
  $handler->display->display_options['fields']['field_slot_datetime']['label'] = '';
  $handler->display->display_options['fields']['field_slot_datetime']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_slot_datetime']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_slot_datetime']['settings'] = array(
    'format_type' => 'date_no_time_',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Date and time */
  $handler->display->display_options['fields']['field_slot_datetime_1']['id'] = 'field_slot_datetime_1';
  $handler->display->display_options['fields']['field_slot_datetime_1']['table'] = 'field_data_field_slot_datetime';
  $handler->display->display_options['fields']['field_slot_datetime_1']['field'] = 'field_slot_datetime';
  $handler->display->display_options['fields']['field_slot_datetime_1']['label'] = '';
  $handler->display->display_options['fields']['field_slot_datetime_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_slot_datetime_1']['settings'] = array(
    'format_type' => 'time_slot',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Global: View */
  $handler->display->display_options['fields']['view']['id'] = 'view';
  $handler->display->display_options['fields']['view']['table'] = 'views';
  $handler->display->display_options['fields']['view']['field'] = 'view';
  $handler->display->display_options['fields']['view']['label'] = '';
  $handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view']['view'] = 'cod_bof_schedule_entity';
  $handler->display->display_options['fields']['view']['display'] = 'block';
  $handler->display->display_options['fields']['view']['arguments'] = '[!nid]/bof_session';
  /* Sort criterion: Content: Date and time (field_slot_datetime) */
  $handler->display->display_options['sorts']['field_slot_datetime_value']['id'] = 'field_slot_datetime_value';
  $handler->display->display_options['sorts']['field_slot_datetime_value']['table'] = 'field_data_field_slot_datetime';
  $handler->display->display_options['sorts']['field_slot_datetime_value']['field'] = 'field_slot_datetime_value';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'time_slot' => 'time_slot',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['required'] = TRUE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['path'] = 'node/%/program/schedule/bofs';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'BoFs';
  $handler->display->display_options['menu']['description'] = 'Birds of a Feather Sessions';
  $handler->display->display_options['menu']['weight'] = '4';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Broken/missing handler */
  $handler->display->display_options['arguments']['field_session_room_target_id']['id'] = 'field_session_room_target_id';
  $handler->display->display_options['arguments']['field_session_room_target_id']['table'] = 'field_data_field_session_room';
  $handler->display->display_options['arguments']['field_session_room_target_id']['field'] = 'field_session_room_target_id';
  $handler->display->display_options['arguments']['field_session_room_target_id']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_session_room_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_session_room_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_session_room_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_session_room_target_id']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Broken/missing handler */
  $handler->display->display_options['arguments']['field_session_slot_target_id']['id'] = 'field_session_slot_target_id';
  $handler->display->display_options['arguments']['field_session_slot_target_id']['table'] = 'field_data_field_session_slot';
  $handler->display->display_options['arguments']['field_session_slot_target_id']['field'] = 'field_session_slot_target_id';
  $handler->display->display_options['arguments']['field_session_slot_target_id']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['field_session_slot_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_session_slot_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_session_slot_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_session_slot_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'bof_session' => 'bof_session',
  );

  /* Display: Block: BoF Listing */
  $handler = $view->new_display('block', 'Block: BoF Listing', 'block_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'BoFs';
  $handler->display->display_options['display_description'] = 'These are BoFs generated from timeslots';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['footer'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_session_timeslot_target_id']['id'] = 'field_session_timeslot_target_id';
  $handler->display->display_options['relationships']['field_session_timeslot_target_id']['table'] = 'field_data_field_session_timeslot';
  $handler->display->display_options['relationships']['field_session_timeslot_target_id']['field'] = 'field_session_timeslot_target_id';
  $handler->display->display_options['relationships']['field_session_timeslot_target_id']['label'] = 'Room/Timeslot/Allowed Types Entity';
  $handler->display->display_options['relationships']['field_session_timeslot_target_id']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Field collection item: Field collection item ID */
  $handler->display->display_options['arguments']['item_id']['id'] = 'item_id';
  $handler->display->display_options['arguments']['item_id']['table'] = 'field_collection_item';
  $handler->display->display_options['arguments']['item_id']['field'] = 'item_id';
  $handler->display->display_options['arguments']['item_id']['relationship'] = 'field_session_timeslot_target_id';
  $handler->display->display_options['arguments']['item_id']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['item_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['item_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['item_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['item_id']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Field collection item: Allowed Schedule Types (field_slot_types_allowed) */
  $handler->display->display_options['arguments']['field_slot_types_allowed_value']['id'] = 'field_slot_types_allowed_value';
  $handler->display->display_options['arguments']['field_slot_types_allowed_value']['table'] = 'field_data_field_slot_types_allowed';
  $handler->display->display_options['arguments']['field_slot_types_allowed_value']['field'] = 'field_slot_types_allowed_value';
  $handler->display->display_options['arguments']['field_slot_types_allowed_value']['relationship'] = 'field_session_timeslot_target_id';
  $handler->display->display_options['arguments']['field_slot_types_allowed_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_slot_types_allowed_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'bof_session' => 'bof_session',
  );
  $export['cod_bof_schedule'] = $view;

  $view = new view();
  $view->name = 'cod_bof_schedule_entity';
  $view->description = 'The scheduling entity that renders Timeslot Combos for BoFs';
  $view->tag = 'default';
  $view->base_table = 'field_collection_item';
  $view->human_name = 'cod_bof_schedule_entity';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'cod_bof_schedule_entity';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '60';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '60';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Field collection item: Entity with the Allowed Slot Types (field_room_slots_types_allowed) */
  $handler->display->display_options['relationships']['field_room_slots_types_allowed_node']['id'] = 'field_room_slots_types_allowed_node';
  $handler->display->display_options['relationships']['field_room_slots_types_allowed_node']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_room_slots_types_allowed_node']['field'] = 'field_room_slots_types_allowed_node';
  $handler->display->display_options['relationships']['field_room_slots_types_allowed_node']['required'] = TRUE;
  /* Field: Field collection item: Field collection item ID */
  $handler->display->display_options['fields']['item_id']['id'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['item_id']['field'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['label'] = '';
  $handler->display->display_options['fields']['item_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['item_id']['element_label_colon'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'field_room_slots_types_allowed_node';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_room_slots_types_allowed_node';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Global: View */
  $handler->display->display_options['fields']['view']['id'] = 'view';
  $handler->display->display_options['fields']['view']['table'] = 'views';
  $handler->display->display_options['fields']['view']['field'] = 'view';
  $handler->display->display_options['fields']['view']['label'] = '';
  $handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['view']['view'] = 'cod_bof_schedule';
  $handler->display->display_options['fields']['view']['display'] = 'block_2';
  $handler->display->display_options['fields']['view']['arguments'] = '[!item_id]/!2';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['relationship'] = 'field_room_slots_types_allowed_node';
  /* Contextual filter: Field collection item: Time Slot (field_slot_types_time_slot) */
  $handler->display->display_options['arguments']['field_slot_types_time_slot_target_id']['id'] = 'field_slot_types_time_slot_target_id';
  $handler->display->display_options['arguments']['field_slot_types_time_slot_target_id']['table'] = 'field_data_field_slot_types_time_slot';
  $handler->display->display_options['arguments']['field_slot_types_time_slot_target_id']['field'] = 'field_slot_types_time_slot_target_id';
  $handler->display->display_options['arguments']['field_slot_types_time_slot_target_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_slot_types_time_slot_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_slot_types_time_slot_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_slot_types_time_slot_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_slot_types_time_slot_target_id']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Field collection item: Allowed Schedule Types (field_slot_types_allowed) */
  $handler->display->display_options['arguments']['field_slot_types_allowed_value']['id'] = 'field_slot_types_allowed_value';
  $handler->display->display_options['arguments']['field_slot_types_allowed_value']['table'] = 'field_data_field_slot_types_allowed';
  $handler->display->display_options['arguments']['field_slot_types_allowed_value']['field'] = 'field_slot_types_allowed_value';
  $handler->display->display_options['arguments']['field_slot_types_allowed_value']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_slot_types_allowed_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_slot_types_allowed_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_slot_types_allowed_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_slot_types_allowed_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_slot_types_allowed_value']['limit'] = '0';
  $handler->display->display_options['arguments']['field_slot_types_allowed_value']['break_phrase'] = TRUE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['relationship'] = 'field_room_slots_types_allowed_node';
  $handler->display->display_options['filters']['status']['value'] = '1';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;

  /* Display: Bof Grid Block */
  $handler = $view->new_display('block', 'Bof Grid Block', 'block_1');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $export['cod_bof_schedule_entity'] = $view;

  return $export;
}
