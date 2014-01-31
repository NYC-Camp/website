<?php
/**
 * @file
 * nyccamp_cod_sponsors.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function nyccamp_cod_sponsors_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field_base
  $overrides["field_base.field_sponsor_related_attendees.field_sponsor_related_attendees"]["DELETED"] = TRUE;

  // Exported overrides for: field_instance
  $overrides["field_instance.node-sponsor-field_sponsor_related_attendees.node-sponsor-field_sponsor_related_attendees"]["DELETED"] = TRUE;

 return $overrides;
}
