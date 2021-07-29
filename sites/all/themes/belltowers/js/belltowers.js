/**
 * @file
 * Javascript functions used by the bootstrap_agency theme.
 */

(function ($) {
  Drupal.behaviors.agencyTheme = {
    attach: function (context) {
      // Replace cbpAnimatedHeader.js.
      $(window).scroll(function () {
          if ($(this).scrollTop() > 200) {
              $('.navbar-default').addClass('navbar-shrink');
          }
          else {
              $('.navbar-default').removeClass('navbar-shrink');
          }
      });

      // Hide the responsive menu when clicking in a menu item.
      $('#navbar').find('.navbar-collapse ul li:not(.dropdown) a').click(function () {
          $('#navbar button.navbar-toggle:visible').click();
      });
    }
  };
  
  // Collapse Navbar
    var navbarCollapse = function () {
        if ($("#navbar").offset().top > 100) {
            $("#navbar").addClass("navbar-shrink");
        } else {
            $("#navbar").removeClass("navbar-shrink");
        }
    };
    // Collapse now if page is not at top
    navbarCollapse();
    // Collapse the navbar when page is scrolled
    $(window).scroll(navbarCollapse);
	
	// scroll top
    $(window).scroll(function() {
		if($(this).scrollTop() != 0) {
			$("#toTop").fadeIn();
		} else {
			$("#toTop").fadeOut();
		}
	});

	$("#toTop").click(function() {
		$("body,html").animate({scrollTop:0},800);
	});
	
})(jQuery);
