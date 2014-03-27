<?php

/*
 * @file
 * Devel Generate for timefield module
 *
 */

/*
 * Implements hook_devel_generate();
 */
function timefield_devel_generate($object, $field, $instance, $bundle) {
  if (field_behaviors_widget('multiple values', $instance) == FIELD_BEHAVIOR_CUSTOM) {
    return devel_generate_multiple('_timefield_devel_generate', $object, $field, $instance, $bundle);
  }
  else {
    return _timefield_devel_generate($object, $field, $instance, $bundle);
  }
}

/*
 * Helper function to generate timefield dummy values.
 */
function _timefield_devel_generate($object, $field, $instance, $bundle) {

  $time = rand(0, 86399);
  $time2 = rand($time + 1, 172799);

  $object_field = array();

  $object_field['value'] = $time;
  $object_field['value2'] = $time2;
  $object_field['label'] = devel_create_greeking(rand(2,3), TRUE);
  $object_field['mon'] = rand(0,1);
  $object_field['tue'] = rand(0,1);
  $object_field['wed'] = rand(0,1);
  $object_field['thu'] = rand(0,1);
  $object_field['fri'] = rand(0,1);
  $object_field['sat'] = rand(0,1);
  $object_field['sun'] = rand(0,1);

  return $object_field;
}
