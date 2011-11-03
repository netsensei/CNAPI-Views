<?php
/**
 * Filter for the date, daterange and datetype API calls
 */
class views_handler_filter_cnapi_datetype extends views_handler_filter_cnapi {

  /**
   * Defines the 'datetype' parameter
   */
  const CNAPI_DATE_DATETYPE = 'datetype';

  /**
   * Overrides init.
   */
  function init(&$view, &$options) {
    parent::init($view, $options);

    // Set the operator, this is set dynamically
    $this->operator = 'datetype';
    $this->when = $this->options['when'];
  }

  /**
   * Overrides option_definition
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['when'] = array('default' => '');

    return $options;
  }

  /**
   * Overrides admin_summary
   */
  function admin_summary() {
    return check_plain((string) $this->operator) . '=' . check_plain((string) $this->when);
  }

  /**
   * Overrides value_form.
   */
  function value_form(&$form, &$form_state) {    
    $valid_types = array('today', 'tomorrow', 'thisweek', 'thisweekend', 'nextweekend', 'next30days');
    $datetypes = array_intersect_key(cnapi_get_datetypes(), array_flip($valid_types));

    $options = array(CNAPI_OPTION_NONE => t('Select a period')) + $datetypes;

    $form['when'] = array(
      '#type' => 'select',
      '#title' => 'Periode',
      '#options' => $options,
      '#default_value' => $this->when,
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
    $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field", $this->when, $this->operator);
  }
}
