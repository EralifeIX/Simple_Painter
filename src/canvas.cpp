#include <QtWidgets>
#include "canvas.h"

Canvas::Canvas(QWidget* parent) : QWidget(parent) {
    setAttribute(Qt::WA_StaticContents);
    _modified = false;
    _drawing = false;
    _penWidth = 5;
    _penColor = Qt::black;
    createUI();
}

bool Canvas::openImage(const QString& fileName) {
    QImage image;
    if(!image.load(fileName))
        return false;

    QSize NewSize = image.size().expandedTo(size());
    resizeImage(image, NewSize);
    _image = image;
    _modified = false;
    update();
    return true;
}

bool Canvas::saveImage(const QString& fileName, const char* fileFormat) {
    QImage currentImage = _image;
    resizeImage(currentImage, size());

    if(currentImage.save(fileName, fileFormat)) {
        _modified = false;
        return true;
    }
    return false;
}

void Canvas::setPenColor(const QColor& color) {
    _penColor = color;
}

void Canvas::setPenWidth(int width) {
    _penWidth = width;
}

void Canvas::createUI() {

    int i = 0;
    int k = 0;

    QSlider* slider = new QSlider(Qt::Horizontal, this);
    slider->setRange(0, 200);
    slider->setValue(5);
    slider->setGeometry(1000, 120, 200, 10);
    connect(slider, SIGNAL(sliderMoved(int)), this,  SLOT(slotSetWidth(int)));

    for(auto color : this->getPenColor()) {
        auto* colorButton = new ColorButton(this, color);
        QString buttonStyle = QString("background-color: %1").arg(color.name());
        colorButton->setStyleSheet(buttonStyle);
        colorButton->setEnabled(true);

        if(k<7)
            colorButton->setGeometry(1000 + i, 40, 20 ,20);
        else
            colorButton->setGeometry(1000 + i - 210, 70, 20 ,20);

        connect(colorButton, SIGNAL(colorChanged(QColor)), this, SLOT(slotChangeColor(QColor)));
        i+=30;
        k++;
    }
}


void Canvas::slotClearImage() {
    _image.fill(Qt::white);
    _modified = true;
    update();
}

void Canvas::slotChangeColor(QColor color) {
    if(color.isValid())
        this->setPenColor(color);
}

void Canvas::slotSetWidth(int width) {
    _penWidth = width;
}


void Canvas::mousePressEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        _lastPoint = event->pos();
        _drawing = true;
    }
}

void Canvas::mouseMoveEvent(QMouseEvent* event) {
    if((event->buttons() & Qt::LeftButton) && _drawing) {
        drawLineTo(event->pos());
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent* event) {
    if((event->buttons() & Qt::LeftButton) && _drawing) {
        drawLineTo(event->pos());
        _drawing = false;
    }
}

void Canvas::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    QRect rect = event->rect();
    painter.drawImage(rect, _image, rect);
}

void Canvas::resizeEvent(QResizeEvent* event) {
    if(width() > _image.width() || height() > _image.height()) {
        int newWidth = qMax(width() + 128, _image.width());
        int newHeight = qMax(height() + 128, _image.height());
        resizeImage(_image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void Canvas::drawLineTo(const QPoint& endPoint) {
    QPainter painter(&_image);
    painter.setPen(QPen(_penColor, _penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(_lastPoint, endPoint);
    _modified = true;
    int radius = (_penWidth / 2) + 2;
    update(QRect(_lastPoint, endPoint).normalized().adjusted(-radius, -radius, radius, radius));
    _lastPoint = endPoint;
}

void Canvas::resizeImage(const QImage& image, const QSize& newSize) {
    if(image.size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(Qt::white);
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), image);
    _image = newImage;
}
