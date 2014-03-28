<?php

/**
 * @file
 * Barcode plugin
 * Code 93 (aka USS-93): Compressed form of Code 39
 */

function barcode_code93_barcode($barnumber, $settings) {
  $bars = barcode_code93_encode($barnumber);
  if (empty($settings->filename_no_format)) {
    header("Content-type: image/". $settings->format);
  }

  $scale = $settings->scale;
  if ($scale < 1) {
    $scale = 2;
  }

  $total_y = (double)$scale * $settings->height + 10 * $scale;

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

  $xpos = $scale * strlen($bars) + 2 * $scale * 10;

  /* allocate the image */
  $total_x = $xpos + $space['left'] + $space['right'];
  $xpos = $space['left'] + $scale * 10;

  $height = floor($total_y - ($scale * 20));
  $height2 = floor($total_y - $space['bottom']);

  $im = @imagecreatetruecolor($total_x, $total_y);
  $bg_color = @imagecolorallocate($im, $settings->bgcolor[0], $settings->bgcolor[1], $settings->bgcolor[2]);
  @imagefilledrectangle($im, 0, 0, $total_x, $total_y, $bg_color);
  $bar_color = @imagecolorallocate($im, $settings->color[0], $settings->color[1], $settings->color[2]);

  for ($i=0; $i < strlen($bars); $i++) {
    $h = $height;
    $val = $bars[$i];

    if ($val == 1) {
      @imagefilledrectangle($im, $xpos, $space['top'], $xpos + $scale - 1, $h, $bar_color);
    }

    $xpos += $scale;
  }

  $font_arr = @imagettfbbox ($scale*10, 0, $settings->font, $barnumber);
  $x = floor($total_x - (int)$font_arr[0] - (int)$font_arr[2] + $scale * 10) / 2;
  @imagettftext($im, $scale * 10, 0, $x, $height2, $bar_color, $settings->font, $barnumber);

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

/* A Code 93 barcode has the following structure:
 * A start character , represented below by the asterisk (*) character. Any 
 * number of characters encoded from the table below. The "C" and "K" checksum
 * digits calculated as described above and encoded using the table below. A
 * stop character, which is a second asterisk character.
 */
function barcode_code93_encode($barnumber) {
  $enc_table = array(
    "0" => "100010100",
    "1" => "101001000",
    "2" => "101000100",
    "3" => "101000010",
    "4" => "100101000",
    "5" => "100100100",
    "6" => "100100010",
    "7" => "101010000",
    "8" => "100010010",
    "9" => "100001010",
    "A" => "110101000",
    "B" => "110100100",
    "C" => "110100010",
    "D" => "110010100",
    "E" => "110010010",
    "F" => "110001010",
    "G" => "101101000",
    "H" => "101100100",
    "I" => "101100010",
    "J" => "100110100",
    "K" => "100011010",
    "L" => "101011000",
    "M" => "101001100",
    "N" => "101000110",
    "O" => "100101100",
    "P" => "100010110",
    "Q" => "110110100",
    "R" => "110110010",
    "S" => "110101100",
    "T" => "110100110",
    "U" => "110010110",
    "V" => "110011010",
    "W" => "101101100",
    "X" => "101100110",
    "Y" => "100110110",
    "Z" => "100111010",
    "-" => "100101110",
    "." => "111010100",
    " " => "111010010",
    "$" => "111001010",
    "/" => "101101110",
    "+" => "101110110",
    "%" => "110101110",
    "$" => "100100110",
    "%" => "111011010",
    "/" => "111010110",
    "+" => "100110010",
    "*" => "101011110",
  );

  $mfc_str = "";
  $widebar = str_pad("", $settings->n2w, "1", STR_PAD_LEFT);
  $widespc = str_pad("", $settings->n2w, "0", STR_PAD_LEFT);

  $arr_key = array_keys($enc_table);
  /// calculating C And K

  for ($j = 0; $j < 2; $j++) {
    $sum = 0;
    for ($i = strlen($barnumber); $i > 0; $i--) {
      $num = $barnumber[strlen($barnumber) - $i];
      if (preg_match("/[A-Z]+/", $num))
        $num = ord($num) - 55;
      elseif ($num == '-') {
        $num = 36;
      }
      elseif ($num == '.') {
        $num = 37;
      }
      elseif ($num == ' ') {
        $num = 38;
      }
      elseif ($num == '$') {
        $num = 39;
      }
      elseif ($num == '/') {
        $num = 40;
      }
      elseif ($num == '+') {
        $num = 41;
      }
      elseif ($num == '%') {
        $num = 42;
      }
      elseif ($num == '*') {
        $num = 43;
      }

      $sum += $i * $num;
    }
    $barnumber .= trim($arr_key[(int)($sum % 47)]);
  }

  $barnumber = "*". $barnumber ."*";

  for ($i = 0; $i < strlen($barnumber); $i++) {
    $mfc_str .= $enc_table[$barnumber[$i]];
  }
  $mfc_str .= '1';

  return $mfc_str;
}
