
#ifndef CsIEventAction_h
#define CsIEventAction_h 1
#include "CsIHit.hh"

#include "G4UserEventAction.hh"
#include "G4Event.hh"

// import the singleton SD class to allow us access the hit collection
#include "G4SDManager.hh"

#include "G4Event.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"

class CsIEventAction : public G4UserEventAction
{

    public:
         CsIEventAction();
        virtual ~CsIEventAction();

    public:
       void BeginOfEventAction(const G4Event*);
       void EndOfEventAction(const G4Event*);

    private: 
        G4SDManager * pSDMan;
        G4HCofThisEvent* hce;
        CsIHitsCollection * HC;
        G4int HCID;


};
#endif 
