#include "thread_pool.h"

	thread_pool::thread_pool()
	{
		const auto cores = std::thread::hardware_concurrency();
		std::cout << "Total threads number = " << cores << "\n";
		std::cout << "Work threads number = " << cores - 3 << "\n";

		for (int i = 0; i < cores - 3; ++i) //2 потока складывают в очередь + 1 основной
		{
			th_vector.push_back(std::thread(&thread_pool::work, this));
		}

	}

	thread_pool::~thread_pool()
	{
		for (auto& el : th_vector)
		{
			el.join();
			std::cout << "work thread finished\n";
		}
	}

	void thread_pool::work()
	{
		std::unique_lock lk(start_mutex);
		start_threads.wait(lk, [this] {return start_work; });
		std::cout << "start working id: " << std::this_thread::get_id() << "\n";
		lk.unlock();

		while (!task_generator_finished)
		{
			pool_queue.sq_pop();
		}
		while (pool_queue.not_empty())
		{
			pool_queue.sq_pop();
		}
	}	

	void thread_pool::submit(std::function<void()> new_task, std::string func_name, int func_count)
	{
		pool_queue.sq_push(new_task, func_name, func_count);
	}

	void thread_pool::start_threads_work()
	{
		start_work = true;
		start_threads.notify_all();
	}

	void thread_pool::finish_tasks()
	{
		task_generator_finished = true;
	}
