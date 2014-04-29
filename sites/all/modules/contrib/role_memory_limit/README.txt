-- SUMMARY --
Role memory limit is a small module that allow you to
set php_memory_limit per role and command line usage(drush).


-- EXAMPLE OF USAGE --
Lets say your php_memory_limit is set to 128mb
and your site has a lot of blocks and you try to get into 
block listing page and drupal crashes.

That is becuse there isn't enough memory.

With this module you can set so the admin have more php_memory_limit,
that way you can render pages that needs alot of memory
but still keep the original php_memory_limit for other users.

To submit bug reports and feature suggestions, or to track changes:
http://drupal.org/project/issues/1810870


-- REQUIREMENTS --
Permission to change php_memory_limit on your webserver.


-- INSTALLATION --

  * Drupal 7
  Install as usual.
  See http://drupal.org/documentation/install/modules-themes/modules-7
  for further information.


-- CONFIGURATION --

  * Drupal 7
  Go to admin/people/permissions#module-role_memory_limit 
  to set the persmission.
  
  Go to admin/config/development/role_memory_limit
  to set the limit for a role.
