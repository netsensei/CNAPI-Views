<?php

class cnapi_views_query extends views_plugin_query {
  
  function init($base_table, $base_field, $options) {
    parent::init($base_table, $base_field, $options);
  }

  /**
   * Add a field to the query table, possibly with an alias. This will
   * automatically call ensure_table to make sure the required table
   * exists, *unless* $table is unset.
   *
   * @param $table
   *   The table this field is attached to. If NULL, it is assumed this will
   *   be a formula; otherwise, ensure_table is used to make sure the
   *   table exists.
   * @param $field
   *   The name of the field to add. This may be a real field or a formula.
   * @param $alias
   *   The alias to create. If not specified, the alias will be $table_$field
   *   unless $table is NULL. When adding formulae, it is recommended that an
   *   alias be used.
   * @param $params
   *   An array of parameters additional to the field that will control items
   *   such as aggregation functions and DISTINCT.
   *
   * @return $name
   *   The name that this field can be referred to as. Usually this is the alias.
   */
  function add_field($table, $field, $alias = '', $params = array()) {
    // We check for this specifically because it gets a special alias.
    if ($table == $this->base_table && $field == $this->base_field && empty($alias)) {
      $alias = $this->base_field;
    }

    if ($table && empty($this->table_queue[$table])) {
      $this->ensure_table($table);
    }

    if (!$alias && $table) {
      $alias = $table . '_' . $field;
    }

    // Make sure an alias is assigned
    $alias = $alias ? $alias : $field;

    // PostgreSQL truncates aliases to 63 characters: http://drupal.org/node/571548

    // We limit the length of the original alias up to 60 characters
    // to get a unique alias later if its have duplicates
    $alias = substr($alias, 0, 60);

    // Create a field info array.
    $field_info = array(
      'field' => $field,
      'table' => $table,
      'alias' => $alias,
    ) + $params;

    // Test to see if the field is actually the same or not. Due to
    // differing parameters changing the aggregation function, we need
    // to do some automatic alias collision detection:
    $base = $alias;
    $counter = 0;
    while (!empty($this->fields[$alias]) && $this->fields[$alias] != $field_info) {
      $field_info['alias'] = $alias = $base . '_' . ++$counter;
    }

    if (empty($this->fields[$alias])) {
      $this->fields[$alias] = $field_info;
    }

    return $alias;
  }

  /**
   * Build the query object. Load up all avaivable facets so the blocks work.
   */
  public function build(&$view) {
    // broken due to upgrade to views-6.x-3.x-dev // $this->init_pager($view);
    $view->init_pager();

    // Let the pager modify the query to add limits.
    $this->pager->query();

    if ($this->pager->use_pager()) {
      $this->pager->set_current_page($view->current_page);
    }
  }

  /**
   * Ensure table.
   */
  function ensure_table() {
    return 'cnapi';
  }

  /**
   * Execute the query
   * @see views_plugin_query::execute()
   */
  function execute(&$view) {
    $start = microtime(TRUE);

    if (isset($this->where)) {
      $params = $this->_get_query_params($this->where);
    }
    else {
      $params = array();
    }

    // pager
    if ($this->pager->use_pager()) {
      $params['page'] = $this->pager->current_page + 1; // CNAPI starts at 1
      $params['pagelength'] = $this->limit;
      $pager_options = TRUE;
    }
    elseif ($this->pager->options['items_per_page']) {
      $params['pagelength'] = $this->pager->options['items_per_page'];
      $pager_options = TRUE;
    }

    // sorting
    if (!empty($this->orderby)) {
      $params['sort'] = $this->orderby;
    }
    
    switch ($this->base_table) {
      case 'cnapievents' :
        $objects = cnapi_get_events($params);
        break;
      case 'cnapiactors' :
        $objects = cnapi_get_actors($params);
        break;
      case 'cnapiproductions' :
        $objects = cnapi_get_productions($params);
    }
    
    if ($objects['total'] > 0) {
      $view->result = $objects['data'];
      $view->total_rows = $objects['total'];
      $view->pager['current_page'] = $this->pager->current_page;
    }
    $view->execute_time = microtime() - $start;
  }

  /**
   * Construct the query_params array for cnapi_get_events()
   * @param unknown_type $where
   */
  function _get_query_params($where) {
    $params = array();
    
    if (is_array($where)) {
      foreach ($where as $group => $group_where) {
        if (is_array($group_where['conditions']) && !empty($group_where['conditions'])) {
          foreach ($group_where['conditions'] as $condition) {
            $params = array_merge($params, $condition);
          }
        }
      }
    }
    
    return $params;
  }

  function add_where($group, $clause, $value, $operator) {
    $this->where[$group]['conditions'][] = array(
      $operator => $value, 
    );
  }

  function add_orderby($sort = NULL, $direction = NULL) {
    if (!is_null($sort) && !is_null($direction)) {
      $this->orderby = $sort . ' ' . $direction;
    }
  }
}
