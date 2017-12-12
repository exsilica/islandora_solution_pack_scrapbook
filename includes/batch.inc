<?php

/**
 * @file
 * Batch used to delete a scrapbook object and all its children.
 */

/**
 * Deletes all issues and pages from a scrapbook object within batches.
 *
 * @param string $pid
 *   The pid of the scrapbook object which we are deleting.
 */
function islandora_scrapbook_delete_scrapbook_batch_operation($pid) {
  module_load_include('inc', 'islandora_scrapbook', 'includes/utilities');
  module_load_include('inc', 'islandora_paged_content', 'includes/batch');
  module_load_include('inc', 'islandora_paged_content', 'includes/utilities');
  module_load_include('inc', 'islandora', 'includes/datastream');
  $object = islandora_object_load($pid);
  $get_pid = function($o) {
    return $o['pid'];
  };
  $issues = islandora_scrapbook_get_issues($object);

  foreach ($issues as $issue) {
    $issue_object = islandora_object_load($issue['pid']);
    $pages = array_values(array_map($get_pid, islandora_paged_content_get_pages($issue_object)));
    $batch_delete = islandora_paged_content_delete_pages_batch($object, $pages);
    $batch_delete['operations'][] = array('islandora_paged_content_delete_parent_object_operation', array($issue_object->id));
    batch_set($batch_delete);
  }
  batch_set(islandora_scrapbook_delete_scrapbook_object_batch($pid));
}

/**
 * The main batch operation from which the other batch operations start.
 *
 * @param AbstractObject $object
 *   An AbstractObject representing a Fedora object.
 *
 * @return array
 *   An array defining the scrapbook object and children deletion batch.
 */
function islandora_scrapbook_delete_scrapbook_batch(AbstractObject $object) {
  return array(
    'operations' => array(
      array('islandora_scrapbook_delete_scrapbook_batch_operation', array(
        $object->id)),
    ),
    'title' => t('Deleting scrapbook object and all its children'),
    'init_message' => t('Preparing to delete scrapbook object and all its children...'),
    'progress_message' => t('Time elapsed: @elapsed <br/>Estimated time remaining @estimate.'),
    'error_message' => t('An error has occurred.'),
    'file' => drupal_get_path('module', 'islandora_scrapbook') . '/includes/batch.inc',
  );
}

/**
 * Creates a batch to go out and delete the scrapbook object.
 *
 * @param string $pid
 *   The pid of the scrapbook object to be deleted.
 *
 * @return array
 *   An array defining the scrapbook object deletion batch.
 */
function islandora_scrapbook_delete_scrapbook_object_batch($pid) {
  return array(
    'operations' => array(
      array('islandora_scrapbook_delete_scrapbook_object', array($pid)),
    ),
    'title' => t('Deleting scrapbook object'),
    'init_message' => t('Preparing to delete scrapbook object...'),
    'progress_message' => t('Time elapsed: @elapsed <br/>Estimated time remaining @estimate.'),
    'error_message' => t('An error has occurred.'),
    'file' => drupal_get_path('module', 'islandora_scrapbook') . '/includes/batch.inc',
  );
}

/**
 * Utility function to delete the scrapbook object.
 *
 * @param string $pid
 *   The pid of the scrapbook object being deleted.
 */
function islandora_scrapbook_delete_scrapbook_object($pid) {
  $object = islandora_object_load($pid);
  islandora_delete_object($object);
}
