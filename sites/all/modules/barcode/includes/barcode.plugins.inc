<?php

/**
 * @file
 * Code to load barcode symbology plugins 
 */ 

/**
 * Builds and return a list of all plugins available in the system.
 *
 * @return Nested array of plugins, grouped by type and
 */
function barcode_discover_plugins() {
  // @TODO: we should probably just turn the plugins into modules and discover
  // this through hooks.
  $plugins['ean'] = array(
    'UPC-A' => t('UPC-A'),
    'EAN-13' => t('EAN-13'),
    'ISBN' => t('ISBN')
  );
  $plugins['ean8'] = array('EAN-8' => t('EAN-8'));
  $plugins['upce'] = array('UPC-E' => t('UPC-E'));
  $plugins['s2o5'] = array(
    'S2O5' => t('Standard 2 of 5'), 
    'I2O5' => t('Industrial 2 of 5')
  );
  $plugins['i25'] = array('I25' => t('Interleaved 2 of 5'));
  $plugins['postnet'] = array('POSTNET' => t('Postnet'));
  $plugins['codabar'] = array('CODABAR' => t('Codabar'));
  $plugins['code128'] = array('CODE128' => t('Code 128'));
  $plugins['code39'] = array('CODE39' => t('Code 39'));
  $plugins['code93'] = array('CODE93' => t('Code 93'));
  $plugins['qrcode'] = array('QRCODE' => t('QR Code'));
  return $plugins;
}

/**
 * Return the plugin filename containing the given encoding.
 */
function barcode_load_plugin($encoding_name) {
  $plugins = barcode_discover_plugins();
  foreach ($plugins as $plugin => $encodings) {
    foreach ($encodings as $encoding => $display_string) {
      if ($encoding == $encoding_name) {
        module_load_include('inc', 'barcode', 'plugins/' . $plugin);
        return $plugin;
      }
    }
  }
  return '';
}

function barcode_plugin_generate_image($plugin, $barcode, $settings) {
  $gen_function = 'barcode_'. $plugin .'_barcode';
  $gen_function($barcode, $settings);
}

function barcode_plugin_max_length($encoding_name) {
  $plugin = barcode_load_plugin($encoding_name);
  $max_length_function = 'barcode_'. $plugin .'_max_length';

  if (function_exists($max_length_function)) {
    return $max_length_function($encoding_name);
  }
}

/**
 * Creates or return the plugin filename containing the given encoding.
 */
function barcode_generate_image($barcode, $variables) {
  $name = md5($variables['barcode_value']);
  $filename_noformat = $barcode['default_path'] .'/'. $name . $variables['encoding'];
  $filename = $filename_noformat .'.'. $variables['image_format'];
  
  // First check if the images already exists.
  if (!file_exists($filename)) {
    $plugin = barcode_load_plugin($variables['encoding']);

    $settings->default_path = drupal_realpath($barcode['default_path']);
    $settings->encode = $variables['encoding'];
    $settings->height = $variables['height'];
    $settings->font = $barcode['font'];
    $settings->format = $variables['image_format'];
    // GD library fails on stream wrappers - get the realpath.
    $settings->filename_no_format = drupal_realpath($filename_noformat);
    $settings->n2w = 2;

    if ($variables['encoding'] != 'QRCODE') {
      $settings->color = array(hexdec(substr($variables['barcolor'], 1, 2)), hexdec(substr($variables['barcolor'], 3, 2)), hexdec(substr($variables['barcolor'], 5, 2)));
      $settings->bgcolor = array(hexdec(substr($variables['bgcolor'], 1, 2)), hexdec(substr($variables['bgcolor'], 3, 2)), hexdec(substr($variables['bgcolor'], 5, 2)));
      $settings->scale = $variables['scale'];   
    }
    barcode_plugin_generate_image($plugin, $variables['barcode_value'], $settings);
  }
  
  if (!file_exists($filename)) {
    watchdog('barcode', 'Failed to generate image using settings @settings', array('@settings' => print_r($settings, TRUE)));
    return FALSE;
  }

  return $filename;
}

function barcode_check_digit($barnumber, $number) {
  $csum_total = 0; // The checksum working variable starts at zero

  // If the source message string is less than 12 characters long, we make it 
  // 12 characters
  if (strlen($barnumber) < $number) {
    $barnumber = str_pad($barnumber, $number, "0", STR_PAD_LEFT);
  }

  // Calculate the checksum value for the message
  for ($i = 0; $i < strlen($barnumber); $i++) {
    if ($i % 2 == 0) {
      $csum_total = $csum_total + (3 * intval($barnumber{$i}));
    }
    else {
      $csum_total = $csum_total + intval($barnumber{$i});
    }
  }

  // Calculate the checksum digit
  if ($csum_total % 10 == 0) {
    $checksum_digit = '';
  }
  else {
    $checksum_digit = 10 - ($csum_total % 10);
  }

  return $barnumber . $checksum_digit;
}
