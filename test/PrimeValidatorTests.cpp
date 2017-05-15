/*
 * PrimeValidatorTests.cpp
 *
 *  Created on: May 11, 2017
 *      Author: gkiessling
 */

#include "catch.hpp"

#include "PrimeValidator.h"

SCENARIO("Unsigned long longs can be validated as prime or not prime")
{
    GIVEN("A PrimeValidator instance")
    {
        PrimeValidator validator;

        WHEN("A value less than two is provided")
        {
            THEN("The result is false")
            {
                REQUIRE(!validator.isPrime(static_cast<unsigned long long>(0)));
                REQUIRE(!validator.isPrime(1));
            }
        }

        WHEN("A prime number is provided")
        {
            THEN("The result is true")
            {
                REQUIRE(validator.isPrime(2LL));
                REQUIRE(validator.isPrime(3LL));
                REQUIRE(validator.isPrime(5LL));
                REQUIRE(validator.isPrime(7LL));
                REQUIRE(validator.isPrime(11LL));
                REQUIRE(validator.isPrime(13LL));
                REQUIRE(validator.isPrime(17LL));
                REQUIRE(validator.isPrime(23LL));
                REQUIRE(validator.isPrime(65537LL));
                REQUIRE(validator.isPrime(982451653LL));
                REQUIRE(validator.isPrime(4257452468389LL));
            }
        }

        WHEN("A non-prime number is provided")
        {
            THEN("The result is false")
            {
                REQUIRE(!validator.isPrime(4LL));
                REQUIRE(!validator.isPrime(6LL));
                REQUIRE(!validator.isPrime(9LL));
                REQUIRE(!validator.isPrime(15LL));
                REQUIRE(!validator.isPrime(32LL));
                REQUIRE(!validator.isPrime(33LL));
                REQUIRE(!validator.isPrime(35LL));
                REQUIRE(!validator.isPrime(49LL));
                REQUIRE(!validator.isPrime(34585LL));
                REQUIRE(!validator.isPrime(982451653LL * 982451653LL));
            }
        }
    }
}

// Using InfInt here results in duplicate symbols when linked due to
// implementation improperly included in header.
//SCENARIO("InfInts can be validated as prime or not prime")
//{
//    GIVEN("A PrimeValidator instance")
//    {
//        PrimeValidator validator;
//
//        WHEN("A value less than two is provided")
//        {
//            THEN("The result is false")
//            {
//                REQUIRE(!validator.isPrime(InfInt(0)));
//                REQUIRE(!validator.isPrime(InfInt(1)));
//            }
//        }
//
//        WHEN("A prime number is provided")
//        {
//            THEN("The result is true")
//            {
//                REQUIRE(validator.isPrime(InfInt(2)));
//                REQUIRE(validator.isPrime(InfInt(3)));
//                REQUIRE(validator.isPrime(InfInt(5)));
//                REQUIRE(validator.isPrime(InfInt(7)));
//                REQUIRE(validator.isPrime(InfInt(11)));
//                REQUIRE(validator.isPrime(InfInt(13)));
//                REQUIRE(validator.isPrime(InfInt(17)));
//                REQUIRE(validator.isPrime(InfInt(23)));
//                REQUIRE(validator.isPrime(InfInt(65537)));
//                REQUIRE(validator.isPrime(InfInt(982451653)));
//                REQUIRE(validator.isPrime(InfInt(4257452468389)));
//            }
//        }
//
//        WHEN("A non-prime number is provided")
//        {
//            THEN("The result is false")
//            {
//                REQUIRE(!validator.isPrime(InfInt(4)));
//                REQUIRE(!validator.isPrime(InfInt(6)));
//                REQUIRE(!validator.isPrime(InfInt(9)));
//                REQUIRE(!validator.isPrime(InfInt(15)));
//                REQUIRE(!validator.isPrime(InfInt(32)));
//                REQUIRE(!validator.isPrime(InfInt(33)));
//                REQUIRE(!validator.isPrime(InfInt(35)));
//                REQUIRE(!validator.isPrime(InfInt(49)));
//                REQUIRE(!validator.isPrime(InfInt(34585)));
//                REQUIRE(!validator.isPrime(InfInt(982451653) * InfInt(4257452468389)));
//            }
//        }
//    }
//}

SCENARIO("An arbitrarily long integer in string form can be validated as prime or not prime")
{
    GIVEN("A PrimeValidator instance")
    {
        PrimeValidator validator;

        WHEN("A value less than two is provided")
        {
            THEN("The result is false")
            {
                REQUIRE(!validator.isPrime("0"));
                REQUIRE(!validator.isPrime("1"));
            }
        }

        WHEN("A prime number is provided")
        {
            THEN("The result is true")
            {
                REQUIRE(validator.isPrime("2"));
                REQUIRE(validator.isPrime("3"));
                REQUIRE(validator.isPrime("5"));
                REQUIRE(validator.isPrime("7"));
                REQUIRE(validator.isPrime("11"));
                REQUIRE(validator.isPrime("13"));
                REQUIRE(validator.isPrime("17"));
                REQUIRE(validator.isPrime("23"));
                REQUIRE(validator.isPrime("65537"));
                REQUIRE(validator.isPrime("982451653"));
                REQUIRE(validator.isPrime("4257452468389"));
                REQUIRE(validator.isPrime("12764787846358441471"));
//                REQUIRE(validator.isPrime("71755440315342536873"));
            }
        }

        WHEN("A non-prime number is provided")
        {
            THEN("The result is false")
            {
                REQUIRE(!validator.isPrime("4"));
                REQUIRE(!validator.isPrime("6"));
                REQUIRE(!validator.isPrime("9"));
                REQUIRE(!validator.isPrime("15"));
                REQUIRE(!validator.isPrime("32"));
                REQUIRE(!validator.isPrime("33"));
                REQUIRE(!validator.isPrime("35"));
                REQUIRE(!validator.isPrime("49"));
                REQUIRE(!validator.isPrime("34585"));
                REQUIRE(!validator.isPrime("33333333333333333333333333333"));
                REQUIRE(!validator.isPrime("27346726347862387628734678235"));
                // Long running test
//                REQUIRE(!validator.isPrime("4182741215137703297017")); // 982451653 * 4257452468389
            }
        }
    }
}
