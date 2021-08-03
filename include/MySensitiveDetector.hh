#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include <fstream>

//class G4Step;
//class G4HCofThisEvent;
class MySensitiveDetector : public G4VSensitiveDetector{

	public: 
		MySensitiveDetector(G4String);
		~MySensitiveDetector();
		virtual void Initialize(G4HCofThisEvent*);
		virtual void EndOfEvent(G4HCofThisEvent*);
		
	private:
		virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
		G4double TotEnergy = 0;
		std::ofstream file;
};

#endif

