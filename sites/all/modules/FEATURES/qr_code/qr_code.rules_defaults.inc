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
  $items['rules_default_value_and_text_format_for_field_mobile_code_'] = entity_import('rules_config', '{ "rules_default_value_and_text_format_for_field_mobile_code_" : {
      "LABEL" : "Default value and text format for field_mobile_code ",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "COD", "COD Extras" ],
      "REQUIRES" : [ "rules" ],
      "ON" : { "user_view" : [] },
      "IF" : [
        { "entity_has_field" : { "entity" : [ "account" ], "field" : "field_mobile_code" } }
      ],
      "DO" : [
        { "data_set" : {
            "data" : [ "account:field-mobile-code:format" ],
            "value" : "mobile_codes_formatting"
          }
        },
        { "data_set" : {
            "data" : [ "account:field-mobile-code:value" ],
            "value" : "[mobilecode #preset=\\u0022small\\u0022][current-user:field-profile-first][\\/mobilecode]"
          }
        }
      ]
    }
  }');
  return $items;
}
