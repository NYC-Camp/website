<?php
/**
 * @file
 * Hooks provided by the RDF module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Allow modules to define Premium levels in code.
 *
 * Providing default Premium levels can be very helpful for features, or 
 * for providing your own custom modules on top of Premium. The format 
 * is standard CTools exportable format.
 *
 * @return 
 *   An associative array of Premium levels, where, keyed by machine 
 *   name. Each level is a stdClass object with the following attributes:
 *   - api_version: If we for future version change the API, this field 
 *     will be changed. For now, it should always have the value 1.
 *   - name: The human readable name of the premium level as a string. 
 *     Could be something simple like 'Bronze Members only'.
 *   - machine_name: The name Drupal uses internally for this level. 
 *     Stored in database tables. Can only contain lowercase letters,
 *     numbers, and underscores. Should be the same as the array key.
 *   - protection_type: One of 'all', 'archive', or 'latest'.
 *   - duration: Duration of Premium status. A number, combines with
 *     the duration unit to specify protection length (for 
 *     protection_type 'latest') or the time that passes before content
 *     is protected (protection_type 'archive'). Has no effect if 
 *     protection_type is 'all'.
 *   - duration_unit: D for days, W for weeks, M for months, Y for years.
 *   - denied_message: The message displayed to the user when Premium 
 *     access is not granted.
 *   - denied_message_format: ID of the text format used for the 
 *     denied_message. This uses standard Drupal input format ids.
 */
function hook_default_premium_levels() {
  $export = array();

  $preset = new stdClass;
  $preset->api_version = 1;
  $preset->name = 'My Premium level';
  $preset->machine_name = 'my_level';
  $preset->protection_type = 'all';
  $preset->duration = 2;
  $preset->duration_unit = 'W';
  $preset->denied_message = t('Full text available to special people only.');
  $preset->denied_message_format = FILTER_FORMAT_DEFAULT;

  $export['my_level'] = $preset;

  return $export;
}

/**
 * Allow modules to determine premium content access for specific content.
 *
 * @param $node
 *   The node we're checking access for.
 * @param $teaser
 *   TRUE if only the node teaser is being displayed. This will likely 
 *   affect your access logic, since teaser mode is not normally 
 *   restricted as premium content.
 * @return
 *   TRUE if access is granted, FALSE if it is denied, or NULL if you do 
 *   not want to alter the verdict. Please note that the first 
 *   hook_premium_access() implementation that returns a boolean value 
 *   gets to determine whether access is denied or allowed, so in most 
 *   use cases, you should return nothing (or NULL) if you do not want 
 *   to explicitly grant access, so Premium's standard role-based 
 *   permissions will take effect.
 */
function hook_premium_access(&$node, $teaser) {
  global $user;

  // We don't alter the access teasers - default is always allow, which 
  // is fine with us.
  if ($teaser) {
    return;
  }

  // If node has our custom level, we check the user.
  if ($node->premium == 'my_level') {
    global $user;
    
    // You have a Reveal IT e-mail-address, you're granted access.
    // This is a silly example, but you can do arbitrarily complex logic here.
    if (preg_match('/@revealit.dk$/', $user->mail)) {
      return TRUE;
    }
  }
}

/**
 * @} End of "addtogroup hooks".
 */

