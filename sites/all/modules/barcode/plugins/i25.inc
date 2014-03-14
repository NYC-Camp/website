<?php

/**
 * @file
 * Barcode plugin
 * Interleaved 2 of 5: Same as Standard 2 of 5
 * Interleaved
 */

function barcode_i25_barcode($barnumber, $settings) {
  $bars = barcode_i25_encode($barnumber, $settings);

  if (empty($settings->filename_no_format)) {
    header("Content-type: image/". $settings->format);
  }

  $scale = $settings->scale;
  if ($scale < 1) {
    $scale = 2;
  }

  $total_y = (double)$scale * $settings->height;

  $space = array(
    'top' => 2 * $scale,
    'bottom' => 2 * $scale,
    'left' => 2 * $scale,
    'right' => 2 * $scale
  );

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
      @imagefilledrectangle($im, $xpos, $space['top'], $xpos+$scale - 1, $h, $bar_color);
    }

    $xpos+=$scale;
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

  if ($settings->format=="gif") {
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

/* A Standard 2 of 5 barcode has the following physical structure:
 *
 * Start character, encoded as 11011010.
 * Data characters properly encoded (see encoding table below).
 * Stop character, encoded as 11010110.
 * 
 * ASCII BARCODE
 * 0    NNWWN
 * 1    WNNNW
 * 2    NWNNW
 * 3    WWNNN
 * 4    NNWNW
 * 5    WNWNN
 * 6    NWWNN
 * 7    NNNWW
 * 8    WNNWN
 * 9    NWNWN
 */
function barcode_i25_encode($barnumber, $settings) {
  $enc_table=array("NNWWN", "WNNNW", "NWNNW", "WWNNN", "NNWNW", "WNWNN", "NWWNN", "NNNWW", "WNNWN", "NWNWN");
  $guards=array("1010", "1101");

  $len=strlen($barnumber);
  if ($len % 2 != 0) {
    $barnumber = barcode_check_digit($barnumber, $len);
    if ($len == strlen($barnumber) && substr($barnumber, -1) != '0') {
      $barnumber .= '0';
    }
  }

  $mfc_str = "";

  $widebar = str_pad("", $settings->n2w, "1", STR_PAD_LEFT);
  $widespc = str_pad("", $settings->n2w, "0", STR_PAD_LEFT);

  for ($i = 0; $i < strlen($barnumber); $i += 2) {
    $tmp = $enc_table[(int)$barnumber[$i]];
    $tmp1 = $enc_table[(int)$barnumber[$i+1]];
    for ($j = 0; $j < strlen($tmp); $j++) {
      if ($tmp[$j]=='N') {
        $mfc_str .= '1';
      }
      else {
        $mfc_str .= $widebar;
      }

      if ($tmp1[$j]=='N') {
        $mfc_str .= '0';
      }
      else {
        $mfc_str .= $widespc;
      }
    }
  }

  return $guards[0] . $mfc_str . $guards[1];
}

