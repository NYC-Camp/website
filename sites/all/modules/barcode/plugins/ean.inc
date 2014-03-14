<?php

/**
 * @file
 * Barcode plugin
 * EAN-13: Used with consumer products internationally, 13 characters
 * UPC-A: Used with consumer products in U.S., 12 characters
 * ISBN: Used to mark books, 13 characters
 */

function barcode_ean_max_length($encoding) {
  if ($encoding == 'UPC-A') {
    return 12;
  }
  elseif ($encoding == 'EAN-13' || $encoding == 'ISBN') {
    return 13;
  } 
}

function barcode_ean_check_digit($barnumber) {
  $csum_total = 0; // The checksum working variable starts at zero

  // If the source message string is less than 12 characters long, we make 
  // it 12 characters
  if (strlen($barnumber) <= 12) {
    $barnumber = str_pad($barnumber, 12, "0", STR_PAD_LEFT);
  }

  // Calculate the checksum value for the message
  for ($i = 0; $i < strlen($barnumber); $i++) {
    if ($i % 2 == 0 ) {
      $csum_total = $csum_total + intval($barnumber{$i});
    }
    else {
      $csum_total = $csum_total + (3 * intval($barnumber{$i}));
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

function barcode_ean_barcode($barnumber, $settings) {
  $barnumber = barcode_ean_check_digit($barnumber);

  $bars = barcode_ean_encode($barnumber, $settings);

  if (empty($settings->filename_no_format)) {
    header("Content-type: image/". $settings->format);
  }

  $scale = $settings->scale;
  if ($scale < 1) {
    $scale = 2;
  }

  $total_y = (double)$scale * $settings->height;
  if (!isset($space)) {
    $space = array(
      'top' => 2 * $scale,
      'bottom' => 2 * $scale,
      'left' => 2 * $scale,
      'right' => 2 * $scale,
    );
  }

  /* count total width */
  $xpos = 0;

  $xpos = $scale * (114);

  /* allocate the image */
  $total_x = $xpos + $space['left'] + $space['right'];
  $xpos = $space['left'] + ($scale * 6);

  $height = floor($total_y - ($scale * 10));
  $height2 = floor($total_y - $space['bottom']);

  $im = @imagecreatetruecolor($total_x, $total_y);
  $bg_color = @imagecolorallocate($im, $settings->bgcolor[0], $settings->bgcolor[1], $settings->bgcolor[2]);
  @imagefilledrectangle($im, 0, 0, $total_x, $total_y, $bg_color);
  $bar_color = @imagecolorallocate($im, $settings->color[0], $settings->color[1], $settings->color[2]);

  for ($i = 0; $i < strlen($bars); $i++) {
    $h = $height;
    $val = strtoupper($bars[$i]);
    if (preg_match("/[a-z]/i", $val)) {
      $val = ord($val) - 65;
      $h = $height2;
    }

    if ($settings->encode == "UPC-A" && ($i < 10 || $i>strlen($bars) - 13)) {
      $h = $height2;
    }

    if ($val == 1) {
      @imagefilledrectangle($im, $xpos, $space['top'], $xpos + $scale - 1, $h, $bar_color);
    }

    $xpos += $scale;
  }


  if ($settings->encode == "UPC-A") {
    $str = substr($barnumber, 1, 1);
  }
  else {
    $str = substr($barnumber, 0, 1);
  }

  @imagettftext($im, $scale * 6, 0, $space['left'], $height, $bar_color, $settings->font, $str);

  if ($settings->encode == "UPC-A") {
    $str = substr($barnumber, 2, 5);
  }
  else {
    $str = substr($barnumber, 1, 6);
  }

  $x = $space['left'] + $scale * strlen($barnumber) + $scale * 6;
  @imagettftext($im, $scale * 6, 0, $x, $height2, $bar_color, $settings->font, $str);

  if ($settings->encode == "UPC-A") {
    $str = substr($barnumber, 7, 5);
  }
  else {
    $str = substr($barnumber, 7, 6);
  }

  $x = $space['left'] + $scale * strlen($bars) / 1.65 + $scale * 6;
  @imagettftext($im, $scale * 6, 0, $x, $height2, $bar_color, $settings->font, $str);

  if ($settings->encode == "UPC-A") {
    $str = substr($barnumber, 12, 1);
    $x = $total_x - $space['left'] - $scale * 6;
    @imagettftext($im, $scale * 6, 0, $x, $height, $bar_color, $settings->font, $str);
  }

  if ($settings->format == "png") {
    if (!empty($settings->filename_no_format)) {
      @imagepng($im, $settings->filename_no_format .".". $settings->format);
    }
    else {
      @imagepng($im);
    }
  }

  if ($settings->format == "gif") {
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

/* An EAN-13 barcode has the following physical structure:
 * 
 * Left-hand guard bars, or start sentinel, encoded as 101.
 * The second character of the number system code, encoded as described below.
 * The five characters of the manufacturer code, encoded as described below.
 * Center guard pattern, encoded as 01010.
 * The five characters of the product code, encoded as right-hand characters,
 * described below.
 * Check digit, encoded as a right-hand character, described below.
 * Right-hand guard bars, or end sentinel, encoded as 101.
 * FIRST NUMBER
 * 
 * SYSTEM DIGIT PARITY TO ENCODE WITH
 *   SECOND NUMBER
 *   SYSTEM DIGIT MANUFACTURER CODE CHARACTERS
 *         1 2 3  4  5
 * 0 (UPC-A) Odd Odd Odd Odd Odd Odd
 * 1     Odd Odd Even Odd Even Even
 * 2     Odd Odd Even Even Odd Even
 * 3     Odd Odd Even Even Even Odd
 * 4     Odd Even Odd Odd Even Even
 * 5     Odd Even Even Odd Odd Even
 * 6     Odd Even Even Even Odd Odd
 * 7     Odd Even Odd Even Odd Even
 * 8     Odd Even Odd Even Even Odd
 * 9     Odd Even Even Odd Even Odd
 */
function barcode_ean_encode($barnumber) {
  $left_odd = array("0001101", "0011001", "0010011", "0111101", "0100011", "0110001", "0101111", "0111011", "0110111", "0001011");
  $left_even = array("0100111", "0110011", "0011011", "0100001", "0011101", "0111001", "0000101", "0010001", "0001001", "0010111");
  $right_all = array("1110010", "1100110", "1101100", "1000010", "1011100", "1001110", "1010000", "1000100", "1001000", "1110100");

  $enc_table = array("000000", "001011", "001101", "001110", "010011", "011001", "011100", "010101", "010110", "011010");

  $guards = array("bab", "ababa", "bab");

  $mfc_str = "";
  $prod_str = "";

  $encbit = $barnumber[0];

  for ($i = 1; $i < strlen($barnumber); $i++) {
    $num = (int)$barnumber{$i};
    if ($i < 7) {
      $even = (substr($enc_table[$encbit], $i - 1, 1) == 1);
      if (!$even) {
        $mfc_str .= $left_odd[$num];
      }
      else {
        $mfc_str .= $left_even[$num];
      }
    }
    elseif ($i >= 7) {
      $prod_str .= $right_all[$num];
    }
  }

  return $guards[0] . $mfc_str . $guards[1] . $prod_str . $guards[2];
}
