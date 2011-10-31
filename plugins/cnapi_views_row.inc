<?php

/**
 * @file
 * Provides the Display suite views entity style plugin.
 */

/**
 * Plugin which defines the view mode on the resulting entity object.
 */
class cnapi_views_row extends views_plugin_row {

  function init(&$view, &$display, $options = NULL) {
    parent::init($view, $display, $options);
    $this->base_table = $view->base_table;
    $this->base_field = 'cnapi_field';
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['style'] = array('default' => 'summary');
    return $options;
  }

  function options_form(&$form, &$form_state) {

    /*$form['style'] = array(
      '#title' => t('Style'),
      '#type' => 'radios',
      '#options' => array(
        'cnapi_ui_actor_summary' => t('Actor summary'),
        'cnapi_ui_event_summary' => t('Event summary'),
        'cnapi_ui_production_summary' => t('Production summary'),
    ),
      '#default_value' => $this->options['style'],
    );*/
  }

  /**
   * Render each $row.
   */
  function render($row) {
    $style = $this->options['style'];
    // @todo Make sure
    return theme('cnapi_ui_event_summary', array('event' => $row));
  }
}
