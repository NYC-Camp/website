<?php
/**
 * @file
 * user_schedule.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function user_schedule_default_rules_configuration() {
  $items = array();
  $items['rules_user_add_schedule'] = entity_import('rules_config', '{ "rules_user_add_schedule" : {
      "LABEL" : "User add schedule",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "REQUIRES" : [ "flag", "rules" ],
      "ON" : { "flag_flagged_session_schedule" : [] },
      "DO" : [
        { "flag_fetch_entity_by_user" : {
            "USING" : { "flag" : "session_schedule", "flagging_user" : [ "flagging_user" ] },
            "PROVIDE" : { "content_flagged_by_user" : { "content_flagged_by_user" : "Content flagged by user" } }
          }
        },
        { "entity_create" : {
            "USING" : {
              "type" : "message",
              "param_type" : "user_schedule",
              "param_user" : [ "flagging-user" ]
            },
            "PROVIDE" : { "entity_created" : { "entity_created" : "Created entity" } }
          }
        },
        { "data_set" : {
            "data" : [ "entity-created:field-message-content" ],
            "value" : [ "flagged-node" ]
          }
        }
      ]
    }
  }');
  return $items;
}
