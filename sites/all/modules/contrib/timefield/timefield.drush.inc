<?php

/**
 * @file
 *   drush integration for timefield.
 */

/**
 * The timefield plugin URI.
 */
define('TIMEFIELD_DOWNLOAD_URI', 'http://fgelinas.com/code/timepicker/releases/jquery-ui-timepicker-0.2.9.zip');

/**
 * Implements hook_drush_command().
 */
function timefield_drush_command() {
  $items = array();

  $items['timefield-plugin'] = array(
    'callback' => 'drush_timefield_plugin',
    'description' => dt("Downloads the jQuery UI Timepicker plugin."),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'arguments' => array(
      'path' => dt('Optional. A path where to install the timefield plugin. If omitted Drush will use the default location.'),
    ),
    'aliases' => array('timepicker-plugin'),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function timefield_drush_help($section) {
  switch ($section) {
    case 'drush:timefield-plugin':
      return dt("Downloads the jQuery UI Timepicker plugin, default location is sites/all/libraries.");
  }
}

/**
 * Command to download the timefield plugin.
 */
function drush_timefield_plugin() {
  if (!drush_shell_exec('type unzip')) {
    return drush_set_error(dt('Missing dependency: unzip. Install it before using this command.'));
  }

  $args = func_get_args();
  if (!empty($args[0])) {
    $path = $args[0];
  }
  else {
    $path = 'sites/all/libraries';
  }

  // Create the path if it does not exist.
  if (!is_dir($path)) {
    drush_op('mkdir', $path);
    drush_log(dt('Directory @path was created', array('@path' => $path)), 'notice');
  }

  // Set the directory to the download location.
  $olddir = getcwd();
  chdir($path);

  $filename = basename(TIMEFIELD_DOWNLOAD_URI);
  $dirname = 'jquery.timepicker';

  // Remove any existing timepicker plugin directory.
  if (is_dir($dirname)) {
    drush_log(dt('An existing timepicker plugin was overwritten at @path', array('@path' => $path)), 'notice');
  }
  // Remove any existing timefield plugin zip archive.
  if (is_file($filename)) {
    drush_op('unlink', $filename);
  }

  // Download the zip archive.
  if (!drush_shell_exec('wget ' . TIMEFIELD_DOWNLOAD_URI)) {
    drush_shell_exec('curl -O ' . TIMEFIELD_DOWNLOAD_URI);
  }

  if (is_file($filename)) {
    // Decompress the zip archive.
    drush_shell_exec('unzip -qq -o ' . $filename . ' -d ' . $dirname);
    // Remove the zip archive.
    drush_op('unlink', $filename);
  }

  // Set working directory back to the previous working directory.
  chdir($olddir);

  if (is_dir($path . '/' . $dirname)) {
    drush_log(dt('Timepicker plugin has been downloaded to @path', array('@path' => $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to download the Timepicker plugin to @path', array('@path' => $path)), 'error');
  }
}
