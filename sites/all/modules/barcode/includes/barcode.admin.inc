<?php

/**
 * @file
 * Code for the issue status admin configuration form.
 */ 

/**
  * Menu callback to configure barcode module settings.
  */
function barcode_settings() {
  $barcode = barcode_get_settings();

  $form['barcode_default_path'] = array(
    '#title' => t('Default path'),
    '#description' => t('A file system URI where the barcode images will be stored. Changing this location will cause that barcodes will be generated again upon view.'),
    '#type' => 'textfield',
    '#default_value' => $barcode['default_path'],
    '#size' => 60,
    '#required' => TRUE,
  );
  $form['barcode_font'] = array(
    '#title' => t('Font file'),
    '#description' => t("The font used in barcode, must be relative path to Drupal's base."),
    '#type' => 'textfield',
    '#default_value' => $barcode['font'],
    '#size' => 100,
    '#required' => TRUE,
  );
  return system_settings_form($form);
}

function barcode_settings_validate($form, &$form_state) {

  $created = file_prepare_directory($form_state['values']['barcode_default_path'], FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS);

  if (!$created) {
    form_set_error('barcode_default_path', t('Path could not be created or made writeable.'));
  }
}
