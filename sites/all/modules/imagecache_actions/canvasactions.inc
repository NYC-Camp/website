<?php
// $ID: $
/**
 * Helper functions for the text2canvas action for imagecache
 * 
 */

/**
 * Implementation of imagecache_hook_form()
 *
 * Settings for preparing a canvas.
 *
 * @param $action array of settings for this action
 * @return a form definition
 */
function canvasactions_definecanvas_form($action) {
  $form = array(
    'RGB' => imagecache_rgb_form($action['RGB']),
    'help' => array(
      '#type' => 'markup',
      '#value' => '<p>'. t('Enter no color value for transparent. This will have the effect of adding clear margins around the image.') .'</p>',
    ),
    'under' => array(
      '#type' => 'checkbox',
      '#title' => t('Resize canvas under image (possibly cropping)'),
      '#default_value' => $action['under'],
      '#description' => t('If not set, this will create a solid flat layer, probably totally obscuring the source image'),
    ),
  );
  $form['info'] = array('#value' => t('Enter values in ONLY ONE of the below options. Either exact or relative. Most values are optional - you can adjust only one dimension as needed. If no useful values are set, the current base image size will be used.'));
  $form['exact'] = array(
      '#type' => 'fieldset',
      '#collapsible' => true,
      '#title' => 'Exact size',
      'help' => array(
        '#type' => 'markup',
        '#value' => '<p>'. t('Set the canvas to a precise size, possibly cropping the image. Use to start with a known size.'). '</p>',
      ),
      
      'width' => array(
        '#type' => 'textfield',
        '#title' => t('Width'),
        '#default_value' => $action['exact']['width'],
        '#description' => t('Enter a value in pixels or percent'),
        '#size' => 5,
      ),
      'height' => array(
        '#type' => 'textfield',
        '#title' => t('Height'),
        '#default_value' => $action['exact']['height'],
        '#description' => t('Enter a value in pixels or percent'),
        '#size' => 5,
      ),
    );
  $form['exact'] = array_merge($form['exact'], canvasactions_pos_form($action['exact']));
  if(! $action['exact']['width'] && !$action['exact']['height']) {
    $form['exact']['#collapsed'] = true;
  }

  $form['relative'] = array(
      '#type' => 'fieldset',
      '#collapsible' => true,
      '#title' => t('Relative size'),
      'help' => array(
        '#type' => 'markup',
        '#value' => '<p>'. t('Set the canvas to a relative size, based on the current image dimensions. Use to add simple borders or expand by a fixed amount. Negative values may crop the image.') .'</p>',
      ),
      'leftdiff' => array(
        '#type' => 'textfield',
        '#title' => t('left difference'),
        '#default_value' => $action['relative']['leftdiff'],
        '#size' => 6,
        '#description' => t('Enter an offset in pixels.'),
      ),
      'rightdiff' => array(
        '#type' => 'textfield',
        '#title' => t('right difference'),
        '#default_value' => $action['relative']['rightdiff'],
        '#size' => 6,
        '#description' => t('Enter an offset in pixels.'),
      ),
      'topdiff' => array(
        '#type' => 'textfield',
        '#title' => t('top difference'),
        '#default_value' => $action['relative']['topdiff'] ,
        '#size' => 6,
        '#description' => t('Enter an offset in pixels.'),
      ),
      'bottomdiff' => array(
        '#type' => 'textfield',
        '#title' => t('bottom difference'),
        '#default_value' => $action['relative']['bottomdiff'],
        '#size' => 6,
        '#description' => t('Enter an offset in pixels.'),
      ),
    );
  if(! $action['relative']['leftdiff'] && !$action['relative']['rightdiff'] && !$action['relative']['topdiff'] && !$action['relative']['bottomdiff']) {
    $form['relative']['#collapsed'] = true;
  }

  $form['#submit'][] = 'canvasactions_definecanvas_form_submit';
  return $form;
}

/**
 * Implementation of theme_hook() for imagecache_ui.module
 */
function theme_canvasactions_definecanvas($element) {
  $action = $element['#value'];
  if ($action['exact']['width'] || $action['exact']['width']) {
    $output = $action['exact']['width'] .'x'. $action['exact']['height'];
  }
  else {
    $output = ' left:'. $action['relative']['leftdiff'];
    $output .= ' right:'. $action['relative']['rightdiff'];
    $output .= ' top:'. $action['relative']['topdiff'];
    $output .= ' bottom:'. $action['relative']['bottomdiff'];
    
  }
  $output .= theme_canvasactions_rgb($action['RGB']);
  return $output ;
}

/**
 * Implementation of hook_image()
 *
 * Creates a solid background canvas
 *
 * Process the imagecache action on the passed image
 *
 * @param $image
 * array defining an image file, including  :
 *
 *   $image- >source as the filename,
 *
 *   $image->info array
 *
 *   $image->res handle on the image object
 */
function canvasactions_definecanvas_image(& $image, $action = array()) {
 
  // May be given either exact or relative dimensions.
  if ($action['exact']['width'] || $action['exact']['width']) {
  // Allows only one dimension to be used if the other is unset.
    if (! $action['exact']['width']) $action['exact']['width'] = $image->info['width'];
    if (! $action['exact']['height']) $action['exact']['height'] = $image->info['height'];

    $targetsize['width'] = _imagecache_percent_filter($action['exact']['width'], $image->info['width']);
    $targetsize['height'] = _imagecache_percent_filter($action['exact']['height'], $image->info['height']);

    $targetsize['left'] = _imagecache_keyword_filter($action['exact']['xpos'], $targetsize['width'], $image->info['width']);
    $targetsize['top'] = _imagecache_keyword_filter($action['exact']['ypos'], $targetsize['height'], $image->info['height']);

  }
  else {
    // calculate relative size
    $targetsize['width'] = $image->info['width'] + $action['relative']['leftdiff'] +  $action['relative']['rightdiff'];
    $targetsize['height'] = $image->info['height'] + $action['relative']['topdiff'] +  $action['relative']['bottomdiff'];
    $targetsize['left'] = $action['relative']['leftdiff'];
    $targetsize['top'] = $action['relative']['topdiff'];
  }
  
  $newcanvas = imagecreatetruecolor($targetsize['width'], $targetsize['height']);
  $RGB = $action['RGB'];

  // convert from hex (as it is stored in the UI)
  if($RGB['HEX'] && $deduced = imagecache_actions_hex2rgba($RGB['HEX'])) {
    $RGB = array_merge($RGB, $deduced);
  }

  if ($RGB['red'] || $RGB['green'] || $RGB['blue']) { // one may be zero...
    $background = imagecolorallocate($newcanvas, $RGB['red'], $RGB['green'], $RGB['blue']);
  }
  else {
    // No color, attempt transparency, assume white
    $background = imagecolorallocatealpha($newcanvas, 255, 255, 255, 127);
    imagesavealpha($newcanvas, TRUE);
    imagealphablending($newcanvas, false);
    imagesavealpha($image->res, TRUE);
  }
  imagefilledrectangle($newcanvas, 0, 0, $targetsize['width'], $targetsize['height'], $background);
  
  if ($action['under']) {
    require_once('watermark.inc');
    $watermark = new watermark();
    $image->res = $watermark->create_watermark($newcanvas, $image->res, $targetsize['left'], $targetsize['top'], 100);
    imagesavealpha($image->res, TRUE);
  } 
  else {
    $image->res = $newcanvas ;
  }
  
  $image->info['width'] = $targetsize['width'];
  $image->info['height'] = $targetsize['height'];
  return TRUE;
}

////////////////////////////////////////////////

/**
 * Place a given image under the current canvas
 *
 * Implementation of imagecache_hook_form()
 *
 * @param $action array of settings for this action
 * @return a form definition
 */
function canvasactions_canvas2file_form($action) {
  $form = array(
    'xpos' => array(
      '#type' => 'textfield',
      '#title' => t('X offset'),
      '#default_value' => $action['xpos'],
      '#size' => 6,
      '#description' => t('Enter an offset in pixels or use a keyword: <em>left</em>, <em>center</em>, or <em>right</em>.'),
    ),
    'ypos' => array(
      '#type' => 'textfield',
      '#title' => t('Y offset'),
      '#default_value' => $action['ypos'],
      '#size' => 6,
      '#description' => t('Enter an offset in pixels or use a keyword: <em>top</em>, <em>center</em>, or <em>bottom</em>.'),
    ),
    'alpha' => array(
      '#type' => 'textfield',
      '#title' => t('opacity'),
      '#default_value' => isset($action['alpha']) ? $action['alpha'] : 100,
      '#size' => 6,
      '#description' => t('Opacity: 0-100.'),
    ),
    'path' => array(
      '#type' => 'textfield',
      '#title' => t('file name'),
      '#default_value' => $action['path'],
      '#description' => t('File may be in the "files/" folder, or relative to the Drupal siteroot.'),
    ),
  );
  return $form;
}

/**
 * Implementation of theme_hook() for imagecache_ui.module
 */
function theme_canvasactions_canvas2file($element) {
  $data = $element['#value'];
  return 'xpos:'. $data['xpos'] .', ypos:'. $data['ypos'] .' alpha:'. $data['alpha'] .'%' ;
}

/**
 * Place the source image on the current background
 *
 * Implementation of hook_image()
 *
 *
 * @param $image
 * @param $action
 */
function canvasactions_canvas2file_image(&$image, $action = array()) {
  // search for full (siteroot) paths, then file dir paths, then relative to the current theme
  if (file_exists($action['path'])) {
    $underlay = imageapi_image_open($action['path']);
  }
  else if (file_exists(file_create_path($action['path']))) {
    $underlay = imageapi_image_open(file_create_path($action['path']));
  }
  // This func modifies the underlay image by ref, placing the current canvas on it
  if (imageapi_image_overlay($underlay, $image, $action['xpos'], $action['ypos'], $action['alpha'])) {
    $image->res = $underlay->res;
    //$image = $underlay;
    return TRUE;
  }
}

////////////////////////////////////////////////


/**
 * Place a given image on top of the current canvas
 *
 * Implementation of imagecache_hook_form()
 *
 * @param $action array of settings for this action
 * @return a form definition
 */
function canvasactions_file2canvas_form($action) {
  $form = array(
    'help' => array(
      '#type' => 'markup',
      '#value' => t('Note that this action may require a lot of processing as transparency blends require that every pixel be re-calculated for each image. This can be a server-intensive process and generate a bit of load time.'),
    ),
    'xpos' => array(
      '#type' => 'textfield',
      '#title' => t('X offset'),
      '#default_value' => $action['xpos'],
      '#size' => 6,
      '#description' => t('Enter an offset in pixels or use a keyword: <em>left</em>, <em>center</em>, or <em>right</em>.'),
    ),
    'ypos' => array(
      '#type' => 'textfield',
      '#title' => t('Y offset'),
      '#default_value' => $action['ypos'],
      '#size' => 6,
      '#description' => t('Enter an offset in pixels or use a keyword: <em>top</em>, <em>center</em>, or <em>bottom</em>.'),
    ),
    'alpha' => array(
      '#type' => 'textfield',
      '#title' => t('opacity'),
      '#default_value' => $action['alpha'],
      '#size' => 6,
      '#description' => t('Opacity: 0-100.'),
    ),
    'path' => array(
      '#type' => 'textfield',
      '#title' => t('file name'),
      '#default_value' => $action['path'],
      '#description' => t('File may be in the "files/" folder, or relative to the Drupal siteroot.'),
    ),
  );
  return $form;
}

/**
 * Implementation of theme_hook() for imagecache_ui.module
 */
function theme_canvasactions_file2canvas($element) {
  $action = $element['#value'];
  return '<strong>'. basename($action['path']) . '</strong> x:'. $action['xpos'] .', y:'. $action['ypos'] .' alpha:'. $action['alpha'] .'%' ;
}

/**
 * Place the source image on the current background
 *
 * Implementation of hook_image()
 *
 *
 * @param $image
 * @param $action
 */
function canvasactions_file2canvas_image(&$image, $action = array()) {
  // search for full (siteroot) paths, then file dir paths, then relative to the current theme
  if (file_exists($action['path'])) {
    $overlay = imageapi_image_open($action['path']);
  }
  else if (file_exists(file_create_path($action['path']))) {
    $overlay = imageapi_image_open(file_create_path($action['path']));
  }
  return imageapi_image_overlay($image, $overlay, $action['xpos'], $action['ypos'], $action['alpha']);
}

///////////////////////////////////////////////////////////////////
/**
 * Place the source image on top of the current canvas
 *
 * Implementation of imagecache_hook_form()
 *
 *
 *
 * @param $action array of settings for this action
 * @return a form definition
 */
function canvasactions_source2canvas_form($action) {
  $form = array(
    'xpos' => array(
      '#type' => 'textfield',
      '#title' => t('X offset'),
      '#default_value' => $action['xpos'],
      '#size' => 6,
      '#description' => t('Enter an offset in pixels or use a keyword: <em>left</em>, <em>center</em>, or <em>right</em>.'),
    ),
    'ypos' => array(
      '#type' => 'textfield',
      '#title' => t('Y offset'),
      '#default_value' => $action['ypos'],
      '#size' => 6,
      '#description' => t('Enter an offset in pixels or use a keyword: <em>top</em>, <em>center</em>, or <em>bottom</em>.'),
    ),
    'alpha' => array(
      '#type' => 'textfield',
      '#title' => t('opacity'),
      '#default_value' => $action['alpha'] ? $action['alpha'] : 100,
      '#size' => 6,
      '#description' => t('Opacity: 0-100.'),
    ),
  );
  return $form;
}

/**
 * Implementation of theme_hook() for imagecache_ui.module
 */
function theme_canvasactions_source2canvas($element) {
  $data = $element['#value'];
  return 'xpos:'. $data['xpos'] .', ypos:'. $data['ypos'] .' alpha:'. $data['alpha'] .'%' ;
}

/**
 * Place the source image on the current background
 *
 * Implementation of hook_image()
 *
 *
 * @param $image
 * @param $action
 */
function canvasactions_source2canvas_image(&$image, $action = array()) {
  $overlay = imageapi_image_open($image->source); // this probably means opening the image twice. c'est la vie
  return imageapi_image_overlay($image, $overlay, $action['xpos'], $action['ypos'], $action['alpha']);
}

////////////////////////////////////////////////
