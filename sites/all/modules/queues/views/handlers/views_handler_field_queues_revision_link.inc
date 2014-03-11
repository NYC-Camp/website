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
class queues_views_handler_field_operations extends views_handler_field {

  function query() {
    // Do nothing -- to override the parent query.
  }

  function get_value($values, $field = NULL) {
    if (isset($values->{$field})) {
      return $values->{$field};
    }
  }

  function render($values) {
    $output = '';
    if (empty($this->relationship)) {
      $qid = $this->get_value($values, 'state_flow_states_entity_id');
      $vid = $this->get_value($values, 'vid');
      $queue = queue_load($qid);

      if (queue_entity_access('edit', $queue)) {
        $links[] = array(
          'title' => t('Edit'),
          'href' => 'admin/content/queues/manage/' . $qid . '/revision/' . $vid,
          'query' => drupal_get_destination(),
        );
      }
      if (queue_entity_access('delete', $queue)) {
        $links[] = array(
          'title' => t('Delete'),
          'href' => 'admin/content/queues/manage/' . $qid . '/revision/' . $vid . '/delete',
          'query' => drupal_get_destination(),
        );
      }
      if (queue_entity_access('edit', $queue)) {
        $links[] = array(
          'title' => t('Schedule'),
          'href' => 'admin/content/queues/manage/' . $this->get_value($values, 'state_flow_states_entity_id') . '/schedule/add',
          'query' => array('edit[revision_id]' => $this->get_value($values, 'vid')),
        );
      }
      $output = theme('links__ctools_dropbutton', array('title' => t('operations'), 'links' => $links));
    }

    $this->add_ctools_css();

    return $output;
  }

  function add_ctools_css() {
    // Include the dropbutton css from views.
    drupal_add_css(drupal_get_path('module', 'views') . '/css/views-admin.css');
    drupal_add_css(drupal_get_path('module', 'views') . '/css/views-admin.ctools.css');
    drupal_add_css(drupal_get_path('module', 'views') . '/css/views-admin.seven.css');
  }
}
