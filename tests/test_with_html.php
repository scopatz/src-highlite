<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
	<?php echo $html->charset(); ?>
	<title>
		<?php __('PhpBibliography:'); ?>
		<?php echo $title_for_layout; ?>
	</title>
<meta name="GENERATOR" content="PhpBibliography <?php echo $phpbibliography_version;?>, http://phpbibliography.sf.net" />
	<?php
		echo $html->meta('icon');

		echo $html->css('phpbibliography');
		//echo $html->css('cake.generic');
		
		echo $scripts_for_layout;
	?>
</head>
<body>
	<div id="container">
		<div id="header">
			<h1><?php /* echo $html->link(__('CakePHP: the rapid development php framework', true), 'http://cakephp.org'); */ ?></h1>
			<cake:nocache>
			<?php 
			if ($session->check('User')) {
				echo __('Logged in as: ',true);
				echo $html->link($session->read('User.username'), 
					array('controller' => 'admins', 'action' => 'edit', $session->read('User.id'), 'admin' => true));
				if ($session->read('User.superuser')) {
					echo ' '.__('(superuser)', true);
				}
				echo ' - ';
				echo $html->link(__('Logout', true), 
					array('controller' => 'admins', 'action' => 'logout', 'admin' => false));
			} 
			?>
			</cake:nocache>
		</div>
		<div id="content">

			<?php $session->flash(); ?>

			<?php echo $content_for_layout; ?>

		</div>
		<div id="footer">
			<?php echo $html->link(
					'Powered by PhpBibliography',
					'http://phpbibliography.sourceforge.net/',
					array('target'=>'_blank'), null, false
				);
			?>
		</div>
	</div>
	<?php echo $cakeDebug; ?>
</body>
</html>