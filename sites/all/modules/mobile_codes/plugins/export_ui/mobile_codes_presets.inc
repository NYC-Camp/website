<?php
/**
 * @file
 */

/**
 * CTools Export UI required function for plugin definition
 */
function mobile_codes_mobile_codes_presets_ctools_export_ui() {
  return array(
    'schema' => 'mobile_codes_presets',
    'access' => 'administer mobile codes',
    'menu' => array(
      'menu prefix' => 'admin/config/content/mobile_codes',
      'menu item' => 'presets',
      'menu title' => 'Presets',
      'menu description' => 'Administer Mobile Codes presets.',
    ),
    'title singular' => t('preset'),
    'title singular proper' => t('Preset'),
    'title plural' => t('presets'),
    'title plural proper' => t('Presets'),
    'form' => array(
      'settings' => 'mobile_codes_presets_export_ui_form',
      'submit' => 'mobile_codes_presets_export_ui_form_submit',
    ),
  );
}

/**
 * Presets form.
 */
function mobile_codes_presets_export_ui_form(&$form, &$form_state) {
  $providers = ctools_export_crud_load_all('mobile_codes_providers');

  $form['info']['#type'] = 'container';
  $form['info']['#attributes'] = array(
    'class' => array('clearfix'),
  );

  $form['info']['provider'] = array(
    '#type' => 'select',
    '#title' => t('Provider'),
    '#options' => array(),
    '#default_value' => $form_state['item']->provider,
    '#ajax' => array(
      'callback' => 'mobile_codes_presets_export_ui_form_js',
      'wrapper' => 'defaults-wrapper',
    ),
  );
  foreach ($providers as $provider) {
    if (!isset($provider->disabled) || !$provider->disabled) {
      $form['info']['provider']['#options'][$provider->name] = $provider->name;
    }
  }
  asort($form['info']['provider']['#options']);

  $form['preset']['defaults'] = array(
    '#type' => 'fieldset',
    '#title' => t('Defaults'),
    '#prefix' => '<div id="defaults-wrapper">',
    '#suffix' => '</div>',
    '#tree' => TRUE,
  );

  $provider = isset($form_state['values']) ? $form_state['values']['provider'] : $form_state['item']->provider;
  $provider = isset($provider) ? $provider : current($form['info']['provider']['#options']);
  $provider = ctools_export_crud_load('mobile_codes_providers', $provider);

  $defaults = isset($form_state['values']) ? $form_state['values']['defaults'] : $form_state['item']->defaults;

  foreach (element_children($provider->parameters) as $parameter) {
    switch ($provider->parameters[$parameter]['type']) {
      case 'select':
        $provider->parameters[$parameter]['value'] = explode("\n", $provider->parameters[$parameter]['value']);
        $options = array();
        foreach ($provider->parameters[$parameter]['value'] as $value) {
          $value = explode('|', $value);
          $options[$value[0]] = isset($value[1]) ? $value[1] : $value[0];
        }
        $title = isset($provider->parameters[$parameter]['label']) ? $provider->parameters[$parameter]['label'] : $parameter;
        $form['preset']['defaults'][$parameter] = array(
          '#type' => 'select',
          '#title' => check_plain($title),
          '#options' => $options,
          '#default_value' => isset($defaults[$parameter]) ? $defaults[$parameter] : current($options),
        );
        break;

      case 'text':
        $title = isset($provider->parameters[$parameter]['label']) ? $provider->parameters[$parameter]['label'] : $parameter;
        $form['preset']['defaults'][$parameter] = array(
          '#type' => 'textfield',
          '#title' => check_plain($title),
          '#size' => 5,
          '#default_value' => isset($defaults[$parameter]) ? $defaults[$parameter] : '',
          '#required' => TRUE,
        );
        break;
    }
  }

  $extras = module_invoke_all('mobile_codes_presets_extras', $form_state['item']->extras);
  if (!empty($extras)) {
    $form['extras'] = array(
      '#type' => 'fieldset',
      '#title' => t('Extras'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#tree' => TRUE,
    );

    foreach ($extras as $delta => $extra) {
      $form['extras'][$delta] = $extra['form'];
    }
  }
}

/**
 * Presets form submit callback.
 */
function mobile_codes_presets_export_ui_form_submit(&$form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}

/**
 * Presets form AJAX calback.
 */
function mobile_codes_presets_export_ui_form_js($form, $form_state) {
  return $form['preset']['defaults'];
}
