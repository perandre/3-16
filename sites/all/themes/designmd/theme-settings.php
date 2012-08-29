<?php

 
function designmd_form_system_theme_settings_alter(&$form, $form_state) {
  global $base_url;

  // Get theme name from url (admin/.../theme_name)
  $theme_name = arg(count(arg()) - 1);

  // Get default theme settings from .info file
  $theme_data = list_themes();   // get data for all themes
  $defaults = ($theme_name && isset($theme_data[$theme_name]->info['settings'])) ? $theme_data[$theme_name]->info['settings'] : array();

  // Create theme settings form widgets using Forms API
  // ST Fieldset
  $form['st_container'] = array(
    '#type' => 'fieldset',
    '#title' => t('Designmd theme settings'),
    '#description' => t('Use these settings to enhance the appearance of your Designmd theme.'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // General Settings
  $form['st_container']['general_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  // Theme Color
  $form['st_container']['general_settings']['them_color_config'] = array(
    '#type' => 'fieldset',
    '#title' => t('Style Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['st_container']['general_settings']['them_color_config']['theme_color'] = array(
    '#type' => 'select',
    '#title' => t('Select'),
    '#default_value' => theme_get_setting('theme_color'),
    '#options'  => array(
        'light'      => t('Light'),
        'dark'     => t('Dark'),
        
    ),
  );

  // Return theme settings form
  return $form;
}
