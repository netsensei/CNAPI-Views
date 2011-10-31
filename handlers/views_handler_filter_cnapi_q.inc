<?php
/**
 * Simple filter to handle matching of boolean values
 *
 * Definition items:
 * - label: (REQUIRED) The label for the checkbox.
 * - type: For basic 'true false' types, an item can specify the following:
 *    - true-false: True/false (this is the default)
 *    - yes-no: Yes/No
 *    - on-off: On/Off
 * - accept null: Treat a NULL value as false.
 */
class views_handler_filter_cnapi_q extends views_handler_filter_cnapi {
  
  function init(&$view, &$options) {
    parent::init($view, $options);
    
    // set the operator
    $this->operator = 'q';
  }
  
  function value_form(&$form, &$form_state) {    
    $form['value'] = array(
      '#type' => 'textfield',
      '#title' => t('Value'),
      '#size' => 30,
      '#default_value' => $this->value,
    );
  }
  
    /**
   * Add this filter to the query.
   *
   * Due to the nature of fapi, the value and the operator have an unintended
   * level of indirection. You will find them in $this->operator
   * and $this->value respectively.
   */
  function query() {
    $this->ensure_my_table();
    $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field", $this->value, $this->operator);
  }

}
