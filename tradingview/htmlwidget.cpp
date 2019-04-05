#include "htmlwidget.h"

#include <QTextStream>
#include <QFile>
#include <QCoreApplication>
#include <QJsonArray>
#include <QJsonDocument>

#include <QDebug>

class HtmlWidget::Private {
public:
    int widgetType;
    QString name;
    int widgetWidth;
    int widgetHeight;
    QString symbol;
    QString containerId;
    QJsonObject properties;
    QHash <int, QString> propertiesCache;
    QHash <int, QString> propertyNamesCache;
    QString beginbodyWidget;
    QString endbodywidget;
    QString apexwidget;
};

HtmlWidget::HtmlWidget(QObject *parent, const QString &name)
    :QObject(parent)
      ,m_data(new Private)
{
    if(!name.isEmpty())
        setWidgetName(name);

    setWidgetType(AdvancedChart);
}

HtmlWidget::~HtmlWidget()
{
    delete m_data;
    m_data = nullptr;
}

int HtmlWidget::widgetType() const
{
    return m_data->widgetType;
}

void HtmlWidget::setWidgetType(int type)
{
    if(m_data->widgetType != type){
        m_data->widgetType = type;
        emit widgetTypeChanged(type);
    }
}

QString HtmlWidget::widgetName() const
{
    return m_data->name;
}

void HtmlWidget::setWidgetName(const QString &name)
{
    if(m_data->name != name) {
        m_data->name = name;
        emit widgetNameChanged(name);
    }
}

QJsonObject HtmlWidget::widgetProperties() const
{
    return m_data->properties;
}

void HtmlWidget::setWidgetProperties(const QJsonObject &properties)
{
    m_data->properties = properties;
    emit widgetPropertiesChanged(m_data->properties);
}

int HtmlWidget::widgetWidth() const
{
    return m_data->widgetWidth;
}

void HtmlWidget::setWidgetWidth(int width)
{
    if(m_data->widgetWidth != width) {
        m_data->widgetWidth = width;
        emit widgetWidthChanged(width);

        setProperty("width", QString::number(width));
    }
}

int HtmlWidget::widgetHeight() const
{
    return m_data->widgetHeight;
}

void HtmlWidget::setWidgetHeight(int height)
{
    if(m_data->widgetHeight != height) {
        m_data->widgetHeight = height;
        emit widgetHeightChanged(height);

        setProperty("height", QString::number(height));
    }
}

QString HtmlWidget::containerID() const
{
    return m_data->containerId;
}

void HtmlWidget::setContainerID(const QString &id)
{
    if(m_data->containerId != id) {
        m_data->containerId = id;
        emit containerIDChanged(m_data->containerId);
    }
}

QString HtmlWidget::assetSymbol() const
{
    return m_data->symbol;
}

void HtmlWidget::setAssetSymbol(const QString &symb)
{
    m_data->properties.insert("symbol", symb);

    if(m_data->symbol != symb) {
        m_data->symbol = symb;
        m_data->properties.insert("symbol", symb);
        emit assetSymbolChanged(m_data->symbol);
    }
}

QString HtmlWidget::beginBodyWidget() const
{
    return m_data->beginbodyWidget;
}

void HtmlWidget::setBeginBodyWidget(const QString &html)
{
    if(m_data->beginbodyWidget != html) {
        m_data->beginbodyWidget = html;
        emit beginBodyWidgetChanged(html);
    }
}

QString HtmlWidget::endBodyWidget() const
{
    return m_data->endbodywidget;
}

void HtmlWidget::setEndBodyWidget(const QString &html)
{
    if(m_data->endbodywidget != html) {
        m_data->endbodywidget = html;
        emit endBodyWidgetChanged(html);
    }
}

QString HtmlWidget::apexWidget() const
{
    return m_data->apexwidget;
}

void HtmlWidget::setApexWidget(const QString &widget)
{
    if(m_data->apexwidget != widget) {
        m_data->apexwidget = widget;
        emit apexWidgetChanged(widget);
    }
}

QString HtmlWidget::tradingviewWidget() const
{
    return beginBodyWidget()
        + tradingviewJS()
        + endBodyWidget();
}

QString HtmlWidget::tradingviewJS() const
{
    QString jsStartCode;
    QString jsEndCode = QString(");\n");
    switch (m_data->widgetType) {
    case AdvancedChart:
    case SimpleChart:
        jsStartCode = QString(("new TradingView.widget(\n"));
        break;
    case BasicChart:
        jsStartCode = "";
        jsEndCode = "";
        break;
    }

    QJsonDocument jsdoc(m_data->properties);
    m_data->properties.insert("symbol", assetSymbol());
    return jsStartCode
        + QString(jsdoc.toJson())
        + jsEndCode;
}

QString HtmlWidget::apexChartWidget() const
{
    return beginBodyWidget() + apexWidget() +endBodyWidget();
}

void HtmlWidget::setProperty(const QString &key, const QString &value)
{
    if(!key.isEmpty()) {
        m_data->properties.insert(key, value);
        emit widgetPropertiesChanged(m_data->properties);
    }
}

const QString HtmlWidget::htmlHeadBodyTags() const
{
    return QString("<!doctype html>\n"
                   "<html>\n"
                   "<head>"
                   //                   "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">"
                   "</head>\n"
                   "<body> \n");
}

const QString HtmlWidget::htmlEnd() const
{
    return QString("</body>\n"
                   "</html>");
}

