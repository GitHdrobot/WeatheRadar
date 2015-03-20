#ifndef DIALOGSAMPLE_H
#define DIALOGSAMPLE_H

#include <QDialog>

namespace Ui {
class DialogSample;
}

class DialogSample : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSample(QWidget *parent = 0);
    ~DialogSample();

private:
    Ui::DialogSample *ui;
};

#endif // DIALOGSAMPLE_H
