<?php
/**
 * @file
 * qr_code.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function qr_code_default_rules_configuration() {
  $items = array();
  $items['rules_default_value_for_field_mobile_code_'] = entity_import('rules_config', '{ "rules_default_value_for_field_mobile_code_" : {
      "LABEL" : "Default value for field_mobile_code ",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "NYC Camp", "QR Code" ],
      "REQUIRES" : [ "rules" ],
      "ON" : { "user_view" : [] },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "account" ], "field" : "field_mobile_code" } }
      ],
      "DO" : [
        { "data_set" : {
            "data" : [ "account:field-mobile-code" ],
            "value" : "[account:field-profile-first] [account:field-profile-last]\\r\\n[account:field-profile-org]\\r\\n"
          }
        }
      ]
    }
  }');
  return $items;
}
