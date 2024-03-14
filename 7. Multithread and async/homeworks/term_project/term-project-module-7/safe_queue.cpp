#include "safe_queue.h"

	void safe_queue::sq_push(std::function<void()> new_task, std::string func_name, int func_count)
	{
		std::lock_guard<std::mutex> lk(queue_mutex);

		work_queue.push(new_task);
		std::cout << "new task added: " << func_name << " count = " << func_count << "\n";
		data_cond.notify_all();
	}

	void safe_queue::sq_pop()
	{
		if (is_empty())
			return;

		std::unique_lock lk(queue_mutex);

		data_cond.wait(lk, [this] {return (!(work_queue.empty())); });

		if (!(work_queue.empty()))
		{
			auto task = work_queue.front();
			work_queue.pop();
			task();
		}

		lk.unlock();
	}

	bool safe_queue::not_empty()
	{
		std::lock_guard<std::mutex> lk(queue_mutex);
		return !work_queue.empty();
	}

	bool safe_queue::is_empty()
	{
		std::lock_guard<std::mutex> lk(queue_mutex);
		return work_queue.empty();
	}


