<?php
/**
 * @file
 * Theme functions for the PBS TV API Displays module
 *
 */



 /**
 * Implements hook_theme().
 */
function pbs_tvapi_displays_theme() {
  return array(
    //main schedule page
    'schedule_grid' => array(
      'variables' => array('variables' => NULL),
    ),
    // episodes within main schedule page
    'episodes' => array(
      'render element' => 'episodes',
      'template' => 'templates/pbs-tvapi--episodes',
    ),
    // episode details in schedule page modal window
    'episodes_details' => array(
      'render element' => 'episodes',
      'template' => 'templates/pbs-tvapi--episodes-details',
    ),
    // schedule grid for a single channel
    'single_channel_grid' => array(
      'variables' => array('variables' => NULL),
    ),
    // episodes within the single channel grid
    'episodes_single_channel' => array(
      'render element' => 'episodes',
      'template' => 'templates/pbs-tvapi--episodes-single-channel',
    ),
    // series page
    'episode_grid' => array(
      'variables' => array('variables' => NULL),
    ),
    // episodes by series
    'episodes_by_series' => array(
      'render element' => 'episodes',
      'template' => 'templates/pbs-tvapi--episodes-by-series',
    ),

    'widget_list' => array(
      'variables' => array('episodes' => NULL, 'fullsched' => TRUE),
      'template' => 'templates/pbs-tvapi--widget-list',
    ),

    'widget_list_kids' => array(
      'variables' => array('episodes' => NULL, 'fullsched' => TRUE, 'note' => NULL),
      'template' => 'templates/pbs-tvapi--widget-list-kids',
    ),

    'combined_widget' => array(
      'variables' => array('now' => NULL, 'tonight' => NULL),
      'template' => 'templates/pbs-tvapi--combined-widget',

    ),
    // what's on now link for the subnav (formerly a dropdown)
    'schedule_dropdown' => array(
      'variables' => array('vars' => NULL, 'date' => NULL, 'time' => NULL),
    ),
    // deprecated -- see theme_deprecated.inc
    'schedule_flyout' => array(
      'variables' => array('vars' => NULL, 'date' => NULL, 'time' => NULL),
    ),



  );
}

/**
 * Allow other modules and themes to affect the episodes on the
 * schedule grid
 */
function template_preprocess_episodes(&$vars) {
}


/**
 * Allow other modules and themes to affect the episode details on the
 * schedule grid
 */
function template_preprocess_episodes_details(&$vars) {

  foreach ($vars['episodes'] as &$episode) {
    // add a prefix for other modules to use
    $episode['prefix'] = NULL;

    // show the episode description instead of the series description,
    // if available
    if (isset($episode['episode_description']) && !empty($episode['episode_description'])) {
      $episode['description'] = $episode['episode_description'];
    }

    // get the series node id for the more info link
    $title_key = $episode['title_key'];
    if (!empty($title_key) && isset($vars['series'][$title_key])) {
      $episode['series'] = $vars['series'][$title_key];
    }
  }
}


/**
 * Returns HTML for tv episodes in series grids.
 *
 * @param $variables
 *   An associative array by delta containing episode information
 *
 * @ingroup themeable
 */
function theme_episode_grid($variables) {

  $episodes_info = array(
    'episodes' => $variables['episodes'],
    'initial_display' => $variables['initial_display']
  );

  $output = '<table class="episodes">';
  $output .= theme('episodes_by_series', $episodes_info);

  $output .= '</table>';
  $output .= '<div class="clear"></div>';

  return $output;
}


/**
 * Allow other modules and themes to affect the episodes for the
 * upcoming listings
 */
function template_preprocess_episodes_by_series(&$vars) {
  // how many episodes should be shown on load
  $show = $vars['initial_display'];

  foreach ($vars['episodes'] as $i => &$episode) {
    // add a prefix for other modules to use
    $episode['prefix'] = NULL;

    // add the logos for each channel
    $channel = $episode['feed']['short_name'];
    switch ($channel) {
      case 'WETADT4':
        $episode['logo'] = '<img src="' . base_path() . drupal_get_path('theme', $GLOBALS['theme']) . '/templates/images/schedule_logo_tv26.png" alt="WETA TV 26 Logo" title="WETA TV26">';
        break;
      case 'WETADT':
        $episode['logo'] = '<img src="' . base_path() . drupal_get_path('theme', $GLOBALS['theme']) . '/templates/images/schedule_logo_wetahd.png" alt="WETA HD Logo" title="WETA HD">';
        break;
      case 'WETADT2':
        $episode['logo'] = '<img src="' . base_path() . drupal_get_path('theme', $GLOBALS['theme']) . '/templates/images/schedule_logo_wetauk.jpg" alt="WETA UK Logo" title="WETA UK">';
        break;
      case 'WETADT3':
        $episode['logo'] = '<img src="' . base_path() . drupal_get_path('theme', $GLOBALS['theme']) . '/templates/images/schedule_logo_wetakids.png" alt="WETA Kids Logo" title="WETA Kids">';
        break;
      default:
        $episode['logo'] = '';
    }

    // add "more" class if there are more episodes than should be visible
    $episode['truncate_class'] = '';
    if ($i >= $show) {
      $episode['truncate_class'] = ' more';
    }
  }
}

/**
 * Returns HTML for schedule grid.
 *
 * @param $variables
 *   An associative array by delta containing channel information
 *
 * @ingroup themeable
 */
function theme_schedule_grid($vars) {

  $dates = $vars['dates'];
  $times = $vars['times'];
  $listings = $vars['listings'];


  $output = '<div class="container schedule">';
  $output .= '<div class="slider-wrapper">';

  $output .= '<div class="today-date">';

  $output .= l(t(''), 'schedule/' . $dates['prev'] . '/' . $times['start'], array('attributes' => array('class' => array('prev'))));
  $output .= '<div class="dt">' . $dates['day'] . ' &bull; ' . $dates['menu_date'] . '</div>';
  $output .= l(t(''), 'schedule/' . $dates['next'] . '/' . $times['start'], array('attributes' => array('class' => array('next'))));
  $output .= '</div>';

  $output .= '<div class="scroll-bar-wrap">';
  $output .= '<div class="scroll-bar"></div>';
  $output .= '</div>';

  $output .= '<div class="clear"></div>';
  $output .= '</div>';
  $output .= '<div class="grid-wrapper scroll-pane">';


  $output .= '<div class="stations">';
  $output .= '<div class="format"><img src="' . base_path() . drupal_get_path('theme', $GLOBALS['theme']) . '/templates/images/tv.jpg" alt="" /> TELEVISION</div>';

  $no_data = '<div class="span_12 p30">';
  $no_data_count = 0;


  foreach ($listings as $i => $channel) {
    if (!empty($channel['episodes'])) {
      $output .= '<div class="station">' . $channel['full_name'] . '</div>';
    }
    else {
      $no_data .= '<p>We currently do not have schedule information for ' . $channel['full_name'] . '.</p>';
      $no_data_count++;
    }
  }
  $no_data .= '</div>';

  $output .= '</div>';
  $output .= '<div class="grid scroll-content">';

  $output .= theme_item_list(array('items' => $times['segments'], 'title' => NULL,  'type' => 'ul', 'attributes' => array('class' => 'schd-head')));

  foreach ($listings as $i => $channel) {
    $channel_names = array(
      'short_name' => $channel['short_name'],
      'full_name' => $channel['full_name'],
    );
    if (!empty($channel['episodes'])) {
      $episodes = $channel['episodes'];
      $variables = array(
        'episodes' => $episodes,
        'series' => $vars['series'],
      );


      $output .= '<div class="show-mobile-schd-head">';
      $output .= '<span class="show-mobile-schd"><img src="' . base_path() . drupal_get_path('theme', $GLOBALS['theme']) . '/templates/images/now_playing.png" alt=""></span>';
      $output .= $channel['full_name'];
      $output .= '</div>';
      $output .= '<ul>';

      $output .= theme('episodes', $variables);
      $output .= theme('episodes_details', $variables);
      $output .= '</ul>';
    }
  }
  $output .= '</div>';

  $output .= '</div>';
  if ($no_data_count > 0) {
    $output .= $no_data;
  }

  $output .= '</div>';

  return $output;

}

/**
 * Display the schedule listing for a single channel
 */
function theme_single_channel_grid($variables) {

  $episodes_info = array(
    'episodes' => $variables['episodes'],
    'series' => $variables['series'],
  );


  $output = '<div class="container">';
  $output .= '<div class="span_12 col p0-60">';
  $output .= '<h2>' . $variables['channel'] . '</h2>';
  $output .= '<table class="episodes">';

  $output .= theme('episodes_single_channel', $episodes_info);

  $output .= '</table>';
  $output .= '<div class="episodes-bottom p10"></div>';
  $output .= '</div>';
  $output .= '</div>';

  return $output;
}

/**
 * Allow other modules and themes to affect the episodes on the
 * schedule grid
 */
function template_preprocess_episodes_single_channel(&$vars) {

  foreach ($vars['episodes'] as $i => &$episode) {
    // add a prefix for other modules to use
    $episode['prefix'] = NULL;

    // show the episode description instead of the series description,
    // if available
    if (isset($episode['episode_description']) && !empty($episode['episode_description'])) {
      $episode['description'] = $episode['episode_description'];
    }

    // If there's a connected series node, link the title to it
    $title_key = $episode['title_key'];
    if (!empty($title_key) && isset($vars['series'][$title_key])) {
      $episode['title'] = l($episode['title'], 'node/' . $vars['series'][$title_key], array('html' => TRUE));
    }

    // set up zebra striping

    $episode['zebra'] = 'even';
    if ($i % 2 == 0) {
      $episode['zebra'] = 'odd';
    }

  }


}

/**
 * Returns HTML for schedule dropdown in subnav.
 *
 * @param $variables
 *   An associative array by delta containing channel information
 *
 * @ingroup themeable
 */
function theme_schedule_dropdown($vars) {
/* REMOVED CURRENT SCHEDULE INFO FOR PERFORMANCE REASONS
  $output = '<ul class="radio">';
  $output .= '<li><a href="#" id="nowplay">What\'s On Now</a>';
  $output .= '<div id="np_flyout">';
  $output .= '<ul>';
  foreach ($vars['vars'] as $i => $channel) {
    $output .= '<li>' . $channel['episode']['feed_common_name'] . '<br />';
    $output .= l($channel['episode']['tg_title'], 'node/' . $channel['episode']['nid']);
    $output .= '</li>';
  }
  $output .= '</ul>';
  $output .= '</div>';
  $output .= '</li>';
  $output .= '</ul>';
 */
  $output = '<ul class="radio">';
  $output .= '<li><a href="/schedule">What\'s On Now</a></li>';
  $output .= '</ul>';
  return $output;
}
