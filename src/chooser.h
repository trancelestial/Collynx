#ifndef CHOOSER_H
#define CHOOSER_H

#include <QDebug>
#include <QWidget>
#include <QPushButton>

namespace Ui {
class chooser;
}

class chooser : public QWidget
{
    Q_OBJECT

public:
    explicit chooser(QWidget *parent = 0);
    ~chooser();
    void cshow(QPoint pos, int w, int h, QColor col);
    QPushButton* getButton(int index);
    int getButtonNum();

private:
    Ui::chooser *ui;
};



#endif // CHOOSER_H
