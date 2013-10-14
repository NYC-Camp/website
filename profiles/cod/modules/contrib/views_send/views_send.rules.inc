<?php

/**
* Implementation of hook_rules_event_info().
*/
function views_send_rules_event_info() {
  $defaults = array(
    'group' => t('Views Send'),
  );
  return array(
    'views_send_email_sent' => $defaults + array(
      'label' => t('After sending an individual email'),
      'variables' => array(
        'views_send_email_message' => array(
          'type' => 'views_send_email_message',
          'label' => t('email message'),
          'description' => t('All information about the message.')
        ),
      ),
    ),
    'views_send_all_email_added_to_spool' => $defaults + array(
      'label' => t('After adding all emails to the spool'),
      'variables' => array(
        'views_send_email_count' => array(
          'type' => 'integer',
          'label' => t('message count'),
          'description' => t('The number of messages added to the spool.')
        ),
      ),
    ),
    'views_send_email_added_to_spool' => $defaults + array(
      'label' => t('After adding an individual email to the spool'),
      'variables' => array(
        'views_send_email_message' => array(
          'type' => 'views_send_email_message',
          'label' => t('email message'),
          'description' => t('All information about the message.')
        ),
      ),
    ),
  );
}

/**
* Implementation of hook_rules_data_info().
*/
function views_send_rules_data_info() {
  $types['views_send_email_message'] = array(
    'label' => t('Views Send email message'), 
    'group' => t('Views Send'), 
    'wrap' => TRUE, 
    'property info' => array(
      'uid' => array(
        'type' => 'integer', 
        'label' => t('User ID'),
      ), 
      'timestamp' => array(
        'type' => 'integer', 
        'label' => t('Timestamp'),
      ), 
      'from_name' => array(
        'type' => 'text', 
        'label' => t('Sender\'s name'), 
      ),
      'from_mail' => array(
        'type' => 'text', 
        'label' => t('Sender\'s e-mail'), 
      ),
      'to_name' => array(
        'type' => 'text', 
        'label' => t('Recipient\'s name'), 
      ),
      'to_mail' => array(
        'type' => 'text', 
        'label' => t('Recipient\'s e-mail'), 
      ),
      'subject' => array(
        'type' => 'text', 
        'label' => t('E-mail subject'), 
      ),
      'body' => array(
        'type' => 'text', 
        'label' => t('E-mail body'), 
      ),
      'headers' => array(
        'type' => 'text', 
        'label' => t('E-mail headers (serialized)'), 
      ),
    ),
  );

  return $types;
}
