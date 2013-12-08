/**
 * @file
 * Drupal behaviors for jPlayer content protection.
 */
(function ($) {

  Drupal.jPlayerProtect = Drupal.jPlayerProtect || {};

  Drupal.behaviors.jPlayerProtectNavigation = {
    attach: function(context, settings) {
      $('.jp-jplayer', context).each(function() {
        var wrapper = this.parentNode;
        var player = $(this);
        player.playerType = $(this).parent().attr('class');
        player.filter(':not(.jplayer-protect-processed)').addClass('jplayer-protect-processed').each(function() {
          // We can't use the play event as it's fired *after* jPlayer
          // attempts to download the audio.
          $(wrapper).find('a.jp-play, a.jp-next, a.jp-previous').each(function() {
            $(this).click(function() {
              if (Drupal.settings.jPlayer.protect) {
                if ($(this).attr('class') == 'jp-next') {
                  Drupal.jPlayer.next(wrapper, player);
                }
                if ($(this).attr('class') == 'jp-previous') {
                  Drupal.jPlayer.previous(wrapper, player);
                }
                Drupal.jPlayerProtect.authorize(wrapper, player);
              }
            });
          });
        });
      });
    }
  };

  Drupal.behaviors.jPlayerProtectPlaylist = {
    attach: function(context, settings) {
      $('.jp-jplayer', context).each(function() {
        var wrapper = this.parentNode;
        var player = $(this);
        player.playerType = $(this).parent().attr('class');
        var playerId = $(player).attr('id');
        player.filter(':not(.jplayer-protect-playlist-processed)').addClass('jplayer-protect-playlist-processed').each(function() {
          $('#' + playerId + '_playlist').find('a').click(function(){
            if (Drupal.settings.jPlayer.protect) {
              var index = $(this).attr('id').split('_')[2];
              if (index) {
                Drupal.jPlayer.setFiles(wrapper, player, index, true);
              }
              Drupal.jPlayerProtect.authorize(wrapper, player);
            }
          });
        });
      });
    }
  };

  /**
   * Ping the authorization URL to gain access to protected files.
   */
  Drupal.jPlayerProtect.authorize = function(wrapper, player) {
    // Generate the authorization URL to ping.
    var time = new Date();

    var track = "";
    if (player.playerType != 'jp-type-playlist') {
      // For a single track, it's easy to get the file to play.
      // TODO fix this for jPlayer 2.0.
      track = $(player).attr('rel');
    }
    else {
      // Get a reference to the current track using the <ul> list that is used
      // for the jPlayer playlist.
      track = $('#' + player.attr('id') + '_playlist .jp-playlist-current a').attr('href');
    }

    var authorize_url = Drupal.settings.basePath + 'jplayer_protect/authorize/' + Drupal.jPlayerProtect.base64Encode(track) + '/' + Drupal.jPlayerProtect.base64Encode(parseInt(time.getTime() / 1000).toString());

    // Ping the authorization URL. We need to disable async so that this
    // command finishes before thisandler returns.

    $.ajax({
      url: authorize_url,
      success: function(data) {
        // Check to see if the access has expired. This could happen due to
        // clock sync differences between the server and the client.
        var seconds = parseInt(data);
        var expires = new Date(seconds * 1000);
        if ($('#jplayer-message').size() == 0) {
          $(wrapper).parent().prepend('<div id="jplayer-message" class="messages error"></div>');
          $('#jplayer-message').hide();
        }
        if (expires < time) {
          var message = Drupal.t('There was an error downloading the audio. Try <a href="@url">reloading the page</a>. If the error persists, check that your computer\'s clock is accurate.', {"@url" : window.location});
          $('#jplayer-message').fadeOut('fast').html("<ul><li>" + message + "</li></ul>").fadeIn('fast');
          $(wrapper).hide();
        }
        else {
          $('#jplayer-message').fadeOut('fast');
        }
      },
      async: false
    });
    return false;
  };

  Drupal.jPlayerProtect.base64Encode = function(data) {
    // From http://phpjs.org/functions/base64_encode:358 where it is
    // dual licensed under GPL/MIT.
    //
    // http://kevin.vanzonneveld.net
    // +   original by: Tyler Akins (http://rumkin.com)
    // +   improved by: Bayron Guevara
    // +   improved by: Thunder.m
    // +   improved by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
    // +   bugfixed by: Pellentesque Malesuada
    // +   improved by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
    // -    depends on: utf8_encode
    // *     example 1: base64_encode('Kevin van Zonneveld');
    // *     returns 1: 'S2V2aW4gdmFuIFpvbm5ldmVsZA=='
    var b64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    var o1, o2, o3, h1, h2, h3, h4, bits, i = 0,
        ac = 0,
        enc = "",
        tmp_arr = [];

    if (!data) {
        return data;
    }

    data = Drupal.jPlayerProtect.utf8Encode(data + '');

    do { // pack three octets into four hexets
        o1 = data.charCodeAt(i++);
        o2 = data.charCodeAt(i++);
        o3 = data.charCodeAt(i++);

        bits = o1 << 16 | o2 << 8 | o3;

        h1 = bits >> 18 & 0x3f;
        h2 = bits >> 12 & 0x3f;
        h3 = bits >> 6 & 0x3f;
        h4 = bits & 0x3f;

        // use hexets to index into b64, and append result to encoded string
        tmp_arr[ac++] = b64.charAt(h1) + b64.charAt(h2) + b64.charAt(h3) + b64.charAt(h4);
    } while (i < data.length);

    enc = tmp_arr.join('');

    switch (data.length % 3) {
    case 1:
        enc = enc.slice(0, -2) + '==';
        break;
    case 2:
        enc = enc.slice(0, -1) + '=';
        break;
    }

    return enc;
  };

  Drupal.jPlayerProtect.utf8Encode = function(argString) {
    // From http://phpjs.org/functions/utf8_encode:577 where it is dual-licensed
    // under GPL/MIT.
    // http://kevin.vanzonneveld.net
    // +   original by: Webtoolkit.info (http://www.webtoolkit.info/)
    // +   improved by: Kevin van Zonneveld (http://kevin.vanzonneveld.net)
    // +   improved by: sowberry
    // +    tweaked by: Jack
    // +   bugfixed by: Onno Marsman
    // +   improved by: Yves Sucaet
    // +   bugfixed by: Onno Marsman
    // +   bugfixed by: Ulrich
    // +   bugfixed by: Rafal Kukawski
    // *     example 1: utf8_encode('Kevin van Zonneveld');
    // *     returns 1: 'Kevin van Zonneveld'

    if (argString === null || typeof argString === "undefined") {
        return "";
    }

    var string = (argString + ''); // .replace(/\r\n/g, "\n").replace(/\r/g, "\n");
    var utftext = "",
        start, end, stringl = 0;

    start = end = 0;
    stringl = string.length;
    for (var n = 0; n < stringl; n++) {
        var c1 = string.charCodeAt(n);
        var enc = null;

        if (c1 < 128) {
            end++;
        } else if (c1 > 127 && c1 < 2048) {
            enc = String.fromCharCode((c1 >> 6) | 192) + String.fromCharCode((c1 & 63) | 128);
        } else {
            enc = String.fromCharCode((c1 >> 12) | 224) + String.fromCharCode(((c1 >> 6) & 63) | 128) + String.fromCharCode((c1 & 63) | 128);
        }
        if (enc !== null) {
            if (end > start) {
                utftext += string.slice(start, end);
            }
            utftext += enc;
            start = end = n + 1;
        }
    }

    if (end > start) {
        utftext += string.slice(start, stringl);
    }

    return utftext;
  };

})(jQuery);

