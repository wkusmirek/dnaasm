#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../../../src/bst/Chainer.hpp"

using namespace dnaasm::bst;
typedef Chainer::S S;

class F : public Chainer {
public:
    F() : Chainer() {}
};

BOOST_FIXTURE_TEST_SUITE(ChainerTests, F)

BOOST_AUTO_TEST_CASE(chainer_s_less_operator)
{
    S s0(0,0);
    S s1(2,8);
    S s2(1,8);
    BOOST_CHECK(s0 < s1);
    BOOST_CHECK(!(s1 < s2));
}

BOOST_AUTO_TEST_CASE(chainer_gap_score)
{
    S s0(0, 0);
    S s1(5, 5);
    S s2(6, 12);
    BOOST_CHECK_EQUAL(gapScore(s0,s1), 0);
    BOOST_CHECK_EQUAL(gapScore(s1,s2), 6);
}

BOOST_AUTO_TEST_CASE(chainer_generic_chaining_init)
{
    std::vector<S> s = {S(1,2), S(3,4)};
    genericChaining(s);
    BOOST_CHECK_EQUAL_COLLECTIONS(result_.rbegin(), result_.rend(),
                                  s.begin(), s.end());
}

BOOST_AUTO_TEST_CASE(chainer_generic_chaining_middle_wrong)
{
    std::vector<S> s = {S(1,2), S(2,7), S(3,4)};
    std::vector<S> r = {S(1,2), S(3,4)};
    genericChaining(s);
    BOOST_CHECK_EQUAL_COLLECTIONS(result_.rbegin(), result_.rend(),
                                  r.begin(), r.end());
}

BOOST_AUTO_TEST_CASE(chainer_generic_chaining_last_wrong)
{
    std::vector<S> s = {S(1,2), S(2,4), S(3,1)};
    std::vector<S> r = {S(1,2), S(2,4)};
    genericChaining(s);
    BOOST_CHECK_EQUAL_COLLECTIONS(result_.rbegin(), result_.rend(),
                                  r.begin(), r.end());
}

BOOST_AUTO_TEST_CASE(chainer_generic_chaining_first_wrong)
{
    std::vector<S> s = {S(5,6), S(1,2), S(3,4)};
    std::vector<S> r = {S(1,2), S(3,4)};
    genericChaining(s);
    BOOST_CHECK_EQUAL_COLLECTIONS(result_.rbegin(), result_.rend(),
                                  r.begin(), r.end());
}

BOOST_AUTO_TEST_CASE(chainer_generic_chaining_real_test1)
{
    std::vector<S> s = {S(1536,9498),S(9378,3902),S(9419,17),S(9597,195),S(9598,196),S(9599,3930),S(9600,197),S(9601,198)};
    std::vector<S> r = {S(9419,17),S(9597,195),S(9598,196),S(9600,197),S(9601,198)};
    genericChaining(s);
    BOOST_CHECK_EQUAL_COLLECTIONS(result_.rbegin(), result_.rend(),
                                  r.begin(), r.end());
}

BOOST_AUTO_TEST_CASE(chainer_generic_chaining_manhattan)
{
    std::vector<S> s = {S(2,3), S(4,1), S(5,6), S(7,2)};
    std::vector<S> r = {S(2,3), S(5,6)};
    genericChaining(s);
    BOOST_CHECK_EQUAL_COLLECTIONS(result_.rbegin(), result_.rend(),
                                  r.begin(), r.end());
}

BOOST_AUTO_TEST_CASE(chainer_get_result)
{
    std::vector<S> s = {S(10,15), S(20,25)};
    Chainer c;
    std::vector<S>& r = c.genericChaining(s);
    BOOST_CHECK_EQUAL_COLLECTIONS(r.rbegin(), r.rend(),
                                  s.begin(), s.end());
}

BOOST_AUTO_TEST_SUITE_END()
