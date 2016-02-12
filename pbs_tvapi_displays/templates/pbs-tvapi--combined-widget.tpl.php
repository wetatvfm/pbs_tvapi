<?php

/**
 * @file
 * Theme a combined widget
 *
 * @param
 *   $now: What's On Now content
 *   $tonight: What's On Tonight content
 *
 * @ingroup themeable
 */
?>

<div class="table_wrap table_right_border">
  <h2>What's On Now</h2>
  <?php print $now; ?>
</div>

<div class="table_wrap left_col_table_wrap">
  <h2>What's On Tonight</h2>
  <?php print $tonight; ?>
</div>

<div class="clear"></div>