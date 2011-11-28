<?php
/**
 * CNAPI Views filter for location
 */
class views_handler_filter_cnapi_location extends views_handler_filter_cnapi {

  /**
   * Overrides init.
   */
  function init(&$view, &$options) {
    parent::init($view, $options);

    // set the operator
    $this->operator = 'location';
    $this->location = $this->options['location'];
  }

  /**
   * Overrides option_definition.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['location'] = array('default' => '');
    return $options;
  }

  /**
   * Overrides admin_summary.
   */
  function admin_summary() {
    return check_plain((string) $this->operator) . '=' . check_plain((string) $this->location);
  }

  /**
   * Overrides value_form.
   */
  function value_form(&$form, &$form_state) {
    $form['location'] = array(
      '#type' => 'textfield',
      '#title' => t('Location'),
      '#description' => t('The location (i.e. CC De Spil or its GUID.'),
      '#default_value' => $this->location,
      '#size' => 40,
    );
  }

  /**
   * Add this filter to the query.
   */
  function query() {
    $this->ensure_my_table();
    $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field", $this->location, $this->operator);
  }
}