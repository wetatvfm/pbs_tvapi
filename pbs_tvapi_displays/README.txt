PBS TV Schedule API Displays
================

== Introduction ==
A Drupal 7 module that provides displays for the PBS TV Schedule API.

== Installation ==
Install as any other module.

It expects a content type with the machine name 'tv_series' which stores non-ephemeral information about individual programs at the series (not episode) level.  This information can be populated by the pbs_tvapi_series module, but this is not required.

== Configuration ==
This module provides the following displays of TV schedule data:

** Pages
* Daily schedule grid for all channels
* Daily schedule grid for a single channel

** Blocks
* What's On Now: TV 26
* What's On Now: Kids
* What's On Now and Tonight: TV 26
* What's On Now: TV 26 for Kids
* What's On Now and Tonight: HD
* What's On Now and Tonight: UK
* What's On Now and Tonight: Kids
* What's On Now Grid
* What's On Now Subnav
* What's On Now Kids Subnav
* Upcoming Episodes by Series
