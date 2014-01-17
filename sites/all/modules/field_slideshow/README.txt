

--- README  -------------------------------------------------------------

Field Slideshow

Provides a Slideshow format for displaying Image and Media fields, using the JQuery Cycle plugin.

Compared to Views slideshows, building the slideshow from multiple nodes, this module builds it from a single node, if you're using a multi-valued Image field.


--- INSTALLATION --------------------------------------------------------

1 - Extract the module into sites/{sitename}/modules directory
2 - Download the JQuery Cycle plugin here : http://jquery.malsup.com/cycle/download.html (don't choose the Lite version), and move the downloaded jquery.cycle.all.js file into /sites/all/libraries/jquery.cycle/
3 - If you're planning to use a carousel for pager, Download the JCarousel plugin here : http://sorgalla.com/jcarousel, and move the content of the downloaded folder into the /sites/all/libraries/jquery.jcarousel folder of your server. When this is done there should be a file sites/all/libraries/jquery.jcarousel/lib/jquery.jcarousel.js, or jquery.jcarousel.min.js


--- USAGE ---------------------------------------------------------------

1 - Enable Field Slideshow at /admin/modules, (Image, Field, and Field UI required as well)
2 - Create or edit a content type at /admin/structure/types and include an Image field. Edit this image field to make it so that multiple image files may be added ("Number of values" setting at admin/structure/types/manage/{content type}/fields/{field_image}).
3 - Go to "Manage display" for your content type (/admin/structure/types/manage/{content type}/display) and switch the format of your multiple image field from Image to Slideshow.
4 - Click the settings wheel in the slideshow-formatted multiple image field to edit advanced settings
5 - Save! and here you go.


--- AVAILABLE OPTIONS ---------------------------------------------------

Image style
Caption
Link
Transition effect
Transition speed
Timeout
Order
Pager (numbers, thumbnails, or Carousel)
Prev/Next controls
Pause on hover

Integration with Colorbox.



Written by Jerome Danthinne
http://www.grincheux.be
