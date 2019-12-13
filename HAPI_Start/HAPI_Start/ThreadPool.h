#pragma once

#include <stack>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <functional>
#include <stdexcept>

class ThreadPool
{
private:

	static std::shared_ptr<ThreadPool> tp;

	ThreadPool() {

		for (int i{ 0 }; i < m_cNumThreads; i++) { //sets max threads and passes in handling function to thread
			vecthdThreadPool.push_back(std::thread(&ThreadPool::ThreadHandler, this));
		}
	}

	std::mutex m_mtxQueueMutex;
	std::condition_variable m_cdnCondition;
	std::atomic_bool m_bTerminate{ false };
	const int m_cNumThreads = std::thread::hardware_concurrency();
	std::vector<std::thread> vecthdThreadPool;
	std::vector<std::function<void()>> vecfnFuncQueue;
	std::function<void()> m_fnCurrentFunc;
	std::atomic_int m_nCounter{ 0 };

	bool ShutdownThread() {
		{
			std::unique_lock<std::mutex> lock(m_mtxQueueMutex); //locks the mutex wakes up all threads and joins them all
			m_bTerminate = true;
		}
		m_cdnCondition.notify_all();

		for (std::thread& t : vecthdThreadPool) {
			t.join();
		}

		return vecthdThreadPool.empty();

	}
public:

	static std::shared_ptr<ThreadPool>& GetInstance() {

		if (!tp)
			tp.reset(new ThreadPool());
		return tp;

	}

	bool NoActiveThreads();

	~ThreadPool() {

		if (m_bTerminate = true) this->ShutdownThread(); //if the queue vector isnt empty, empty it

	}

	void ThreadHandler();
	void AddJob(std::function<void()> newJob);
	int GetActiveThreads();
	int GetNumThreads() const;

protected:

};

#define THREADPOOL ThreadPool::GetInstance()

