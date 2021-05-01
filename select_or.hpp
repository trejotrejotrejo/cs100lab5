#ifndef __SELECT_AND_HPP__
#define __SELECT_AND_HPP__
 
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
           if (position1->select(sheet, row) == true || position2->select(sheet, row) == true) {
                 return true;
            }
           else {
                return false;
            }
       }
  };
  
