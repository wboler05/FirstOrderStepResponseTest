#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>
#include <QTimer>

#include "systemresponseobject.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void on_impulse_btn_clicked();
    void on_input_gain_dsb_valueChanged(const double &);
    void on_time_constant_dsb_valueChanged(const double &);
    void on_dt_dsb_valueChanged(const double &);
    void on_start_btn_clicked();
    void on_stop_btn_clicked();

    void on_minX_dsb_valueChanged(const double &);
    void on_minY_dsb_valueChanged(const double &);
    void on_maxX_dsb_valueChanged(const double &);
    void on_maxY_dsb_valueChanged(const double &);

    void updateSystem();
    void updateCoefficients();

private:
    Ui::MainWindow *ui;
    QPointer<QTimer> m_system_timer;
    double m_dt;

    double m_count;

    SystemResponseObject m_systemResponse;

    bool m_schedule_impulse_flag;
    bool m_running_flag;
};

#endif // MAINWINDOW_H
