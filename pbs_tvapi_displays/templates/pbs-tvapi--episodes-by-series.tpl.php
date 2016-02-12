<?php

/**
 * @file
 * Theme tv episodes for a single channel display of the schedule grid.
 *
 * @param $episodes
 *   An associative array by delta containing:
 *   - title
 *   - eptitle
 *   - duration
 *   - starttime
 *   - endtime
 *   - program_id
 *   - show_id
 *   - title_key
 *   - promo_id
 *   - youtube_id
 *   - promo_thumbnail
 *   - description
 *   - episode_description
 *   - special_warnings
 *   - channel
 *   - width
 *   - start_formatted
 *   - end_formatted
 *   - start_formatted_details
 *   - detail_id
 *   - startnote
 *   - zebra
 *
 * @ingroup themeable
 */

?>

<?php foreach ($episodes as $i => $episode): ?>

<tr class="listblock <?php print $episode['truncate_class']; ?>">
<td class="left-twoeight"><?php print $episode['logo']; ?></td>
<td class="left"><p><?php print $episode['date_formatted']; ?><br />
  <?php print $episode['time_formatted']; ?><br />
  (<?php print $episode['minutes']; ?> minutes)</p></td>

<td class="right halves"><p><strong><?php print $episode['episode_title']; ?>&nbsp;&nbsp;</strong><?php print $episode['prefix']; ?></p>
      <?php
      if (isset($episode['episode_description'])) {
        print '<p>' . $episode['episode_description'] . '</p>';
      }
      ?>
</td>
</tr>

<?php endforeach; ?>
