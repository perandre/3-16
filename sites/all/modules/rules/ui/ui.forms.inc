<?php
// $Id: ui.forms.inc,v 1.1.2.6 2011/01/05 11:38:13 fago Exp $

/**
 * @file Rules UI forms
 */

/**
 * Ajax callback for reloading the whole form.
 */
function rules_ui_form_ajax_reload_form($form, $form_state) {
  return $form;
}

/**
 * Defines #ajax properties.
 */
function rules_ui_form_default_ajax($effect = 'slide') {
  return array(
    'callback' => 'rules_ui_form_ajax_reload_form',
    'wrapper' => 'rules-form-wrapper',
    'effect' => $effect,
    'speed' => 'fast',
  );
}

/**
 * Submit handler for switching the parameter input mode.
 */
function rules_ui_parameter_replace_submit($form, &$form_state) {
  if (isset($form_state['triggering_element'])) {
    $name = $form_state['triggering_element']['#parameter'];
    $form_state['parameter_mode'][$name] = $form_state['parameter_mode'][$name] == 'selector' ? 'input' : 'selector';
  }
  $form_state['rebuild'] = TRUE;
}


/**
 * General form submit handler, that rebuilds the form
 */
function rules_form_submit_rebuild($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}


/**
 * Edit a rules configuration.
 */
function rules_ui_form_edit_rules_config($form, &$form_state, $rules_config, $base_path) {
  RulesPluginUI::$basePath = $base_path;
  $form_state += array('rules_element' => $rules_config);
  // Add the rule configuration's form.
  $rules_config->form($form, $form_state, array('show settings' => TRUE, 'button' => TRUE));
  $form['#validate'] = array('rules_ui_form_rules_config_validate');
  return $form;
}

/**
 * General rules configuration form validation callback. Also populates the
 * rules configuration with the form values.
 */
function rules_ui_form_rules_config_validate($form, &$form_state) {
  $form_state['rules_element']->form_validate($form, $form_state);
}

/**
 * Edit a rules configuration form submit callback.
 */
function rules_ui_form_edit_rules_config_submit($form, &$form_state) {
  $form_state['rules_element']->form_submit($form, $form_state);
  if (empty($form_state['redirect'])) {
    $form_state['redirect'] = RulesPluginUI::defaultRedirect($form_state['rules_element']);
  }
}

/**
 * Clone a rules configuration form.
 */
function rules_ui_form_clone_rules_config($form, &$form_state, $rules_config, $base_path) {
  RulesPluginUI::$basePath = $base_path;
  $rules_config = clone $rules_config;
  $rules_config->module = 'rules';
  $rules_config->id = FALSE;
  $rules_config->name = '';
  $rules_config->label .= ' (' . t('cloned') . ')';

  $form['#validate'][] = 'rules_ui_form_rules_config_validate';
  $form['#submit'][] = 'rules_ui_form_edit_rules_config_submit';
  $form_state += array('rules_element' => $rules_config);
  // Add the rule configuration's form.
  $rules_config->form($form, $form_state, array('show settings' => TRUE, 'button' => TRUE, 'init' => TRUE));

  // Open the settings fieldset so altering the name is easier.
  $form['settings']['#collapsed'] = FALSE;
  return $form;
}

/**
 * Configuration form to directly execute a rules configuration.
 */
function rules_ui_form_execute_rules_config($form, &$form_state, $rules_config, $base_path) {
  // Only components can be executed.
  if (!($rules_config instanceof RulesTriggerableInterface)) {
    RulesPluginUI::$basePath = $base_path;
    // Create either the appropriate action or condition element.
    $element = rules_plugin_factory($rules_config instanceof RulesActionInterface ? 'action' : 'condition', 'component_' . $rules_config->name);
    $form['exec_help'] = array(
      '#prefix' => '<p>',
      '#markup' => t('This form allows you to manually trigger the execution of the @plugin "%label". If this component requires any parameters, input the suiting execution arguments below.', array('@plugin' => $rules_config->plugin(), '%label' => $rules_config->label())),
      '#suffix' => '</p>',
    );
    $element->form($form, $form_state);

    // For conditions hide the option to negate them.
    if (isset($form['negate'])) {
      $form['negate']['#access'] = FALSE;
    }
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Execute'),
      '#weight' => 20,
    );
    // Re-use the validation callback, which will also populate the action with
    // the configuration settings in the form.
    $form['#validate'] = array('rules_ui_form_rules_config_validate');
    return $form;
  }
  drupal_not_found();
  exit;
}

/**
 * Submit callback for directly executing a component.
 */
function rules_ui_form_execute_rules_config_submit($form, &$form_state) {
  $element = $form_state['rules_element'];
  $result = $element->execute();
  if ($element instanceof RulesActionInterface) {
    drupal_set_message(t('Component %label has been executed.', array('%label' => $element->label())));
  }
  else {
    drupal_set_message(t('Component %label evaluated to %result.', array('%label' => $element->label(), '%result' => $result ? 'true' : 'false')));
  }
}

/**
 * Gets the confirmation question for valid operations, or else FALSE.
 */
function rules_ui_confirm_operations($op, $rules_config) {
  switch ($op) {
    case 'enable':
      return t('Are you sure you want to enable the %plugin %label?', array('%plugin' => $rules_config->plugin(), '%label' => $rules_config->label()));
    case 'disable':
      return t('Are you sure you want to disable the %plugin %label?', array('%plugin' => $rules_config->plugin(), '%label' => $rules_config->label()));
    case 'revert':
      return t('Are you sure you want to revert the %plugin %label?', array('%plugin' => $rules_config->plugin(), '%label' => $rules_config->label()));
    case 'delete':
      return t('Are you sure you want to delete the %plugin %label?', array('%plugin' => $rules_config->plugin(), '%label' => $rules_config->label()));
    default:
      return FALSE;
  }
}

/**
 * Confirmation form for applying the operation to the config.
 */
function rules_ui_form_rules_config_confirm_op($form, &$form_state, $rules_config, $op, $base_path) {
  if ($confirm_question = rules_ui_confirm_operations($op, $rules_config)) {
    RulesPluginUI::$basePath = $base_path;
    $form_state += array('rules_config' => $rules_config, 'op' => $op);
    return confirm_form($form, $confirm_question, $base_path, t('This action cannot be undone.'), t('Confirm'), t('Cancel'));
  }
  else {
    drupal_not_found();
    exit;
  }
}

/**
 * Applies the operation and returns the message to show to the user. Also the
 * operation is logged to the watchdog. Note that the string is defined two
 * times so that the translation extractor can find it.
 */
function rules_ui_confirm_operation_apply($op, $rules_config) {
  $vars = array('%plugin' => $rules_config->plugin(), '%label' => $rules_config->label());
  $edit_link = l(t('edit'), RulesPluginUI::path($rules_config->name));

  switch ($op) {
    case 'enable':
      $rules_config->active = TRUE;
      $rules_config->save();
      watchdog('rules', 'Enabled %plugin %label.', $vars, WATCHDOG_NOTICE, $edit_link);
      return t('Enabled %plugin %label.', $vars);

    case 'disable':
      $rules_config->active = FALSE;
      $rules_config->save();
      watchdog('rules', 'Disabled %plugin %label.', $vars, WATCHDOG_NOTICE, $edit_link);
      return t('Disabled %plugin %label.', $vars);

    case 'revert':
      $rules_config->delete();
      watchdog('rules', 'Reverted %plugin %label to the defaults.', $vars, WATCHDOG_NOTICE, $edit_link);
      return t('Reverted %plugin %label to the defaults.', $vars);

    case 'delete':
      $rules_config->delete();
      watchdog('rules', 'Deleted %plugin %label.', $vars);
      return t('Deleted %plugin %label.', $vars);
  }
}

/**
 * Rule config deletion form submit callback.
 */
function rules_ui_form_rules_config_confirm_op_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $msg = rules_ui_confirm_operation_apply($form_state['op'], $form_state['rules_config']);
    drupal_set_message($msg);
  }
}

/**
 * Add a new element a rules configuration.
 */
function rules_ui_add_element($form, &$form_state, $rules_config, $plugin_name, RulesContainerPlugin $parent, $base_path) {
  $cache = rules_get_cache();
  if (!isset($cache['plugin_info'][$plugin_name]['class'])) {
    drupal_not_found();
    exit;
  }
  RulesPluginUI::$basePath = $base_path;
  $plugin_is_abstract = in_array('RulesAbstractPlugin', class_parents($cache['plugin_info'][$plugin_name]['class']));
  // In the first step create the element and in the second step show its edit
  // form.
  if ($plugin_is_abstract && !isset($form_state['rules_element'])) {
    RulesPluginUI::formDefaults($form, $form_state);
    $form_state += array('parent_element' => $parent, 'plugin' => $plugin_name);

    $form['element_name'] = array(
      '#type' => 'select',
      '#title' => t('Select the %element to add', array('%element' => $plugin_name)),
      '#options' => RulesPluginUI::getOptions($plugin_name . '_info'),
      '#ajax' => rules_ui_form_default_ajax() + array(
        'trigger_as' => array('name' => 'continue'),
      ),
    );
    $form['continue'] = array(
      '#type' => 'submit',
      '#name' => 'continue',
      '#value' => t('Continue'),
      '#ajax' => rules_ui_form_default_ajax(),
    );
  }
  elseif (!$plugin_is_abstract) {
    // Create the initial, empty element.
    $element = rules_plugin_factory($plugin_name);
    // Always add the new element at the bottom, thus set an appropriate weight.
    $iterator = $parent->getIterator();
    if ($sibling = end($iterator)) {
      $element->weight = $sibling->weight + 1;
    }
    $element->setParent($parent);
    $form_state['rules_element'] = $element;
  }

  if (isset($form_state['rules_element'])) {
    $form_state['rules_element']->form($form, $form_state, array('button' => TRUE, 'init' => TRUE));
    $form['#validate'][] = 'rules_ui_edit_element_validate';
    $form['#submit'][] = 'rules_ui_edit_element_submit';
  }
  return $form;
}

/**
 * Add element submit callback.
 * Used for "abstract plugins" to create the initial element object with the
 * given implemenation name and rebuild the form.
 */
function rules_ui_add_element_submit($form, &$form_state) {
  $element = rules_plugin_factory($form_state['plugin'], $form_state['values']['element_name']);

  // Always add the new element at the bottom, thus set an appropriate weight.
  $iterator = $form_state['parent_element']->getIterator();
  if ($sibling = end($iterator)) {
    $element->weight = $sibling->weight + 1;
  }
  // Clear the element settings so they won't be processed on serialization as
  // there is nothing to be processed yet.
  $element->settings = array();
  $element->setParent($form_state['parent_element']);

  $form_state['rules_element'] = $element;
  $form_state['rebuild'] = TRUE;
}

/**
 * Delete elements.
 */
function rules_ui_delete_element($form, &$form_state, $rules_config, $rules_element, $base_path) {
  RulesPluginUI::$basePath = $base_path;
  $form_state += array('rules_config' => $rules_config, 'rules_element' => $rules_element);
  $confirm_question = t('Are you sure you want to delete the %element_plugin %element_name?', array('%element_plugin' => $rules_element->plugin(), '%element_name' => $rules_element->label(), '%plugin' => $rules_config->plugin(), '%label' => $rules_config->label()));
  return confirm_form($form, $confirm_question, RulesPluginUI::path($rules_config->name), t('This action cannot be undone.'), t('Delete'), t('Cancel'));
}

/**
 * Rule config deletion form validation callback.
 */
function rules_ui_delete_element_validate($form, &$form_state) {
  // Save the parent for determining the right redirect target on submit.
  $form_state['element_parent'] = $form_state['rules_element']->parentElement();
  $removed_plugin = $form_state['rules_element']->plugin();
  $form_state['rules_element']->delete();
  try {
    $form_state['rules_config']->integrityCheck();
  }
  catch (RulesException $e) {
    $args = array(
      '@plugin' => $e->element->plugin(),
      '%label' => $e->element->label(),
      '@removed-plugin' => $removed_plugin,
      '!url' => url(RulesPluginUI::path($form_state['rules_config']->name, 'edit', $e->element)),
    );
    form_set_error('', t('Unable to delete the @removed-plugin as some of its provided variables are utilized by the @plugin <a href="!url">%label</a>.', $args));
  }
}

/**
 * Rule config deletion form submit callback.
 */
function rules_ui_delete_element_submit($form, &$form_state) {
  $rules_config = $form_state['rules_config'];
  $rules_config->save();
  if (empty($form_state['redirect'])) {
    $form_state['redirect'] = RulesPluginUI::defaultRedirect($form_state['element_parent']);
  }
}


/**
 * Configure a rule element.
 */
function rules_ui_edit_element($form, &$form_state, $rules_config, $element, $base_path) {
  RulesPluginUI::$basePath = $base_path;
  $form_state += array('rules_element' => $element);
  $form_state['rules_element']->form($form, $form_state, array('button' => TRUE));
  return $form;
}

/**
 * Validate the element configuration.
 */
function rules_ui_edit_element_validate($form, &$form_state) {
  $form_state['rules_element']->form_validate($form, $form_state);
}

/**
 * Submit the element configuration.
 */
function rules_ui_edit_element_submit($form, &$form_state) {
  $form_state['rules_element']->form_submit($form, $form_state);
  if (empty($form_state['redirect'])) {
    $form_state['redirect'] = RulesPluginUI::defaultRedirect($form_state['rules_element']);
  }
}

/**
 * Add a new event.
 */
function rules_ui_add_event($form, &$form_state, RulesReactionRule $rules_config, $base_path) {
  RulesPluginUI::$basePath = $base_path;
  $form_state += array('rules_config' => $rules_config);
  $events = array_diff_key(rules_fetch_data('event_info'), array_flip($rules_config->events()));

  $form['help'] = array(
    '#markup' => t('Select the event to add, however note that only events providing all utilized variables can be added.'),
  );
  $form['event'] = array(
    '#type' => 'select',
    '#title' => t('React on event'),
    '#options' => RulesPluginUI::getOptions($events),
    '#description' => t('Whenever the event occurrs, rule evaluation is triggered.'),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add'),
  );
  $form_state['redirect'] = RulesPluginUI::path($rules_config->name);
  return $form;
}

/**
 * Validate the event configuration.
 */
function rules_ui_add_event_validate($form, &$form_state) {
  if (!empty($form_state['values']['event'])) {
    $rules_config = $form_state['rules_config'];
    $rules_config->event($form_state['values']['event']);
    try {
      $rules_config->integrityCheck();
    }
    catch (RulesException $e) {
      $args = array(
        '@plugin' => $e->element->plugin(),
        '%label' => $e->element->label(),
        '!url' => url(RulesPluginUI::path($form_state['rules_config']->name, 'edit', $e->element)),
      );
      form_set_error('', t('Unable to add this event as it does not provide all variables utilized by the @plugin <a href="!url">%label</a>.', $args));
    }
  }
}

/**
 * Submit the event configuration.
 */
function rules_ui_add_event_submit($form, &$form_state) {
  if (!empty($form_state['values']['event'])) {
    $rules_config = $form_state['rules_config'];
    $rules_config->save();
    drupal_set_message(t('Added event to rule %label', array('%label' => $rules_config->label())));
  }
}

/**
 * Form to remove a event from a rule.
 */
function rules_ui_remove_event($form, &$form_state, $rules_config, $event, $base_path) {
  RulesPluginUI::$basePath = $base_path;
  $form_state += array('rules_config' => $rules_config, 'rules_event' => $event);
  $events = rules_fetch_data('event_info');
  $event_label = $events[$event]['label'];
  $confirm_question = t('Are you sure you want to remove the event %event from the %plugin %label?', array('%plugin' => $rules_config->plugin(), '%label' => $rules_config->label(), '%event' => $event_label));
  return confirm_form($form, $confirm_question, RulesPluginUI::path($rules_config->name), t('This action cannot be undone.'), t('Remove'), t('Cancel'));
}

/**
 * Validate the event configuration.
 */
function rules_ui_remove_event_validate($form, &$form_state) {
  $rules_config = $form_state['rules_config'];
  $rules_config->removeEvent($form_state['rules_event']);
  try {
    $rules_config->integrityCheck();
  }
  catch (RulesException $e) {
    $args = array(
      '@plugin' => $e->element->plugin(),
      '%label' => $e->element->label(),
      '!url' => url(RulesPluginUI::path($form_state['rules_config']->name, 'edit', $e->element)),
    );
    form_set_error('', t('Unable to remove the event as some of its provided variables are utilized by the @plugin <a href="!url">%label</a>.', $args));
  }
}

/**
 * Submit the event configuration.
 */
function rules_ui_remove_event_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    $rules_config = $form_state['rules_config'];
    $rules_config->save();
    $form_state['redirect'] = RulesPluginUI::path($rules_config->name);
    drupal_set_message(t('Event %event was removed from %plugin %label', array('%event' => $form_state['rules_event'], '%label' => $rules_config->label(), '%plugin' => $rules_config->plugin())));
  }
}

/**
 * FAPI process callback for the data selection widget.
 * This finalises the auto completion callback path by appending the form build
 * id.
 */
function rules_data_selection_process($element, &$form_state, $form) {
  $element['#autocomplete_path'] .= '/' . $form['#build_id'];
  // Workaround for problems with jquery css in seven theme.
  if ($GLOBALS['theme'] == 'seven') {
    drupal_add_css(drupal_get_path('module', 'rules') . '/ui/rules.ui.seven.css');
  }
  $form_state['cache'] = TRUE;
  return $element;
}

/**
 * Autocomplete data selection results.
 */
function rules_ui_form_data_selection_auto_completion($parameter, $form_build_id, $string = '') {
  // Get the form and its state from the cache to get the currently edited
  // or created element.
  $form_state = form_state_defaults();
  $form = form_get_cache($form_build_id, $form_state);
  if (!isset($form_state['rules_element'])) {
    return;
  }
  $element = $form_state['rules_element'];

  $params = $element->pluginParameterInfo();
  $matches = array();
  if (isset($params[$parameter])) {
    $parts = explode(':', $string);
    // Remove the last part as it might be unfinished.
    $last_part = array_pop($parts);
    $selector = implode(':', $parts);

    // Start with the partly given selector or from scratch.
    $result = array();
    if ($selector && $wrapper = $element->applyDataSelector($selector)) {
      $result = RulesData::matchingDataSelector($wrapper, $params[$parameter], $selector . ':', 0);
    }
    elseif (!$selector) {
      $result = RulesData::matchingDataSelector($element->availableVariables(), $params[$parameter], '', 1);
    }

    foreach ($result as $selector => $info) {
      // If we have an uncomplete last part, take it into account now.
      $attributes = array();
      if (!$last_part || strpos($selector, $string) === 0) {
        $attributes['class'][] = 'rules-dsac-item';
        $attributes['title'] = isset($info['description']) ? check_plain($info['description']) : '';
        if ($selector[strlen($selector) - 1] == ':') {
          $attributes['class'][] = 'rules-dsac-group';
          $text = '> ' . check_plain($selector) . '... (' . check_plain($info['label']) . ')';
        }
        else {
          $text = check_plain($selector) . ' (' . check_plain($info['label']) . ')';
        }
        $matches[$selector] = "<div" . drupal_attributes($attributes) . ">$text</div";
      }
    }
  }
  drupal_json_output($matches);
}


/**
 * FAPI validation of an integer element. Copy of the private function
 * _element_validate_integer().
 */
function rules_ui_element_integer_validate($element, &$form_state) {;
  $value = $element['#value'];
  if ($value !== '' && (!is_numeric($value) || intval($value) != $value)) {
    form_error($element, t('%name must be an integer.', array('%name' => isset($element['#title']) ? $element['#title'] : t('Element'))));
  }
}

/**
 * FAPI validation of a decimal element. Improved version of the private
 * function _element_validate_number().
 */
function rules_ui_element_decimal_validate($element, &$form_state) {
  // Substitute the decimal separator ",".
  $value = strtr($element['#value'], ',', '.');
  if ($value != '' && !is_numeric($value)) {
    form_error($element, t('%name must be a number.', array('%name' => $element['#title'])));
  }
  elseif ($value != $element['#value']) {
    form_set_value($element, $value, $form_state);
  }
}

/**
 * FAPI validation of a date element. Makes sure the specified date format is
 * correct and converts date values specifiy a fixed (= non relative) date to
 * a timestamp. Relative dates are handled by the date input evaluator.
 */
function rules_ui_element_date_validate($element, &$form_state) {
  $value = $element['#value'];
  if ($value == '' || (is_numeric($value) && intval($value) == $value)) {
    // The value is a timestamp.
    return;
  }
  elseif (is_string($value) && RulesDateInputEvaluator::gmstrtotime($value) === FALSE) {
    form_error($element, t('Wrong date format. Specify the date in the format %format.', array('%format' => gmdate('Y-m-d H:i:s', time() + 86400))));
  }
  elseif (is_string($value) && RulesDateInputEvaluator::isFixedDateString($value)) {
    // As the date string specifies a fixed format, we can convert it now.
    $value = RulesDateInputEvaluator::gmstrtotime($value);
    form_set_value($element, $value, $form_state);
  }
}

/**
 * FAPI process callback for the duration element type.
 */
function rules_ui_element_duration_process($element, &$form_state) {
  $element['value'] = array(
    '#type' => 'textfield',
    '#size' => 8,
    '#element_validate' => array('rules_ui_element_integer_validate'),
    '#default_value' => $element['#default_value'],
    '#required' => !empty($element['#required']),
  );
  $element['multiplier'] = array(
    '#type' => 'select',
    '#options' => rules_ui_element_duration_multipliers(),
    '#default_value' => 1,
  );

  // Put the child elements in a container-inline div.
  $element['value']['#prefix'] = '<div class="rules-duration container-inline">';
  $element['multiplier']['#suffix'] = '</div>';

  // Set an appropriate multiplier.
  foreach (array_keys(rules_ui_element_duration_multipliers()) as $m) {
    if ($element['value']['#default_value'] % $m == 0) {
      $element['multiplier']['#default_value'] = $m;
    }
  }
  // Divide value by the multiplier, so the display is correct.
  $element['value']['#default_value'] /= $element['multiplier']['#default_value'];
  return $element;
}

/**
 * Defines possible duration multiplier.
 */
function rules_ui_element_duration_multipliers() {
  return array(
    1 => t('seconds'),
    60 => t('minutes'),
    3600 => t('hours'),
    86400 => t('days'),
  );
}

/**
 * Helper function to determine the value for a rules duration form
 * element.
 */
function rules_ui_element_duration_value($element, $input = FALSE) {
  // This runs before child elements are processed, so we cannot calculate the
  // value here. But we have to make sure the value is an array, so the form
  // API is able to proccess the children to set their values in the array. Thus
  // once the form API has finished processing the element, the value is an
  // array containing the child element values. Then finally the after build
  // callback converts it back to the numeric value and sets that.
  return array();
}

/**
 * FAPI after build callback for the duration parameter type form.
 * Fixes up the form value by applying the multiplier.
 */
function rules_ui_element_duration_after_build($element, &$form_state) {
  $element['#value'] = $element['value']['#value'] * $element['multiplier']['#value'];
  form_set_value($element, $element['#value'], $form_state);
  return $element;
}

/**
 * FAPI after build callback for specifying a list of values. Turns the textual
 * value in an array.
 */
function rules_ui_list_textarea_after_build($element, &$form_state) {
  $element['#value'] = explode("\n", $element['#value']);
  form_set_value($element, $element['#value'], $form_state);
  return $element;
}

/**
 * FAPI pre render callback. Turns the value back to a string for rendering.
 */
function rules_ui_list_textarea_pre_render($element) {
  $element['#value'] = implode("\n", $element['#value']);
  return $element;
}

/**
 * FAPI callback to validate a list of integers.
 */
function rules_ui_element_integer_list_validate($element, &$form_state) {
  foreach ($element['#value'] as $value) {
    if ($value !== '' && (!is_numeric($value) || intval($value) != $value)) {
      form_error($element, t('Each line of %name must be an integer.', array('%name' => $element['#title'])));
    }
  }
}

/**
 * FAPI callback to validate a machine readable name.
 */
function rules_ui_element_machine_name_validate($element, &$form_state) {
  if ($element['#value'] && !preg_match('!^[a-z0-9_]+$!', $element['#value'])) {
    form_error($element, t('Machine-readable names must contain only lowercase letters, numbers, and underscores.'));
  }
}

/**
 * FAPI callback to validate the form for editing variable info.
 * @see RulesPluginUI::getVariableForm()
 */
function rules_ui_element_variable_form_validate($elements, &$form_state) {
  $names = array();
  foreach (element_children($elements['items']) as $item_key) {
    $element = &$elements['items'][$item_key];
    if ($element['name']['#value'] || $element['type']['#value'] || $element['label']['#value']) {
      foreach (array('name' => t('Machine name'), 'label' => t('Label'), 'type' => t('Data type')) as $key => $title) {
        if (!$element[$key]['#value']) {
          form_error($element[$key], t('!name field is required.', array('!name' => $title)));
        }
      }
      if (isset($names[$element['name']['#value']])) {
        form_error($element['name'], t('The machine-readable name %name is already taken.', array('%name' => $element['name']['#value'])));
      }
      $names[$element['name']['#value']] = TRUE;
    }
  }
}

/**
 * Helper to sort elements by their 'weight' key.
 */
function rules_element_sort_helper($a, $b) {
  $a += array('weight' => 0);
  $b += array('weight' => 0);
  if ($a['weight'] == $b['weight']) {
    return 0;
  }
  return ($a['weight'] < $b['weight']) ? -1 : 1;
}

/**
 * Form after build handler to set the static base path.
 *
 * @see RulesPluginUI::formDefaults()
 */
function rules_form_after_build_restore_base_path($form, &$form_state) {
  if (isset($form_state['_rules_base_path'])) {
    RulesPluginUI::$basePath = $form_state['_rules_base_path'];
  }
  return $form;
}
