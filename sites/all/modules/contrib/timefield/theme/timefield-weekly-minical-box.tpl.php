<?php

/**
 * @file
 * Template file for timefield minical box
 *
 * variables available:
 */

?>
<div class="<?php print $classes; ?>">
  <?php if ($label): ?>
    <div class="timefield-minical-label">
        <strong><?php print $label; ?></strong>
    </div>
  <?php endif; ?>
  <div class="timefield-minical-times">
    <?php print $time; ?>
  </div>
</div>
