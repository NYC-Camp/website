This project is a greenhouse for Rules functionality – triggers, actions, data
types, conditions and more that could be included in the Rules module, but
probably should be tested out and voted on first. Feel free to add your own
ideas, opinions, examples and feature requests!

INSTALLATION
============

The usual. Download, enable. You will need the Rules module. (Surprise!)


RULES BONUS: MISCELLANEOUS
==========================

Conditions

* Check number of results from a view: This condition loads a view and checks
  the number of results – condition is passed if it is at least as many results
  as you set. You can pass on arguments to the view.

Actions

* Load a node list with Views: This action executes a node view, along with any
  defined arguments, and loads the result as Rules list. This allows executing
  Rules loops on the results of a view. Yeah.

* Load a user list with Views: This works the same way as the previous action,
  but acts on user views and returns a list of users.

* Load a comment list with Views: This works the same way as the previous
  action, but acts on comment views and returns a list of comments.

* Set page title: This action sets the page title. The page title will be used
  as $title in page.tpl.php. The action uses drupal_set_title to set the current
  page title

* Set the active menu item: This action is A FIRST ATTEMPT at setting the active
  menu item using Rules. It sets the active menu item in the sense that the menu
  recognises it and show all children links. Currently it sets active-trail
  class on the item chosen. Requires the Menu position module.

* Clone a node: This action clones a node and resets a few properties (such as
  nid) before saving it. Useful if you want to clone a node, but make some
  changes in the copy.

* Load the first node in a Views list: This action fetches the first node in a
  node view (assuming there is at least one row of results). It is similar to
  loading a node list with Views (see above), but is quicker if you are only
  interested in getting the first hit. This is useful if you want to perform
  more complex queries than "fetch entity by property" allows.

* Create a date from a number: This action provides a variable of the date type,
  with the time given in an integer unix timestamp.

* Load a path alias: Fetches the alias for a given path and, optionally, a given
  language.

* Merge two strings: Allows merging two strings into a new one. This action is
  only present because it is currently not possible to get metadata from text
  variables. :-/

Events

* Allow Page manager variants to act as Rule even triggers: This introduces a
  new setting on your Page manager variants – "Create a Rules event for this
  variant" (found in the new tab "Reactions"). This makes your variant appear in
  the list of Rules events, allowing you to execute Rules conditions and
  conditions when variants are loaded. Not least: You also get the context
  objects in the variant to work with.

Other

* All Rules condition components are exposed as CTools access plugins, for
  example making them accessible in Page manager and Panels.

RULES BONUS: THEME
==================

Actions

* Set head title: This action sets the head title. This is the <title> element
  in the HTML document. The action implements hook_preprocess_html to set the
  head title

* Set body class: This adds classes to the <body> element. It can use available
  substitutions. The outputted class is sanitized. The action implements
  hook_preprocess_html to set additional body classes.

RULES BONUS: BLOCK
==================

Actions

* Place a block: This action lets you place a block in a region, and decide its
  weight. Works on both blocks enabled by default (thereby moving them) and on
  disabled blocks (thereby enabling them). All regions in all enabled themes are
  available for selection.

* Disable a block: This action hides a block from view.

RULES BONUS: VIEWS
==================

Data types

* View display: This data type contains a number of properties.
  - Read-only properties are machine name, human name, display (machine) name,
    base table and total number of rows (assuming the view has been built).
  - Writable properties are: argument values (list of text strings), current
    page number, items per page and offset.
  - View handlers are also available, but currently only supports reading of
    alias names and the action 'unset a view handler' described below. Available
    handlers are fields, contextual filters, sort criteria, filters,
    relationships, headers, footers and no-result behaviours.

Plugins

* Views argument validator: This plugin can be used for building custom
  validators for Views arguments (contextual filter values). The validators have
  access to the current argument as well as a list of all arguments (so far)
  provided to the view, and can alter both. The plugin must set the 'validation'
  variable to TRUE to mark the argument as valid.

Events

* Before a view is being built: This event allows Rules to, for example, change
  the arguments being sent to the view. You cannot, however, read the number of
  results (since the view has not yet been executed).
* After a view has been built: This allows Rules to act whenever a view is going
  to be rendered. Allows, for example, to check the number of results from a
  view.
* After a view has been rendered: This is very similar to the previous event,
  but also contains the actual output of the view.

Actions

* Unset a view handler: This allows removing a handler, such as a filter or
  a field, based on its alias.

RULES BONUS: THINK TWICE
========================

This module contains experimental code for Rules. The module depends on bad
judgement. If you need to enable/disable a module through Rules you probably
have other problems to deal with.

Actions

* Enable a module: Now you can have modules enabled when users log in!

* Disable a module: Combine this with the 'module has been enabled' event for
  interesting effects.

* Modify $page: Now you can override any part of the $page render array, and
  finally have the main content set to your favourite video clip. On all pages!
