<?php
/**
 * CNAPI Views filter for city/region
 */
class views_handler_filter_cnapi_cityregion extends views_handler_filter_cnapi {
  
  /**
   * Overrides init.
   */
  function init(&$view, &$options) {
    parent::init($view, $options);

    // set the operator
    $this->operator = $this->options['operator'];
    $this->cityregion = $this->options['cityregion'];
  }
  
  /**
   * Overrides option_definition.
   */
  function option_definition() {
    $options = parent::option_definition();
    
    $options['operator'] = array('default' => '');
    $options['cityregion'] = array('default' => '');

    return $options;
  }

  /**
   * Overrides admin_summary.
   */
  function admin_summary() {
    return check_plain((string) $this->operator) . '=' . check_plain((string) $this->cityregion);
  }

  /**
   * Overrides value_form.
   */
  function value_form(&$form, &$form_state) {    
    $form['cityregion'] = array(
      '#type' => 'textfield',
      '#title' => t('City or region'),
      '#autocomplete_path' => 'cnapi/autocomplete/location',
      '#default_value' => $this->cityregion,
      '#size' => 40,
    );
  }
  
  /**
   * Overrides value_submit.
   */
  function value_submit($form, &$form_state) {
    $location = cnapi_location_parse($form_state['values']['options']['cityregion']);
    $form_state['values']['options']['operator'] = $location['type'];
  }

  /**
   * Add this filter to the query.
   */
  function query() {
    $this->ensure_my_table();    
    $location = cnapi_location_parse($this->cityregion);
    $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field", $location['value'], $location['type']);
  }
}
