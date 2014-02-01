<?php
/**
 * @file
 * views_collection.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function views_collection_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'preach';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Preach';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Taler';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Gjør det';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Nullstill';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['tags']['first'] = '« første';
  $handler->display->display_options['pager']['options']['tags']['previous'] = '‹ forrige';
  $handler->display->display_options['pager']['options']['tags']['next'] = 'neste ›';
  $handler->display->display_options['pager']['options']['tags']['last'] = 'siste »';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_take_date' => 'field_take_date',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_take_date' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Felt: Innhold: Tittel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Felt: Innhold: Opptaksdato */
  $handler->display->display_options['fields']['field_take_date']['id'] = 'field_take_date';
  $handler->display->display_options['fields']['field_take_date']['table'] = 'field_data_field_take_date';
  $handler->display->display_options['fields']['field_take_date']['field'] = 'field_take_date';
  $handler->display->display_options['fields']['field_take_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
    'show_repeat_rule' => 'show',
  );
  /* Sort criterion: Innhold: Opptaksdato (field_take_date) */
  $handler->display->display_options['sorts']['field_take_date_value']['id'] = 'field_take_date_value';
  $handler->display->display_options['sorts']['field_take_date_value']['table'] = 'field_data_field_take_date';
  $handler->display->display_options['sorts']['field_take_date_value']['field'] = 'field_take_date_value';
  $handler->display->display_options['sorts']['field_take_date_value']['order'] = 'DESC';
  /* Filter criterion: Innhold: Publisert */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Innhold: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'sound' => 'sound',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'voksen/taler';
  $translatables['preach'] = array(
    t('Master'),
    t('Taler'),
    t('more'),
    t('Gjør det'),
    t('Nullstill'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« første'),
    t('‹ forrige'),
    t('neste ›'),
    t('siste »'),
    t('Tittel'),
    t('Opptaksdato'),
    t('Page'),
  );
  $export['preach'] = $view;

  return $export;
}
