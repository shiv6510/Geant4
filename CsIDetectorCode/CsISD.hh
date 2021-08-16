#ifndef CsISD_h
#define CsISD_h 1

#include "G4VSensitiveDetector.hh"
#include "CsIHit.hh"
#include "G4SDManager.hh"

// packages for units
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"
class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;
class CsISD : public G4VSensitiveDetector{

	public: 
		CsISD(G4String name);
		virtual ~CsISD();
                
		
	private:
                virtual void Initialize(G4HCofThisEvent*HCE);
                virtual G4bool ProcessHits(G4Step*aStep, G4TouchableHistory*ROhist);
                CsIHitsCollection *fHitsCollection;
                G4SDManager * pSDMan;
                 G4int HCID; 
                 G4int total_hits;
                 G4int id;
};

#endif

