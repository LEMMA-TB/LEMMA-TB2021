#ifndef B1ActionInitialization_h
#define B1ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "globals.hh"
/// Action initialization class.

class B1ActionInitialization : public G4VUserActionInitialization
{
  public:
    B1ActionInitialization(G4bool MuonBeamFlag,G4bool ElectronBeamFlag);
    virtual ~B1ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
	
	private:
	G4bool fMuonBeamFlag;
	G4bool fElectronBeamFlag;
};


#endif

    
