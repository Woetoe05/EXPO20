#include <Calculations.h>


/// @brief In which state 
/// @param currentAmount 
/// @param wantedAmount 
/// @param minimumCE 
/// @return a value 10, 20, 30
int whichState(double currentAmount, double wantedAmount, double minimumCE){
  if (currentAmount <= 0.8*wantedAmount){//normal speed under risk amount
    return 10;
  }
  else if (currentAmount >= minimumCE){//stop when in CE range
    return 30;
  }
  else if (currentAmount >= 0.8*wantedAmount){//slower speed above risk amount
    return 20;
  }
  return 0;
}