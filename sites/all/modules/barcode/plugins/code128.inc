<?php

/**
 * @file
 * Barcode plugin
 * Code 128: Very dense code, used extensively worldwide
 */

function barcode_code128_barcode($barnumber, $settings) {
  $use_keys = "B";
  if (preg_match("/^[0-9". chr(128) . chr(129) . chr(130) ."]+$/", $barnumber)) {
    $use_keys='C';
    if (strlen($barnumber)%2 != 0) {
      $barnumber = '0'. $barnumber;
    }
  }

  for ($i = 0; $i < 32; $i++) {
    $chr = chr($i);
  }

  if (preg_match("/[". $chr ."]+/", $barnumber)) {
    $use_keys = 'A';
  }

  $bars = barcode_code128_encode($barnumber, $settings, $use_keys);

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
    $val = strtoupper($bars[$i]);

    if ($val == 1) {
      @imagefilledrectangle($im, $xpos, $space['top'], $xpos + $scale - 1, $h, $bar_color);
    }

    $xpos += $scale;
  }

  $font_arr = @imagettfbbox($scale * 10, 0, $settings->font, $barnumber);
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

function barcode_code128_encode($barnumber, $settings, $use_keys) {
  $enc_table=array("11011001100", "11001101100", "11001100110", "10010011000", "10010001100", "10001001100", "10011001000", "10011000100", "10001100100", "11001001000", "11001000100", "11000100100", "10110011100", "10011011100", "10011001110", "10111001100", "10011101100", "10011100110", "11001110010", "11001011100", "11001001110", "11011100100", "11001110100", "11101101110", "11101001100", "11100101100", "11100100110", "11101100100", "11100110100", "11100110010", "11011011000", "11011000110", "11000110110", "10100011000", "10001011000", "10001000110", "10110001000", "10001101000", "10001100010", "11010001000", "11000101000", "11000100010", "10110111000", "10110001110", "10001101110", "10111011000", "10111000110", "10001110110", "11101110110", "11010001110", "11000101110", "11011101000", "11011100010", "11011101110", "11101011000", "11101000110", "11100010110", "11101101000", "11101100010", "11100011010", "11101111010", "11001000010", "11110001010", "10100110000", "10100001100", "10010110000", "10010000110", "10000101100", "10000100110", "10110010000", "10110000100", "10011010000", "10011000010", "10000110100", "10000110010", "11000010010", "11001010000", "11110111010", "11000010100", "10001111010", "10100111100", "10010111100", "10010011110", "10111100100", "10011110100", "10011110010", "11110100100", "11110010100", "11110010010", "11011011110", "11011110110", "11110110110", "10101111000", "10100011110", "10001011110", "10111101000", "10111100010", "11110101000", "11110100010", "10111011110", "10111101110", "11101011110", "11110101110", "11010000100", "11010010000", "11010011100", "11000111010");

  $start = array(
    "A" => "11010000100",
    "B" => "11010010000",
    "C" => "11010011100",
  );
  $stop = "11000111010";

  $sum = 0;
  $mfc_str = "";
  if ($use_keys == 'C') {
    for ($i = 0; $i < strlen($barnumber); $i += 2) {
      $val = substr($barnumber, $i, 2);
      if (is_int($val)) {
        $sum += ($i + 1) * (int)($val);
      }
      elseif ($barnumber == chr(129)) {
        $sum += ($i+1) * 100;
      }
      elseif ($barnumber == chr(130)) {
        $sum += ($i + 1) * 101;
      }

      $mfc_str .= $enc_table[$val];
    }
  }
  else {
    for ($i = 0; $i < strlen($barnumber); $i++) {
      $num = ord($barnumber[$i]);
      if ($num >= 32 && $num <= 126) {
        $num = ord($barnumber[$i]) - 32;
      }
      elseif ($num == 128) {
        $num = 99;
      }
      elseif ($num == 129) {
        $num = 100;
      }
      elseif ($num == 130) {
        $num = 101;
      }
      elseif ($num < 32 && $use_keys == 'A') {
        $num = $num + 64;
      }

      $sum += ($i + 1) * $num;
      $mfc_str .= $enc_table[$num];
    }
  }

  if ($use_keys == 'A') {
    $check = ($sum + 103) % 103;
  }

  if ($use_keys == 'B') {
    $check = ($sum + 104) % 103;
  }

  if ($use_keys == 'C') {
    $check = ($sum + 105) % 103;
  }

  return $start[$use_keys] . $mfc_str . $enc_table[$check] . $stop ."11";
}
