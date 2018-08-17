#ifndef B1ActionInitialization_h
#define B1ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "globals.hh"
#include "B1RunAction.hh"
#include <vector>

/// Action initialization class.

class B1ActionInitialization : public G4VUserActionInitialization
{
public:
	B1ActionInitialization(G4double BeamEnergy,G4double BeamDP, G4bool CalibMuMBeamFlag, G4bool CalibMuPBeamFlag, G4bool ProdMuonBeamFlag ,G4bool ElectronBeamFlag, G4bool SimpleFlag, G4bool StoreCaloEnDepFlag, G4bool StoreGammaConvFlag, G4bool ExtSourceFlagBha, G4bool ExtSourceFlagMu, G4double EThr, std::vector<G4int> & ChannelMap, G4bool fDetEnterExitFlag);
	virtual ~B1ActionInitialization();
	
	virtual void BuildForMaster() const;
	virtual void Build() const;
	
private:
	G4double fBeamEnergy;
	G4double fBeamDP;
	G4bool fCalibMuMBeamFlag;
	G4bool fCalibMuPBeamFlag;
	G4bool fProdMuonBeamFlag;
	G4bool fElectronBeamFlag;
	G4bool fSimpleFlag;
	G4bool fStoreCaloEnDepFlag;
	G4bool fStoreGammaConvDepFlag;

	G4bool fExtSourceFlagBha;
	G4bool fExtSourceFlagMu;
	G4double fEThr;
	G4bool fDetEnterExitFlag;
	
public:
	std::vector<G4int> fChannelMap;

};

#endif
