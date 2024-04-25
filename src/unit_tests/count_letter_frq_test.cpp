#include <gtest/gtest.h>
#include "../server/count_letter_frq.h"

TEST(count_letter_suite, first_test) {
  std::string in_data = "H";
  std::string exp_data = "H\t |\t 1|";
  std::string res_data = count_letter_frequency(in_data);
  ASSERT_EQ(exp_data, res_data);
}