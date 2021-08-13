
#include "YourActionInitialization.hh"

#include "YourPrimaryGeneratorAction.hh"

#include "CsIConstruction.hh"
#include "CsIEventAction.hh"
#include "RunAction.hh"
YourActionInitialization::YourActionInitialization()
:   G4VUserActionInitialization()
   
{
}


YourActionInitialization::~YourActionInitialization()
{
}

// NOT CALLED IN SEQUENTIAL MODE i.e. ONLY FOR MT:
// - ONLY FOR creating RunAction for the Master thread
void YourActionInitialization::BuildForMaster() const
{
    SetUserAction(new RunAction);
}

// Create all User Actions here:
// - for sequential mode (will be invoked immediately by the only one G4RunManager
//   when the ActionInitialization object is registered in it in the main)
// - for worker threads (will be invoked later by all worker G4RunManager-s)
//
void YourActionInitialization::Build() const
{
  // Set UserPrimaryGeneratorAction
  YourPrimaryGeneratorAction* primaryAction = new YourPrimaryGeneratorAction();
  SetUserAction(primaryAction);
  SetUserAction(new CsIEventAction); 
 SetUserAction(new RunAction);
}
