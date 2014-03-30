<?php
/**
 * @file
 * sessions_display_suite.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function sessions_display_suite_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|session|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'session';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'add_to_my_schedule_flag' => array(
      'weight' => '13',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'login_or_register_display_suite' => array(
      'weight' => '14',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'comments' => array(
      'weight' => '15',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'submitted_by' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'ds_post_date_medium',
    ),
    'ds_user_picture' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'ds_picture_user_picture_display_suite',
    ),
  );
  $export['node|session|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_custom_fields_info().
 */
function sessions_display_suite_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'add_to_my_schedule_flag';
  $ds_field->label = 'Add to my schedule flag';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'session|*';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php
if(user_is_logged_in()) {
  if(
    $entity->field_accepted[\'und\'][0][\'value\'] == 1 || 
    $entity->field_accepted[\'und\'][0][\'value\'] == 4 ||
    $entity->field_accepted[\'und\'][0][\'value\'] == 5 ||
    $entity->field_accepted[\'und\'][0][\'value\'] == 6
    ){
      print \'<br>\';
      print flag_create_link(\'session_schedule\', $entity->nid);
      print \'<br>\';
    }
}
?>',
      'format' => 'ds_code',
    ),
    'use_token' => 0,
  );
  $export['add_to_my_schedule_flag'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'login_or_register_display_suite';
  $ds_field->label = 'Login or register display suite';
  $ds_field->field_type = 5;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'session|*';
  $ds_field->properties = array(
    'code' => array(
      'value' => '<?php
// TODO: Don\'t copy verbatim theme_comment_post_forbidden() to this field.
$node = $entity;
  global $user;

  // Since this is expensive to compute, we cache it so that a page with many
  // comments only has to query the database once for all the links.
  $authenticated_post_comments = &drupal_static(__FUNCTION__, NULL);

  if (!$user->uid) {
    if (!isset($authenticated_post_comments)) {
      // We only output a link if we are certain that users will get permission
      // to post comments by logging in.
      $comment_roles = user_roles(TRUE, \'post comments\');
      $authenticated_post_comments = isset($comment_roles[DRUPAL_AUTHENTICATED_RID]);
    }

    if ($authenticated_post_comments) {
      // We cannot use drupal_get_destination() because these links
      // sometimes appear on /node and taxonomy listing pages.
      if (variable_get(\'comment_form_location_\' . $node->type, COMMENT_FORM_BELOW) == COMMENT_FORM_SEPARATE_PAGE) {
        $destination = array(\'destination\' => "comment/reply/$node->nid#comment-form");
      }
      else {
        $destination = array(\'destination\' => "node/$node->nid#comment-form");
      }

      if (variable_get(\'user_register\', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL)) {
        // Users can register themselves.
        return t(\'<a href="@login">Log in</a> or <a href="@register">register</a> to post comments\', array(\'@login\' => url(\'user/login\', array(\'query\' => $destination)), \'@register\' => url(\'user/register\', array(\'query\' => $destination))));
      }
      else {
        // Only admins can add new users, no public registration.
        return t(\'<a href="@login">Log in</a> to post comments\', array(\'@login\' => url(\'user/login\', array(\'query\' => $destination))));
      }
    }
  }
?>',
      'format' => 'ds_code',
    ),
    'use_token' => 0,
  );
  $export['login_or_register_display_suite'] = $ds_field;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function sessions_display_suite_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|session|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'session';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'ds_user_picture',
        1 => 'submitted_by',
        2 => 'field_event_subtitle',
        3 => 'body',
        4 => 'field_presenters',
        5 => 'field_session_track',
        6 => 'field_experience',
        7 => 'group_schedule_info',
        8 => 'field_session_time',
        9 => 'field_accepted',
        10 => 'field_which_day',
        11 => 'field_session_other_info',
        12 => 'field_session_topics',
        13 => 'field_summit_session',
        14 => 'field_slides',
        15 => 'add_to_my_schedule_flag',
        16 => 'login_or_register_display_suite',
        17 => 'comments',
      ),
    ),
    'fields' => array(
      'ds_user_picture' => 'ds_content',
      'submitted_by' => 'ds_content',
      'field_event_subtitle' => 'ds_content',
      'body' => 'ds_content',
      'field_presenters' => 'ds_content',
      'field_session_track' => 'ds_content',
      'field_experience' => 'ds_content',
      'group_schedule_info' => 'ds_content',
      'field_session_time' => 'ds_content',
      'field_accepted' => 'ds_content',
      'field_which_day' => 'ds_content',
      'field_session_other_info' => 'ds_content',
      'field_session_topics' => 'ds_content',
      'field_summit_session' => 'ds_content',
      'field_slides' => 'ds_content',
      'add_to_my_schedule_flag' => 'ds_content',
      'login_or_register_display_suite' => 'ds_content',
      'comments' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|session|default'] = $ds_layout;

  return $export;
}
