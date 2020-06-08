#include "painter.h"
#include "chooser.h"
#include "sender.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMainWindow *window = new QMainWindow();

    window->setAttribute( Qt::WA_TranslucentBackground );
    window->setWindowTitle(QString::fromUtf8("ColLynx"));
    window->setWindowFlags(Qt::FramelessWindowHint /*| Qt::WindowStaysOnTopHint*/);

    Painter w(window);
    Sender::getInstance().setPainterFriend(&w);
    window->setCentralWidget(&w);
    window->show();
    return a.exec();
}
