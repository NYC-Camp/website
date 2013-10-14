$Id: README.txt,v 1.2.2.1 2010/10/12 14:37:27 xeniox Exp $

Description
-----------
This module provides the ability to have more fine-grained control over what users with the permission 'administer permissions' can configure.
You can decide which user roles will see a limited permissions table at admin/user/permissions, and who has unrestricted access to it.
The modules allows you to lock certain permissions and / or certain roles. This means that these permissions / roles will not be available for configuration to a user with limited permission configuration rights.

This module could be useful if you want to allow a client to control website permissions for relatively harmless things like posting comments, creating content, administering taxonomy etc..., 
but you don't want the client to have the opportunity to change permissions for things like Views, content types, themes, ...

Installation
------------
1) Place the module folder in your sites/all/modules folder
2) Activate the module via admin/build/modules

Configuration
-------------
1) Optionally, go to admin/user/permissions and configure the permissions:
   - 'manage permission locks': users with this permission set can decide which permissions will be locked for users with limited access to the permission settings.
   - 'manage permissions unrestricted': users without this permission will have no right to configure permissions that are locked, while users with this permission are not restricted.
2) Go to Admin > Users > Permissions and click the tab 'Lock permissions'.
3) On this configuration page, you can decide what users with limited permission configuration rights can and cannot configure.
   You can both choose to lock certain permissions from being configured, as well as disallowing the ability to modify permissions for one or more roles.
4) Users with the 'administer permissions' permission, but without the 'manage permissions unrestricted' permissions, will now see a limited set a of permissions / roles to configure permissions for, based on the 'Lock permissions' settings.

Using hook_permissions_lock
---------------------------
This module supports a hook that lets you set permission locks through other modules. This allows you to specify the lock settings through code rather than through the database.
This could be useful to avoid repetition or migration problems in your projects.

Usage example:

/**
 * Implementation of hook_permissions_lock().
 */
function <modulename>_permissions_lock($type) {
  switch ($type) {
    case 'permission':
      return array('use PHP for block visibility', 'select different theme', 'administer views'); // specify permissions
    break;
    case 'role':
      return array(1, 2); // specify role ids
    break;
  }
}

Author
------
Sven Decabooter (http://drupal.org/user/35369)
The author can be contacted for paid customizations of this module as well as Drupal consulting and development.