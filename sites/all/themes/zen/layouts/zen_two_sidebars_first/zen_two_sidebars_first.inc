<?php
// Plugin definition
$plugin = array(
  'title'       => t('Two sidebars before content'),
  'icon'        => 'zen-two-sidebars-first.png',
  'category'    => t('Columns: 3'),
  'theme'       => 'zen_two_sidebars_first',
  'css'         => 'zen-two-sidebars-first.css',
  'admin theme' => 'zen_two_sidebars_first_admin',
  'admin css'   => 'zen-two-sidebars-first-admin.css',
  'regions'     => array(
    'content'        => t('Content'),
    'sidebar_first'  => t('First sidebar'),
    'sidebar_second' => t('Second sidebar'),
  ),
);
