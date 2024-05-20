#include "stopwatch.h"
#include <QDebug>

Stopwatch::Stopwatch()
{

}

Stopwatch::~Stopwatch()
{

}

void Stopwatch::StartTimer()
{
    start_time = QTime::currentTime();
    last_lap_time = QTime::currentTime();

}

QTime Stopwatch::get_time_result(QTime& _time)
{
   QTime current_time = QTime::currentTime();
   QTime result = get_time_diff(current_time, _time);
   return result;
}

QTime Stopwatch::get_lap_time()
{

    QTime result = get_time_result(last_lap_time);
    last_lap_time = QTime::currentTime();
   // qDebug() << "get_lap_time: " << result.toString("hh:mm:ss:zzz");
    return result;
}

QTime Stopwatch::get_total_time()
{
   QTime result = get_time_result(start_time);  
   return result;
}

QTime Stopwatch::get_time_diff(const QTime& time1, const QTime& time2)
{
    int ms_sec = 1000;
    int ms_min = ms_sec * 60;
    int ms_hour = ms_min * 60;

    int time_difference = time2.msecsTo(time1);
    QTime result = QTime(time_difference/ms_hour,
                   (time_difference % ms_hour) / ms_min,
                   (time_difference % ms_min) / ms_sec,
                   time_difference % ms_sec);
    return result;
}
