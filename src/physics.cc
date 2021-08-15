#include "physics.hh"

// EM and optics are the most important physics in this simulation
// Radioactive decay is not included at the moment due to inefficeint implementation 
MyPhysicsList::MyPhysicsList(){
	RegisterPhysics ( new G4EmStandardPhysics() );
	RegisterPhysics ( new G4OpticalPhysics() );
}
MyPhysicsList::~MyPhysicsList(){}
