<?php
/**
 * @file
 * The admin file containing the menu callback function.
 */

/**
 * Menu callback for the String Overrides module to display its administration.
 */
function chartbeat_admin_settings($form, &$form_state) {
  $form['chartbeat_uid'] = array(
    '#type' => 'textfield',
    '#title' => t('Account ID'),
    '#description' => t('In order to activate Chartbeat, you must enter your Account ID. You can
find yours <a href="@chartbeat">here</a>.',
      array('@chartbeat' => 'http://chartbeat.com/drupal')),
    '#default_value' => variable_get('chartbeat_uid', ''),
  );

  $domain = variable_get('chartbeat_domain', _chartbeat_get_default_domain());
  if (empty($domain)) {
    $domain = _chartbeat_get_default_domain();
  }

  $form['chartbeat_domain'] = array(
    '#type' => 'textfield',
    '#title' => t('Domain'),
    '#description' => t('The domain name of the site you want to track.'),
    '#default_value' => $domain,
  );
  $form['chartbeat_options_advanced'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['chartbeat_options_advanced']['chartbeat_use_canonical'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Canonical'),
    '#description' => t('If your site defines &lt;link rel="canonical"
      .../&gt;, you can set check this value to to make Chartbeat use the
      canonical path instead of the actual URL.'),
    '#default_value' => variable_get('chartbeat_use_canonical', '1'),
  );
  $form['chartbeat_options_advanced']['chartbeat_cookies'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Cookies'),
    '#description' => t('Customers who are subject to the EU e-Privacy Directive
      can set this variable to prevent Chartbeat from using cookies. NOTE: By
      using Chartbeat without cookies, you will be unable to see if a user is
      new or returning.'),
    '#default_value' => variable_get('chartbeat_cookies', '1'),
  );
  $form['chartbeat_options_live'] = array(
    '#type' => 'fieldset',
    '#title' => t('Live Stats'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['chartbeat_options_live']['chartbeat_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Chartbeat API Key'),
    '#description' => t('To enable live stats in your Drupal dashboard, please enter your API key. You can find yours <a href="@api">here</a>.',
       array('@api' => 'http://chartbeat.com/drupal/')),
    '#default_value' => variable_get('chartbeat_api_key', ''),
  );
  $form['chartbeat_publishing'] = array(
    '#type' => 'fieldset',
    '#title' => t('Chartbeat Publishing Options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('These options are only available to Chartbeat Publishing accounts. For more
      information, visit <a href=http://chartbeat.com/publishing/>Chartbeat Publishing</a>.'),
  );

  $sections_enabled = isset($form_state['values']['chartbeat_sections_enable']) ? (bool) $form_state['values']['chartbeat_sections_enable'] : variable_get('chartbeat_sections_enable', FALSE);

  $form['chartbeat_publishing']['chartbeat_sections_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable sections'),
    '#description' => t('Enables section tracking. See <a href="@groups">here</a>
      for more information.',
      array('@groups' => 'http://chartbeat.com/docs/configuration_variables/#groups')),
    '#default_value' => module_exists('taxonomy') ? $sections_enabled : FALSE,
    '#disabled' => module_exists('taxonomy') ? FALSE : TRUE,
  );

  if (module_exists('taxonomy')) {
    $form['chartbeat_publishing']['chartbeat_sections_enable']['#ajax'] = array(
      'callback' => 'chartbeat_admin_settings_publishing_sections_callback',
      'wrapper' => 'chartbeat-sections-taxonomy-vocab-wrapper',
      'method' => 'replace',
    );

    $form['chartbeat_publishing']['chartbeat_sections_wrapper'] = array(
      '#type' => 'fieldset',
      '#title' => t('Current Vocabularies'),
      '#prefix' => '<div id="chartbeat-sections-taxonomy-vocab-wrapper">',
      '#suffix' => '</div>',
      '#collapsible' => FALSE,
      '#collapsed' => FALSE,
      '#description' => !module_exists('taxonomy') ? t('The taxonomy module must be enabled to use sections.') : ($sections_enabled ? t('Select which taxonomy vocabularies will be tracked as sections.') : t('You must enable sections support to select taxonomy vocabularies.')),
    );

    if ($sections_enabled || !empty($form_state['values']['chartbeat_sections_enable'])) {
      $form['chartbeat_publishing']['chartbeat_sections_wrapper']['chartbeat_sections'] = array(
        '#type' => 'checkboxes',
        '#options' => _chartbeat_vocab_array_format(taxonomy_get_vocabularies()),
        '#default_value' => variable_get('chartbeat_sections', ''),
      );
    }
  }

  $form['chartbeat_publishing']['chartbeat_authors_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable authors'),
    '#description' => t('Enable author tracking. See <a href="@groups">here</a> for more information.', array(
      '@groups' => 'http://chartbeat.com/docs/configuration_variables/#groups',
    )),
    '#default_value' => variable_get('chartbeat_authors_enabled', FALSE),
  );

  return system_settings_form($form);
}

/**
 * Page callback for the dashboard iframe embed page.
 */
function chartbeat_dashboard_page() {
  $url = variable_get('chartbeat_domain', '');
  $key = variable_get('chartbeat_api_key', '');
  if (!empty($url) && !empty($key)) {
    $content = "<iframe src=\"http://chartbeat.com/dashboard/?url=$url&k=$key&slim=1\" height=\"700\" width=\"100%\"></iframe>";
  }
  else {
    $content = 'Notice: You must save the domain and API key on the settings page to see the dashboard.';
  }
  $variables = array(
    '#type' => 'markup',
    '#markup' => $content,
  );

  return render($variables);
}

/**
 * Page callback for the dashboard iframe embed page.
 */
function chartbeat_publishing_dashboard_page() {
  $url = variable_get('chartbeat_domain', '');
  $key = variable_get('chartbeat_api_key', '');
  if (!empty($url) && !empty($key)) {
    $content = "<iframe src=\"http://chartbeat.com/publishing/dashboard/?url=$url&k=$key&slim=1\" height=\"700\" width=\"100%\"></iframe>";
  }
  else {
    $content = 'Notice: You must save the domain and API key on the settings page to see the dashboard.';
  }
  $variables = array(
    '#type' => 'markup',
    '#markup' => $content,
  );

  return render($variables);
}

/**
 * Ajax callback for enabling or disabling the `Enable sections` option.
 *
 * @return array
 *   Returns the form fields that are to be used as a replacement.
 */
function chartbeat_admin_settings_publishing_sections_callback($form, $form_state) {
  return $form['chartbeat_publishing']['chartbeat_sections_wrapper'];
}

/**
 * Helper function to format the list of vocabularies properly.
 *
 * @param array $array
 *   array of vocabularies
 *
 * @return array
 *   reformatted array of vocabulary names, keyed by VID
 */
function _chartbeat_vocab_array_format($array = NULL) {
  $vocab_array = array();
  foreach ($array as $vocab) {
    $vocab_array[$vocab->vid] = $vocab->name;
  }
  return $vocab_array;
}
