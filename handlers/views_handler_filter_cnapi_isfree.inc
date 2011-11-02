<?php
/**
 * Simple filter to handle matching of boolean values
 */
class views_handler_filter_cnapi_isfree extends views_handler_filter_cnapi {
  
  function init(&$view, &$options) {
    parent::init($view, $options);
    
    // set the operator
    $this->operator = 'isfree';
  }
  
  function value_form(&$form, &$form_state) {    
    $form['value'] = array(
      '#type' => 'select',
      '#title' => t('Show only free events?'),
      '#options' => array(
        'yes' => t('Yes'),
        'no' => t('No'),
      ),
      '#default_value' => $this->value,
    );
  }
  
  /**
   * Add this filter to the query.
   */
  function query() {
    $this->ensure_my_table();    
    $value = ($this->value == 'yes') ? 'true' : 'false';
    $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field", $value, $this->operator);
  }
}
