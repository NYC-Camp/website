<?php

/**
 * @file
 * Definition of queues_views_handler_field_operations.
 */

/**
 * A handler to provide proper displays for the representative image.
 *
 * @ingroup views_field_handlers
 */
class queues_views_handler_field_queue_operations extends queues_views_handler_field_operations {

  function render($values) {
    $output = '';
    $links = array();
    if (empty($this->relationship)) {
      $qid = $this->get_value($values, 'qid');
      $queue = queue_load($qid);

      if (queue_entity_access('edit', $queue)) {
        $links[] = array(
          'title' => t('Edit'),
          'href' => 'admin/content/queues/manage/' . $qid,
          'query' => drupal_get_destination(),
        );
      }
      if (queue_entity_access('delete', $queue)) {
        $links[] = array(
          'title' => t('Delete'),
          'href' => 'admin/content/queues/manage/' . $qid . '/delete/',
          'query' => array(
            'destination' => 'admin/content/queues',
          ),
        );
      }

      $output = theme('links__ctools_dropbutton', array('title' => t('operations'), 'links' => $links));
    }

    $this->add_ctools_css();

    return $output;
  }

  function add_ctools_css() {
    parent::add_ctools_css();
    // Include the dropbutton css from pub_editorial.
    drupal_add_css(drupal_get_path('module', 'pub_editorial') . '/css/pub_editorial.css', array('weight' => 10));
  }
}
