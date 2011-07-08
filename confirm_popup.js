/**
 * 
 */

Drupal.behaviors.confirm_popup = function () {
  Drupal.settings.confirm_popup.links = eval(Drupal.settings.confirm_popup.links);
  var links = $("a");
  var path = Drupal.settings.confirm_popup.base_path;
  $.each(Drupal.settings.confirm_popup.links, function (i, item) {
  	// for every path we check against
  	var frags = item.split("%");
  	var links_t = links;
  	$.each(frags, function (i, item) {
  	  // filter the list of links by the path fragment
  	  links_t = links_t.filter("[href*="+item+"]");
  	});

	links_t.each(function (i, item) {
	  // add in the necessary path bits and classes
      if (item.className.indexOf("ctools-use-dialog") == -1) {
    	if (item.href.indexOf(Drupal.settings.confirm_popup.base_domain) != -1){
    	  var base_path = Drupal.settings.confirm_popup.base_domain+'/'+path;
    	  item.href = item.href.replace(base_path, base_path+"confirm_popup/nojs/");
    	}
    	else if (item.href.indexOf("http:") != -1) { 
	      if (path == "/") {
	        item.href = "confirm_popup/nojs/"+item.href;
	      }
    	}
    	else {
    	  item.href = item.href.replace(path, path+"confirm_popup/nojs/");
        }
        item.className += " ctools-use-dialog ctools-modal-confirm-popup-modal";
	  }
	});
  });

  // tell ctools to go. We don\'t know if ctools has already processed or not.
  Drupal.behaviors.Dialog();
}