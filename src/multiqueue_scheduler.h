/*
 * multiqueue_scheduler.h
 *
 *  Created on: Oct 21, 2015
 *      Author: me
 */

#ifndef BASE_MULTIQUEUE_SCHEDULER_H
#define BASE_MULTIQUEUE_SCHEDULER_H

#include <base/worker_queue.h>
#include <base/callable.h>
#include <vector>

namespace base {
class multiqueue_scheduler
{
public:
   explicit multiqueue_scheduler(const size_t num_workers) : num_workers_{num_workers}
   {
      threads_.reserve(num_workers_);
      for (size_t i = 0; i < num_workers_; ++i)
      {
         threads_.emplace_back(&multiqueue_scheduler::thread_entry, this, i);
      }
   }

   ~multiqueue_scheduler()
   {
      for (auto& q : queues_)
      {
         q.quit();
      }

      for (auto& t: threads_)
      {
         t.join();
      }
   }

private:
   void thread_entry(const size_t index)
   {
      while (true)
      {
         callable f = queues_[index].try_pop_front();

         for (size_t i = index + 1; i < num_workers_ && !f; ++i)
         {
            f = queues_[i].try_pop_back();
         }

         for (size_t i = 0; i < index && !f; ++i)
         {
            f = queues_[i].try_pop_back();
         }

         if (!f)
         {
            f = queues_[index].pop_front();
            if (!f)
            {
               break;
            }
         }

         f();
      }
   }

   const size_t num_workers_;
   std::vector<std::thread> threads_;
   std::vector<worker_queue> queues_{num_workers_};
};
}

#endif
