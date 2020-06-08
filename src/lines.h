#ifndef LINES_H
#define LINES_H

#include <QVector>
#include <QPolygon>
#include <QPoint>
#include <QDebug>
#include <QPen>
#include <QPainter>

class Shape
{
public:
    enum Type {line, ellipse, circle, rectangle, square};
    virtual void drawSelf(QPainter & screen) const = 0;
    virtual void addPoint(QPoint newPoint) = 0;
    virtual ~Shape() {}
};

class MyEllipse : public Shape
{
public:
    MyEllipse();
    void drawSelf(QPainter & screen) const;
    void addPoint(QPoint newPoint);
    ~MyEllipse() {}
    QRect rect;
protected:
    bool firstPoint;
};

class MyCircle : public MyEllipse
{
public:
    void addPoint(QPoint newPoint);
};

class MyRectangle : public Shape
{
public:
    MyRectangle();
    void drawSelf(QPainter & screen) const;
    void addPoint(QPoint newPoint);
    ~MyRectangle() {}
    QRect rect;
protected:
    bool firstPoint;
};

class MySquare : public MyRectangle
{
public:
    void addPoint(QPoint newPoint);
};

class MyLine : public Shape
{
    void drawSelf(QPainter & screen) const;
    void addPoint(QPoint newPoint);
    ~MyLine() {}
    QPolygon poly;
};

class Drawable
{
public:
    Drawable();
    Drawable(Shape::Type shapeType);
    void drawOn(QPainter & screen) const;
    Shape * shape;
    QPen pen;
};

class Lines
{
public:
    Lines();
    void drawAll(QPainter & screen) const;
    QVector<Drawable>& getLines();
    void changeLastType(Shape::Type shapeType);
    void addPoint(QPoint newPoint, Shape::Type shapeType);
    void newLine(Shape::Type shapeType);
    void newLine(QPen newPen, Shape::Type shapeType);
    void newLine(QPen newPen, int brushSize, Shape::Type shapeType);
    void setPen(QPen newPen);
    void setPen(int color, int brushSize);
    void setPenColor(const int color);
    void setPenWidth(const int brushSize);
    bool isShown;
    void undo();
private:
    QVector<Drawable> lines;
};

#endif // LINES_H
