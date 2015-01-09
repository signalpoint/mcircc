<?php

/**
 * The vendor's add customer form.
 */
function mcircc_user_add_form($form, &$form_state) {
  $form['mail'] = array(
    '#type' => 'textfield',
    '#title' => 'E-mail address',
    '#required' => TRUE,
    '#description' => 'Enter the e-mail address of the user.'
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Create new user'
  );
  return $form;
}

/**
 *
 */
function mcircc_user_add_form_validate($form, &$form_state) {
  $mail = $form_state['values']['mail'];
  if (!valid_email_address($mail)) {
    form_set_error('mail', 'You must enter a valid e-mail address!');
  }
  else if ($account = user_load_by_mail($mail)) {
    form_set_error('mail', 'A user with that e-mail address already exists!');
  }
}

/**
 *
 */
function mcircc_user_add_form_submit($form, &$form_state) {

  // Build a user account object.
  $mail = $form_state['values']['mail'];
  $account = new stdClass();
  $account->name = substr($mail, 0, strpos($mail, '@'));
  $account->mail = $mail;
  $account->status = 1;
  $account->roles = array(
    DRUPAL_AUTHENTICATED_RID => 'authenticated user'
  );
  // Make sure user name isn't already taken, if it is generate a random one.
  $query = db_select('users', 'u')
    ->fields('u', array('uid'))
    ->condition('u.name', $account->name)
    ->execute();
  $result = $query->fetchField();
  if ($result) { $account->name .= '-' . user_password(); }
  $account = user_save($account);
  if (!$account) {
    drupal_set_message(
      'There was a problem creating the new account! ' .
      'Please contact us if the problem persists.', 'error'
    );
  }
  else {
    _user_mail_notify('register_admin_created', $account);
    drupal_set_message('Created new account for user, and notified them via e-mail! ' . $mail);
  }

}

