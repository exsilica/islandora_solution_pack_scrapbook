<?php

/**
 * @file
 * This is the template file for the object page for scrapbook
 *
 * Available variables:
 * - $islandora_content: A rendered vertical tabbed scrapbook issue browser.
 * - $parent_collections: An array containing parent collection IslandoraFedoraObject(s).
 * - $description: Rendered metadata descripton for the object.
 * - $metadata: Rendered metadata display for the binary object.
 *
 * @see template_preprocess_islandora_scrapbook()
 */
?>
<div class="islandora-scrapbook-object islandora">
  <div class="islandora-scrapbook-content-wrapper clearfix">
    <?php if ($islandora_content): ?>
      <div class="islandora-scrapbook-content">
        <?php print $islandora_content; ?>
      </div>
    <?php endif; ?>
  </div>
  <div class="islandora-scrapbook-metadata">
    <?php print $description; ?>
    <?php if ($parent_collections): ?>
      <div>
        <h2><?php print t('In collections'); ?></h2>
        <ul>
          <?php foreach ($parent_collections as $collection): ?>
        <li><?php print l($collection->label, "islandora/object/{$collection->id}"); ?></li>
          <?php endforeach; ?>
        </ul>
      </div>
    <?php endif; ?>
    <?php print $metadata; ?>
  </div>
</div>
