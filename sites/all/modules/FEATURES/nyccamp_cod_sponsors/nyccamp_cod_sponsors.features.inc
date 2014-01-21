<?php
/**
 * @file
 * nyccamp_cod_sponsors.features.inc
 */

/**
 * Implements hook_field_default_field_bases_alter().
 */
function nyccamp_cod_sponsors_field_default_field_bases_alter(&$data) {
  if (isset($data['field_sponsor_related_attendees'])) {
    unset($data['field_sponsor_related_attendees']);
  }
}

/**
 * Implements hook_field_default_field_instances_alter().
 */
function nyccamp_cod_sponsors_field_default_field_instances_alter(&$data) {
  if (isset($data['node-sponsor-field_sponsor_related_attendees'])) {
    unset($data['node-sponsor-field_sponsor_related_attendees']);
  }
}
