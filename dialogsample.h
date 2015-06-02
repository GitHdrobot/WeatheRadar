#ifndef DIALOGSAMPLE_H
#define DIALOGSAMPLE_H

#include <QDialog>
#include "rvp900.h"
extern RVP900 rvp9;

namespace Ui {
class DialogSample;
}

class DialogSample : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSample(QWidget *parent = 0);
    ~DialogSample();

private slots:
    void on_dSpinBoxdBZCali_editingFinished();

    void on_pushButtonNoiseSet_clicked();

private:
    Ui::DialogSample *ui;
};

#endif // DIALOGSAMPLE_H
