<?php

/**
 * @file
 * Template file for timefield
 *
 * variables available:
 *
 * $time['time'] - the formatted output of this field, with a hyphen between
 * the first and second time if the "to time" exists.
 * $time['formatted_value'] - first time value formatted as described in display
 * settings
 * $time['formatted_value2'] - second time value formatted as described in
 * display settings
 * $time['value'] - integer value of first time, expressed as timezone
 * agnostic offset from 00:00
 * $time['value2'] - integer value of second time, expressed as timezone
 * agnostic offset from 00:00
 *
 * If this is a weekly repeat, the following array will also be available
 * $time['days'] - an array of days, keyed by 3 letter signifier
 *
 */

?>
<div class="time-default">
<?php print $time['time'] ?>
</div>
