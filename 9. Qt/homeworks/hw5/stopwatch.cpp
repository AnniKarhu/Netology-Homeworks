#include "stopwatch.h"
#include <QDebug>

Stopwatch::Stopwatch()
{
    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, Stopwatch::on_timer);

}

Stopwatch::~Stopwatch()
{
    delete timer;
}

bool Stopwatch::IsActive()
{
    if (timer == nullptr)
        return false;

    return timer->isActive();
}

void Stopwatch::ClearTimer()
{
    start_time = QTime::currentTime();
    last_lap_time = QTime::currentTime();
    LapsNum = 1;
}

void Stopwatch::StartTimer()
{
    if (timer == nullptr)
        return;

   // start_time = QTime::currentTime();
   // last_lap_time = QTime::currentTime();
   // LapsNum = 1;
    ClearTimer();
    timer->start(timer_interval);

}

void Stopwatch::StopTimer()
{
    if (timer == nullptr)
        return;

    QString total_time_str =  get_total_time().toString("hh:mm:ss:zzz");
    timer->stop();
}

QTime Stopwatch::get_time_result(QTime& _time)
{
   QTime current_time = QTime::currentTime();
   QTime result = get_time_diff(current_time, _time);
   return result;
}

void Stopwatch::on_timer()
{
   QString total_time_str =  get_total_time().toString("hh:mm:ss:zzz");
   emit on_timer_signal(total_time_str);
}

QTime Stopwatch::get_lap_time()
{
    QTime result = get_time_result(last_lap_time);
    last_lap_time = QTime::currentTime();
    return result;
}

int Stopwatch::get_lap_num()
{
    return LapsNum++;
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
