#ifndef CHARTFORM_H
#define CHARTFORM_H

#include <QDialog>

///Подключаем все что нужно для графиков

#include <QtCharts>
//#include <QChartView>


//#include "graphicchart.h"
//#include <QChart>

#include "graphicchart.h"

namespace Ui {
class ChartForm;
}

class ChartForm : public QDialog
{
    Q_OBJECT

public:
    explicit ChartForm(QWidget *parent = nullptr);
    void add_chart_widget(QChartView& chartView);
    ~ChartForm();

private:
    Ui::ChartForm *ui;
    QChart* chart;
    QChartView* chartView;
};

#endif // CHARTFORM_H
