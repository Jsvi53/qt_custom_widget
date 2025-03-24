/*** 
 * @Date: 2025-03-23 18:43:09
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-25 00:20:46
 * @FilePath: \qt_custom_widget\include\onsitebalancer\onsitebalancer.h
 */
#pragma once
#include <QMainWindow>
#include <QPropertyAnimation>
#include <QVariantAnimation>
#include <QGraphicsBlurEffect>

#include "onsitebalancer/home.h"
#include "onsitebalancer/settingscreen.h"

namespace Hs {
class HomeScreen;
}
namespace Ss {
class SettingScreen;
}

class OnSiteBalancer : public QMainWindow
{
    Q_OBJECT
public:
    explicit OnSiteBalancer(QWidget *parent = nullptr);
    ~OnSiteBalancer();

private:
    // 成员函数声明（移除类名前缀）
    void triggerTransition(QWidget* newPage, QPushButton* triggerBtn);
    void reverseTransition(QWidget* targetPage, QPushButton* triggerBtn);

    // 成员变量
    Hs::HomeScreen* homeScreen;
    Ss::SettingScreen* settingScreen;
    QWidget* currentPage = nullptr;

    // 动画相关
    QPropertyAnimation* scaleAnim = nullptr;
    QVariantAnimation* fadeAnim = nullptr;
    QGraphicsBlurEffect* blurEffect = nullptr;

    QHash<QRect, QRegion> maskCache;
};