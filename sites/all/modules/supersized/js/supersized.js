jQuery(function($){
  function supersized_callback() {
    // Bind click event to the overlay if link is set of the active slide.
    var url = api.getField('url');
    if (url) {
      var overlay = $('#supersized-overlay');
      overlay.css('cursor', 'pointer');
      overlay.unbind('click').bind('click', function(){
        var new_window = parseInt(Drupal.settings.supersized.new_window);
        if (new_window) {
          window.open(url);
        }
        else {
          window.location = url;
        }
        return false;
      });
    }
    // Check if user determine callback is defined.
    if(typeof window.supersized_slide_callback == 'function'){
      supersized_slide_callback();
    }
  }
  // Prepare slide_links.
  if (Drupal.settings.supersized.slide_links == 0) {
    Drupal.settings.supersized.slide_links = false;
  }
  $.supersized.themeVars.image_path = Drupal.settings.supersized.image_path;
  $.supersized({
    // Functionality.
    slideshow               : 1,
    autoplay                : parseInt(Drupal.settings.supersized.autoplay),
    start_slide             : parseInt(Drupal.settings.supersized.start_slide),
    stop_loop               : parseInt(Drupal.settings.supersized.stop_loop),
    random                  : parseInt(Drupal.settings.supersized.random),
    slide_interval          : parseInt(Drupal.settings.supersized.slide_interval),
    transition              : parseInt(Drupal.settings.supersized.transition),
    transition_speed        : parseInt(Drupal.settings.supersized.transition_speed),
    new_window              : parseInt(Drupal.settings.supersized.new_window),
    pause_hover             : parseInt(Drupal.settings.supersized.pause_hover),
    keyboard_nav            : parseInt(Drupal.settings.supersized.keyboard_nav),
    performance             : parseInt(Drupal.settings.supersized.performance),
    image_protect           : parseInt(Drupal.settings.supersized.image_protect),
    on_new_slide            : supersized_callback,

    // Size & Position.
    min_width               : parseInt(Drupal.settings.supersized.min_width),
    min_height              : parseInt(Drupal.settings.supersized.min_height),
    vertical_center         : parseInt(Drupal.settings.supersized.vertical_center),
    horizontal_center       : parseInt(Drupal.settings.supersized.horizontal_center),
    fit_always              : parseInt(Drupal.settings.supersized.fit_always),
    fit_portrait            : parseInt(Drupal.settings.supersized.fit_portrait),
    fit_landscape           : parseInt(Drupal.settings.supersized.fit_landscape),

    // Components.
    slide_links             : Drupal.settings.supersized.slide_links,
    thumb_links             : parseInt(Drupal.settings.supersized.thumb_links),
    thumbnail_navigation    : parseInt(Drupal.settings.supersized.thumbnail_navigation),
    slides                  : Drupal.settings.supersized.slides,

    // Theme Options.
    progress_bar            : parseInt(Drupal.settings.supersized.progress_bar),
    mouse_scrub             : parseInt(Drupal.settings.supersized.mouse_scrub)
  });
});
