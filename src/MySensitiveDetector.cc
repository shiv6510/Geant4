#include "MySensitiveDetector.hh"

// constructor
MySensitiveDetector::MySensitiveDetector(G4String name):G4VSensitiveDetector(name){}
// destructor
MySensitiveDetector::~MySensitiveDetector(){}

void MySensitiveDetector::Initialize(G4HCofThisEvent*){
	TotEnergy = 0;
	file.open("data.txt", std::ios::app);
}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *R0hist){
	/*
	G4Track *track = aStep->GetTrack();
	G4int trackID = track->GetTrackID();
	//track->SetTrackStatus(fStopAndKill);

	G4double energy = aStep->GetTotalEnergyDeposit();

	G4cout << energy << ",";
	*/
	//G4Track *track = aStep->GetTrack();
	//G4int trackID = track->GetTrackID();

	G4double energy = aStep->GetTotalEnergyDeposit();
	TotEnergy += energy;

	return true;
}

void MySensitiveDetector::EndOfEvent(G4HCofThisEvent*HCE){
	//G4cout << TotEnergy << G4endl;
	if (TotEnergy != 0){
		file << TotEnergy << G4endl;
		file.close();
	}
}
