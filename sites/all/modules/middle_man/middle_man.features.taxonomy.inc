<?php
/**
 * @file
 * middle_man.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function middle_man_taxonomy_default_vocabularies() {
  return array(
    'aktivitetstype' => array(
      'name' => 'Aktivitetstype',
      'machine_name' => 'aktivitetstype',
      'description' => 'Barn, voksne, ungdom, live, osv?',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'metatags' => array(),
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
    'mest_for' => array(
      'name' => 'Mest for',
      'machine_name' => 'mest_for',
      'description' => 'Målgruppe',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'metatags' => array(),
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
    'style' => array(
      'name' => 'Style',
      'machine_name' => 'style',
      'description' => 'Musikkstil',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
      'metatags' => array(),
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
    'tags' => array(
      'name' => 'Tags',
      'machine_name' => 'tags',
      'description' => 'Use tags to group articles on similar topics into categories.',
      'hierarchy' => 1,
      'module' => 'taxonomy',
      'weight' => 0,
      'metatags' => array(),
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
