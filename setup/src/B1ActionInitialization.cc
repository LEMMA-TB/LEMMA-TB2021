#include "B1ActionInitialization.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1RunAction.hh"
#include "B1EventAction.hh"
#include "B1SteppingAction.hh"
#include "B1StackingAction.hh"
#include <vector>

B1ActionInitialization::B1ActionInitialization(G4double BeamEnergy,G4double BeamDP, G4bool CalibMuMBeamFlag, G4bool CalibMuPBeamFlag, G4bool ProdMuonBeamFlag, G4bool ElectronBeamFlag, G4bool SimpleFlag, G4bool StoreCaloEnDepFlag, G4bool StoreGammaConvDepFlag, G4bool ExtSourceFlagBha, G4bool ExtSourceFlagMu, G4double EThr, std::map<G4int,G4int> & ChannelMap, G4bool DetEnterExitFlag, G4int NTotChannels, std::vector<G4int> & TriggerLogic,  G4int TargMat, G4double TargDZ, G4bool Aug2018Flag)
: G4VUserActionInitialization(), fBeamEnergy(BeamEnergy),fBeamDP(BeamDP), fCalibMuMBeamFlag(CalibMuMBeamFlag),fCalibMuPBeamFlag(CalibMuPBeamFlag),fProdMuonBeamFlag(ProdMuonBeamFlag), fElectronBeamFlag(ElectronBeamFlag), fSimpleFlag(SimpleFlag), fStoreCaloEnDepFlag(StoreCaloEnDepFlag), fStoreGammaConvDepFlag(StoreGammaConvDepFlag), fExtSourceFlagBha(ExtSourceFlagBha), fExtSourceFlagMu(ExtSourceFlagMu), fEThr(EThr),fDetEnterExitFlag(DetEnterExitFlag) , fNTotChannels(NTotChannels), fTargMat(TargMat), fTargDZ(TargDZ), fAug2018Flag(Aug2018Flag), fChannelMap(ChannelMap), fTriggerLogic(TriggerLogic)
{
}

B1ActionInitialization::~B1ActionInitialization()
{}

void B1ActionInitialization::BuildForMaster() const
{
	SetUserAction(new B1RunAction(fChannelMap));
}

void B1ActionInitialization::Build() const
{
	B1RunAction* runAction = new B1RunAction(fChannelMap);
	SetUserAction(runAction);
	
	B1EventAction* eventAction = new B1EventAction(runAction, fNTotChannels, fTriggerLogic);
	SetUserAction(new B1PrimaryGeneratorAction(fBeamEnergy, fBeamDP, fCalibMuMBeamFlag, fCalibMuPBeamFlag, fProdMuonBeamFlag, fElectronBeamFlag, fSimpleFlag, fExtSourceFlagBha, fExtSourceFlagMu, fTargMat, fTargDZ));
	SetUserAction(eventAction);
	SetUserAction(new B1SteppingAction(eventAction, runAction, fStoreCaloEnDepFlag, fStoreGammaConvDepFlag, fEThr, fChannelMap, fDetEnterExitFlag, fTriggerLogic, fAug2018Flag));
	SetUserAction(new B1StackingAction(eventAction, runAction, fStoreGammaConvDepFlag));
}

