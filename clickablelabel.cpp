#include "clickablelabel.h"

ClickableLabel::ClickableLabel(int id,QWidget* parent)
    : QLabel(parent) {
    this->id=id;
}

void ClickableLabel::mousePressEvent(QMouseEvent* event){
    Q_UNUSED(event);
    emit clicked(id);
}
