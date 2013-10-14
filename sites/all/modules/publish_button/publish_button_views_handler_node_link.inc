<?php
/**
 * @file
 * View handler for the module.
 */

/**
 * Extends the node link handler.
 */
class publish_button_views_handler_node_link extends views_handler_field_node_link {
  function construct() {
    parent::construct();
    $this->additional_fields['nid'] = 'nid';
    $this->additional_fields['status'] = 'status';
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array('default' => '', 'translatable' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    // The default handler only have one text to display, unset to use two.
    unset($form['text']);
    $form['publish_button_publish'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display for publishing'),
      '#default_value' => $this->options['publish'],
    );
    $form['publish_button_unpublish'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display for unpublishing'),
      '#default_value' => $this->options['unpublish'],
    );
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    $value = $this->get_value($values, 'nid');
    return $this->render_link($this->sanitize_value($value), $values);
  }

  function render_link($data, $values) {
    // Load the node to get the type, better programming needed...
    $node = node_load($data);
    if (_publish_button_publish_permissions($node->type) == TRUE && _publish_button_unpublish_permissions($node->type) == TRUE) {
      if ($values->node_status) {
        $status = 'unpublish';
      }
      if (!$values->node_status) {
        $status = 'publish';
      }
      if (isset($this->options['alter'])) {
        $this->options['alter']['make_link'] = TRUE;
        $this->options['alter']['path'] = 'publish_button/' . $data . '/' . $status;
        $this->options['alter']['query'] = drupal_get_destination();
        $text = empty($this->options[$status]) ? t($status) : $this->options[$status];
        $publish_button = array(
          '#type' => 'button',
          '#access' => TRUE,
          '#value' =>  $text ,
          '#weight' => '30',
        );
        return $publish_button;
      }
    }
  }
}
