# prime-server
Simple server for verifying the primality of positive integers.

## Building and Running
From the top level directory, run `make`.

To build and run the unit tests, run `make test`.

To start the server, run `./prime-server prime-server.conf`.

To use the client to send a primality test request, run `./prime-client 127.0.0.1:50000 1234567`.

## Tests
Due to time constraints, the test set is not complete. As such, unit tests only
exist for the `PrimeValidator` class. Furthermore, due to incorrect header-only
implementation of InfInt, the tests for the InfInt overloads of `PrimeValidator::isPrime()`
are commented out. A couple of long-running tests are also commented out.

## Design and Implementation
The initial design of the project consists of three simple components:
* `PrimeClient`
    * Requests a primality test by sending a single integer in string form
    with a newline terminator to `PrimeServer`.
    * Reports the result of the test on the command line and then exits.
* `PrimeServer`
    * Spawns a new thread for each primality test request (asynchronous IO
    would be a better approach for a "production" implementation).
    * Uses `PrimeValidator` to test arbitrarily large numbers for primality.
    * Replies with "true" or "false" followed by a newline terminator.
* `PrimeValidator`
    * Provies `isPrime()` implementations for `unsigned long long`, `InfInt`
    and `string`.
    * The `InfInt` and `string` overloads call the `unsigned long long` overload
    when the argument is small enough to fit.

In terms of design for optimum performance, there are a few possible approaches:
* Build up a cache of known prime numbers
* Reduce the number of modulus calculations
* Distribute the modulus calculations among multiple servers

The second approach is related to the first because, when iterating through
integers to test for divisibility, only primes need to be tested. So to do the
minimum number of modulus calculations requires generating a cache of all
prime numbers up to the square root of the number under test. Doing so, however,
would quickly use up a lot of memory and storage, as [over two quintillion prime
numbers can be represented in a 64-bit unsigned integer](https://primes.utm.edu/howmany.html).
Nonetheless, the collection of known primes could easily be split into ranges
and distributed among multiple servers; subsequent lookups would certainly be
very fast for known primes.

Short of only testing divisibility by primes, the set of numbers to test can be
reduced by 50% by only testing divisibility by odd numbers (as well as by 2);
my implementation uses this optimization. The set could be reduced by over 70%
by also not testing by multiples of 3 and 5 (by starting with 5 and incrementing
the test number by 2, 4 or 6 in a sequence like (2, 4, 2, 4, 2, 4, 6...)),
however the extra complexity was not worthwhile for this project.

In terms of infrastructure, the most cost-effective optimization is the third
approach identified above, namely to distribute calculations among multiple
servers. I had intended to implement this optimization (note the "auxilliary
servers" listed in `prime-server-aux.conf`, the `PrimeClient` instances
loaded into `PrimeServer` and the `sendDivisibleByOddRangeTest()` method defined
in `PrimeClient`), however I have not been able to complete it due to time
constraints. 

One further performance optimization in my implementation is the use of the
InfInt big integer implementation when the number under test is too large to
fit in a 64-bit unsigned integer. 

## Third Party Libraries
The implementation includes the following third party libraries:
* Catch - unit testing framework
* InfInt - Big integer implementation
* RapidJSON - JSON parser - used to parse the server configuration file
