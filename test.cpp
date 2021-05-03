#include "spreadsheet.hpp"
#include "gtest/gtest.h"
#include "select.hpp"
#include <cstring>
#include "select_test.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
