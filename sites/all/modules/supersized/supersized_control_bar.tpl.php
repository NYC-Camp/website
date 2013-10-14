<?php
/**
 * @file
 * Template file for control bar.
 *
 * Also see template_preprocess_supersized_control_bar().
 */
?>

<div id="controls-wrapper" class="load-item">
  <div id="controls">

    <?php print $pause_link; ?>

    <!--Slide counter-->
    <div id="slidecounter">
      <span class="slidenumber"></span> / <span class="totalslides"></span>
    </div>

    <!--Slide captions displayed here-->
    <div id="slidecaption"></div>

    <!--Thumb Tray button-->
    <?php print $tray_button_link; ?>

    <!--Navigation-->
    <ul id="slide-list"></ul>

  </div>
</div>
