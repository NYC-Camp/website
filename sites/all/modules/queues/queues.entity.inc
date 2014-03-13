<?php

/**
 * @file
 *
 * Class API and helper for our queues entity.
 */

/**
 * QueueEntity
 */
class QueueEntity extends Entity {
  public $title;
  public $type;
  public $description;
  public $is_new = FALSE;
  public $status = 1;
  public $default_revision = TRUE;

  public function __construct($values = array()) {
    // If this is new then set the type first.
    if (isset($values['is_new'])) {
      $type = arg(4);
      // All I've done is move the hack to a more generic place.
      // The problem is entity API does not pass in the type on the "add" op.
      // The proper fix for this is to take over the menu path from entity api.
      // I do not want to do this just now, because of time.
      if (is_string($type)) {
        $this->type = isset($values['type']) ? $values['type'] : $type;
      }
    }
    parent::__construct($values, 'queues');
  }

  /**
   * Returns the default Queues Label which are the Title Property.
   *
   * @return string
   */
  protected function defaultLabel() {
    return $this->title;
  }


  public function save() {
    parent::save();
  }

  /**
   * Return the defaultUri Path for queues.
   *
   * @return array
   */
  protected function defaultUri() {
    // Queues have no display. Only a management screen.
    return array('path' => 'admin/content/queues/manage/' . $this->identifier());
  }
}

/**
 * Load multiple models based on certain conditions.
 *
 * @param $queues_ids
 *   An array of queue IDs.
 * @param $conditions
 *   An array of conditions to match against the {queues} table.
 * @param $reset
 *   A boolean indicating that the internal cache should be reset.
 * @return
 *   An array of queue objects, indexed by queue_id.
 *
 * @see entity_load()
 * @see queue_load()
 */
function queue_load_multiple($queues_ids = array(), $conditions = array(), $reset = FALSE) {
  return entity_load('queues', $queues_ids, $conditions, $reset);
}
