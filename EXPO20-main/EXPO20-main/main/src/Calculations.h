
/// @brief not used anymore
/// @param currentAmount 
/// @return 
int checkCurrentAmount(double currentAmount);


/// @brief checks the currentAmount with the wantedAmount and returns the state
/// @param currentAmount 
/// @param wantedAmount 
/// @param minimumCE 
/// @return 
int whichState(double currentAmount, double wantedAmount, double minimumCE);

/// @brief inputs amount of degrees and get amount of steps
/// @param degrees 
/// @return steps 
long degreesToSteps(long degrees);

/// @brief main function for turning motor clockwise
/// @param RPM 
void stepperForward(int RPM);