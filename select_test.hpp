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
TEST(SelectContainsTest, SingleCharacter) {
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

TEST(SelectContainsTest, caseSensitive) {
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

TEST(SelectContainsTest, CheckBothColumnsForName) {
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

TEST(SelectANDTest, select_OneColumn_TwoSelectsOne) {
          Spreadsheet sheet;
          sheet.set_column_names({"Musical Artists"});
          sheet.add_row({"The Weeknd"});
          sheet.add_row({"Drake"});
          sheet.add_row({"Taylor Swift"});
          sheet.add_row({"Justin Bieber"});
          sheet.add_row({"Selena Gomez"});
          sheet.add_row({"Ariana Grande"});
  
          sheet.set_selection(
                  new Select_And(
                          new Select_Contains(&sheet,"Musical Artists","n"),
                          new Select_Contains(&sheet,"Musical Artists","a")));
          std::stringstream ss;
          sheet.print_selection(ss);
          std::string test = ss.str();
          EXPECT_EQ(test, "Selena Gomez \nAriana Grande \n");
  }
  
TEST(SelectANDTest, select_TwoColumns_TwoSelectsTwo) {
          Spreadsheet sheet;
          sheet.set_column_names({"Name", "FavoriteArtist"});
          sheet.add_row({"Dona Ethelbert","Bruno Mars"});
          sheet.add_row({"Frank Claire","Drake"});
          sheet.add_row({"Dorian Raquel","Taylor Swift"});
          sheet.add_row({"Fox Gus","Justin Bieber"});
          sheet.add_row({"Anton Irene","Selena Gomez"});
          sheet.add_row({"Ryleigh Haywood","Ariana Grande"});
          sheet.add_row({"Chelsie Lauressa","Logic"});
          sheet.add_row({"Romayne Danielle","The Weeknd"});
	 
	 
          sheet.set_selection(new Select_And(new Select_Contains(&sheet,"FavoriteArtist","n"),
                          new Select_Contains(&sheet,"Name","n")));
            std::stringstream ss;
            sheet.print_selection(ss);
            std::string test = ss.str();
           EXPECT_EQ(test, "Dona Ethelbert Bruno Mars \nAnton Irene Selena Gomez \nRomayne Danielle The Weeknd \n");
   }
 
 TEST(SelectORTest, selectOneColumn_TwoSelectsOne) {
         Spreadsheet sheet;
         sheet.set_column_names({"CarBrands"});
         sheet.add_row({"BMW"});
         sheet.add_row({"Mercedes"});
         sheet.add_row({"Honda"});
         sheet.add_row({"Toyota"});
         sheet.add_row({"Lexus"});
         sheet.add_row({"Land Rover"});
         sheet.add_row({"Tesla"});
 
         sheet.set_selection(new Select_Or(new Select_Contains(&sheet,"CarBrands","BMW"),
                         new Select_Contains(&sheet,"CarBrands","es")));
 
         std::stringstream ss;
         sheet.print_selection(ss);
         std::string test = ss.str();
         EXPECT_EQ(test, "BMW \nMercedes \nTesla \n");
 }
 
 TEST(SelectORTest, select_TwoColumns_noMatchOne) {
	        Spreadsheet sheet;
         sheet.set_column_names({"Name", "FavoriteCarBrand"});
         sheet.add_row({"Dona Ethelbert","Acura"});
         sheet.add_row({"Frank Claire","Subaru"});
         sheet.add_row({"Dorian Raquel","Chevrolet"});
         sheet.add_row({"Fox Gus","Ford"});
         sheet.add_row({"Anton Irene","Mitsubishi"});
         sheet.add_row({"Ryleigh Haywood","Hyundai"});
         sheet.add_row({"Chelsie Lauressa","Volkswagen"});
         sheet.add_row({"Romayne Danielle","Audi"});
 
         sheet.set_selection(new Select_Or(new Select_Contains(&sheet,"FavoriteCarBrand","Ferrari"),
                                         new Select_Contains(&sheet,"Name","Greg")));
 
         std::stringstream ss;
         sheet.print_selection(ss);
         std::string test = ss.str();
         EXPECT_EQ(test, "");
 }

TEST(SelectNOTTest, OneColumnNoMatch) {
	Spreadsheet sheet;
	sheet.set_column_names({"Food"});
	sheet.add_row({"apple"});
	sheet.add_row({"apples"});
	sheet.add_row({"Snapple"});

	sheet.set_selection(
		new Select_Not( 
			new Select_Contains(&sheet,"Food","apple")));

	std::stringstream ss;
	sheet.print_selection(ss);
	std::string test = ss.str();
	EXPECT_EQ(test, "");
}

TEST(SelectNOTTest, OneColumnNoMatchNoData) {
	Spreadsheet sheet;

	sheet.set_selection(
		new Select_Not( 
			new Select_Contains(&sheet,"Food","Apple")));

	std::stringstream ss;
	sheet.print_selection(ss);
	std::string test = ss.str();
	EXPECT_EQ(test, "");
}

#endif //__SELECT_TEST__
