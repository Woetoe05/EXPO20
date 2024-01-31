#include <Calculations.h>


/// @brief which states determines the rpm
/// @param currentAmount 
/// @param wantedAmount 
/// @param minimumCE 
/// @return the rpm
int whichState(double currentAmount, double wantedAmount, double minimumCE){
  
  if (currentAmount <= 0.8*wantedAmount && currentAmount >= 0.5*wantedAmount && wantedAmount <= 400){
    return 40;
  } 
  else if (currentAmount <= 0.8*wantedAmount){//normal speed under risk amount
    return 100;
  }
  else if (currentAmount >= wantedAmount){//stop when above wanted amount
    return 0;
  }
  else if (currentAmount >= minimumCE){//slow down a lot when in CE range
    return 5;
  }
  else if (currentAmount >= 0.8*wantedAmount){//slower speed above risk amount
    return 20;
  }
  
  
  return 0;
}