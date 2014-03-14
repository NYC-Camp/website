<?php

/**
 * @file QueueEntityType
 *
 * Class API and helper for our QueueEntityType.
 */
use \Drupal\Queues;

/**
 * QueueEntityType
 *
 * Extends Entity, sets up sane defaults for us.
 */
class QueueEntityType extends Entity {
  public $label;
  public $type;
  public $target = 'node';
  public $is_new = FALSE;

  protected function defaultLabel() {
    return $this->label;
  }

  public function create(array $values = array()) {
    $values += array(
      'label' => ''
    );
    return parent::create($values);
  }

  public function save() {
    parent::save();

    // Lets make sure our fields exists.
    // We do this after we save our entity.
    _queues_type_ensure_instance($this);
  }
}

/**
 * Load an QueueEntityType from the db.
 *
 * @param $type
 *   The type to be loaded.
 *
 * @see queues_type_get_types()
 */
function queues_type_load($type) {
  return queues_type_get_types($type);
}

/**
 * Load an QueueEntityType from the db by name.
 *
 * @param $type
 *   The type to be loaded.
 *
 * @see queues_type_load()
 */
function queues_type_get_types($name = NULL) {
  $types = entity_load_multiple_by_name('queues_type', isset($name) ? array($name) : FALSE);
  return isset($name) ? reset($types) : $types;
}

/**
 * Load an QueueEntityType from the db by name.
 *
 * @param $type
 *   The type to be loaded.
 *
 * @see queues_type_load()
 */
function queues_type_form($form, $form_state, $QueueEntityType, $op = 'edit') {

  $form['label'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#default_value' => $QueueEntityType->label,
    '#description' => t('The human-readable name of this queue type. This text will be displayed as part of the list on the Add new queue page. It is recommended that this name begin with a capital letter and contain only letters, numbers, and spaces. This name must be unique.'),
  );

  $form['type'] = array(
    '#type' => 'machine_name',
    '#title' => t('machine_name'),
    '#maxlength' => 32,
    '#default_value' => $QueueEntityType->type,
    '#machine_name' => array(
      'exists' => 'queues_type_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this queue type. It must only contain lowercase letters, numbers, and underscores. This name will be used for constructing the URL of the Add new queue page, in which underscores will be converted into hyphens.'),
  );

  // Get valid target entity types.
  $entity_info = entity_get_info();
  unset($entity_info['queues'], $entity_info['queues_type']);

  $entity_types = array();
  foreach ($entity_info as $entity_type => $info) {
    $entity_types[$entity_type] = $info['label'];
  }
  $form['target'] = array(
    '#title' => t('Entity type'),
    '#type' => 'select',
    '#options' => $entity_types,
    '#default_value' => $QueueEntityType->target,
    '#required' => TRUE,
    '#disabled' => $QueueEntityType->is_new ? FALSE : TRUE,
    '#ajax' => array(
      'callback' => 'queues_export_ui_target_type_callback',
      'wrapper' => 'entityqueue-target-bundles',
    ),
  );

  $form['settings'] = array(
    '#type' => 'vertical_tabs',
    '#tree' => TRUE,
  );

  $target = !empty($form_state['values']['target']) ? $form_state['values']['target'] : $QueueEntityType->target;
  $bundles = array();
  foreach ($entity_info[$target]['bundles'] as $bundle_name => $bundle_info) {
    $bundles[$bundle_name] = $bundle_info['label'];
  }

  $form['settings']['entityreference_field'] = array(
    '#type' => 'fieldset',
    '#title' => t('Entityreference field settings'),
    '#collapsible' => TRUE,
  );

  $form['settings']['entityreference_field']['cardinality'] = array(
    '#title' => t('Number of values'),
    '#disabled' => $QueueEntityType->is_new ? FALSE : TRUE,
    '#type' => 'select',
    '#default_value' => isset($QueueEntityType->settings['entityreference_field']['cardinality']) ? $QueueEntityType->settings['entityreference_field']['cardinality'] : -1,
    '#options' => array(
      '-1' => t('Unlimited'),
      '1' => t('1'),
      '2' => t('2'),
      '3' => t('3'),
      '4' => t('4'),
      '5' => t('5'),
      '6' => t('6'),
      '7' => t('7'),
      '8' => t('8'),
      '9' => t('9'),
      '10' => t('10'),
    ),
  );

  $form['settings']['entityreference_field']['target_bundles'] = array(
    '#type' => 'checkboxes',
    '#disabled' => $QueueEntityType->is_new ? FALSE : TRUE,
    '#title' => $target == 'node' ? t('Content types') : t('Bundles'),
    '#prefix' => '<div id="entityqueue-target-bundles">',
    '#suffix' => '</div>',
    '#options' => $bundles,
    '#default_value' => !empty($QueueEntityType->settings['entityreference_field']['target_bundles']) ? $QueueEntityType->settings['entityreference_field']['target_bundles'] : array(),
    '#multiple' => TRUE,
    '#description' => t('The bundles of the entity type that can be referenced. Optional, leave empty for all bundles.'),
  );



  $form['actions'] = array(
    '#type' => 'actions',
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save queue type'),
    '#weight' => 20,
  );

  return $form;
}

/**
 * Selects just the target bundles dropdown to be returned for re-rendering.
 *
 * @return array
 *  A renderable array representing the target bundles dropdown.
 */
function queues_export_ui_target_type_callback($form, $form_state) {
  return $form['settings']['entityreference_field']['target_bundles'];
}


/**
 * Form API submit callback for the type form.
 */
function queues_type_form_submit(&$form, &$form_state) {
  unset($form_state['values']['settings']['settings__active_tab']);

  $QueueEntityType = entity_ui_form_submit_build_entity($form, $form_state);
  $QueueEntityType->save();

  $form_state['redirect'] = 'admin/structure/queues';
}

/**
 * Makes sure that a entityreference field instance exists for a queue.
 *
 * @param EntityQueue $queue
 *   An EntityQueue object.
 */
function _queues_type_ensure_instance(QueueEntityType $QueueEntityType) {
  $field_name = _queues_get_target_field_name($QueueEntityType->identifier());

  if (!field_info_instance('queues', $field_name, $QueueEntityType->type)) {
    _queues_create_entityreference_field($QueueEntityType, $field_name, 'queues', $QueueEntityType->type, t('Queue items'), 0, array());
  }
}

/**
 * Creates a locked instance of a entityreference field on the specified bundle.
 *
 * @param EntityQueue $queue
 *   An EntityQueue object.
 * @param string $field_name
 *   The name of the field; if it already exists, a new instance of the existing
 *   field will be created.
 * @param string $entity_type
 *   The type of entity the field instance will be attached to.
 * @param string $bundle
 *   The bundle name of the entity the field instance will be attached to.
 * @param string $label
 *   The label of the field instance.
 * @param int $weight
 *   The default weight of the field instance widget and display.
 * @param array $display
 *   An array of default display data used for the entity's current view modes.
 * @param array $handler_settings
 *   An array of Entityrefence field handler settings.
 */
function _queues_create_entityreference_field($QueueEntityType, $field_name, $entity_type, $bundle, $label, $weight = 0, $display = array()) {
  // If a field type we know should exist isn't found, clear the Field cache.
  if (!field_info_field_types('entityreference')) {
    field_cache_clear();
  }

  // Look for or add the specified entityreference field to the requested entity
  // bundle.
  $field = field_info_field($field_name);
  $instance = field_info_instance($entity_type, $field_name, $bundle);
  if (empty($field)) {
    $field = array(
      'field_name' => $field_name,
      'type' => 'entityreference',
      'cardinality' => $QueueEntityType->settings['entityreference_field']['cardinality'],
      'entity_types' => array($entity_type),
      'translatable' => FALSE,
      'locked' => FALSE, // Lets not lock it for now.
      'settings' => array(
        'target_type' => $QueueEntityType->target,
        'handler' => 'base',
        'handler_settings' => array(
          'target_bundles' => $QueueEntityType->settings['entityreference_field']['target_bundles'],
          'sort' => array('type' => 'none')
        ),
      ),
    );
    field_create_field($field);
  }

  if (empty($instance)) {
    $instance = array(
      'field_name' => $field_name,
      'entity_type' => $entity_type,
      'bundle' => $bundle,

      'label' => $label,
      'required' => FALSE,
      'settings' => array(),

      'widget' => array(
        'type' => 'entityreference_autocomplete',
        'weight' => $weight,
        'settings' => array(
          'match_operator' => 'CONTAINS',
          'size' => 60,
          'path' => '',
        ),
      ),

      'display' => $display,
    );
    field_create_instance($instance);
    field_cache_clear(TRUE);
  }
}
