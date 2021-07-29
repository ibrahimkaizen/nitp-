<div class="wrapper">


  <!-- Content Wrapper. Contains page content -->
  <div class="login-box">
  <div class="login-logo">
    <a href="<?php print $front_page; ?>"><?php print $site_name; ?></a>
  </div>
  <!-- /.login-logo -->
  <div class="login-box-body">
    <p class="login-box-msg">Sign in to start your session</p>
    <?php if ($messages): ?>
      <div id="messages">
        <div class="section clearfix">
          <?php print $messages; ?>
        </div>
      </div>
    <?php endif; ?>

    <?php
      $form = drupal_get_form('user_login');
      print drupal_render($form);
    ?>

    <a href="user/password"><?php print t('I forgot my password'); ?></a>

  </div>
  <!-- /.login-box-body -->
</div>
     <!-- /.content-wrapper -->


</div>
 <!-- ./wrapper -->
