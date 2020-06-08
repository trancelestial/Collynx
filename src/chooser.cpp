#include "chooser.h"
#include "ui_chooser.h"
#include "painter.h"

chooser::chooser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chooser)
{
    setStyleSheet("background : rgba(0,0,200,0.7);");
    hide();
    ui->setupUi(this);
}

chooser::~chooser()
{
    delete ui;
}

//postavi boju pickera, i pozicioniraj ga
void chooser::cshow(QPoint pos, int w, int h, QColor col)
{
    int y = pos.y();
    int x = pos.x();
    int xOffset = 0, yOffset = 0;

    if(y + height() > h)
        yOffset = height();

    if(x + width() > w)
        xOffset = width();

    int r,g,b;
    col.getRgb(&r,&g,&b);
    QString rgba = QString::number(r) + "," + QString::number(g) + "," + QString::number(b) + ", 0.5 ";

    setStyleSheet("background : rgba("+rgba+");");
    move(pos.x() - xOffset, pos.y() - yOffset);
    show();
}

int chooser::getButtonNum(){
    return findChildren<QPushButton*>().size();
}

QPushButton* chooser::getButton(int index){
    return findChildren<QPushButton*>().at(index-1);
}



