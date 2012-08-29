

<!-- BEGIN: #header -->


<div id="header" class="wrapper"> 

    <!-- BEGIN: #logo-->
      <?php if ($logo): ?>
      <div id="logo"  class="three columns alpha">  <a href="<?php print $front_page; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo">
          <img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" />
        </a></div>
      <?php endif; ?>
    <!-- END: #logo -->
    
    <?php if ($site_name || $site_slogan) : ?>
		<div id="branding-wrapper">
			<?php if ($site_name) : ?>
				<?php if ($is_front) : ?>
					<h1 class="site-name"><a href="<?php print $base_path ?>" title="<?php print $site_name ?>"><?php print $site_name ?></a></h1>
				<?php endif; ?>
				<?php if (!$is_front) : ?>
					<h2 class="site-name"><a href="<?php print $base_path ?>" title="<?php print $site_name ?>"><?php print $site_name ?></a></h2>
				<?php endif; ?>
			<?php endif; ?>
			<?php if ($site_slogan) : ?>
				<div class='site-slogan'><?php print $site_slogan; ?></div>
			<?php endif; ?>
        	</div><!-- end branding wrapper -->
	<?php endif; ?>
    
    <?php if ($page['social']): ?>
		 <div id="social">
			<?php print render ($page['social']); ?>
		</div>
	<?php endif; ?>

    
    <div class="clear"></div> 
    <!-- BEGIN: #menu -->
 
 <?php if($menu_bar = render($page['menu_bar'])): ?>
            <!-- MAIN NAV -->
            <div id="menu-bar-wrapper" class="clearfix">
              
                <?php print $menu_bar; ?>
              
            </div>
 <?php endif;?>
  <!-- END: #menu -->
 
    
    
                  
</div><!--END: #header -->


<!--BEGIN: breadcrumbs -->
<div class="breadcrumbs">
    <?php if ($page['titlebar']): ?>
<?php print render($page['titlebar']); ?>
 <?php endif; ?>
    
    <!--BEGIN: link nav top-->
    <div id="breadcrumbs-nav">
       <?php if ($breadcrumb): print $breadcrumb; endif;?>
    </div><!--END: link nav top-->
    
</div><!--END: breadcrumbs -->

<?php if ($page['maintop']): ?><div class="maintop wrapper"><?php print render($page['maintop']); ?></div><?php endif; ?>
<!--BEGIN: #content-->
<div id="content" class="wrapper">
 <?php if ($page['featured']): ?><div class="welcome"><?php print render($page['featured']); ?></div><div class="divider"></div><?php endif; ?>



    <!--BEGIN: content-->
<div>

  <?php print render($title_prefix); ?>
        <?php if ($title): ?><h1 class="title" id="page-title"><?php print $title; ?></h1><?php endif; ?>
        <?php print render($title_suffix); ?>
        <?php if ($tabs): ?><div class="tabs"><?php print render($tabs); ?></div><?php endif; ?>
        <?php print render($page['help']); ?>
        <?php if ($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
        <?php print render($page['content']); ?>
        <?php print $feed_icons; ?>
        
        </div>
        
        
       
        
    <div class="clear"></div>
    

    <!-- BEGIN:  -->
    
<?php if ($page['postscript_first']): ?><div class="one-two"><div id="postscript-first"><?php print render($page['postscript_first']); ?></div> </div>
    
    <div class="clear hide"></div>
    <div class="divider hide"></div><?php endif; ?>
       
   
    
    <!--BEGIN:  post-->
    
        <?php if ($page['postscript_second']): ?><div class="one-two last"><div id="postscript-second"><?php print render($page['postscript_second']); ?></div> </div>
        
    <div class="clear"></div>
    <div class="divider"></div><?php endif; ?>
       
   

    <!--BEGIN: .testimonial-->
    
    <?php if ($page['postscript_third']): ?><div class="one-two"><div id="postscript-third"><?php print render($page['postscript_third']); ?></div> </div>
    
    <div class="clear hide"></div>
    <div class="divider hide"></div><?php endif; ?>
   
    
    <!--BEGIN: newsletters-->
   
     <?php if ($page['postscript_fourth']): ?> <div class="one-two last"><div id="postscript-fourth"><?php print render($page['postscript_fourth']); ?></div> </div>

    <div class="clear"></div><?php endif; ?>
    
      
     <?php if($page['bottom_1'] || $page['bottom_2'] || $page['bottom_3'] || $page['bottom_4']) : ?>
    <div style="clear:both"></div>
     <h2 class="h-divider">Our team</h2>
    <div id="bottom-wrapper" class="in<?php print (bool) $page['bottom_1'] + (bool) $page['bottom_2'] + (bool) $page['bottom_3'] + (bool) $page['bottom_4']; ?>">
          <?php if($page['bottom_1']) : ?>
          <div class="one-four m-bottom">
            <?php print render ($page['bottom_1']); ?>
          </div>
          <?php endif; ?>
          <?php if($page['bottom_2']) : ?>
           <div class="one-four m-bottom">
            <?php print render ($page['bottom_2']); ?>
          </div>
          <?php endif; ?>
          <?php if($page['bottom_3']) : ?>
           <div class="one-four m-bottom">
            <?php print render ($page['bottom_3']); ?>
          </div>
          <?php endif; ?>
          <?php if($page['bottom_4']) : ?>
          <div class="one-four m-bottom last">
            <?php print render ($page['bottom_4']); ?>
          </div>
          <?php endif; ?>
      <div style="clear:both"></div>
    </div><!-- end bottom -->
    <?php endif; ?>
       
</div><!--END: #content-->
     
<?php if($page['footer_top']) : ?>
 <!--BEGIN: client logo-->
          <div id="client-logo">
            <?php print render ($page['footer_top']); ?>
             <div class="clear"></div>
        </div><!--END: #client logo-->
          <?php endif; ?>
        
<!--BEGIN: #footer-->
<div id="footer" class="wrapper">


    <!--BEGIN: about us -->            
    <div class="one-four">
    <?php if ($page['footer_firstcolumn']): ?>
<?php print render($page['footer_firstcolumn']); ?>
 <?php endif; ?>

        
    </div><!--END: about us -->
 
    <!--BEGIN: arhive -->        
    <div class="one-three">
    <?php if ($page['footer_secondcolumn']): ?>
<?php print render($page['footer_secondcolumn']); ?>
 <?php endif; ?>
       
    </div><!--END: arhive -->
    
    <!--BEGIN: hot link -->
    <div class="one-three">
     <?php if ($page['footer_thirdcolumn']): ?>
<?php print render($page['footer_thirdcolumn']); ?>
 <?php endif; ?>
           
    </div><!--END: hot link -->
    
    <!--BEGIN: blog -->
    <div class="one-three">
    <?php if ($page['footer_fourthcolumn']): ?>
<?php print render($page['footer_fourthcolumn']); ?>
 <?php endif; ?>
        
    </div><!--END: blog -->
        
    <!--END: flickr -->
    <div class="one-four last">
    <?php if ($page['footer_fifthcolumn']): ?>
<?php print render($page['footer_fifthcolumn']); ?>
 <?php endif; ?>
       
    </div><!--END: flickr  -->

    <div class="clear"></div>
    
    <!--BEGIN: footer bottom-->
    <div class="footer-buttom">
    
    <?php if ($page['footer-a']): ?>
<?php print render($page['footer-a']); ?>
 <?php endif; ?>
       
        
    <?php if ($page['footer-b']): ?>
<?php print render($page['footer-b']); ?>
 <?php endif; ?>
       
        
        <div class="clear"></div>
    </div><!--END: footer bootom-->
    
</div><!--END: #footer-->
