<?php
/**
 * @file
 * qr_code.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function qr_code_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'qr_code';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'QR code';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access user profiles';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Footer: Global: Text area */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  $handler->display->display_options['footer']['area']['label'] = 'About the QR code';
  $handler->display->display_options['footer']['area']['content'] = '<strong>About the QR code</strong>
<br><br>
We\'re thinking of using this <a href="http://en.wikipedia.org/wiki/QR_code">QR code</a> to expedite registration at the UN. Currently the QR code contains your first name, your last name, and your organization.';
  $handler->display->display_options['footer']['area']['format'] = 'filtered_html';
  /* Field: User: Mobile Code */
  $handler->display->display_options['fields']['field_mobile_code']['id'] = 'field_mobile_code';
  $handler->display->display_options['fields']['field_mobile_code']['table'] = 'field_data_field_mobile_code';
  $handler->display->display_options['fields']['field_mobile_code']['field'] = 'field_mobile_code';
  $handler->display->display_options['fields']['field_mobile_code']['label'] = '';
  $handler->display->display_options['fields']['field_mobile_code']['element_label_colon'] = FALSE;
  /* Sort criterion: User: Created date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'users';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['uid']['title'] = '%1';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['uid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['uid']['validate']['type'] = 'php';
  $handler->display->display_options['arguments']['uid']['validate_options']['code'] = 'if($GLOBALS[\'user\']->uid == $argument) {
return TRUE;
} elseif((arg(0) == \'user\' && is_numeric(arg(1)) && arg(2) == \'qr-code\')) {
drupal_set_message(t(\'You may view your qr-code only. QR codes are not publicly shared.\'), \'warning\');
}';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'user/%/qr-code';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'QR Code';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['qr_code'] = $view;

  return $export;
}
