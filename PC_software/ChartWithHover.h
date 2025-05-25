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
    void mouseMoveEvent(QMouseEvent* event) override; // 重写鼠标移动事件

private:
    QChart* chart;                             // 图表对象
    QGraphicsRectItem* tooltipRect;            // 提示框背景
    QGraphicsSimpleTextItem* tooltipItem;      // 显示文本的提示框
    QSplineSeries* series1;                    // 第一条曲线
    QSplineSeries* series2;                    // 第二条曲线
    QAreaSeries* areaSeries1;                  // 第一条曲线的填充区域
    QAreaSeries* areaSeries2;                  // 第二条曲线的填充区域

    void addEmptyCirclesToSeries(QSplineSeries* series, const QColor& color);
    void createLineSeries();                   // 创建曲线和填充区域
    void enableHoverEffect();                  // 初始化鼠标悬停提示框
    bool isNearPoint(const QPointF& mousePos, const QPointF& point); // 判断鼠标是否接近数据点
};
