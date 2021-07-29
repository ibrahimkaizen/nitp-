/**
 * @file
 * JavaScript behaviors.
 */

function pyramid(id, labels, dataset) {
  var ctx = document.getElementById(id)
  if (ctx) {
    var pyramidBar = new Chart(ctx.getContext('2d'), {
        type: 'horizontalBar',
        data: {
            labels: labels,
            datasets: dataset
        },
        options: {
          title: {
            display: true,
            text: "Chart.js Bar Chart - Stacked",
          },
          tooltips: {
            intersect: false,
            callbacks: {
              label: (c) => {
                const value = Number(c.value);
                const positiveOnly = value < 0 ? -value : value;
                let retStr = "";
                if (c.datasetIndex === 0) {
                  retStr += `Male: ${positiveOnly.toString()}`;
                } else {
                  retStr += `Female: ${positiveOnly.toString()}`;
                }
                return retStr;
              },
            },
          },
          responsive: true,
          legend: {
            position: "bottom",
          },
          scales: {
            xAxes: [
              {
                stacked: false,
                ticks: {
                  beginAtZero: true,
                  callback: (v) => { return v < 0 ? -v: v }
                },
              },
            ],
            yAxes: [
              {
                stacked: true,
                ticks: {
                  beginAtZero: true,
                },
                position: "left",
              }
            ],
          },
        },
    });
  }
}

 (function ($) {
  Drupal.behaviors.chartman2 = {
    attach: function (context, settings) {

      if(Drupal.settings.chartman2_task2a) {
        pie(
          "chartman2_task2a", 
          Drupal.settings.chartman2_task2a.label, 
          Drupal.settings.chartman2_task2a.data,
        )
      }

      if(Drupal.settings.chartman2_task2b) {
        pyramid(
          "chartman2_task2b", 
          Drupal.settings.chartman2_task2b.label, 
          Drupal.settings.chartman2_task2b.data,
        )
      }

      if(Drupal.settings.chartman2_task5b) {
        barWithLine(
          "chartman2_task5b", 
          Drupal.settings.chartman2_task5b.label, 
          Drupal.settings.chartman2_task5b.data,
          'Number of samples tested', 
          'Test Positivity',
        )
      }
      
      if(Drupal.settings.chartman2_task3a) {
        pie(
          "chartman2_task3a", 
          Drupal.settings.chartman2_task3a.label, 
          Drupal.settings.chartman2_task3a.data,
        )
      }
      
      if(Drupal.settings.chartman2_task3b) {
        stacked_bar(
          "chartman2_task3b", 
          Drupal.settings.chartman2_task3b.label, 
          Drupal.settings.chartman2_task3b.data,
          'Breakdown by group and gender'
        )
      }

      if(Drupal.settings.chartman2_task3c) {
        pie(
          "chartman2_task3c", 
          Drupal.settings.chartman2_task3c.label, 
          Drupal.settings.chartman2_task3c.data,
        )
      }

      if(Drupal.settings.chartman2_task3d) {
        pie(
          "chartman2_task3d", 
          Drupal.settings.chartman2_task3d.label, 
          Drupal.settings.chartman2_task3d.data,
        )
      }

      if(Drupal.settings.chartman2_task3e) {
        bars(
          "chartman2_task3e", 
          Drupal.settings.chartman2_task3e.label, 
          Drupal.settings.chartman2_task3e.data,
          'Sample Processed'
        )
      }

      if(Drupal.settings.chartman2_task4a) {
        pie(
          "chartman2_task4a", 
          Drupal.settings.chartman2_task4a.label, 
          Drupal.settings.chartman2_task4a.data,
        )
      }

      if(Drupal.settings.chartman2_task4b) {
        pie(
          "chartman2_task4b", 
          Drupal.settings.chartman2_task4b.label, 
          Drupal.settings.chartman2_task4b.data,
        )
      }
      if(Drupal.settings.chartman2_task4c) {
        pie(
          "chartman2_task4c", 
          Drupal.settings.chartman2_task4c.label, 
          Drupal.settings.chartman2_task4c.data,
        )
      }

    }
  };
})(jQuery);
