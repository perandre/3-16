<!DOCTYPE html>
<html lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>"<?php print $rdf_namespaces; ?>>
<head>
<?php print $head; ?>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta name="viewport" content="width=100%; initial-scale=1; maximum-scale=1; minimum-scale=1; user-scalable=no;" />
<title><?php print $head_title; ?></title>
<?php print $styles; ?>
<?php print $scripts; ?>
 <!--BEGIN: google fonts-->
    <link href='http://fonts.googleapis.com/css?family=Rokkitt:400,700|Droid+Serif:400,400italic,700,700italic|Droid+Sans:400,700' rel='stylesheet' type='text/css' />
    <!--END: google fonts-->
<!--[if lt IE 9]><script src="http://html5shiv.googlecode.com/svn/trunk/html5.js"></script><![endif]-->

</head>
<body class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php print $page_top; ?>
  <?php print $page; ?>
  <?php print $page_bottom; ?>
</body>
</html>