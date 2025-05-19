#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <Int.hpp>
#include <sstream>

#define NOT_USED(var) static_cast<void>(var)

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
    }
    SECTION("check num is not equal 22") {
        REQUIRE( !(num == 22) );
        REQUIRE( num != 22 );
    }
}

TEST_CASE( "Summation and subtraction", "[base]" ) {
    Int num1(10);
    Int num2(5);
    Int num3(0);

    num3 = num1 + 2;
    REQUIRE( num3 == 12 );

    num3 = num2 + 3;
    REQUIRE( num3 == 8 );

    num3 = num1 + num2;
    REQUIRE( num3 == 15 );


    num3 = num1 - 2;
    REQUIRE( num3 == 8 );

    num3 = num2 - 3;
    REQUIRE( num3 == 2 );

    num3 = num1 - num2;
    REQUIRE( num3 == 5 );
}

TEST_CASE( "Summation+equal and subtraction+equal", "[base]" ) {
    Int num1(10);
    Int num2(3);
    Int num3(0);

    num1 += 2;
    REQUIRE( num1 == 12 );

    num3 = (num1 += 5);
    REQUIRE( num1 == 17 );
    REQUIRE( num3 == 17 );

    num1 += num2;
    REQUIRE( num1 == 20 );

    num3 = (num1 += num2);
    REQUIRE( num1 == 23 );
    REQUIRE( num3 == 23 );


    num1 -= 2;
    REQUIRE( num1 == 21 );

    num3 = (num1 -= 5);
    REQUIRE( num1 == 16 );
    REQUIRE( num3 == 16 );

    num1 -= num2;
    REQUIRE( num1 == 13 );

    num3 = (num1 -= num2);
    REQUIRE( num1 == 10 );
    REQUIRE( num3 == 10 );
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
}

TEST_CASE( "Compare tests 2", "[logic]" ) {
    SECTION("More than test") {
        Int num1 = 1;
        Int num9 = 9;
        REQUIRE( num1 < num9 );
        REQUIRE( num9 > num1 );

        REQUIRE( num1 < 9 );
        REQUIRE( num9 > 1 );

        REQUIRE( 1 < num9 );
        REQUIRE( 9 > num1 );
    }

    SECTION("More than or equal test") {
        Int num5 = 5;
        Int num6 = 6;
        REQUIRE( num5 <= num6 );
        REQUIRE( num6 >= num5 );

        REQUIRE( num5 <= 6 );
        REQUIRE( num6 >= 5 );

        REQUIRE( 6 >= num5 );
        REQUIRE( 5 <= num6 );


        REQUIRE( num5 <= num5 );
        REQUIRE( num6 >= num6 );

        REQUIRE( num6 <= 6 );
        REQUIRE( num5 >= 5 );

        REQUIRE( 6 >= num6 );
        REQUIRE( 5 <= num5 );
    }

}


TEST_CASE( "Other tests", "[other]" ) {
    SECTION("std::cout") {
        Int num = 10;

        std::ostringstream oss1;
        std::ostringstream oss2;

        oss1 << num;
        REQUIRE( oss1.str() == "10" );

        num = 5;
        oss2 << num << num;
        REQUIRE( oss2.str() == "55" );

    }
}
