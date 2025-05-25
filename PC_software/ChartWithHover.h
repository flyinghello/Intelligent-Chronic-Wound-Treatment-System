#pragma once

#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QValueAxis>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsRectItem>
#include <QWidget>
#include <QEasingCurve>
#include <QScatterSeries>
#include <QMutex>
#include "global.h"

class ChartWithHover : public QChartView
{
    Q_OBJECT

public:
    explicit ChartWithHover(QWidget* parent = nullptr);
    ~ChartWithHover();
    void createLineSeries(std::shared_ptr<PatientData> patientdata);
    void changeLineSeries(QPointF t,QPointF v);
protected:
    void mouseMoveEvent(QMouseEvent* event) override; // ��д����ƶ��¼�

private:
    QChart* chart;                             // ͼ�����
    QGraphicsRectItem* tooltipRect;            // ��ʾ�򱳾�
    QGraphicsSimpleTextItem* tooltipItem;      // ��ʾ�ı�����ʾ��
    QSplineSeries* series1;                    // ��һ������
    QSplineSeries* series2;                    // �ڶ�������
    QAreaSeries* areaSeries1;                  // ��һ�����ߵ��������
    QAreaSeries* areaSeries2;                  // �ڶ������ߵ��������

    void addEmptyCirclesToSeries(QSplineSeries* series, const QColor& color);
    void createLineSeries();                   // �������ߺ��������
    void enableHoverEffect();                  // ��ʼ�������ͣ��ʾ��
    bool isNearPoint(const QPointF& mousePos, const QPointF& point); // �ж�����Ƿ�ӽ����ݵ�
};
