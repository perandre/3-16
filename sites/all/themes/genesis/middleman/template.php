<?php

/**
 * Preprocess and Process Functions SEE: http://drupal.org/node/254940#variables-processor
 * 1. Rename each function to match your subthemes name,
 *    e.g. if you name your theme "themeName" then the function
 *    name will be "themeName_preprocess_hook". Tip - you can
 *    search/replace on "middleman".
 * 2. Uncomment the required function to use.
 */

/**
 * Override or insert variables into all templates.
 */
/* -- Delete this line if you want to use these functions
function middleman_preprocess(&$vars, $hook) {
}
function middleman_process(&$vars, $hook) {
}
// */

/**
 * Override or insert variables into the html templates.
 */
/* -- Delete this line if you want to use these functions
function middleman_preprocess_html(&$vars) {
  // Uncomment the folowing line to add a conditional stylesheet for IE 7 or less.
  // drupal_add_css(path_to_theme() . '/css/ie/ie-lte-7.css', array('weight' => CSS_THEME, 'browsers' => array('IE' => 'lte IE 7', '!IE' => FALSE), 'preprocess' => FALSE));
}
function middleman_process_html(&$vars) {
}
// */

/**
 * Override or insert variables into the page templates.
 */
/* -- Delete this line if you want to use these functions
function middleman_preprocess_page(&$vars) {
}
function middleman_process_page(&$vars) {
}
// */

/**
 * Override or insert variables into the node templates.
 */
/* -- Delete this line if you want to use these functions
function middleman_preprocess_node(&$vars) {
}
function middleman_process_node(&$vars) {
}
// */

/**
 * Override or insert variables into the comment templates.
 */
/* -- Delete this line if you want to use these functions
function middleman_preprocess_comment(&$vars) {
}
function middleman_process_comment(&$vars) {
}
// */

/**
 * Override or insert variables into the block templates.
 */
function middleman_preprocess_block(&$vars) {

  // Add custom class based upon block id
  switch ($vars['elements']['#block']->bid) {
    // Add block reset class
    case 443:
      $vars['classes_array'][] = 'block-reset';
      break;
  }
}
/* -- Delete this line if you want to use these functions
function middleman_process_block(&$vars) {
}
// */
