<?php

include_once __DIR__ . './../queues.helpers.inc';

class QueuesHelpersTest extends PHPUnit_Framework_TestCase {

  public function testFieldNameSize() {
    $field_name_1 = "my_really_long_field_name_value";
    $field_name_2 = "my_short_field_name";
    $field_name_3 = "my_extremely_long_field_name_value_extra_long";

    $this->assertLessThanOrEqual(32, strlen(_queues_get_target_field_name($field_name_1)));
    $this->assertLessThanOrEqual(32, strlen(_queues_get_target_field_name($field_name_2)));
    $this->assertLessThanOrEqual(32, strlen(_queues_get_target_field_name($field_name_3)));
  }
}
