<?php

/**
 * @file
 * Views integration.
 */

/**
 * Implements hook_views_data().
 */
function cnapi_views_data() {

  // CNAPI Events
  $data['cnapievents']['table']['group'] = t('CNAPI Events');
  $data['cnapievents']['table']['base'] = array(
    'field' => 'cdbid',
    'title' => t('CNAPI Events'),
    'help' => t('CNAPI Events'),
    'query class' => 'cnapi_views_query',
  );
  
  $data['cnapievents']['q'] = array(
    'title' => t('Query'),
    'help' => t('Perform a free text search.'), // The help that appears on the UI,    
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_q',
    ),
  );
  
  $data['cnapievents']['k'] = array(
    'title' => t('Keywords'),
    'help' => t('Perform a keywords/tags search.'), // The help that appears on the UI,    
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_k',
    ),
  );
  
  $data['cnapievents']['heading'] = array(
    'title' => t('Headings'),
    'help' => t('Perform search based on headings.'), // The help that appears on the UI,    
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_heading',
    ),
  );
  
  $data['cnapievents']['daterange'] = array(
    'title' => t('Daterange'),
    'help' => t('Perform search based on a date range.'), // The help that appears on the UI,    
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_daterange',
    ),
  );

  return $data;
}

/**
 * Implements hook_views_plugins().
 */
function cnapi_views_views_plugins() {
  $path = drupal_get_path('module', 'views_cnapi');
  return array(
    'module' => 'cnapi_views',
    'query' => array(
      'cnapi_views_query' => array(
        'uses fields' => FALSE,
        'path' => $path . '/plugins',
        'title' => t('Cnapi Query'),
        'help' => t('Query that allows you to search with Cnapi.'),
        'handler' => 'cnapi_views_query',
        'parent' => 'views_query',
      ),
    ),
    'row' => array(
      'cnapi' => array(
        'title' => t('Cnapi'),
        'handler' => 'cnapi_views_row',
        'path' => $path . '/plugins',
        'base' => array('cnapievents'),
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
  );
}