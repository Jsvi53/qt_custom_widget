/*** 
 * @Date: 2025-03-08 23:59:29
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-08 23:59:33
 * @FilePath: /qt_custom_widget/include/fileapp/TemplateParams.h
 */
// TemplateParams.h
#ifndef TEMPLATEPARAMS_H
#define TEMPLATEPARAMS_H

#include <QString>

struct TemplateParams {
    QString sensorId;       // 传感器ID
    double maxRpm;          // 最大转速
    double calibrationFactor; // 校准因子
    // 其他参数...
};

#endif // TEMPLATEPARAMS_H