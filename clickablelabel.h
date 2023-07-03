#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QResizeEvent>

class ClickableLabel : public QLabel
{
public:
    ClickableLabel(int,QWidget* parent = nullptr);
signals:
    void clicked(int);
protected:
    Q_OBJECT
    int id;
    void mousePressEvent(QMouseEvent*) override;
};

#endif // CLICKABLELABEL_H
