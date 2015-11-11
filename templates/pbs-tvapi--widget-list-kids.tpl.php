<?php

/**
 * @file
 * Theme a widget list for kids pages
 *
 * @param $variables
 *   An associative array by delta containing:
 *   - episodes
 *     - title : Program title
 *     - eptitle: Episode title (if it exists)
 *     - starttime: Program start time
 *     - kids_image: Image associated with kids program
 *   - fullsched: Boolean value. If true, link to Full Schedule will display
 *   - note: Explanatory note about schedule on TV26
 *
 * @ingroup themeable
 */
?>

<table class="whats_on">
  <?php if (isset($variables['note'])) : ?>
  <tr>
    <td colspan="2"><?php print $variables['note']?></td>
  </tr>
  <?php endif; ?>

  <?php foreach ($variables['episodes'] as $i => $episode): ?>
   <tr>
    <th><?php print $episode['starttime'];?></th>
      <td>
        <?php
        if (isset($episode['kids_image'])) {
          print $episode['kids_image'];
        }
        ?>
        <?php print $episode['title']; ?>
        <?php if (isset($episode['eptitle'])):?>
        <br /><?php print $episode['eptitle'];
        endif; ?>
      </td>
   </tr>
  <?php endforeach; ?>

  <?php if ($variables['fullsched']): ?>
    <tr>
      <td colspan="2"><?php print l(t('See Full Schedule'), 'schedule', array('attributes' => array('class' => array('arrow_link'))))?>
      </td>
    </tr>
  <?php endif; ?>
</table>