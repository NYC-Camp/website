<?php

/**
 * @file
 * Provides a batched rule set component to rules.
 *
 * This is based upon rules core plugin 'rule set'.
 * @See rules.plugins.inc
 */

/**
 * Implements hook_rules_rules_plugin_info().
 *
 * Declares neccessary meta-data about the this plugin.
 */
function rb_batch_rules_plugin_info() {
  return array(
    'batched rule set' => array(
      'label' => t('Batched rule set'),
      'module' => 'rb_batch',
      'class' => 'BatchedRuleSet',
      'component' => TRUE,
      'embeddable' => FALSE,
      'extenders' => array(
        'RulesPluginUIInterface' => array(
          'class' => 'BatchedRuleSetUI',
        ),
      ),
    ),
  );
}

/**
 * A set of rules to execute upon defined variables, within the possibility
 * of executing each rule as batch operation.
 */
class BatchedRuleSet extends RulesRuleSet {
  protected $itemName = 'batched rule set';

  public function evaluate(RulesState $state) {
    rules_log('Taking over %label to batch API.', array('%label' => $this->label), RulesLog::INFO, NULL, TRUE);
    // Take over further evaluation through batch.
    $operations = array();
    // Create an array containing the static operational function
    // and provide them each rule within the initial rules state.
    foreach ($this->children as $rule) {
      $operations[] = array('rb_batch_operation_rule_evaluate', array($rule, $state));
    }
    // This will set the batch to be executed (on the next site).
    batch_set(array('operations' => $operations));
    rules_log('Finished takeover %label.', array('%label' => $this->label), RulesLog::INFO, NULL, FALSE);
  }
}

/**
 * Class defining the UI for the batched rules plugin.
 * Here is not much to do so far, but implementation is needed.
 */
class BatchedRuleSetUI extends RulesRuleSetUI {
  // Override form to hide the variables settings.
  public function form(&$form, &$form_state, $options = array(), $iterator = NULL) {
    // Pass an iterator just iterating over the rules, thus no further child
    // elements will be displayed.
    parent::form($form, $form_state, $options, $this->element->getIterator());
  }
}

/**
 * Implements hook_rules_action_info().
 *
 * Declares meta-data about the action which enables to alter
 * batch API context data on rules runtime.
 */
function rb_batch_rules_action_info() {
  $actions = array();
  $actions['rb_batch_action_batch_context'] = array(
    'label' => t('Alter batch context'),
    'group' => t('Batched Rules'),
    'parameter' => array(
      'batch_context_message' => array(
        'type' => 'text',
        'label' => t('Message'),
        'description' => t("A message shown on progress page after this rule was executed. (Defaults to it's title)"),
      ),
      'batch_context_finished' => array(
        'type' => 'boolean',
        'label' => t('Finished'),
        'description' => t("Wether this rule succeed and is finished. (Will be re-executed otherwise)"),
        'default value' => TRUE,
      ),
    ),
  );
  return $actions;
}

/**
 * Pseudo action to alter batch context data (Message and Finished values).
 */
function rb_batch_action_batch_context($message, $finished) {
  /**
   * We don't need to do anything here, rules will save our arguments
   * to the state object anyway. We will use it later while execution
   * in the batch operations.
   * @see rb_batch.module
   */
}
