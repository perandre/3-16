<?php
function designmd_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];
  if (!empty($breadcrumb)) {
    // Use CSS to hide titile .element-invisible.
    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';
    // comment below line to hide current page to breadcrumb
	$breadcrumb[] = drupal_get_title();
    $output .= '<nav class="breadcrumb">' . implode('   ', $breadcrumb) . '</nav>';
    return $output;
  }
}
function  designmd_form_contact_site_form_alter(&$form, &$form_state) {
  drupal_set_title(' ');
}

function designmd_theme() {
return array(
'contact_site_form' => array(
'render element' => 'form',
'template' => 'contact-site-form',
'path' => drupal_get_path('theme', 'designmd').'/templates',
),
);
}
function designmd_preprocess_contact_site_form(&$vars)
{
$vars['contact'] = drupal_render_children($vars['form']);
 
}

