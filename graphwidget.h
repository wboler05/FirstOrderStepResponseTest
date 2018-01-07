#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QOpenGLWidget>
#include <QPainter>
#include <QTimer>

class GraphWidget : public QOpenGLWidget
{
public:
    GraphWidget(QWidget * parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~GraphWidget();


    QVector<QVector<QPointF>> & dataPoints() { return m_data_points; }
    QVector<QColor> & dataPointColors() { return m_data_point_colors; }

    void setMinX(const double & x) { m_min_x = x; }
    void setMaxX(const double & x) { m_max_x = x; }
    void setRangeX(const double & minX, const double & maxX) {
        setMinX(minX); setMaxX(maxX);
    }

    void setMinY(const double & y) { m_min_y = y; }
    void setMaxY(const double & y) { m_max_y = y; }
    void setRangeY(const double & minY, const double & maxY) {
        setMinY(minY); setMaxY(maxY);
    }

    const double & minX() { return m_min_x; }
    const double & maxX() { return m_max_x; }
    QPointF rangeX() { return QPointF(m_min_x, m_max_x); }

    const double & minY() { return m_min_y; }
    const double & maxY() { return m_max_y; }
    QPointF rangeY() { return QPointF(m_min_y, m_max_y); }

    double scaleDataToPlotX(const double & x);
    double scaleDataToPlotY(const double  & y);


protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int x, int y);

private:
    QVector<QVector<QPointF>> m_data_points;
    QVector<QColor> m_data_point_colors;

    double m_min_x=0;
    double m_max_x=0;
    double m_min_y=0;
    double m_max_y=0;

};

#endif // GRAPHWIDGET_H
