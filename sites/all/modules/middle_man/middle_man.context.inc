<?php
/**
 * @file
 * middle_man.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function middle_man_context_default_contexts() {
  $export = array();

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'Global';
  $context->description = 'Gjelder hele siten!';
  $context->tag = '';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'twitter_block-default' => array(
          'module' => 'twitter_block',
          'delta' => 'default',
          'region' => 'featured',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Gjelder hele siten!');
  $export['Global'] = $context;

  $context = new stdClass;
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'forside';
  $context->description = 'Front';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-slideshow-block' => array(
          'module' => 'views',
          'delta' => 'slideshow-block',
          'region' => 'featured',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Front');
  $export['forside'] = $context;

  return $export;
}
