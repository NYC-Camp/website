<?php

/**
 * @file
 * Barcode plugin
 * QR Code: get the QR code from Google Graphic API
 */
function barcode_qrcode_barcode($barnumber, $settings) {
  if (empty($settings->filename_no_format)) {
    header("Content-type: image/". $settings->format);
  }

  $h = $settings->height;
  $name = md5($barnumber);
  $content = urlencode($barnumber);
  $url = 'http://chart.apis.google.com/chart?chs=' . $h . 'x' . $h . '&cht=qr&chl=' . $content;
  $img = $settings->default_path .'/'. $name . $settings->encode .'.'. $settings->format; 
  
  file_put_contents($img, file_get_contents($url));
}

function barcode_qrcode_max_length($encoding) {
  return 8192;
}
