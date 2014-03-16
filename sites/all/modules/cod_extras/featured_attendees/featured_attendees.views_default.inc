<?php
/**
 * @file
 * featured_attendees.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function featured_attendees_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'attendees_featured';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'Attendees - Featured';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Featured Attendees';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    6 => '6',
    3 => '3',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'flexslider';
  $handler->display->display_options['style_options']['optionset'] = 'carousel';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: User: Featured Attendee Blurb */
  $handler->display->display_options['fields']['field_featured_attendee_blurb']['id'] = 'field_featured_attendee_blurb';
  $handler->display->display_options['fields']['field_featured_attendee_blurb']['table'] = 'field_data_field_featured_attendee_blurb';
  $handler->display->display_options['fields']['field_featured_attendee_blurb']['field'] = 'field_featured_attendee_blurb';
  $handler->display->display_options['fields']['field_featured_attendee_blurb']['exclude'] = TRUE;
  /* Field: User: My Drupal.org profile */
  $handler->display->display_options['fields']['field_my_drupal_org_profile']['id'] = 'field_my_drupal_org_profile';
  $handler->display->display_options['fields']['field_my_drupal_org_profile']['table'] = 'field_data_field_my_drupal_org_profile';
  $handler->display->display_options['fields']['field_my_drupal_org_profile']['field'] = 'field_my_drupal_org_profile';
  $handler->display->display_options['fields']['field_my_drupal_org_profile']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_my_drupal_org_profile']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_my_drupal_org_profile']['type'] = 'link_absolute';
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['label'] = '';
  $handler->display->display_options['fields']['picture']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['picture']['alter']['alt'] = '[field_featured_attendee_blurb]';
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['picture']['image_style'] = 'flexslider_full';
  /* Field: User: First name */
  $handler->display->display_options['fields']['field_profile_first']['id'] = 'field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['table'] = 'field_data_field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['field'] = 'field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['label'] = '';
  $handler->display->display_options['fields']['field_profile_first']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_profile_first']['element_label_colon'] = FALSE;
  /* Field: User: Last name */
  $handler->display->display_options['fields']['field_profile_last']['id'] = 'field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['table'] = 'field_data_field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['field'] = 'field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['label'] = '';
  $handler->display->display_options['fields']['field_profile_last']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_profile_last']['alter']['text'] = '[field_profile_first] [field_profile_last]';
  $handler->display->display_options['fields']['field_profile_last']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_profile_last']['alter']['path'] = 'user/[uid]';
  $handler->display->display_options['fields']['field_profile_last']['alter']['replace_spaces'] = TRUE;
  $handler->display->display_options['fields']['field_profile_last']['element_label_colon'] = FALSE;
  /* Field: User: IRC */
  $handler->display->display_options['fields']['field_profile_irc']['id'] = 'field_profile_irc';
  $handler->display->display_options['fields']['field_profile_irc']['table'] = 'field_data_field_profile_irc';
  $handler->display->display_options['fields']['field_profile_irc']['field'] = 'field_profile_irc';
  $handler->display->display_options['fields']['field_profile_irc']['label'] = '';
  $handler->display->display_options['fields']['field_profile_irc']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_profile_irc']['alter']['path'] = '[field_my_drupal_org_profile]';
  $handler->display->display_options['fields']['field_profile_irc']['alter']['external'] = TRUE;
  $handler->display->display_options['fields']['field_profile_irc']['alter']['alt'] = 'Visit the drupal.org profile page';
  $handler->display->display_options['fields']['field_profile_irc']['element_label_colon'] = FALSE;
  /* Sort criterion: Draggableviews: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'draggableviews_structure';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_view'] = 'self';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_new_items_bottom_list'] = 1;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: User: Featured Attendee (field_user_featured_attendee) */
  $handler->display->display_options['filters']['field_user_featured_attendee_value']['id'] = 'field_user_featured_attendee_value';
  $handler->display->display_options['filters']['field_user_featured_attendee_value']['table'] = 'field_data_field_user_featured_attendee';
  $handler->display->display_options['filters']['field_user_featured_attendee_value']['field'] = 'field_user_featured_attendee_value';
  $handler->display->display_options['filters']['field_user_featured_attendee_value']['value'] = array(
    0 => '0',
  );

  /* Display: Attendees - Featured - Set Order */
  $handler = $view->new_display('page', 'Attendees - Featured - Set Order', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Set Order of Featured Attendees';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'draggableviews' => 'draggableviews',
    'picture' => 'picture',
    'field_profile_first' => 'field_profile_first',
    'field_profile_last' => 'field_profile_last',
    'name_1' => 'name_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'draggableviews' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'picture' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_profile_first' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_profile_last' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Draggableviews: User */
  $handler->display->display_options['fields']['draggableviews']['id'] = 'draggableviews';
  $handler->display->display_options['fields']['draggableviews']['table'] = 'users';
  $handler->display->display_options['fields']['draggableviews']['field'] = 'draggableviews';
  $handler->display->display_options['fields']['draggableviews']['label'] = '';
  $handler->display->display_options['fields']['draggableviews']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['draggableviews']['save_button_label'] = 'Set Order';
  $handler->display->display_options['fields']['draggableviews']['draggableviews']['ajax'] = 1;
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['picture']['link_photo_to_profile'] = FALSE;
  $handler->display->display_options['fields']['picture']['image_style'] = 'thumbnail';
  /* Field: User: First name */
  $handler->display->display_options['fields']['field_profile_first']['id'] = 'field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['table'] = 'field_data_field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['field'] = 'field_profile_first';
  $handler->display->display_options['fields']['field_profile_first']['label'] = '';
  $handler->display->display_options['fields']['field_profile_first']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_profile_first']['element_label_colon'] = FALSE;
  /* Field: User: Last name */
  $handler->display->display_options['fields']['field_profile_last']['id'] = 'field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['table'] = 'field_data_field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['field'] = 'field_profile_last';
  $handler->display->display_options['fields']['field_profile_last']['label'] = 'Name';
  $handler->display->display_options['fields']['field_profile_last']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_profile_last']['alter']['text'] = '[field_profile_first] [field_profile_last]';
  $handler->display->display_options['fields']['field_profile_last']['element_label_colon'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'users';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['label'] = 'Username';
  $handler->display->display_options['fields']['name_1']['element_label_colon'] = FALSE;
  /* Field: User: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'users';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Edit User';
  $handler->display->display_options['fields']['edit_node']['text'] = 'Edit User';
  $handler->display->display_options['path'] = 'admin/dashboard/featured-attendees';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: User: Featured Attendee (field_user_featured_attendee) */
  $handler->display->display_options['filters']['field_user_featured_attendee_value']['id'] = 'field_user_featured_attendee_value';
  $handler->display->display_options['filters']['field_user_featured_attendee_value']['table'] = 'field_data_field_user_featured_attendee';
  $handler->display->display_options['filters']['field_user_featured_attendee_value']['field'] = 'field_user_featured_attendee_value';
  $handler->display->display_options['filters']['field_user_featured_attendee_value']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['block_description'] = 'Featured Attendees';
  $export['attendees_featured'] = $view;

  return $export;
}
