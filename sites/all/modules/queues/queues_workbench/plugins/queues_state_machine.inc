<?php

/**
 * @file
 * State Flow implementation of the State Machine class
 */

class QueuesStatesEntity extends StateFlowEntity {

  /**
   * On enter published Callback.
   *
   * @see StateFlowEntity::fire_event()
   */
  public function on_enter_published() {
    // I am -most surely- going to hate myself later at some point, but this is
    // the only way I can see to solve the problem.

    // We need to persist the status = TRUE in the entity, BUT if we go through
    // all the process of saving the entity, then it will get saved twice and
    // that will create a new revision. Next time when trying to load the
    // moderation state from state_flow_history we won't find any record since
    // there will be a newer revision (from the second save) without a record in
    // state_flow_history, hence the current state being NULL and the incorrect
    // values in the entity form moderation dropdown.
    $this->persist_status(TRUE);
  }

  /**
   * On exit publish Callback.
   *
   * @see StateFlowEntity::fire_event()
   */
  public function on_enter_unpublished() {
    $this->persist_status(FALSE);
  }

  /**
   * On exit publish Callback.
   *
   * @see StateFlowEntity::fire_event()
   */
  public function on_exit_published() {
    // Do not do anything. Since onEnterUnpublished will do all the heavy
    // lifting.
  }

  /**
   * Set Published Callback.
   *
   * StateFlowEntity calls this directly so I can't use the camelCase.
   *
   * @see StateFlowEntity::fire_event()
   */
  public function set_published($reset = FALSE) {
    $this->object->status = TRUE;
    $this->object->published_revision_id = $this->object->vid;
    if (isset($this->object->is_new) && isset($this->object->qid)) {
      $this->object->is_new = FALSE;
    }
    $this->object->save();
  }

  /**
   * Persist the entity status. WARNING: This won't save the actual entity,
   * don't expect any entity hook to be fired by this method.
   *
   * @param bool $status
   *   The status to be persisted.
   *
   * @return int
   *   Returns the same as drupal_write_record.
   *
   * @see drupal_write_record
   */
  protected function persist_status($status) {
    $this->object->status = $status;
    drupal_write_record('queues', $this->object, array('qid'));
    drupal_write_record('queues_revision', $this->object, array('vid'));
  }
}
