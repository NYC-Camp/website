DESCRIPTION
--------------

Timefield is a Field API field that can store 3 types of time values: a simple
time value, a start time and end time, or a combination of these two with a 
basic weekly repeat value.  The values are stored in the database as integer 
offsets from 12AM.  If the second value continues into the next day, 
i.e. 8PM - 2AM, the second value is stored as an offset +1 day.

The goal of this field is to provide time storage that is not dependent on the 
Gregorian calendar.

INSTALLATION
------------

1) Start by copying the module files into your 'modules' directory.  For more
information: http://drupal.org/documentation/install/modules-themes/modules-7

2) The Timefield module utilizes a jQuery plugin to assist with the input of
time values.  The use of this plugin is facilitated by the Libraries module. If 
not already installed, download, enable, and configure the latest versions of 
the Libraries module. See:
http://drupal.org/project/libraries

3) Acquire the timepicker plugin.  There are a few ways to do this.
a) Direct Download:
You can either download a zip or tarball file from github:
https://github.com/fgelinas/timepicker/downloads
Or you can download the plugin from the author's site:
http://fgelinas.com/code/timepicker
Once you have the compressed file, unzip it to the libraries folder to a
subfolder called "jquery.timepicker".
The main javascript file should have a path like this:
/sites/all/libraries/jquery.timepicker/jquery.ui.timepicker.js

b) You can also clone the repository directly:
From your libraries subfolder, execute this command:
git clone https://github.com/fgelinas/timepicker.git jquery.timepicker

c) If you have drush installed, you can use the command 
"drush timefield-plugin" to automatically download and install this library.

USAGE
-------
Timefield module provides a field type 'timefield' with a default JQuery widget.
The timefield can have an optional 'to time' and various input formats, 
depending on your preference.  While this field is multi-value capable, 
I am not really sure about a use-case for this.  
There are a three display formatters, time (with optional to time, duration,
and a mini-calendar output.  You can configure various output formats in the 
format settings dialog option on the "Manage Display" section of the Field API 
UI.
