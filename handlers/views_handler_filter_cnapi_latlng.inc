<?php
/**
 * CNAPI Views filter for locations
 */
class views_handler_filter_cnapi_latlng extends views_handler_filter_cnapi {
  
  /**
   * Overrides init.
   */
  function init(&$view, &$options) {
    parent::init($view, $options);

    // set the operator
    $this->operator = 'latlng';
    $this->latitude = $this->options['latitude'];
    $this->longitude = $this->options['longitude'];
    $this->radius = $this->options['radius'];
  }
  
  /**
   * Overrides option_definition.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['latitude'] = array('default' => '');
    $options['longitude'] = array('default' => '');
    $options['radius'] = array('default' => '');

    return $options;
  }
  
  /**
   * Overrides admin_summary
   */
  function admin_summary() {
    $value = $this->parse_gis_location();
    return check_plain((string) $this->operator) . '=' . check_plain((string) $value);
  }

  /**
   * Overrides value_form.
   */
  function value_form(&$form, &$form_state) {    
    $form['latitude'] = array(
      '#type' => 'textfield',
      '#title' => t('Latitude'),
      '#default_value' => $this->latitude,
      '#required' => TRUE,
      '#size' => 40,
    );
    
    $form['longitude'] = array(
      '#type' => 'textfield',
      '#title' => t('Longitude'),
      '#default_value' => $this->longitude,
      '#required' => TRUE,
      '#size' => 40,
    );
    
    $form['radius'] = array(
      '#type' => 'textfield',
      '#title' => t('Radius'),
      '#default_value' => $this->radius,
      '#size' => 40,
    );
  }
  
  /**
   * Prepare the GIS coordinates for the API call
   */
  function parse_gis_location() {
    $output = $this->latitude . ';' . $this->longitude;
    if (!empty($this->radius)) {
      $output .= '!' . $this->radius;
    }
    return $output;
  }

  /**
   * Add this filter to the query.
   */
  function query() {
    $this->ensure_my_table();
    $value = $this->parse_gis_location();
    $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field", $value, $this->operator);
  }
}