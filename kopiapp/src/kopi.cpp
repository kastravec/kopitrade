#include "kopi.h"

#include "portfolio.h"
#include "asset.h"
#include "trade.h"
#include "portfoliolistmodel.h"
#include "assetlistmodel.h"
#include "tradelistmodel.h"
#include "ksymbol.h"
#include "kaccount.h"
#include "ksymbolmodel.h"
#include "watchlistsmodel.h"
#include "watchlistsymbolmodel.h"

#include "httprest.h"
#include "kscheduler.h"
#include "jsonobjectlist.h"

#include "iexsymbolsmodel.h"
#include "iexdataendpoint.h"
#include "iexchartsmodel.h"
#include "iexcloudglobals.h"

#include "htmlwidget.h"

#include "kopiuser.h"
#include "kopirestless.h"

#include "kstyle.h"
#include "kopiappsettings.h"

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QQmlEngine>
#include <QCoreApplication>
#include <QStandardPaths>

#include <QMap>
#include <QtMath>

static QString numberToText(uint number)
{
    static QMap<uint, QString> numbers;

    //Only initialize once
    if (numbers.isEmpty())
    {
        numbers[0] = "zero";
        numbers[1] = "one";
        numbers[2] = "two";
        numbers[3] = "three";
        numbers[4] = "four";
        numbers[5] = "five";
        numbers[6] = "six";
        numbers[7] = "seven";
        numbers[8] = "eight";
        numbers[9] = "nine";
        numbers[10] = "ten";
        numbers[11] = "eleven";
        numbers[12] = "twelve";
        numbers[13] = "thirteen";
        numbers[14] = "fourteen";
        numbers[15] = "fifteen";
        numbers[16] = "sixteen";
        numbers[17] = "seventeen";
        numbers[18] = "eighteen";
        numbers[19] = "nineteen";
        numbers[20] = "twenty";
        numbers[30] = "thirty";
        numbers[40] = "forty";
        numbers[50] = "fifty";
        numbers[60] = "sixty";
        numbers[70] = "seventy";
        numbers[80] = "eighty";
        numbers[90] = "ninety";
    }

    static QMap<uint, QString> powers;

    //Only initialize once
    if (powers.isEmpty())
    {
        powers[2] = "hundred";
        powers[3] = "thousand";
        powers[6] = "million";
        powers[9] = "billion";
    }

    QString output;

    if (number < 21)
    {
        output = numbers[number];
    }
    else if (number < 100)
    {
        output = numbers[10 * qFloor(number / 10)];
        uint remainder = number % 10;

        if (remainder > 0)
            output += "-" + numberToText(remainder);
    }
    else
    {
        uint power = 2;
        uint place = 0;
        QString powerString;

        //QMap::keys is ordered
        foreach (uint pow, powers.keys())
        {
            uint place_value = qPow(10, pow);
            uint tmp_place = qFloor(number / place_value);
            if (tmp_place < 1)
                break;

            place = tmp_place;
            power = pow;
            powerString = powers[pow];
        }

        if (power > 0)
        {
            output = numberToText(place) + " " + powerString;
            uint remainder = number % uint(qPow(10, power));

            if (remainder > 0)
                output += " " + numberToText(remainder);
        }
    }

    return output;
}

static QObject *watchlistsModelSingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return WatchListsModel::instance();
}

static QObject *iexGlobalsSingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return IEXCloudGlobals::instance();
}

static QObject *iexDataSymbolModelInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return IEXSymbolsModel::instance();
}

static QObject *kopiSingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return Kopi::instance();
}

static QObject *portfolioModelSingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return PortfolioListModel::instance();
}

static QObject *kopiAppSettingsSingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return KopiAppSettings::instance();
}

static QObject *kstyleSingletonProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return KStyle::instance();
}

class Kopi::Private
{
public:
    int status;
    QString localStorePath;
};

Kopi *Kopi::m_instance = nullptr;
Kopi *Kopi::instance()
{
    if(m_instance == nullptr)
        m_instance = new Kopi;

    return m_instance;
}

Kopi::Kopi(QObject *parent)
    :QObject(parent)
      ,m_data(new Private)
{
    m_data->status = Blank;

}

Kopi::~Kopi()
{
    delete m_data;
    m_data = nullptr;
}

int Kopi::status() const
{
    return m_data->status;
}

QString Kopi::localStorePath() const
{
    return m_data->localStorePath;
}

void Kopi::setLocalStorePath(const QString &path)
{
    if(m_data->localStorePath != path) {
        m_data->localStorePath = path;
        emit localStorePathChanged(path);
    }
}

bool Kopi::storeLocally()
{
    //storing all symbols in cache/allsymbols.json array
    QDir pwdDir(m_data->localStorePath);
    if(pwdDir.cd("cache")) {
        QFile file(pwdDir.path() + "/allsymbols.json");
        if(file.open(QIODevice::WriteOnly)) {
            QTextStream datastream(&file);
            QJsonDocument jsdoc(IEXSymbolsModel::instance()->toJsonArray());
            datastream << jsdoc.toJson();
        }

        file.close();
    }

    //storing all symbols in watchlists/watchlists.json array
    pwdDir.setPath(m_data->localStorePath);
    if(pwdDir.cd("watchlists")) {
        QFile file(pwdDir.path() + "/watchlists.json");
        if(file.open(QIODevice::WriteOnly)) {
            QTextStream datastream(&file);
            QJsonDocument jsdoc(WatchListsModel::instance()->toJSON());
            datastream << jsdoc.toJson();
        }

        file.close();
        return true;
    }

    return false;
}

bool Kopi::readLocalStore()
{
    QDir pwdDir(m_data->localStorePath);

    //reading all symbols cached
    if(pwdDir.cd("cache")) {
        QFile file(pwdDir.path() + "/allsymbols.json");
        if(file.open(QIODevice::ReadOnly)) {
            QJsonDocument jsdoc = QJsonDocument::fromJson(file.readAll());
            IEXSymbolsModel::instance()->fromJsonArray(jsdoc.array());
            file.close();
        }
    }

    //reading watchlists
    pwdDir.setPath(m_data->localStorePath);
    if(pwdDir.cd("watchlists")) {
        QFile file(pwdDir.path() + "/watchlists.json");
        if(file.open(QIODevice::ReadOnly)) {
            QJsonDocument jsdoc = QJsonDocument::fromJson(file.readAll());
            WatchListsModel::instance()->fromJSON(jsdoc.object());
            file.close();
            return true;
        }
    }

    return false;
}

void Kopi::setStatus(int status)
{
    if(m_data->status != status) {
        m_data->status = status;
        emit statusChanged(m_data->status);
    }
}

bool Kopi::checkDefaultLocalStore()
{
    QDir pwdDir(QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0]);

    //if local store is not present then let's create it
    if(!pwdDir.exists("kopi-localstore"))
        if(!pwdDir.mkdir("kopi-localstore"))
            return false;

    pwdDir.cd("kopi-localstore");

    //create the necessary folders if they do not exist
    if(!pwdDir.exists("watchlists"))
        pwdDir.mkdir("watchlists");
    if(!pwdDir.exists("cache/stocks")) {
        pwdDir.mkpath("cache/stocks");
    }

    setLocalStorePath(pwdDir.path());
    return true;
}

QString Kopi::stringify(uint number)
{
    return numberToText(number);
}

void registerToQml()
{
    qmlRegisterSingletonType<Kopi>("Kopi", 1, 0, "Kopi", kopiSingletonProvider);
    qmlRegisterSingletonType<PortfolioListModel>("Kopi", 1, 0, "PortfolioListModel", portfolioModelSingletonProvider);

    qmlRegisterSingletonType<IEXSymbolsModel>("Kopi", 1, 0, "IEXSymbolsModel", iexDataSymbolModelInstance);
    qmlRegisterSingletonType<IEXCloudGlobals>("Kopi", 1, 0, "IEXCloudGlobals", iexGlobalsSingletonProvider);

    qmlRegisterSingletonType<KopiAppSettings>("Kopi", 1, 0, "KopiAppSettings", kopiAppSettingsSingletonProvider);
    qmlRegisterSingletonType<KStyle>("Kopi", 1, 0, "KStyle", kstyleSingletonProvider);
    qmlRegisterSingletonType<WatchListsModel>("Kopi", 1, 0, "WatchListsModel", watchlistsModelSingletonProvider);

    qmlRegisterType<Portfolio>("Kopi", 1, 0, "Portfolio");
    qmlRegisterType<Asset>("Kopi", 1, 0, "Asset");
    qmlRegisterType<Trade>("Kopi", 1, 0, "Trade");
    qmlRegisterType<AssetListModel>("Kopi", 1, 0, "AssetListModel");
    qmlRegisterType<TradeListModel>("Kopi", 1, 0, "TradeListModel");
    qmlRegisterType<HttpRest>("Kopi", 1, 0, "HttpRest");
    qmlRegisterType<IEXDataEndpoint>("Kopi", 1, 0, "IEXDataEndpoint");
    qmlRegisterType<HtmlWidget>("Kopi", 1, 0, "HtmlWidget");
    qmlRegisterType<KSymbol>("Kopi", 1, 0, "KSymbol");
    qmlRegisterType<KSymbolModel>("Kopi", 1, 0, "KSymbolModel");
    qmlRegisterType<KAccount>("Kopi", 1, 0, "KAccount");
    qmlRegisterType<KopiUser>("Kopi", 1, 0, "KopiUser");
    qmlRegisterType<WatchListSymbolModel>("Kopi", 1, 0, "WatchListSymbolModel");
    qmlRegisterType<IEXChartsModel>("Kopi", 1, 0, "IEXChartsModel");
    qmlRegisterType<KScheduler>("Kopi", 1, 0, "KScheduler");
    qmlRegisterType<JsonObjectList>("Kopi", 1, 0, "JsonObjectList");
}

Q_COREAPP_STARTUP_FUNCTION(registerToQml)
