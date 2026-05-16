#pragma once

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>


class UIPanel : public QWidget
{
    Q_OBJECT

    public:
        explicit UIPanel(QWidget *parent = nullptr);

    private:
        QVBoxLayout *panel_layout;
        // QLabel *speed_label;
        QCheckBox *on_off_checkbox;

    signals:
        void run_simulation_toggled(bool is_running);
};