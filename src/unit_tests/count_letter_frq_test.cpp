#include <gtest/gtest.h>
#include "../server/count_letter_frq.h"

TEST(count_letter_suite, first_test) {
  std::string in_data = "12356 \t\t\t 00 _^&";
  std::string exp_data = get_table_header(in_data);
  std::string res_data = count_letter_frequency(in_data);
  ASSERT_EQ(exp_data, res_data);
}
