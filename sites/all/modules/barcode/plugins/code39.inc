<?php

/**
 * @file
 * Barcode plugin
 * Code 39 (aka USD-3, 3 of 9): U.S. Government and military use, required for
 * DoD applications
 */

function barcode_code39_barcode($barnumber, $settings) {
  $bars = barcode_code39_encode($barnumber, $settings, FALSE);

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

  for ($i = 0; $i < strlen($bars); $i++) {
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

/* A Code 39 barcode has the following structure:
 * A start character - the asterisk (*) character. Any number of characters
 * encoded from the table below. An optional checksum digit calculated as
 * described above and encoded from the table below. A stop character, which
 * is a second asterisk character.
 */
function barcode_code39_encode($barnumber, $checkdigit = FALSE) {
  $enc_table = array(
          "0" => "NNNWWNWNN",
          "1" => "WNNWNNNNW",
          "2" => "NNWWNNNNW",
          "3" => "WNWWNNNNN",
          "4" => "NNNWWNNNW",
          "5" => "WNNWWNNNN",
          "6" => "NNWWWNNNN",
          "7" => "NNNWNNWNW",
          "8" => "WNNWNNWNN",
          "9" => "NNWWNNWNN",
          "A" => "WNNNNWNNW",
          "B" => "NNWNNWNNW",
          "C" => "WNWNNWNNN",
          "D" => "NNNNWWNNW",
          "E" => "WNNNWWNNN",
          "F" => "NNWNWWNNN",
          "G" => "NNNNNWWNW",
          "H" => "WNNNNWWNN",
          "I" => "NNWNNWWNN",
          "J" => "NNNNWWWNN",
          "K" => "WNNNNNNWW",
          "L" => "NNWNNNNWW",
          "M" => "WNWNNNNWN",
          "N" => "NNNNWNNWW",
          "O" => "WNNNWNNWN",
          "P" => "NNWNWNNWN",
          "Q" => "NNNNNNWWW",
          "R" => "WNNNNNWWN",
          "S" => "NNWNNNWWN",
          "T" => "NNNNWNWWN",
          "U" => "WWNNNNNNW",
          "V" => "NWWNNNNNW",
          "W" => "WWWNNNNNN",
          "X" => "NWNNWNNNW",
          "Y" => "WWNNWNNNN",
          "Z" => "NWWNWNNNN",
          "-" => "NWNNNNWNW",
          "." => "WWNNNNWNN",
          " " => "NWWNNNWNN",
          "$" => "NWNWNWNNN",
          "/" => "NWNWNNNWN",
          "+" => "NWNNNWNWN",
          "%" => "NNNWNWNWN",
          "*" => "NWNNWNWNN",
  );

  $mfc_str = "";
  $widebar = str_pad("", $settings->n2w, "1", STR_PAD_LEFT);
  $widespc = str_pad("", $settings->n2w, "0", STR_PAD_LEFT);

  if ($checkdigit == TRUE) {
    $arr_key = array_keys($enc_table);
    for ($i = 0; $i < strlen($barnumber); $i++) {
      $num = $barnumber[$i];
      if (preg_match("/[A-Z]+/", $num)) {
        $num = ord($num)-55;
      }
      elseif ($num == '-') {
        $num = 36;
      }
      elseif ($num == '.') {
        $num = 37;
      }
      elseif ($num == ' ') {
        $num=38;
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

      $sum += $num;
    }
    $barnumber .= trim($arr_key[(int)($sum % 43)]);
  }

  $barnumber = "*". $barnumber ."*";

  for ($i = 0; $i < strlen($barnumber); $i++) {
    $tmp = $enc_table[$barnumber[$i]];

    $bar = TRUE;

    for ($j = 0; $j < strlen($tmp); $j++) {
      if ($tmp[$j] == 'N' && $bar) {
        $mfc_str .= '1';
      }
      elseif ($tmp[$j] == 'N' && !$bar) {
        $mfc_str .= '0';
      }
      elseif ($tmp[$j] == 'W' && $bar) {
        $mfc_str .= $widebar;
      }
      elseif ($tmp[$j] == 'W' && !$bar) {
        $mfc_str .= $widespc;
      }

      $bar = !$bar;
    }

    $mfc_str .= '0';
  }

  return $mfc_str;
}


