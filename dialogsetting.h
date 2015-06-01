#ifndef DIALOGSETTING_H
#define DIALOGSETTING_H

#include <QDialog>
#include "rvp900.h"
extern RVP900 rvp9;
namespace Ui {
class DialogSetting;
}

class DialogSetting : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSetting(QWidget *parent = 0);
    ~DialogSetting();

private slots:
    void on_comboBoxProcMode_currentIndexChanged(int index);

    void on_comboBoxPulseAccu_currentIndexChanged(int index);

    void on_comboBoxWinType_currentIndexChanged(int index);

    void on_comboBoxBinNum_currentIndexChanged(int index);

private:
    Ui::DialogSetting *ui;
};

#endif // DIALOGSETTING_H
