<?php

/**
 * @file
 * Views integration for Queues Workbench.
 */

/**
 * Implements hook_views_data_alter().
 */
function queues_workbench_views_data_alter(&$data) {

  $data['state_flow_states']['table']['join']['queues_revision'] = array(
    'left_field' => 'vid',
    'field' => 'revision_id',
    'type' => 'INNER',
    'extra' => array(
      array(
        'field' => 'entity_type',
        'value' => 'queues',
        'operator' => '='
      )
    )
  );

  $data['state_flow_history']['table']['join']['queues'] = array(
    'left_field' => 'qid',
    'field' => 'entity_id',
    'type' => 'INNER',
    'extra' => array(
      array(
        'field' => 'entity_type',
        'value' => 'queues',
        'operator' => '='
      )
    )
  );

  $data['state_flow_history']['revision_id']['relationship'] = array(
    'title' => t('Queues Revision'),
    'label' => t('Queues Revision'),
    'base' => 'queues_revision',
    'base field' => 'vid',
    'type' => 'INNER',
  );

  $data['state_flow_history']['qid'] = array(
     'title' => t('Queue'),
     'help' => t('The queue according to the State Flow.'),
     'relationship' => array(
         'base' => 'queues',
         'field' => 'entity_id',
         'handler' => 'views_handler_relationship',
         'label' => t('Queues'),
     ),
   );

  $data['queues_revision']['is_published'] = array(
    'real field' => 'vid',
    'title' => t('Is this revision published?'),
    'help' => t('Checks whether this is the revision that is also in the queue table and that its status is 1'),
    'field' => array(
      'handler' => 'queues_workbench_handler_field_is_queues_revision_published',
      'click sortable' => FALSE,
    ),
  );
}
