<?php
/**
 * @file
 * notify_node_authors_about_new_comments.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function notify_node_authors_about_new_comments_default_rules_configuration() {
  $items = array();
  $items['rules_notify_node_author_on_new_comments'] = entity_import('rules_config', '{ "rules_notify_node_author_on_new_comments" : {
      "LABEL" : "Notify node author on new comments",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Comment notification" ],
      "REQUIRES" : [ "rules", "comment" ],
      "ON" : [ "comment_insert" ],
      "IF" : [
        { "data_is" : {
            "data" : [ "comment:node:author:field-user-comment-notify" ],
            "value" : 1
          }
        },
        { "NOT data_is" : { "data" : [ "comment:author" ], "value" : [ "comment:node:author" ] } },
        { "NOT user_has_role" : {
            "account" : [ "comment:node:author" ],
            "roles" : { "value" : { "1" : "1" } }
          }
        }
      ],
      "DO" : [
        { "mail" : {
            "to" : [ "comment:node:author:mail" ],
            "subject" : "New comment posted to \\"[comment:node:title]\\"",
            "message" : "A new comment has been posted to [comment:node:title].\\r\\nYou can view it at [comment:url].\\r\\n\\r\\nKind regards,\\r\\n\\/\\/the robot at [site:name]"
          }
        }
      ]
    }
  }');
  return $items;
}
