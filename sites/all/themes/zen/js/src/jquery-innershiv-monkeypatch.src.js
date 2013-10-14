// Monkeypatch the innerShiv in the ajax insert method.
(function () {

if (Drupal.ajax) {
  var _insert = Drupal.ajax.prototype.commands.insert;
  Drupal.ajax.prototype.commands.insert =  function (ajax, response, status) {
    response.data = innerShiv(response.data, false);
    _insert(ajax,response,status);
  }
}

})();
