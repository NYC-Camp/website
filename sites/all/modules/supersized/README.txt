
CONTENTS OF THIS FILE
---------------------

 * Author
 * Description
 * Dependencies
 * Usage
 * Installation
 * Context
 * Themes
 * After slide JS callback
 * Hooks
 * Notes

AUTHOR
------
Aaron Fan (http://drupal.org/user/576672)

DESCRIPTION
-----------
This module make it easy to implement Supersized JQuery plugin into Druapl
system. All available Supersized JQuery settings are configurable by UI.

A field type "Supersized Slide" comes with this module, and obviously,
Supersized background slides are managed by fields of node.

We have also provided a Context reaction, so you could assign node with
Supersized field by any Context condition!

DEPENDENCIES
------------
context
file
image
imagecache_actions
libraries (>=2)

We are trying to minimize the dependencies as much as possible. However, the
file size of background images can be very huge. So we decided to predefine an
image style which is going to scale down the dimension and well as changing the
file format into jpeg which helps a lot to reduce the file size.

USAGE
-----
1. Add a "Supersized Slide" field to any content type, in most of the cases,
this would be a multiple value field.
2. Configure the Supersized options such as transition, interval, etc...
3. Create a new content and upload beautiful images using the Supersized field.
Yes, there you go! Supersized is just that easy to setup.

* Important, if the background of your theme is not transparent, you will not
be able to see the background.  You may need to make changes to your theme CSS.

INSTALLATION
------------
Download Supersized from:
http://bit.ly/YCHcYs
This is not the official release, however, this branch provide an "after slide"
JS callback which dramatically increases the ability to create awesome effects.

1. Decompress the downloaded file and place it in the the libraries folder such
   as sites/all/libraries.
2. Install this module as usual, and enabled Supersized.
3. (Optional) Enable Supersized context, which allow you to assign content with
   Supersized under any context condition.

* Important, we will be using the js and css files from supersized/slideshow.

CONTEXT
---------
Enabled Supersized Context, you will find a new condition and a reaction.  Use
this new condition to determine weather a page has Supersized, and use this new
reaction to assign node with Supersized.

For example, you may want to have Supersized on a page which is created by
Views, and the path is `/latest-blog`.  You should create a node that has
Supersized field, upload your beautiful pictures and save it.  You will then
create a new context, condition with be path: /latest-blog, and your reaction
would be Supersized: a chosen node.

THEMES
------
Theme functions as follow:
theme_supersized_overlay()
theme_supersized_arrow_nav()
theme_supersized_progress_bar()
theme_supersized_thumbnail_navigation()
theme_supersized_thumb_links()
theme_supersized_slide_links()
template_preprocess_supersized_control_bar()

The default them comes with Supersized JQuery plugin supports 'image_path'. The
default path would be {LIBRARY PATH}/supersized/slideshow/img, however, if your
theme contains /images/supersized/ this folder, images will be crab from this
folder instead.

AFTER SLIDE CALLBACK
--------------------
Define a js function and name it `supersized_slide_callback`.  This function
will be called after each slides.

/**
 * Supersized slide callback function.
 */
function am_billboard_slide_callback() {
  var title = api.getField('title');
  var body = api.getField('body');
  // Do something with the slide title and body...
}

HOOKS
-----
hook_supersized_overlay()
This is for adding custom overlay pattern.  Define
YOURMODULE_supersized_overlay() in your module, and this hook should return the
an array such as

return array(
  'your_style_01' => array(
    'name' => t('Your Style 1'),
    'file' => 'filename of image',
    'file path' => 'path to image',
  ),
  'your_style_02' => array(
    'name' => t('Your Style 2'),
    'file' => 'filename of image',
    'file path' => 'path to image',
  ),
);

For example:
function YOURMODULE_supersized_overlay() {
  $file_path = module_get_path('module', 'YOURMODULE');
  return array(
    'YOURMODULE_1' => array(
      'name' => t('YOURMODULE 1'),
      'file' => 'overlay_01.png',
      'file path' => $file_path,
    ),
    'YOURMODULE_2' => array(
      'name' => t('YOURMODULE 2'),
      'file' => 'overlay_01.png',
      'file path' => $file_path,
    ),
  );
}

NOTES
-----
1. Some users has report that html, and body has to be 100%, otherwise scrollbar
   will be randomly appear and disappear.  This is somehow depends depends on
   your theme.  You may set this in case you are having the same problem.
   (http://drupal.org/node/1974030#comment-7405596)

2. Issue about stretching image to fit whole screen.
   (http://drupal.org/node/1978216)
