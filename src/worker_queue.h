#ifndef BASE_WORKER_QUEUE_H
#define BASE_WORKER_QUEUE_H

#include <base/callable.h>
#include <base/export.h>

#include <condition_variable>
#include <mutex>
#include <deque>
#include <utility>

namespace base {
class EXPORT_API worker_queue
{
public:
   callable try_pop_back()
   {
      std::unique_lock<std::mutex> lock{mutex_, std::try_to_lock};
      if (!lock || queue_.empty() || quit_) return {};
      auto result = std::move(queue_.back());
      queue_.pop_front();
      return result;
   }

   callable try_pop_front()
   {
      std::unique_lock<std::mutex> lock{mutex_, std::try_to_lock};
      if (!lock || queue_.empty() || quit_) return {};
      auto result = std::move(queue_.front());
      queue_.pop_front();
      return result;
   }

   callable pop_front()
   {
      std::unique_lock<std::mutex> lock{mutex_};
      while (queue_.empty() && !quit_) cv_.wait(lock);
      if (queue_.empty()) return {};
      auto result = std::move(queue_.front());
      queue_.pop_front();
      return result;
   }

   template<typename F>
   void push_front(F&& f)
   {
      {
         std::lock_guard<std::mutex> lock{mutex_};
         queue_.emplace_front(std::forward<F>(f));
      }
      cv_.notify_one();
   }

   void quit()
   {
      {
         std::lock_guard<std::mutex> lock{mutex_};
         quit_ = true;
      }
      cv_.notify_all();
   }

private:
   bool quit_ = false;
   std::deque<callable> queue_;
   std::mutex mutex_;
   std::condition_variable cv_;
};
}

#endif
