<?php
/**
 * CNAPI Views filter for location
 */
class views_handler_filter_cnapi_locationtype extends views_handler_filter_cnapi {

  /**
   * Overrides init.
   */
  function init(&$view, &$options) {
    parent::init($view, $options);

    // set the operator
    $this->operator = 'locationtype';
    $this->locationtype = $this->options['locationtype'];
  }

  /**
   * Overrides option_definition.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['locationtype'] = array('default' => '');
    return $options;
  }

  /**
   * Overrides admin_summary.
   */
  function admin_summary() {
    $types = cnapi_get_actortypes();
    $type = $types[$this->locationtype];    
    return check_plain((string) $this->operator) . '=' . check_plain((string) $type['name'] .  ' (' . $this->locationtype . ')');
  }

  /**
   * Overrides value_form.
   */
  function value_form(&$form, &$form_state) {
    
    $options = array();
    foreach (cnapi_get_actortypes() as $cid => $type) {
      $options[$cid] = $type['name'];
    }
       
    $form['locationtype'] = array(
      '#type' => 'select',
      '#title' => t('Locationtype'),
      '#description' => t('The type of location (i.e.) kunstencentrum.'),
      '#options' => $options,
      '#multiple' => FALSE,
      '#default_value' => $this->locationtype,
    );
  }

  /**
   * Add this filter to the query.
   */
  function query() {
    $this->ensure_my_table();
    $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field", $this->locationtype, $this->operator);
  }
  
}