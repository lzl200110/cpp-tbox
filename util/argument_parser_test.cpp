#include <gtest/gtest.h>

#include <tbox/base/defines.h>
#include "argument_parser.h"

using namespace tbox::util;

TEST(ArgumentParser, Fail)
{
    const char* argv[] = {"test_fail", "-x"};
    ArgumentParser parser(
        [&](char short_opt, const std::string &long_opt, ArgumentParser::OptionValue& opt_value) {
            return false;
        }
    );

    ASSERT_FALSE(parser.parse(NUMBER_OF_ARRAY(argv), argv));
}

TEST(ArgumentParser, LongOptionKeyAndValue)
{
    const char* argv[] = {"test_long_opt_key_and_value", "--key=123", "-n"};
    ArgumentParser parser(
        [&](char short_opt, const std::string &long_opt, ArgumentParser::OptionValue& opt_value) {
            if (short_opt == 0) {
                EXPECT_EQ(long_opt, "key");
                EXPECT_TRUE(opt_value.valid());
                EXPECT_EQ(opt_value.get(), "123");
            } else {
                EXPECT_EQ(short_opt, 'n');
                EXPECT_FALSE(opt_value.valid());
            }
            return true;
        }
    );
    ASSERT_TRUE(parser.parse(NUMBER_OF_ARRAY(argv), argv));
}

TEST(ArgumentParser, All)
{
    const char* argv[] = {"test_all", "-ab", "123", "-x", "--set", "xyz", "--run"};
    ArgumentParser parser(
        [&](char short_opt, const std::string &long_opt, ArgumentParser::OptionValue& opt_value) {
            if (short_opt == 'a') {
                EXPECT_FALSE(opt_value.valid());
            } else if (short_opt == 'b') {
                EXPECT_TRUE(opt_value.valid());
                EXPECT_EQ(opt_value.get(), "123");
            } else if (short_opt == 'x') {
                EXPECT_TRUE(opt_value.valid());
            } else if (long_opt == "set") {
                EXPECT_TRUE(opt_value.valid());
                EXPECT_EQ(opt_value.get(), "xyz");
            } else if (long_opt == "run") {
                EXPECT_FALSE(opt_value.valid());
            } else {
                return false;
            }
            return true;
        }
    );

    ASSERT_TRUE(parser.parse(NUMBER_OF_ARRAY(argv), argv));
}
