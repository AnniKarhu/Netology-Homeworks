#pragma once
#include <iostream>
#include <mutex>
#include <queue>
#include <functional>
#include <condition_variable>

class safe_queue
{
private:
	std::queue<std::function<void()>>   work_queue;	
	std::mutex queue_mutex;
	std::condition_variable data_cond;
public:
	void sq_push(std::function<void()> new_task, std::string func_name, int func_count);
	void sq_pop();
	bool not_empty();
	bool is_empty();
};
