#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_dt(0.3),
    m_count(0),
    m_schedule_impulse_flag(false),
    m_running_flag(false)
{
    ui->setupUi(this);

    m_system_timer = new QTimer(this);
    connect(m_system_timer, SIGNAL(timeout()), this, SLOT(updateSystem()));

    ui->graph_gl->dataPoints().resize(2);
    ui->graph_gl->dataPointColors().resize(2);
    ui->graph_gl->dataPointColors()[0] = QColor(Qt::white);
    //ui->graph_gl->dataPointColors()[1] = QColor(235, 237, 161);
    ui->graph_gl->dataPointColors()[1] = QColor(Qt::red);

    std::vector<double> a = { 1, ui->time_constant_dsb->value() };
    std::vector<double> b = { 1 };
    m_systemResponse.setCoeffs(a, b);

    ui->dt_dsb->setValue(m_dt);
    ui->minX_dsb->setValue(0);
    ui->maxX_dsb->setValue(60);
    ui->minY_dsb->setValue(-4);
    ui->maxY_dsb->setValue(4);

    ui->input_gain_dsb->setValue(0.5);
    ui->time_constant_dsb->setValue(0.5);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_impulse_btn_clicked() {
    m_schedule_impulse_flag = true;
}

void MainWindow::on_input_gain_dsb_valueChanged(const double &) {

}

void MainWindow::on_time_constant_dsb_valueChanged(const double &) {

}

void MainWindow::on_dt_dsb_valueChanged(const double &) {

}

void MainWindow::on_start_btn_clicked() {
    qDebug() << "Start Pressed";
    if (!m_running_flag) {
        qDebug() << "Running. ";
        m_running_flag = true;
        m_dt = ui->dt_dsb->value();

        updateCoefficients();

        m_system_timer->setInterval(qRound(ui->dt_dsb->value() * 1000.0));
        m_count = 0;

        for (int i = 0; i < ui->graph_gl->dataPoints().length(); i++) {
            ui->graph_gl->dataPoints()[i].clear();
        }

        m_system_timer->start();
    }
}

void MainWindow::on_stop_btn_clicked() {
    m_system_timer->stop();
    m_running_flag = false;
}

void MainWindow::on_minX_dsb_valueChanged(const double & x) {
    if (x < ui->graph_gl->maxX()) {
        ui->graph_gl->setMinX(x);
    } else {
        ui->graph_gl->setMinX(ui->graph_gl->maxX());
        ui->graph_gl->setMaxX(x);
    }
}

void MainWindow::on_minY_dsb_valueChanged(const double & y) {
    if (y < ui->graph_gl->maxY()) {
        ui->graph_gl->setMinY(y);
    } else {
        ui->graph_gl->setMinY(ui->graph_gl->maxY());
        ui->graph_gl->setMaxY(y);
    }
}

void MainWindow::on_maxX_dsb_valueChanged(const double & x) {
    if (x > ui->graph_gl->minX()) {
        ui->graph_gl->setMaxX(x);
    } else {
        ui->graph_gl->setMaxX(ui->graph_gl->minX());
        ui->graph_gl->setMinX(x);
    }
}

void MainWindow::on_maxY_dsb_valueChanged(const double & y) {
    if (y > ui->graph_gl->minY()) {
        ui->graph_gl->setMaxY(y);
    } else {
        ui->graph_gl->setMaxY(ui->graph_gl->minY());
        ui->graph_gl->setMinY(y);
    }
}

void MainWindow::updateSystem() {
    if (m_running_flag) {

        if (m_count > ui->graph_gl->maxX()) {
            double range = ui->graph_gl->maxX() - ui->graph_gl->minX();
            ui->maxX_dsb->setValue(m_count);
            ui->minX_dsb->setValue(m_count - range);
        }

        double l_input = 0;
        if (m_schedule_impulse_flag) {
            m_schedule_impulse_flag = false;
            l_input += ui->input_gain_dsb->value();
        }
        if (ui->step_cb->isChecked()) {
            l_input += ui->input_gain_dsb->value();
        }

        double l_output = m_systemResponse.response(l_input);

        QVector<QPointF> points;
        points.resize(2);
        points[0] = QPointF(m_count, l_input);
        points[1] = QPointF(m_count, l_output);

        ui->graph_gl->dataPoints()[0].append(points[0]);
        ui->graph_gl->dataPoints()[1].append(points[1]);

        m_count += m_dt;
    }
}

void MainWindow::updateCoefficients() {
    std::vector<double> a = { 1.0/m_dt, -ui->time_constant_dsb->value() };
    std::vector<double> b = { 1 };
    m_systemResponse.setCoeffs(a, b);
}
