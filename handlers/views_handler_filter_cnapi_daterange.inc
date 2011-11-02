<?php
/**
 * Filter for the date, daterange and datetype API calls
 */
class views_handler_filter_cnapi_daterange extends views_handler_filter_cnapi {
  
  /**
   * Defines the 'datetype' parameter
   */
  const CNAPI_DATE_DATETYPE = 'datetype';
  
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
    // Somehow [#attached]['css'] doesn't work with the CNAPI Datepicker
    drupal_add_css(drupal_get_path('module', 'cnapi_views') . '/css/cnapi_views.css');
  
    // Set the operator, this is set dynamically
    $this->operator = $this->options['operator'];
    
    $this->when = $this->options['when'];
    $this->when_date = $this->options['when_date'];
    $this->date_type = $this->options['date_type'];
  }
  
  /**
   * Overrides option_definition
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['operator'] = array('default' => 'datetype');
    $options['date_type'] = array('default' => self::CNAPI_DATE_DATERANGE);
    $options['when'] = array('default' => '_none');
    $options['when_date'] = array('default' => '');
    
    return $options;
  }
  
  /**
   * Overrides admin_summary
   */
  function admin_summary() {
    return check_plain((string) $this->operator) . '=' . check_plain((string) $this->when_date);
  }
  
  /**
   * Overrides value_form.
   */
  function value_form(&$form, &$form_state) {    
    $valid_types = array('today', 'tomorrow', 'thisweek', 'thisweekend', 'nextweekend', 'next30days');
    $datetypes = array_intersect_key(cnapi_get_datetypes(), array_flip($valid_types));
    $options = array(CNAPI_OPTION_NONE => 'Selecteer een datum') + $datetypes;

    ctools_include('dependent');
    $form['#tree'] = TRUE;
    
    $form['when'] = array(
      '#type' => 'select',
      '#title' => t('When'),
      '#options' => $options,
      '#default_value' => $this->when,
      '#attributes' => array('class' => array('has-datepicker')),
    );

    $form['date_type'] = array(
      '#type' => 'select',
      '#title' => t('Date type'),
      '#options' => array(
        self::CNAPI_DATE_DATERANGE => t('Date range'), 
        self::CNAPI_DATE_DATE => t('One or more discrete dates'),
       ),
      '#default_value' => $this->date_type,
      '#process' => array('ctools_dependent_process'),
      '#dependency' => array('edit-options-when' => array('_none', '_datepicker')),
    );

    $form['when_date'] = array(
      '#title' => t('Select dates'),
      '#type' => 'textfield',
      '#default_value' => $this->when_date,
      '#description' => 'Formaat yyyy/mm/dd',
      '#size' => 10,
      '#attributes' => array('class' => array('date-for-datepicker')),
    );

    if ($this->when == '_none') {
      $form['when_date_display'] = array(
        '#prefix' => '<div class="form-item">',
        '#suffix' => '</div>',
        '#markup' => $this->_parse_date($this->operator, $this->when_date),
      );
    }

    $form['#attached']['library'][] = array('cnapi_browse', 'jquery.datePicker');
    $form['#attached']['js'][] = drupal_get_path('module', 'cnapi_browse') . '/js/cnapi_browse.js';
  }

  /**
   * Overrides value_submit.
   */
  function value_submit($form, &$form_state) {
    $valid_types = array('today', 'tomorrow', 'thisweek', 'thisweekend', 'nextweekend', 'next30days');
    $datetypes = array_intersect_key(cnapi_get_datetypes(), array_flip($valid_types));

    if (in_array($form_state['values']['options']['when'], array_keys($datetypes))) {
      $form_state['values']['options']['operator'] = self::CNAPI_DATE_DATETYPE;
    }
    else {     
      $form_state['values']['options']['operator'] = $form_state['values']['options']['date_type'];
    }
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
    $date = $this->_parse_date($this->operator, $this->when_date);
    $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field", $date, $this->operator);
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

  /**
   * Helper function. Parse the date so it can be correctly passed to the API call
   * 
   * @param type $datetype
   *   CNAPI_DATE_DATERANGE, CNAPI_DATE_DATE or CNAPI_DATE_DATETYPE
   * @param type $daterange
   *   A datestring to parse
   * @return string
   *  The parsed date string
   */
  function _parse_date($datetype, $daterange) {
    $date = '';
    
    switch ($datetype) {
      case self::CNAPI_DATE_DATERANGE :
        $parts = explode(';', $daterange);
        usort($parts, array($this, '_sort_dates'));
        $start = array_shift($parts);
        $end = array_pop($parts);
        $date = "$start..$end";
        break;
      default :
      $date = $daterange;
    }
    
    return $date;
  }
}
