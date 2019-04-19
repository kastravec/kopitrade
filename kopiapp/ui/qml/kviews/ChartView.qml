import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.4
import QtQuick.Dialogs 1.3

import Kopi 1.0
import "../basickontrols"

ChartViewForm {
    id: root

    signal oneChartView
    signal twoChartView

    property int chartViewType: 1
    property string currentSymbol
    property KSymbol ksymbol

    property var basicChartJS: {
        "width": "100%",
        "height": "100%",
        "locale": "en",
        "dateRange": "5y",
        "colorTheme": "dark",
        "trendLineColor": "#37a6ef",
        "underLineColor": "rgba(55, 166, 239, 0.15)",
        "isTransparent": true,
        "autosize": true,
        "largeChartUrl": ""
    }

    property var simpleChartJS: {
        "interval": "W",
        "timezone": "Etc/UTC",
        "theme": "Dark",
        "style": "2",
        "locale": "en",
        "enableg_publishing": false,
        "withdateranges": false,
        "hide_side_toolbar": true,
        "hide_top_toolbar": true,
        "allow_symbol_change": false,
        "hide_legend": true,
        "save_image": false,
        "autosize": true,
        "padding": "0",
        "hidevolume": true
    }

    property var advancedChartJS: {
        "interval": "W",
        "timezone": "Etc/UTC",
        "theme": "Dark",
        "style": "1",
        "locale": "en",
        "enableg_publishing": false,
        "withdateranges": false,
        "hide_side_toolbar": false,
        "allow_symbol_change": false,
        "hide_legend": false,
        "save_image": false,
        "autosize": true,
        "padding": "0",
        "hidevolume": true
    }

    Component.onCompleted: {
        chartTypeCombo.currentIndex = root.chartViewType
        chartOne.widgetType = HtmlWidget.SimpleChart
    }

    onCurrentSymbolChanged: {
        symbolChangedRefresh()
    }

    Connections {
        target: ksymbol
        onPriceChanged: root.priceLabel.text = ksymbol.price
    }

    chartTypeCombo.onActivated: {
        chartTypeChanged(chartTypeCombo.currentIndex)
    }

    onChartViewTypeChanged: chartTypeChanged(root.chartViewType)

    //html code widget one - the default one
    HtmlWidget {
        id: chartOne
        widgetType: HtmlWidget.BasicChart
        widgetName: "chartOneName"
        assetSymbol: root.currentSymbol
        containerID: "tradingview_2278"
        widgetProperties: root.basicChartJS
        beginBodyWidget: "<div class=\"tradingview-widget-container\">"
                         + "\n<div id=\"" + chartOne.containerID + "\"> </div>"
                         + "\n<script type=\"text/javascript\" src=\"https://s3.tradingview.com/external-embedding/embed-widget-mini-symbol-overview.js\" async>"
        endBodyWidget: "</script> \n</div \n><!-- TradingView Widget END -->"

        Component.onCompleted: {
            chartTypeChanged(root.chartTypeCombo.currentIndex)
            chartGridView.webview.loadHtml(
                        chartOne.tradingviewWidget(),
                        "http://kopitrade.io")
        }
    }

    function symbolChangedRefresh() {
        root.ksymbol = IEXSymbolsModel.symbol(root.currentSymbol)
        if(root.ksymbol) {
            chartOne.assetSymbol = root.currentSymbol
            chartGridView.webview.loadHtml(chartOne.tradingviewWidget(),
                                           "http://kopitrade.io")
        }
    }

    function chartTypeChanged(index) {
        switch (index) {
        case 0:
            chartOne.widgetType = HtmlWidget.BasicChart
            chartOne.widgetProperties = root.basicChartJS
            chartOne.beginBodyWidget = "<div class=\"tradingview-widget-container\">"
                    + "\n<div id=\"" + chartOne.containerID + "\"> </div>"
                    + "\n<script type=\"text/javascript\" src=\"https://s3.tradingview.com/external-embedding/embed-widget-mini-symbol-overview.js\" async>"
            break
        case 1:
            chartOne.widgetType = HtmlWidget.SimpleChart
            chartOne.widgetProperties = root.simpleChartJS
            chartOne.beginBodyWidget = "<div class=\"tradingview-widget-container\">"
                    + "\n<div id=\"" + chartOne.containerID + "\"> </div>"
                    + "\n<script type=\"text/javascript\" src=\"https://s3.tradingview.com/tv.js\"></script> "
                    + "\n<script type=\"text/javascript\"> \n"
            break
        case 2:
            chartOne.widgetType = HtmlWidget.AdvancedChart
            chartOne.widgetProperties = root.advancedChartJS
            chartOne.beginBodyWidget = "<div class=\"tradingview-widget-container\">"
                    + "\n<div id=\"" + chartOne.containerID + "\"> </div>"
                    + "\n<script type=\"text/javascript\" src=\"https://s3.tradingview.com/tv.js\"></script> "
                    + "\n<script type=\"text/javascript\"> \n"
            break
        }

        chartOne.assetSymbol = root.currentSymbol
        chartGridView.webview.loadHtml(chartOne.tradingviewWidget(),
                                       "http://kopitrade.io")
    }
}
