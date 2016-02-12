<?php

/**
 * @file
 * Theme tv episode details for modal popups.
 *
 * @param $episodes
 *   An associative array by delta containing:
 *   - prefix
 *   - detail_id
 *   - starttime
 *   - startstamp
 *   - endstamp
 *   - duration
 *   - eptitle
 *   - full_title
 *   - description
 *   - series
 *   - channel
 *
 * @ingroup themeable
 */
?>

<div style="display: none;">
  <?php foreach ($episodes as $i => $episode): ?>
    <div id="<?php print $episode['detail_id']?>">
      <div class="show-desc">
        <div class="mfp-close">X CLOSE&nbsp;</div>
        <div class="content">
          <?php if ($episode['prefix']): print $episode['prefix']; endif; ?>
          <?php if ($episode['title']): ?>
             <div class="episode_title"><?php print $episode['title']; ?></div>
          <?php  endif; ?>
          <?php if ($episode['eptitle']):?>
            <div class="show_title"><?php print $episode['eptitle']; ?></div>
          <?php endif; ?>

          <p><?php if ($episode['start_formatted_details']): print $episode['start_formatted_details']; endif; ?><?php if ($episode['channel']): ?> on <?php print $episode['channel']; endif;?>
            <br />
            <?php if ($episode['duration']): ?>
              (<?php print $episode['duration']; ?> minutes)<?php endif; ?>
          </p>

          <?php if ($episode['description']): ?> <p><?php print $episode['description']; ?></p><?php endif; ?>

          <?php if (!empty($episode['series'])): ?>
            <p><?php print l(t('More Info &rarr;'), 'node/' . $episode['series'], array('html' => TRUE)); ?></p>
          <?php endif; ?>
        </div>
      </div>
    </div>
  <?php endforeach; ?>
</div>
