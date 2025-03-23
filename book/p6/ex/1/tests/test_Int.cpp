#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <Int.hpp>

#define NOT_USED(var) static_cast<void>(var);

TEST_CASE( "Simple tests", "[base]" ) {
    SECTION("Create empty obj") {
        Int num;
        NOT_USED(num);
    }

    SECTION("Create empty obj and compare with zero") {
        Int num;
        REQUIRE( num == 0 );
    }
}

TEST_CASE( "Create obj with number", "[base]" ) {
    Int num(21);
    NOT_USED(num);
}

TEST_CASE( "Create obj with number and compare value", "[base]" ) {
    Int num(21);

    SECTION("check num is equal 21") {
        REQUIRE( num == 21 );
        REQUIRE( num.getValue() == 21 );
    }
    SECTION("check num is not equal 22") {
        REQUIRE( !(num == 22) );
        REQUIRE( num != 22 );
    }
}

TEST_CASE( "Compare tests", "[logic]" ) {
    Int num;

    SECTION("Change value after creating obj") {
        num = 11;
        REQUIRE( num == 11 );
    }

    SECTION("Init obj by other obj after creation") {
        Int num2;
        num2 = num = 2;
        REQUIRE( num2 == 2 );
    }

    SECTION("Init obj by other obj while creation") {
        Int num2 = num = 2;
        num = 3;
        REQUIRE( num2 == 2 );
        REQUIRE( num == 3 );
    }

    SECTION("Compare 2 obj") {
        Int num2 = 5;
        num = 5;
        REQUIRE( num == num2 );

        num = 3;
        REQUIRE( !(num == num2) );

        REQUIRE( num != num2 );
    }

    SECTION("More than test") {
        Int num1 = 1, num9 = 9;
        REQUIRE( num1 < num9 );
        REQUIRE( num9 > num1 );

        REQUIRE( num1 < 9 );
        REQUIRE( num9 > 1 );

        REQUIRE( 1 < num9 );
        REQUIRE( 9 > num1 );
    }

}
