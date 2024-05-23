#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QTime>
#include <QTimer>
#include <QLabel>

class Stopwatch: public QObject
{
     Q_OBJECT
public:
   Stopwatch();
   virtual ~Stopwatch();

   void StartTimer();
   void StopTimer();
   void ClearTimer();

   QTime get_lap_time();
   QTime get_total_time();
   int get_lap_num();

   bool IsActive();

signals:
   void on_timer_signal(QString);

private:

    const int timer_interval = 100;
    int LapsNum = 1;

    QTimer* timer = nullptr;;
    QTime start_time = QTime(0, 0, 0, 0);
    QTime last_lap_time = QTime(0, 0, 0, 0);

    QTime get_time_result(QTime& _time);
    QTime get_time_diff(const QTime& time1, const QTime& time2);

 private slots:
    void on_timer();
};

#endif // STOPWATCH_H
