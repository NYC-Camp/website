<?php
// Plugin definition
$plugin = array(
  'title'       => t('One sidebar after content'),
  'icon'        => 'zen-one-sidebar-second.png',
  'category'    => t('Columns: 2'),
  'theme'       => 'zen_one_sidebar_second',
  'css'         => 'zen-one-sidebar-second.css',
  'admin theme' => 'zen_one_sidebar_second_admin',
  'admin css'   => 'zen-one-sidebar-second-admin.css',
  'regions'     => array(
    'content'       => t('Content'),
    'sidebar_first' => t('Sidebar'),
  ),
);
