CONTENTS OF THIS FILE
---------------------
 * Introduction
 * Usage
 * Integration with other modules
 * Setting data
 * Getting data


INTRODUCTION
---------------------

Maintainer: afox / Antti Kettunen <antti.kettunen@aspectus.fi>

First login is a simple utility module which enables the use of "first
logins". With this module the site admin can enable content or do things
that appear only on the first login for users.


USAGE
-----

Install the module as usual. Go to admin/settings/first_login and set the
number of logins that are counted as "first". Then implement as either 
Context condition or in custom code.


INTEGRATION WITH OTHER MODULES
------------------------------

First login will integrate nicely with both Views (field + filter) and 
Context (condition). The best way to use First Login is using it as a 
Context condition plugin.

First login also provides a couple utility functions to set and get first 
login data. Available data is either "status" or "count".


SETTING DATA
------------

To set data programmatically, use first_login_set_data -function.

first_login_set_data($account, $data = array())

 * $account is the user object to be modified
 * $data is the array of keys to change ('status' or 'count')

Possible keys:
 * status - Boolean indicating whether 
            first logins are active for this user
 * count - integer count of the logins


GETTING DATA
------------
To get data, use first_login_get_data -function

first_login_get_data($uid = NULL, $key = NULL)

You can either get just the specific key or all of the data. 
If $uid is omitted, the current user is used.
