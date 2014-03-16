<?php

/**
 * @file
 * Barcode plugin
 * Postnet: Printed by U.S. Post Office on envelopes
 */

function barcode_postnet_barcode($barnumber, $settings) {
  $bars = barcode_postnet_encode($barnumber, $settings);

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
      'right' => 2 * $scale
    );
  }

  /* count total width */
  $xpos = 0;

  $xpos = $scale * strlen($bars) * 2;

  /* allocate the image */
  $total_x = $xpos + $space['left'] + $space['right'];
  $xpos = $space['left'];

  $height = floor($total_y - ($scale * 10));
  $height2 = floor($total_y - $space['bottom']);

  $im = @imagecreatetruecolor($total_x, $total_y);
  $bg_color = @imagecolorallocate($im, $settings->bgcolor[0], $settings->bgcolor[1], $settings->bgcolor[2]);
  @imagefilledrectangle($im, 0, 0, $total_x, $total_y, $bg_color);
  $bar_color = @imagecolorallocate($im, $settings->color[0], $settings->color[1], $settings->color[2]);

  for ($i = 0; $i < strlen($bars); $i++) {
    $val = strtoupper($bars[$i]);
    $h = $total_y - $space['bottom'];

    if ($val == 1) {
      @imagefilledrectangle($im, $xpos, $space['top'], $xpos + $scale - 1, $height2, $bar_color);
    }
    else {
      @imagefilledrectangle($im, $xpos, floor($height2 / 1.5), $xpos + $scale - 1, $height2, $bar_color);
    }

    $xpos += 2 * $scale;
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

/*
 * A PostNet barcode has the following structure:
 *
 * Frame bar, encoded as a single 1.
 * 5, 9, or 11 data characters properly encoded (see encoding table below).
 * Check digit, encoded using encoding table below.
 * Final frame bar, encoded as a single 1.
 *
 * 0    11000
 * 1    00011
 * 2    00101
 * 3    00110
 * 4    01001
 * 5    01010
 * 6    01100
 * 7    10001
 * 8    10010
 * 9    10100
 */
function barcode_postnet_encode($barnumber, $settings) {
  $enc_table = array("11000", "00011", "00101", "00110", "01001", "01010", "01100", "10001", "10010", "10100");

  $sum = 0;
  $encstr = "";
  for ($i = 0; $i < strlen($barnumber); $i++) {
    $sum += (int)$barnumber[$i];
    $encstr .= $enc_table[(int)$barnumber[$i]];
  }

  if ($sum % 10 != 0) {
    $check = (int)(10 - ($sum % 10));
  }

  $encstr .= $enc_table[$check];
  $encstr = "1" . $encstr . "1";
  return $encstr;
}
