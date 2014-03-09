<?php
/**
 * @file
 * A file to contain overrides to the css aggregation.
 */

/**
 * Magic override callback to group CSS items.
 *
 * This function arranges the CSS items that are in the #items property of the
 * styles element into groups. Arranging the CSS items into groups serves two
 * purposes. When aggregation is enabled, files within a group are aggregated
 * into a single file, significantly improving page loading performance by
 * minimizing network traffic overhead. When aggregation is disabled, grouping
 * allows multiple files to be loaded from a single STYLE tag, enabling sites
 * with many modules enabled or a complex theme being used to stay within IE's
 * 31 CSS inclusion tag limit: http://drupal.org/node/228818.
 *
 * This function puts multiple items into the same group if they are groupable
 * and if they are for the same 'media' and 'browsers'. Items of the 'file' type
 * are groupable if their 'preprocess' flag is TRUE, items of the 'inline' type
 * are always groupable, and items of the 'external' type are never groupable.
 * This function also ensures that the process of grouping items does not change
 * their relative order. This requirement may result in multiple groups for the
 * same type, media, and browsers, if needed to accommodate other items in
 * between.
 *
 * @param $css
 *   An array of CSS items, as returned by drupal_add_css(), but after
 *   alteration performed by drupal_get_css().
 *
 * @return
 *   An array of CSS groups. Each group contains the same keys (e.g., 'media',
 *   'data', etc.) as a CSS item from the $css parameter, with the value of
 *   each key applying to the group as a whole. Each group also contains an
 *   'items' key, which is the subset of items from $css that are in the group.
 *
 * @see drupal_pre_render_styles()
 * @see system_element_info()
 */
function magic_group_css($css) {
  $magic_mq_embed = theme_get_setting('magic_embedded_mqs');

  $groups = array();
  // If a group can contain multiple items, we track the information that must
  // be the same for each item in the group, so that when we iterate the next
  // item, we can determine if it can be put into the current group, or if a
  // new group needs to be made for it.

  $current_group_keys = NULL;
  // When creating a new group, we pre-increment $i, so by initializing it to
  // -1, the first group will have index 0.
  $i = -1;
  foreach ($css as $item) {
    // The browsers for which the CSS item needs to be loaded is part of the
    // information that determines when a new group is needed, but the order of
    // keys in the array doesn't matter, and we don't want a new group if all
    // that's different is that order.
    ksort($item['browsers']);

    // If the item can be grouped with other items, set $group_keys to an array
    // of information that must be the same for all items in its group. If the
    // item can't be grouped with other items, set $group_keys to FALSE. We
    // put items into a group that can be aggregated together: whether they will
    // be aggregated is up to the _drupal_css_aggregate() function or an
    // override of that function specified in hook_css_alter(), but regardless
    // of the details of that function, a group represents items that can be
    // aggregated. Since a group may be rendered with a single HTML tag, all
    // items in the group must share the same information that would need to be
    // part of that HTML tag.
    switch ($item['type']) {
      case 'file':
        // Group file items if their 'preprocess' flag is TRUE.
        // Help ensure maximum reuse of aggregate files by only grouping
        // together items that share the same 'group' value and 'every_page'
        // flag. See drupal_add_css() for details about that.
        if ($item['preprocess']) {
          // Ignore the media query if CSS aggregation is enabled.
          $group_keys = $magic_mq_embed ? array($item['type'], $item['group'], $item['every_page'], $item['browsers']) : array($item['type'], $item['group'], $item['every_page'], $item['media'], $item['browsers']);
        }
        else {
          $group_keys = FALSE;
        }
        break;
      case 'inline':
        // Always group inline items.
        $group_keys = array($item['type'], $item['media'], $item['browsers']);
        break;
      case 'external':
        // Do not group external items.
        $group_keys = FALSE;
        break;
    }

    // If the group keys don't match the most recent group we're working with,
    // then a new group must be made.
    if ($group_keys !== $current_group_keys) {
      $i++;
      // Initialize the new group with the same properties as the first item
      // being placed into it. The item's 'data' and 'weight' properties are
      // unique to the item and should not be carried over to the group.
      $groups[$i] = $item;
      unset($groups[$i]['data'], $groups[$i]['weight']);
      $groups[$i]['items'] = array();
      $current_group_keys = $group_keys ? $group_keys : NULL;
    }

    // Add the item to the current group.
    $groups[$i]['items'][] = $item;
  }
  return $groups;
}

/**
 * Magic override callback to aggregate CSS files and inline content.
 *
 * Having the browser load fewer CSS files results in much faster page loads
 * than when it loads many small files. This function aggregates files within
 * the same group into a single file unless the site-wide setting to do so is
 * disabled (commonly the case during site development). To optimize download,
 * it also compresses the aggregate files by removing comments, whitespace, and
 * other unnecessary content. Additionally, this functions aggregates inline
 * content together, regardless of the site-wide aggregation setting.
 *
 * @param $css_groups
 *   An array of CSS groups as returned by drupal_group_css(). This function
 *   modifies the group's 'data' property for each group that is aggregated.
 *
 * @see drupal_group_css()
 * @see drupal_pre_render_styles()
 * @see system_element_info()
 */
function magic_aggregate_css(&$css_groups) {
  $preprocess_css = (variable_get('preprocess_css', FALSE) && (!defined('MAINTENANCE_MODE') || MAINTENANCE_MODE != 'update'));
  $magic_mq_embed = theme_get_setting('magic_embedded_mqs');

  // For each group that needs aggregation, aggregate its items.
  foreach ($css_groups as $key => $group) {
    switch ($group['type']) {
      // If a file group can be aggregated into a single file, do so, and set
      // the group's data property to the file path of the aggregate file.
      case 'file':
        if ($group['preprocess'] && $preprocess_css) {
          if ($magic_mq_embed) {
            $css_groups[$key]['data'] = magic_build_css_cache($group['items']);
          }
          else {
            $css_groups[$key]['data'] = drupal_build_css_cache($group['items']);
          }
        }
        break;
      // Aggregate all inline CSS content into the group's data property.
      case 'inline':
        $css_groups[$key]['data'] = '';
        foreach ($group['items'] as $item) {
          $css_groups[$key]['data'] .= drupal_load_stylesheet_content($item['data'], $item['preprocess']);
        }
        break;
    }
  }
}

/**
 * Aggregates and optimizes CSS files into a cache file in the files directory.
 *
 * The file name for the CSS cache file is generated from the hash of the
 * aggregated contents of the files in $css. This forces proxies and browsers
 * to download new CSS when the CSS changes.
 *
 * The cache file name is retrieved on a page load via a lookup variable that
 * contains an associative array. The array key is the hash of the file names
 * in $css while the value is the cache file name. The cache file is generated
 * in two cases. First, if there is no file name value for the key, which will
 * happen if a new file name has been added to $css or after the lookup
 * variable is emptied to force a rebuild of the cache. Second, the cache file
 * is generated if it is missing on disk. Old cache files are not deleted
 * immediately when the lookup variable is emptied, but are deleted after a set
 * period by drupal_delete_file_if_stale(). This ensures that files referenced
 * by a cached page will still be available.
 *
 * @param $css
 *   An array of CSS files to aggregate and compress into one file.
 *
 * @return
 *   The URI of the CSS cache file, or FALSE if the file could not be saved.
 */
function magic_build_css_cache($css) {
  $data = '';
  $uri = '';
  $map = variable_get('drupal_css_cache_files', array());
  // Create a new array so that only the file names are used to create the hash.
  // This prevents new aggregates from being created unnecessarily.
  $css_data = array();
  foreach ($css as $css_file) {
    $css_data[] = $css_file['data'];
  }
  $key = hash('sha256', serialize($css_data));
  if (isset($map[$key])) {
    $uri = $map[$key];
  }

  if (empty($uri) || !file_exists($uri)) {
    // Build aggregate CSS file.
    foreach ($css as $stylesheet) {
      // Only 'file' stylesheets can be aggregated.
      if ($stylesheet['type'] == 'file') {
        $contents = drupal_load_stylesheet($stylesheet['data'], TRUE);

        // Build the base URL of this CSS file: start with the full URL.
        $css_base_url = file_create_url($stylesheet['data']);
        // Move to the parent.
        $css_base_url = substr($css_base_url, 0, strrpos($css_base_url, '/'));
        // Simplify to a relative URL if the stylesheet URL starts with the
        // base URL of the website.
        if (substr($css_base_url, 0, strlen($GLOBALS['base_root'])) == $GLOBALS['base_root']) {
          $css_base_url = substr($css_base_url, strlen($GLOBALS['base_root']));
        }

        _drupal_build_css_path(NULL, $css_base_url . '/');
        // Anchor all paths in the CSS with its base URL, ignoring external and absolute paths.

        // We change this section to add in media queries into the aggregate, to
        // save http requests.
        $contents = preg_replace_callback('/url\(\s*[\'"]?(?![a-z]+:|\/+)([^\'")]+)[\'"]?\s*\)/i', '_drupal_build_css_path', $contents);
        if ($stylesheet['media'] != 'all') {
          $contents = "\n" . $contents;
          $contents = '@media ' . $stylesheet['media'] . ' { ' . $contents . ' }' . "\n";
          $stylesheet['media'] = 'all';
        }

        $data .= $contents;
      }
    }

    // Per the W3C specification at http://www.w3.org/TR/REC-CSS2/cascade.html#at-import,
    // @import rules must proceed any other style, so we move those to the top.
    $regexp = '/@import[^;]+;/i';
    preg_match_all($regexp, $data, $matches);
    $data = preg_replace($regexp, '', $data);
    $data = implode('', $matches[0]) . $data;

    // Prefix filename to prevent blocking by firewalls which reject files
    // starting with "ad*".
    $filename = 'css_' . drupal_hash_base64($data) . '.css';
    // Create the css/ within the files folder.
    $csspath = 'public://css';
    $uri = $csspath . '/' . $filename;
    // Create the CSS file.
    file_prepare_directory($csspath, FILE_CREATE_DIRECTORY);
    if (!file_exists($uri) && !file_unmanaged_save_data($data, $uri, FILE_EXISTS_REPLACE)) {
      return FALSE;
    }
    // If CSS gzip compression is enabled, clean URLs are enabled (which means
    // that rewrite rules are working) and the zlib extension is available then
    // create a gzipped version of this file. This file is served conditionally
    // to browsers that accept gzip using .htaccess rules.
    if (variable_get('css_gzip_compression', TRUE) && variable_get('clean_url', 0) && extension_loaded('zlib')) {
      if (!file_exists($uri . '.gz') && !file_unmanaged_save_data(gzencode($data, 9, FORCE_GZIP), $uri . '.gz', FILE_EXISTS_REPLACE)) {
        return FALSE;
      }
    }
    // Save the updated map.
    $map[$key] = $uri;
    variable_set('drupal_css_cache_files', $map);
  }
  return $uri;
}
