<?php
/**
 * @defgroup views_field_handlers Views' field handlers
 * @{
 * Handlers to tell Views how to build and display fields.
 *
 */

/**
 * Base field handler that has no options and renders an unformatted field.
 *
 * Definition terms:
 * - additional fields: An array of fields that should be added to the query
 *                      for some purpose. The array is in the form of:
 *                      array('identifier' => array('table' => tablename,
 *                      'field' => fieldname); as many fields as are necessary
 *                      may be in this array.
 * - click sortable: If TRUE, this field may be click sorted.
 */

class views_handler_field_jeditable extends views_handler_field_boolean {
// class views_handler_field_jeditable extends views_handler_field_entity {
  /**
   * Render the field.
   *
   * @param $values
   *   The values retrieved from the database.
   */
  function render($values) {
    $value = $this->get_value($values);
//     krumo($this->field_alias); die;
//     krumo($value); die;
    $element['value']=$this->get_value($values);
    $field['field_name']=substr($this->field_alias,strpos($this->field_alias,'_')+1);
//     krumo($field['field_name']); die;
    $entity=$values->_field_data['nid']['entity'];
//     $entity_type['nid']=$values->nid;
    $entity_type=$values->_field_data['nid']['entity_type'];
//     $entity_type='node';
    $widget_type='textfield';
    $field_delta=0;
//     krumo(theme('jeditable_formatter_jeditable', array('element' => $item, 'field' => $instance, 'entity' => $entity, 'entity_type' => $entity_type, 'widget_type' => $widget_type, 'delta' => $field_delta ))); die;
    
    return theme('jeditable_formatter_jeditable', array('element' => $element, 'field' => $field, 'entity' => $entity, 'entity_type' => $entity_type, 'widget_type' => $widget_type, 'delta' => $field_delta ));
//     return $value;
//     return $this->sanitize_value($value);
  }
}
