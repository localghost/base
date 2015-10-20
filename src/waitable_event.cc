#include "waitable_event.h"

namespace base {
void waitable_event::wait()
{
  std::unique_lock<std::mutex> lock{m_};
  wait_on_lock(lock);
}

void waitable_event::wait_and_reset()
{
  std::unique_lock<std::mutex> lock{m_};
  wait_on_lock(lock);
  signaled_ = false;
}

void waitable_event::signal()
{
  {
    std::lock_guard<std::mutex> guard{m_};
    signaled_ = true;
  }
  cv_.notify_all();
}

void waitable_event::wait_on_lock(std::unique_lock<std::mutex>& lock)
{
  while (!signaled_) cv_.wait(lock);
}
}
