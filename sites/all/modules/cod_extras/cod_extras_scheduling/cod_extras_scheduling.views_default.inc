<?php
/**
 * @file
 * cod_extras_scheduling.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cod_extras_scheduling_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'admin_schedling_slots';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Admin - Schedling Slots';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '<none>';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '100';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_schedule_slot_conf_day',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
    1 => array(
      'field' => 'field_room_building',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
    2 => array(
      'field' => 'field_schedule_slot_room',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['row_class'] = 'schedule-slot';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<a href="/node/add/schedule-slot">Create a Schedule Slot</a>';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_schedule_slot_sch_tim_slot_target_id']['id'] = 'field_schedule_slot_sch_tim_slot_target_id';
  $handler->display->display_options['relationships']['field_schedule_slot_sch_tim_slot_target_id']['table'] = 'field_data_field_schedule_slot_sch_tim_slot';
  $handler->display->display_options['relationships']['field_schedule_slot_sch_tim_slot_target_id']['field'] = 'field_schedule_slot_sch_tim_slot_target_id';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_schedule_slot_room_target_id']['id'] = 'field_schedule_slot_room_target_id';
  $handler->display->display_options['relationships']['field_schedule_slot_room_target_id']['table'] = 'field_data_field_schedule_slot_room';
  $handler->display->display_options['relationships']['field_schedule_slot_room_target_id']['field'] = 'field_schedule_slot_room_target_id';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['exclude'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['text'] = 'Edit';
  /* Field: Content: Conference Day */
  $handler->display->display_options['fields']['field_schedule_slot_conf_day']['id'] = 'field_schedule_slot_conf_day';
  $handler->display->display_options['fields']['field_schedule_slot_conf_day']['table'] = 'field_data_field_schedule_slot_conf_day';
  $handler->display->display_options['fields']['field_schedule_slot_conf_day']['field'] = 'field_schedule_slot_conf_day';
  $handler->display->display_options['fields']['field_schedule_slot_conf_day']['label'] = '';
  $handler->display->display_options['fields']['field_schedule_slot_conf_day']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_schedule_slot_conf_day']['element_type'] = 'h2';
  $handler->display->display_options['fields']['field_schedule_slot_conf_day']['element_class'] = 'pane-title';
  $handler->display->display_options['fields']['field_schedule_slot_conf_day']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_schedule_slot_conf_day']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Building */
  $handler->display->display_options['fields']['field_room_building']['id'] = 'field_room_building';
  $handler->display->display_options['fields']['field_room_building']['table'] = 'field_data_field_room_building';
  $handler->display->display_options['fields']['field_room_building']['field'] = 'field_room_building';
  $handler->display->display_options['fields']['field_room_building']['relationship'] = 'field_schedule_slot_room_target_id';
  $handler->display->display_options['fields']['field_room_building']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_room_building']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Room */
  $handler->display->display_options['fields']['field_schedule_slot_room']['id'] = 'field_schedule_slot_room';
  $handler->display->display_options['fields']['field_schedule_slot_room']['table'] = 'field_data_field_schedule_slot_room';
  $handler->display->display_options['fields']['field_schedule_slot_room']['field'] = 'field_schedule_slot_room';
  $handler->display->display_options['fields']['field_schedule_slot_room']['label'] = '';
  $handler->display->display_options['fields']['field_schedule_slot_room']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_schedule_slot_room']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_schedule_slot_room']['alter']['text'] = '[field_schedule_slot_room] Room';
  $handler->display->display_options['fields']['field_schedule_slot_room']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_schedule_slot_room']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Time Slot */
  $handler->display->display_options['fields']['field_schedule_slot_sch_tim_slot']['id'] = 'field_schedule_slot_sch_tim_slot';
  $handler->display->display_options['fields']['field_schedule_slot_sch_tim_slot']['table'] = 'field_data_field_schedule_slot_sch_tim_slot';
  $handler->display->display_options['fields']['field_schedule_slot_sch_tim_slot']['field'] = 'field_schedule_slot_sch_tim_slot';
  $handler->display->display_options['fields']['field_schedule_slot_sch_tim_slot']['label'] = '';
  $handler->display->display_options['fields']['field_schedule_slot_sch_tim_slot']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_schedule_slot_sch_tim_slot']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_schedule_slot_sch_tim_slot']['alter']['text'] = '[field_schedule_slot_sch_tim_slot] ([edit_node])';
  $handler->display->display_options['fields']['field_schedule_slot_sch_tim_slot']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_schedule_slot_sch_tim_slot']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Scheduled Session/Event */
  $handler->display->display_options['fields']['field_schedule_slot_session_evnt']['id'] = 'field_schedule_slot_session_evnt';
  $handler->display->display_options['fields']['field_schedule_slot_session_evnt']['table'] = 'field_data_field_schedule_slot_session_evnt';
  $handler->display->display_options['fields']['field_schedule_slot_session_evnt']['field'] = 'field_schedule_slot_session_evnt';
  $handler->display->display_options['fields']['field_schedule_slot_session_evnt']['label'] = '';
  $handler->display->display_options['fields']['field_schedule_slot_session_evnt']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_schedule_slot_session_evnt']['alter']['text'] = '<div class="scheduled">
<div>[field_schedule_slot_sch_tim_slot]</div>
<div>[field_schedule_slot_session_evnt]</div>
</div>';
  $handler->display->display_options['fields']['field_schedule_slot_session_evnt']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_schedule_slot_session_evnt']['empty'] = '<div class="unscheduled">
<div>[field_schedule_slot_sch_tim_slot]</div>
<div>No Session Scheduled</div>
</div>';
  $handler->display->display_options['fields']['field_schedule_slot_session_evnt']['type'] = 'entityreference_entity_view';
  $handler->display->display_options['fields']['field_schedule_slot_session_evnt']['settings'] = array(
    'view_mode' => 'listing',
    'links' => 1,
  );
  /* Sort criterion: Content: Conference Day (field_schedule_slot_conf_day) */
  $handler->display->display_options['sorts']['field_schedule_slot_conf_day_target_id']['id'] = 'field_schedule_slot_conf_day_target_id';
  $handler->display->display_options['sorts']['field_schedule_slot_conf_day_target_id']['table'] = 'field_data_field_schedule_slot_conf_day';
  $handler->display->display_options['sorts']['field_schedule_slot_conf_day_target_id']['field'] = 'field_schedule_slot_conf_day_target_id';
  /* Sort criterion: Content: Room (field_schedule_slot_room) */
  $handler->display->display_options['sorts']['field_schedule_slot_room_target_id']['id'] = 'field_schedule_slot_room_target_id';
  $handler->display->display_options['sorts']['field_schedule_slot_room_target_id']['table'] = 'field_data_field_schedule_slot_room';
  $handler->display->display_options['sorts']['field_schedule_slot_room_target_id']['field'] = 'field_schedule_slot_room_target_id';
  /* Sort criterion: Draggableviews: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'draggableviews_structure';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['relationship'] = 'field_schedule_slot_sch_tim_slot_target_id';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_view'] = 'admin_manage_schedule_time_slots:block';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_arguments'] = 'none';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_new_items_bottom_list'] = 1;
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
    'schedule_slot' => 'schedule_slot',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['admin_schedling_slots'] = $view;

  $view = new view();
  $view->name = 'admin_sessions_for_scheduling';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Admin - Sessions for Scheduling';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Sessions for Scheduling';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'ds';
  $handler->display->display_options['row_options']['view_mode'] = 'admin_scheduling';
  $handler->display->display_options['row_options']['load_comments'] = 0;
  $handler->display->display_options['row_options']['alternating'] = 0;
  $handler->display->display_options['row_options']['advanced'] = 0;
  $handler->display->display_options['row_options']['delta_fieldset']['delta_fields'] = array();
  $handler->display->display_options['row_options']['default_fieldset']['view_mode'] = 'admin_scheduling';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Presenters */
  $handler->display->display_options['fields']['field_presenters']['id'] = 'field_presenters';
  $handler->display->display_options['fields']['field_presenters']['table'] = 'field_data_field_presenters';
  $handler->display->display_options['fields']['field_presenters']['field'] = 'field_presenters';
  $handler->display->display_options['fields']['field_presenters']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_presenters']['delta_offset'] = '0';
  /* Field: Content: Track(s) */
  $handler->display->display_options['fields']['field_session_track']['id'] = 'field_session_track';
  $handler->display->display_options['fields']['field_session_track']['table'] = 'field_data_field_session_track';
  $handler->display->display_options['fields']['field_session_track']['field'] = 'field_session_track';
  $handler->display->display_options['fields']['field_session_track']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_session_track']['delta_offset'] = '0';
  /* Field: Content: Level */
  $handler->display->display_options['fields']['field_experience']['id'] = 'field_experience';
  $handler->display->display_options['fields']['field_experience']['table'] = 'field_data_field_experience';
  $handler->display->display_options['fields']['field_experience']['field'] = 'field_experience';
  $handler->display->display_options['fields']['field_experience']['label'] = 'Experience Level';
  /* Field: Content: Session Type */
  $handler->display->display_options['fields']['field_session_other_info']['id'] = 'field_session_other_info';
  $handler->display->display_options['fields']['field_session_other_info']['table'] = 'field_data_field_session_other_info';
  $handler->display->display_options['fields']['field_session_other_info']['field'] = 'field_session_other_info';
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
    'schedule_item' => 'schedule_item',
    'session' => 'session',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    8 => 0,
    12 => 0,
    7 => 0,
    6 => 0,
    5 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
    4 => 0,
    3 => 0,
    13 => 0,
    14 => 0,
    15 => 0,
    16 => 0,
    17 => 0,
    18 => 0,
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    8 => 0,
    12 => 0,
    7 => 0,
    6 => 0,
    5 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
    4 => 0,
    3 => 0,
    13 => 0,
    14 => 0,
    15 => 0,
    16 => 0,
    17 => 0,
    18 => 0,
  );
  /* Filter criterion: Content: Status (field_accepted) */
  $handler->display->display_options['filters']['field_accepted_value']['id'] = 'field_accepted_value';
  $handler->display->display_options['filters']['field_accepted_value']['table'] = 'field_data_field_accepted';
  $handler->display->display_options['filters']['field_accepted_value']['field'] = 'field_accepted_value';
  $handler->display->display_options['filters']['field_accepted_value']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['field_accepted_value']['group'] = 1;
  $handler->display->display_options['filters']['field_accepted_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_accepted_value']['expose']['operator_id'] = 'field_accepted_value_op';
  $handler->display->display_options['filters']['field_accepted_value']['expose']['label'] = 'Accepted?';
  $handler->display->display_options['filters']['field_accepted_value']['expose']['operator'] = 'field_accepted_value_op';
  $handler->display->display_options['filters']['field_accepted_value']['expose']['identifier'] = 'field_accepted_value';
  $handler->display->display_options['filters']['field_accepted_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    8 => 0,
    12 => 0,
    7 => 0,
    6 => 0,
    5 => 0,
    9 => 0,
    10 => 0,
    11 => 0,
    4 => 0,
    3 => 0,
    13 => 0,
    14 => 0,
    15 => 0,
    16 => 0,
    17 => 0,
    18 => 0,
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['admin_sessions_for_scheduling'] = $view;

  return $export;
}
