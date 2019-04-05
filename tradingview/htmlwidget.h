#ifndef TRADINGVIEWWIDGET_H
#define TRADINGVIEWWIDGET_H

#include <QObject>
#include <QJsonObject>

class HtmlWidget : public QObject
{
    Q_OBJECT
public:

    enum WidgetProperty {
        ContainerID = 0,
        Width,
        Height,
        Autosize,
        Symbol,
        SymbolDescription,
        Interval,
        Theme,
        Style,
        EnableSideBar,
        AllowChangeSymbol,
        EnableTopToolbar,
        EnableBottomToolbar,
        Details
    };

    enum WidgetType {
        AdvancedChart = 11,
        SimpleChart,
        BasicChart,
        SingleTicker,
        TickerPanel
    };

    Q_ENUM(WidgetProperty)
    Q_ENUM(WidgetType)
    Q_PROPERTY(int widgetType READ widgetType WRITE setWidgetType NOTIFY widgetTypeChanged)
    Q_PROPERTY(QString widgetName READ widgetName WRITE setWidgetName NOTIFY widgetNameChanged)
    Q_PROPERTY(int widgetWidth READ widgetWidth WRITE setWidgetWidth NOTIFY widgetWidthChanged)
    Q_PROPERTY(int widgetHeight READ widgetHeight WRITE setWidgetHeight NOTIFY widgetHeightChanged)
    Q_PROPERTY(QString assetSymbol READ assetSymbol WRITE setAssetSymbol NOTIFY assetSymbolChanged)
    Q_PROPERTY(QString containerID READ containerID WRITE setContainerID NOTIFY containerIDChanged)
    Q_PROPERTY(QJsonObject widgetProperties READ widgetProperties WRITE setWidgetProperties NOTIFY widgetPropertiesChanged)
    Q_PROPERTY(QString beginBodyWidget READ beginBodyWidget WRITE setBeginBodyWidget NOTIFY beginBodyWidgetChanged)
    Q_PROPERTY(QString endBodyWidget READ endBodyWidget WRITE setEndBodyWidget NOTIFY endBodyWidgetChanged)
    Q_PROPERTY(QString apexWidget READ apexWidget WRITE setApexWidget NOTIFY apexWidgetChanged)

    explicit HtmlWidget(QObject *parent = nullptr,  const QString &name = QString());
    ~HtmlWidget();

    int widgetType() const;
    void setWidgetType(int type);

    QString widgetName() const;
    void setWidgetName(const QString &name);

    QJsonObject widgetProperties() const;
    void setWidgetProperties(const QJsonObject &properties);

    int widgetWidth() const;
    void setWidgetWidth(int width);

    int widgetHeight() const;
    void setWidgetHeight(int height);

    QString containerID() const;
    void setContainerID(const QString &id);

    QString assetSymbol() const;
    void setAssetSymbol(const QString &symb);

    QString beginBodyWidget() const;
    void setBeginBodyWidget(const QString &html);

    QString endBodyWidget() const;
    void setEndBodyWidget(const QString &html);

    QString apexWidget() const;
    void setApexWidget(const QString &widget);

    Q_INVOKABLE QString tradingviewWidget() const;
    Q_INVOKABLE QString tradingviewJS() const;
    Q_INVOKABLE QString apexChartWidget() const;
    Q_INVOKABLE void setProperty(const QString &key, const QString &value);

Q_SIGNALS:
    void widgetTypeChanged(int type);
    void widgetNameChanged(const QString &name);
    void widgetWidthChanged(int width);
    void widgetHeightChanged(int height);
    void widgetPropertiesChanged(const QJsonObject &properties);
    void assetSymbolChanged(const QString &symb);
    void containerIDChanged(const QString &id);
    void widgetFileUpdated();
    void beginBodyWidgetChanged(const QString &html);
    void endBodyWidgetChanged(const QString &html);
    void apexWidgetChanged(const QString &html);

private:
    const QString htmlHeadBodyTags() const;
    const QString htmlEnd() const;

    class Private;
    Private *m_data;
};

#endif // TRADINGVIEWWIDGET_H
