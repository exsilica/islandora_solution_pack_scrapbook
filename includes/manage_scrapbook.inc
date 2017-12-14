<?php

/**
 * @file
 * Contains one local action for ingesting pages.
 */

require_once dirname(__FILE__) . '/utilities.inc';

/**
 * Displays all the book management forms in a set of vertical tabs.
 *
 * @param AbstractObject $object
 *   The Scrapbook object to manage.
 *
 * @return array
 *   A renderable array containing all the management forms related to
 *   book objects.
 * Scrapbook update: The empty date form is the only field in the Newspaper manage tab;
 * hopefully most of this section can be discarded without breaking all the things. (20171212 cvm)
 * Update 20171214: Things are broken.
 *
function islandora_scrapbook_manage_scrapbook(AbstractObject $object) {
  drupal_set_title($object->label);
  return drupal_get_form('islandora_scrapbook_empty_issue_date_form', $object);
} 
*/

/**
 * Form to add dates missing from Scrapbook issues.
 *
 * @param array $form
 *   The form object.
 * @param array $form_state
 *   The form state.
 * @param AbstractObject|NULL $object
 *   The parent of the issues missing dates or NULL for all issues.
 *
 * @return array
 *   Renderable array of the form.
 *
function islandora_scrapbook_empty_issue_date_form(array $form, array &$form_state, $object) {
  $empty_issues = islandora_scrapbook_get_empty_dates($object);
  $form = array();
  $form['dates_table'] = array(
    '#type' => 'fieldset',
    '#title' => t('Issues missing a dateIssued field.'),
    '#description' => t('These scrapbook Issues will not appear in the default browse listing until they have valid dates. Add a date in the format "YYYY-MM-DD" and save the changes.'),
  );
  if (count($empty_issues) > 0) {
    foreach ($empty_issues as $issue) {
      $issue_obj = islandora_object_load($issue['pid']);
      if ($issue_obj) {
        $escaped_pid = $issue['pid'];
        $form['dates_table'][$escaped_pid] = array(
          '#type' => 'textfield',
          '#name' => "issue_dates[$escaped_pid]",
          '#prefix' => '<div class="islandora-scrapbook-empty-issues">',
          '#suffix' => t('<a target="_new" href="@url">@label (@pid)</a></div>',
            array(
              '@url' => url('islandora/object/' . $issue['pid']),
              '@label' => $issue['label'],
              '@pid' => $issue['pid'],
            )
          ),
          '#attributes' => array('class' => array('datepicker')),
          '#default_value' => (isset($form_state['input']['issue_dates'][$escaped_pid]) ? $form_state['input']['issue_dates'][$escaped_pid] : ""),
          '#disabled' => (!islandora_user_access($issue_obj, array(ISLANDORA_METADATA_EDIT), array('islandora:scrapbookIssueCModel'))),
          '#size' => 20,
          '#maxlength' => 10,
        );
      }
    }
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
    );
    $form['issue_dates'] = array(
      '#type' => 'value',
    );
    $form['#after_build'] = array(
      'islandora_scrapbook_empty_issue_date_datepicker',
    );
  }
  else {
    $form['dates_table']['all_good'] = array(
      '#type' => 'item',
      '#markup' => t('None found.'),
    );
  }
  return $form;
} 
*/

/**
 * Add datepicker to the issue date textfields.
 *
 * @param array $form
 *   The form object.
 * @param array $form_state
 *   The form state.
 *
 * @return array
 *   Renderable array of the form.
 *
function islandora_scrapbook_empty_issue_date_datepicker(array $form, array $form_state) {
  drupal_add_library('system', 'ui.datepicker');
  drupal_add_js("(function ($) { $('.datepicker').datepicker({dateFormat: \"yy-mm-dd\"
}); })(jQuery);", array('type' => 'inline', 'scope' => 'footer', 'weight' => 5));
  return $form;
} 
*/

/**
 * Implements hook_form_validate().
 *
 * Validate the dates entered on the form.
 *
function islandora_scrapbook_empty_issue_date_form_validate($form, &$form_state) {
  $errors = FALSE;
  $updates = 0;
  foreach ($form_state['values']['issue_dates'] as $key => $date) {
    if (trim($date) != "") {
      $updates += 1;
      if (!preg_match('/^\d{4}-\d{1,2}-\d{1,2}$/', $date)) {
        form_set_error("$key");
        $errors = TRUE;
      }
      else {
        try {
          $dt = new DateTime($date);
        }
        catch (Exception $e) {
          form_set_error("$key");
          $errors = TRUE;
        }
      }
    }
  }
  if ($errors) {
    drupal_set_message(t("Invalid date(s), please enter a valid date of the format YYYY-MM-DD."), "error");
  }
  elseif ($updates == 0) {
    drupal_set_message(t("You did not submit any dates."), "error");
  }
} 
*/

/**
 * Implements hook_form_submit().
 *
 * Update the objects with the dateIssued relationships.
 *
function islandora_scrapbook_empty_issue_date_form_submit($form, &$form_state) {
  module_load_include('inc', 'islandora_scrapbook', 'includes/utilities');
  $out = TRUE;
  foreach ($form_state['values']['issue_dates'] as $key => $date) {
    if (trim($date) != "") {
      $object = islandora_object_load($key);
      if ($object) {
        $dt = new DateTime($date);
        if (isset($object['MODS'])) {
          // Set the dateIssued to the MODS datastream.
          $ret = islandora_scrapbook_set_mods_date_issued($object['MODS'], $dt);
        }
        else {
          // Set the dateIssued to the RELS-EXT.
          $ret = islandora_scrapbook_set_date_issued($object, $dt);
        }
        if (isset($ret) && $ret === FALSE) {
          $out = FALSE;
        }
      }
    }
  }
  if (!$out) {
    drupal_set_message(t("There were some errors completing your request. Check the watchdog logs for more information"), "error");
  }
  else {
    drupal_set_message(t("Issue dates saved."));
  }
} 
*/

/**
 * Local menu action, that gets the ingest page form.
 *
 * @param AbstractObject $scrapbook
 *   The Scrapbook to ingest into.
 *
 * @return sting
 *   The HTML repersentation of the ingest page form.
 */
function islandora_scrapbook_ingest_issue(AbstractObject $scrapbook) {
  global $user;
  module_load_include('inc', 'islandora', 'includes/utilities');
  module_load_include('inc', 'islandora', 'includes/ingest.form');
  $tuque = islandora_get_tuque_connection();
  $issue = $tuque->repository->constructObject(islandora_get_namespace($scrapbook->id));
  $issue->owner = $user->name;
  $issue->label = 'New Issue';
  $issue->models = 'islandora:scrapbookIssueCModel';
  // Assume sequential adding of issues for now.
  $issues = islandora_scrapbook_get_issues($scrapbook);
  $num_issues = count($issues) + 1;
  $issue->relationships->add(FEDORA_RELS_EXT_URI, 'isMemberOf', $scrapbook->id);
  $issue->relationships->add(ISLANDORA_RELS_EXT_URI, 'isSequenceNumber', (string) $num_issues, TRUE);
  drupal_set_title(t('Add issue to @scrapbook', array('@scrapbook' => $scrapbook->label)));
  return drupal_get_form('islandora_ingest_form', array(
      'models' => array('islandora:scrapbookIssueCModel'),
      'objects' => array($issue),
      'parent' => $scrapbook->id,
    ));
}
