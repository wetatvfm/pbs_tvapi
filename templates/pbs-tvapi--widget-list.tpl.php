<?php

/**
 * @file
 * Theme a widget list
 *
 * @param $variables
 *   An associative array by delta containing:
 *   - episodes
 *     - title : Program title
 *     - eptitle: Episode title (if it exists)
 *     - starttime: Program start time
 *   - fullsched: Boolean value. If true, link to Full Schedule will display
 *
 * @ingroup themeable
 */
?>

<table class="whats_on">
  <?php foreach ($variables['episodes'] as $i => $episode): ?>
   <tr>
    <th><?php print $episode['starttime'];?></th>
      <td><?php print $episode['title']; ?>
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