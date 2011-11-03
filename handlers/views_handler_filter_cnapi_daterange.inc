<?php
/**
 * Filter for the date, daterange and datetype API calls
 */
class views_handler_filter_cnapi_daterange extends views_handler_filter_cnapi {

  /**
   * Defines the 'daterange' parameter
   */
  const CNAPI_DATE_DATERANGE = 'daterange';

  /**
   * Defines the 'date' parameter
   */
  const CNAPI_DATE_DATE = 'date';

  /**
   * Overrides init.
   */
  function init(&$view, &$options) {
    parent::init($view, $options);

    // Set the operator, this is set dynamically
    $this->operator = $this->options['date_type'];
    $this->date = $this->options['date'];
  }

  /**
   * Overrides option_definition
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['date_type'] = array('default' => self::CNAPI_DATE_DATERANGE);
    $options['date'] = array('default' => '');

    return $options;
  }

  /**
   * Overrides admin_summary
   */
  function admin_summary() {
    $date = $this->parse_daterange($this->operator, $this->date);
    return check_plain((string) $this->operator) . '=' . check_plain((string) $date);
  }

  /**
   * Overrides value_form.
   */
  function value_form(&$form, &$form_state) {
    $form['date'] = array(
      '#type' => 'textfield',
      '#title' => 'Datum',
      '#default_value' => $this->date,
      '#description' => 'Formaat yyyy/mm/dd',
      '#size' => 10,
      '#attributes' => array('class' => array('date-for-datepicker')),
    );

    $form['date_type'] = array(
      '#type' => 'select',
      '#title' => t('Date type'),
      '#options' => array(
        self::CNAPI_DATE_DATERANGE => t('Date range (x..y)'),
        self::CNAPI_DATE_DATE => t('One or more discrete dates (x;y)'),
       ),
      '#default_value' => $this->date_type,
    );

    $form['#attached']['library'][] = array('cnapi_browse', 'jquery.datePicker');
    $form['#attached']['js'][] = drupal_get_path('module', 'cnapi_browse') . '/js/cnapi_browse.js';
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
    $date = $this->parse_daterange($this->operator, $this->date);
    $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field", $date, $this->operator);
  }

  /**
   * Helper function. Parse the date so it can be correctly passed to the API call
   * 
   * @param type $datetype
   *   CNAPI_DATE_DATERANGE, CNAPI_DATE_DATE
   * @param type $daterange
   *   A datestring to parse
   * @return string
   *  The parsed date string
   */
  function parse_daterange($datetype, $daterange) {
    $date = '';

    if ($datetype == self::CNAPI_DATE_DATERANGE) {
        $parts = explode(';', $daterange);
        usort($parts, array($this, '_sort_dates'));
        $start = array_shift($parts);
        $end = array_pop($parts);
        $date = "$start..$end";
    }
    else {
      $date = $daterange;
    }

    return $date;
  }

  /**
   * Helper function. Callback to sort dates during parsing of a daterange
   */
  function _sort_dates($a, $b) {
    $a_t = strtotime($a);
    $b_t = strtotime($b);
    if( $a_t == $b_t ) return 0 ;
    return ($a_t > $b_t ) ? 1 : -1;
  }
}
