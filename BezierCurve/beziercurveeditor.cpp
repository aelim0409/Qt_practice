#include "beziercurveeditor.h"

#include <QPainter>
#include <QMouseEvent>
#include <QPainterPath>

BezierCurveEditor::BezierCurveEditor(QWidget *parent)
    : QWidget(parent)
    , m_curvePen(Qt::black)
    , m_dragging(false)
{
    m_curvePen.setWidth(4);

    m_colors[0] = Qt::yellow;
    m_colors[1] = Qt::red;
    m_colors[2] = Qt::blue;
    m_colors[3] = Qt::yellow;

    for (int i = 0; i < NUM_POINTS; i++) {
        m_pens[i]    = QPen(m_colors[i]);
        m_brushes[i] = QBrush(m_colors[i]);
    }
}

BezierCurveEditor::~BezierCurveEditor()
{

}

QPointF st;
QPointF ed;



QPointF BezierCurveEditor::myCubicTo(QPointF PT[],float t)
{
    QPointF P;

   P.setX( PT[0].x()*(1 - t) * (1 - t) * (1 - t) + 3 * (1 - t) *(1-t)* t * PT[1].x() + 3 * (1 - t) * t * t * PT[2].x() + t * t * t * PT[3].x());
   P.setY( PT[0].y() * (1 - t) * (1 - t) * (1 - t) + 3 * (1 - t) *(1-t)* t * PT[1].y() + 3 * (1 - t) * t * t * PT[2].y() + t * t * t * PT[3].y());

    qDebug()<<P.x()<<P.y();
    return P;
}
int pointFlag=0;
void BezierCurveEditor::mousePressEvent(QMouseEvent *event)
{



    if(event->buttons() & Qt::LeftButton)
    {
        qDebug()<<"dddddddddd"<<pointFlag;
        if(pointFlag==0)
        {   m_points[StartPoint]    = QPointF(event->pos());    pointFlag++;    qDebug()<<event->pos()<<pointFlag;}
        else if(pointFlag==1)
        {   m_points[ControlPoint1] =  QPointF(event->pos());   pointFlag++;    qDebug()<<event->pos()<<pointFlag;}
        else if(pointFlag==2)
        {   m_points[ControlPoint2] =  QPointF(event->pos());   pointFlag++;    qDebug()<<event->pos()<<pointFlag;}
        else if(pointFlag==3)
        {   m_points[EndPoint]      =  QPointF(event->pos());   pointFlag=0;    qDebug()<<event->pos()<<pointFlag;}

    }
/*
    if(event->buttons() & Qt::RightButton)
    {
        for(int i = 0; i < NUM_POINTS; i++) {
            if(distance(m_points[i], event->pos()) <= POINT_RADIUS) {
                m_selectedPoint = i;
                m_dragging = true;
                break;
            }
        }
    }
    */
}



void BezierCurveEditor::mouseMoveEvent(QMouseEvent *event)
{
    if(m_dragging) {
        m_points[m_selectedPoint] = event->pos();
    }
    update();
}

void BezierCurveEditor::mouseReleaseEvent(QMouseEvent *)
{
    m_dragging = false;
}

void BezierCurveEditor::resizeEvent(QResizeEvent *)
{

    m_points[StartPoint]    = QPointF(50, height() - 50);
    m_points[ControlPoint1] = QPointF(width() - 50, height() - 50);
    m_points[ControlPoint2] = QPointF(50, 50);
    m_points[EndPoint]      = QPointF(width() - 50, 50);


}

void BezierCurveEditor::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

   //QPen pen = QPen(Qt::black, Qt::SolidLine);
    //painter.setRenderHint(QPainter::Antialiasing, true);



    //curve 그리기
   // QPainterPath path;
   // path.moveTo(m_points[StartPoint]);
    //path.cubicTo(m_points[ControlPoint1], m_points[ControlPoint2], m_points[EndPoint]);
   // painter.drawPath(path);


    //if(pointFlag==4)
    //{
        st = m_points[StartPoint];

        for(float t = 0; t<=1.0;t+=0.02)
        {
            ed = myCubicTo(m_points,t);
           // painter.setPen(pen);
            painter.drawLine(st.x(),st.y(),ed.x(),ed.y());

            st=ed;
        }

        //pointFlag=0;
    //}

    //painter.drawLine( m_points[StartPoint],ed);

    for (int i = 0; i < NUM_POINTS; i++) {
        painter.setPen(m_pens[i]);
        painter.setBrush(m_brushes[i]);
        painter.drawEllipse(m_points[i], POINT_RADIUS, POINT_RADIUS);
    }

    painter.end();
}
