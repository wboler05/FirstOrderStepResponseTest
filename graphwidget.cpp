#include "graphwidget.h"

GraphWidget::GraphWidget(QWidget * parent, Qt::WindowFlags f) :
    QOpenGLWidget(parent, f)
{
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->setInterval(16);
    timer->start();
}

GraphWidget::~GraphWidget() {

}

void GraphWidget::initializeGL() {

}

void GraphWidget::paintGL() {
    QPainter painter(this);
    painter.setBrush(QBrush(QColor(88, 113, 153)));
    painter.drawRect(rect());

    if (m_data_points.length() != 0) {
        if (m_data_point_colors.length() == m_data_points.length()) {

            for (int i = 0; i < m_data_points.length(); i++) {
                for (int p = 0; p < m_data_points.at(i).length(); p++) {
                    const QPointF & point = m_data_points.at(i).at(p);
                    if (point.x() > m_min_x && point.x() < m_max_x &&
                        point.y() > m_min_y && point.y() < m_max_y) {

                        QPointF newPoint = QPointF(scaleDataToPlotX(point.x()),
                                        scaleDataToPlotY(point.y()));

                        QPen pen(m_data_point_colors.at(i));
                        pen.setWidth(5);
                        painter.setPen(pen);
                        painter.drawPoint(newPoint);
                    }
                }
            }
        }
    }


}

void GraphWidget::resizeGL(int x, int y) {

}

double GraphWidget::scaleDataToPlotX(const double & x) {
    return ((double) width() / (m_max_x - m_min_x)) * (x - m_min_x);
}

double GraphWidget::scaleDataToPlotY(const double  & y) {
    return ((double) height() / (m_min_y - m_max_y)) * (y - m_max_y);
}
