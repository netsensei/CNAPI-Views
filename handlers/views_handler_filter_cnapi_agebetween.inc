<?php
/**
 * CNAPI Views filter for agebetween
 */
class views_handler_filter_cnapi_agebetween extends views_handler_filter_cnapi {
  
  /**
   * Overrides init.
   */
  function init(&$view, &$options) {
    parent::init($view, $options);

    // set the operator
    $this->operator = 'agebetween';
    $this->upper = $this->options['upper'];
    $this->lower = $this->options['lower'];
  }
  
  /**
   * Overrides option_definition.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['upper'] = array('default' => '');
    $options['lower'] = array('default' => '');

    return $options;
  }
  
  /**
   * Overrides admin_summary
   */
  function admin_summary() {
    $value = $this->parse_age_between();
    return check_plain((string) $this->operator) . '=' . check_plain((string) $value);
  }

  /**
   * Overrides value_form.
   */
  function value_form(&$form, &$form_state) {
    $options = array();
    for ($i = 1; $i <= 99; $i++) {
      $options[$i] = $i;
    }

    $form['lower'] = array(
      '#type' => 'select',
      '#title' => t('Lower boundary'),
      '#default_value' => $this->lower,
      '#options' => $options,
      '#required' => TRUE,
      '#multiple' => FALSE,
    );
    
    $form['upper'] = array(
      '#type' => 'select',
      '#title' => t('Upper boundary'),
      '#default_value' => $this->upper,
      '#options' => $options,
      '#required' => TRUE,
      '#multiple' => FALSE,
    );
  }
  
  /**
   * Overrides value_validate
   */
  function value_validate($form, &$form_state) {
    if ($form_state['values']['options']['lower'] >= $form_state['values']['options']['upper']) {
      form_set_error('lower', t('The lower age can not be great the then upper age.'));
    }
  }
  
  /**
   * Prepare the GIS coordinates for the API call
   */
  function parse_age_between() {
    return $this->lower . '..' . $this->upper;
  }

  /**
   * Add this filter to the query.
   */
  function query() {
    $this->ensure_my_table();
    $value = $this->parse_age_between();
    $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field", $value, $this->operator);
  }
}