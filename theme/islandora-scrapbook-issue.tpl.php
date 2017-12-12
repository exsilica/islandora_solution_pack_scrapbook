<?php

/**
 * @file
 */
?>
<div class="islandora-scrapbook-issue clearfix">
  <span class="islandora-scrapbook-issue-navigator">
    <?php print theme('islandora_scrapbook_issue_navigator', array('object' => $object)); ?>
  </span>
  <?php if (isset($viewer_id) && $viewer_id != "none"): ?>
    <div id="book-viewer">
      <?php print $viewer; ?>
    </div>
  <?php else: ?>
    <?php print theme('islandora_objects', array('objects' => $pages)); ?>
  <?php endif; ?>
  <div class="islandora-scrapbook-issue-metadata">
    <?php print $description; ?>
    <?php print $metadata; ?>
  </div>
</div>
