<?php

function cod_events_views_pre_render(&$view) {
  if($view->name == 'cod_events_admin' && $default_event = variable_get('cod_events_default_event', 0)) {
    foreach($view->result AS $rid => $row) {
      if($row->nid == $default_event) {
        $view->result[$rid]->node_title = t('!event (default event)', array('!event' => $view->result[$rid]->node_title));
      }
    }
  }
}