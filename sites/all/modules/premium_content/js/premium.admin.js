(function ($) {
 "use strict";

  Drupal.behaviors.premiumAdmin = {
    attach: function(context, settings) {
      // Show/hide the duration selection only if needed.
      $("#edit-protection-type input").change(function() {
        if ($(this).attr('checked')) {
          if ($(this).attr('id') === 'edit-protection-type-all') {
            $('#edit-protection-duration').hide();
          }
          else {
            $('#edit-protection-duration').show();
          }
        }
      });
      $("#edit-protection-type input:checked").trigger('change');
    }
  };
}(jQuery));

