<?php
 /**
  * This template is used to print a single field in a view. It is not
  * actually used in default Views, as this is registered as a theme
  * function which has better performance. For single overrides, the
  * template is perfectly okay.
  *
  * Variables available:
  * - $view: The view object
  * - $field: The field handler object that can process the input
  * - $row: The raw SQL result that can be used
  * - $output: The processed output that will normally be used.
  *
  * When fetching output from the $row, this construct should be used:
  * $data = $row->{$field->field_alias}
  *
  * The above will guarantee that you'll always get the correct data,
  * regardless of any changes in the aliasing that might happen if
  * the view is modified.
  */
?>



                        <div class="border-img">
                            <img src="<?php print file_create_url($row->_field_data['nid']['entity']->field_image['nb'][0]['uri']); dpm($row); ?>" alt="Images"/>
                            <a href="<?php print file_create_url($row->_field_data['nid']['entity']->field_image['nb'][0]['uri']); ?>" data-rel="prettyPhoto" title="<?php print $fields['title_1']->content; ?>" class="img-view"></a>
                             <?php print $fields['view_node_1']->content; ?>
                        </div>
                        <h2 class="title"><?php print $fields['title']->content; ?></h2>
                        <?php print $fields['body']->content; ?>
                        <?php print $fields['view_node']->content; ?>

                    