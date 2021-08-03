#include "G4VHit.hh"

class Hit : public G4VHit{
	
	public:
		Hit(/* some arguments*/);
		virtual ~Hit();
		virtual void Draw();
		virtual void Print();
	
	private:
    // some data members

	
	public:
    // some get/set methods

};

#include "G4THitsCollection.hh"
typedef G4THitsCollection<Hit> SDHitCollection;
