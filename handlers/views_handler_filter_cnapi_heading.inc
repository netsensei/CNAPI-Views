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
class views_handler_filter_cnapi_heading extends views_handler_filter_cnapi {
  
  /**
   * Overrides init.
   */
  function init(&$view, &$options) {
    parent::init($view, $options);
    
    // set the operator
    $this->operator = 'heading';
    $this->headings = $this->options['headings'];
  }
  
  /**
   * Overrides option_definition.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['headings'] = array('default' => '');

    return $options;
  }

  /**
   * Overrides value_form.
   */
  function value_form(&$form, &$form_state) {
    $headings = cnapi_get_headings_tree(NULL, 'flat');
    $options = cnapi_get_select_options($headings, 'hid', 'name');

    $form['headings'] = array(
      '#type' => 'select',
      '#title' => t('Headings'),
      '#options' => $options,
      '#default_value' => $this->headings,
      '#multiple' => TRUE,
    );
  }
  
  /**
   * Overrides admin_summary
   */
  function admin_summary() {
    $value = $this->parse_headings();
    return check_plain((string) $this->operator) . '=' . check_plain((string) $value);
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
    $value = $this->parse_headings();
    $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field", $value, $this->operator);
  }

  /**
   * Helper function, parses the headings
   */
  function parse_headings() {
    return implode(';', $this->headings);
  }

}
