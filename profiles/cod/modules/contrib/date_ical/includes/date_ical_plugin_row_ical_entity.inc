<?php

/**
 * @file
 * Contains the iCal row style plugin.
 */

/**
 * Plugin which creates a view on the resulting object
 * and formats it as an iCal VEVENT.
 */
class date_ical_plugin_row_ical_entity extends views_plugin_row {
  
  // Basic properties that let the row style follow relationships.
  var $base_table = 'node';
  var $base_field = 'nid';
  
  // Stores the nodes loaded with pre_render.
  var $entities = array();
  
  function init(&$view, &$display, $options = NULL) {
    parent::init($view, $display, $options);
    $this->base_table = $view->base_table;
    $this->base_field = $view->base_field;
  }
  
  function option_definition() {
    $options = parent::option_definition();
    $options['date_field'] = array('default' => array());
    $options['location_field'] = array('default' => array());
    return $options;
  }
  
  /**
   * Provide a form for setting options.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    
    // Build the select dropdown for the date field that the user wants to use
    // to populate the date fields in VEVENTs.
    $data = date_views_fields($this->base_table);
    $options = array();
    foreach ($data['name'] as $item => $value) {
      // We only want to see one value for each field, skip '_value2', and other columns.
      if ($item == $value['fromto'][0]) {
        $options[$item] = $value['label'];
      }
    }
    $form['date_field'] = array(
      '#type' => 'select',
      '#title' => t('Date field'),
      '#options' => $options,
      '#default_value' => $this->options['date_field'],
      '#description' => t('Please identify the field to use as the iCal date for each item in this view.
          Add a Date Filter or a Date Argument to the view to limit results to content in a specified date range.'),
      '#required' => TRUE,
    );
    $form['instructions'] = array(
      // The surrounding <div> is necessary to ensure that the settings dialog expands to show everything.
      '#prefix' => '<div style="font-size: 90%">',
      '#suffix' => '</div>',
      '#markup' => t("Each item's Title and iCal view mode will be included as the SUMMARY and DESCRIPTION elements (respectively) in the VEVENTs output by this View.
        <br>To change the iCal view mode, configure it on the 'Manage Display' page for each Content Type.
        Please note that HTML will be stripped from the output (link URLs will become footnotes), to comply with iCal standards."),
    );
    
    // Build the select dropdown for the text/node_reference field that the user
    // wants to use to (optionally) populate the LOCATION.
    $location_fields = date_ical_get_location_fields($this->base_table);
    $location_options = array('none' => '- None -');
    foreach ($location_fields['name'] as $item => $value) {
      $location_options[$item] = $value['label'];
    }
    $form['location_field'] = array(
      '#type' => 'select',
      '#title' => t('LOCATION field'),
      '#options' => $location_options,
      '#default_value' => $this->options['location_field'],
      '#description' => t('You may optionally include a LOCATION component for each event in the iCal output.
        Choose which text or Node Reference field you would like to be output as the LOCATION.
        If using a Node Reference, the Title of the referenced node will be used.'),
    );
  }
  
  function pre_render($values) {
    // @TODO When the date is coming in through a relationship, the nid
    // of the view is not the right node to use, then we need the related node.
    // Need to sort out how that should be handled.
    
    // Preload each entity used in this view from the cache.
    // Provides all the entity values relatively cheaply, and we don't
    // need to do it repeatedly for the same entity if there are
    // multiple results for one entity.
    $ids = array();
    foreach ($values as $row) {
      // Use the $id as the key so we don't create more than one value per entity.
      $id = $row->{$this->field_alias};
      
      // Node revisions need special loading.
      if ($this->view->base_table == 'node_revision') {
        $this->entities[$id] = node_load(NULL, $id);
      }
      // For other entities we just create an array of ids to pass
      // to entity_load().
      else {
        $ids[$id] = $id;
      }
    }
    
    $base_tables = date_views_base_tables();
    $this->entity_type = $base_tables[$this->view->base_table];
    if (!empty($ids)) {
      $this->entities = entity_load($this->entity_type, $ids);
    }
    
    // Get the language for this view.
    $this->language = $this->display->handler->get_option('field_language');
    $substitutions = views_views_query_substitutions($this->view);
    if (array_key_exists($this->language, $substitutions)) {
      $this->language = $substitutions[$this->language];
    }
  }
  
  function render($row) {
    global $base_url;
    $id = $row->{$this->field_alias};
    if (!is_numeric($id)) {
      return;
    }
    
    // Load the specified entity:
    $entity = $this->entities[$id];
    if (empty($entity)) {
      return;
    }
    
    $date_fields = date_views_fields($this->base_table);
    $date_info = $date_fields['name'][$this->options['date_field']];
    $field_name  = str_replace(array('_value', '_value2'), '', $date_info['real_field_name']);
    $table_name  = $date_info['table_name'];
    $delta_field = $date_info['delta_field'];
    $is_field    = $date_info['is_field'];
    
    // This is ugly and hacky but I can't figure out any generic way to
    // recognize that the node module is going to give some the revision timestamp
    // a different field name on the entity than the actual column name in the database.
    if ($this->view->base_table == 'node_revision' && $field_name == 'timestamp') {
      $field_name = 'revision_timestamp';
    }
    
    if (!isset($entity->$field_name)) {
      // This entity doesn't have the date property that the user configured
      // our view to use. We can't do anything with it
      return;
    }
    $date_field = $entity->$field_name;
    
    // Pull the date value from the specified field of the entity.
    $entity->date_id = array();
    $start = NULL;
    $end   = NULL;
    $lang = $entity->language;
    $delta = isset($row->$delta_field) ? $row->$delta_field : 0;
    if ($is_field) {
      $items = field_get_items($this->entity_type, $entity, $field_name);
      if (!$items) {
        // This entity doesn't have data in the date field that the user
        // configured our view to use. We can't do anything with it.
        return;
      }
      $date_field = $items[$delta];
      $domain = check_plain($_SERVER['SERVER_NAME']);
      $entity->date_id[] = "calendar.$id.$field_name.$delta@$domain";
      
      if (!empty($date_field['value'])) {
        $start = new DateObject($date_field['value'], $date_field['timezone_db']);
        if (array_key_exists('value2', $date_field)) {
          $end = new DateObject($date_field['value2'], $date_field['timezone_db']);
        }
        else {
          $end = clone $start;
        }
      }
    }
    elseif (!$is_field && !empty($date_field)) {
      $start = new DateObject($date_field, $date_field['timezone_db']);
      $end   = new DateObject($date_field, $date_field['timezone_db']);
    }
    
    // Set the item date to the proper display timezone.
    $start->setTimezone(new dateTimezone($date_field['timezone']));
    $end->setTimezone(new dateTimezone($date_field['timezone']));
    
    $start_formatted = $start->format(DATE_FORMAT_DATETIME);
    $end_formatted = $end->format(DATE_FORMAT_DATETIME);
    
    $all_day = date_is_all_day($start_formatted, $end_formatted, date_granularity_precision($date_info['granularity']));
    
    // According to RFC 2445 (clarified in RFC 5545) the DTEND value is
    // non-inclusive. When it is a DATE rather than a DATETIME, this means
    // that we should add one day to its value.
    if ($all_day) {
      $end->modify("+1 day");
    }
    
    module_load_include('inc', 'date_api', 'date_api_ical');
    
    // If the user specified a LOCATION field, pull that data from the entity.
    $location = '';
    if (!empty($this->options['location_field']) && $this->options['location_field'] != 'none') {
      $location_fields = date_ical_get_location_fields();
      $location_info = $location_fields['name'][$this->options['location_field']];
      $location_field_name = $location_info['real_field_name'];
      
      // Only attempt this is the entity actually has this field.
      $items = field_get_items($this->entity_type, $entity, $location_field_name);
      if ($items) {
        $location_field = $items[$delta];
        
        if ($location_info['type'] == 'node_reference') {
          // Make sure this Node Reference actually references a node.
          if ($location_field['nid']) {
            $node = node_load($location_field['nid']);
            $location = check_plain($node->title);
          }
        }
        else {
          $location = check_plain($location_field['value']);
        }
      }
    }
    
    // Create the rendered display using the display settings from the 'iCal' view mode.
    $rendered_array = entity_view($this->entity_type, array($entity), 'ical', $this->language, TRUE);
    $item_text = drupal_render($rendered_array);
    
    $event = array();
    $event['summary'] = trim(drupal_html_to_text(entity_label($this->entity_type, $entity)));
    $event['description'] = trim(drupal_html_to_text($item_text));
    $event['all_day'] = $all_day;
    $event['start'] = $start;
    $event['end'] = $end;
    $uri = entity_uri($this->entity_type, $entity);
    $uri['options']['absolute'] = TRUE;
    $event['url'] = url($uri['path'], $uri['options']);
    $event['uid'] = !empty($entity->date_id) ? $entity->date_id[0] : $event['url'];
    $event['rrule'] = $is_field && array_key_exists('rrule', $date_field) ? $date_field['rrule'] : '';
    if ($location) {
      $event['location'] = $location;
    }
    
    // Pull the 'changed' date from the entity, so that subscription clients can tell if the event has been updated.
    // According to the iCal standard, LAST-MODIFIED must be UTC. Fortunately, Drupal stores timestamps in the DB
    // as UTC, so we just need to specify that UTC be used rather than the server's local timezone.
    $event['last-modified'] = new DateObject($entity->changed, new DateTimeZone('UTC'));
    
    // Allow other modules to alter the structured event object, before it gets converted to an iCal VEVENT.
    $context = array(
      'entity' => $entity,
      'entity_type' => $this->entity_type,
      'language' => $this->language,
    );
    drupal_alter('date_ical_feed_event_render', $event, $this->view, $context);
    
    return $event;
  }
}
