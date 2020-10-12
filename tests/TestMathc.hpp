#include <boost/test/included/unit_test.hpp>

#include "lrr_math.h"

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

BOOST_AUTO_TEST_CASE( lrr_math_basics, * utf::tolerance(0.001) )
{
    static const float observed[][2] = {
        {50, 53.63},
        {54.75, 58.38},
        {78.9, 83.8},
        {85.1, 90},
    };

    const int observed_size = sizeof(observed) / sizeof(observed[0]);
    
    auto r = lrr_get_corrected(observed, observed_size, 50);
    BOOST_TEST(r == 53.63);

    r = lrr_get_corrected(observed, observed_size, 54.75);
    BOOST_TEST(r == 58.38);

    r = lrr_get_corrected(observed, observed_size, 75.00);
    BOOST_TEST(r == 79.69);

    r = lrr_get_corrected(observed, observed_size, 78.9);
    BOOST_TEST(r == 83.8);

    r = lrr_get_corrected(observed, observed_size, 85.0);
    BOOST_TEST(r == 89.9);

    // out of range!
    r = lrr_get_corrected(observed, observed_size, 85.1);
    BOOST_TEST(r == 85.1);
}