import QtQuick 2.12

import Kopi 1.0

PortfolioDashboardForm {
    id: root

    Component.onCompleted: {
        chartView1.webview.loadHtml(chart1.apexChartWidget(),
                                       "http://kopitrade.io")
        chartView2.webview.loadHtml(chart2.apexChartWidget(),
                                       "http://kopitrade.io")
        chartView3.webview.loadHtml(chart3.apexChartWidget(),
                                       "http://kopitrade.io")
        chartView4.webview.loadHtml(chart4.apexChartWidget(),
                                       "http://kopitrade.io")
    }

    //html code widget one - the default one
    HtmlWidget {
        id: chart1
        containerID: "chart"
        beginBodyWidget: "<div id=\""
                         + containerID +"\">"
                         +"</div>"
                         + "\n<script src=\"https://cdn.jsdelivr.net/npm/apexcharts\"></script> "
                         + "\n<script>"
        endBodyWidget: "</script>"

        apexWidget: "var options = {"
                    + "\n chart: {width: \'100%\', height: \'100%\', "
                    + "\n type: 'line' },"
                    + "\n series: [{"
                    + "\n name: 'sales',"
                    + "\n data: [30,40,35,50,49,60,70,91,125]}],"
                    + "\n xaxis: {categories: [1991,1992,1993,1994,1995,1996,1997, 1998,1999]}}"
                    + "\n var chart = new ApexCharts(document.querySelector(\"#chart\"), options);"
                    + "\n chart.render();"

    }

    HtmlWidget {
        id: chart2
        containerID: "chart"

        property var chartCode: {
            "chart": {
                "width": '100%',
                "height": '100%',
                "type": 'donut',
            },
            "series": [44, 55, 41, 17, 15],
            "responsive": [{
                "breakpoint": 480,
                "options": {
                    "chart": {
                    },
                    "legend": {
                        "position": 'bottom'
                    }
                }
            }]
        }

        beginBodyWidget: "<div id=\""
                         + containerID +"\">"
                         +"</div>"
                         + "\n<script src=\"https://cdn.jsdelivr.net/npm/apexcharts\"></script> "
                         + "\n<script>"
        endBodyWidget: "</script>"

        apexWidget: "var options = " + JSON.stringify(chartCode)
                    + "\n var chart = new ApexCharts(document.querySelector(\"#chart\"), options);"
                    + "\n chart.render();"
    }

    HtmlWidget {
        id: chart3

        property var chartCode: {
            "chart": {
                "width": '100%',
                "height": '100%',
                "type": 'pie',
            },
            "labels": ['Team A', 'Team B', 'Team C', 'Team D', 'Team E'],
            "series": [44, 55, 13, 43, 22],
            "responsive": [{
                "breakpoint": 480,
                "options": {
                    "chart": {},
                    "legend": {"position": 'bottom'}
               }
            }]
        }

        containerID: "chart"
        beginBodyWidget: "<div id=\""
                         + containerID +"\">"
                         +"</div>"
                         + "\n<script src=\"https://cdn.jsdelivr.net/npm/apexcharts\"></script> "
                         + "\n<script>"
        endBodyWidget: "\n </script>"

        apexWidget: "\n var options = " + JSON.stringify(chartCode)
                     + "\n var chart = new ApexCharts(document.querySelector(\"#chart\"), options);"
                     + "\n chart.render();"
    }

    HtmlWidget {
        id: chart4
        containerID: "chart"
        beginBodyWidget: "<div id=\""
                         + containerID +"\">"
                         +"</div>"
                         + "\n<script src=\"https://cdn.jsdelivr.net/npm/apexcharts\"></script> "
                         + "\n<script>"
        endBodyWidget: "\n </script>"

        apexWidget: "var options = {"
                    + "\n chart: {width: \'100%\', height: \'100%\', "
                    + "\n type: 'line' },"
                    + "\n series: [{"
                    + "\n name: 'sales',"
                    + "\n data: [30,40,35,50,49,60,70,91,125]}],"
                    + "\n xaxis: {categories: [1991,1992,1993,1994,1995,1996,1997, 1998,1999]}}"
                    + "\n var chart = new ApexCharts(document.querySelector(\"#chart\"), options);"
                    + "\n chart.render();"

    }
}
