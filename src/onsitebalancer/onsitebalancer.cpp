#include "onsitebalancer/onsitebalancer.h"
#include <QDebug>
#include <QEasingCurve>
#include <QPainter>
#include <QPainterPath>

OnSiteBalancer::OnSiteBalancer(QWidget *parent)
    : QMainWindow(parent),
      homeScreen(new Hs::HomeScreen(this)),
      settingScreen(new Ss::SettingScreen(this))
{
    // 基础设置
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    setStyleSheet("background: transparent;");
    resize(1280, 800);

    // 页面初始化
    homeScreen->setGeometry(rect());
    settingScreen->setGeometry(rect());
    homeScreen->show();
    settingScreen->hide();
    currentPage = homeScreen;

    // 样式设置
    homeScreen->setStyleSheet(R"(
        Hs--HomeScreen {
            background: #FFFFFF;
            border-radius: 12px;
            border: 1px solid #E0E0E0;
        }
    )");

    settingScreen->setStyleSheet(R"(
        Ss--SettingScreen {
            background: #FAFAFA;
            border-radius: 12px;
            border: 1px solid #E0E0E0;
        }
    )");

    // 连接信号
    connect(homeScreen->getButton("home_SettingButton"), &QPushButton::clicked, [=]() {
        triggerTransition(settingScreen, homeScreen->getButton("home_SettingButton"));
    });

    connect(settingScreen->getButton("naviBtn_l"), &QPushButton::clicked, [=]() {
        reverseTransition(homeScreen, settingScreen->getButton("naviBtn_l"));
    });
}

OnSiteBalancer::~OnSiteBalancer()
{
    delete scaleAnim;
    delete fadeAnim;
    delete blurEffect;
}

void OnSiteBalancer::triggerTransition(QWidget* newPage, QPushButton* triggerBtn)
{
    if (newPage == currentPage) return;

    // 清理旧动画
    if(scaleAnim) scaleAnim->deleteLater();
    if(fadeAnim) fadeAnim->deleteLater();
    if(blurEffect) blurEffect->deleteLater();

    // 计算动画起点
    const QPoint globalPos = triggerBtn->mapToGlobal(triggerBtn->rect().center());
    const QPoint startPos = mapFromGlobal(globalPos);

    // 设置旧页面模糊效果
    blurEffect = new QGraphicsBlurEffect(currentPage);
    blurEffect->setBlurRadius(0);
    currentPage->setGraphicsEffect(blurEffect);

    // 准备新页面
    newPage->setGeometry(QRect(startPos, QSize(1, 1)));
    newPage->show();
    newPage->raise();

    // 几何动画
    scaleAnim = new QPropertyAnimation(newPage, "geometry");
    scaleAnim->setDuration(600);
    scaleAnim->setStartValue(QRect(startPos, QSize(1, 1)));
    scaleAnim->setEndValue(rect());
    scaleAnim->setEasingCurve(QEasingCurve::OutBack);

    // 颜色渐变
    fadeAnim = new QVariantAnimation;
    fadeAnim->setDuration(500);
    fadeAnim->setStartValue(QColor(255, 255, 255, 0));
    fadeAnim->setEndValue(QColor(255, 255, 255, 220));

    // 动画更新
    connect(scaleAnim, &QPropertyAnimation::valueChanged, [=](const QVariant &value) mutable {
        QRect rect = value.toRect();
        QPainterPath maskPath;
        maskPath.addRoundedRect(rect, 12, 12);
        newPage->setMask(QRegion(maskPath.toFillPolygon().toPolygon()));

        qreal progress = rect.width() / static_cast<qreal>(width());
        blurEffect->setBlurRadius(static_cast<int>(12 * (1 - progress)));
    });

    connect(fadeAnim, &QVariantAnimation::valueChanged, [=](const QVariant &value) {
        newPage->setStyleSheet(QString(R"(
            Ss--SettingScreen {
                background: %1;
                border-radius: 12px;
            }
        )").arg(value.value<QColor>().name(QColor::HexArgb)));
    });

    // 动画完成
    connect(scaleAnim, &QPropertyAnimation::finished, [=]() {
        currentPage->hide();
        currentPage = newPage;
        newPage->clearMask();
        blurEffect->deleteLater();
        blurEffect = nullptr;
    });

    scaleAnim->start();
    fadeAnim->start();
}

void OnSiteBalancer::reverseTransition(QWidget* targetPage, QPushButton* triggerBtn)
{
    if (currentPage == targetPage) return;

    // 清理旧动画
    if(scaleAnim) scaleAnim->deleteLater();
    if(fadeAnim) fadeAnim->deleteLater();
    if(blurEffect) blurEffect->deleteLater();

    // 计算动画终点
    const QPoint globalPos = triggerBtn->mapToGlobal(triggerBtn->rect().center());
    const QPoint endPos = mapFromGlobal(globalPos);

    // 显示目标页面
    targetPage->show();
    targetPage->lower();

    // 几何动画
    scaleAnim = new QPropertyAnimation(currentPage, "geometry");
    scaleAnim->setDuration(600);
    scaleAnim->setStartValue(rect());
    scaleAnim->setEndValue(QRect(endPos, QSize(1, 1)));
    scaleAnim->setEasingCurve(QEasingCurve::InBack);

    // 颜色渐变
    fadeAnim = new QVariantAnimation;
    fadeAnim->setDuration(500);
    fadeAnim->setStartValue(QColor(250, 250, 250, 220));
    fadeAnim->setEndValue(QColor(250, 250, 250, 0));

    // 动画更新
    connect(scaleAnim, &QPropertyAnimation::valueChanged, [=](const QVariant &value) mutable {
        QRect rect = value.toRect();
        QPainterPath maskPath;
        maskPath.addRoundedRect(rect, 12, 12);
        currentPage->setMask(QRegion(maskPath.toFillPolygon().toPolygon()));
    });

    connect(fadeAnim, &QVariantAnimation::valueChanged, [=](const QVariant &value) {
        currentPage->setStyleSheet(QString(R"(
            Ss--SettingScreen {
                background: %1;
                border-radius: 12px;
            }
        )").arg(value.value<QColor>().name(QColor::HexArgb)));
    });

    // 动画完成
    connect(scaleAnim, &QPropertyAnimation::finished, [=]() {
        currentPage->hide();
        currentPage = targetPage;
        targetPage->raise();
        currentPage->clearMask();
    });

    scaleAnim->start();
    fadeAnim->start();
}