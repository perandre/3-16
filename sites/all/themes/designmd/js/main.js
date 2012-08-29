(function($) {
 $(document).ready(function(){
                $('#latest-work').elastislide({
                    imageW 	: 260,
                    margin  : 30                    
                });
            });
			
			
			 $(document).ready(function(){
                $('#testimonial').elastislide({
                    imageW 	: 555,
                    margin  : 30                    
                });
            });
			
			
			$(document).ready(function(){
                $('#newsletters').elastislide({
                    imageW 	: 555,
                    margin      : 30            
                });
            });

})(jQuery);


(function($) {
	
$(document).ready(function(){
    
    $('.features div:last, .newsletters div:last, .about-work > div:last, .team > div:last, .related-post > div:last').addClass('last');
    
    $('a[data-rel]').each(function() {
        $(this).attr('rel', $(this).data('rel'));
    });


 
    
    //prettyPhoto
    $("a[rel^='prettyPhoto']").prettyPhoto();
    
    
    //Portfolio Image Hover
    $('div.border-img a, .gallery li a').css({ opacity: 0 });
    $(".portfolio li, div.border-img:not(.not-hover)").hover(function () {						 
    	$(this).find("img").stop(true, true).animate({ opacity: 0.7 }, 300);
        $(this).find("a.img-view").animate({left: 50+'%', marginLeft: -41+'px', opacity: 1}, 300, 'easeOutQuart');
        $(this).find("a.img-link").animate({right: 50+'%', marginRight: -41+'px', opacity: 1}, 300, 'easeOutQuart');
    }, function() {
    	$(this).find("img").stop(true, true).animate({ opacity: 1 }, 300);
        $(this).find("a.img-view").animate({left: -36+'px', marginLeft: 0, opacity: 0 });
        $(this).find("a.img-link").animate({right:  -36+'px', marginRight: 0, opacity: 0 });
    });
    
    
    //Portfolio Image Hover
    $("img.border-img:not(.not-hover)").hover(function () {						 
    	$(this).stop(true, true).animate({ opacity: 0.7 }, 800);
    }, function() {
    	$(this).stop(true, true).animate({ opacity: 1 }, 800);
    });

    
     //Blog Image Hover
    $(".latest-blog img").hover(function () {						 
    	$(this).stop(true, true).animate({ opacity: 0.7 }, 800);
    }, function() {
    	$(this).stop(true, true).animate({ opacity: 1 }, 800);
    });
    //Portfolio Image Hover
    $("img.border-img:not(.not-hover)").hover(function () {						 
    	$(this).stop(true, true).animate({ opacity: 0.7 }, 800);
    }, function() {
    	$(this).stop(true, true).animate({ opacity: 1 }, 800);
    });

    //Gallery Image Hover
    $(".gallery li").hover(function () {	
        $(this).find("img").stop(true, true).animate({ opacity: 0.7 }, 300);
    	$(this).find("a.img-view").animate({left: 50+'%', marginLeft: -18+'px', opacity: 1}, 300, 'easeOutQuart');
    }, function() {
    	$(this).find("a.img-view").animate({left: -36+'px', marginLeft: 0, opacity: 0 });
        $(this).find("img").stop(true, true).animate({ opacity: 1 }, 300);
    });
	
	//Portf Image Hover
    $("#isotope-container div.border-img").hover(function () {	
        $(this).find("img").stop(true, true).animate({ opacity: 0.7 }, 300);
    	$(this).find("a.img-view").animate({left: 50+'%', marginLeft: -18+'px', opacity: 1}, 300, 'easeOutQuart');
    }, function() {
    	$(this).find("a.img-view").animate({left: -36+'px', marginLeft: 0, opacity: 0 });
        $(this).find("img").stop(true, true).animate({ opacity: 1 }, 300);
    });
    
    //Features Hover
    $("div.features div").hover(function () {						 
    	$(this).find("img").stop(true, true).animate({ opacity: 0.8 }, 100);
    }, function() {
    	$(this).find("img").stop(true, true).animate({ opacity: 1.0 }, 100);
    });
    
    
    //Testimonial Image Hover
    $('.views-field-field--testimonial-image .field-content img').css({ opacity: 0.5 });
    $(".views-field-field--testimonial-image .field-content img").hover(function () {						 
    	$(this).stop(true, true).animate({ opacity: 1.0 }, 800);
    }, function() {
    	$(this).stop(true, true).animate({ opacity: 0.5 }, 800);
    });
	
	 //Clients Image Hover
    $('#client-logo img').css({ opacity: 0.5 });
    $("#client-logo img").hover(function () {						 
    	$(this).stop(true, true).animate({ opacity: 1.0 }, 800);
    }, function() {
    	$(this).stop(true, true).animate({ opacity: 0.5 }, 800);
    });
	 //Tab
    $("div.tab-raz div").hover(function () {						 
    	$(this).find("img").stop(true, true).animate({ opacity: 0.6 }, 800);
    }, function() {
    	$(this).find("img").stop(true, true).animate({ opacity: 1.0 }, 800);
    });
    

 

    //FLICKR
    $('#footer .flickr').jflickrfeed({
		limit: 8,
		qstrings: {
			id: '99771506@N00'
		},
		itemTemplate: '<li>'+
						'<a rel="prettyPhoto[flickr]" href="{{image}}" title="{{title}}">' +
							'<img src="{{image_s}}" alt="{{title}}" />' +
						'</a>' +
					  '</li>'
	}, function(data) {
		$("a[rel^='prettyPhoto']").prettyPhoto();

        $("#footer .flickr li").hover(function () {						 
    	   $(this).find("img").stop(true, true).animate({ opacity: 0.5 }, 800);
        }, function() {
    	   $(this).find("img").stop(true, true).animate({ opacity: 1.0 }, 800);
        });
	});


    //SIDEBAR TABS
    $('.s-tab ul.tab-sidebar').each(function() {
        $(this).find('li').each(function(i) {
          $(this).click(function(){
            $(this).addClass('active').siblings().removeClass('active')
              .parents('div.s-tab').find('div.tab').slideUp(500).delay(500).end().find('div.tab:eq('+i+')').slideDown(1000);
          });
        });
    });
    
    
    //TOGGLE
    $(".close").click(function(){$("#seting").toggle("fast");
    $(this).toggleClass("openpanel");return false});
    $(".toggle-block").hide(); 
    $("p.toggle").click(function(){
    		$(this).toggleClass("active").next().slideToggle(500);
    		return false; 
    });
    

    //ACCORDION
    $('.acc-block').hide();
    $('.acc-header:first').addClass('active').next().show();
    $('.acc-header').click(function(){
    	if( $(this).next().is(':hidden') ) {
    		$('.acc-header').removeClass('active').next().slideUp(500);
    		$(this).toggleClass('active').next().slideDown(500);
    	}
    	return false;
    });
    
    
});


$(window).load(function() {
    
    $('#slider').flexslider({
        animation: "slide",
        slideshow: true, 
        slideshowSpeed: 7000,
        animationDuration: 600,   
        directionNav: true,
        controlNav: false,
        controlsContainer: "#home_slider",
        manualControls: "#home_slider_control li", 
        start: function(){$('#slider').removeClass('loader');},
        after: function(){$('ul.slides li').find("div").fadeIn(500);},
        before: function(){$('ul.slides li').find("div").fadeOut(0);}
        
    });
    
    $('#slider .flex-direction-nav a').css({ opacity: 0 });
    $("#slider").hover(function () {						 
        $(this).find("a.flex-prev").animate({left: 30+'px', opacity: 1}, 300, 'easeOutQuart');
        $(this).find("a.flex-next").animate({right: 30+'px', opacity: 1}, 300, 'easeOutQuart');
    }, function() {
        $(this).find("a.flex-prev").animate({left: -50+'px', opacity: 0 });
        $(this).find("a.flex-next").animate({right:  -50+'px', opacity: 0 });
    });
    
});


  $(document).ready(function(){
                $('#latest-work').elastislide({
                    imageW 	: 260,
                    margin  : 30                    
                });
            });
			
			
			 $(document).ready(function(){
                $('#testimonial').elastislide({
                    imageW 	: 555,
                    margin  : 30                    
                });
            });
			
			
			$(document).ready(function(){
                $('#newsletters').elastislide({
                    imageW 	: 555,
                    margin      : 30            
                });
            });

})(jQuery);


(function($){
  $.fn.autofill = function(options){
    var defaults = {
      value:'',
      defaultTextColor:"#777777",
      activeTextColor:"#ffffff",
      password: false
    };
    var options = $.extend(defaults,options);
    return this.each(function(){
      var obj=$(this);
      obj.css({color:options.defaultTextColor})
        .val(options.value)
        .focus(function(){
          if(obj.val()==options.value){
            obj.val("").css({color:options.activeTextColor});
            if (options.password && obj.attr('type') == 'text') {
              obj.attr('type', 'password');
            }
          }
        })
        .blur(function(){
          if(obj.val()==""){
            obj.css({color:options.defaultTextColor}).val(options.value);
            if (options.password && obj.attr('type') == 'password') {
              obj.attr('type', 'text');
            }
          }
        });
    });
  };
})(jQuery);

(function ($) {
Drupal.behaviors.designmd = {
  attach: function (context) {
    $('#search-block-form .form-text', context).autofill({
      value: "Search..."
    });
  } 
};
})(jQuery);

(function ($) {
		 $(document).ready(function(){

$('#breadcrumbs-nav nav.breadcrumb a[title]').remove();
});
})(jQuery);

(function ($) {
            	$(document).ready(function(){
        	       //TWITTER
                    $(".s-tweet").tweet({
                    	  join_text: "auto",
                    	  username: "envato",
                    	  avatar_size: 40,
                    	  count: 3,
                    	  auto_join_text_default: "we said,",
                    	  auto_join_text_ed: "we",
                    	  auto_join_text_ing: "we were",
                    	  auto_join_text_reply: "we replied",
                    	  auto_join_text_url: "we were checking out",
                    	  loading_text: "loading tweets..."
                    });
            	});
          
})(jQuery);

(function ($) {
                $(window).load(function() {
                    $('#slider-blog-3').flexslider({
                        controlNav: false,  
                    });
                });
})(jQuery);

