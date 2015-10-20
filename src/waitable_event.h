#ifndef BASE_WAITABLE_EVENT_H
#define BASE_WAITABLE_EVENT_H

#include <mutex>
#include <condition_variable>
#include <base/export.h>

namespace base {
/// This is a primitive synchronization mechanism between threads.
/// When a thread signals it all threads that are waiting or it are notified. If the state is not reset than
/// all subsequent waits will finish instantly.
class EXPORT_API waitable_event
{
public:
  void wait();
  void wait_and_reset();

  void signal();

private:
  void wait_on_lock(std::unique_lock<std::mutex>& lock);

  std::mutex m_;
  std::condition_variable cv_;
  bool signaled_ = false;
};
}

#endif
