PBS TV Schedule API Promos Module
================

== Introduction ==
A Drupal 7 module that supplements the PBS TV Schedule API module, adding integration with YouTube and COVE to display promotional videos.

== Installation ==
Install as any other module.

For displaying the promos, the module presupposes the Magnific Popup jQuery plugin. http://dimsemenov.com/plugins/magnific-popup/

== Configuration ==
This module expects a content type with the machine name 'youtube_promos' that contains the following fields:

* Series:  A reference to a node of the TV Series type, which provides the
  program or show id of a program.
* Episode ID: The episode id of the specific episode the program is for.  If
  this is a program without individual episodes, the show id is used instead.
* Promo type: A select list with the options youtube or cove.
* COVE ID: The video id for the selected COVE video.
* YouTube ID: The video id for the selected YouTube video.

The module creates an Episode Finder widget block to help determine the specific episode ids.  This should be configured to display on the node add/edit page for the promos content type.
