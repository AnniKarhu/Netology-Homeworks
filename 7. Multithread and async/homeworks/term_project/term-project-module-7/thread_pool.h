#pragma once
#include <iostream>
#include <vector>
#include <thread>
#include <string>

#include "safe_queue.h"

class thread_pool
{
private:
	std::vector<std::thread> th_vector;
	safe_queue  pool_queue;
	
	std::atomic<bool> task_generator_finished = false;
	bool start_work = false;
	
	std::mutex start_mutex;
	std::condition_variable start_threads;
	
	void work(); //рабочая функция потоков	

public:	
	
	thread_pool();	
	~thread_pool();	

	void submit(std::function<void()> new_task, std::string func_name, int func_count); //добавление задачи в очередь
	void start_threads_work(); //старт рабочих потоков
	void finish_tasks(); //флаг завершения генерирования задач	
};
