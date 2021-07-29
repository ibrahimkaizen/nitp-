//This function generates random backgroundColor
function Color(datas){
    var Color = []
    var dynamicColors = function() {
        var r = Math.floor(Math.random() * 255);
        var g = Math.floor(Math.random() * 255);
        var b = Math.floor(Math.random() * 255);
        return "rgb(" + r + "," + g + "," + b + ")";
    };

    for (var i in datas) {
        Color.push(dynamicColors());
    }
    return Color
}

//this function generates the PieChart
function pie(id, labels, datas) {
    var ctx = document.getElementById(id)
    if (ctx) {
      var myPieChart = new Chart(ctx.getContext('2d'), {
        type: 'doughnut',
        data: {
          labels: labels,
          datasets: [{
            data: datas,
            backgroundColor: Color(datas)
          }]
        },
        options: {
          cutoutPercentage: 30,
          rotation: 120,
          /* plugins: {
            labels: {
              fontColor: '#fff',
              shadowColor: 'rgba(255,0,0,0.75)',
            }
          } */
        }
      });
    }

}

//this function generated the bar chart
function bars(id, labels, datas, ylabel) {
    var ctx = document.getElementById(id)
    if (ctx) {
      var myPieChart = new Chart(ctx.getContext('2d'), {
        type: 'bar',
        data: {
          labels: labels,
          datasets: datas
        },
        options: {
          scales: {
            yAxes: [{
              scaleLabel: {
                display: true,
                labelString: ylabel
              }
            }],
            xAxes: [{
              categoryPercentage: 1.0,
              barPercentage: 1.0
            }]
          },
          /* plugins: {
            labels: false
          } */
        }
      });
    }
}

function barWithLine(id, labels, datas, ya, yb) {
    var ctx = document.getElementById(id)
    if (ctx) {
      var mybarWithLine = new Chart(ctx.getContext('2d'), {
        type: 'bar',
        data: {
          labels: labels,
          datasets: datas
        },
        options: {
          scales: {
            yAxes: [{
              id: 'A',
              type: 'linear',
              position: 'left',
              scaleLabel: {
                display: true,
                labelString: ya
              }
            }, {
              id: 'B',
              type: 'linear',
              position: 'right',
              scaleLabel: {
                display: true,
                labelString: yb
              },
              ticks:{
                max:100
              }

            }],
            xAxes: [{
              categoryPercentage: 1.0,
              barPercentage: 1.0
            }]
          },
          /* plugins: {
            labels: false
          } */
        }
      });

    }
}

function stacked_bar(id, labels, dataset, ylabel) {
    var ctx = document.getElementById(id)
    if (ctx) {
      var mystackBar = new Chart(ctx.getContext('2d'), {
        type: 'bar',
        data: {
          labels: labels,
          datasets: dataset
        },
        options: {
          scales: {
            xAxes: [{
                stacked: true
            }],
            yAxes: [{
                stacked: true,
                scaleLabel: {
                  display: true,
                  labelString: ylabel
                }
            }]
          },
          /* plugins: {
            labels: false
          } */
        }
      });
    }
}

function horizontalBar(id, labels, dataset) {
    var ctx = document.getElementById(id)
    if (ctx) {
      var stackedBar = new Chart(ctx.getContext('2d'), {
          type: 'horizontalBar',
          data: {
              labels: labels,
              datasets: dataset
          },
          options: {
              scales: {
                  xAxes: [{
                      stacked: true,
                      ticks:{
                        max:100
                      }
                  }],
                  yAxes: [{
                      stacked: true
                  }]
              },
              elements: {
                rectangle: {
                  borderWidth: 2,
                }
              },
              /* plugins: {
                labels: false
              } */
          }
      });
    }
}

