#include "chartform.h"
#include "ui_chartform.h"

ChartForm::ChartForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChartForm)
{
    ui->setupUi(this);

    //Выделим память под наши объекты.

     //Объект QChart является основным, в котором хранятся все данные графиков и который отвечает
     //за само поле отображения графика, управляет осями, легенодой и прочими атрибутами графика.
     chart = new QChart( );
     chart->legend()->setVisible(false);

     //Объект QChartView является виджетом отображальщиком графика. В его конструктор необходимо передать ссылку
     //на объект QChart.
     chartView = new QChartView(chart);

     //И создадим объект нашего класса.
     //graphClass = new GraphicChart(NUM_GRAPHS);

     //chart -> chartView -> данные для отображения


     //ui->gridLayout->addWidget(chartView); //Размещаем ChartView на лайауте
     chartView->show( );

}

ChartForm::~ChartForm()
{
    delete ui;
    delete chart;
    delete chartView;
}

void ChartForm::add_chart_widget(QChartView& chartView)
{

   // ui->gridLayout->addWidget(chartView);

}
