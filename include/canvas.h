#ifndef CANVAS_H
#define CANVAS_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <vector>
#include "colorbutton.h"

class Canvas : public QWidget {
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = nullptr);

    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char* fileFormat);
    void setPenColor(const QColor &color);
    void setPenWidth(int width);
    void createUI();

    [[nodiscard]] const std::vector<QColor>& getPenColor() const {return _colors;};
    [[nodiscard]] bool isModified() const { return _modified; }
    [[nodiscard]] QColor penColor() const {return _penColor; }
    [[nodiscard]] int penWidth () const { return _penWidth; }

public slots:
    void slotClearImage();
    void slotChangeColor( QColor color);
    void slotSetWidth(int width);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    void drawLineTo(const QPoint &endPoint);
    void resizeImage(const QImage &image, const QSize& size);
    bool _modified;
    bool _drawing;
    QColor _penColor;
    int _penWidth;
    QImage _image;
    QPoint _lastPoint;
    const std::vector<QColor> _colors{ Qt::black, Qt::white,  Qt::darkGray,Qt::gray, Qt::darkRed, Qt::red, Qt::darkYellow,
        Qt::yellow, Qt::darkBlue, Qt::blue, Qt::darkMagenta,  Qt::magenta,Qt::darkGreen, Qt::green};

};



















#endif //CANVAS_H
