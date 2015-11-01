#include <boost/test/unit_test.hpp>

#include <base/log.h>

#include <sstream>

BOOST_AUTO_TEST_SUITE(TSBaseLog)

namespace detail {
std::ostream& operator/(std::ostream& stream, std::stringbuf & buffer)
{
   stream.rdbuf(&buffer);
   return stream;
}
}

BOOST_AUTO_TEST_CASE(TCBaseLogDebug)
{
   using namespace detail;

   std::stringstream ss;
   LOG_DEBUG / *ss.rdbuf() << "Test debug log";
   BOOST_CHECK_EQUAL(ss.str(), "Test debug log");
}

BOOST_AUTO_TEST_CASE(TCBaseLogInfo)
{
   using namespace detail;

   std::stringstream ss;
   LOG_INFO / *ss.rdbuf() << "Test info log " << 42;
   BOOST_CHECK_EQUAL(ss.str(), "Test info log 42");
}

//BOOST_AUTO_TEST_CASE(TCEncodeLongString)
//{
//    BOOST_CHECK_EQUAL(base64::encode(data), expected);
//}
//
//BOOST_AUTO_TEST_CASE(TCEncodeUtf8String)
//{
//    const char* const data = "za��������";
//    const char* const expected = "emHFvMOzxYLEhw==";
//    BOOST_CHECK_EQUAL(base64::encode(data), expected);
//}

BOOST_AUTO_TEST_SUITE_END()
