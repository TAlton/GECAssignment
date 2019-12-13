#include "ThreadPool.h"

std::shared_ptr<ThreadPool> ThreadPool::tp = nullptr;

void ThreadPool::ThreadHandler() {

	while (true) {

		{

			std::unique_lock<std::mutex> lock(m_mtxQueueMutex);

			m_cdnCondition.wait(lock, [this] { return !vecfnFuncQueue.empty() || m_bTerminate; });

			if (vecfnFuncQueue.empty()) {

				return;

			}
			else {

				m_nCounter++;
				m_fnCurrentFunc = vecfnFuncQueue.back();
				vecfnFuncQueue.pop_back();
				m_fnCurrentFunc();
				m_nCounter--;

			}

		}


	}

}

void ThreadPool::AddJob(std::function<void()> newJob) {

	{

		std::unique_lock<std::mutex> lock(m_mtxQueueMutex);

		vecfnFuncQueue.push_back(newJob);

	}

	m_cdnCondition.notify_one();

}

int ThreadPool::GetActiveThreads() {

	return m_nCounter;

}

bool ThreadPool::NoActiveThreads() {

	for (int i{ 0 }; i < vecthdThreadPool.size(); i++) {

		if (!vecthdThreadPool[i].joinable()) {
			continue;
		}
		else {
			return false;
		}

	}

	return true;

}

int ThreadPool::GetNumThreads() const {

	return m_cNumThreads;

}

