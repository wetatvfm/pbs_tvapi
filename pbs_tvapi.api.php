<?php

/**
 * Alter the filtered list of episodes.
 *
 * This hook is called after the daily schedule has been assembled into an
 * array and may be used for adding items such as promos to the listings.
 *
 * If the module wishes to act on the rendered HTML of the node rather than the
 * structured content array, it may use this hook to add a #post_render
 * callback.  Alternatively, it could also implement hook_preprocess_node(). See
 * drupal_render() and theme() documentation respectively for details.
 *
 * @param $listings
 *   An array containing the listings from the API call.
 *
 * @ingroup pbs_tvapi_api_hooks
 */
function hook_pbs_tvapi_listings_alter(&$listings) {

}
