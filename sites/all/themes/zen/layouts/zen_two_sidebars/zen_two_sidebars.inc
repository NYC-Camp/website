<?php
// Plugin definition
$plugin = array(
  'title'       => t('Two sidebars with content'),
  'icon'        => 'zen-two-sidebars.png',
  'category'    => t('Columns: 3'),
  'theme'       => 'zen_two_sidebars',
  'css'         => 'zen-two-sidebars.css',
  'admin theme' => 'zen_two_sidebars_admin',
  'admin css'   => 'zen-two-sidebars-admin.css',
  'regions'     => array(
    'content'        => t('Content'),
    'sidebar_first'  => t('First sidebar'),
    'sidebar_second' => t('Second sidebar'),
  ),
);
