<?php
/**
 * @file
 * Displays the scrapbook page controls.
 */
?>
<div class="islandora-scrapbook-controls">
  <?php print theme('item_list', array('items' => $controls, 'attributes' => array('class' => array('items', 'inline')))); ?>
</div>
