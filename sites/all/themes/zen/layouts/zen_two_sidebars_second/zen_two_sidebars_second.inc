<?php
// Plugin definition
$plugin = array(
  'title'       => t('Two sidebars after content'),
  'icon'        => 'zen-two-sidebars-second.png',
  'category'    => t('Columns: 3'),
  'theme'       => 'zen_two_sidebars_second',
  'css'         => 'zen-two-sidebars-second.css',
  'admin theme' => 'zen_two_sidebars_second_admin',
  'admin css'   => 'zen-two-sidebars-second-admin.css',
  'regions'     => array(
    'content'        => t('Content'),
    'sidebar_first'  => t('First sidebar'),
    'sidebar_second' => t('Second sidebar'),
  ),
);
