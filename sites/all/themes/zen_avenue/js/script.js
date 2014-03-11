/**
 * @file
 * A JavaScript file for the theme.
 *
 * In order for this JavaScript to be loaded on pages, see the instructions in
 * the README.txt next to this file.
 */

// JavaScript should be made compatible with libraries other than jQuery by
// wrapping it with an "anonymous closure". See:
// - http://drupal.org/node/1446420
// - http://www.adequatelygood.com/2010/3/JavaScript-Module-Pattern-In-Depth
(function ($, Drupal, window, document, undefined) {

	// Instagram block
	$(document).ready(function() {
		$(".instagram").instagram({
			hash: 'nyccamp',
			show: '9',
			clientId: '5d11182acc7f44739c96ca8d2f7b8ac9'
	  });
	});

/*
  $(document).ready(function() {
    $(".colorbox-instagram").colorbox({
    });
  });
*/

	$(window).load(function () {
	 	$('div.instagram-placeholder').each( function(i) {
	  	if( i % 4 != 3 )
	    return
		 	$(this).addClass('last')
		})
	});

  $(window).load(function() {
    $('.flexslider').flexslider();
  });


  // Mobile menus
  $(document).ready(function () {
    $("#min-menu a").click(function(event){
      $("body").toggleClass("sideslide");
      $("body").removeClass("scheduleslide");
      event.stopPropagation();
      event.preventDefault();
      $('html').bind('click', closeMobileNav);
    });
    $("#min-schedule a").click(function(event){
      $("body").toggleClass("scheduleslide");
      $("body").removeClass("sideslide");
      event.stopPropagation();
      event.preventDefault();
      $('html').bind('click', closeMobileNav);
    });

    $('#mobile-nav, .region-sidebar-first').click(function(event){
      event.stopPropagation();
    });

    //close mobile navs on the click outside of nav area
    function closeMobileNav() {
      $("body").removeClass("sideslide");
      $("body").removeClass("scheduleslide");
      $('html').unbind('click');
    }
  });

})(jQuery, Drupal, this, this.document);
