#include "B1ActionInitialization.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1RunAction.hh"
#include "B1EventAction.hh"
#include "B1SteppingAction.hh"
#include "B1StackingAction.hh"

B1ActionInitialization::B1ActionInitialization(G4double BeamEnergy, G4bool CalibMuonBeamFlag, G4bool ProdMuonBeamFlag, G4bool ElectronBeamFlag, G4bool SimpleFlag, G4bool StoreCaloEnDepFlag, G4bool ExtSourceFlagBha, G4bool ExtSourceFlagMu, G4double EThr)
: G4VUserActionInitialization(), fBeamEnergy(BeamEnergy), fCalibMuonBeamFlag(CalibMuonBeamFlag),fProdMuonBeamFlag(ProdMuonBeamFlag), fElectronBeamFlag(ElectronBeamFlag), fSimpleFlag(SimpleFlag), fStoreCaloEnDepFlag(StoreCaloEnDepFlag), fExtSourceFlagBha(ExtSourceFlagBha), fExtSourceFlagMu(ExtSourceFlagMu), fEThr(EThr)
{

}


B1ActionInitialization::~B1ActionInitialization()
{}


void B1ActionInitialization::BuildForMaster() const
{
	SetUserAction(new B1RunAction);
}

void B1ActionInitialization::Build() const
{
//	SetUserAction(new B1RunAction);
	B1RunAction* runAction = new B1RunAction;
//	runAction = new B1RunAction();
//	frunAction=runAction;
	SetUserAction(runAction);
	
	B1EventAction* eventAction = new B1EventAction(runAction);
	SetUserAction(new B1PrimaryGeneratorAction(fBeamEnergy, fCalibMuonBeamFlag, fProdMuonBeamFlag, fElectronBeamFlag, fSimpleFlag, fExtSourceFlagBha, fExtSourceFlagMu));
	SetUserAction(eventAction);
	SetUserAction(new B1SteppingAction(eventAction, runAction, fStoreCaloEnDepFlag, fEThr));
	SetUserAction(new B1StackingAction(eventAction, runAction));
}

