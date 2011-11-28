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

  // CNAPI Actors
  $data['cnapiactors']['table']['group'] = t('CNAPI Actors');
  $data['cnapiactors']['table']['base'] = array(
    'field' => 'cdbid',
    'title' => t('CNAPI Actors'),
    'help' => t('CNAPI Actors'),
    'query class' => 'cnapi_views_query',
  );

  // CNAPI Productions
  $data['cnapiproductions']['table']['group'] = t('CNAPI Productions');
  $data['cnapiproductions']['table']['base'] = array(
    'field' => 'cdbid',
    'title' => t('CNAPI Productions'),
    'help' => t('CNAPI Productions'),
    'query class' => 'cnapi_views_query',
  );

  $data['views']['cnapisort'] = array(
    'title' => t('CNAPI Sort'),
    'help' => t('Add a sorting order to the result set.'),
    'sort' => array(
      'handler' => 'views_handler_sort_cnapi',
    ),
  );

  // Query (q) Filter
  $data['cnapievents']['q'] = array(
    'title' => t('Query'),
    'help' => t('Perform a free text search.'),
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_q',
    ),
  );

  $data['cnapiactors']['q'] = array(
    'title' => t('Query'),
    'help' => t('Perform a free text search.'),
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_q',
    ),
  );

  $data['cnapiproductions']['q'] = array(
    'title' => t('Query'),
    'help' => t('Perform a free text search.'),
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_q',
    ),
  );

  // Keywords (k) filter
  $data['cnapievents']['k'] = array(
    'title' => t('Keywords'),
    'help' => t('Perform a keywords/tags search.'),
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_k',
    ),
  );

  $data['cnapiactors']['k'] = array(
    'title' => t('Keywords'),
    'help' => t('Perform a keywords/tags search.'),
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_k',
    ),
  );

  $data['cnapiproductions']['k'] = array(
    'title' => t('Keywords'),
    'help' => t('Perform a keywords/tags search.'),
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_k',
    ),
  );

  // Headings (heading) filter
  $data['cnapievents']['heading'] = array(
    'title' => t('Headings'),
    'help' => t('Perform search based on headings.'),
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_heading',
    ),
  );

  // Datetype (datetype) filter
  $data['cnapievents']['datetype'] = array(
    'title' => t('Datetype'),
    'help' => t('Perform search based on a datetype.'),
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_datetype',
    ),
  );

  // Daterange (daterange, date) filter
  $data['cnapievents']['daterange'] = array(
    'title' => t('Date(range)'),
    'help' => t('Perform search based on a date(range).'),
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_daterange',
    ),
  );

  // Isfree (isfree) filter
  $data['cnapievents']['isfree'] = array(
    'title' => t('Is free'),
    'help' => t('Is the event free or not.'),
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_isfree',
    ),
  );

  $data['cnapiproductions']['isfree'] = array(
    'title' => t('Is free'),
    'help' => t('Is the event free or not.'),
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_isfree',
    ),
  );

  // City/Region filter
  $data['cnapievents']['cityregion'] = array(
    'title' => t('City/Region'),
    'help' => t('Select objects for a city or a region'),
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_cityregion',
    ),
  );

  $data['cnapiactors']['cityregion'] = array(
    'title' => t('City/Region'),
    'help' => t('Select objects for a city or a region'),
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_cityregion',
    ),
  );

  // Location type filter
  $data['cnapievents']['locationtype'] = array(
    'title' => t('Location type'),
    'help' => t('Select objects based on their location type'),
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_locationtype',
    ),
  );

  $data['cnapiactors']['locationtype'] = array(
    'title' => t('Location type'),
    'help' => t('Select objects based on their location type'),
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_locationtype',
    ),
  );

  // Location filter
  $data['cnapievents']['location'] = array(
    'title' => t('Location'),
    'help' => t('Select objects based on their location name or GUID'),
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_location',
    ),
  );

  $data['cnapiproductions']['location'] = array(
    'title' => t('Location'),
    'help' => t('Select objects based on their location name or GUID'),
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_location',
    ),
  );

  // LatLng (latlng) filter
  $data['cnapiactors']['latlng'] = array(
    'title' => t('GIS Coordinates'),
    'help' => t('Select objects for a GIS location'),
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_latlng',
    ),
  );

  // AgeBetween (agebetween) filter
  $data['cnapievents']['agebetween'] = array(
    'title' => t('Age between'),
    'help' => t('Select objects with the age between x and y'),
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_agebetween',
    ),
  );

  $data['cnapiproductions']['agebetween'] = array(
    'title' => t('Age between'),
    'help' => t('Select objects with the age between x and y'),
    'filter' => array(
      'handler' => 'views_handler_filter_cnapi_agebetween',
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
      'cnapievent' => array(
        'title' => t('CNAPI Event'),
        'handler' => 'cnapi_views_row_event',
        'path' => $path . '/plugins',
        'base' => array('cnapievents'),
        'uses options' => TRUE,
        'type' => 'normal',
      ),
      'cnapiactor' => array(
        'title' => t('CNAPI Actor'),
        'handler' => 'cnapi_views_row_actor',
        'path' => $path . '/plugins',
        'base' => array('cnapiactors'),
        'uses options' => TRUE,
        'type' => 'normal',
      ),
      'cnapiproduction' => array(
        'title' => t('CNAPI Production'),
        'handler' => 'cnapi_views_row_production',
        'path' => $path . '/plugins',
        'base' => array('cnapiproductions'),
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
    'pager' => array(
      'cnapipagerfull' => array(
        'title' => t('Paged output, CNAPI Full pager'),
        'short title' => t('CNAPI Full'),
        'help' => t('Use the CNAPI Full pager output.'),
        'handler' => 'cnapi_views_pager_full',
        'uses options' => TRUE,
        'parent' => 'full',
      ),
    ),
  );
}