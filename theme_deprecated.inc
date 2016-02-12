<?php
/**
 * @file
 * Deprecated theme functions, stored here for archival purposes.
 *
 */

/**
 * Returns HTML for tv episodes in the nav flyout.
 *
 * @param $variables
 *   An associative array by delta containing:
 *   - title : Program title
 *   - eptitle: Episode title (if it exists)
 *   - duration: Duration of the program
 *   - promo: YouTube promo
 *   - starttime: Program start time
 *   - endtime: Program end time
 *
 * width = (duration * 4) - 1
 *  120px = 30 minutes and subtract 1px for the border.
 *  for example:
 *  - 0.5 hr = 119px
 *  - 1 hr = 239px
 *  - 1.5 hr = 179px
 *  - etc.
 *
 * @ingroup themeable
 */
function theme_episodes_flyout($vars, $date, $time, $series) {
  $gridstart = $time;
  $fullstart = strtotime($date . ', ' . $gridstart . ':00');
  $fullend = $fullstart + (24 * 60 * 60);

  $count = 1;

  $output = '';
  $totaleps = count($vars);
  foreach ($vars as $i => $episode) {
      $width = ($episode['duration'] * 4) - 1;
      $thisstart = date('H', strtotime($episode['starttime']));
      $minutes = date('i', strtotime($episode['starttime']));
      if ($count == 1) {
        if ($thisstart == $gridstart && $minutes > 0) {
          $padwidth = (((($thisstart - $gridstart) * 60) + $minutes) * 4) - 1;
          $output .= '<li style="width: ' . $padwidth . '">' . $padwidth . '</li>';
        }
        elseif ($thisstart < $gridstart) {
          $endtime = strtotime($episode['endtime']);
          $width = ((($endtime - $fullstart) / 60) * 4) - 1;
        }
      }
      elseif ($count == $totaleps) {
        $starttime = strtotime($episode['starttime']);
        $width = ((($fullend - $starttime) / 60) * 4) - 1;
      }

      $epstart = strtotime($episode['starttime']);
      $epend = strtotime($episode['endtime']);
      $program = $episode['program_id'];
      $feed = $episode['feed_id'];
      $tid = $episode['title_id'];


      $start = date('g:i A', strtotime($episode['starttime']));
      $end = date('g:i A', strtotime($episode['endtime']));
      $title = '<span class="title">' . check_plain($episode['title']) . '</span>';
      $eptitle = '<span class="episode">' . check_plain($episode['eptitle']) . '</span>';
      $minute = date('i', $epstart);
      if ($minute != '00' && $minute != '30') {
        $startnote = '<span class="startnote">(Starts at ' . date('g:i a', $epstart) . ')</startnote>';
      }

      if (isset($series[$tid])) {
        $link = 'node/' . $series[$tid];
        $display_title = l($title, $link, array('html' => TRUE));
      }
      else {
        $display_title = $title;
      }


      $output .= '<li style="width: ' . $width . 'px">';
      $output .= '<span class="show-mobile-schd">' . $start . ' &mdash; ' . $end . '</span>';
      $output .= $display_title;
      $output .= $eptitle;
      if (isset($startnote)) {
        $output .= $startnote;
      }
      $output .= '</li>';

      $count++;
      unset($startnote);

  }
  return $output;
}

/**
 * Returns HTML for schedule grid in nav flyout.
 *
 * @param $variables
 *   An associative array by delta containing channel information
 *
 * @ingroup themeable
 */
function theme_schedule_flyout($vars, $series) {

  // Begin setup
  $day = date('D', strtotime($vars['date']));
  $date = date('M j', strtotime($vars['date']));

  $seemore = '<img src="' . base_path() . drupal_get_path('theme', $GLOBALS['theme']) . '/templates/images/go-see-more.gif" alt="Full schedule button" /><br />View Full Schedule';

  // Get what's currently playing on FM for later display.  Need to call the view twice because otherwise it gets confused.
  $cwview = views_get_view('now_playing');
  $vlvview = views_get_view('now_playing');
  $cwargs[] = '1';
  $vlvargs[] = '2';
  $display_id = 'block_3';
  $cw_nowplaying = $cwview->execute_display($display_id, $cwargs);
  $vlv_nowplaying = $vlvview->execute_display($display_id, $vlvargs);


  // set up time options
  $timesegments = array();
  $after = array();
  $before = array();

  $start = $vars['time'];

  // build time headers
  foreach (range(0, 23) as $fullhour) {
    $parthour = $fullhour > 12 ? $fullhour - 12 : $fullhour;
    if ($parthour == 0) {
      $parthour = 12;
    }
    $halfhour = $parthour . ':30';
    $parthour = $parthour . ':00';

    $parthour .= $fullhour > 11 ? ' PM' : ' AM';
    $halfhour .= $fullhour > 11 ? ' PM' : ' AM';
    if ($fullhour < $start) {
      //need to move these hours to the end
      $after[$fullhour] = $parthour;
      $after[$fullhour . '.5'] = $halfhour;
    }
    else {
      $before[$fullhour] = $parthour;
      $before[$fullhour . '.5'] = $halfhour;
    }
  }
  // put the list back together
  $timesegments = $before += $after;

  // limit to 7 blocks
  $timesegments = array_slice($timesegments, 0, 7);
  // end setup

  // Begin output
  $output = '<div class="subnav" id="schedule_nav_sub">';
  $output .= '<div class="subnav-home-inner">';
  $output .= '<div class="grid-wrapper nav-grid">';
  $output .= '<div class="seemore">';
  $output .= '<div class="seemore-top"></div>';
  $output .= l($seemore, 'schedule', array('html' => TRUE));
  $output .= '</div>'; //end seemore

  $output .= '<div class="stations">';
  $output .= '<div class="format"><img src="' . base_path() . drupal_get_path('theme', $GLOBALS['theme']) . '/templates/images/tv.jpg" alt="" /> TELEVISION</div>';

  foreach ($vars['vars'] as $i => $channel) {
    $output .= '<div class="station">' . $channel['feed_common_name'] . '</div>';
  }
  $output .= '<div class="format format-nav"><img src="' . base_path() . drupal_get_path('theme', $GLOBALS['theme']) . '/templates/images/notes.jpg" alt="" /> RADIO</div>';


  $output .= '</div>'; // end stations


  $output .= '<div class="grid scroll-content">';

  $output .= theme_item_list(array('items' => $timesegments, 'title' => NULL,  'type' => 'ul', 'attributes' => array('class' => 'schd-head')));

  foreach ($vars['vars'] as $i => $channel) {
    $episodes = $channel['episodes'];
    $output .= '<div class="show-mobile-schd-head">';
    $output .= '<span class="show-mobile-schd"><img src="' . base_path() . drupal_get_path('theme', $GLOBALS['theme']) . '/templates/images/now_playing.png" alt=""></span>';
    $output .= $channel['feed_common_name'];
    $output .= '</div>';
    $output .= '<ul>';
    $output .= theme_episodes_flyout($episodes['variables'], $episodes['date'], $episodes['time'], $series);
    $output .= '</ul>';
  }
  // end tv schedule

  $output .= '<ul class="schd-head full-width-row">';
  $output .= '<li>CLASSICAL WETA  <a href="#">' . $cw_nowplaying['content'] . '</a></li>';
  $output .= '<li class="border-left">VIVALAVOCE  <a href="#">' . $vlv_nowplaying['content'] . '</a></li>';
  $output .= '</ul>';
  // end fm listings

  $output .= '</div>'; // end grid scroll-content

  $output .= '</div>'; // end grid-wrapper nav-grid
  $output .= '</div>'; // end subnav-home-inner
  $output .= '</div>'; // end subnav

  return $output;
}



