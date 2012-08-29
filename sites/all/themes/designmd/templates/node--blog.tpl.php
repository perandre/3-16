<?php 
if (!$page) { 
?>
<div class="blog-box">
<div class="image"><?php print render($content['field_blog_image']); ?></div>
                                
<div class="details">
 <h2 class="blog-head"><a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
<p class="meta">By <?php print render($name) ?>   / On <?php print format_date($node->created, 'custom', 'M.d.Y') ?>  /  <?php
// Query database table taxonomy_term_data and taxonomy_index
// So I can get all terms from my node.
$term = db_query('SELECT t.name, t.tid FROM {taxonomy_index} n LEFT JOIN  {taxonomy_term_data} t ON (n.tid = t.tid) WHERE n.nid = :nid', array(':nid' => $node->nid));

// db_query in Drupal 7 returns a stdClass object. 
// Value names are corresponding to the fields in your SQL query 
//(in our case "t.name") AND t.tid for build path.
$tags = '';
foreach ($term as $record) {
  // I put l() function for make my links.
  $tags .= l($record->name, 'taxonomy/term/' . $record->tid) . ' ';
}

print 'In ' . $tags;
?> /  Width <?php if ($node->comment and !($node->comment == 1 and !$node->comment_count)) { ?>  <a href="<?php print url("node/$node->nid", array('fragment' => 'comment-form')) ?>"><?php print format_plural($node->comment_count, '1 Comment', '@count Comments') ?></a><?php } ?></p>                                    
<?php hide($content['comments']); hide($content['links']); print render($content); ?>
<a href="<?php print $node_url; ?>" class="read">read more</a>

</div>
<div class="clear"></div>


</div>
<?php } else { 

$acc = user_load(1);
?>


        <!--BEGIN: blog single -->
        <div class="blog-single">
                    
            
            
            <!--BEGIN: meta-->
            <p class="meta">By <?php print render($name) ?>  / On <?php print format_date($node->created, 'custom', 'M.d.Y') ?>  /  <?php
// Query database table taxonomy_term_data and taxonomy_index
// So I can get all terms from my node.
$term = db_query('SELECT t.name, t.tid FROM {taxonomy_index} n LEFT JOIN  {taxonomy_term_data} t ON (n.tid = t.tid) WHERE n.nid = :nid', array(':nid' => $node->nid));

// db_query in Drupal 7 returns a stdClass object. 
// Value names are corresponding to the fields in your SQL query 
//(in our case "t.name") AND t.tid for build path.
$tags = '';
foreach ($term as $record) {
  // I put l() function for make my links.
  $tags .= l($record->name, 'taxonomy/term/' . $record->tid) . ' ';
}

print 'In ' . $tags;
?> /  Width <?php if ($node->comment and !($node->comment == 1 and !$node->comment_count)) { ?>  <a href="<?php print url("node/$node->nid", array('fragment' => 'comment-form')) ?>"><?php print format_plural($node->comment_count, '1 Comment', '@count Comments') ?></a><?php } ?></p>
            <!--END: meta-->

          
           <?php hide($content['comments']); hide($content['links']); print render($content); ?>
</div>
<div class="clear"></div>
 <div class="divider"></div>


<div class="clear"></div>
<?php //print '<pre>'. check_plain(print_r($node, 1)) .'</pre>'; ?>

<?php print render($content['comments']); ?>
<div class="clear"></div>

<?php } ?>
