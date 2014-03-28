<?php

/**
 * @file
 * Barcode plugin
 * EAN-8: Short version of EAN-13, 8 characters
 */

function barcode_ean8_max_length($encoding) {
  return 8;
}

function barcode_ean8_barcode($barnumber, $settings) {
  $barnumber = barcode_check_digit($barnumber, 7);
  $bars = barcode_ean8_encode($barnumber);

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
      'right' => 2 * $scale,
    );
  }

  /* count total width */
  $xpos = 0;

  $xpos = $scale * strlen($bars);

  /* allocate the image */
  $total_x = $xpos + $space['left'] + $space['right'];
  $xpos = $space['left'];

  $height = floor($total_y - ($scale * 10));
  $height2 = floor($total_y - $space['bottom']);

  $im =@imagecreatetruecolor($total_x, $total_y);
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

    if ($val == 1) {
      @imagefilledrectangle($im, $xpos, $space['top'], $xpos + $scale - 1, $h, $bar_color);
    }

    $xpos += $scale;
  }

  $str = substr($barnumber, 0, 4);
  $x = $space['left'] + $scale * strlen($barnumber);
  @imagettftext($im, $scale * 6, 0, $x, $height2, $bar_color, $settings->font, $str);

  $str = substr($barnumber, 4, 4);
  $x = $space['left'] + $scale * strlen($bars) / 1.65;
  @imagettftext($im, $scale * 6, 0, $x, $height2, $bar_color, $settings->font, $str);

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

  if ($settings->format == "jpg" || $settings->format == "jpeg" ) {
    if (!empty($settings->filename_no_format)) {
      @imagejpeg($im, $settings->filename_no_format .".". $settings->format);
    }
    else {
      @imagejpeg($im);
    }
  }

  @imagedestroy($im);
}

/* An EAN-8 barcode has the following physical structure:
 * 
 * Left-hand guard bars, or start sentinel, encoded as 101.
 * Two number system characters, encoded as left-hand odd-parity characters.
 * First two message characters, encoded as left-hand odd-parity characters.
 * Center guard bars, encoded as 01010.
 * Last three message characters, encoded as right-hand characters.
 * Check digit, encoded as right-hand character.
 * Right-hand guar bars, or end sentinel, encoded as 101.
 */
function barcode_ean8_encode($barnumber) {
  $left_odd = array("0001101", "0011001", "0010011", "0111101", "0100011", "0110001", "0101111", "0111011", "0110111", "0001011");
  $left_even = array("0100111", "0110011", "0011011", "0100001", "0011101", "0111001", "0000101", "0010001", "0001001", "0010111");
  $right_all = array("1110010", "1100110", "1101100", "1000010", "1011100", "1001110", "1010000", "1000100", "1001000", "1110100");

  $enc_table = array("000000", "001011", "001101", "001110", "010011", "011001", "011100", "010101", "010110", "011010");

  $guards=array("bab", "ababa", "bab");

  $mfc_str = "";
  $prod_str = "";

  for ($i = 0; $i < strlen($barnumber); $i++) {
    $num = (int)$barnumber{$i};
    if ($i < 4) {
      $mfc_str .= $left_odd[$num];
    }
    elseif ($i >= 4) {
      $prod_str .= $right_all[$num];
    }
  }

  return $guards[0] . $mfc_str . $guards[1] . $prod_str . $guards[2];
}
