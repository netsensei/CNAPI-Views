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
class views_handler_filter_cnapi extends views_handler_filter {

  /**
   * Determine if a filter can be exposed.
   */
  function can_expose() { return FALSE; }
  
  /**
   * Display the filter on the administrative summary
   */
  function admin_summary() {
    return check_plain((string) $this->operator) . '=' . check_plain((string) $this->value);
  }
  
  /**
   * Shortcut to display the value form.
   */
  function show_value_form(&$form, &$form_state) {
    $this->value_form($form, $form_state);
  }

}
