<?php
/**
 * @file
 * notify_on_comment_replies.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function notify_on_comment_replies_default_rules_configuration() {
  $items = array();
  $items['rules_notify_on_comment_replies'] = entity_import('rules_config', '{ "rules_notify_on_comment_replies" : {
      "LABEL" : "Notify on comment replies",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Comment notification" ],
      "REQUIRES" : [ "rules", "comment" ],
      "ON" : [ "comment_insert" ],
      "IF" : [
        { "entity_has_field" : { "entity" : [ "comment:parent" ], "field" : "field_comment_notify" } },
        { "data_is" : { "data" : [ "comment:parent:field-comment-notify" ], "value" : 1 } },
        { "NOT data_is" : { "data" : [ "comment:author" ], "value" : [ "comment:parent:author" ] } }
      ],
      "DO" : [
        { "mail" : {
            "to" : [ "comment:parent:author:mail" ],
            "subject" : "Reply posted to [comment:parent:title]",
            "message" : "A reply has been posted to your comment [comment:parent:title].\\r\\nYou can view it at [comment:url].\\r\\n\\r\\nKind regards,\\r\\n\\/\\/the robot at [site:name]"
          }
        }
      ]
    }
  }');
  return $items;
}
