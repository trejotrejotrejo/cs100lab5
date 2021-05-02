#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <string>
using namespace std;

class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.
class Select_Column: public Select
{
protected:
    int column;
public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;
};

class Select_Contains: public Select {
protected:
    int column;
    string input;
public:   
    Select_Contains(const Spreadsheet* sheet, const std::string& name, const std::string& name2) {
        column = sheet->get_column_by_name(name);
        input = name2;
    }
    bool select(const Spreadsheet* sheet, int row) const {
        string test; 
        test = sheet->cell_data(row,column);
        size_t found = test.find(input);
        if (found != string::npos) {
           return true;
        }
        else {
           return false;
        }
    }
};

class Select_Not: public Select {
protected:
   Select* position;
public:
   Select_Not(Select* pos) {
       position = pos;
   }
   ~Select_Not() {
       delete position;
   }
   bool select(const Spreadsheet* sheet, int row) const {
       return !(this->position->select(sheet,row));
   }
};

class Select_And : public Select {

protected:
	Select *position1;
	Select *position2;

public:
	Select_And(Select* pos1, Select* pos2) {
		position1 = pos1;
		position2 = pos2;
	}
	~Select_And() {
		delete position1;
		delete position2;
	}
	bool select(const Spreadhsheet* sheet, int row) const {
		if (position1->select(sheet, row) == true && position2->select(sheet, row) == true) {
			return true;
		}
		else {
			return false;
		}
	}
};

class Select_Or : public Select { 
  protected:
      Select *position1;
      Select *position2;
  
  public:
      Select_Or(Select* pos1, Select* pos2) {
               position1 = pos1;
               position2 = pos2;
      }
     ~Select_Or() {
           delete position1;
           delete position2;
      }
      bool select(const Spreadhsheet* sheet, int row) const {
           if (position1->select(sheet, row) == true || position2->select(sheet, row) == true) {
                 return true;
            }
           else {
                return false;
            }
       }
};
 
#endif //__SELECT_HPP__
