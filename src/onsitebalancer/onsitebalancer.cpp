#include <QDebug>
#include <QEasingCurve>
#include <QPainter>
#include <QPainterPath>

#include "onsitebalancer/onsitebalancer.h"

OnSiteBalancer::OnSiteBalancer(QWidget *parent) : QMainWindow(parent), homeScreen(new Hs::HomeScreen(this)), settingScreen(new Ss::SettingScreen(this))
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

    // 连接信号
    connect(homeScreen->getButton("home_SettingButton"), &QPushButton::clicked, [=]() { triggerTransition(settingScreen, homeScreen->getButton("home_SettingButton")); });

    connect(settingScreen->getButton("naviBtn_l"), &QPushButton::clicked, [=]() { reverseTransition(homeScreen, settingScreen->getButton("naviBtn_l")); });
}

OnSiteBalancer::~OnSiteBalancer()
{
    delete scaleAnim;
    delete fadeAnim;
    delete blurEffect;
}

void OnSiteBalancer::triggerTransition(QWidget *newPage, QPushButton *triggerBtn)
{
    if(newPage == currentPage)
        return;

    // 清理旧动画
    if(scaleAnim)
        scaleAnim->deleteLater();
    if(fadeAnim)
        fadeAnim->deleteLater();
    if(blurEffect)
        blurEffect->deleteLater();

    // 计算动画起点
    const QPoint globalPos = triggerBtn->mapToGlobal(triggerBtn->rect().center());
    const QPoint startPos  = mapFromGlobal(globalPos);

    // 设置旧页面模糊效果
    blurEffect = new QGraphicsBlurEffect(currentPage);
    blurEffect->setBlurRadius(0);
    currentPage->setGraphicsEffect(blurEffect);

    // 准备新页面
    newPage->setGeometry(QRect(startPos, QSize(1, 1)));  // 设置初始位置
    newPage->show();
    newPage->raise();  // 确保新页面在最上层

    // 几何动画
    scaleAnim = new QPropertyAnimation(newPage, "geometry");  // 设置动画目标属性
    scaleAnim->setDuration(600);                              // 设置动画时长
    scaleAnim->setStartValue(QRect(startPos, QSize(1, 1)));   // 设置动画起始位置
    scaleAnim->setEndValue(rect());                           // 设置动画结束位置
    scaleAnim->setEasingCurve(QEasingCurve::OutCubic);        // 设置动画缓动曲线

    // 颜色渐变
    fadeAnim = new QVariantAnimation;
    fadeAnim->setDuration(500);
    fadeAnim->setStartValue(QColor(255, 255, 255, 0));
    fadeAnim->setEndValue(QColor(255, 255, 255, 220));

    // 动画更新
    connect(scaleAnim, &QPropertyAnimation::valueChanged, [=](const QVariant &value) mutable {
        QRect          rect = value.toRect();
        static QRegion cachedRegion;
        if(cachedRegion.rectCount() == 0 || rect != cachedRegion.boundingRect())
        {
            QPainterPath path;
            path.addRoundedRect(rect, 12, 12);
            cachedRegion = QRegion(path.toFillPolygon().toPolygon());
        }
        newPage->setMask(cachedRegion);
        // 模糊效果更新（见后续优化）
        qreal progress = rect.width() / static_cast<qreal>(width());
        blurEffect->setBlurRadius(static_cast<int>(8 * (1 - progress)));
    });

    connect(fadeAnim, &QVariantAnimation::valueChanged, [=](const QVariant &value) {
        QColor   color   = value.value<QColor>();
        QPalette palette = newPage->palette();
        palette.setColor(QPalette::Window, color);
        newPage->setPalette(palette);
        newPage->setAttribute(Qt::WA_OpaquePaintEvent, false);  // 允许透明
        newPage->update();                                      // 手动触发重绘
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

void OnSiteBalancer::reverseTransition(QWidget *targetPage, QPushButton *triggerBtn)
{
    if(currentPage == targetPage)
        return;

    // 清理旧动画
    if(scaleAnim)
        scaleAnim->deleteLater();
    if(fadeAnim)
        fadeAnim->deleteLater();
    if(blurEffect)
        blurEffect->deleteLater();

    // 计算动画终点
    const QPoint globalPos = triggerBtn->mapToGlobal(triggerBtn->rect().center());
    const QPoint endPos    = mapFromGlobal(globalPos);

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
        QRect        rect = value.toRect();
        QPainterPath maskPath;
        maskPath.addRoundedRect(rect, 12, 12);
        currentPage->setMask(QRegion(maskPath.toFillPolygon().toPolygon()));
    });

    connect(fadeAnim, &QVariantAnimation::valueChanged, [=](const QVariant &value) {
        QColor   color   = value.value<QColor>();
        QPalette palette = currentPage->palette();
        palette.setColor(QPalette::Window, color);
        currentPage->setPalette(palette);
        currentPage->setAttribute(Qt::WA_OpaquePaintEvent, false);  // 允许透明
        currentPage->update();                                      // 手动触发重绘
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