<?php

$plugin = array(
  'form' => 'mcircc_import_display_name_form',
  'validate' => 'mcircc_import_display_name_validate',
  'callback' => 'mcircc_import_display_name_callback',
  'name' => 'MCIRCC Import User Name',
  'multi' => 'direct',
  'category' => 'MCIRCC',
);

function mcircc_import_display_name_form($importer, $element_key, $settings) {
  $form = array();
  return $form;
}

function mcircc_import_display_name_validate(&$settings) {
}

function mcircc_import_display_name_callback($result, $item_key, $element_key, &$field, $settings, $source) {

  /*dpm('result');
  dpm($result);
  dpm('item_key');
  dpm($item_key);
  dpm('element_key');
  dpm($element_key);
  dpm('field');
  dpm($field);
  dpm('settings');
  dpm($settings);
  dpm('source');
  dpm($source);*/

  $current_item = $result->current_item;
  /*dpm('current item');
  dpm($current_item);*/
  
  // Map the first name and last name onto the display name field.
  $field = $current_item['first name'] . ' ' .
      $current_item['last name'];
}

