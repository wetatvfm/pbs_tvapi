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
 * @param $series
 *   An associative array with the title_key of the episode as the key and
 *   the node id as the value.
 *
 * @ingroup themeable
 */

?>

<?php foreach ($episodes as $i => $episode): ?>

<tr class="listblock <?php print $episode['zebra']; ?>">
  <td class="left">
    <p><?php print $episode['start_formatted']; ?></p>
  </td>
  <td class="right halves">
    <p><strong><?php print $episode['title']; ?></strong>  <?php print $episode['prefix']; ?></p>

    <?php if (isset($episode['eptitle']) && !empty($episode['eptitle'])) { ?>
      <p><em><?php print $episode['eptitle']; ?></em></p>
    <?php } ?>
    <p><?php print $episode['description']; ?></p>
    <p><?php print $episode['duration']; ?> minutes</p>
  </td>
</tr>

<?php endforeach; ?>
