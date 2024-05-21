#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QTime>
#include <QTimer>
#include <QLabel>

class Stopwatch: public QObject
{
     Q_OBJECT
public:
   Stopwatch(QLabel* _lbl_Value);
   virtual ~Stopwatch();

   void StartTimer();
   void StopTimer();

   QTime get_lap_time();
   QTime get_total_time();

   bool IsActive();

private:

    const int timer_interval = 100;

    QLabel* lbl_Value = nullptr;
    QTimer* timer = nullptr;;
    QTime start_time = QTime(0, 0, 0, 0);
    QTime last_lap_time = QTime(0, 0, 0, 0);

    QTime get_time_result(QTime& _time);
    QTime get_time_diff(const QTime& time1, const QTime& time2);

 private slots:
    void on_timer();
};

#endif // STOPWATCH_H
