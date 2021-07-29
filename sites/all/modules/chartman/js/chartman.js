/**
 * @file
 * JavaScript behaviors.
 */

 (function ($) {
  Drupal.behaviors.chartman = {
    attach: function (context, settings) {

      if(Drupal.settings.task_1) {
        pie("task_1_a", Drupal.settings.task_1.label, Drupal.settings.task_1.data_a)
      }

      if(Drupal.settings.task_1_b) {
        pie("task_1_b", Drupal.settings.task_1_b.label, Drupal.settings.task_1_b.data_b)
      }

      if(Drupal.settings.task_2) {
        bars("task_2_a", Drupal.settings.task_2.label, Drupal.settings.task_2.data, 'Number of samples tested')
      }

      if(Drupal.settings.task_2_2) {
        bars("task_2_2", Drupal.settings.task_2_2.label, Drupal.settings.  task_2_2.data, 'Sample Processed')
      }

      if(Drupal.settings.task_3) {
        stacked_bar("task_3_a", Drupal.settings.task_3.label, Drupal.settings.task_3.data, 'Number of samples tested')
      }

      if(Drupal.settings.task_4) {
        stacked_bar("task_4", Drupal.settings.task_4.label, Drupal.settings.task_4.data, 'Number of samples tested')
      }

      if(Drupal.settings.task_10) {
        horizontalBar("task_10", Drupal.settings.task_10.label, Drupal.settings.task_10.data)
      }

      if(Drupal.settings.task_11) {
        horizontalBar("task_11", Drupal.settings.task_11.label, Drupal.settings.task_11.data)
      }

      if(Drupal.settings.task_12) {
        barWithLine("task_12", Drupal.settings.task_12.label, Drupal.settings.task_12.data, 'Number of samples tested', 'Test Positivity')
      }

      if(Drupal.settings.task_12b) {
        barWithLine("task_12b", Drupal.settings.task_12b.label, Drupal.settings.task_12b.data, 'Number of samples tested', 'Test Positivity')
      }

      if(Drupal.settings.task_13) {
        stacked_bar("task_13", Drupal.settings.task_13.label, Drupal.settings.task_13.data, 'Number of samples tested')
      }

      if(Drupal.settings.task_14) {
        barWithLine("task_14", Drupal.settings.task_14.label, Drupal.settings.task_14.data, 'Number of samples tested', 'Moving Average Test Positivity %')
      }

      if(Drupal.settings.task_17) {
        barWithLine("task_17", Drupal.settings.task_17.label, Drupal.settings.task_17.data, 'Number of samples tested', 'Test Positivity %')
      }

    }
  };
})(jQuery);
