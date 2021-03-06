<?php
// $Id: rules.plugins.inc,v 1.1.2.3 2011/01/04 13:08:35 fago Exp $

/**
 * @file Contains plugin info and implementations not needed for rule evaluation.
 */


/**
 * Implements a rules action.
 */
class RulesAction extends RulesAbstractPlugin implements RulesActionInterface {

  protected $itemName = 'action';

  /**
   * Execute the callback and update/save data as specified by the action.
   */
  protected function executeCallback(array $args, RulesState $state = NULL) {
    rules_log('Evaluating the action %name.', array('%name' => $this->elementName));
    $return = $this->__call('execute', empty($this->info['named parameter']) ? $args : array($args));
    // Get the (partially) wrapped arguments.
    $args = $state->currentArguments;

    if (is_array($return)) {
      foreach ($return as $name => $data) {
        // Update the data value using the wrapper.
        if (isset($args[$name]) && $args[$name] instanceof EntityMetadataWrapper) {
          try {
            $args[$name]->set($data);
          }
          catch (EntityMetadataWrapperException $e) {
            throw new RulesException('Unable to update the argument for parameter %name: %error', array('%name' => $name, '%error' => $e->getMessage()), $this);
          }
        }
        elseif (isset($args[$name])) {
          $state->variables[$name] = $data;
        }
        // Add provided variables.
        elseif (!$state->varInfo($name) && isset($this->info['provides'][$name])) {
          $var_name = isset($this->settings[$name . ':var']) ? $this->settings[$name . ':var'] : $name;
          $state->addVariable($var_name, $data, $this->info['provides'][$name]);
          rules_log('Added the provided variable %name of type %type', array('%name' => $var_name, '%type' => $this->info['provides'][$name]['type']));
          if (!empty($this->info['provides'][$name]['save']) && $state->variables[$name] instanceof EntityDrupalWrapper) {
            $state->saveChanges($var_name, $state->variables[$name]);
          }
        }
      }
    }
    // Save parameters as defined in the parameter info.
    if ($return !== FALSE) {
      foreach ($this->info['parameter'] as $name => $info) {
        if (!empty($info['save']) && $args[$name] instanceof EntityMetadataWrapper) {
          if (isset($this->settings[$name . ':select'])) {
            $state->saveChanges($this->settings[$name . ':select'], $args[$name]);
          }
          else {
            // Wrapper has been configured via direct input, so just save.
            rules_log('Saved argument of type %type for parameter %name.', array('%name' => $name, '%type' => $args[$name]->type()));
            $args[$name]->save();
          }
        }
      }
    }
  }
}

/**
 * Implements a rules condition.
 */
class RulesCondition extends RulesAbstractPlugin implements RulesConditionInterface {

  protected $itemName = 'condition';
  protected $negate = FALSE;

  public function providesVariables() {
    return array();
  }

  public function negate($negate = TRUE) {
    $this->negate = (bool) $negate;
    return $this;
  }

  public function isNegated() {
    return $this->negate;
  }

  protected function executeCallback(array $args, RulesState $state = NULL) {
    $return = (bool) $this->__call('execute', empty($this->info['named parameter']) ? $args : array($args));
    rules_log('The condition %name evaluated to %bool', array('%name' => $this->elementName, '%bool' => $return ? 'TRUE' : 'FALSE'));
    return $this->negate ? !$return : $return;
  }

  public function __sleep() {
    return parent::__sleep() + array('negate' => 'negate');
  }

  /**
   * Just return the boolean result.
   */
  protected function returnVariables(RulesState $state, $result = NULL) {
    return $result;
  }

  public function export($php = FALSE) {
    $not = $this->negate ? 'NOT ' : '';
    $export = $this->exportSettings();
    // Abbreviate the export making "USING" implicit.
    $export = array($not . $this->elementName => $export['USING']);
    return $this->isRoot() ? $this->returnExport($export, $php) : $export;
  }

  public function label() {
    $label = parent::label();
    return $this->negate ? t('NOT @condition', array('@condition' => $label)) : $label;
  }
}

/**
 * An actual rule.
 * Note: A rule also implements the RulesActionInterface (inherited).
 */
class Rule extends RulesActionContainer {

  protected $conditions = NULL;
  protected $itemName = 'rule';

  public $label = 'unlabeled';

  public function __construct($variables = array(), $providesVars = array()) {
    parent::__construct($variables, $providesVars);

    // Initialize the conditions container.
    if (!isset($this->conditions)) {
      $this->conditions = rules_and();
      // Don't use setParent() to avoid having it added to the children.
      $this->conditions->parent = $this;
    }
  }

  /**
   * Get an iterator over all contained conditions. Note that this iterator also
   * implements the ArrayAcces interface.
   *
   * @return RulesRecursiveElementIterator
   */
  public function conditions() {
    return $this->conditions->getIterator();
  }

  /**
   * Returns the "And" condition container, which contains all conditions of
   * this rule.
   *
   * @return RulesAnd
   */
  public function conditionContainer() {
    return $this->conditions;
  }

  public function __sleep() {
    return parent::__sleep() + drupal_map_assoc(array('conditions', 'label'));
  }

  /**
   * Get an iterator over all contained actions. Note that this iterator also
   * implements the ArrayAcces interface.
   *
   * @return RulesRecursiveElementIterator
   */
  public function actions() {
    return parent::getIterator();
  }

  /**
   * Add a condition. Pass either an instance of the RulesConditionInterface
   * or the arguments as needed by rules_condition().
   *
   * @return Rule
   *   Returns $this to support chained usage.
   */
  public function condition($name, $settings = array()) {
    $this->conditions->condition($name, $settings);
    return $this;
  }

  public function sortChildren($deep = FALSE) {
    $this->conditions->sortChildren($deep);
    parent::sortChildren($deep);
  }

  public function evaluate(RulesState $state) {
    rules_log('Evaluating rule %label.', array('%label' => $this->label));
    if ($this->conditions->evaluate($state)) {
      parent::evaluate($state);
    }
  }

  /**
   * Fires the rule, i.e. evaluates the rule without checking its conditions.
   *
   * @see RulesPlugin::evaluate()
   */
  public function fire(RulesState $state) {
    rules_log('Firing rule %label.', array('%label' => $this->label));
    parent::evaluate($state);
  }

  public function integrityCheck() {
    $this->conditions->integrityCheck();
    return parent::integrityCheck();
  }

  public function access() {
    return (!isset($this->conditions) || $this->conditions->access()) && parent::access();
  }

  public function dependencies() {
    return array_keys(array_flip($this->conditions->dependencies()) + array_flip(parent::dependencies()));
  }

  public function destroy() {
    $this->conditions->destroy();
    parent::destroy();
  }

  /**
   * @return RulesRecursiveElementIterator
   */
  public function getIterator() {
    $array = array_merge(array($this->conditions), $this->children);
    return new RulesRecursiveElementIterator($array);
  }

  protected function stateVariables($element = NULL) {
    // Don't add in provided action variables for the conditions.
    if (isset($element) && $element === $this->conditions) {
      return $this->availableVariables();
    }
    $vars = parent::stateVariables($element);
    // Take variable info assertions of conditions into account.
    if ($assertions = $this->conditions->variableInfoAssertions()) {
      $vars = RulesData::addMetadataAssertions($vars, $assertions);
    }
    return $vars;
  }

  protected function exportChildren($key = NULL) {
    $export = array();
    if ($this->conditions->children) {
      $export = $this->conditions->exportChildren('IF');
    }
    return $export + parent::exportChildren('DO');
  }

  public function __clone() {
    parent::__clone();
    $this->conditions = clone $this->conditions;
    $this->conditions->parent = $this;
  }

  /**
   * Rules may not provided any variable info assertions, as Rules are only
   * conditionally executed.
   */
  protected function variableInfoAssertions() {
    return array();
  }
}

/**
 * Represents rules getting triggered by events.
 */
class RulesReactionRule extends Rule implements RulesTriggerableInterface {

  protected $itemName = 'reaction rule';
  protected $events = array();

  /**
   * Returns the array of events associated with that Rule.
   */
  public function &events() {
    return $this->events;
  }

  /**
   * Removes an event from the rule configuration.
   *
   * @param $event
   *   The name of the event to remove.
   * @return RulesReactionRule
   */
  public function removeEvent($event) {
    if (($id = array_search($event, $this->events)) !== FALSE) {
      unset($this->events[$id]);
    }
    return $this;
  }

  /**
   * @return RulesReactionRule
   */
  public function event($event) {
    $this->events[] = $event;
    return $this;
  }

  /**
   * Reaction rules can't add variables to the parent scope, so clone $state.
   */
  public function evaluate(RulesState $state) {
    // Implement recursion prevention for reaction rules.
    if ($state->isBlocked($this)) {
      return rules_log('Not evaluating @plugin %label to prevent recursion.', array('%label' => $this->label(), '@plugin' => $this->plugin()), RulesLog::INFO);
    }
    $state->block($this);
    $copy = clone $state;
    parent::evaluate($copy);
    $state->unblock($this);
  }

  public function access() {
    $event_info = rules_fetch_data('event_info');
    foreach ($this->events as $event) {
      if (!empty($event_info[$event]['access callback']) && !call_user_func($event_info[$event]['access callback'], 'event', $event)) {
        return FALSE;
      }
    }
    return parent::access();
  }

  public function dependencies() {
    $modules = array_flip(parent::dependencies());
    $event_info = rules_fetch_data('event_info');
    foreach ($this->events as $event) {
      if (isset($event_info[$event]['module'])) {
        $modules[$event_info[$event]['module']] = TRUE;
      }
    }
    return array_keys($modules);
  }

  public function providesVariables() {
    return array();
  }

  public function parameterInfo($optional = FALSE) {
    // If executed directly, all variables as defined by the event need to
    // be passed.
    return rules_filter_array($this->availableVariables(), 'handler', FALSE);
  }

  public function availableVariables() {
    if (isset($this->parent)) {
      // Return the event variables provided by the event set, once cached.
      return $this->parent->stateVariables();
    }
    //TODO: Once we have event_info caching make use of it.
    $event_info = rules_fetch_data('event_info');
    $events = array_intersect($this->events, array_keys($event_info));
    foreach ($events as $event) {
      $event_info[$event] += array('variables' => array());
      if (!isset($vars)) {
        $vars = $event_info[$event]['variables'];
      }
      else {
        $vars = array_intersect_key($vars, $event_info[$event]['variables']);
      }
    }
    return parent::availableVariables() + (isset($vars) ? $vars : array());
  }

  public function __sleep() {
    return parent::__sleep() + drupal_map_assoc(array('events'));
  }

  protected function exportChildren($key = 'ON') {
    $export[$key] = array_values($this->events);
    return $export + parent::exportChildren();
  }
}

/**
 * A logical AND.
 */
class RulesAnd extends RulesConditionContainer {

  protected $itemName = 'and';

  public function evaluate(RulesState $state) {
    foreach ($this->children as $condition) {
      if (!$condition->evaluate($state)) {
        rules_log('AND evaluated to FALSE.');
        return $this->negate;
      }
    }
    rules_log('AND evaluated to TRUE.');
    return !$this->negate;
  }

  public function label() {
    return !empty($this->label) ? $this->label : ($this->negate ? t('NOT AND') : t('AND'));
  }
}

/**
 * A logical OR.
 */
class RulesOr extends RulesConditionContainer {

  protected $itemName = 'or';

  public function evaluate(RulesState $state) {
    foreach ($this->children as $condition) {
      if ($condition->evaluate($state)) {
        rules_log('OR evaluated to TRUE.');
        return !$this->negate;
      }
    }
    rules_log('OR evaluated to FALSE.');
    return $this->negate;
  }

  public function label() {
    return !empty($this->label) ? $this->label : ($this->negate ? t('NOT OR') : t('OR'));
  }

  /**
   * Overridden to exclude all variable assertions as in an OR we cannot assert
   * the children are successfully evaluated.
   */
  protected function stateVariables($element = NULL) {
    $vars = $this->availableVariables();
    if (isset($element)) {
      // Add in variables provided by siblings executed before the element.
      foreach ($this->children as $child) {
        if ($child === $element) {
          break;
        }
        $vars += $child->providesVariables();
      }
    }
    return $vars;
  }
}

/**
 * A loop element.
 */
class RulesLoop extends RulesActionContainer {

  protected $itemName = 'loop';

  public function __construct($settings = array(), $variables = NULL) {
    $this->setUp();
    $this->settings = (array) $settings + array(
      'item:var' => 'list-item',
      'item:label' => t('Current list item'),
    );
    if (!empty($variables)) {
      $this->info['variables'] = $variables;
    }
  }

  public function pluginParameterInfo() {
    $info['list'] = array(
      'type' => 'list',
      'restriction' => 'selector',
      'label' => t('List'),
      'description' => t('The list to loop over.'),
    );
    return $info;
  }

  public function integrityCheck() {
    parent::integrityCheck();
    $this->checkVarName($this->settings['item:var']);
  }

  protected function listItemType() {
    if (!isset($this->settings['item:type'])) {
      $info = $this->getArgumentInfo('list');
      $this->settings['item:type'] = isset($info['type']) ? entity_property_list_extract_type($info['type']) : 'unknown';
    }
    return $this->settings['item:type'];
  }

  protected function listItemInfo() {
    return array(
      'type' => $this->listItemType(),
      'label' => $this->settings['item:label'],
    );
  }

  public function evaluate(RulesState $state) {
    $param_info = $this->pluginParameterInfo();
    $list = $this->getArgument('list', $param_info['list'], $state);
    $item_var_info = $this->listItemInfo();
    $item_var_name = $this->settings['item:var'];

    if (isset($this->settings['list:select'])) {
      rules_log('Looping over the list items of %selector', array('%selector' => $this->settings['list:select']));
    }

    // Loop over the list and evaluate the children for each list item.
    foreach ($list as $key => $item) {
      // Use a separate state so variables are available in the loop only.
      $state2 = clone $state;
      $state2->addVariable($item_var_name, $list[$key], $item_var_info);
      parent::evaluate($state2);
    }
  }

  protected function stateVariables($element = NULL) {
    return array($this->settings['item:var'] => $this->listItemInfo()) + parent::stateVariables($element);
  }

  public function label() {
    return !empty($this->label) ? $this->label : t('Loop');
  }

  protected function exportChildren($key = 'LOOP OVER') {
    return parent::exportChildren($key);
  }
}

/**
 * An action set component.
 */
class RulesActionSet extends RulesActionContainer {

  protected $itemName = 'action set';

}

/**
 * A set of rules to execute upon defined variables.
 */
class RulesRuleSet extends RulesActionContainer {

  protected $itemName = 'rule set';

  /**
   * @return RulesRuleSet
   */
  public function rule($rule) {
    return $this->action($rule);
  }

  protected function exportChildren($key = 'RULES') {
    return parent::exportChildren($key);
  }
}

/**
 * This class is used for caching the rules to be evaluated per event.
 */
class RulesEventSet extends RulesRuleSet {

  protected $itemName = 'event set';
  // Event sets may recurse as we block recursions on rule-level.
  public $recursion = TRUE;

  public function __construct($info = array()) {
    $this->setup();
    $this->info = $info;
  }

  public function executeByArgs($args = array()) {
    rules_log('Reacting on event %label.', array('%label' => $this->info['label']), RulesLog::INFO, TRUE);
    $state = $this->setUpState($args);
    module_invoke_all('rules_config_execute', $this);
    $this->evaluate($state);
    $state->cleanUp($this);
    rules_log('Finished reacting on event %label.', array('%label' => $this->info['label']), RulesLog::INFO, FALSE);
  }

  public function rebuildCache(&$itemInfo, &$cache) {
    parent::rebuildCache($itemInfo, $cache);
    // Set up the per-event cache.
    $events = rules_fetch_data('event_info');
    $empty = array();

    foreach ($events as $name => $info) {
      $info += array(
        'variables' => isset($info['arguments']) ? $info['arguments'] : array(),
      );
      // Add all rules associated with this event to an EventSet for caching.
      if ($rules = rules_config_load_multiple(FALSE, array('event' => $name, 'active' => TRUE))) {
        $event = new RulesEventSet($info);
        $event->name = $name;
        foreach ($rules as $rule) {
          // Clone the rule to avoid modules getting the changed version from
          // the static cache.
          $event->rule(clone $rule);
        }
        $event->optimize();
        // Allow modules to alter the cached event set.
        drupal_alter('rules_event_set', $name, $event);
        cache_set('event_' . $name, $event, 'cache_rules');
        $event->destroy();
      }
      else {
        $empty[] = $name;
      }
    }
    // Cache a list of empty sets so we can use it to speed up later calls.
    // See rules_get_event_set().
    variable_set('rules_empty_sets', array_flip($empty));
  }

  protected function stateVariables($element = NULL) {
    return $this->availableVariables();
  }
}
