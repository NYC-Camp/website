The Mobile Codes module provides the ability to render Text, URLs or any other
form of informaton as a Mobile Code, including but not limited to the QR and
Datamatrix formats, providing a simple way of transfering said information from
the screen to a Mobile phone.

Mobile Codes was written and is maintained by Stuart Clark (deciphered).
- http://stuar.tc/lark



Features
--------------------------------------------------------------------------------

* User definable and Features exportable Mobile Code Providers and Presets.
  * Defaults provided:
    * Six (6) External Providers.
    * One (1) Internal Provider (see below).
    * Three (3) to five (5) Presets (based on installed modules).
* Render Mobile Codes via:
  * Field/Views formatters:
    * File module.
    * Image modules.
    * Link module.
    * Text module.
    * plus example Custom Formatters for extended support.
  * Pseudo field via Content Types.
  * Input filter.
  * Tokens:
    * Text field tokens.
    * URL tokens.
    * User vCard tokens.
  * Drupal API Theme() call.
* Blocks:
  * Node URL block - Creates a Mobile Code of the current Node URL.
  * User vCard - Uses the vCard module to provide a vCard Mobile Code from a
    Nodes Author or a users profile.
  * Mobile Code generator - An Admin module optimized helper block.
* Support for:
  * Drupal core Image module - Use an Image style on the Mobile Codes.
  * Shorten module - Shorten URLs in Mobile Codes.



Required modules
--------------------------------------------------------------------------------

* Chaos tool suite module.



Recommended modules
--------------------------------------------------------------------------------

* Custom Formatters module.
* Drupal core Image module.
* Libraries API module.



Configuration
--------------------------------------------------------------------------------

All configuration for Mobile Codes can be found at:
  Administer > Configuration > Content authoring > Mobile Codes
  http://[www.yoursite.com/path/to/drupal]/admin/config/content/mobile_codes


Note: When using the Input filter, be sure to enable the <IMG> tag on your Text
      format or the Mobile Code will be filtered out.



Advanced configuration
--------------------------------------------------------------------------------

* Setting up an internal Provider with the PHP QR Code library:

  1. Download, install and enable the Libraries API module.
       http://drupal.org/project/libraries

  2. Download the PHP QR Code library.
       http://sourceforge.net/projects/phpqrcode/files/releases/phpqrcode-2010100721_1.1.4.zip/download

  3. Extract the PHP QR Code library to your Libraries directory.
       e.g. sites/all/libraries/phpqrcode

  4. Clear cached data from the Perfomance page.
       Administer > Configuration > Development > Performance
       http://[www.yoursite.com/path/to/drupal]/admin/config/development/performance


  Note: Mobile Codes will automatically detect the PHP QR Code library once
        installed as above and add a new PHP QR Code Provider to the list.



Makefile entries
--------------------------------------------------------------------------------

For easy downloading of Mobile Codes and it's required/recommended modules
and/or libraries, you can use the following entries in your makefile:


  projects[ctools][subdir] = contrib
  projects[ctools][version] = 1.3

  projects[libraries][subdir] = contrib
  projects[libraries][version] = 2.1

  libraries[phpqrcode][download][type] = get
  libraries[phpqrcode][download][url] = http://sourceforge.net/projects/phpqrcode/files/releases/phpqrcode-2010100721_1.1.4.zip/download

