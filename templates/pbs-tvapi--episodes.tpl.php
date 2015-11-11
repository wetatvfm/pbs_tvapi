<?php

/**
 * @file
 * Theme tv episodes for the schedule grid.
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
 *
 * width = (duration * 4) - 1
 *  120px = 30 minutes and subtract 1px for the border.
 *  for example:
 *  - 0.5 hr = 119px
 *  - 1 hr = 239px
 *  - 1.5 hr = 179px
 *  - etc.
 *
 * @param $series
 *   An associative array with the title_key of the episode as the key and
 *   the node id as the value.
 *
 * @ingroup themeable
 */

?>

<?php
foreach ($episodes as $i => $episode) {

  $title = '<span class="title">' . $episode['title'] . '</span>';
  $eptitle = '<span class="episode">' . $episode['eptitle'] . '</span>';

?>
  <li style="width: <?php print $episode['width']; ?>px">
    <span class="show-mobile-schd"><?php print $episode['start_formatted']; ?>  &mdash; <?php print $episode['end_formatted']; ?></span>

    <?php print l($title, '', array('html' => TRUE, 'attributes' => array('class' => array('sched_detail hide-mobile')), 'fragment' => $episode['detail_id'], 'external' => TRUE)); ?>

    <?php
    // get the node id from the series array and use it to construct the link to the program page on mobile
    if (isset($episode['title_key'])) {
      print l($title, 'node/' . $series[$episode['title_key']], array('html' => TRUE, 'attributes' => array('class' => array('show-mobile'))));
    }
    else {
    ?>
      <span class="show-mobile"><?php print $title; ?></span>
    <?php } ?>

    <?php print $eptitle; ?>

    <?php if ($episode['startnote']) { ?>
      <span class="startnote">(Starts at <?php print $episode['start_formatted']; ?>)</span>
     <?php } ?>
  </li>

<?php
}
?>
