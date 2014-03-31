<?php
/**
 * @file
 * example_rule_promotion_syncronization.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function example_rule_promotion_syncronization_default_rules_configuration() {
  $items = array();
  $items['rules_actions_on_article_deletion'] = entity_import('rules_config', '{ "rules_actions_on_article_deletion" : {
      "LABEL" : "Actions on article deletion",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Promotion management" ],
      "REQUIRES" : [ "rules" ],
      "ON" : [ "node_delete" ],
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "article" : "article" } } } }
      ],
      "DO" : [
        { "entity_query" : {
            "USING" : {
              "type" : "node",
              "property" : "field_promotion_article",
              "value" : [ "node" ]
            },
            "PROVIDE" : { "entity_fetched" : { "promotion_list" : "List of promotions" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "promotion-list" ] },
            "ITEM" : { "promotion" : "Promotion" },
            "DO" : [
              { "entity_delete" : { "data" : [ "promotion" ] } },
              { "drupal_message" : { "message" : "Deleted article promotion \\"[promotion:title]\\"." } }
            ]
          }
        }
      ]
    }
  }');
  $items['rules_actions_when_articles_are_updated'] = entity_import('rules_config', '{ "rules_actions_when_articles_are_updated" : {
      "LABEL" : "Actions when articles are updated",
      "PLUGIN" : "reaction rule",
      "TAGS" : [ "Promotion management" ],
      "REQUIRES" : [ "rules" ],
      "ON" : [ "node_update" ],
      "IF" : [
        { "node_is_of_type" : { "node" : [ "node" ], "type" : { "value" : { "article" : "article" } } } }
      ],
      "DO" : [
        { "component_rules_consider_publishing_promotions" : { "node" : [ "node" ], "node_unsaved" : [ "node-unchanged" ] } },
        { "component_rules_consider_unpublishing_promotions" : { "node" : [ "node" ], "node_unsaved" : [ "node-unchanged" ] } }
      ]
    }
  }');
  $items['rules_consider_publishing_promotions'] = entity_import('rules_config', '{ "rules_consider_publishing_promotions" : {
      "LABEL" : "Consider publishing promotions",
      "PLUGIN" : "rule",
      "TAGS" : [ "Promotion management" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "node" : { "label" : "Saved content", "type" : "node" },
        "node_unsaved" : { "label" : "Unsaved content", "type" : "node" }
      },
      "IF" : [
        { "data_is" : { "data" : [ "node:status" ], "value" : 1 } },
        { "data_is" : { "data" : [ "node-unsaved:status" ], "value" : 0 } }
      ],
      "DO" : [
        { "entity_query" : {
            "USING" : {
              "type" : "node",
              "property" : "field_promotion_article",
              "value" : [ "node" ]
            },
            "PROVIDE" : { "entity_fetched" : { "promotion_list" : "List of promotions" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "promotion-list" ] },
            "ITEM" : { "promotion" : "Promotion" },
            "DO" : [ { "node_publish" : { "node" : [ "promotion" ] } } ]
          }
        }
      ]
    }
  }');
  $items['rules_consider_unpublishing_promotions'] = entity_import('rules_config', '{ "rules_consider_unpublishing_promotions" : {
      "LABEL" : "Consider unpublishing promotions",
      "PLUGIN" : "rule",
      "TAGS" : [ "Promotion management" ],
      "REQUIRES" : [ "rules" ],
      "USES VARIABLES" : {
        "node" : { "label" : "Saved content", "type" : "node" },
        "node_unsaved" : { "label" : "Unsaved content", "type" : "node" }
      },
      "IF" : [
        { "data_is" : { "data" : [ "node:status" ], "value" : 0 } },
        { "data_is" : { "data" : [ "node-unsaved:status" ], "value" : 1 } }
      ],
      "DO" : [
        { "entity_query" : {
            "USING" : {
              "type" : "node",
              "property" : "field_promotion_article",
              "value" : [ "node" ]
            },
            "PROVIDE" : { "entity_fetched" : { "promotion_list" : "List of promotions" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "promotion-list" ] },
            "ITEM" : { "promotion" : "Promotion" },
            "DO" : [ { "node_unpublish" : { "node" : [ "promotion" ] } } ]
          }
        }
      ]
    }
  }');
  return $items;
}
