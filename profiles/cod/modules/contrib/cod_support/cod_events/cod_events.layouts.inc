<?php
/**
 * @file
 * cod_events.layouts.inc
 */

/**
 * Implements hook_default_panels_layout().
 */
function cod_events_default_panels_layout() {
  $export = array();

  $layout = new stdClass();
  $layout->disabled = FALSE; /* Edit this to true to make a default layout disabled initially */
  $layout->api_version = 1;
  $layout->name = 'cod_events_dashboard_tabs';
  $layout->admin_title = 'cod_events_dashboard_tabs';
  $layout->admin_description = 'Provides a dashboard layout with tabs below and two or three blocks on top for summaries';
  $layout->category = 'cod';
  $layout->plugin = 'flexible';
  $layout->settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 'main',
        ),
        'parent' => NULL,
      ),
      'main' => array(
        'type' => 'column',
        'width' => 100,
        'width_type' => '%',
        'children' => array(
          0 => 'main-row',
          1 => 1,
        ),
        'parent' => 'canvas',
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'summary_left',
          1 => 'center',
          2 => 'summary_right',
        ),
        'parent' => 'main',
      ),
      'center' => array(
        'type' => 'region',
        'title' => 'summery_center',
        'width' => '37.913348503336',
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => '',
      ),
      'summary_left' => array(
        'type' => 'region',
        'title' => 'summary_left',
        'width' => '32.95402530147208',
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => '',
      ),
      'summary_right' => array(
        'type' => 'region',
        'title' => 'summary_right',
        'width' => '29.132626195191914',
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => '',
      ),
      1 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'dashboard_tabs',
        ),
        'parent' => 'main',
        'class' => '',
      ),
      'dashboard_tabs' => array(
        'type' => 'region',
        'title' => 'dashboard_tabs',
        'width' => 100,
        'width_type' => '%',
        'parent' => '1',
        'class' => '',
      ),
    ),
  );
  $export['cod_events_dashboard_tabs'] = $layout;

  return $export;
}
