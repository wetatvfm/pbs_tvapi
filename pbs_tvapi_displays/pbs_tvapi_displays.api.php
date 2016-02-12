<?php

/**
 * @file
 * Hooks provided by the PBS TV Schedule API Displays module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Alter the filtered list of episodes for daily methods.
 *
 * This hook is called after the daily schedule has been assembled into an
 * array and may be used for adding items such as promos to the listings.
 *
 * @param $listings
 *   An array containing the listings from the API call.
 *
 * @ingroup pbs_tvapi_displays_api_hooks
 */
function hook_pbs_tvapi_displays_daily_listings_alter(&$listings) {

}


/**
 * Alter the filtered list of episodes for upcoming methods.
 *
 * This hook is called after the upcoming episodes listing has been assembled
 * into an array and may be used for adding items such as promos to the
 * listings.
 *
 * @param $listings
 *   An array containing the listings from the API call.
 *
 * @ingroup pbs_tvapi_displays_api_hooks
 */
function hook_pbs_tvapi_displays_upcoming_listings_alter(&$listings) {

}
