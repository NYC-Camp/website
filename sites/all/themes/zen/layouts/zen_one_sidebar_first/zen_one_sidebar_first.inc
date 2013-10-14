<?php
// Plugin definition
$plugin = array(
  'title'       => t('One sidebar before content'),
  'icon'        => 'zen-one-sidebar-first.png',
  'category'    => t('Columns: 2'),
  'theme'       => 'zen_one_sidebar_first',
  'css'         => 'zen-one-sidebar-first.css',
  'admin theme' => 'zen_one_sidebar_first_admin',
  'admin css'   => 'zen-one-sidebar-first-admin.css',
  'regions'     => array(
    'content'       => t('Content'),
    'sidebar_first' => t('Sidebar'),
  ),
);
