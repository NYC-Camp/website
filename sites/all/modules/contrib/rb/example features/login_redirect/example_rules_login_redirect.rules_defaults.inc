<?php
/**
 * @file
 * example_rules_login_redirect.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function example_rules_login_redirect_default_rules_configuration() {
  $items = array();
  $items['rules_login_redirect_for_administrators'] = entity_import('rules_config', '{ "rules_login_redirect_for_administrators" : {
      "LABEL" : "Login redirect for administrators",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Login redirect" ],
      "REQUIRES" : [ "rules" ],
      "ON" : [ "user_login" ],
      "IF" : [
        { "user_has_role" : { "account" : [ "account" ], "roles" : { "value" : { "3" : "3" } } } }
      ],
      "DO" : [ { "redirect" : { "url" : "admin\\/content" } } ]
    }
  }');
  $items['rules_login_redirect_for_non_administrators'] = entity_import('rules_config', '{ "rules_login_redirect_for_non_administrators" : {
      "LABEL" : "Login redirect for non-administrators",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Login redirect" ],
      "REQUIRES" : [ "rules" ],
      "ON" : [ "user_login" ],
      "IF" : [
        { "NOT user_has_role" : { "account" : [ "account" ], "roles" : { "value" : { "3" : "3" } } } }
      ],
      "DO" : [ { "redirect" : { "url" : "\\u003cfront\\u003e" } } ]
    }
  }');
  return $items;
}
