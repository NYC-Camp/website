<?php
/**
 * @file
 * Admin functionality, separated for performance purposes.
 */

/**
 * The settings form.
 */
function corresponding_node_references_settings_form() {
  $form['intro'] = array('#markup' => t('Check which node references should listen to each other. When checking a check box a reference on node type A to node B will automatically update the node reference field on node B adding an entrie which points to node A.'));

  $result = db_query("SELECT field_name, data FROM {field_config} WHERE type = :type AND deleted = 0", array(':type' => 'node_reference'));
  foreach ($result as $row) {
    $data = unserialize($row->data);
    foreach ($data['settings']['referenceable_types'] as $reference) {
      if ($reference != '0') {
        $references[$row->field_name][] = $reference;
      }
    }
  }

  $result = db_query("SELECT fci.field_name, fci.entity_type, fci.bundle FROM {field_config_instance} fci INNER JOIN {field_config} fc ON fc.field_name = fci.field_name WHERE fc.type = :type", array(':type' => 'node_reference'));

  foreach ($result as $row) {
    if (!empty($references[$row->field_name])) {
      foreach ($references[$row->field_name] as $reference) {
        if ($row->entity_type == 'node') {
          $fields_to_compare[] = array('field_type' => $row->field_name, 'bundle' => $row->bundle, 'reference' => $reference);
        }
      }
    }
  }
  if (!empty($fields_to_compare)) {
    $corr_noderefs = array();
    foreach ($fields_to_compare as $field) {
      foreach ($fields_to_compare as $second_field) {
        if ($field['bundle'] == $second_field['reference'] && $second_field['bundle'] == $field['reference']) {
          if (!array_key_exists($field['bundle'] . ' ' . $field['field_type'] . ' ' . $second_field['bundle'] . ' ' . $second_field['field_type'], $corr_noderefs) && !array_key_exists($second_field['bundle'] . ' ' . $second_field['field_type'] . ' ' . $field['bundle'] . ' ' . $field['field_type'], $corr_noderefs)) {
            $corr_noderefs[$field['bundle'] . ' ' . $field['field_type'] . ' ' . $second_field['bundle'] . ' ' . $second_field['field_type']] = array('bundle_1' => $field['bundle'], 'field_1' => $field['field_type'], 'bundle_2' => $second_field['bundle'], 'field_2' => $second_field['field_type']);
          }
        }
      }
    }

    if (!empty($corr_noderefs)) {
      $count = 0;
      foreach ($corr_noderefs as $key => $corr_noderef) {
        $formated_label = corresponding_node_references_format_label($key);
        $formated_key = str_replace(' ', '*', $key);
        $mapping[] = $formated_key;
        $form['values'][$count] = array(
          '#type' => 'fieldset',
        );
        $form['values'][$count]['enabled_' . $count] = array(
          '#type' => 'checkbox',
          '#default_value' => corresponding_node_references_preset_enabled($formated_key),
          '#title' => $formated_label,
        );
        $count++;
      }

      //We are using a hidden field to submit the configuration because on some systems the checkbox name length is limited
      //, using the key would cause the length to be too long see issue #558612
      $form['mapping'] = array(
        '#type' => 'hidden',
        '#value' => serialize($mapping),
      );
      $form['submit'] = array('#type' => 'submit', '#value' => t('Save'));
    }
  }
  else {
    $form['text'] = array('#markup' => '<div>' . t('There are no node types which have a corresponding node reference') . '</div>');
  }


  return $form;
}

/**
 * Submit function for settings form.
 */
function corresponding_node_references_settings_form_submit($form, $form_values) {
  ctools_include('export');
  $query_values = array();

  $mapping = unserialize($form_values['values']['mapping']);
  foreach ($form_values['values'] as $key => $value) {
    $keys = explode('_', $key);
    if ($keys[0] == 'enabled') {
      $query_values[$mapping[$keys[1]]] = $value;
    }
  }

  // load all existing presets
  $presets = ctools_export_crud_load_all('corresponding_node_references');

  foreach ($query_values as $key => $value) {
    // get preset object (create new one if it doesn't exist already).
    $preset = empty($presets[$key]) ? ctools_export_crud_new('corresponding_node_references') : $presets[$key];
    // set and save value
    if (empty($preset->node_types_content_fields)) {
      $preset->node_types_content_fields = $key;
    }
    $preset->enabled = $value;
    ctools_export_crud_save('corresponding_node_references', $preset);
    // remove from list of presets, so we know which ones are still used
    if (isset($presets[$key])) unset($presets[$key]);
  }

  // delete old presets
  foreach ($presets as $preset) {
    //ctools_export_crud_delete($preset);
  }

  drupal_set_message(t('The configuration has been saved'));
}

/**
 * The update form.
 * Allows updating of current nodes.
 */
function corresponding_node_references_update_form() {
  $form = array();

  $form['intro'] = array(
    '#value' => t('This will update all the existing nodes for the selected content types so that their node reference fields are in sync.') . '<br />' . t('This process may take a long time depending on the number of nodes you are updating.') . '<br />' . t('When the process is finished you will see a count of the number of nodes that were updated.')
  );

  $options = _node_types_build()->types;
  foreach ($options as $type => $class) {
    $options[$type] = $class->name;
  }

  $form['types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Node types'),
    '#options' => $options,
    '#description' => t('Select the node types that you want to update.'),
  );

  $form['limit'] = array(
    '#type' => 'select',
    '#title' => t('Number of nodes to process at once'),
    '#options' => array(
      10 => t('10'),
      20 => t('20'),
      30 => t('30'),
      50 => t('50'),
      75 => t('75'),
      100 => t('100'),
      125 => t('125'),
      150 => t('150'),
      200 => t('200'),
      250 => t('250'),
      300 => t('300'),
      350 => t('350'),
      400 => t('400'),
      450 => t('450'),
      500 => t('500'),
    ),
    '#default_value' => 50,
    '#description' => t('This process is done in batches. This is the number of nodes processed in each batch. If necessary, reduce the number of nodes to prevent timeouts and memory errors while processing.'),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'submit',
  );

  return $form;
}

/**
 * The update form.
 * Allows updating of current nodes.
 */
function corresponding_node_references_update_form_validate($form, &$form_state) {
  $types = array_filter($form_state['values']['types']);
  if (empty($types)) {
    form_set_error('types', t('You must select at least one node type.'));
  }
}

/**
 * The update form.
 * Allows updating of current nodes.
 */
function corresponding_node_references_update_form_submit($form, &$form_state) {
  $types = array_filter($form_state['values']['types']);
  $types = array_keys($types);
  corresponding_node_references_batch_index_remaining($types, $form_state['values']['limit']);
}