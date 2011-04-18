<?php

if (!class_exists('purl_confirm_popup_path')) {

  class purl_confirm_popup_path extends purl_path implements purl_processor {

    public function method() {
      return 'purl_confirm_popup_path';
    }

    public function adjust(&$value, $item, &$q) {
      // do nothing. this is on purpose.
    }

    public function parse($valid_values, $q) {
      // just return something so we get added to the active list
      return array(new purl_path_element($this, $q, '', ''));
    }

    public function rewrite(&$path, &$options, $element) {
      // the processor needs to be added on page load, in purl_get_normal_path,
      // or it requires some options to be set on the links themselves
      // in order to be run.
      // so i gotta figure out how to make this attach itself in purl_get_normal_path?
      if (!module_exists('confirm_popup')) return;

      if (in_array(_menu_find_router_path($path), _confirm_popup_get_confirm_paths())) {
      	ctools_include('ajax');
      	ctools_include('modal');
      	ctools_modal_add_js();
      	_confirm_popup_modal_settings();

        $path = 'confirm_popup/nojs/'.$path;

        // this doesn't work as expected.
        // the options array isn't passed by reference up the call stack
        // to where the <a> tag is built.
        // i need to find some place else to do this.

        // theme somethingorother or javascript?
        // ended up doing it in a preprocess_page hook
        $classes = explode(' ',$options['attributes']['class']);
        if (!in_array('ctools-use-modal', $classes)) {
          $classes[] = 'ctools-use-modal';
          $classes[] = 'ctools-modal-confirm-popup-modal';
        }
        $options['attributes']['class'] = implode(' ', $classes);
      }
    }
  }
}