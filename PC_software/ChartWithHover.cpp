#include "ChartWithHover.h"
#include <QMouseEvent>
#include <QtDebug>
#include <QGraphicsRectItem>
#include <QGraphicsDropShadowEffect>
#include "WebsocketMgr.h"

ChartWithHover::ChartWithHover(QWidget* parent)
    : QChartView(parent), tooltipItem(nullptr), tooltipRect(nullptr)
{
    // ��ʼ��ͼ��
    chart = new QChart();
    chart->setTitle("Patient Total");
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setAnimationDuration(1000);
    chart->setAnimationEasingCurve(QEasingCurve::OutCubic);

    // ������������ϵ�к��������
    createLineSeries();

    // ��ʼ��������
    QValueAxis* axisX = new QValueAxis();
    axisX->setRange(0, 9);
    axisX->setLabelsVisible(false); // ���غ����ǩ
    chart->addAxis(axisX, Qt::AlignBottom);

    QValueAxis* axisY = new QValueAxis();
    axisY->setRange(0, 45);
    axisY->setTitleText("Number of Patients");
    chart->addAxis(axisY, Qt::AlignLeft);

    // ��������󶨵�����ϵ��
    series1->attachAxis(axisX);
    series1->attachAxis(axisY);
    series2->attachAxis(axisX);
    series2->attachAxis(axisY);

    areaSeries1->attachAxis(axisX);
    areaSeries1->attachAxis(axisY);
    areaSeries2->attachAxis(axisX);
    areaSeries2->attachAxis(axisY);


    // ����ͼ��
    this->setChart(chart);
    this->setRenderHint(QPainter::Antialiasing);
    this->setMouseTracking(true); // �������׷��

    // ��ʼ�������ͣ��ʾ��
    enableHoverEffect();
}

ChartWithHover::~ChartWithHover() {}


void ChartWithHover::addEmptyCirclesToSeries(QSplineSeries* series, const QColor& color)
{
    // ��ȡ QChartView �ĳ���
    QGraphicsScene* scene = this->scene();

    // ����ϵ���е��������ݵ�
    for (const QPointF& point : series->pointsVector()) {
        qDebug() << point;
        // �����ݵ�ӳ�䵽ͼ�����Ļ����ϵ
        QPointF screenPos = chart->mapToPosition(point);

        // ��ӡ�����Ե���
        qDebug() <<"point"<<point << "screenPos:" << screenPos;

        // ��������Բ��
        QGraphicsEllipseItem* circleItem = new QGraphicsEllipseItem(screenPos.x() - 5, screenPos.y() - 5, 10, 10);
        circleItem->setPen(QPen(color));        // ����ԲȦ��ɫ
        circleItem->setBrush(Qt::NoBrush);     // ����Բ
        circleItem->setZValue(10);             // ȷ��Բ����ʾ��ͼ���ϲ�

        // ��Բ����ӵ� QChartView �ĳ�����
        scene->addItem(circleItem);
    }
}



void ChartWithHover::createLineSeries()
{
    // ��һ������
    series1 = new QSplineSeries();
    *series1 << QPointF(0, 10) << QPointF(1, 80) << QPointF(2, 50)
        << QPointF(3, 20) << QPointF(4, 100) << QPointF(5, 120)
        << QPointF(6, 80) << QPointF(7, 60) << QPointF(8, 90)
        << QPointF(9, 100);

    QSplineSeries* bottomSeries1 = new QSplineSeries();
    *bottomSeries1 << QPointF(0, 0) << QPointF(9, 0);

    areaSeries1 = new QAreaSeries(series1, bottomSeries1);
    areaSeries1->setName("Temperature");
    areaSeries1->setBrush(QColor(50, 150, 255, 100)); // ��͸����ɫ�������
    
    chart->addSeries(areaSeries1);
    // �ڶ�������
    series2 = new QSplineSeries();
    *series2 << QPointF(0, 40) << QPointF(1, 50) << QPointF(2, 30)
        << QPointF(3, 10) << QPointF(4, 60) << QPointF(5, 86)
        << QPointF(6, 50) << QPointF(7, 70) << QPointF(8, 85)
        << QPointF(9, 40);

    QSplineSeries* bottomSeries2 = new QSplineSeries();
    *bottomSeries2 << QPointF(0, 0) << QPointF(9, 0);

    /*areaSeries2->setName(QString::fromLocal8Bit("��ѹ "));*/
    areaSeries2 = new QAreaSeries(series2, bottomSeries2);
    areaSeries2->setName("Voltage");
    areaSeries2->setBrush(QColor(255, 200, 0, 100)); // ��͸����ɫ�������
    chart->addSeries(areaSeries2);
}

void ChartWithHover::createLineSeries(std::shared_ptr<PatientData> patientdata)
{
    series1->clear();
    series2->clear();
    for (int i = 0; i < patientdata->_temperaturearray.size(); i++)
    {
        *series1 << QPoint(i, patientdata->_temperaturearray[i].toDouble());
        *series2 << QPoint(i, patientdata->_voltagearray[i].toDouble());
    }
    areaSeries1->setPointsVisible(true);
    areaSeries2->setPointsVisible(true);

    //// ����ɢ��ϵ�в�������ʽ
    //QScatterSeries* scatterSeries1 = new QScatterSeries();
    //scatterSeries1->setPointLabelsVisible(false);
    //scatterSeries1->setMarkerShape(QScatterSeries::MarkerShapeCircle);  // ���õ����״ΪԲ��
    //scatterSeries1->setMarkerSize(8);  // ���õ�Ĵ�С
    //scatterSeries1->setBrush(Qt::NoBrush);  // ���ÿ���Ч��
    //QPen pen1(Qt::blue);  // ������ɫ�߿�
    //pen1.setWidth(2);     // ���ñ߿���Ϊ3
    //scatterSeries1->setPen(pen1);  // Ӧ�ñ߿�

    //QScatterSeries* scatterSeries2 = new QScatterSeries();
    //scatterSeries2->setPointLabelsVisible(false);
    //scatterSeries2->setMarkerShape(QScatterSeries::MarkerShapeCircle);  // ���õ����״ΪԲ��
    //scatterSeries2->setMarkerSize(8);  // ���õ�Ĵ�С
    //scatterSeries2->setBrush(Qt::NoBrush);  // ���ÿ���Ч��
    //QPen pen2(Qt::yellow);  // ������ɫ�߿�
    //pen2.setWidth(2);       // ���ñ߿���Ϊ3
    //scatterSeries2->setPen(pen2);  // Ӧ�ñ߿�

    //// �������ݣ�������ݵ㵽ϵ����
    //for (int i = 0; i < patientdata->_temperaturearray.size(); ++i) {
    //    scatterSeries1->append(i, patientdata->_temperaturearray[i].toDouble());
    //    scatterSeries2->append(i, patientdata->_voltagearray[i].toDouble());
    //}

    //// ��ϵ����ӵ�ͼ����
    //chart->addSeries(scatterSeries1);
    //chart->addSeries(scatterSeries2);

    //// ����ͼ���������
    //chart->createDefaultAxes();
}

void ChartWithHover::changeLineSeries(QPointF t,QPointF v)
{
    // ɾ����һ���㣨������ 0 �ĵ㣩
    series1->remove(0);
    series2->remove(0);

    // ����������
    // ͨ����ȡ��ǰ����б��������ǵ� x ����
    for (int i = 0; i < series1->count(); ++i) {
        QPointF point = series1->at(i);
        series1->replace(i, QPointF(point.x() - 1, point.y()));
    }

    for (int i = 0; i < series2->count(); ++i) {
        QPointF point = series2->at(i);
        series2->replace(i, QPointF(point.x() - 1, point.y()));
    }

    // ����µĵ㵽����ĩβ
    series1->append(t);
    series2->append(v);
}

void ChartWithHover::enableHoverEffect()
{
    tooltipItem = new QGraphicsSimpleTextItem(chart);
    tooltipItem->setZValue(10);
    tooltipItem->setFont(QFont("Arial", 10, QFont::Bold));

    tooltipRect = new QGraphicsRectItem();
    tooltipRect->setZValue(9); // ����Ϊ�����ı���
    tooltipRect->setBrush(QColor(0, 0, 0, 180)); // ��͸������
    tooltipRect->setPen(Qt::NoPen); // ȥ���߿�
    tooltipRect->setVisible(false); // Ĭ������

    chart->scene()->addItem(tooltipRect);
    chart->scene()->addItem(tooltipItem);
    tooltipItem->hide();
    tooltipRect->hide();
}

// �ж�����Ƿ�ӽ����ݵ�
bool ChartWithHover::isNearPoint(const QPointF& mousePos, const QPointF& point)
{
    const double maxDistance = 10.0; // �жϾ�����ֵ
    double distance = qSqrt(qPow(mousePos.x() - point.x(), 2) + qPow(mousePos.y() - point.y(), 2));
    return distance < maxDistance;
}

void ChartWithHover::mouseMoveEvent(QMouseEvent* event)
{
    // ��ȡ�����ͼ���ϵ�����
    QPointF chartPoint = chart->mapToValue(event->pos());

    tooltipItem->hide();
    tooltipRect->hide();

    // ��ʼ������
    QPointF nearestPoint;
    double minDistanceXY = std::numeric_limits<double>::max(); // ��С����

    // �����洢�������ɫ�ͻ�ɫ��
    QPointF nearestPointSeries1;
    QPointF nearestPointSeries2;

    double minDistanceX1 = std::numeric_limits<double>::max();
    double minDistanceX2 = std::numeric_limits<double>::max();

    // ��һ������ϵ�У����Ȱ�X���ҵ�����ĵ�
    for (const QPointF& point : series1->pointsVector()) {
        double distanceX = qAbs(chartPoint.x() - point.x());
        if (distanceX < minDistanceX1) {
            minDistanceX1 = distanceX;
            nearestPointSeries1 = point;
        }
    }

    // �ڶ�������ϵ�У����Ȱ�X���ҵ�����ĵ�
    for (const QPointF& point : series2->pointsVector()) {
        double distanceX = qAbs(chartPoint.x() - point.x());
        if (distanceX < minDistanceX2) {
            minDistanceX2 = distanceX;
            nearestPointSeries2 = point;
        }
    }

    // Ȼ�󣬰�Y�ᾫϸ�ж�
    if (!nearestPointSeries1.isNull()) {
        double distanceYSeries1 = qAbs(chartPoint.y() - nearestPointSeries1.y());
        double distanceXSeries1 = qAbs(chartPoint.x() - nearestPointSeries1.x());
        double totalDistanceSeries1 = qSqrt(qPow(distanceXSeries1, 2) + qPow(distanceYSeries1, 2));
        if (totalDistanceSeries1 < minDistanceXY) {
            minDistanceXY = totalDistanceSeries1;
            nearestPoint = nearestPointSeries1;
        }
    }

    if (!nearestPointSeries2.isNull()) {
        double distanceYSeries2 = qAbs(chartPoint.y() - nearestPointSeries2.y());
        double distanceXSeries2 = qAbs(chartPoint.x() - nearestPointSeries2.x());
        double totalDistanceSeries2 = qSqrt(qPow(distanceXSeries2, 2) + qPow(distanceYSeries2, 2));
        if (totalDistanceSeries2 < minDistanceXY) {
            minDistanceXY = totalDistanceSeries2;
            nearestPoint = nearestPointSeries2;
        }
    }

    // ��������㹻������ʾ��ʾ��
    if (minDistanceXY < 10.0) {
        if (nearestPoint == nearestPointSeries1) {
            tooltipItem->setText(QString("Temperature\nX: %1\nY: %2")
                .arg(nearestPoint.x()).arg(nearestPoint.y()));

            // ����������ʽ
            tooltipItem->setFont(QFont("Arial", 12, QFont::Bold)); // ��������
            tooltipItem->setBrush(QColor(255, 255, 255)); // ��ɫ����
            tooltipItem->setPen(QPen(QColor(0, 0, 0))); // ��ɫ��ߣ����ӶԱȶ�

            // ������ӰЧ����Ӧ��
            QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect();
            shadowEffect->setColor(QColor(0, 0, 0, 160));  // ��Ӱ��ɫ
            shadowEffect->setOffset(3, 3);                  // ��Ӱƫ��
            shadowEffect->setBlurRadius(6);                 // ��Ӱģ���뾶
            tooltipItem->setGraphicsEffect(shadowEffect);   // ����ӰЧ��Ӧ����tooltipItem

            // ���ý��䱳��
            QLinearGradient gradient(0, 0, 0, 30); // ���ϵ��µĽ���
            gradient.setColorAt(0, QColor(0, 0, 255, 150));  // ����Ϊ��͸����ɫ
            gradient.setColorAt(1, QColor(0, 0, 255, 50));   // �ײ�Ϊ��͸������ɫ
            tooltipRect->setBrush(gradient); // ���ý��䱳��

            // ����Բ��Ч��
            tooltipRect->setPen(Qt::NoPen);  // ����ʾ�߿�
            
        }
        else {
            tooltipItem->setText(QString("Voltage\nX: %1\nY: %2")
                .arg(nearestPoint.x()).arg(nearestPoint.y()));

            // ����������ʽ
            tooltipItem->setFont(QFont("Arial", 12, QFont::Bold)); // ��������
            tooltipItem->setBrush(QColor(255, 255, 255)); // ��ɫ����
            tooltipItem->setPen(QPen(QColor(0, 0, 0))); // ��ɫ��ߣ����ӶԱȶ�

            // ������ӰЧ����Ӧ��
            QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect();
            shadowEffect->setColor(QColor(0, 0, 0, 160));  // ��Ӱ��ɫ
            shadowEffect->setOffset(3, 3);                  // ��Ӱƫ��
            shadowEffect->setBlurRadius(6);                 // ��Ӱģ���뾶
            tooltipItem->setGraphicsEffect(shadowEffect);   // ����ӰЧ��Ӧ����tooltipItem

            // ���ý��䱳��
            QLinearGradient gradient(0, 0, 0, 30); // ���ϵ��µĽ���
            gradient.setColorAt(0, QColor(255, 200, 0, 180));  // ����Ϊ͸����ɫ
            gradient.setColorAt(1, QColor(255, 200, 0, 80));   // �ײ�Ϊ��͸���Ļ�ɫ
            tooltipRect->setBrush(gradient); // ���ý��䱳��

            // ����Բ��Ч��
            tooltipRect->setPen(Qt::NoPen);  // ����ʾ�߿�
        }



        // ��ȡ tooltip ��λ��
        QPointF tooltipPos = chart->mapToPosition(nearestPoint);

        // ���� tooltip ��λ��
        tooltipRect->setRect(tooltipPos.x(), tooltipPos.y(), tooltipItem->boundingRect().width() + 10, tooltipItem->boundingRect().height() + 10);
        tooltipItem->setPos(tooltipPos.x() + 5, tooltipPos.y() + 5); // ���ı���һЩ���

        tooltipItem->show();
        tooltipRect->show();
    }
    else {
        tooltipItem->hide();
        tooltipRect->hide();
    }

    QChartView::mouseMoveEvent(event); // ���ø��������ƶ��¼�
}
