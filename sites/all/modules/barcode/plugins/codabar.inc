<?php

/**
 * @file
 * Barcode plugin
 * Codabar (aka Ames Code/USD-4/NW-7/2 of 7 Code): Used in libraries and blood 
 * banks
 */

function barcode_codabar_barcode($barnumber, $settings) {
  $bars = barcode_codabar_encode($barnumber, $settings);

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
  $xpos = 0;

  $xpos = $scale * strlen($bars);

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
    $h = $height;
    $val = strtoupper($bars[$i]);

    if ($val == 1) {
      @imagefilledrectangle($im, $xpos, $space['top'], $xpos+$scale-1, $h, $bar_color);
    }

    $xpos += $scale;
  }


  $x = ($total_x - strlen($bars)) / 2;
  @imagettftext($im, $scale * 6, 0, $x, $height2, $bar_color, $settings->font, $barnumber);

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

/* A Code 11 Barcode has the following structure:
 *
 * One of four possible start characters (A, B, C, or D), encoded from the
 * table below.
 *
 * A narrow, inter-character space.
 *
 * The data of the message, encoded from the table below, with a narrow 
 * inter-character space between each character.
 *
 * One of four possible stop characters (A, B, C, or D), encoded from the 
 * table below
 */
function barcode_codabar_encode($barnumber, $settings) {
  $enc_table=array("0000011", "0000110", "0001001", "1100000", "0010010", "1000010", "0100001", "0100100", "0110000", "1001000");
  $chr_table=array("-" => "0001100", "$" => "0011000", ":" => "1000101", "/" => "1010001", "." => "1010100", "+" => "0011111", "A" => "0011010", "B" => "0001011", "C" => "0101001", "D" => "0001110");

  $mfc_str = "";

  $widebar = str_pad("", $settings->n2w, "1", STR_PAD_LEFT);
  $widespc = str_pad("", $settings->n2w, "0", STR_PAD_LEFT);

  for ($i=0; $i < strlen($barnumber); $i++) {
    if (preg_match("/[0-9]+/", $barnumber[$i])) {
      $tmp = $enc_table[(int)$barnumber[$i]];
    }
    else {
      $tmp = $chr_table[strtoupper(trim($barnumber[$i]))];
    }

    $bar = TRUE;

    for ($j = 0; $j < strlen($tmp); $j++) {
      if ($tmp[$j] == '0' && $bar) {
        $mfc_str .= '1';
      }
      elseif ($tmp[$j] == '0' && !$bar) {
        $mfc_str .= '0';
      }
      elseif ($tmp[$j] == '1' && $bar) {
        $mfc_str .= $widebar;
      }
      elseif ($tmp[$j] == '1' && !$bar) {
        $mfc_str .= $widespc;
      }

      $bar = !$bar;
    }
    $mfc_str .= '0';
  }

  return $mfc_str;
}
