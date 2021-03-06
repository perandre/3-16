<?php
/**
 * @file
 * middle_man.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function middle_man_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}

/**
 * Implements hook_views_api().
 */
function middle_man_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function middle_man_image_default_styles() {
  $styles = array();

  // Exported image style: 4col.
  $styles['4col'] = array(
    'name' => '4col',
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
          'width' => 290,
          'height' => 186,
        ),
        'weight' => 1,
      ),
    ),
    'label' => '4col',
  );

  // Exported image style: node-full.
  $styles['node-full'] = array(
    'name' => 'node-full',
    'effects' => array(
      4 => array(
        'label' => 'Skala',
        'help' => 'Skalering vil beholde størrelsesforhold i det originale bildet. Hvis bare en dimensjon er oppgitt, så beregnes den andre dimensjonen.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 554,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'node-full',
  );

  // Exported image style: slideshow.
  $styles['slideshow'] = array(
    'name' => 'slideshow',
    'effects' => array(
      2 => array(
        'label' => 'Skaler og beskjær',
        'help' => 'Skaler og beskjær vil beholde størrelsesforhold i det originale bildet og så beskjære den største dimensjonen. Dette er mest nyttig for å lage perfekte kvadratiske miniatyrbilder uten å strekke bildet.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 907,
          'height' => 297,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'slideshow',
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function middle_man_node_info() {
  $items = array(
    'article' => array(
      'name' => t('Article'),
      'base' => 'node_content',
      'description' => t('Use <em>articles</em> for time-sensitive content like news, press releases or blog posts.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'banner' => array(
      'name' => t('Banner'),
      'base' => 'node_content',
      'description' => t('Opprett et banner for slideshow eller andre steder på siten.'),
      'has_title' => '1',
      'title_label' => t('Tittel'),
      'help' => '',
    ),
    'blog' => array(
      'name' => t('blog'),
      'base' => 'node_content',
      'description' => t('Blogginnlegg'),
      'has_title' => '1',
      'title_label' => t('Tittel'),
      'help' => '',
    ),
    'event' => array(
      'name' => t('Event'),
      'base' => 'node_content',
      'description' => t('Opprett en hendelse i kalenderen!'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'page' => array(
      'name' => t('Basic page'),
      'base' => 'node_content',
      'description' => t('Use <em>basic pages</em> for your static content, such as an \'About us\' page.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'sound' => array(
      'name' => t('Lyd'),
      'base' => 'node_content',
      'description' => t('Brukes til taler'),
      'has_title' => '1',
      'title_label' => t('Tittel'),
      'help' => '',
    ),
    'tune' => array(
      'name' => t('Tune'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Tittel'),
      'help' => '',
    ),
    'webform' => array(
      'name' => t('Webform'),
      'base' => 'node_content',
      'description' => t('Create a new form or questionnaire accessible to users. Submission results and statistics are recorded and accessible to privileged users.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'worship' => array(
      'name' => t('Møte'),
      'base' => 'node_content',
      'description' => t('Samling lovsanger for et herlig møte!'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
