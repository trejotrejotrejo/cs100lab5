#ifndef __SELECT_TEST__
#define __SELECT_TEST__
#include "spreadsheet.hpp"
#include "select.hpp"

#include <string>
#include <sstream>

#include "gtest/gtest.h"


TEST(SpreadsheetTest, blankSheet) {
	Spreadsheet sheet;
	std::stringstream ss;
	sheet.print_selection(ss);
	std::string test = ss.str();
	EXPECT_EQ(test, "");
}

 TEST(SpreadsheetTest, columnNameNoEntries) {
        Spreadsheet sheet;
	sheet.set_column_names({"Sports"});
	sheet.set_selection(new Select_Contains(&sheet, "Sports", "golf"));
        std::stringstream ss;
        sheet.print_selection(ss);
        std::string test = ss.str();
        EXPECT_EQ(test, "");
 }
TEST(ContainTest, SingleCharacter) {
	Spreadsheet sheet;
	sheet.set_column_names({"First"});
	sheet.add_row({"Goldfish"});
	sheet.add_row({"Hamster"});
	sheet.add_row({"Rabbit"});
	sheet.add_row({"Kitten"});
	sheet.set_selection(new Select_Contains(&sheet,"First", "t"));
	std::stringstream ss;
	sheet.print_selection(ss);
	std::string str = ss.str();
	ASSERT_EQ(str, "Hamster \nRabbit \nKitten \n");
}

TEST(SelectTest, caseSensitive) {
	Spreadsheet sheet;
	sheet.set_column_names({"Food"});
	sheet.add_row({"apple"});
	sheet.add_row({"apples"});
	sheet.add_row({"APPLE"});
	sheet.add_row({"Snapple"});
	sheet.add_row({"app"});
	
	sheet.set_selection(new Select_Contains(&sheet, "Food", "apple"));
	
	std::stringstream ss;
	sheet.print_selection(ss);
	std::string test = ss.str();
	EXPECT_EQ(test, "apple \napples \nSnapple \n");
}

TEST(ContainTest, CheckBothColumnsForName) {
 Spreadsheet sheet;
        sheet.set_column_names({"First","First"});
        sheet.add_row({"Red", "Coca-Cola"});
        sheet.add_row({"Blue", "Pepsi"});
        sheet.add_row({"Orange", "Fanta"});
        sheet.set_selection(new Select_Contains(&sheet,"First", "Red"));
        std::stringstream ss;
        sheet.print_selection(ss);
        std::string str = ss.str();
        ASSERT_EQ(str,"Red Coca-Cola \n");
}



#endif //__SPREADSHEET_TEST__
