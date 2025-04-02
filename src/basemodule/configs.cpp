#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#include "basemodule/configs.h"


SystemConfigs &SystemConfigs::instance()
{
    static SystemConfigs instance;
    return instance;
}

void SYSCONFIGS::SystemConfigs::loadJsonParams()
{
    // 打开 JSON 文件
    QFile file("configs.json");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "无法打开文件：" << file.fileName();
        exit(1);
    }

    // 读取文件内容
    QByteArray jsonData = file.readAll();
    file.close();

    // 解析 JSON 数据
    QJsonParseError parseError;
    QJsonDocument   jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

    if(parseError.error != QJsonParseError::NoError)
    {
        qDebug() << "JSON 解析错误：" << parseError.errorString();
        return;
    }

    // 检查 JSON 数据类型
    if(jsonDoc.isNull())
    {
        qDebug() << "JSON 数据为空";
        return;
    }

    if(jsonDoc.isObject())
    {
        // JSON 数据是一个对象
        QJsonObject jsonObject = jsonDoc.object();

        // 检查是否存在 "SystemConfigs" 对象
        if(!jsonObject.contains("SystemConfigs") || !jsonObject["SystemConfigs"].isObject())
        {
            qDebug() << "JSON 数据中缺少 SystemConfigs 对象";
            return;
        }

        QJsonObject systemConfigs = jsonObject["SystemConfigs"].toObject();

        // 检查是否存在 "measurementItem" 对象
        if(!systemConfigs.contains("measurementItem") || !systemConfigs["measurementItem"].isObject())
        {
            qDebug() << "JSON 数据中缺少 measurementItem 对象";
            return;
        }

        QJsonObject measurementItem = systemConfigs["measurementItem"].toObject();

        // 填充 measurementItem 成员变量
        measurementItem.accelerationRMS           = measurementItem["accelerationRMS"].toBool();
        measurementItem.acceleration0P            = measurementItem["acceleration0P"].toBool();
        measurementItem.accelerationPP            = measurementItem["accelerationPP"].toBool();
        measurementItem.speedRMS                  = measurementItem["speedRMS"].toBool();
        measurementItem.speed0P                   = measurementItem["speed0P"].toBool();
        measurementItem.speedPP                   = measurementItem["speedPP"].toBool();
        measurementItem.speedCrest                = measurementItem["speedCrest"].toBool();
        measurementItem.speedPhase                = measurementItem["speedPhase"].toBool();
        measurementItem.speedPhaseAplitude        = measurementItem["speedPhaseAplitude"].toBool();
        measurementItem.displacementRMS           = measurementItem["displacementRMS"].toBool();
        measurementItem.displacement0P            = measurementItem["displacement0P"].toBool();
        measurementItem.displacementPP            = measurementItem["displacementPP"].toBool();
        measurementItem.displacementCrest         = measurementItem["displacementCrest"].toBool();
        measurementItem.displacementPhase         = measurementItem["displacementPhase"].toBool();
        measurementItem.displacementPhaseAplitude = measurementItem["displacementPhaseAplitude"].toBool();
        measurementItem.showRouteSummary          = measurementItem["showRouteSummary"].toBool();
        measurementItem.detailRouteGuidance       = measurementItem["detailRouteGuidance"].toBool();

        qDebug() << "加载的配置：";
        qDebug() << "accelerationRMS:" << measurementItem.accelerationRMS;
        qDebug() << "acceleration0P:" << measurementItem.acceleration0P;
        qDebug() << "accelerationPP:" << measurementItem.accelerationPP;

    } else
    {
        qDebug() << "JSON 数据类型未知";
    }
}