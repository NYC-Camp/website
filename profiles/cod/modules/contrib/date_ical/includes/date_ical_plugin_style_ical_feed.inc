<?php

/**
 * @file
 * Views style plugin for the Date iCal module.
 */

/**
 * Default style plugin to render an iCal feed.
 */
class date_ical_plugin_style_ical_feed extends views_plugin_style {
  
  function _default_calendar_name() {
    $view_title = $this->view->get_title();
    $calendar_name = variable_get('site_name', 'Drupal');
    $calendar_name .= !empty($view_title) ? ': ' . $view_title : '';
    return $calendar_name;
  }
  
  // Sets up the iCal feed icon on calendar pages.
  function attach_to($display_id, $path, $title) {
    $display = $this->view->display[$display_id]->handler;
    $url_options = array();
    $input = $this->view->get_exposed_input();
    if ($input) {
      $url_options['query'] = $input;
    }
    $url_options['absolute'] = TRUE;
    $url = url($this->view->get_url(NULL, $path), $url_options);
    if (empty($this->preview)) {
      $this->view->feed_icon .= theme('date_ical_icon', array('url' => $url, 'title' => $title));
      drupal_add_html_head_link(array(
        'rel' => 'alternate',
        'type' => 'application/calendar',
        'title' => $title,
        'href' => $url
      ));
    }
  }
  
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    // Allow users to override the default Calendar name (X-WR-CALNAME).
    $form['cal_name'] = array(
      '#type' => 'textfield',
      '#title' => t('iCal Calendar Name'),
      '#default_value' => $this->options['cal_name'],
      '#description' => t('This will appear as the title of the iCal feed. If ' .
        'left blank, the View Title will be used. If that is also blank, the site ' .
        'name will be inserted as the iCal feed title.'),
    );
  }
  
  function render() {
    if (empty($this->row_plugin) || $this->row_plugin->plugin_name != 'date_ical') {
      debug('views_plugin_style_ical_feed: This style plugin supports only the iCal Entity row plugin.');
      return 'To enable iCal output, this view\'s Format must be configured to Show: iCal Entity.';
    }
    $rows = array();
    foreach ($this->view->result as $row_index => $row) {
      $this->view->row_index = $row_index;
      $rows[] = $this->row_plugin->render($row);
    }
    unset($this->view->row_index);

    // Try to load the iCalcreator library, and check if that worked.
    $library = libraries_load('iCalcreator');
    if (!empty($library['loaded'])) {
      // Create a vcalendar object using the iCalcreator library.
      $config = array('unique_id' => 'Drupal: Date iCal');
      $vcalendar = new vcalendar($config);
      $vcalendar->setMethod('PUBLISH');
      
      // If the iCal Calendar Name has been set in the Feed Style options, it's used as the
      // title in the iCal feed. If not, the View Title is used. If that is blank, then the
      // Site Name is used.
      $cal_name = $this->options['cal_name'];
      if (empty($cal_name)) {
        $view_title = $this->view->get_title();
        if (!empty($view_title)) {
          $cal_name = $view_title;
        }
        else {
          $cal_name = variable_get('site_name', 'Drupal');
        }
      }
      $vcalendar->setProperty('x-wr-calname', $cal_name, array('VALUE' => 'TEXT'));

      // Now add the vevents.
      $timezones = array();
      foreach ($rows as $row) {
        if (empty($row)) {
          // The row plugin returned NULL for this row, which can happen due to
          // various error conditions. The only thing we can do is skip it.
          continue;
        }
        
        $vevent = $vcalendar->newComponent('vevent');
        // Get the start date as an array.
        $rendered_date = $row['start']->toArray();
        if ($row['all_day']) {
          $rendered_date['hour'] = FALSE;
          $rendered_date['minute'] = FALSE;
          $rendered_date['second'] = FALSE;
        }
        $timezone = $row['start']->getTimezone()->getName();
        $timezones[$timezone] = $timezone;
        $vevent->setDtstart(
          $rendered_date['year'],
          $rendered_date['month'],
          $rendered_date['day'],
          $rendered_date['hour'],
          $rendered_date['minute'],
          $rendered_date['second'],
          $timezone);

        // Keep a copy of the start date, as it's useful later.
        $rendered_start = $rendered_date + array('tz' => $row['start']->getTimezone());

        // Only add the end date if there is one.
        if (!empty($row['end'])) {
          $rendered_date = $row['end']->toArray();
          $timezone = $row['start']->getTimezone()->getName();
          $timezones[$timezone] = $timezone;
          $vevent->setDtend(
            $rendered_date['year'],
            $rendered_date['month'],
            $rendered_date['day'],
            $rendered_date['hour'],
            $rendered_date['minute'],
            $rendered_date['second'],
            $timezone);
          // Keep a copy of the start date, as it's useful later.
          $rendered_end = $rendered_date + array('tz' => $row['end']->getTimezone());
        }
        $vevent->setProperty('uid', $row['uid']);
        $vevent->setProperty('summary', $row['summary']);

        // Handle repeating dates from the date_repeat module.
        if (!empty($row['rrule']) && module_exists('date_repeat')) {
          // Split the rrule into the actual rule, exceptions and additions.
          list($rrule, $exceptions, $additions) = date_repeat_split_rrule($row['rrule']);
          // Add the rrule itself. We need to massage the data a bit, since iCalcreator expects RRULEs to be
          // in a different format than the Date API gives them to us.
          $rrule = self::convert_rrule_for_icalcreator($rrule);
          $vevent->setRrule($rrule);
          // Process exceptions if there are any.
          if (!empty($exceptions)) {
            $exdates = array();
            foreach ($exceptions as $exception) {
              $except = date_ical_date($exception, 'UTC');
              date_timezone_set($except, $rendered_start['tz']);
              $rendered_date = $except->toArray();
              $exdates[] = array(
                'year' => $rendered_date['year'],
                'month' => $rendered_date['month'],
                'day' => $rendered_date['day'],
                // Use the time information from the start date.
                'hour' => $rendered_start['hour'],
                'min' => $rendered_start['minute'],
                'second' => $rendered_start['second'],
                'tz' => $rendered_start['tz']->getName(),
              );
            }
            // Add those exclusions as 'EXDATE's.
            $vevent->setExdate($exdates);
          }
          // Process additions if there are any.
          if (!empty($additions)) {
            $add_dates = array();
            foreach ($additions as $addition) {
              $add = date_ical_date($addition, 'UTC');
              date_timezone_set($add, $rendered_start['tz']);
              $rendered_date = $add->toArray();

              $add_date = array(
                'year' => $rendered_date['year'],
                'month' => $rendered_date['month'],
                'day' => $rendered_date['day'],
                // Use the time information from the start date.
                'hour' => $rendered_start['hour'],
                'min' => $rendered_start['minute'],
                'second' => $rendered_start['second'],
                'tz' => $rendered_start['tz']->getName(),
              );
              // If there was an end date specified, use that too.
              if (!empty($row['end'])) {
                $add_date = array($add_date);
                $add_date[] = array(
                  'year' => $rendered_date['year'],
                  'month' => $rendered_date['month'],
                  'day' => $rendered_date['day'],
                  // Use the time information from the end date.
                  'hour' => $rendered_end['hour'],
                  'min' => $rendered_end['minute'],
                  'second' => $rendered_end['second'],
                  'tz' => $rendered_end['tz']->getName(),
                );
              }

              $add_dates[] = $add_date;
            }
            // Add the additions as 'RDATE's.
            $vevent->setRdate($add_dates);
          }
        }
        if (!empty($row['url'])) {
          $vevent->setUrl($row['url'], array('type' => 'URI'));
        }
        if (!empty($row['location'])) {
          $vevent->setProperty('location', $row['location']);
        }
        if (!empty($row['description'])) {
          $vevent->setProperty('description', $row['description']);
        }
        if (!empty($row['last-modified'])) {
          $lm = $row['last-modified']->toArray();
          $vevent->setLastModified(
            $lm['year'],
            $lm['month'],
            $lm['day'],
            $lm['hour'],
            $lm['minute'],
            $lm['second'],
            $lm['timezone']
          );
        }
        
        // Allow other modules to alter the VEVENT object.
        drupal_alter('date_ical_feed_ical_vevent_render', $vevent, $this->view, $row);
      }

      // Now add all the timezones we just used to the file too.
      foreach ($timezones as $timezone) {
        iCalUtilityFunctions::createTimezone($vcalendar, $timezone);
      }

      // Allow other modules to alter the calendar as a whole.
      drupal_alter('date_ical_feed_ical_vcalendar_render', $vcalendar, $this->view);

      $output = $vcalendar->createCalendar();
    }
    else {
      // The iCalcreator library isn't available, so we can't output anything.
      $output = 'Please install the iCalcreator library to enable iCal output.';
    }

    if (empty($variables['view']->live_preview)) {
      // Prevent devel module from appending queries to ical export.
      $GLOBALS['devel_shutdown'] = FALSE;
      drupal_add_http_header('Content-Type', 'application/calendar; charset=utf-8');
    }
    
    header('Content-type: text/calendar');
    // For sites with Clean URLs disabled, the "path" value in the view Display
    // doesn't actually get applied to the URL of the calendar feed. So, we
    // need to manually instruct browsers to download a .ics file.
    if (!variable_get('clean_url', FALSE)) {
      $path_array = explode('/', $this->display->display_options['path']);
      $filename = array_pop($path_array);
      header("Content-Disposition: attachment; filename=\"$filename\"");
    }
    
    return $output;
  }
  
  /**
   * This function converts an rrule array to the iCalcreator format.
   *
   * iCalcreator expects the BYDAY element to be an array like this:
   * (array) ( [([plus] ordwk / minus ordwk)], "DAY" => weekday )
   *
   * But the way that the Date API gives it to us is like this:
   * (array) ( [([plus] ordwk / minus ordwk)]weekday )
   */
  public static function convert_rrule_for_icalcreator($rrule) {
    $new_rrule = array();
    foreach ($rrule as $key => $value) {
      if (strtoupper($key) == 'DATA') {
        // iCalcreator doesn't expect the 'DATA' key that the Date API gives us.
        continue;
      }
      if (strtoupper($key) == 'BYDAY') {
        $new_byday = array();
        foreach ($value as $day) {
          // Fortunately, the weekday values are always 2 characters, so it's easy to
          // split off the ordwk part, even though it could be 1 or 2 characters.
          $weekday = substr($day, -2);
          $ordwk = substr($day, 0, -2);
          $new_byday[] = array($ordwk, 'DAY' => $weekday);
        }
        $value = $new_byday;
      }
      
      $new_rrule[$key] = $value;
    }
    return $new_rrule;
  }
}
