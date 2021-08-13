#include "CsIEventAction.hh"
#include "CsIHit.hh"

#include "Analysis.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
CsIEventAction :: CsIEventAction() : G4UserEventAction(), HCID(-1) 
{
       pSDMan = G4SDManager :: GetSDMpointer();
       G4RunManager::GetRunManager()->SetPrintProgress(1);     


}
 CsIEventAction :: ~CsIEventAction()
{

}
void CsIEventAction::BeginOfEventAction(const G4Event* event)
{
   if(HCID ==-1)
    {
        
        HCID = pSDMan -> GetCollectionID("CsISD/CsICollect"); //CsIHitsCollection wrong ID? 

    }
   hce = event->GetHCofThisEvent();
  //G4cout<<"hce:  "<<hce<<G4endl;
} 
 void CsIEventAction::EndOfEventAction(const G4Event* event)
 {
  // =============================================
  // Exercise 3
  // Print on screen the hits of the CsI
  // Step 1: Get the hits collection of this event
   
//Important: The code assumes you have called the two SDs: "/hodoscope1" and "/hodoscope2" and that they create a hit collection called "hodosopeColl". Change these if you have modified the names. 
//  G4cout<<"Is this THE error?"<<G4endl;
     hce = event->GetHCofThisEvent();
 // G4cout<<"Is this error?"<<G4endl;
  // G4cout<<"hce 2:  "<<hce<<G4endl; //hce 1 and 2 are the same, but they change each event, is this normal?
  if (!hce)
  {
    G4ExceptionDescription msg;
    msg << "No hits collection of this event found.\n";
    G4Exception("EventAction::EndOfEventAction()","Code001", JustWarning, msg);
    return;
  }
  // Step 2: Using the memorised IDs get the collections
  // corresponding to the two CsIs
  // Get hits collections
  CsIHitsCollection* hHC1 = static_cast<CsIHitsCollection*>(hce->GetHC(HCID));
  //should return a number instead of 0, should not return null 
  G4cout<<"hHC1: "<<hHC1<<G4endl;

  if ( (!hHC1))
  {
    G4ExceptionDescription msg;
    msg << "Some of hits collections of this event not found.\n";
    G4Exception("EventAction::EndOfEventAction()","Code002", JustWarning, msg);
    return;
  }
  //
  // Print diagnostics
  //
  G4int printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if ( printModulo==0 || event->GetEventID() % printModulo != 0) return;
 
  G4PrimaryParticle* primary = event->GetPrimaryVertex(0)->GetPrimary(0);
  G4cout << G4endl
    << ">>> Event " << event->GetEventID() << " >>> Simulation truth : "
    << primary->GetG4code()->GetParticleName()
    << " " << primary->GetMomentum() << G4endl;

  // Step 3: Loop on the one collections and dump on screen hits
  // CsI 1
  G4int n_hit = hHC1->entries();

  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance(); 
   analysisManager->FillH1(0, n_hit);
   G4double total_energy=0; 
   G4double kinetic_energy=0;
   G4double edep=0;
//  G4cout << "CsI  has " << n_hit << " hits." << G4endl;
  for (G4int i=0;i<n_hit;i++)
  {
    CsIHit* hit = (*hHC1)[i]; 
//bus error around there? 
    edep=hit->GetEdep();

    if (edep>0.)
       {
            
            total_energy += edep;
        }
    //G4cout<<"number of hits: "<<n_hit<<G4endl;
    //G4cout<<" i: "<< i<<G4endl;
    //hit->Print();
  } 
   analysisManager->FillNtupleDColumn(0, total_energy/keV);
   //analysisManager->FillNtupleIColumn(1, hHC1->entries());
   //G4cout<<"Kinetic EnergyCSIEventAction:     "<<total_energy/eV; 
   analysisManager->AddNtupleRow();  
//G4cout<<"Is this the error?"<<G4endl;
}
