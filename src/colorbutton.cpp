#include "colorbutton.h"

ColorButton::ColorButton(QWidget *parent, const QColor& color) : _color(color), QPushButton(parent) {
    connect(this, SIGNAL(clicked()), this, SLOT(slotColorChanged()));
};

void ColorButton::slotColorChanged() {
    emit colorChanged(_color);
}
