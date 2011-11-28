<?php

/**
 * The plugin to handle full CNAPI  pager.
 *
 * @ingroup views_pager_plugins
 */
class cnapi_views_pager_full extends views_plugin_pager_full {

  function set_total_items($total) {
    $this->total_items = $total;
  }

}