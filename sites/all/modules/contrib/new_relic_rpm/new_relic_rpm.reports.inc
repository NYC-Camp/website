<?php
/**
 * @file
 * Reporting page callbacks.
 */

/**
 * Main page for RPM reporting. List all the applications on this API Key.
 */
function new_relic_rpm_reporting() {

  // If no API key is set, break here and error out.
  $api_key = variable_get('new_relic_rpm_api_key', '');
  if (empty($api_key)) {
    drupal_set_message(t('You need to enter your New Relic API key from your New Relic account settings page before you are able to view reports within Drupal. Visit the <a href="@settings">New Relic RPM Drupal admin page</a> to enter your API key.', array('@settings' => url('admin/config/new-relic-rpm'))), 'error');
    return '<h2>' . t('No API key found.') . '</h2>';
  }

  // Get basic app health. This is also our first check for a bad key/access denied.
  // Only hit the REST API every 60 seconds.
  if ($_SESSION['new_relic_rpm_health_time'] < $_SERVER['REQUEST_TIME'] - 60 || !$_SESSION['new_relic_rpm_health_xml']) {
    $app_health = new_relic_rpm_curl('https://rpm.newrelic.com/accounts.xml?include=application_health');
  }
  else {
    $app_health = $_SESSION['new_relic_rpm_health_xml'];
  }
  // Error out of the return is False, store data if it is good.
  if (!$app_health) {
    drupal_set_message(t('The New Relic REST API has denied your key. Either the key you entered on the <a href="@settings">New Relic RPM Drupal admin page</a> is incorrect, or you have not enabled API access for this application within the New Relic RPM webiste.', array('@settings' => url('admin/config/new-relic-rpm'))), 'error');
    return '<h2>' . t('API access denied.') . '</h2>';
  }
  else {
    $_SESSION['new_relic_rpm_health_time'] = $_SERVER['REQUEST_TIME'];
    $_SESSION['new_relic_rpm_health_xml'] = $app_health;
  }

  return new_relic_rpm_render_health($app_health);
}

/**
 * Load the details for a specfic application.
 */
function new_relic_rpm_reporting_details($cust_id, $app_id) {

  $output = '';

  // If no API key is set, break here and error out.
  $api_key = variable_get('new_relic_rpm_api_key', '');
  if (empty($api_key)) {
    drupal_set_message(t('You need to enter your New Relic API key from your New Relic account settings page before you are able to view reports within Drupal. Visit the <a href="@settings">New Relic RPM Drupal admin page<a/> to enter your API key.', array('@settings' => url('admin/config/new-relic-rpm'))), 'error');
    return '<h2>' . t('No API key found.') . '</h2>';
  }

  // Only hit the REST API every 60 seconds.
  if ($_SESSION['new_relic_rpm_dash_time'] < $_SERVER['REQUEST_TIME'] - 60 || !$_SESSION['new_relic_rpm_dash_xml']) {
    $app_dashboard = new_relic_rpm_curl('https://rpm.newrelic.com/application_dashboard?application_id=' . $app_id);
  }
  else {
    $app_dashboard = $_SESSION['new_relic_rpm_dash_xml'];
  }

  // Error out if value is false, save cached copy of XML if it is good.
  if (!$app_dashboard) {
    drupal_set_message(t('The New Relic REST API has denied your key. Either the key you entered on the <a href="@settings">New Relic RPM Drupal admin page</a> is incorrect, or you have not enabled API access for this application within the New Relic RPM webiste.', array('@settings' => url('admin/config/new-relic-rpm'))), 'error');
    return '<h2>' . t('API access denied.') . '</h2>';
  }
  else {
    $_SESSION['new_relic_rpm_dash_time'] = $_SERVER['REQUEST_TIME'];
    $_SESSION['new_relic_rpm_dash_xml'] = $app_dashboard;
  }

  $output .= $app_dashboard;

  //$post_vars['deployment[application_id]'] = check_plain($_GET['app_name']);
  //$deployments = new_relic_rpm_curl('https://rpm.newrelic.com/deployments.xml', $post_vars);
  //$output .= '<pre>'.htmlentities(print_r($deployments, TRUE)).'</pre>';
  $output .= new_relic_rpm_render_actions($cust_id, $app_id);

  return $output;
}

/**
 * Render the application health display.
 * TODO -- Figure out the threshold information
 */
function new_relic_rpm_render_health($app_health) {

  $app_obj = simplexml_load_string($app_health);
  $cust_id = (string) $app_obj->account->id;

  $apps = $app_obj->account->applications;
  foreach ($apps as $app) {
    foreach ($app as $data) {

      foreach ($data->{"threshold-values"} as $val) {
        foreach ($val->threshold_value as $v) {

          $app_name = (string) $data->name;
          $attr_name = (string) $v->attributes()->name;
          $app_data[$app_name][$attr_name]['val'] = (string) $v->attributes()->formatted_metric_value;
          $app_data[$app_name][$attr_name]['mval'] = (string) $v->attributes()->metric_value;
          $app_data[$app_name][$attr_name]['thresh'] = (string) $v->attributes()->threshold_value;
          $app_data[$app_name]['AppID'] = (string) $data->id;

        }

      }
    }
  }

  $table['header'] = array(
    'App Name',
    'App ID',
    'ApDex',
    'Resp. Time',
    'Errors %',
    'Error Rate (EPM)',
    'Throughput (rpm)',
    'App Busy %',
    'DB %',
    'CPU',
    'Memory',
    'Details',
  );

  $metrics = array('Apdex', 'Response Time', 'Errors', 'Error Rate', 'Throughput', 'Application Busy', 'DB', 'CPU', 'Memory');
  foreach ($app_data as $k => $v) {
    $row = array($k, $v['AppID']);
    foreach ($metrics as $metric) {
      $cell = array('data' => $v[$metric]['val']);
      if ($v[$metric]['mval'] > $v[$metric]['thresh']) {
        $cell['class'] = 'error';
      }
      $row[] = $cell;
    }
    $row[] = l('Details', 'admin/reports/new-relic-rpm/details/' . $cust_id . '/' . $v['AppID'], array('query' => array('app_name' => $k)));
    $table['rows'][] = $row;
  }

  return theme('table', $table);
}

/**
 * Render the quick actions menu.
 */
function new_relic_rpm_render_actions($cust_id, $app_id) {

  $rpm_url = "https://rpm.newrelic.com/accounts/{$cust_id}/applications/{$app_id}";
  $actions = array(
    'transactions' => t('Web Transactions'),
    'databases' => t('Database Activity'),
    'background_tasks' => t('Background Tasks'),
    'traced_errors' => t('Traced Errors'),
    'edit' => t('App Settings'),
    'edit_alerts' => t('App Alerts & Thresholds'),
    'deployments' => t('Deployments'),
  );
  $links = array(
    'overview' => array(
      'title' => t("Overview"),
      'href' => $rpm_url,
      'attributes' => array('class' => '_blank'),
    )
  );
  foreach ($actions as $action => $title) {
    $links[$action] = array(
      'title' => $title,
      'href' => "{$rpm_url}/{$action}",
      'attributes' => array('target' => '_blank'),
    );
  }

  $list = array(
    'heading' => t('Links to New Relic\'s website for this Application'),
    'links' => $links,
  );

  return theme('links', $list);
}
