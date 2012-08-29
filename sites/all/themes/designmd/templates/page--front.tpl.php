
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
        	</div>
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



<?php if ($page['slider']): ?><?php print render($page['slider']); ?><?php endif; ?> 

<!--BEGIN: #content-->
<div id="content" class="wrapper">
 <?php if ($page['featured']): ?><div class="welcome"><?php print render($page['featured']); ?></div><?php endif; ?>

 <div class="divider"></div>

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
    <div class="divider"></div>

 
    
<?php if ($page['postscript_first']): ?><div class="one-two"><div id="postscript-first"><?php print render($page['postscript_first']); ?></div></div>
    
    <div class="clear hide"></div>
    <div class="divider hide"></div><?php endif; ?>
       
    
<?php if ($page['postscript_second']): ?><div class="one-two last"><div id="postscript-second"><?php print render($page['postscript_second']); ?></div></div>
        
    <div class="clear"></div>
    <div class="divider"></div><?php endif; ?>
       
    
    <?php if ($page['postscript_third']): ?><div class="one-two"><div id="postscript-third"><?php print render($page['postscript_third']); ?></div> </div>
    
    <div class="clear hide"></div>
    <div class="divider hide"></div><?php endif; ?>
   
    
     <?php if ($page['postscript_fourth']): ?><div class="one-two last"><div id="postscript-fourth"><?php print render($page['postscript_fourth']); ?></div> </div>

    <div class="clear"></div><?php endif; ?>
       
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


          
    <div class="one-four">
    <?php if ($page['footer_firstcolumn']): ?>
<?php print render($page['footer_firstcolumn']); ?>
 <?php endif; ?>

        
    </div>
      
    <div class="one-three">
    <?php if ($page['footer_secondcolumn']): ?>
<?php print render($page['footer_secondcolumn']); ?>
 <?php endif; ?>
       
    </div>

    <div class="one-three">
     <?php if ($page['footer_thirdcolumn']): ?>
<?php print render($page['footer_thirdcolumn']); ?>
 <?php endif; ?>
           
    </div>
    
    <div class="one-three">
    <?php if ($page['footer_fourthcolumn']): ?>
<?php print render($page['footer_fourthcolumn']); ?>
 <?php endif; ?>
        
    </div>
        

    <div class="one-four last">
    <?php if ($page['footer_fifthcolumn']): ?>
<?php print render($page['footer_fifthcolumn']); ?>
 <?php endif; ?>
       
    </div>

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
