#include <boost/test/included/unit_test.hpp>

#include "lrr_kty8x.h"

namespace utf = boost::unit_test;

// BOOST_CHECK( add( 2,2 ) == 4 );        // #1 continues on error
    // BOOST_REQUIRE( add( 2,2 ) == 4 );      // #2 throws on error
    // if( add( 2,2 ) != 4 )
    //   BOOST_ERROR( "Ouch..." );            // #3 continues on error
    // if( add( 2,2 ) != 4 )
    //   BOOST_FAIL( "Ouch..." );             // #4 throws on error
    // if( add( 2,2 ) != 4 ) throw "Ouch..."; // #5 throws on error
    // BOOST_CHECK_MESSAGE( add( 2,2 ) == 4,  // #6 continues on error
    //                      "add(..) result: " << add( 2,2 ) );
    // BOOST_CHECK_EQUAL( add( 2,2 ), 4 );	  // #7 continues on error

BOOST_AUTO_TEST_CASE( lrr_KT81_120_basics, * utf::tolerance(0.01) )
{
    float t;
    // - 20
    t = kty81_120_get_temp(684);
    BOOST_TEST(t == -20.0);
    // -10
    t = kty81_120_get_temp(747);
    BOOST_TEST(t == -10.0);
    // 0
    t = kty81_120_get_temp(815);
    BOOST_TEST(t == 0);
    // 10
    t = kty81_120_get_temp(886.1);
    BOOST_TEST(t == 10.0);
    // 20
    t = kty81_120_get_temp(961);
    BOOST_TEST(t == 20.0);
    // 25
    t = kty81_120_get_temp(1000);
    BOOST_TEST(t == 25.0);
    // 30
    t = kty81_120_get_temp(1040);
    BOOST_TEST(t == 30.0);
    // 50
    t = kty81_120_get_temp(1209.1);
    BOOST_TEST(t == 50.0);
    // 80
    t = kty81_120_get_temp(1490);
    BOOST_TEST(t == 80.0);
    // 100
    t = kty81_120_get_temp(1696);
    BOOST_TEST(t == 100.0);
    // 150
    t = kty81_120_get_temp(2211);
    BOOST_TEST(t == 150.0);
}

BOOST_AUTO_TEST_CASE( lrr_NTC_basics, * utf::tolerance(0.01) )
{
    float t;
    // - 20
    t = ntc_get_temp(100218);
    BOOST_TEST(t == -20.56);
    // -10
    t = ntc_get_temp(57017);
    BOOST_TEST(t == -10.56);
    // 0
    t = ntc_get_temp(31732);
    BOOST_TEST(t == 0.56);
    // 10
    t = ntc_get_temp(19376);
    BOOST_TEST(t == 10.56);
    // 20
    t = ntc_get_temp(12182);
    BOOST_TEST(t == 20.56);
    // 25
    t = ntc_get_temp(10000);
    BOOST_TEST(t == 25.0);
    // 30
    t = ntc_get_temp(7866.1);
    BOOST_TEST(t == 30.56);
    // std::cout << t << " == " << 30.56;
    // 50
    t = ntc_get_temp(3525);
    BOOST_TEST(t == 50.56);
    // 80
    t = ntc_get_temp(1234);
    BOOST_TEST(t == 80.56);
    // 120
    t = ntc_get_temp(597);
    BOOST_TEST(t == 120.0);
    // 150
    t = ntc_get_temp(310);
    BOOST_TEST(t == 150.0);
}