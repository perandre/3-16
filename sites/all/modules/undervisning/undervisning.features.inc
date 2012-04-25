<?php
/**
 * @file
 * undervisning.features.inc
 */

/**
 * Implementation of hook_views_api().
 */
function undervisning_views_api() {
  list($module, $api) = func_get_args();
  if ($module == "views" && $api == "views_default") {
    return array("version" => 3.0);
  }
}

/**
 * Implementation of hook_image_default_styles().
 */
function undervisning_image_default_styles() {
  $styles = array();

  // Exported image style: small
  $styles['small'] = array(
    'name' => 'small',
    'effects' => array(
      3 => array(
        'label' => 'Skaler og beskjær',
        'help' => 'Skaler og beskjær vil beholde størrelsesforhold i det originale bildet og så beskjære den største dimensjonen. Dette er mest nyttig for å lage perfekte kvadratiske miniatyrbilder uten å strekke bildet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '136',
          'height' => '102',
        ),
        'weight' => '1',
      ),
    ),
  );

  return $styles;
}
