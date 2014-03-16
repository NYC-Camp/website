<?php
/**
 * @file
 */

/**
 * CTools Export UI required function for plugin definition
 */
function mobile_codes_mobile_codes_providers_ctools_export_ui() {
  return array(
    'schema' => 'mobile_codes_providers',
    'access' => 'administer mobile codes',
    'menu' => array(
      'menu prefix' => 'admin/config/content/mobile_codes',
      'menu item' => 'providers',
      'menu title' => 'Providers',
      'menu description' => 'Administer Mobile Codes providers.',
    ),
    'title singular' => t('provider'),
    'title singular proper' => t('Provider'),
    'title plural' => t('providers'),
    'title plural proper' => t('Providers'),
    'form' => array(
      'settings' => 'mobile_codes_providers_export_ui_form',
      'submit' => 'mobile_codes_providers_export_ui_form_submit',
    ),
  );
}

/**
 * Providers form.
 */
function mobile_codes_providers_export_ui_form(&$form, &$form_state) {
  $form['provider']['url'] = array(
    '#type' => 'container',
    '#attributes' => array(
      'class' => array('clearfix'),
    ),
  );

  $form['provider']['url']['url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL'),
    '#default_value' => isset($form_state['item']->url) ? $form_state['item']->url : '',
    '#maxlength' => 512,
    '#ajax' => array(
      'callback' => 'mobile_codes_providers_export_ui_form_js',
      'wrapper' => 'parameters-wrapper',
    ),
    '#required' => TRUE,
  );

  $form['provider']['parameters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Parameters'),
    '#theme' => 'mobile_codes_providers_export_ui_form_parameters',
    '#prefix' => '<div id="parameters-wrapper">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );

  $url = !empty($form_state['values']) ? $form_state['values']['url'] : $form_state['item']->url;
  $parameters = !empty($form_state['values']) ? $form_state['values']['parameters'] : $form_state['item']->parameters;

  preg_match_all('/\[(.*?)\]/', $url, $tokens, PREG_SET_ORDER);
  foreach ($tokens as $token) {
    $form['provider']['parameters'][$token[1]]['token'] = array(
      '#type' => 'value',
      '#value' => $token[1],
    );

    if ($parameters[$token[1]]['type'] != 'data') {
      $form['provider']['parameters'][$token[1]]['label'] = array(
        '#type' => 'textfield',
        '#title' => t('Label'),
        '#size' => 30,
        '#default_value' => isset($parameters[$token[1]]) ? $parameters[$token[1]]['label'] : '',
      );
    }

    $form['provider']['parameters'][$token[1]]['type'] = array(
      '#type' => 'select',
      '#options' => array(
        'data' => t('Data'),
        'select' => t('Selectbox'),
        'text' => t('Textfield'),
      ),
      '#default_value' => isset($parameters[$token[1]]) ? $parameters[$token[1]]['type'] : 'text',
      '#ajax' => array(
        'callback' => 'mobile_codes_providers_export_ui_form_js',
        'wrapper' => 'parameters-wrapper',
      ),
      '#prefix' => '<div class="clearfix">',
      '#suffix' => '</div>',
    );

    if (isset($parameters[$token[1]]) && $parameters[$token[1]]['type'] == 'select') {
      $form['provider']['parameters'][$token[1]]['value'] = array(
        '#type' => 'textarea',
        '#title' => t('Values'),
        '#default_value' => isset($parameters[$token[1]]) ? $parameters[$token[1]]['value'] : '',
      );
    }
  }
}

/**
 * Theme function for Mobile Codes providers export UI parameters.
 */
function theme_mobile_codes_providers_export_ui_form_parameters($variables) {
  $element = $variables['element'];

  $headers = array(t('Token'), t('Label'), t('Type'), t('Values'));
  $rows = array();
  foreach (element_children($element) as $child) {
    foreach (element_children($element[$child]) as $field) {
      unset($element[$child][$field]['#title']);
    }

    $rows[] = array(
      array('data' => drupal_render($element[$child]['token']) . "[{$element[$child]['token']['#value']}]"),
      array('data' => drupal_render($element[$child]['label'])),
      array('data' => drupal_render($element[$child]['type'])),
      array('data' => drupal_render($element[$child]['value'])),
    );
  }

  return theme('table', array('header' => $headers, 'rows' => $rows));
}

/**
 * Providers form submit callback.
 */
function mobile_codes_providers_export_ui_form_submit(&$form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

/**
 * Providers form AJAX calback.
 */
function mobile_codes_providers_export_ui_form_js($form, $form_state) {
  return $form['provider']['parameters'];
}
