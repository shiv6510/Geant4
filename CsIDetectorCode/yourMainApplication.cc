
// Include global-definitions
#include "globals.hh"

// RunManager include (depending if Serial or MT)
//#include "G4RunManagerFactory.hh"
#include "G4RunManager.hh"
// Your detector construction and user action initialization
#include "CsIConstruction.hh"
#include "YourActionInitialization.hh"

// To use and combine the reference physics lists
#include "G4PhysListFactory.hh"

// For the UI manager (to execute the G4 macro input file)
#include "G4UImanager.hh"

// For VIS and/or UI-session
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4ScoringManager.hh"

#include "FTFP_BERT.hh"
#include "G4StepLimiterPhysics.hh"
//#include "CsIPhysicsList.hh"

#include "G4OpticalPhysics.hh"
#include "G4EmStandardPhysics.hh"

#include "physics.hh"
int main(int argc, char** argv)
{
    // Interactive OR batch mode? Check the inputs:
    // - if no arguments i.e. argc = 1 (i.e. no macro file)
    //    => interactive mode: create G4UIExecutive i.e. UI session for interactive
    //                         command executions
    // - if argument is given i.e. argc = 2 (i.e. macro file)
    //    => batch mode: macro file will be processed by the G4UImanager
    //                   (the UI manager can execute commands given as string
    //                    by its ApplyCommand method)
    G4String macrofile = "";
    G4UIExecutive* ui  = nullptr;
    if ( argc == 1 )
    {
      // If you want to specifty the UI-session type i.e. qt, csh, tcsh, etc.
      // the one with higher priority will be used otherwise and GUI (e.g. qt)
      // has higher prioriy compared to terminals.
      // ui = new G4UIExecutive(argc, argv, "tcsh");
      ui = new G4UIExecutive(argc, argv);
    }
    else
    {
      macrofile = argv[1];
      G4cout << " Reading G4 commands from macro file" << macrofile << " \n";
    }

    // Construct the default run manager (MT)
    //
    G4RunManager * runManager = new G4RunManager;
    //G4RunManager* runManager = new G4MTRunManager;
    //G4ScoringManager* scoringManager = G4ScoringManager::GetScoringManager();
                                             
    // Set (MANDATORY) User initialization classes:
    //  = 1. G4VUserDetectorConstruction
    //  = 2. G4VUserPhysicsList
    //  = 3. G4VUserActionInitialization (that contains G4VUserPrimaryGeneratorAction)
    //
    // 1. DetectorConstruction = CsIConstruction <- G4VUserDetectorConstruction
    CsIConstruction* detector = new CsIConstruction;
    runManager->SetUserInitialization( detector );
    //
    // 2. PhysicsList = G4VModularPhysicsList <- G4VUserPhysicsList
    //    (use reference physics list through the G4PhysListFactory)
   //const G4String plName = "FTFP_BERT_EMZ";
   //G4PhysListFactory plFactory;
   //G4VModularPhysicsList *pl = plFactory.GetReferencePhysList( plName );
  // G4VModularPhysicsList *pl=new FTFP_BERT;
  // pl->RegisterPhysics(new G4EmStandardPhysics());
  // pl->RegisterPhysics(new G4OpticalPhysics());
   runManager->SetUserInitialization( new MyPhysicsList() ); 
    
    //runManager->SetUserInitialization(pl);
    //
    // 3. ActionInitialization = YourActionInitialization <- G4VUserActionInitialization
    //    (and YourActionInitialization contains YourPrimaryGeneratorAction which is
    //     <- G4VUserPrimaryGeneratorActions)
    //    Note, that:
    //     - all other UserActions (Run, Event, Stepping, Tracking, Stacking) are optional !
    //     - the DetectorConstruction pointer is propagated down to the UserActions
    //       because some actions (e.g. PrimaryGenerator) needs information from the detector.
    runManager->SetUserInitialization( new YourActionInitialization() );
   
    // Initialize the RunManager and execute 10 events
      runManager->Initialize();
//    runManager->BeamOn(10);

    // Add visualization:
    // - create a G4VisExecutive object as the Visualization Manager
    // - initialize the Visualization Manager (will handle all vis components)
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    // Get the pointer to the User Interface manager.
    G4UImanager* UI = G4UImanager::GetUIpointer();

    // Then either:
    // - batch mode: process the macro file
    // - interactive mode: create ui-session
    if ( ! ui )
    {
      // batch mode
      G4String command  = "/control/execute ";
      UI->ApplyCommand( command + macrofile );

      // Here we are after the batch execution!
    }
    else
    {
      // interactive mode
      //UI->ApplyCommand("/control/execute vis.mac");
      ui->SessionStart();
      // Here we are after the ui-session termination!
      delete ui;
    }

    // Delete the Visualization Manager
    delete visManager;

    // At the end delete the Run Manager
    delete runManager;

    return 0;
}
