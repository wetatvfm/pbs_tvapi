<?php
/**
 * @file
 * Block functions for the PBS TV API Displays module
 *
 */

/**
 * Implements hook_block_info().
 *
 * This hook declares what blocks are provided by the module.
 */
function pbs_tvapi_displays_block_info() {
  // This hook returns an array, each component of which is an array of block
  // information. The array keys are the 'delta' values used in other block
  // hooks.
  $blocks['on_now_26'] = array(
    // info: The name of the block.
    'info' => t('TV Schedule: What\'s On Now: TV 26'),
  );
  $blocks['on_now_kids'] = array(
    // info: The name of the block.
    'info' => t('TV Schedule: What\'s On Now: Kids'),
  );
  $blocks['on_now_tonight_26'] = array(
    'info' => t('TV Schedule: What\'s On Now and Tonight: TV 26'),
  );
  $blocks['on_now_kids_26'] = array(
    // info: The name of the block.
    'info' => t('TV Schedule: What\'s On Now: TV 26 for Kids'),
  );
  $blocks['on_now_tonight_HD'] = array(
    'info' => t('TV Schedule: What\'s On Now and Tonight: HD'),
  );
  $blocks['on_now_tonight_UK'] = array(
    'info' => t('TV Schedule: What\'s On Now and Tonight: UK'),
  );
  $blocks['on_now_tonight_kids'] = array(
    'info' => t('TV Schedule: What\'s On Now and Tonight: Kids'),
  );
  $blocks['on_now_grid'] = array(
    'info' => t('TV Schedule: What\'s On Now Grid'),
  );
  $blocks['on_now_dropdown'] = array(
    'info' => t('TV Schedule: What\'s On Now Subnav'),
  );
  $blocks['on_now_kids_dropdown'] = array(
    'info' => t('TV Schedule: What\'s On Now Kids Subnav'),
  );
  $blocks['upcoming_byseries'] = array(
    'info' => t('TV Schedule: Upcoming Episodes by Series'),
  );
  $blocks['upcoming_noresults'] = array(
    'info' => t('TV Schedule: No upcoming episodes message'),
  );
  $blocks['schedule_form'] = array(
    'info' => t('TV Schedule: Daily Schedule Form'),
  );
  return $blocks;
}

/**
 * Implements hook_block_view().
 *
 * This hook generates the contents of the blocks themselves.
 */
function pbs_tvapi_displays_block_view($delta = '') {
  $block = array();
  //The $delta parameter tells us which block is being requested.
  switch ($delta) {
    case 'on_now_26':
      $block['subject'] = t('What\'s On Now: TV 26');
      $block['content'] = pbs_tvapi_displays_blockcontents($delta);
      break;
    case 'on_now_kids':
      $block['subject'] = t('What\'s On Now: Kids');
      $block['content'] = pbs_tvapi_displays_blockcontents($delta);
      break;
    case 'on_now_kids_26':
      $block['subject'] = t('What\'s On Now: TV 26 for Kids');
      $block['content'] = pbs_tvapi_displays_blockcontents($delta);
      break;
    case 'on_now_tonight_26':
      $block['subject'] = t('What\'s On Now and Tonight: TV 26');
      $block['content'] = pbs_tvapi_displays_blockcontents($delta);
      break;
    case 'on_now_tonight_HD':
      $block['subject'] = t('What\'s On Now and Tonight: HD');
      $block['content'] = pbs_tvapi_displays_blockcontents($delta);
      break;
    case 'on_now_tonight_UK':
      $block['subject'] = t('What\'s On Now and Tonight: UK');
      $block['content'] = pbs_tvapi_displays_blockcontents($delta);
      break;
    case 'on_now_tonight_kids':
      $block['subject'] = t('What\'s On Now and Tonight: Kids');
      $block['content'] = pbs_tvapi_displays_blockcontents($delta);
      break;
    case 'on_now_grid':
      $block['subject'] = t('What\'s On Now Grid');
      $block['content'] = pbs_tvapi_displays_blockcontents($delta);
      break;
    case 'on_now_dropdown':
      $block['content'] = pbs_tvapi_displays_blockcontents($delta);
      break;
    case 'on_now_kids_dropdown':
      $block['content'] = pbs_tvapi_displays_blockcontents($delta);
      break;
    case 'upcoming_byseries':
      $block['subject'] = t('Upcoming Episodes');
      $block['content'] = pbs_tvapi_displays_blockcontents($delta);
      break;
    case 'upcoming_noresults':
      $block['content'] = pbs_tvapi_displays_blockcontents($delta);
      break;
    case 'schedule_form':
      $form = drupal_get_form('pbs_tvapi_displays_dailyschedule_form');
      $block['content'] = render($form);
      break;
  }
  return $block;
}

/**
 * A module-defined block content function.
 */
function pbs_tvapi_displays_blockcontents($which_block) {
  switch ($which_block) {
    case 'on_now_26':
      $channel = 'WETADT4';
      $output = pbs_tvapi_displays_onnow($channel);
      return $output;
    case 'on_now_kids':
      $channel = 'WETADT3';
      $output = pbs_tvapi_displays_onnow_kids($channel);
      return $output;
    case 'on_now_kids_26':
      $channel = 'WETADT4';
      $output = pbs_tvapi_displays_onnow_kids($channel);
      return $output;
    case 'on_now_tonight_26':
      $channel = 'WETADT4';
      $now = pbs_tvapi_displays_onnow($channel);
      $tonight = pbs_tvapi_displays_ontonight($channel, FALSE);
      $output = theme('combined_widget', array('now' => $now, 'tonight' => $tonight));
      return $output;
    case 'on_now_tonight_HD':
      $channel = 'WETADT';
      $now = pbs_tvapi_displays_onnow($channel);
      $tonight = pbs_tvapi_displays_ontonight($channel, FALSE);
      $output = theme('combined_widget', array('now' => $now, 'tonight' => $tonight));
      return $output;
    case 'on_now_tonight_UK':
      $channel = 'WETADT2';
      $now = pbs_tvapi_displays_onnow($channel);
      $tonight = pbs_tvapi_displays_ontonight($channel, FALSE);
      $output = theme('combined_widget', array('now' => $now, 'tonight' => $tonight));
      return $output;
    case 'on_now_tonight_kids':
      $channel = 'WETADT3';
      $now = pbs_tvapi_displays_onnow($channel);
      $tonight = pbs_tvapi_displays_ontonight($channel, FALSE);
      $output = theme('combined_widget', array('now' => $now, 'tonight' => $tonight));
      return $output;
    case 'on_now_grid':
      $output = pbs_tvapi_displays_on_now_grid();
      return $output;
    case 'on_now_dropdown':
      $channels = array(
        'WETADT4',
        'WETADT',
        'WETADT2',
        'WETADT3',
      );
      $output = pbs_tvapi_displays_on_now_dropdown($channels);
      return $output;
    case 'on_now_kids_dropdown':
      $channels = array(
        'WETADT3',
        'WETADT4',
      );
      $output = pbs_tvapi_displays_on_now_dropdown($channels);
      return $output;
    case 'upcoming_byseries':
      $node = arg(1);
      $output = pbs_tvapi_displays_upcomingbyseries($node);
      return $output;
    case 'upcoming_noresults':
      $message = variable_get('upcoming_noresults_message', NULL);
      $message = check_markup($message['value'], $message['format'], '', TRUE);
      return $message;
  }
}

/**
 * Implements hook_block_configure().
 *
 * This hook declares configuration options for blocks provided by this module.
 */
function pbs_tvapi_displays_block_configure($delta = '') {
  // The $delta parameter tells us which block is being configured.
  // In this example, we'll allow the administrator to customize
  // the text of the 'configurable text string' block defined in this module.

  $form = array();
  if ($delta == 'upcoming_noresults') {
    // All we need to provide is the specific configuration options for our
    // block. Drupal will take care of the standard block configuration options
    // (block title, page visibility, etc.) and the save button.
    $form['upcoming_noresults_message'] = array(
      '#type' => 'text_format',
      '#title' => t('Error message'),
      '#size' => 60,
      '#description' => t('This text will appear on a TV Series page if there are no upcoming episodes.'),
      '#default_value' => variable_get('upcoming_noresults_message',  t('There are no upcoming broadcasts of this program in the next two weeks. Check back soon!')),
    );
  }
  return $form;
}

/**
 * Implements hook_block_save().
 *
 * This hook declares how the configured options for a block
 * provided by this module are saved.
 */
function pbs_tvapi_displays_block_save($delta = '', $edit = array()) {
  // We need to save settings from the configuration form.
  // We need to check $delta to make sure we are saving the right block.
  if ($delta == 'upcoming_noresults') {
    // Have Drupal save the string to the database.
    variable_set('upcoming_noresults_message', $edit['upcoming_noresults_message']);
  }
  return;
}
