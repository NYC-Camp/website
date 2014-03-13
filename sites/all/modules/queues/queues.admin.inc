<?php

/**
 * @file
 * Profile type editing UI.
 */

class QueueEntityUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults. We need to do this.
   *
   * The parent class hook_menu() sucks for content management.
   */
  public function hook_menu() {
    $plural_label = isset($this->entityInfo['plural label']) ? $this->entityInfo['plural label'] : $this->entityInfo['label'] . 's';

    // Lets get the default menu items.
    $items = parent::hook_menu();

    // We do not want a generic add queue page.
    unset($items[$this->path . '/add']);

    $items[$this->path] = array(
      'title' => $plural_label,
      'page callback' => 'drupal_get_form',
      'page arguments' => array($this->entityType . '_overview_form', $this->entityType),
      'description' => 'Manage ' . $plural_label . '.',
      'access callback' => 'entity_access',
      'access arguments' => array('view', $this->entityType),
      'file' => 'includes/entity.ui.inc',
      'type' => MENU_LOCAL_TASK,
    );

    $items[$this->path . '/list'] = array(
      'title' => 'List',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
    );

    // Add menu items to add each different type of entity.
    foreach (queues_type_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title' => t('Add @queue', array('@queue' => $type->label)),
        'page callback' => 'entity_ui_get_form',
        'page arguments' => array($this->entityType, NULL, 'add'),
        'access callback' => 'entity_access',
        'access arguments' => array('create', $this->entityType),
        'type' => MENU_LOCAL_ACTION,
      );
    }
    $items['queues/view/%queue'] = array(
      'title' => t('View Queues'),
      'access arguments' => array('view', 2),
      'access callback' => 'queue_entity_access',
      'page callback' => 'queue_entity_view',
      'page arguments' => array(2),
    );
    $items['queues/view/%queue/revision/%'] = array(
      'title' => t('View Queues Revision'),
      'access arguments' => array('view', 4),
      'access callback' => 'queue_entity_access',
      'page callback' => 'queue_entity_revision_view',
      'page arguments' => array(2, 4),
    );

    $items['admin/content/queues/manage/%/revision/%'] = array(
      'title' => t('Edit'),
      'access arguments' => array('edit', 4),
      'access callback' => 'queue_entity_access',
      'page callback' => 'queues_revision_edit',
      'page arguments' => array(4, 6),
    );

    $items['admin/content/queues/manage/%/revision/%/delete'] = array(
      'title' => t('Delete'),
      'access arguments' => array('delete', 4),
      'access callback' => 'queue_entity_access',
      'page callback' => 'drupal_get_form',
      'page arguments' => array('queues_confirm_delete_revision_form', 4, 6),
    );

    return $items;
  }

  /**
   * Overrides hook_menu() defaults.
   *
   * @return array
   *   The form for which the specific queue bundle.
   */
  public function hook_forms() {
    $forms = parent::hook_forms();

    if (!(count($this->entityInfo['bundles']) == 1 && isset($this->entityInfo['bundles'][$this->entityType]))) {
      foreach ($this->entityInfo['bundles'] as $bundle => $bundle_info) {
        $forms[$this->entityType . '_edit_' . $bundle . '_form']['callback'] = $this->entityType . '_form';
        // Again the wrapper callback is invoked by entity_ui_get_form() anyway.
      }
    }
    return $forms;
  }
}

/**
 * Queues Revision Form.
 *
 * @param QueueEntity $QueueEntity
 *   The QueueEntity being edited.
 * @param $revision_id
 * @return array|mixed
 */
function queues_revision_edit($QueueEntity, $revision_id) {
  $entity = entity_revision_load('queues', $revision_id);
  return entity_ui_get_form('queues', $entity, 'edit');
}


/**
 * View a specific Queue Revision.
 *
 * @param QueueEntity $queue_entity
 *   The Queue Entity being viewed.
 *
 * @param int $revision_id
 *   The Revision ID of the Queue being viewed.
 *
 * @return array
 *   A render array.
 */
function queue_entity_revision_view($queue_entity, $revision_id = NULL) {
  $entity = entity_revision_load('queues', $revision_id);
  return entity_view('queues', array($entity));
}

/**
 * View a specific Queue.
 *
 * @param QueueEntity $queue_entity
 *   The Queue Entity being viewed.
 *
 * @param int $revision_id
 *   The Revision ID of the Queue being viewed.
 *
 * @return array
 *   A render array.
 */
function queue_entity_view($queue_entity, $revision_id = NULL) {
  return entity_view('queues', array($queue_entity));
}

/**
 * Queues Form.
 *
 * @param array $form
 *   Form array.
 * @param array $form_state
 *   Form State array.
 * @param array $QueueEntity
 * @param string $op
 * @return mixed
 */
function queues_form($form, $form_state, $QueueEntity, $op) {

  $form['title'] = array(
    '#type' => 'textfield',
    '#title' => t('Title'),
    '#required' => TRUE,
    '#default_value' => $QueueEntity->title,
    '#weight' => -10,
  );

  $form['options'] = array(
    '#type' => 'vertical_tabs',
  );

  $form['options']['publishing'] = array(
    '#type' => 'fieldset',
    '#title' => t('Publishing Options'),
  );

  $form['options']['publishing']['status'] = array(
    '#type' => 'checkbox',
    '#title' => t('Published'),
    '#default_value' => $QueueEntity->status,
  );

  $form['options']['publishing']['revision']['is_new_revision'] = array(
    '#type' => 'checkbox',
    '#title' => t('Create new revision'),
    '#default_value' => $QueueEntity->default_revision,
    '#id' => 'edit-revision',
  );

  if ($QueueEntity->is_new === TRUE) {
    // On new Entities, Hide the checkbox and always make a new revision.
    $form['options']['publishing']['revision']['#access'] = FALSE;
    $form['default_revision'] = array(
      '#type' => 'value',
      '#value' => TRUE,
    );
  }
  else {
    $form['options']['publishing']['revision']['default_revision'] = array(
      '#type' => 'checkbox',
      '#title' => t('Set Revision as default'),
      '#default_value' => $QueueEntity->isDefaultRevision(),
      '#states' => array(
        // Hide if the option above is disabled, to avoid potential dataloss.
        'invisible' => array(
          ':input[name="is_new_revision"]' => array('checked' => FALSE),
        ),
      ),
    );
  }


  field_attach_form('queues', $QueueEntity, $form, $form_state);

  // TODO: Save the "label" of the queue.
  $form['actions'] = array(
    '#type' => 'actions',
    'submit' => array(
      '#type' => 'submit',
      '#value' => t('Save queue'),
      '#weight' => 20,
    ),
  );


  return $form;
}

function queues_form_submit($form, &$form_state) {
  $QueueEntity = $form_state['queues'];
  entity_form_submit_build_entity('queues', $QueueEntity, $form, $form_state);
  $QueueEntity->save();
  $form_state['redirect'] = 'admin/content/queues';
}

function queues_confirm_delete_revision_form($form, &$form_state, $qid, $vid) {
  $queue = queue_load($qid);

  if ($queue->vid == $vid) {
    drupal_set_message(t('This revision cannot be deleted because it is currently the primary revision for this queue'), 'error');
    drupal_goto('admin/content/queues/manage/' . $qid . '/revisions-state-flow-states');
  }
  else {
    $form = array(
      'qid' => array(
        '#type' => 'value',
        '#value' => $qid,
      ),
      'vid' => array(
        '#type' => 'value',
        '#value' => $vid,
      ),
    );
    return confirm_form($form, t('Are you sure you want to delete this revision?'), "admin/content/queues/manage/$qid/revisions-state-flow-states", t('This action cannot be undone.'), t('Delete revision'), t('Cancel'));
  }
}

function queues_confirm_delete_revision_form_submit($form, &$form_state) {
  $qid = $form_state['values']['qid'];
  $vid = $form_state['values']['vid'];

  if (entity_revision_delete('queues', $vid)) {
    drupal_set_message(t('The revision has been successfully deleted.'));
  }
  else {
    drupal_set_message(t('The revision could not be deleted.'), 'error');
  }

  drupal_goto('admin/content/queues/manage/' . $qid . '/revisions-state-flow-states');
}
