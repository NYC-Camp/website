<?php
/**
 * @file
 * example_rules_create_promotion.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function example_rules_create_promotion_default_rules_configuration() {
  $items = array();
  $items['rules_actions_on_article_creation'] = entity_import('rules_config', '{ "rules_actions_on_article_creation" : {
      "LABEL" : "Actions on article creation",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Promotion management" ],
      "REQUIRES" : [ "rules" ],
      "ON" : [ "node_insert" ],
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "article" : "article" } } } }
      ],
      "DO" : [ { "component_rules_create_promotion" : { "node" : [ "node" ] } } ]
    }
  }');
  $items['rules_create_promotion'] = entity_import('rules_config', '{ "rules_create_promotion" : {
      "LABEL" : "Create promotion",
      "PLUGIN" : "rule set",
      "TAGS" : [ "Promotion management" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : { "node" : { "label" : "New content", "type" : "node" } },
      "RULES" : [
        { "RULE" : {
            "PROVIDE" : { "entity_created" : { "promotion" : "Promotion" } },
            "IF" : [
              { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "article" : "article" } } } }
            ],
            "DO" : [
              { "entity_create" : {
                  "USING" : {
                    "type" : "node",
                    "param_type" : "article_promotion",
                    "param_title" : [ "node:title" ],
                    "param_author" : [ "node:author" ]
                  },
                  "PROVIDE" : { "entity_created" : { "promotion" : "Promotion" } }
                }
              },
              { "data_set" : { "data" : [ "promotion:field-promotion-article" ], "value" : [ "node" ] } },
              { "data_set" : {
                  "data" : [ "promotion:field-promotion-text" ],
                  "value" : [ "node:body" ]
                }
              },
              { "data_set" : {
                  "data" : [ "promotion:field-promotion-image" ],
                  "value" : [ "node:field-image" ]
                }
              },
              { "entity_save" : { "data" : [ "promotion" ], "immediate" : 1 } }
            ],
            "LABEL" : "Create the promotion node"
          }
        },
        { "RULE" : {
            "IF" : [ { "data_is" : { "data" : [ "node:status" ], "value" : 0 } } ],
            "DO" : [ { "node_unpublish" : { "node" : [ "promotion" ] } } ],
            "LABEL" : "Unpublish promotion, if necessary"
          }
        },
        { "RULE" : {
            "DO" : [
              { "drupal_message" : { "message" : "An article promotion has been automatically created. \\u003ca href=\\"[site:url]node\\/[promotion:nid]\\/edit\\"\\u003eClick here if you want to customize it.\\u003c\\/a\\u003e (More promotions can be created manually.)" } }
            ],
            "LABEL" : "Display an edit link"
          }
        }
      ]
    }
  }');
  return $items;
}
