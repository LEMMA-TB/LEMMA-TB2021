#ifndef B1PrimaryGeneratorAction_h
#define B1PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include "B1EventAction.hh"



class G4ParticleGun;
class G4Event;
class G4Box;

class B1PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
	B1PrimaryGeneratorAction(G4double BeamEnergy, G4bool CalibMuonBeamFlag, G4bool ProdMuonBeamFlag, G4bool ElectronBeamFlag, G4bool SimpleFlag, G4bool ExtSourceFlagBha, G4bool ExtSourceFlagMu);
	virtual ~B1PrimaryGeneratorAction();
	
	// method from the base class
	virtual void GeneratePrimaries(G4Event*);
	
	// method to access particle gun
	const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
	
private:
	G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
//	G4Box* fEnvelopeBox;
//	B1EventAction* evtPrimAction;
	G4double fBeamEnergy;
	G4bool fCalibMuonBeamFlag;
	G4bool fProdMuonBeamFlag;
	G4bool fElectronBeamFlag;
	G4bool fSimpleFlag;
	G4bool fExtSourceFlagBha;
	G4bool fExtSourceFlagMu;

	G4VPrimaryGenerator* hepmcAscii;
	
};

#endif


