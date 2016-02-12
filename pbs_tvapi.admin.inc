<?php

/**
 * @file
 * Form functions for settings form for the PBS TV Schedules API.
 */

/**
 * Settings form for PBS TV Schedules API.
 */
function pbs_tvapi_admin_site_settings($form, &$form_state) {
  $form = array();

  $form['pbs_tvapi_settings'] = array(
    '#title' => 'PBS TV Schedules API Settings',
    '#type' => 'fieldset',
  );

  $form['pbs_tvapi_settings']['pbs_tvapi_key'] = array(
    '#title' => 'PBS TV Schedules API Key',
    '#type' => 'textfield',
    '#required' => TRUE,
    '#description' => t('Enter your PBS TV Schedules API key. See the <a href="@documentation">official documentation</a> for instructions on how to request a key.', array('@documentation' => url('https://projects.pbs.org/confluence/display/tvsapi/TV+Schedules+Version+2', array('absolute' => TRUE)))),
    '#default_value' => variable_get('pbs_tvapi_key', ''),
  );

  $form['pbs_tvapi_settings']['pbs_tvapi_callsign'] = array(
    '#title' => 'Callsign',
    '#type' => 'textfield',
    '#required' => TRUE,
    '#description' => 'Your station\'s callsign (e.g., WETA)',
    '#default_value' => variable_get('pbs_tvapi_callsign', ''),
  );
    $form['pbs_tvapi_timeout'] = array(
    '#title' => 'Time out',
    '#type' => 'textfield',
    '#required' => TRUE,
    '#size' => 5,
    '#maxlength' => 3,
    '#description' => 'Number of seconds for the request to wait (default is 15)',
    '#default_value' => variable_get('pbs_schedule_api_timeout', 15),
  );

  return system_settings_form($form);
}

/**
 * Validate the PBS TV Schedules API settings form.
 */
function pbs_tvapi_admin_site_settings_validate($form, &$form_state) {
  $values = $form_state['values'];

  // Make sure the timeout is a number
  if (!is_int((int)$values['pbs_tvapi_timeout'])) {
    form_set_error('pbs_tvapi_timeout', t('Timeout must be an integer between 1-999'));
  }
  elseif ((int)$values['pbs_tvapi_timeout'] < 0 || (int)$values['pbs_tvapi_timeout'] > 999) {
    form_set_error('pbs_tvapi_timeout', t('Timeout must be an integer between 1-999'));
  }

  // Validate the key against PBS's schedule API
  $api_key = $values['pbs_tvapi_key'];
  $callsign = $values['pbs_tvapi_callsign'];

  $response = pbs_tvapi_call2('today', '', $api_key, $callsign);

  if (!$response) {
    form_set_error('pbs_tvapi_settings', t('Failed to connect to the PBS TV Schedules API with those credentials.'));
  }
  else {
    drupal_set_message(t('Successfully connected with the PBS TV Schedules API. Settings have been saved.'));
  }
}


/**
 * Method test form for PBS TV Schedules API.
 */
function pbs_tvapi_admin_tests($form, &$form_state) {

  // get defaults
  $values = $form_state['values'];
  $selectedmethod = $values['method'];
  $selecteddate = $values['date'];
  $selectedprogram = $values['program_id'];
  $selectedshow = $values['show_id'];
  $selectedterms = $values['terms'];

  // build form
  $form = array();

  $form['pbs_tvapi_tests'] = array(
    '#title' => 'Test PBS TV Schedules API Results',
    '#type' => 'fieldset',
  );

  // method options
  $methods = array();
  $methods['today'] = 'What\'s on today';
  $methods['day'] = 'Full listings for a specific day';
  $methods['upcoming/program'] = 'Program information';
  $methods['upcoming/show'] = 'Show information';
  $methods['search'] = 'Listings search';

  // build methods select element
  $form['pbs_tvapi_tests']['method_options'] = array(
    '#type' => 'value',
    '#value' => $methods,
  );

  $form['pbs_tvapi_tests']['method'] = array(
    '#type' => 'select',
    '#title' => t('Method'),
    '#name' => 'method',
    '#options' => $form['pbs_tvapi_tests']['method_options']['#value'],
    '#default_value' => $selectedmethod,
    '#required' => TRUE,
  );

  // only show date element if Full Listings is selected
  $form['pbs_tvapi_tests']['date'] = array(
    '#type' => 'date',
    '#title' => 'Date',
    '#default_value' => $selecteddate,
    '#states' => array(
      'visible' => array(
        ':input[name="method"]' => array('value' => 'day'),
      ),
      'required' => array(
        ':input[name="method"]' => array('value' => 'day'),
      ),
    ),
  );

  // only show program id element if Program Info is selected
  $form['pbs_tvapi_tests']['program_id'] = array(
    '#type' => 'textfield',
    '#title' => 'Program ID',
    '#default_value' => $selectedprogram,
    '#description' => 'A numerical id identifying the program.',
    '#states' => array(
      'visible' => array(
        ':input[name="method"]' => array('value' => 'upcoming/program'),
      ),
      'required' => array(
        ':input[name="method"]' => array('value' => 'upcoming/program'),
      ),
    ),
  );

  // only show show id element if Show Info is selected
  $form['pbs_tvapi_tests']['show_id'] = array(
    '#type' => 'textfield',
    '#title' => 'Show ID',
    '#default_value' => $selectedshow,
    '#description' => 'An id identlfying the show. It must start with "episode_", "movie_" or "onetimeonly_".',
    '#states' => array(
      'visible' => array(
        ':input[name="method"]' => array('value' => 'upcoming/show'),
      ),
      'required' => array(
        ':input[name="method"]' => array('value' => 'upcoming/show'),
      ),
    ),
  );

  // only show search term element if Search is selected
  $form['pbs_tvapi_tests']['terms'] = array(
    '#type' => 'textfield',
    '#title' => 'Search terms',
    '#default_value' => $selectedterms,
    '#description' => 'Search terms must have a minimum of 3 characters. Phrases should be enclosed in single or double quotes. When using a phrase without single/double quotes the AND operator will match results where all terms exist anywhere in the field.',
    '#states' => array(
      'visible' => array(
        ':input[name="method"]' => array('value' => 'search'),
      ),
      'required' => array(
        ':input[name="method"]' => array('value' => 'search'),
      ),
    ),
  );

  // use an AJAX callback to display results without refreshing the page
  $form['submit'] = array(
    '#type' => 'submit',
    '#ajax' => array(
      'callback' => 'pbs_tvapi_admin_test_submit_driven_callback',
      'wrapper' => 'box',
      'name' => 'submit1',
    ),
    '#value' => t('Get response'),
  );

  // results will be displayed here
  $form['box'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="box">',
    '#suffix' => '</div>',
    '#markup' => '',
  );

  return $form;
}

/**
 * Validate the PBS TV Schedules API test form.
 */
function pbs_tvapi_admin_tests_validate($form, &$form_state) {
    $values = $form_state['values'];

    $selectedmethod = $values['method'];
    $selecteddate = $values['date'];
    $selectedprogram = $values['program_id'];
    $selectedshow = $values['show_id'];
    $selectedterms = $values['terms'];

    switch ($selectedmethod) {
      case 'day':
        if (empty($selecteddate)) {
          $pass = FALSE;
          $message = 'Please select a date.';
        }
        break;
      case 'upcoming/program':
        if (empty($selectedprogram)) {
          $pass = FALSE;
          $message = 'Please enter a Program ID.';
        }
        elseif (!is_numeric($selectedprogram)) {
          $pass = FALSE;
          $message = 'The Program ID must be numeric.';
        }
        break;
      case 'upcoming/show':
        if (empty($selectedshow)) {
          $pass = FALSE;
          $message = 'Please enter a Show ID.';
        }
        else {
          $prefix_options = array(
            'episode',
            'movie',
            'onetimeonly'
          );
          $showparts = explode($selectedshow, '_');
          $prefix = $showparts[0];
          if (!in_array($prefix, $prefix_options)) {
            $pass = FALSE;
            $message = 'The Show ID must start with "episode_", "movie_", or "onetimeonly_".';
          }
        }
        break;
      case 'search':
        if (empty($selectedterms)) {
          $pass = FALSE;
          $message = 'Please enter a search term.';
        }
        break;
      default:
        $pass = TRUE;
    }

  if (!$pass) {
    form_set_error('pbs_tvapi_tests', t($message));
  }
}


/**
 * Select the 'box' element, change the markup in it, and return it as a
 * renderable array.
 *
 * @return renderable array (the box element)
 */
function pbs_tvapi_admin_test_submit_driven_callback($form, $form_state) {

  $values = $form_state['values'];
  $method = $values['method'];
  $date = $values['date'];
  $program_id = $values['program_id'];
  $show_id = $values['show_id'];
  $terms = $values['terms'];

  $params = NULL;

  if ($method == 'day' && !empty($date)) {
    // format the date into what the API needs
    $year = $date['year'];
    $month = $date['month'];
    $day = $date['day'];

    if (drupal_strlen($month) < 2) {
      $month = '0' . $month;
    }

    if (drupal_strlen($day) < 2) {
      $day = '0' . $day;
    }

    // set parameter
    $params = $year . $month . $day;
  }

  if ($method == 'upcoming/program' && !empty($program_id)) {
    $params = $program_id;
  }

  if ($method == 'upcoming/show' && !empty($show_id)) {
    $params = $show_id;
  }

  if ($method == 'search' && !empty($terms)) {
    $params = $terms;
  }

  // call the API
  $output = pbs_tvapi_call2($method, $params);

  // alter the form to display the results
  $element = $form['box'];
  $element['#markup'] = '<pre>' . print_r($output, 1) . '</pre>';

  return $element;
}
