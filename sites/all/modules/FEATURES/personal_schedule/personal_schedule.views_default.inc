<?php
/**
 * @file
 * personal_schedule.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function personal_schedule_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'personal_schedule';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Personal schedule';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Personal schedule';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    2 => '2',
  );
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '60';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '60';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['disable_sql_rewrite'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_dates_1',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'There are currently no sessions in your schedule. Look for and click "Add this session to your schedule" on any accepted session to add the session here.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Flags: session_schedule */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['label'] = 'schedule';
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'session_schedule';
  $handler->display->display_options['relationships']['flag_content_rel']['user_scope'] = 'any';
  /* Relationship: Flags: User */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'flag_content';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['uid']['label'] = 'Schedule user';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_session_time_target_id']['id'] = 'field_session_time_target_id';
  $handler->display->display_options['relationships']['field_session_time_target_id']['table'] = 'field_data_field_session_time';
  $handler->display->display_options['relationships']['field_session_time_target_id']['field'] = 'field_session_time_target_id';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['relationships']['uid_1']['table'] = 'node';
  $handler->display->display_options['relationships']['uid_1']['field'] = 'uid';
  /* Field: Content: Date and time */
  $handler->display->display_options['fields']['field_slot_datetime']['id'] = 'field_slot_datetime';
  $handler->display->display_options['fields']['field_slot_datetime']['table'] = 'field_data_field_slot_datetime';
  $handler->display->display_options['fields']['field_slot_datetime']['field'] = 'field_slot_datetime';
  $handler->display->display_options['fields']['field_slot_datetime']['relationship'] = 'field_session_time_target_id';
  $handler->display->display_options['fields']['field_slot_datetime']['label'] = '';
  $handler->display->display_options['fields']['field_slot_datetime']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_slot_datetime']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_slot_datetime']['settings'] = array(
    'format_type' => 'day',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Session Time(s) */
  $handler->display->display_options['fields']['field_session_time']['id'] = 'field_session_time';
  $handler->display->display_options['fields']['field_session_time']['table'] = 'field_data_field_session_time';
  $handler->display->display_options['fields']['field_session_time']['field'] = 'field_session_time';
  $handler->display->display_options['fields']['field_session_time']['label'] = '';
  $handler->display->display_options['fields']['field_session_time']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_session_time']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_session_time']['delta_offset'] = '0';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Room assignment */
  $handler->display->display_options['fields']['field_room_assignment']['id'] = 'field_room_assignment';
  $handler->display->display_options['fields']['field_room_assignment']['table'] = 'field_data_field_room_assignment';
  $handler->display->display_options['fields']['field_room_assignment']['field'] = 'field_room_assignment';
  $handler->display->display_options['fields']['field_room_assignment']['label'] = '';
  $handler->display->display_options['fields']['field_room_assignment']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_room_assignment']['alter']['text'] = 'Location: <a href="/node/[field_room_assignment-target_id]">[field_room_assignment]</a>';
  $handler->display->display_options['fields']['field_room_assignment']['alter']['path'] = '[field_room_assignment]';
  $handler->display->display_options['fields']['field_room_assignment']['alter']['replace_spaces'] = TRUE;
  $handler->display->display_options['fields']['field_room_assignment']['alter']['path_case'] = 'lower';
  $handler->display->display_options['fields']['field_room_assignment']['alter']['alt'] = '[field_room_assignment]';
  $handler->display->display_options['fields']['field_room_assignment']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_room_assignment']['settings'] = array(
    'link' => 0,
  );
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid_1';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Content: Day */
  $handler->display->display_options['fields']['field_which_day']['id'] = 'field_which_day';
  $handler->display->display_options['fields']['field_which_day']['table'] = 'field_data_field_which_day';
  $handler->display->display_options['fields']['field_which_day']['field'] = 'field_which_day';
  $handler->display->display_options['fields']['field_which_day']['label'] = '';
  $handler->display->display_options['fields']['field_which_day']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_which_day']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_which_day']['delta_offset'] = '0';
  /* Sort criterion: Content: Date and time -  start date (field_slot_datetime) */
  $handler->display->display_options['sorts']['field_slot_datetime_value']['id'] = 'field_slot_datetime_value';
  $handler->display->display_options['sorts']['field_slot_datetime_value']['table'] = 'field_data_field_slot_datetime';
  $handler->display->display_options['sorts']['field_slot_datetime_value']['field'] = 'field_slot_datetime_value';
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['arguments']['uid_1']['table'] = 'users';
  $handler->display->display_options['arguments']['uid_1']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid_1']['relationship'] = 'uid';
  $handler->display->display_options['arguments']['uid_1']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['uid_1']['title'] = '%1';
  $handler->display->display_options['arguments']['uid_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['uid_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid_1']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Flags: User uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'flag_content';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['uid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['uid']['validate']['type'] = 'php';
  $handler->display->display_options['arguments']['uid']['validate_options']['code'] = 'if($GLOBALS[\'user\']->uid == $argument) {
return TRUE;
} elseif((arg(0) == \'user\' && is_numeric(arg(1)) && arg(2) == \'schedule\')) {
drupal_set_message(t(\'You may view your schedule only. Schedules are not publicly shared.\'), \'warning\');
}
';
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
    'session' => 'session',
  );
  /* Filter criterion: Content: Status (field_accepted) */
  $handler->display->display_options['filters']['field_accepted_value']['id'] = 'field_accepted_value';
  $handler->display->display_options['filters']['field_accepted_value']['table'] = 'field_data_field_accepted';
  $handler->display->display_options['filters']['field_accepted_value']['field'] = 'field_accepted_value';
  $handler->display->display_options['filters']['field_accepted_value']['value'] = array(
    1 => '1',
    4 => '4',
    6 => '6',
    5 => '5',
  );

  /* Display: Sessions */
  $handler = $view->new_display('page', 'Sessions', 'my_schedule');
  $handler->display->display_options['display_description'] = 'The Sessions the user has flagged "Add to your schedule"';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_schedule_slot_conf_day',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'There are currently no sessions in your schedule. Look for and click "Add this session to your schedule" on any accepted session to add the session here.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Flags: session_schedule */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['label'] = 'schedule';
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'session_schedule';
  $handler->display->display_options['relationships']['flag_content_rel']['user_scope'] = 'any';
  /* Relationship: Flags: User */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'flag_content';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['uid']['label'] = 'Schedule user';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_session_time_target_id']['id'] = 'field_session_time_target_id';
  $handler->display->display_options['relationships']['field_session_time_target_id']['table'] = 'field_data_field_session_time';
  $handler->display->display_options['relationships']['field_session_time_target_id']['field'] = 'field_session_time_target_id';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['relationships']['uid_1']['table'] = 'node';
  $handler->display->display_options['relationships']['uid_1']['field'] = 'uid';
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_schedule_slot_session_evnt_node']['id'] = 'reverse_field_schedule_slot_session_evnt_node';
  $handler->display->display_options['relationships']['reverse_field_schedule_slot_session_evnt_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_schedule_slot_session_evnt_node']['field'] = 'reverse_field_schedule_slot_session_evnt_node';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_schedule_slot_room_target_id']['id'] = 'field_schedule_slot_room_target_id';
  $handler->display->display_options['relationships']['field_schedule_slot_room_target_id']['table'] = 'field_data_field_schedule_slot_room';
  $handler->display->display_options['relationships']['field_schedule_slot_room_target_id']['field'] = 'field_schedule_slot_room_target_id';
  $handler->display->display_options['relationships']['field_schedule_slot_room_target_id']['relationship'] = 'reverse_field_schedule_slot_session_evnt_node';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Date and time */
  $handler->display->display_options['fields']['field_slot_datetime']['id'] = 'field_slot_datetime';
  $handler->display->display_options['fields']['field_slot_datetime']['table'] = 'field_data_field_slot_datetime';
  $handler->display->display_options['fields']['field_slot_datetime']['field'] = 'field_slot_datetime';
  $handler->display->display_options['fields']['field_slot_datetime']['relationship'] = 'field_session_time_target_id';
  $handler->display->display_options['fields']['field_slot_datetime']['label'] = '';
  $handler->display->display_options['fields']['field_slot_datetime']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_slot_datetime']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_slot_datetime']['settings'] = array(
    'format_type' => 'day',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Session Time(s) */
  $handler->display->display_options['fields']['field_session_time']['id'] = 'field_session_time';
  $handler->display->display_options['fields']['field_session_time']['table'] = 'field_data_field_session_time';
  $handler->display->display_options['fields']['field_session_time']['field'] = 'field_session_time';
  $handler->display->display_options['fields']['field_session_time']['label'] = '';
  $handler->display->display_options['fields']['field_session_time']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_session_time']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_session_time']['delta_offset'] = '0';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Room assignment */
  $handler->display->display_options['fields']['field_room_assignment']['id'] = 'field_room_assignment';
  $handler->display->display_options['fields']['field_room_assignment']['table'] = 'field_data_field_room_assignment';
  $handler->display->display_options['fields']['field_room_assignment']['field'] = 'field_room_assignment';
  $handler->display->display_options['fields']['field_room_assignment']['label'] = '';
  $handler->display->display_options['fields']['field_room_assignment']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_room_assignment']['alter']['text'] = 'Location: <a href="/node/[field_room_assignment-target_id]">[field_room_assignment]</a>';
  $handler->display->display_options['fields']['field_room_assignment']['alter']['path'] = '[field_room_assignment]';
  $handler->display->display_options['fields']['field_room_assignment']['alter']['replace_spaces'] = TRUE;
  $handler->display->display_options['fields']['field_room_assignment']['alter']['path_case'] = 'lower';
  $handler->display->display_options['fields']['field_room_assignment']['alter']['alt'] = '[field_room_assignment]';
  $handler->display->display_options['fields']['field_room_assignment']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_room_assignment']['settings'] = array(
    'link' => 0,
  );
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid_1';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  /* Field: Content: Day */
  $handler->display->display_options['fields']['field_which_day']['id'] = 'field_which_day';
  $handler->display->display_options['fields']['field_which_day']['table'] = 'field_data_field_which_day';
  $handler->display->display_options['fields']['field_which_day']['field'] = 'field_which_day';
  $handler->display->display_options['fields']['field_which_day']['label'] = '';
  $handler->display->display_options['fields']['field_which_day']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_which_day']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_which_day']['delta_offset'] = '0';
  /* Field: Content: Conference Day */
  $handler->display->display_options['fields']['field_schedule_slot_conf_day']['id'] = 'field_schedule_slot_conf_day';
  $handler->display->display_options['fields']['field_schedule_slot_conf_day']['table'] = 'field_data_field_schedule_slot_conf_day';
  $handler->display->display_options['fields']['field_schedule_slot_conf_day']['field'] = 'field_schedule_slot_conf_day';
  $handler->display->display_options['fields']['field_schedule_slot_conf_day']['relationship'] = 'reverse_field_schedule_slot_session_evnt_node';
  $handler->display->display_options['fields']['field_schedule_slot_conf_day']['label'] = '';
  $handler->display->display_options['fields']['field_schedule_slot_conf_day']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_schedule_slot_conf_day']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_schedule_slot_conf_day']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Time Slot */
  $handler->display->display_options['fields']['field_schedule_slot_sch_tim_slot']['id'] = 'field_schedule_slot_sch_tim_slot';
  $handler->display->display_options['fields']['field_schedule_slot_sch_tim_slot']['table'] = 'field_data_field_schedule_slot_sch_tim_slot';
  $handler->display->display_options['fields']['field_schedule_slot_sch_tim_slot']['field'] = 'field_schedule_slot_sch_tim_slot';
  $handler->display->display_options['fields']['field_schedule_slot_sch_tim_slot']['relationship'] = 'reverse_field_schedule_slot_session_evnt_node';
  $handler->display->display_options['fields']['field_schedule_slot_sch_tim_slot']['label'] = '';
  $handler->display->display_options['fields']['field_schedule_slot_sch_tim_slot']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_schedule_slot_sch_tim_slot']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Building */
  $handler->display->display_options['fields']['field_room_building']['id'] = 'field_room_building';
  $handler->display->display_options['fields']['field_room_building']['table'] = 'field_data_field_room_building';
  $handler->display->display_options['fields']['field_room_building']['field'] = 'field_room_building';
  $handler->display->display_options['fields']['field_room_building']['relationship'] = 'field_schedule_slot_room_target_id';
  $handler->display->display_options['fields']['field_room_building']['label'] = '';
  $handler->display->display_options['fields']['field_room_building']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_room_building']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Room */
  $handler->display->display_options['fields']['field_schedule_slot_room']['id'] = 'field_schedule_slot_room';
  $handler->display->display_options['fields']['field_schedule_slot_room']['table'] = 'field_data_field_schedule_slot_room';
  $handler->display->display_options['fields']['field_schedule_slot_room']['field'] = 'field_schedule_slot_room';
  $handler->display->display_options['fields']['field_schedule_slot_room']['relationship'] = 'reverse_field_schedule_slot_session_evnt_node';
  $handler->display->display_options['fields']['field_schedule_slot_room']['label'] = '';
  $handler->display->display_options['fields']['field_schedule_slot_room']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_schedule_slot_room']['alter']['text'] = 'Room [field_schedule_slot_room]';
  $handler->display->display_options['fields']['field_schedule_slot_room']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_schedule_slot_room']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Time Slot (field_schedule_slot_sch_tim_slot) */
  $handler->display->display_options['sorts']['field_schedule_slot_sch_tim_slot_target_id']['id'] = 'field_schedule_slot_sch_tim_slot_target_id';
  $handler->display->display_options['sorts']['field_schedule_slot_sch_tim_slot_target_id']['table'] = 'field_data_field_schedule_slot_sch_tim_slot';
  $handler->display->display_options['sorts']['field_schedule_slot_sch_tim_slot_target_id']['field'] = 'field_schedule_slot_sch_tim_slot_target_id';
  $handler->display->display_options['sorts']['field_schedule_slot_sch_tim_slot_target_id']['relationship'] = 'reverse_field_schedule_slot_session_evnt_node';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['arguments']['uid_1']['table'] = 'users';
  $handler->display->display_options['arguments']['uid_1']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid_1']['relationship'] = 'uid';
  $handler->display->display_options['arguments']['uid_1']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid_1']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['uid_1']['title'] = '%1\'s sessions';
  $handler->display->display_options['arguments']['uid_1']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['uid_1']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['uid_1']['validate']['type'] = 'php';
  $handler->display->display_options['arguments']['uid_1']['validate_options']['code'] = 'if($GLOBALS[\'user\']->uid == $argument) {
return TRUE;
} elseif((arg(0) == \'user\' && is_numeric(arg(1)) && arg(2) == \'my-sessions\')) {
drupal_set_message(t(\'You may view your sessions only. Your sessions are not publicly shared.\'), \'warning\');
}
';
  /* Contextual filter: Flags: User uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'flag_content';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['uid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['uid']['validate']['type'] = 'php';
  $handler->display->display_options['arguments']['uid']['validate_options']['code'] = 'if($GLOBALS[\'user\']->uid == $argument) {
return TRUE;
} elseif((arg(0) == \'user\' && is_numeric(arg(1)) && arg(2) == \'my-sessions\')) {
drupal_set_message(t(\'You may view your sessions only. Your sessions are not publicly shared.\'), \'warning\');
}
';
  $handler->display->display_options['path'] = 'user/%/my-sessions';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'My Sessions';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Events */
  $handler = $view->new_display('page', 'Events', 'registrations');
  $handler->display->display_options['display_description'] = 'Events the user has registered for.';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_dates_1',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'You are currently not registered for any events or the NYC Camp!
<br><br>
Remember that you must register for NYC Camp to attend. See the registration block below this one to register.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Registration: Node to Registration */
  $handler->display->display_options['relationships']['registration_rel']['id'] = 'registration_rel';
  $handler->display->display_options['relationships']['registration_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['registration_rel']['field'] = 'registration_rel';
  /* Relationship: Registration: User */
  $handler->display->display_options['relationships']['user_uid']['id'] = 'user_uid';
  $handler->display->display_options['relationships']['user_uid']['table'] = 'registration';
  $handler->display->display_options['relationships']['user_uid']['field'] = 'user_uid';
  $handler->display->display_options['relationships']['user_uid']['relationship'] = 'registration_rel';
  /* Relationship: Registration: Registration to Node */
  $handler->display->display_options['relationships']['registration_related_node']['id'] = 'registration_related_node';
  $handler->display->display_options['relationships']['registration_related_node']['table'] = 'registration';
  $handler->display->display_options['relationships']['registration_related_node']['field'] = 'registration_related_node';
  $handler->display->display_options['relationships']['registration_related_node']['relationship'] = 'registration_rel';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_session_time_target_id']['id'] = 'field_session_time_target_id';
  $handler->display->display_options['relationships']['field_session_time_target_id']['table'] = 'field_data_field_session_time';
  $handler->display->display_options['relationships']['field_session_time_target_id']['field'] = 'field_session_time_target_id';
  $handler->display->display_options['relationships']['field_session_time_target_id']['relationship'] = 'registration_related_node';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Date and time */
  $handler->display->display_options['fields']['field_slot_datetime']['id'] = 'field_slot_datetime';
  $handler->display->display_options['fields']['field_slot_datetime']['table'] = 'field_data_field_slot_datetime';
  $handler->display->display_options['fields']['field_slot_datetime']['field'] = 'field_slot_datetime';
  $handler->display->display_options['fields']['field_slot_datetime']['label'] = '';
  $handler->display->display_options['fields']['field_slot_datetime']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_slot_datetime']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_slot_datetime']['settings'] = array(
    'format_type' => 'day',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'registration_related_node';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Room assignment */
  $handler->display->display_options['fields']['field_room_assignment']['id'] = 'field_room_assignment';
  $handler->display->display_options['fields']['field_room_assignment']['table'] = 'field_data_field_room_assignment';
  $handler->display->display_options['fields']['field_room_assignment']['field'] = 'field_room_assignment';
  $handler->display->display_options['fields']['field_room_assignment']['relationship'] = 'registration_related_node';
  $handler->display->display_options['fields']['field_room_assignment']['label'] = '';
  $handler->display->display_options['fields']['field_room_assignment']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_room_assignment']['alter']['text'] = 'Location: <a href="/node/[field_room_assignment-target_id]">[field_room_assignment]</a>';
  $handler->display->display_options['fields']['field_room_assignment']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_room_assignment']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Dates */
  $handler->display->display_options['fields']['field_dates']['id'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates']['table'] = 'field_data_field_dates';
  $handler->display->display_options['fields']['field_dates']['field'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates']['label'] = '';
  $handler->display->display_options['fields']['field_dates']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dates']['settings'] = array(
    'format_type' => 'medium',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Dates */
  $handler->display->display_options['fields']['field_dates_1']['id'] = 'field_dates_1';
  $handler->display->display_options['fields']['field_dates_1']['table'] = 'field_data_field_dates';
  $handler->display->display_options['fields']['field_dates_1']['field'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates_1']['label'] = '';
  $handler->display->display_options['fields']['field_dates_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dates_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dates_1']['settings'] = array(
    'format_type' => 'day',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Registration: Registration ID */
  $handler->display->display_options['fields']['registration_id']['id'] = 'registration_id';
  $handler->display->display_options['fields']['registration_id']['table'] = 'registration';
  $handler->display->display_options['fields']['registration_id']['field'] = 'registration_id';
  $handler->display->display_options['fields']['registration_id']['relationship'] = 'registration_rel';
  $handler->display->display_options['fields']['registration_id']['label'] = '';
  $handler->display->display_options['fields']['registration_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['registration_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['registration_id']['separator'] = '';
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['relationship'] = 'user_uid';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Cancel this registration';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'registration/[registration_id]/delete?destination=user/[uid]/my-registration';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Dates -  start date (field_dates) */
  $handler->display->display_options['sorts']['field_dates_value']['id'] = 'field_dates_value';
  $handler->display->display_options['sorts']['field_dates_value']['table'] = 'field_data_field_dates';
  $handler->display->display_options['sorts']['field_dates_value']['field'] = 'field_dates_value';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'user_uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['uid']['title'] = '%1\'s registrations';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['uid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['uid']['validate']['type'] = 'php';
  $handler->display->display_options['arguments']['uid']['validate_options']['code'] = 'if($GLOBALS[\'user\']->uid == $argument) {
return TRUE;
} elseif((arg(0) == \'user\' && is_numeric(arg(1)) && arg(2) == \'my-events\')) {
drupal_set_message(t(\'You may view your events only. Your events are not publicly shared.\'), \'warning\');
}
';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['relationship'] = 'registration_related_node';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter criterion: Registration: Date created */
  $handler->display->display_options['filters']['created']['id'] = 'created';
  $handler->display->display_options['filters']['created']['table'] = 'registration';
  $handler->display->display_options['filters']['created']['field'] = 'created';
  $handler->display->display_options['filters']['created']['relationship'] = 'registration_rel';
  $handler->display->display_options['filters']['created']['operator'] = '>=';
  $handler->display->display_options['filters']['created']['value']['value'] = '2014-01-01';
  $handler->display->display_options['path'] = 'user/%/my-registration';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'My Registrations';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['personal_schedule'] = $view;

  return $export;
}
