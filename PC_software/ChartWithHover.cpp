#include "ChartWithHover.h"
#include <QMouseEvent>
#include <QtDebug>
#include <QGraphicsRectItem>
#include <QGraphicsDropShadowEffect>
#include "WebsocketMgr.h"

ChartWithHover::ChartWithHover(QWidget* parent)
    : QChartView(parent), tooltipItem(nullptr), tooltipRect(nullptr)
{
    // 初始化图表
    chart = new QChart();
    chart->setTitle("Patient Total");
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setAnimationDuration(1000);
    chart->setAnimationEasingCurve(QEasingCurve::OutCubic);

    // 创建曲线数据系列和填充区域
    createLineSeries();

    // 初始化坐标轴
    QValueAxis* axisX = new QValueAxis();
    axisX->setRange(0, 9);
    axisX->setLabelsVisible(false); // 隐藏横轴标签
    chart->addAxis(axisX, Qt::AlignBottom);

    QValueAxis* axisY = new QValueAxis();
    axisY->setRange(0, 45);
    axisY->setTitleText("Number of Patients");
    chart->addAxis(axisY, Qt::AlignLeft);

    // 将坐标轴绑定到数据系列
    series1->attachAxis(axisX);
    series1->attachAxis(axisY);
    series2->attachAxis(axisX);
    series2->attachAxis(axisY);

    areaSeries1->attachAxis(axisX);
    areaSeries1->attachAxis(axisY);
    areaSeries2->attachAxis(axisX);
    areaSeries2->attachAxis(axisY);


    // 设置图表
    this->setChart(chart);
    this->setRenderHint(QPainter::Antialiasing);
    this->setMouseTracking(true); // 启用鼠标追踪

    // 初始化鼠标悬停提示框
    enableHoverEffect();
}

ChartWithHover::~ChartWithHover() {}


void ChartWithHover::addEmptyCirclesToSeries(QSplineSeries* series, const QColor& color)
{
    // 获取 QChartView 的场景
    QGraphicsScene* scene = this->scene();

    // 遍历系列中的所有数据点
    for (const QPointF& point : series->pointsVector()) {
        qDebug() << point;
        // 将数据点映射到图表的屏幕坐标系
        QPointF screenPos = chart->mapToPosition(point);

        // 打印坐标以调试
        qDebug() <<"point"<<point << "screenPos:" << screenPos;

        // 创建空心圆点
        QGraphicsEllipseItem* circleItem = new QGraphicsEllipseItem(screenPos.x() - 5, screenPos.y() - 5, 10, 10);
        circleItem->setPen(QPen(color));        // 设置圆圈颜色
        circleItem->setBrush(Qt::NoBrush);     // 空心圆
        circleItem->setZValue(10);             // 确保圆点显示在图表上层

        // 将圆点添加到 QChartView 的场景中
        scene->addItem(circleItem);
    }
}



void ChartWithHover::createLineSeries()
{
    // 第一条曲线
    series1 = new QSplineSeries();
    *series1 << QPointF(0, 10) << QPointF(1, 80) << QPointF(2, 50)
        << QPointF(3, 20) << QPointF(4, 100) << QPointF(5, 120)
        << QPointF(6, 80) << QPointF(7, 60) << QPointF(8, 90)
        << QPointF(9, 100);

    QSplineSeries* bottomSeries1 = new QSplineSeries();
    *bottomSeries1 << QPointF(0, 0) << QPointF(9, 0);

    areaSeries1 = new QAreaSeries(series1, bottomSeries1);
    areaSeries1->setName("Temperature");
    areaSeries1->setBrush(QColor(50, 150, 255, 100)); // 半透明蓝色填充区域
    
    chart->addSeries(areaSeries1);
    // 第二条曲线
    series2 = new QSplineSeries();
    *series2 << QPointF(0, 40) << QPointF(1, 50) << QPointF(2, 30)
        << QPointF(3, 10) << QPointF(4, 60) << QPointF(5, 86)
        << QPointF(6, 50) << QPointF(7, 70) << QPointF(8, 85)
        << QPointF(9, 40);

    QSplineSeries* bottomSeries2 = new QSplineSeries();
    *bottomSeries2 << QPointF(0, 0) << QPointF(9, 0);

    /*areaSeries2->setName(QString::fromLocal8Bit("电压 "));*/
    areaSeries2 = new QAreaSeries(series2, bottomSeries2);
    areaSeries2->setName("Voltage");
    areaSeries2->setBrush(QColor(255, 200, 0, 100)); // 半透明黄色填充区域
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

    //// 创建散点系列并设置样式
    //QScatterSeries* scatterSeries1 = new QScatterSeries();
    //scatterSeries1->setPointLabelsVisible(false);
    //scatterSeries1->setMarkerShape(QScatterSeries::MarkerShapeCircle);  // 设置点的形状为圆形
    //scatterSeries1->setMarkerSize(8);  // 设置点的大小
    //scatterSeries1->setBrush(Qt::NoBrush);  // 设置空心效果
    //QPen pen1(Qt::blue);  // 创建蓝色边框
    //pen1.setWidth(2);     // 设置边框宽度为3
    //scatterSeries1->setPen(pen1);  // 应用边框

    //QScatterSeries* scatterSeries2 = new QScatterSeries();
    //scatterSeries2->setPointLabelsVisible(false);
    //scatterSeries2->setMarkerShape(QScatterSeries::MarkerShapeCircle);  // 设置点的形状为圆形
    //scatterSeries2->setMarkerSize(8);  // 设置点的大小
    //scatterSeries2->setBrush(Qt::NoBrush);  // 设置空心效果
    //QPen pen2(Qt::yellow);  // 创建黄色边框
    //pen2.setWidth(2);       // 设置边框宽度为3
    //scatterSeries2->setPen(pen2);  // 应用边框

    //// 遍历数据，添加数据点到系列中
    //for (int i = 0; i < patientdata->_temperaturearray.size(); ++i) {
    //    scatterSeries1->append(i, patientdata->_temperaturearray[i].toDouble());
    //    scatterSeries2->append(i, patientdata->_voltagearray[i].toDouble());
    //}

    //// 将系列添加到图表中
    //chart->addSeries(scatterSeries1);
    //chart->addSeries(scatterSeries2);

    //// 更新图表的坐标轴
    //chart->createDefaultAxes();
}

void ChartWithHover::changeLineSeries(QPointF t,QPointF v)
{
    // 删除第一个点（即索引 0 的点）
    series1->remove(0);
    series2->remove(0);

    // 左移其他点
    // 通过获取当前点的列表并调整它们的 x 坐标
    for (int i = 0; i < series1->count(); ++i) {
        QPointF point = series1->at(i);
        series1->replace(i, QPointF(point.x() - 1, point.y()));
    }

    for (int i = 0; i < series2->count(); ++i) {
        QPointF point = series2->at(i);
        series2->replace(i, QPointF(point.x() - 1, point.y()));
    }

    // 添加新的点到序列末尾
    series1->append(t);
    series2->append(v);
}

void ChartWithHover::enableHoverEffect()
{
    tooltipItem = new QGraphicsSimpleTextItem(chart);
    tooltipItem->setZValue(10);
    tooltipItem->setFont(QFont("Arial", 10, QFont::Bold));

    tooltipRect = new QGraphicsRectItem();
    tooltipRect->setZValue(9); // 设置为低于文本项
    tooltipRect->setBrush(QColor(0, 0, 0, 180)); // 半透明背景
    tooltipRect->setPen(Qt::NoPen); // 去掉边框
    tooltipRect->setVisible(false); // 默认隐藏

    chart->scene()->addItem(tooltipRect);
    chart->scene()->addItem(tooltipItem);
    tooltipItem->hide();
    tooltipRect->hide();
}

// 判断鼠标是否接近数据点
bool ChartWithHover::isNearPoint(const QPointF& mousePos, const QPointF& point)
{
    const double maxDistance = 10.0; // 判断距离阈值
    double distance = qSqrt(qPow(mousePos.x() - point.x(), 2) + qPow(mousePos.y() - point.y(), 2));
    return distance < maxDistance;
}

void ChartWithHover::mouseMoveEvent(QMouseEvent* event)
{
    // 获取鼠标在图表上的坐标
    QPointF chartPoint = chart->mapToValue(event->pos());

    tooltipItem->hide();
    tooltipRect->hide();

    // 初始化变量
    QPointF nearestPoint;
    double minDistanceXY = std::numeric_limits<double>::max(); // 最小距离

    // 用来存储最近的蓝色和黄色点
    QPointF nearestPointSeries1;
    QPointF nearestPointSeries2;

    double minDistanceX1 = std::numeric_limits<double>::max();
    double minDistanceX2 = std::numeric_limits<double>::max();

    // 第一条曲线系列，优先按X轴找到最近的点
    for (const QPointF& point : series1->pointsVector()) {
        double distanceX = qAbs(chartPoint.x() - point.x());
        if (distanceX < minDistanceX1) {
            minDistanceX1 = distanceX;
            nearestPointSeries1 = point;
        }
    }

    // 第二条曲线系列，优先按X轴找到最近的点
    for (const QPointF& point : series2->pointsVector()) {
        double distanceX = qAbs(chartPoint.x() - point.x());
        if (distanceX < minDistanceX2) {
            minDistanceX2 = distanceX;
            nearestPointSeries2 = point;
        }
    }

    // 然后，按Y轴精细判断
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

    // 如果距离足够近，显示提示框
    if (minDistanceXY < 10.0) {
        if (nearestPoint == nearestPointSeries1) {
            tooltipItem->setText(QString("Temperature\nX: %1\nY: %2")
                .arg(nearestPoint.x()).arg(nearestPoint.y()));

            // 设置字体样式
            tooltipItem->setFont(QFont("Arial", 12, QFont::Bold)); // 增大字体
            tooltipItem->setBrush(QColor(255, 255, 255)); // 白色字体
            tooltipItem->setPen(QPen(QColor(0, 0, 0))); // 黑色描边，增加对比度

            // 创建阴影效果并应用
            QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect();
            shadowEffect->setColor(QColor(0, 0, 0, 160));  // 阴影颜色
            shadowEffect->setOffset(3, 3);                  // 阴影偏移
            shadowEffect->setBlurRadius(6);                 // 阴影模糊半径
            tooltipItem->setGraphicsEffect(shadowEffect);   // 将阴影效果应用于tooltipItem

            // 设置渐变背景
            QLinearGradient gradient(0, 0, 0, 30); // 从上到下的渐变
            gradient.setColorAt(0, QColor(0, 0, 255, 150));  // 顶部为半透明蓝色
            gradient.setColorAt(1, QColor(0, 0, 255, 50));   // 底部为更透明的蓝色
            tooltipRect->setBrush(gradient); // 设置渐变背景

            // 设置圆角效果
            tooltipRect->setPen(Qt::NoPen);  // 不显示边框
            
        }
        else {
            tooltipItem->setText(QString("Voltage\nX: %1\nY: %2")
                .arg(nearestPoint.x()).arg(nearestPoint.y()));

            // 设置字体样式
            tooltipItem->setFont(QFont("Arial", 12, QFont::Bold)); // 增大字体
            tooltipItem->setBrush(QColor(255, 255, 255)); // 白色字体
            tooltipItem->setPen(QPen(QColor(0, 0, 0))); // 黑色描边，增加对比度

            // 创建阴影效果并应用
            QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect();
            shadowEffect->setColor(QColor(0, 0, 0, 160));  // 阴影颜色
            shadowEffect->setOffset(3, 3);                  // 阴影偏移
            shadowEffect->setBlurRadius(6);                 // 阴影模糊半径
            tooltipItem->setGraphicsEffect(shadowEffect);   // 将阴影效果应用于tooltipItem

            // 设置渐变背景
            QLinearGradient gradient(0, 0, 0, 30); // 从上到下的渐变
            gradient.setColorAt(0, QColor(255, 200, 0, 180));  // 顶部为透明黄色
            gradient.setColorAt(1, QColor(255, 200, 0, 80));   // 底部为更透明的黄色
            tooltipRect->setBrush(gradient); // 设置渐变背景

            // 设置圆角效果
            tooltipRect->setPen(Qt::NoPen);  // 不显示边框
        }



        // 获取 tooltip 的位置
        QPointF tooltipPos = chart->mapToPosition(nearestPoint);

        // 更新 tooltip 的位置
        tooltipRect->setRect(tooltipPos.x(), tooltipPos.y(), tooltipItem->boundingRect().width() + 10, tooltipItem->boundingRect().height() + 10);
        tooltipItem->setPos(tooltipPos.x() + 5, tooltipPos.y() + 5); // 给文本留一些间距

        tooltipItem->show();
        tooltipRect->show();
    }
    else {
        tooltipItem->hide();
        tooltipRect->hide();
    }

    QChartView::mouseMoveEvent(event); // 调用父类的鼠标移动事件
}
