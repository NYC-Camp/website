<?php

/**
 * @file
 * This file holds style plugin Timefield MiniCal
 *
 */

/**
 * @class
 * Extension of the Views Plugin Syle for
 */
class TimefieldPluginStyleMinical extends views_plugin_style {
  /**
   * Set default options
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['data_source'] = array('default' => '');
    $options['box_source'] = array('default' => '');
    return $options;
  }

  /**
   * Options form
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $handlers = $this->display->handler->get_handlers('field');

    $data_source_options = $box_source_options = array(
      '' => '<none>',
    );

    foreach ($handlers as $handle) {
      $box_source_options[$handle->options['id']] = (!empty($handle->options['label'])) ? $handle->options['label'] : $handle->options['id'];

      if (!empty($handle->field_info['type']) && $handle->field_info['type'] == 'timefield') {
        $data_source_options[$handle->options['id']] = $handle->options['label'];
      }
    }

    if (count($data_source_options) == 1) {
      $form['error'] = array(
        '#markup' => 'Please add at least 1 weekly summary field to the view',
      );
    }
    else {

      $form['data_source'] = array(
        '#type' => 'select',
        '#title' => t('Data Source'),
        '#description' => t('What field provides the weekly summary (timefield) data?'),
        '#options' => $data_source_options,
        '#default_value' => $this->options['data_source'] ? $this->options['data_source'] : '',
      );

      $form['box_source'] = array(
        '#type' => 'select',
        '#title' => t('Fill in Text'),
        '#description' => t('What field provides the content for the mini-calendar table cell?'),
        '#options' => $box_source_options,
        '#default_value' => $this->options['box_source'] ? $this->options['box_source'] : '',
      );
    }
  }

  /**
   * Renders views
   */
  function render() {
    $style_options = $this->view->style_options;

    $cal_data = (!empty($style_options['data_source'])) ? 'field_' . $style_options['data_source']: NULL;
    $box_data = (!empty($style_options['box_source'])) ? $style_options['box_source'] : NULL;

    $raw_data = array();
    if ($cal_data) {
      $this->render_fields($this->view->result);
      $raw_data = array();

      foreach ($this->view->result as $id => $result) {

        $times = (!empty($result->$cal_data)) ? $result->$cal_data : NULL;

        if (!empty($times)) {
          $description = ($box_data ? $this->rendered_fields[$id][$box_data] : '');

          foreach ($times as $item) {
            $item['raw']['label'] = $description;
            $raw_data[] = $item['raw'];
          }
        }
      }
    }

    $settings = array(
      'display_format' => array(
        'separator' => ':',
        'period_separator' => '',
        'period' => 'a',
        'hour' => 'g',
        'minute' => 'i',
      ),
      'column_format' => array(
        'separator' => ':',
        'period_separator' => '',
        'period' => 'a',
        'hour' => 'g',
        'minute' => 'i',
      ),
      'first_day' => 'mon',
      'absolute_start' => '8:00 am',
      'absolute_end' => '10:00 pm',
      'range' => 120,
      'adjust_range' => FALSE,
    );

    if (!empty($raw_data)) {
      $header = _timefield_weekly_summary_build_header($settings['first_day']);
      $rows = timefield_weekly_summary_build_rows($raw_data, $header, $settings);

      $element = array(
        '#header' => $header,
        '#rows' => $rows,
        '#theme' => 'table',
      );
    }
    else {
      $element = array('#markup' => 'No content');
    }

    return drupal_render($element);
  }
}
