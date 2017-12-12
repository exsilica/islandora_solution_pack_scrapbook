<?php

/**
 * @file
 * Provides the management interface for scrapbook Issue objects.
 */

require_once dirname(__FILE__) . '/utilities.inc';

/**
 * Local menu action, that gets the ingest page form.
 *
 * @global $user
 *
 * @param AbstractObject $issue
 *   The scrapbook to ingest into.
 *
 * @return sting
 *   The HTML repersentation of the ingest page form.
 */
function islandora_scrapbook_ingest_page(AbstractObject $issue) {
  global $user;
  module_load_include('inc', 'islandora', 'includes/utilities');
  module_load_include('inc', 'islandora', 'includes/ingest.form');
  $tuque = islandora_get_tuque_connection();
  $page = $tuque->repository->constructObject(islandora_get_namespace($issue->id));
  $page->owner = $user->name;
  $page->label = 'New Page';
  $page->models = 'islandora:scrapbookPageCModel';
  $scrapbook = islandora_object_load(islandora_scrapbook_get_scrapbook($issue));
  drupal_set_title(t('Add page to @scrapbook issue @issue', array('@scrapbook' => $scrapbook->label, '@issue' => $issue->label)));
  return drupal_get_form('islandora_ingest_form', array(
      'models' => array('islandora:scrapbookPageCModel'),
      'issue' => $issue,
      'objects' => array($page),
      'parent' => $issue->id,
    ));
}
