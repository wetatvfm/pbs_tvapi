PBS TV Schedule API Series
================

== Introduction ==
A Drupal 7 module that provides a mechanism for distilling TV Series information from the API into an XML file for import via Feeds or some other method.

== Installation ==
Install as any other module.

Ensure that the location for the XML file is writeable by the site.


== Configuration ==

This module only creates the XML file.

You will need to
* Configure cron to generate the XML file on a regular basis
* Create the content type to hold the information
* Create the Feeds importer (or other method) to routinely import the XML file
  into your database

