#include <Calculations.h> 

/// @brief Check the current amount/
/// @param currentAmount 
/// @return amount + 10
int checkCurrentAmount(double currentAmount){
  // for now it is +=10
  // later it will check the weight
  currentAmount += 10;
  return currentAmount;
}

/// @brief In which state whatever
/// @param currentAmount 
/// @param wantedAmount 
/// @param minimumCE 
/// @return a value 10, 20, 30 or 0
int whichState(double currentAmount, double wantedAmount, double minimumCE){
  if (currentAmount <= 0.8*wantedAmount){//normal speed under risk amount
    return 10;
  }
  else if (currentAmount >= 0.8*wantedAmount){//slower speed above risk amount
    return 20;
  }
  else if (currentAmount >= minimumCE){//stop when in CE range
    return 30;
  }
  else{
    return 0;
    }
}