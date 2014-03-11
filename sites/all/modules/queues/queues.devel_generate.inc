<?php

/**
 * Generate queues.
 *
 * @param int $num
 *   The number of queues to generate.
 * @param bool $kill
 *   Set to TRUE to delete all queues before generating.
 * @param $types
 *   An array of queue types to generate.
 */
function queues_generate_queues($num, $kill, $types) {
  module_load_include('inc', 'devel_generate', 'devel_generate.fields');

  if ($kill) {
    $q = new EntityFieldQuery();
    $queues = $q->entityCondition('entity_type', 'queues')
      ->execute();
    entity_delete_multiple('queues', array_keys($queues['queues']));
  }

  for ($i = 0; $i < $num; $i++) {
    $title = devel_create_greeking(1, TRUE);
    $description = devel_create_greeking(mt_rand(2, 255));
    $type = $types[array_rand($types)];

    $values = array(
      'title' => $title,
      'type' => $type,
      'description' => $description,
      'is_new' => TRUE,
    );

    $queue = new QueueEntity($values);

    // Populate all core fields on behalf of field.module
    devel_generate_fields($queue, 'queues', $type);

    $queue->save();
  }
}

