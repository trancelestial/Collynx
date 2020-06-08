#include "lines.h"

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

Lines::Lines() : isShown(true)
{
    newLine(Shape::Type::line);
}

MyEllipse::MyEllipse() : firstPoint(true)
{}

MyRectangle::MyRectangle() : firstPoint(true)
{}

void Lines::changeLastType(Shape::Type shapeType)
{
    delete lines.last().shape;
    switch (shapeType) {
    case Shape::Type::rectangle:
        lines.last().shape = new MyRectangle();
        break;
    case Shape::Type::square:
        lines.last().shape = new MySquare();
        break;
    case Shape::Type::ellipse:
        lines.last().shape = new MyEllipse();
        break;
    case Shape::Type::circle:
        lines.last().shape = new MyCircle();
        break;
    default:
        lines.last().shape = new MyLine();
        break;
    }
}

void MyLine::addPoint(QPoint newPoint)
{
    poly.append(newPoint);
}

void MyEllipse::addPoint(QPoint newPoint)
{
    if (firstPoint){
        firstPoint = false;
        rect.setTopLeft(newPoint);
        rect.setBottomRight(newPoint);
    } else {
        rect.setBottomRight(newPoint);
    }
}

void MyCircle::addPoint(QPoint newPoint)
{
    if (firstPoint){
        firstPoint = false;
        rect.setTopLeft(newPoint);
        rect.setBottomRight(newPoint);
    } else {
        QPoint fp = rect.topLeft();
        int dx = newPoint.x() - fp.x();
        int dy = newPoint.y() - fp.y();
        int length = std::max(std::abs(dx),std::abs(dy));
        newPoint.setX(fp.x()+sgn(dx)*length);
        newPoint.setY(fp.y()+sgn(dy)*length);
        rect.setBottomRight(newPoint);
    }
}

void MyRectangle::addPoint(QPoint newPoint)
{
    if (firstPoint){
        firstPoint = false;
        rect.setTopLeft(newPoint);
        rect.setBottomRight(newPoint);
    } else {
        rect.setBottomRight(newPoint);
    }
}

void MySquare::addPoint(QPoint newPoint)
{
    if (firstPoint){
        firstPoint = false;
        rect.setTopLeft(newPoint);
        rect.setBottomRight(newPoint);
    } else {
        QPoint fp = rect.topLeft();
        int dx = newPoint.x() - fp.x();
        int dy = newPoint.y() - fp.y();
        int length = std::max(std::abs(dx),std::abs(dy));
        newPoint.setX(fp.x()+sgn(dx)*length);
        newPoint.setY(fp.y()+sgn(dy)*length);
        rect.setBottomRight(newPoint);
    }
}

void MyEllipse::drawSelf(QPainter &screen) const
{
    //qDebug() << rect.topLeft();
    screen.drawEllipse(rect);
}

void MyLine::drawSelf(QPainter &screen) const
{
    if (poly.length()==1){
      screen.drawPoint(poly.first());
    } else {
      screen.drawPolyline(poly);
    }
}

void MyRectangle::drawSelf(QPainter &screen) const
{
    screen.drawRect(rect);
}

Drawable::Drawable()
{
    shape = new MyLine();
}

Drawable::Drawable(Shape::Type shapeType)
{
    switch (shapeType) {
    case Shape::Type::rectangle:
        shape = new MyRectangle();
        break;
    case Shape::Type::square:
        shape = new MySquare();
        break;
    case Shape::Type::ellipse:
        shape = new MyEllipse();
        break;
    case Shape::Type::circle:
        shape = new MyCircle();
        break;
    default:
        shape = new MyLine();
        break;
    }
}

void Drawable::drawOn(QPainter & screen) const
{
    screen.setPen(pen);
    //qDebug() << poly.length();
    shape->drawSelf(screen);
}

void Lines::drawAll(QPainter & screen) const
{
    if (!isShown) return;
    for (const auto l : lines){
        l.drawOn(screen);
    }
}

QVector<Drawable>& Lines::getLines()
{
    return lines;
}

void Lines::addPoint(QPoint newPoint, Shape::Type shapeType)
{
    Q_UNUSED(shapeType);
    lines.last().shape->addPoint(newPoint);
}

void Lines::newLine(QPen newPen, int brushSize, Shape::Type shapeType)
{
    Drawable newPoly(shapeType);
    newPen.setCapStyle(Qt::RoundCap);
    newPen.setWidth(brushSize);
    newPoly.pen = newPen;
    lines.append(newPoly);
}

void Lines::newLine(Shape::Type shapeType)
{
    Drawable newPoly(shapeType);
    QPen newPen(Qt::red);
    newPen.setCapStyle(Qt::RoundCap);
    int defaultWidth = 7;
    newPen.setWidth(defaultWidth);
    newPoly.pen = newPen;
    lines.append(newPoly);
}

void Lines::newLine(QPen newPen, Shape::Type shapeType)
{
    Drawable newPoly(shapeType);
    newPoly.pen = newPen;

    lines.append(newPoly);
}

void Lines::setPen(QPen newPen)
{
    lines.last().pen = newPen;
}

void Lines::setPen(int color, int brushSize)
{
    QColor col(color);
    QPen pen(col);
    pen.setWidth(brushSize);
    lines.last().pen = pen;
}

void Lines::undo()
{
    //the last poly is empty, so remove the 2nd last
    if (lines.length() > 1){
        //qDebug() << lines.length() << "before";
        QPen lastPen = lines.last().pen;
        int toDelete = lines.length() - 2;
        delete lines[toDelete].shape;
        lines.remove(toDelete);
    }
}

void Lines::setPenColor(const int color)
{
    QColor col(color);
    lines.last().pen.setColor(col);
}

void Lines::setPenWidth(const int brushSize)
{
    lines.last().pen.setWidth(brushSize);
}
