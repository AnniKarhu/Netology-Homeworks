#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QTime>

class Stopwatch
{
public:
   Stopwatch(); //(QWidget* _parent = nullptr);
   virtual ~Stopwatch();

   void StartTimer();
   //void StopTimer();
   //void LapTimer();

   QTime get_lap_time();
   QTime get_total_time();


private:

    QWidget* parent;

    QTime start_time = QTime(0, 0, 0, 0);
    QTime last_lap_time = QTime(0, 0, 0, 0);
   // QTime total_time = QTime(0, 0, 0, 0);

    QTime get_time_result(QTime& _time);

    QTime get_time_diff(const QTime& time1, const QTime& time2);
};

#endif // STOPWATCH_H
