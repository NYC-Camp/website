// $Id: $

(function ($) {

Drupal.behaviors.weightFieldsetSummaries = {
  attach: function (context) {
    // Provide the summary for the node type form.
    $('fieldset#edit-weight-form', context).drupalSetSummary(function(context) {
      var vals = [];

      // Default weight setting.
      vals.push(Drupal.t("Weight: @weight", {'@weight': $("select[name='node_weight'] option:selected", context).text()}));

      return Drupal.checkPlain(vals.join(', '));
    });
  }
};

})(jQuery);

