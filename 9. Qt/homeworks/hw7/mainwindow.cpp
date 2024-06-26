#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pb_clearResult->setCheckable(true);

    //chartForm = new ChartForm(this);
    connect(this, &MainWindow::sig_BuildChart, this, &MainWindow::on_BuildChart);

    //Выделить память под объекты.

     //Объект QChart является основным, в котором хранятся все данные графиков и который отвечает
     //за само поле отображения графика, управляет осями, легенодой и прочими атрибутами графика.
     chart = new QChart( );
     chart->legend()->setVisible(false);

     //Объект QChartView является виджетом отображальщиком графика. В его конструктор необходимо передать ссылку
     //на объект QChart.
     chartView = new QChartView(chart);

     //создать объект класса-обертки
     graphClass = new GraphicChart(NUM_GRAPHS);

     //chart -> chartView -> данные для отображения

     //ui->gridLayout->addWidget(chartView); //Размещаем ChartView на лайауте, без него график отображается в отдельном окне
    // chartView->show( );

}

MainWindow::~MainWindow()
{
    delete ui;
    delete chart;
    delete graphClass;
    delete chartView;
}



/****************************************************/
/*!
@brief:	Метод считывает данные из файла
@param: path - путь к файлу
        numberChannel - какой канал АЦП считать
*/
/****************************************************/
QVector<uint32_t> MainWindow::ReadFile(QString path, uint8_t numberChannel)
{

    QFile file(path);
    file.open(QIODevice::ReadOnly);

    if(file.isOpen() == false){

        if(pathToFile.isEmpty()){
            QMessageBox mb;
            mb.setWindowTitle("Ошибка");
            mb.setText("Ошибка открытия фала");
            mb.exec();
        }
    }
    else{

        //продумать как выйти из функции
    }

    QDataStream dataStream;
    dataStream.setDevice(&file);
    dataStream.setByteOrder(QDataStream::LittleEndian);

    QVector<uint32_t> readData;
    readData.clear();
    uint32_t currentWorld = 0, sizeFrame = 0;

    while(dataStream.atEnd() == false){

        dataStream >> currentWorld;

        if(currentWorld == 0xFFFFFFFF){

            dataStream >> currentWorld;

            if(currentWorld < 0x80000000){

                dataStream >> sizeFrame;

                if(sizeFrame > 1500){
                    continue;
                }

                for(int i = 0; i<sizeFrame/sizeof(uint32_t); i++){

                    dataStream >> currentWorld;

                    if((currentWorld >> 24) == numberChannel){

                        readData.append(currentWorld);

                    }
                }
            }
        }
    }
    ui->chB_readSucces->setChecked(true);
    return readData;
}

QVector<double> MainWindow::ProcessFile(const QVector<uint32_t> dataFile)
{
    QVector<double> resultData;
    resultData.clear();

    foreach (int word, dataFile) {
        word &= 0x00FFFFFF;
        if(word > 0x800000){
            word -= 0x1000000;
        }

        double res = ((double)word/6000000)*10;
        resultData.append(res);
    }
    ui->chB_procFileSucces->setChecked(true);

    return resultData;
}

QVector<double> MainWindow::FindMax(QVector<double> resultData)
{
    double max = 0, sMax=0;
    //Поиск первого максиума
    foreach (double num, resultData){
        //QThread::usleep(1);
        if(num > max){
            max = num;
        }
    }

    //Поиск 2го максимума
    foreach (double num, resultData){
        //QThread::usleep(1);
        if(num > sMax && (qFuzzyCompare(num, max) == false)){
            sMax = num;
        }
    }

    QVector<double> maxs = {max, sMax};
    ui->chB_maxSucess->setChecked(true);
    return maxs;
}

QVector<double> MainWindow::FindMin(QVector<double> resultData)
{

    double min = 0, sMin = 0;
    QThread::sleep(1);
    //Поиск первого максиума
    foreach (double num, resultData){
        if(num < min){
            min = num;
        }
    }
    QThread::sleep(1);
    //Поиск 2го максимума
    foreach (double num, resultData){
        if(num < sMin && (qFuzzyCompare(num, min) == false)){
            sMin = num;
        }
    }

    QVector<double> mins = {min, sMin};
    ui->chB_minSucess->setChecked(true);
    return mins;

}

void MainWindow::DisplayResult(QVector<double> mins, QVector<double> maxs)
{
    ui->te_Result->append("Расчет закончен!");

    ui->te_Result->append("Первый минимум " + QString::number(mins.first()));
    ui->te_Result->append("Второй минимум " + QString::number(mins.at(1)));

    ui->te_Result->append("Первый максимум " + QString::number(maxs.first()));
    ui->te_Result->append("Второй максимум " + QString::number(maxs.at(1)));
}


/****************************************************/
/*!
@brief:	Обработчик клика на кнопку "Выбрать путь"
*/
/****************************************************/
void MainWindow::on_pb_path_clicked()
{
    pathToFile = "";
    ui->le_path->clear();

    pathToFile =  QFileDialog::getOpenFileName(this,
                                              tr("Открыть файл"), "/home/", tr("ADC Files (*.adc)"));

    ui->le_path->setText(pathToFile);
}

/****************************************************/
/*!
@brief:	Обработчик клика на кнопку "Старт"
*/
/****************************************************/
void MainWindow::on_pb_start_clicked()
{


    //проверка на то, что файл выбран
    if(pathToFile.isEmpty()){

        QMessageBox mb;
        mb.setWindowTitle("Ошибка");
        mb.setText("Выберите файл!");
        mb.exec();
        return;
    }

    ui->chB_maxSucess->setChecked(false);
    ui->chB_procFileSucces->setChecked(false);
    ui->chB_readSucces->setChecked(false);
    ui->chB_minSucess->setChecked(false);

    int selectIndex = ui->cmB_numCh->currentIndex();
    //Маски каналов
    if(selectIndex == 0){
        numberSelectChannel = 0xEA;
    }
    else if(selectIndex == 1){
        numberSelectChannel = 0xEF;
    }
    else if(selectIndex == 2){
        numberSelectChannel = 0xED;
    }


    auto read = [&]{ return ReadFile(pathToFile, numberSelectChannel); };
    auto process = [&](QVector<uint32_t> res){ return ProcessFile(res);};
    auto findMax = [&](QVector<double> res){
                                                maxs = FindMax(res);
                                                mins = FindMin(res);
                                                DisplayResult(mins, maxs);


                                                //создать контейнеры для хранения данных
                                                QVector<double> x;
                                                QVector<double> y;

                                                //шаг сетки и граничные значения
                                                double step = 1/FD; //(FD*100); //#define FD 1000.0 //частота дискретизации //0.001;

                                                double minVal = 0;
                                                double maxVal = 1;
                                                double steps = round(((maxVal - minVal) / step));
                                                x.resize(steps);
                                                x[0] = minVal;
                                                for(int i = 1; i<steps; i++){
                                                    x[i] = x[i-1]+step;
                                                }

                                                y.resize(steps);

                                                //Добавить все точки в массив
                                                for(int i = 0; (i<steps && i<res.size()); i++)
                                                {
                                                    y[i] = res[i];
                                                }

                                                QVector<double> maxs_y = FindMax(y);
                                                QVector<double> mins_y = FindMin(y);

                                                //очистить предыдущее - сначала проверить есть ли данные
                                                //если вызвать ClearGraph без проверки - приведет к краху программы
                                                //Перед новой отрисовкой очистить график
                                                if(chart->series().isEmpty() == false){
                                                    graphClass->ClearGraph(chart);
                                                }

                                                //Добавить данные в серию
                                                graphClass->AddDataToGrahp(x,y, 1);

                                                // qDebug() << mins_y[0];
                                                // qDebug() << maxs_y[0];

                                                emit sig_BuildChart(mins_y[0], maxs_y[0]);

                                             };

    auto result = QtConcurrent::run(read)
                               .then(process)
                               .then(findMax);



}

void MainWindow::on_BuildChart(double min, double max)
{
      //chartForm->show();
    chartView->show( );

    //Обновить график, т.е. добавить сформированыые серии на график
    graphClass->UpdateGraph(chart);
    //И отобразить его.
    ViewGraph(min, max);

}

void MainWindow::ViewGraph(double min, double max)
{
    chartView->chart( )->createDefaultAxes();
    chart->axisY()->setRange(min, max); //(-1.1,+0.15);
    chartView->resize(1000,400);
    chartView->show( );
}




