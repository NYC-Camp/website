<?php
/**
 * @file
 * user_schedule.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function user_schedule_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_default_message_type().
 */
function user_schedule_default_message_type() {
  $items = array();
  $items['user_schedule'] = entity_import('message_type', '{
    "name" : "user_schedule",
    "description" : "User schedule",
    "argument_keys" : [],
    "argument" : [],
    "category" : "message_type",
    "data" : {
      "token options" : { "clear" : 0 },
      "purge" : { "override" : 0, "enabled" : 0, "quota" : "", "days" : "" }
    },
    "language" : "",
    "arguments" : null,
    "message_text" : { "und" : [
        {
          "value" : "\\u003Cp\\u003E[message:field-message-content:title] has been added to [message:user:name]\\u0027s schedule.\\u003C\\/p\\u003E",
          "format" : "filtered_html",
          "safe_value" : "\\u003Cp\\u003E[message:field-message-content:title] has been added to [message:user:name]\\u0027s schedule.\\u003C\\/p\\u003E"
        }
      ]
    }
  }');
  return $items;
}
