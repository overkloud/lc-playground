#include "gtest/gtest.h"
#include "../Solution.h"
 


namespace {

    // The fixture for testing class Foo.
    class SolutionTest : public ::testing::Test {
    protected:
        // You can remove any or all of the following functions if its body
        // is empty.

        SolutionTest() {
            // You can do set-up work for each test here.
        }

        virtual ~SolutionTest() {
            // You can do clean-up work that doesn't throw exceptions here.
        }

        // If the constructor and destructor are not enough for setting up
        // and cleaning up each test, you can define the following methods:

        virtual void SetUp() {
            // Code here will be called immediately after the constructor (right
            // before each test).
        }

        virtual void TearDown() {
            // Code here will be called immediately after each test (right
            // before the destructor).
        }

        // Objects declared here can be used by all tests in the test case for Foo.
    };

    // Tests that the Foo::Bar() method does Abc.
    TEST_F(SolutionTest, SplitString) {
        vint v = splitToInts("1 2 3 4 5");
        ASSERT_EQ(v.size(), 5);
        ASSERT_EQ(v[0], 1);
        ASSERT_EQ(v[1], 2);
        ASSERT_EQ(v[2], 3);
        ASSERT_EQ(v[3], 4);
        ASSERT_EQ(v[4], 5);


        v = splitToInts("1 2 3 4 5", ' ', 2);
        ASSERT_EQ(v.size(), 2);
        ASSERT_EQ(v[0], 1);
        ASSERT_EQ(v[1], 2);

        v = splitToInts("1 2 3 4 5  ", ' ', 5);
        ASSERT_EQ(v.size(), 5);
        ASSERT_EQ(v[0], 1);
        ASSERT_EQ(v[1], 2);
        ASSERT_EQ(v[2], 3);
        ASSERT_EQ(v[3], 4);
        ASSERT_EQ(v[4], 5);

        v = splitToInts("1 2 3 4 5  ");
        ASSERT_EQ(v.size(), 5);
        ASSERT_EQ(v[0], 1);
        ASSERT_EQ(v[1], 2);
        ASSERT_EQ(v[2], 3);
        ASSERT_EQ(v[3], 4);
        ASSERT_EQ(v[4], 5);

        v = splitToInts("1 2 3   4 5  ", ' ', 5);
        ASSERT_EQ(v.size(), 5);
        ASSERT_EQ(v[0], 1);
        ASSERT_EQ(v[1], 2);
        ASSERT_EQ(v[2], 3);
        ASSERT_EQ(v[3], 4);
        ASSERT_EQ(v[4], 5);

        v = splitToInts("   1 2 3   4 5  ", ' ', 5);
        ASSERT_EQ(v.size(), 5);
        ASSERT_EQ(v[0], 1);
        ASSERT_EQ(v[1], 2);
        ASSERT_EQ(v[2], 3);
        ASSERT_EQ(v[3], 4);
        ASSERT_EQ(v[4], 5);
    }



}  // namespace

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}