<?php

/**
 * @file
 * Barcode plugin
 * UPC-E: Short version of UPC symbol, 6 characters
 */

function barcode_upce_max_length($encoding) {
  return 6;
}

function barcode_upce_barcode($barnumber, $settings) {
  if (strlen($barnumber)>6) {
    barcode_load_plugin('ean'); 
    barcode_ean13_check_digit($barnumber);
    $barnumber = substr($this->barcode_ean13_check_digit($barnumber), 1);
    $encbit = $barnumber[0];
    $checkdigit = $barnumber[11];
    $barnumber = barcode_convert_upca_to_upce($barnumber);
  }
  else {
    $barnumber = barcode_check_digit($barnumber, 7);
    $encbit = $barnumber[0];
    $checkdigit = $barnumber[7];
    $barnumber = substr($barnumber, 1, 6);
  }

  $bars = barcode_upce_encode($barnumber, $settings, $encbit, $checkdigit);

  if (empty($settings->filename_no_format)) {
    header("Content-type: image/". $settings->format);
  }

  $scale = $settings->scale;
  if ($scale < 1) {
    $scale = 2;
  }

  $total_y = (double)$scale * $settings->height;
  if (!$space) {
    $space = array(
      'top' => 2 * $scale,
      'bottom' => 2 * $scale,
      'left' => 2 * $scale,
      'right' => 2 * $scale
    );
  }

  /* count total width */
  $xpos=$scale*strlen($bars)+$scale*12;

  /* allocate the image */
  $total_x = $xpos + $space['left'] + $space['right'];
  $xpos = $space['left'] + ($scale * 6);

  $height = floor($total_y - ($scale * 10));
  $height2 = floor($total_y - $space['bottom']);

  $im = @imagecreatetruecolor($total_x, $total_y);
  $bg_color = @imagecolorallocate($im, $settings->bgcolor[0], $settings->bgcolor[1], $settings->bgcolor[2]);
  @imagefilledrectangle($im, 0, 0, $total_x, $total_y, $bg_color);
  $bar_color = @imagecolorallocate($im, $settings->color[0], $settings->color[1], $settings->color[2]);

  for ($i=0; $i < strlen($bars); $i++) {
    $h = $height;
    $val = strtoupper($bars[$i]);
    if (preg_match("/[a-z]/i", $val)) {
      $val = ord($val) - 65;
      $h = $height2;
    }

    if ($val == 1) {
      @imagefilledrectangle($im, $xpos, $space['top'], $xpos + $scale - 1, $h, $bar_color);
    }

    $xpos += $scale;
  }

  @imagettftext($im, $scale * 6, 0, $space['left'], $height, $bar_color, $settings->font, $encbit);

  $x = $space['left'] + $scale * strlen($barnumber) + $scale * 6;
  @imagettftext($im, $scale * 6, 0, $x, $height2, $bar_color, $settings->font, $barnumber);

  $x = $total_x - $space['left'] - $scale * 6;
  @imagettftext($im, $scale * 6, 0, $x, $height, $bar_color, $settings->font, $checkdigit);

  if ($settings->format == "png") {
    if (!empty($settings->filename_no_format)) {
      @imagepng($im, $settings->filename_no_format .".". $settings->format);
    }
    else {
      @imagepng($im);
    }
  }

  if ($settings->format=="gif") {
    if (!empty($settings->filename_no_format)) {
      @imagegif($im, $settings->filename_no_format .".". $settings->format);
    }
    else {
      @imagegif($im);
    }
  }

  if ($settings->format == "jpg" || $settings->format == "jpeg") {
    if (!empty($settings->filename_no_format)) {
      @imagejpeg($im, $settings->filename_no_format .".". $settings->format);
    }
    else {
      @imagejpeg($im);
    }
  }

  @imagedestroy($im);
}

function barcode_upce_encode($barnumber, $settings, $encbit, $checkdigit) {
  $left_odd = array("0001101", "0011001", "0010011", "0111101", "0100011", "0110001", "0101111", "0111011", "0110111", "0001011");
  $left_even=array("0100111", "0110011", "0011011", "0100001", "0011101", "0111001", "0000101", "0010001", "0001001", "0010111");

  $enc_table0=array("EEEOOO", "EEOEOO", "EEOOEO", "EEOOOE", "EOEEOO", "EOOEEO", "EOOOEE", "EOEOEO", "EOEOOE", "EOOEOE");
  $enc_table1=array("OOOEEE", "OOEOEE", "OOEEOE", "OOEEEO", "OEOOEE", "OEEOOE", "OEEEOO", "OEOEOE", "OEOEEO", "OEEOEO");

  $guards=array("bab", "ababa", "b");

  if ($encbit == 0) {
    $enc_table = $enc_table0;
  }
  elseif ($encbit == 1) {
    $enc_table = $enc_table1;
  }
  else {
    $settings->error = "Not an UPC-E barcode number";
    return FALSE;
  }

  $mfc_str = "";
  $prod_str = "";
  $checkdigit;
  $enc_table[$checkdigit];

  for ($i = 0; $i < strlen($barnumber); $i++) {
    $num = (int)$barnumber{$i};
    $even = (substr($enc_table[$checkdigit], $i, 1) == 'E');
    if (!$even) {
      $mfc_str .= $left_odd[$num];
    }
    else {
      $mfc_str .= $left_even[$num];
    }
  }

  return $guards[0] . $mfc_str . $guards[1] . $guards[2];
}

// @todo handle error
function barcode_convert_upca_to_upce($upca) {
  $upce = "";

  // If the source message string is less than 12 characters long, we make it 
  // 12 characters
  if (strlen($upca) < 12) {
   $barnumber = str_pad($barnumber, 12, "0", STR_PAD_LEFT);
  }

  if (substr($upca, 0, 1) != '0' && substr($upca, 0, 1) != '1') {
    $settings->error = 'Invalid Number System (only 0 & 1 are valid)';
    return FALSE;
  }
  else {
    if (substr($upca, 3, 3) == '000' || substr($upca, 3, 3) == '100' || substr($upca, 3, 3) == '200') {
      $upce = substr($upca, 1, 2) . substr($upca, 8, 3) . substr($upca, 3, 1);
    }
    elseif (substr($upca, 4, 2) == '00') {
      $upce = substr($upca, 1, 2) . substr($upca, 9, 2) .'3';
    }
    elseif (substr($upca, 5, 1) == '0') {
      $upce = substr($upca, 1, 4) . substr($upca, 10, 1) .'4';
    }
    elseif (substr($upca, 10, 1) >= '5') {
      $upce = substr($upca, 1, 5) . substr($upca, 10, 1);
    }
    else {
      $settings->error = 'Invalid product code (00005 to 00009 are valid)';
      return FALSE;
    }
  }

  return $upce;
}

