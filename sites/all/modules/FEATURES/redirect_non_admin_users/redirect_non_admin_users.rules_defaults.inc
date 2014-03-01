<?php
/**
 * @file
 * redirect_non_admin_users.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function redirect_non_admin_users_default_rules_configuration() {
  $items = array();
  $items['rules_redirect_non_admin_users'] = entity_import('rules_config', '{ "rules_redirect_non_admin_users" : {
      "LABEL" : "Redirect non admin users",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "nyccamp", "nyccamp-hacks" ],
      "REQUIRES" : [ "pathrules", "rules" ],
      "ON" : { "init" : [] },
      "IF" : [
        { "pathrules_checkpath" : { "path" : "node\\/add", "operation" : "equals" } },
        { "NOT user_has_role" : {
            "account" : [ "site:current-user" ],
            "roles" : { "value" : { "3" : "3" } }
          }
        }
      ],
      "DO" : [ { "redirect" : { "url" : "\\u003Cfront\\u003E" } } ]
    }
  }');
  return $items;
}
