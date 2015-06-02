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

    void on_checkBoxRangeNorm_clicked();

    void on_checkBoxR2Enable_clicked();

    void on_checkBoxCMS_clicked();

    void on_checkBoxLsr_clicked();

    void on_checkBoxDsr_clicked();

    void on_checkBox3x3_clicked();

    void on_doubleSpinBoxLogThreshold_editingFinished();

    void on_doubleSpinBoxSigThreshold_editingFinished();

    void on_doubleSpinBoxCCORThreshold_editingFinished();

    void on_doubleSpinBoxSQIThreshold_editingFinished();

private:
    Ui::DialogSetting *ui;
};

#endif // DIALOGSETTING_H
