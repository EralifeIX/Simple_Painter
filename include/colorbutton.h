#include "QPushButton"

#ifndef COLORBUTTON_H
#define COLORBUTTON_H

class ColorButton : public QPushButton {
    Q_OBJECT
public:
    explicit ColorButton(QWidget *parent = nullptr, const QColor& color = Qt::black);
private:
    const QColor _color;

private slots:
    void slotColorChanged();

signals:
    void colorChanged(QColor);
};
















#endif //COLORBUTTON_H
