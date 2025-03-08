/*** 
 * @Date: 2025-03-09 00:43:33
 * @LastEditors: jsvi53
 * @LastEditTime: 2025-03-09 00:43:40
 * @FilePath: /qt_custom_widget/include/fileapp/TemplateConfigPage.h
 */
#ifndef TEMPLATECONFIGPAGE_H
#define TEMPLATECONFIGPAGE_H

#include <QWidget>
#include "fileapp/TemplateParams.h"

namespace Ui {
    class TemplateConfigPage;
}

class TemplateConfigPage : public QWidget
{
    Q_OBJECT
public:
    explicit TemplateConfigPage(QWidget *parent = nullptr);
    ~TemplateConfigPage();

    void loadParams(const TemplateParams &params); // 加载参数

private:
    Ui::TemplateConfigPage *ui;
};

#endif // TEMPLATECONFIGPAGE_H