UNDERSTANDING THESE SCRIPTS
---------------------------

Versions of Internet Explorer before IE9 don't understand HTML5 or CSS3 media
queries, two technologies that modern web design depends on. Fortunately, there
are JavaScript shims that can add a degree of compatibility back into IE.

The html5-respond.js script that is included by Zen is a combination of the
following scripts:

- HTML5 shim: IE does not recognize HTML5 elements and will not allow them to be
  styled unless they are added to the DOM. http://code.google.com/p/html5shim/

- HTML5 innerShiv: If HTML5 tags are added outside of the DOM and inserted via
  innerHTML(), or a jQuery equivalent, IE will not recognize the tags.
  http://jdbartlett.com/innershiv/

- innerShiv monkeypatch for jQuery's ajax method: The innerShiv script needs
  some glue code so that jQuery will utilize it "automatically".
  http://drupal.org/node/1180142

- Respond.js: IE doesn't understand CSS3 media queries. This script adds support
  for min/max-width queries. https://github.com/scottjehl/Respond

By default, Zen includes the html5-respond.js from within the html.tpl.php
template. If you want to change that behavior, you can simply override that
template from within your sub-theme. To help you while modifying that template,
the js/src directory contains the source of these files and various combinations
of some of them.

- html5-innershiv.js:
  Same as html5-respond.js but without the respond script.

- html5.src.js:
  Original source of the HTML5 shim.

- innershiv.min.js:
- innershiv.src.js:
  Minimized version and original source of the innershiv.src.js.

- jquery-innershiv-monkeypatch.min.js:
- jquery-innershiv-monkeypatch.src.js:
  Minimized version and original source of the monkeypatch.

- respond.min.js:
- respond.src.js:
  Minimized version and original source of the respond.js script.
