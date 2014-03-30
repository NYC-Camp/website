-- SUMMARY --

Batched Rules

Provides a batched rule set component to rules. Using a batched rule set you
can execute very performance heavy rule sets without fearing of running out
of execution time.

-- ATTENTION --

DO NOT USE THIS MODULE IF YOU ARE USING RULES > 7.x-beta3

Due to the rules issues #1285856, #1341344 using this module would break your
site. If you're site is already broken because you didn't read this (who would)
you have to delete the batched rulesets you have created manually.
To do so remove all batched rulesets in the rules_config table in your database.

-- REQUIREMENTS --

Rules (http://drupal.org/project/rules)


-- HOW TO USE? --

Install as usual, see http://drupal.org/node/895232 for further information.

Configuration
  No initial configuration neccessary.

Batched rule sets
  After installation a new 'Batched rule set' component was added and can be
  used just like the default 'Rule set'.

Alter batch context
  Per default the batch status message will be the last processed rule's title
  and any rule will only be executed once.
  This behaviour can be modified by the 'Alter batch context' action. Using it
  in a rule set that is configured to use the batch API, the progress message
  can be altered and a rule can be marked to get re-executed.

Schedule
  Unfortunately batched rule sets can not be scheduled technically.
