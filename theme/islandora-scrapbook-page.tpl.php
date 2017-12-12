<?php

/**
 * @file
 * islandora-scrapbook-page.tpl.php
 * This is the template file for the object page for scrapbook
 *
 * Available variables:
 * - $object: The Islandora object rendered in this template file
 * - $islandora_content: A rendered image. By default this is the JPG datastream
 *   which is a medium sized image. Alternatively this could be a rendered
 *   viewer which displays the JP2 datastream image.
 * - $description: Rendered metadata descripton for the object.
 * - $metadata: Rendered metadata display for the binary object.
 *
 * @see template_preprocess_islandora_scrapbook_page()
 * @see theme_islandora_scrapbook_page()
 *
 */
?>
<div class="islandora-scrapbook-object">
  <div class="islandora-scrapbook-controls">
    <?php print theme('islandora_scrapbook_page_controls', array('object' => $object)); ?>
  </div>
  <div class="islandora-scrapbook-content-wrapper clearfix">
    <?php if ($content): ?>
      <div class="islandora-scrapbook-content">
        <?php print $content; ?>
      </div>
    <?php endif; ?>
  </div>
  <div class="islandora-scrapbook-page-metadata">
    <?php print $description; ?>
    <?php print $metadata; ?>
  </div>
</div>
