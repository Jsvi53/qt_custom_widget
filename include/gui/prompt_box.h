#ifndef PROMPT_BOX_H
#define PROMPT_BOX_H

#include <QWidget>

namespace Ui {
class prompt_box;
}

class prompt_box : public QWidget
{
    Q_OBJECT

public:
    explicit prompt_box(QWidget *parent = nullptr);
    ~prompt_box();

private:
    Ui::prompt_box *ui;
};

#endif // PROMPT_BOX_H
