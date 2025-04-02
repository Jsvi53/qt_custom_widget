/***
 * @Date: 2025-04-01 15:00:56
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-04-01 15:18:29
 * @FilePath: \qt_custom_widget\include\basemodule\configs.h
 */
#pragma once
#include <QString>

// Measurement Item
namespace SYSCONFIGS {
    struct MeasurementItem {
        // default vibration parmeters
        bool accelerationRMS;
        bool acceleration0P;
        bool accelerationPP;
        bool speedRMS;
        bool speed0P;
        bool speedPP;
        bool speedCrest;
        bool speedPhase;
        bool speedPhaseAplitude;

        // default displacement parmeters
        bool displacementRMS;
        bool displacement0P;
        bool displacementPP;
        bool displacementCrest;
        bool displacementPhase;
        bool displacementPhaseAplitude;

        // default route setup parmeters
        bool showRouteSummary;
        bool detailRouteGuidance;
    };
}  // namespace SYSCONFIGS

class SystemConfigs
{
public:
    static SystemConfigs &instance();
    // 测量项,默认值为false
    SYSCONFIGS::MeasurementItem measurementItem
    {
        false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
    }

private:
    SystemConfigs()                                 = default;
    SystemConfigs(const SystemConfigs &)            = delete;  // 禁止拷贝构造函数
    SystemConfigs &operator=(const SystemConfigs &) = delete;  // 禁止赋值操作符重载
    ~SystemConfigs()                                = default;

    // 其他成员变量和方法
    void loadJsonParams();
};
