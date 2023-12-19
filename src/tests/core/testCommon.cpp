#include <cstdint>
#include <iostream>
#include <vector>

#include <common.hpp>
#include <TestHelpers.hpp>


void
testIsBase64()
{
    std::vector<uint8_t> test;
    REQUIRE( isBase64<uint8_t>( { test.data(), test.size() } ) );

    test = { 'b' };
    REQUIRE( isBase64<uint8_t>( { test.data(), test.size() } ) );

    test = { '6' };
    REQUIRE( isBase64<uint8_t>( { test.data(), test.size() } ) );

    test = { '\n' };
    REQUIRE( isBase64<uint8_t>( { test.data(), test.size() } ) );

    test = { '/' };
    REQUIRE( isBase64<uint8_t>( { test.data(), test.size() } ) );

    test = { '\2' };
    REQUIRE( !isBase64<uint8_t>( { test.data(), test.size() } ) );
}


void
testUnsignedSaturatingAddition()
{
    REQUIRE_EQUAL( saturatingAddition( 0U, 0U ), 0U );
    REQUIRE_EQUAL( saturatingAddition( 0U, 1U ), 1U );
    REQUIRE_EQUAL( saturatingAddition( 1U, 0U ), 1U );
    REQUIRE_EQUAL( saturatingAddition( 1U, 1U ), 2U );

    constexpr auto MAX = std::numeric_limits<uint64_t>::max();
    REQUIRE_EQUAL( saturatingAddition( MAX, uint64_t( 0 ) ), MAX );
    REQUIRE_EQUAL( saturatingAddition( uint64_t( 0 ), MAX ), MAX );

    REQUIRE_EQUAL( saturatingAddition( MAX, uint64_t( 1 ) ), MAX );
    REQUIRE_EQUAL( saturatingAddition( uint64_t( 1 ), MAX ), MAX );

    REQUIRE_EQUAL( saturatingAddition( MAX - 1U, uint64_t( 1 ) ), MAX );
    REQUIRE_EQUAL( saturatingAddition( uint64_t( 1 ), MAX - 1U ), MAX );

    REQUIRE_EQUAL( saturatingAddition( MAX - 1U, uint64_t( 2 ) ), MAX );
    REQUIRE_EQUAL( saturatingAddition( uint64_t( 2 ), MAX - 1U ), MAX );

    REQUIRE_EQUAL( saturatingAddition( MAX - 3U, uint64_t( 2 ) ), MAX - 1U );
    REQUIRE_EQUAL( saturatingAddition( uint64_t( 2 ), MAX - 3U ), MAX - 1U );

    REQUIRE_EQUAL( saturatingAddition( MAX, MAX ), MAX );
    REQUIRE_EQUAL( saturatingAddition( MAX - 1U, MAX - 1U ), MAX );

    REQUIRE_EQUAL( saturatingAddition( MAX, MAX - 1U ), MAX );
    REQUIRE_EQUAL( saturatingAddition( MAX - 1U, MAX - 1U ), MAX );
}


void
testSignedSaturatingAddition()
{
    REQUIRE_EQUAL( saturatingAddition( 0, 0 ), 0 );
    REQUIRE_EQUAL( saturatingAddition( 0, 1 ), 1 );
    REQUIRE_EQUAL( saturatingAddition( 1, 0 ), 1 );
    REQUIRE_EQUAL( saturatingAddition( 1, 1 ), 2 );

    REQUIRE_EQUAL( saturatingAddition( 0, -1 ), -1 );
    REQUIRE_EQUAL( saturatingAddition( -1, 0 ), -1 );
    REQUIRE_EQUAL( saturatingAddition( -2, 1 ), -1 );
    REQUIRE_EQUAL( saturatingAddition( 1, -2 ), -1 );
    REQUIRE_EQUAL( saturatingAddition( -2, -1 ), -3 );
    REQUIRE_EQUAL( saturatingAddition( -1, -2 ), -3 );

    constexpr auto MAX = std::numeric_limits<int64_t>::max();
    REQUIRE_EQUAL( saturatingAddition( MAX, int64_t( 0 ) ), MAX );
    REQUIRE_EQUAL( saturatingAddition( int64_t( 0 ), MAX ), MAX );

    REQUIRE_EQUAL( saturatingAddition( MAX, int64_t( 1 ) ), MAX );
    REQUIRE_EQUAL( saturatingAddition( int64_t( 1 ), MAX ), MAX );

    REQUIRE_EQUAL( saturatingAddition( MAX - 1, int64_t( 1 ) ), MAX );
    REQUIRE_EQUAL( saturatingAddition( int64_t( 1 ), MAX - 1 ), MAX );

    REQUIRE_EQUAL( saturatingAddition( MAX - 1, int64_t( 2 ) ), MAX );
    REQUIRE_EQUAL( saturatingAddition( int64_t( 2 ), MAX - 1 ), MAX );

    REQUIRE_EQUAL( saturatingAddition( MAX - 3, int64_t( 2 ) ), MAX - 1 );
    REQUIRE_EQUAL( saturatingAddition( int64_t( 2 ), MAX - 3 ), MAX - 1 );

    REQUIRE_EQUAL( saturatingAddition( MAX, MAX ), MAX );
    REQUIRE_EQUAL( saturatingAddition( MAX - 1, MAX - 1 ), MAX );

    REQUIRE_EQUAL( saturatingAddition( MAX, MAX - 1 ), MAX );
    REQUIRE_EQUAL( saturatingAddition( MAX - 1, MAX - 1 ), MAX );
}


int
main()
{
    testIsBase64();
    testUnsignedSaturatingAddition();
    testSignedSaturatingAddition();

    std::cout << "Tests successful: " << ( gnTests - gnTestErrors ) << " / " << gnTests << "\n";

    return gnTestErrors;
}
