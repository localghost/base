#ifndef BASE_LOG_H
#define BASE_LOG_H

#include <ostream>
#include <sstream>
#include <base/export.h>

namespace base {
namespace log {

// FIXME 2015-07-24 This is a workaround for GCC, see https://gcc.gnu.org/bugzilla/show_bug.cgi?id=43407
#if defined(__GNUC__) && !defined(__APPLE_CC__)
enum class severity : int EXPORT_API
#else
enum class EXPORT_API severity
#endif // __GNUC__
{
    Info,
    Debug,
    Warning,
    Error
};

class EXPORT_API message
{
public:
    message(severity severity_,
            const char* file,
            unsigned int line,
            const char* function);
    ~message();

    std::ostream& stream();

private:
    std::ostringstream oss;
};

struct EXPORT_API ostream_voidifier
{
  void operator&(const std::ostream&) { }
};
extern ostream_voidifier voidifier EXPORT_API; 
}
}

#define LOG(Severity) \
    ::base::log::message{Severity, __FILE__, __LINE__, __FUNCTION__}.stream()

#define LOG_IF(Condition, Severity) \
    !(Condition) ? static_cast<void>(0) : ::base::log::voidifier & LOG(Severity)

#define LOG_INFO LOG(::base::log::severity::Info)
        
#ifdef DEBUG_BUILD
#define LOG_DEBUG LOG_IF(true, ::base::log::severity::Debug)
#else
#define LOG_DEBUG LOG_IF(false, ::base::log::severity::Debug)
#endif

#define LOG_WARNING LOG(::base::log::severity::Warning)

#define LOG_ERROR LOG(::base::log::severity::Error)
        
#endif
