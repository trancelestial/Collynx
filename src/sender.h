#ifndef SENDER_H
#define SENDER_H
#include "painter.h"
#include "lines.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QString>
#include <QPen>
//singleton
class Sender : public QObject
{
    Q_OBJECT
public:
    enum Tag{
        endline = -6969, color = -6966, width = -6696, shape = -6999, undo = -9699, id = -9696
    };
    bool send(QString toSend);
    bool send(QPoint tosend, QString id);
    void send(QPen &pen, QString id);
    void send(Tag t, QString id);
    void send(Shape::Type shapeType, QString id);
    int send(QByteArray toSend);
    bool makeConnection();
    static Sender & getInstance();
    Sender(Sender const&)         = delete;
    void operator=(Sender const&) = delete;
    void setPainterFriend(Painter * p);
    Painter * getPainterFriend();
    void setImg(bool value);
    bool getImg();
private:
    Sender(){}
    static bool connected;
    static bool receivingImage;
    static QByteArray image;
    QTcpSocket * mySocket;
    Painter * painterFriend;

protected:

public slots:
    void readyRead();
};

#endif // SENDER_H
