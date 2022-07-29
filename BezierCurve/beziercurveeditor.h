#ifndef BEZIERCURVEEDITOR_H
#define BEZIERCURVEEDITOR_H

#include <QPen>
#include <QBrush>
#include <QWidget>

class BezierCurveEditor : public QWidget
{
    Q_OBJECT
public:
    explicit BezierCurveEditor(QWidget *parent = 0);
    ~BezierCurveEditor();
    int point_flag=0;

    const int NUM_POINTS = 4;
    const qreal POINT_RADIUS = 8.0;

    QPointF         m_points[4];
    QPen            m_pens[4];
    QBrush          m_brushes[4];
    Qt::GlobalColor m_colors[4];

    QPen        m_curvePen;

    bool        m_dragging;
    int         m_selectedPoint;

    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    QPointF myCubicTo(QPointF PT[],float t);



private:
    enum PointIndices {
        StartPoint = 0,
        ControlPoint1 = 1,
        ControlPoint2 = 2,
        EndPoint = 3
    };

};

#endif // BEZIERCURVEEDITOR_H
