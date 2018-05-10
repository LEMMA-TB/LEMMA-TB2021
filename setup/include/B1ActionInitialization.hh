#ifndef B1ActionInitialization_h
#define B1ActionInitialization_h 1

#include "G4VUserActionInitialization.hh"
#include "globals.hh"
/// Action initialization class.

class B1ActionInitialization : public G4VUserActionInitialization
{
  public:
    B1ActionInitialization(G4double BeamEnergy, G4bool CalibMuonBeamFlag, G4bool ProdMuonBeamFlag ,G4bool ElectronBeamFlag, G4bool SimpleFlag, G4bool StoreCaloEnDepFlag, G4bool ExtSourceFlagBha, G4bool ExtSourceFlagMu, G4double EThr);
    virtual ~B1ActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
	
	private:
	G4double fBeamEnergy;
	G4bool fCalibMuonBeamFlag;
	G4bool fProdMuonBeamFlag;
	G4bool fElectronBeamFlag;
	G4bool fSimpleFlag;
	G4bool fStoreCaloEnDepFlag;

	G4bool fExtSourceFlagBha;
	G4bool fExtSourceFlagMu;
	G4double fEThr;

};


#endif

    
