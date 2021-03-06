/*
 * Robot Testing Framework
 *
 * Copyright (C) 2015-2019 Istituto Italiano di Tecnologia (IIT)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */


#include <robottestingframework/ConsoleListener.h>
#include <robottestingframework/FixtureManager.h>
#include <robottestingframework/TestAssert.h>
#include <robottestingframework/TestCase.h>
#include <robottestingframework/TestResult.h>
#include <robottestingframework/TestResultCollector.h>
#include <robottestingframework/TestRunner.h>
#include <robottestingframework/TestSuite.h>

#include <cstdio>

using namespace robottestingframework;

class MyTest1 : public TestCase
{
public:
    MyTest1() :
            TestCase("MyTest1")
    {
    }

    void run() override
    {
        ROBOTTESTINGFRAMEWORK_TEST_REPORT("testing smaller");
        ROBOTTESTINGFRAMEWORK_TEST_FAIL_IF_FALSE(3 < 5, "is not smaller");
    }
};

class MyTest2 : public TestCase
{
public:
    MyTest2() :
            TestCase("MyTest2")
    {
    }

    void run() override
    {
        ROBOTTESTINGFRAMEWORK_TEST_REPORT("testing equality");
        ROBOTTESTINGFRAMEWORK_TEST_FAIL_IF_FALSE(3 == 3, "are not equal");
    }
};

class MyFixture : public FixtureManager
{
public:
    MyFixture(FixtureEvents* dispatcher) :
            FixtureManager(dispatcher)
    {
    }

    bool setup(int argc, char** argv) override
    {
        // setup and initialize the fixture
        // ...
        printf("Myfixture setup!\n");
        // return true if everything is fine.
        return true;
    }

    bool check() override
    {
        printf("Myfixture checking ...\n");
        return true;
    }

    void tearDown() override
    {
        // uninitialize the fixture
        // ...
        printf("Myfixture tear down!\n");
        // for an example if there is any error during tear down,
        // throw an exception.
        throw FixtureException(TestMessage("MyFixture cannot tear down!"));
    }
};

int main(int argc, char** argv)
{
    // create a test listener to collect the result
    ConsoleListener listener(false);

    // create a collector to get computer readable
    // test results
    TestResultCollector collector;

    // create a test result and add the listeners
    TestResult result;
    result.addListener(&listener);
    result.addListener(&collector);

    // create a test suite
    TestSuite suite("MyTestSuite");

    // create a fixture manager for the test suite
    MyFixture fixture(&suite);
    suite.addFixtureManager(&fixture);

    // creates test cases and add them to the suite
    MyTest1 test1;
    MyTest2 test2;
    suite.addTest(&test1);
    suite.addTest(&test2);

    // create a test runner and run the tests
    TestRunner runner;
    runner.addTest(&suite);
    runner.run(result);

    // return the number of failed tests
    return collector.failedCount();
}
