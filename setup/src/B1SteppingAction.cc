#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"
#include "HistoManager.hh"
#include "B1RunAction.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4EventManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalVolumeStore.hh"

//---------------------------
#include "G4ProcessType.hh"
#include "G4OpticalPhoton.hh"

#define FLAG2018A


B1SteppingAction::B1SteppingAction(B1EventAction* eventAction, B1RunAction* runAction, G4bool StoreCaloEnDepFlag, G4bool StoreGammaConvDepFlag, G4double EThr, const std::map<G4int,G4int> & ChannelMap, G4bool DetEnterExitFlag, const std::vector<G4int>  & TriggerLogic)
: G4UserSteppingAction(),
fEventAction(eventAction),
runStepAction(runAction),
fScoringVolume_S1(0),
fScoringVolume_T1(0),
fScoringVolume_T2(0),
fScoringVolume_Targ(0),
fScoringVolume_C0(0),
fScoringVolume_C1(0),
fScoringVolume_C2(0),
fScoringVolume_C3(0),
fScoringVolume_C4(0),
fScoringVolume_C5(0),
fScoringVolume_C6(0),
fScoringVolume_C7(0),
fScoringVolume_S2(0),
fScoringVolume_S3(0),
fScoringVolume_S4(0),
fScoringVolume_S5(0),
fScoringVolume_S6(0),
fScoringVolume_S7(0),
fScoringVolume_Pb1a(0),
fScoringVolume_Pb1b(0),
fScoringVolume_Pb1c(0),
fScoringVolume_Pb2a(0),
fScoringVolume_Pb2b(0),
fScoringVolume_Pb2c(0),
fScoringVolume_PbG(0),
fScoringVolume_CeH(0),
fScoringVolume_CeV(0),
fScoringVolume_CeVtilt(0),
fScoringVolume_Mu1(0),
fScoringVolume_Mu2(0),
fStoreCaloEnDepFlag(StoreCaloEnDepFlag),
fStoreGammaConvDepFlag(StoreGammaConvDepFlag),
fEThr(EThr),
fChannelMap(ChannelMap),
fDetEnterExitFlag(DetEnterExitFlag),
fTriggerLogic(TriggerLogic)
{}


B1SteppingAction::~B1SteppingAction()
{}

void B1SteppingAction::UserSteppingAction(const G4Step* step){
	const G4double hplanck=4.136e-15; //eV*s
	const G4double clight=3e14; //um/s
	const G4double CerFotLambdaCut=0.2; //in [um], cut due to PMT sensitivity
	const B1DetectorConstruction* detectorConstruction = static_cast<const B1DetectorConstruction*>
	(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	if (!fScoringVolume_S1) {fScoringVolume_S1 = detectorConstruction->GetScoringVolume_S1();}
	if (!fScoringVolume_T1) {fScoringVolume_T1 = detectorConstruction->GetScoringVolume_T1();}
	if (!fScoringVolume_T2) {fScoringVolume_T2 = detectorConstruction->GetScoringVolume_T2();}
	if (!fScoringVolume_Targ) {fScoringVolume_Targ = detectorConstruction->GetScoringVolume_Targ();}
	if (!fScoringVolume_C0) {fScoringVolume_C0 = detectorConstruction->GetScoringVolume_C0();}
	if (!fScoringVolume_C1) {fScoringVolume_C1 = detectorConstruction->GetScoringVolume_C1();}
	if (!fScoringVolume_C2) {fScoringVolume_C2 = detectorConstruction->GetScoringVolume_C2();}
	if (!fScoringVolume_C3) {fScoringVolume_C3 = detectorConstruction->GetScoringVolume_C3();}
	if (!fScoringVolume_C4) {fScoringVolume_C4 = detectorConstruction->GetScoringVolume_C4();}
	if (!fScoringVolume_C5) {fScoringVolume_C5 = detectorConstruction->GetScoringVolume_C5();}
	if (!fScoringVolume_C6) {fScoringVolume_C6 = detectorConstruction->GetScoringVolume_C6();}
	if (!fScoringVolume_C7) {fScoringVolume_C7 = detectorConstruction->GetScoringVolume_C7();}
	if (!fScoringVolume_S2) {fScoringVolume_S2 = detectorConstruction->GetScoringVolume_S2();}
	if (!fScoringVolume_S3) {fScoringVolume_S3 = detectorConstruction->GetScoringVolume_S3();}
	if (!fScoringVolume_S4) {fScoringVolume_S4 = detectorConstruction->GetScoringVolume_S4();}
#ifndef FLAG2018A
		if (!fScoringVolume_S5) {fScoringVolume_S5 = detectorConstruction->GetScoringVolume_S5();}
		if (!fScoringVolume_S6) {fScoringVolume_S6 = detectorConstruction->GetScoringVolume_S6();}
		if (!fScoringVolume_S7) {fScoringVolume_S7 = detectorConstruction->GetScoringVolume_S7();}
	if (!fScoringVolume_CeH) {fScoringVolume_CeH = detectorConstruction->GetScoringVolume_CeH();}
	if (!fScoringVolume_CeVtilt) {fScoringVolume_CeVtilt = detectorConstruction->GetScoringVolume_CeVtilt();}
	if (!fScoringVolume_CeV) {fScoringVolume_CeV = detectorConstruction->GetScoringVolume_CeV();}
#endif
	if (!fScoringVolume_Pb1a) {fScoringVolume_Pb1a = detectorConstruction->GetScoringVolume_Pb1a();}
	if (!fScoringVolume_Pb1b) {fScoringVolume_Pb1b = detectorConstruction->GetScoringVolume_Pb1b();}
	if (!fScoringVolume_Pb1c) {fScoringVolume_Pb1c = detectorConstruction->GetScoringVolume_Pb1c();}
	if (!fScoringVolume_Pb2a) {fScoringVolume_Pb2a = detectorConstruction->GetScoringVolume_Pb2a();}
	if (!fScoringVolume_Pb2b) {fScoringVolume_Pb2b = detectorConstruction->GetScoringVolume_Pb2b();}
	if (!fScoringVolume_Pb2c) {fScoringVolume_Pb2c = detectorConstruction->GetScoringVolume_Pb2c();}
	if (!fScoringVolume_PbG) {fScoringVolume_PbG = detectorConstruction->GetScoringVolume_PbG();}

	if (!fScoringVolume_Mu1) {fScoringVolume_Mu1 = detectorConstruction->GetScoringVolume_Mu1();}
	if (!fScoringVolume_Mu2) {fScoringVolume_Mu2 = detectorConstruction->GetScoringVolume_Mu2();}
	
	
	G4LogicalVolume* volume =
	step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	
	G4VPhysicalVolume* ThisVol = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
	G4VPhysicalVolume* NextVol = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume();
	
	if (fDetEnterExitFlag) {
		// ########################
		// What enters PbGlass 1
		if (NextVol && ThisVol->GetName()=="CaloTable1" && ( NextVol->GetLogicalVolume()==fScoringVolume_Pb1a ||  NextVol->GetLogicalVolume()==fScoringVolume_Pb1b || NextVol->GetLogicalVolume()==fScoringVolume_Pb1c) ) {
			(runStepAction->GetVectorPbGlass1EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
			(runStepAction->GetVectorPbGlass1EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
			(runStepAction->GetVectorPbGlass1EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
			(runStepAction->GetVectorPbGlass1EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
			(runStepAction->GetVectorPbGlass1EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
			(runStepAction->GetVectorPbGlass1EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
			(runStepAction->GetVectorPbGlass1EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
			(runStepAction->GetVectorPbGlass1EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
			(runStepAction->GetVectorPbGlass1EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
			(runStepAction->GetVectorPbGlass1EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
			(runStepAction->GetVectorPbGlass1EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
		}
		
		// ########################
		// What enters PbGlass 2
		if (NextVol && ThisVol->GetName()=="CaloTable2" && ( NextVol->GetLogicalVolume()==fScoringVolume_Pb2a ||  NextVol->GetLogicalVolume()==fScoringVolume_Pb2b || NextVol->GetLogicalVolume()==fScoringVolume_Pb2c) ) {
			(runStepAction->GetVectorPbGlass2EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
			(runStepAction->GetVectorPbGlass2EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
			(runStepAction->GetVectorPbGlass2EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
			(runStepAction->GetVectorPbGlass2EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
			(runStepAction->GetVectorPbGlass2EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
			(runStepAction->GetVectorPbGlass2EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
			(runStepAction->GetVectorPbGlass2EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
			(runStepAction->GetVectorPbGlass2EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
			(runStepAction->GetVectorPbGlass2EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
			(runStepAction->GetVectorPbGlass2EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
			(runStepAction->GetVectorPbGlass2EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
		}
		
		// ########################
		// What enters PbGlassG
		if (NextVol && ThisVol->GetName()=="World" && ( NextVol->GetLogicalVolume()==fScoringVolume_PbG) ) {
			(runStepAction->GetVectorPbGlassGEnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
			(runStepAction->GetVectorPbGlassGEnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
			(runStepAction->GetVectorPbGlassGEnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
			(runStepAction->GetVectorPbGlassGEnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
			(runStepAction->GetVectorPbGlassGEnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
			(runStepAction->GetVectorPbGlassGEnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
			(runStepAction->GetVectorPbGlassGEnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
			(runStepAction->GetVectorPbGlassGEnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
		}
		
		// ########################
		// What exits PbGlass 1
		if (NextVol && NextVol->GetName()=="CaloTable1" && ( ThisVol->GetLogicalVolume()==fScoringVolume_Pb1a ||  NextVol->GetLogicalVolume()==fScoringVolume_Pb1b || NextVol->GetLogicalVolume()==fScoringVolume_Pb1c) ) {
			(runStepAction->GetVectorPbGlass1ExitEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
			(runStepAction->GetVectorPbGlass1ExitPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
			(runStepAction->GetVectorPbGlass1ExitX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
			(runStepAction->GetVectorPbGlass1ExitY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
			(runStepAction->GetVectorPbGlass1ExitZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
			(runStepAction->GetVectorPbGlass1ExitPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
			(runStepAction->GetVectorPbGlass1ExitPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
			(runStepAction->GetVectorPbGlass1ExitPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
		}
		
		// ########################
		// What exits PbGlass 2
		if (NextVol && NextVol->GetName()=="CaloTable2" && ( ThisVol->GetLogicalVolume()==fScoringVolume_Pb2a ||  NextVol->GetLogicalVolume()==fScoringVolume_Pb2b || NextVol->GetLogicalVolume()==fScoringVolume_Pb2c) ) {
			(runStepAction->GetVectorPbGlass2ExitEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
			(runStepAction->GetVectorPbGlass2ExitPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
			(runStepAction->GetVectorPbGlass2ExitX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
			(runStepAction->GetVectorPbGlass2ExitY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
			(runStepAction->GetVectorPbGlass2ExitZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
			(runStepAction->GetVectorPbGlass2ExitPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
			(runStepAction->GetVectorPbGlass2ExitPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
			(runStepAction->GetVectorPbGlass2ExitPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
		}
		
		// ########################
		// What exits PbGlassG
		if (NextVol && NextVol->GetName()=="World" && ( ThisVol->GetLogicalVolume()==fScoringVolume_PbG ) ) {
			(runStepAction->GetVectorPbGlassGExitEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
			(runStepAction->GetVectorPbGlassGExitPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
			(runStepAction->GetVectorPbGlassGExitX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
			(runStepAction->GetVectorPbGlassGExitY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
			(runStepAction->GetVectorPbGlassGExitZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
			(runStepAction->GetVectorPbGlassGExitPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
			(runStepAction->GetVectorPbGlassGExitPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
			(runStepAction->GetVectorPbGlassGExitPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
		}
		
		// ########################
		// What enters Dummy1
		if (NextVol && ThisVol->GetName()=="World" && ( NextVol->GetName()=="Dummy1") ) {
			(runStepAction->GetVectorDummy1EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
			(runStepAction->GetVectorDummy1EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
			(runStepAction->GetVectorDummy1EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
			(runStepAction->GetVectorDummy1EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
			(runStepAction->GetVectorDummy1EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
			(runStepAction->GetVectorDummy1EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
			(runStepAction->GetVectorDummy1EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
			(runStepAction->GetVectorDummy1EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
			(runStepAction->GetVectorDummy1EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
			(runStepAction->GetVectorDummy1EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
			(runStepAction->GetVectorDummy1EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
		}
		// What enters Dummy2
		if (NextVol && ThisVol->GetName()=="World" && ( NextVol->GetName()=="Dummy2") ) {
			(runStepAction->GetVectorDummy2EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
			(runStepAction->GetVectorDummy2EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
			(runStepAction->GetVectorDummy2EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
			(runStepAction->GetVectorDummy2EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
			(runStepAction->GetVectorDummy2EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
			(runStepAction->GetVectorDummy2EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
			(runStepAction->GetVectorDummy2EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
			(runStepAction->GetVectorDummy2EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
			(runStepAction->GetVectorDummy2EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
			(runStepAction->GetVectorDummy2EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
			(runStepAction->GetVectorDummy2EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
		}
		// What enters Ce1
		if (NextVol && ThisVol->GetName()=="CaloTable1" && ( NextVol->GetName()=="Ce1") ) {
			(runStepAction->GetVectorCe1EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
			(runStepAction->GetVectorCe1EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
			(runStepAction->GetVectorCe1EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
			(runStepAction->GetVectorCe1EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
			(runStepAction->GetVectorCe1EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
			(runStepAction->GetVectorCe1EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
			(runStepAction->GetVectorCe1EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
			(runStepAction->GetVectorCe1EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
			(runStepAction->GetVectorCe1EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
			(runStepAction->GetVectorCe1EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
			(runStepAction->GetVectorCe1EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
		}
		// What enters Ce2
		if (NextVol && ThisVol->GetName()=="CaloTable2" && ( NextVol->GetName()=="Ce2") ) {
			(runStepAction->GetVectorCe2EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
			(runStepAction->GetVectorCe2EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
			(runStepAction->GetVectorCe2EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
			(runStepAction->GetVectorCe2EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
			(runStepAction->GetVectorCe2EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
			(runStepAction->GetVectorCe2EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
			(runStepAction->GetVectorCe2EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
			(runStepAction->GetVectorCe2EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
			(runStepAction->GetVectorCe2EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
			(runStepAction->GetVectorCe2EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
			(runStepAction->GetVectorCe2EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
		}
		// What enters S4
		if (NextVol && ThisVol->GetName()=="World" && ( NextVol->GetName()=="S4") ) {
			(runStepAction->GetVectorS4EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
			(runStepAction->GetVectorS4EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
			(runStepAction->GetVectorS4EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
			(runStepAction->GetVectorS4EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
			(runStepAction->GetVectorS4EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
			(runStepAction->GetVectorS4EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
			(runStepAction->GetVectorS4EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
			(runStepAction->GetVectorS4EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
			(runStepAction->GetVectorS4EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
			(runStepAction->GetVectorS4EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
			(runStepAction->GetVectorS4EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
		}
		// What enters S5
		if (NextVol && ThisVol->GetName()=="World" && ( NextVol->GetName()=="S5") ) {
			(runStepAction->GetVectorS5EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
			(runStepAction->GetVectorS5EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
			(runStepAction->GetVectorS5EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
			(runStepAction->GetVectorS5EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
			(runStepAction->GetVectorS5EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
			(runStepAction->GetVectorS5EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
			(runStepAction->GetVectorS5EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
			(runStepAction->GetVectorS5EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
			(runStepAction->GetVectorS5EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
			(runStepAction->GetVectorS5EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
			(runStepAction->GetVectorS5EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
		}
		// What enters S6
		if (NextVol && ThisVol->GetName()=="World" && ( NextVol->GetName()=="S6") ) {
			(runStepAction->GetVectorS6EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
			(runStepAction->GetVectorS6EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
			(runStepAction->GetVectorS6EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
			(runStepAction->GetVectorS6EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
			(runStepAction->GetVectorS6EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
			(runStepAction->GetVectorS6EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
			(runStepAction->GetVectorS6EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
			(runStepAction->GetVectorS6EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
			(runStepAction->GetVectorS6EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
			(runStepAction->GetVectorS6EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
			(runStepAction->GetVectorS6EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
		}
		// What enters S7
		if (NextVol && ThisVol->GetName()=="World" && ( NextVol->GetName()=="S7") ) {
			(runStepAction->GetVectorS7EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
			(runStepAction->GetVectorS7EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
			(runStepAction->GetVectorS7EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
			(runStepAction->GetVectorS7EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
			(runStepAction->GetVectorS7EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
			(runStepAction->GetVectorS7EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
			(runStepAction->GetVectorS7EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
			(runStepAction->GetVectorS7EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
			(runStepAction->GetVectorS7EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
			(runStepAction->GetVectorS7EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
			(runStepAction->GetVectorS7EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
		}
		// What enters Mu1
		if (NextVol && ThisVol->GetName()=="World" && ( NextVol->GetName()=="Mu1") ) {
			(runStepAction->GetVectorMu1EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
			(runStepAction->GetVectorMu1EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
			(runStepAction->GetVectorMu1EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
			(runStepAction->GetVectorMu1EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
			(runStepAction->GetVectorMu1EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
			(runStepAction->GetVectorMu1EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
			(runStepAction->GetVectorMu1EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
			(runStepAction->GetVectorMu1EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
			(runStepAction->GetVectorMu1EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
			(runStepAction->GetVectorMu1EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
			(runStepAction->GetVectorMu1EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
			(runStepAction->GetVectorMu1EnterCopyNb()).push_back(step->GetPostStepPoint()->GetTouchableHandle()->GetCopyNumber());
		}
		// What enters Mu2
		if (NextVol && ThisVol->GetName()=="World" && ( NextVol->GetName()=="Mu2") ) {
			(runStepAction->GetVectorMu2EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
			(runStepAction->GetVectorMu2EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
			(runStepAction->GetVectorMu2EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
			(runStepAction->GetVectorMu2EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
			(runStepAction->GetVectorMu2EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
			(runStepAction->GetVectorMu2EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
			(runStepAction->GetVectorMu2EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
			(runStepAction->GetVectorMu2EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
			(runStepAction->GetVectorMu2EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
			(runStepAction->GetVectorMu2EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
			(runStepAction->GetVectorMu2EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
			(runStepAction->GetVectorMu2EnterCopyNb()).push_back(step->GetPostStepPoint()->GetTouchableHandle()->GetCopyNumber());
		}
	}

	// Were HORSA and VERSA flipped?
	B1DetectorConstruction* detectorConstructionNonConst = (B1DetectorConstruction*)
	(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
	
#ifndef FLAG2018A
	G4bool HorsaVersaFlip=detectorConstructionNonConst->GetHorsaVersaFlip();
#else
	G4bool HorsaVersaFlip=true;
#endif
	
	G4bool SHOW = false;
	G4bool dofill = false;
	G4int subdet=-10;
	if      (volume==fScoringVolume_S1) {subdet=9; dofill=true;}  //
	else if (volume==fScoringVolume_T1) {subdet=10; dofill=true;}  //
	else if (volume==fScoringVolume_T2)   {subdet=20; dofill=true;}  //
	else if (volume==fScoringVolume_Targ)   {subdet=25; dofill=true;}  //
	else if (volume==fScoringVolume_C0)   {subdet=30; dofill=true;}  //
	else if (volume==fScoringVolume_C1)   {subdet=31; dofill=true;}  //
	else if (volume==fScoringVolume_C2)   {subdet=32; dofill=true;}  //
	else if (volume==fScoringVolume_C3)   {subdet=33; dofill=true;}  //
	else if (volume==fScoringVolume_C4)   {subdet=34; dofill=true;}  //
	else if (volume==fScoringVolume_C5)   {subdet=35; dofill=true;}  //
	else if (volume==fScoringVolume_C6)   {subdet=36; dofill=true;}  //
	else if (volume==fScoringVolume_C7)   {subdet=37; dofill=true;}  //
	else if (volume==fScoringVolume_S2)   {subdet=38; dofill=true;}  //
	else if (volume==fScoringVolume_S3)   {subdet=39; dofill=true;}  //
	else if (volume==fScoringVolume_S4)   {subdet=63; dofill=true;}  //
	else if (volume==fScoringVolume_S5)   {subdet=64; dofill=true;}  //
	else if (volume==fScoringVolume_S6)   {subdet=65; dofill=true;}  //
	else if (volume==fScoringVolume_S7)   {subdet=66; dofill=true;}  //
	else if (volume==fScoringVolume_Pb1a)   {subdet=41; dofill=true;}  //
	else if (volume==fScoringVolume_Pb1b)   {subdet=42; dofill=true;}  //
	else if (volume==fScoringVolume_Pb1c)   {subdet=43; dofill=true;}  //
	else if (volume==fScoringVolume_Pb2a)   {subdet=44; dofill=true;}  //
	else if (volume==fScoringVolume_Pb2b)   {subdet=45; dofill=true;}  //
	else if (volume==fScoringVolume_Pb2c)   {subdet=46; dofill=true;}  //
	else if (volume==fScoringVolume_PbG)   {subdet=77; dofill=true;}  //
	else if (volume==fScoringVolume_CeVtilt && !HorsaVersaFlip)   {subdet=51; dofill=true;}  //
	else if (volume==fScoringVolume_CeV && !HorsaVersaFlip)   {subdet=51; dofill=true;}  //
	else if (volume==fScoringVolume_CeH && !HorsaVersaFlip)   {subdet=52; dofill=true;}  //
	else if (volume==fScoringVolume_CeVtilt && HorsaVersaFlip)   {subdet=52; dofill=true;}  //
	else if (volume==fScoringVolume_CeV && HorsaVersaFlip)   {subdet=52; dofill=true;}  //
	else if (volume==fScoringVolume_CeH && HorsaVersaFlip)   {subdet=51; dofill=true;}  //
	else if (volume==fScoringVolume_Mu1)   {subdet=61; dofill=true;}  //
	else if (volume==fScoringVolume_Mu2)   {subdet=62; dofill=true;}  //
	
	
	if (fStoreGammaConvDepFlag && NextVol) { //Like "subdet", but for PostStep volume
		G4LogicalVolume* Postvolume =	NextVol->GetLogicalVolume();
		G4int Postsubdet=0;
		if      (Postvolume==fScoringVolume_S1) {Postsubdet=9; }  //
		else if (Postvolume==fScoringVolume_T1) {Postsubdet=10; }  //
		else if (Postvolume==fScoringVolume_T2)   {Postsubdet=20; }  //
		else if (Postvolume==fScoringVolume_Targ)   {Postsubdet=25; }  //
		else if (Postvolume==fScoringVolume_C0)   {Postsubdet=30; }  //
		else if (Postvolume==fScoringVolume_C1)   {Postsubdet=31; }  //
		else if (Postvolume==fScoringVolume_C2)   {Postsubdet=32; }  //
		else if (Postvolume==fScoringVolume_C3)   {Postsubdet=33; }  //
		else if (Postvolume==fScoringVolume_C4)   {Postsubdet=34; }  //
		else if (Postvolume==fScoringVolume_C5)   {Postsubdet=35; }  //
		else if (Postvolume==fScoringVolume_C6)   {Postsubdet=36; }  //
		else if (Postvolume==fScoringVolume_C7)   {Postsubdet=37; }  //
		else if (Postvolume==fScoringVolume_S2)   {Postsubdet=38; }  //
		else if (Postvolume==fScoringVolume_S3)   {Postsubdet=39; }  //
		else if (Postvolume==fScoringVolume_S4)   {Postsubdet=63; }  //
		else if (Postvolume==fScoringVolume_S5)   {Postsubdet=64; }  //
		else if (Postvolume==fScoringVolume_S6)   {Postsubdet=65; }  //
		else if (Postvolume==fScoringVolume_S7)   {Postsubdet=66; }  //
		else if (Postvolume==fScoringVolume_Pb1a)   {Postsubdet=41; }  //
		else if (Postvolume==fScoringVolume_Pb1b)   {Postsubdet=42; }  //
		else if (Postvolume==fScoringVolume_Pb1c)   {Postsubdet=43; }  //
		else if (Postvolume==fScoringVolume_Pb2a)   {Postsubdet=44; }  //
		else if (Postvolume==fScoringVolume_Pb2b)   {Postsubdet=45; }  //
		else if (Postvolume==fScoringVolume_Pb2c)   {Postsubdet=46; }  //
		else if (Postvolume==fScoringVolume_PbG)   {Postsubdet=77; }  //
		else if (Postvolume==fScoringVolume_CeVtilt && !HorsaVersaFlip)   {Postsubdet=51; }  //
		else if (Postvolume==fScoringVolume_CeV && !HorsaVersaFlip)   {Postsubdet=51; }  //
		else if (Postvolume==fScoringVolume_CeH && !HorsaVersaFlip)   {Postsubdet=52; }  //
		else if (Postvolume==fScoringVolume_CeVtilt && HorsaVersaFlip)   {Postsubdet=52; }  //
		else if (Postvolume==fScoringVolume_CeV && HorsaVersaFlip)   {Postsubdet=52; }  //
		else if (Postvolume==fScoringVolume_CeH && HorsaVersaFlip)   {Postsubdet=51; }  //
		else if (Postvolume==fScoringVolume_Mu1)   {Postsubdet=61; }  //
		else if (Postvolume==fScoringVolume_Mu2)   {Postsubdet=62; }  //
		else if (Postvolume->GetName()=="World")   {Postsubdet=-10; }  //
		
		G4VPhysicalVolume* physicalBend = G4PhysicalVolumeStore::GetInstance()->GetVolume("Mag");
		G4double zGammaConvCut=physicalBend->GetTranslation().z();
		
		// If we have a Gamma Conversion before magnet...
		if (step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding()==22 && step->GetPostStepPoint()->GetProcessDefinedStep() && step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() == "conv" && step->GetPostStepPoint()->GetPosition().z()<zGammaConvCut) {
			
			(runStepAction->GetVectorGammaConvX()).push_back((step->GetPostStepPoint()->GetPosition().x()/cm));
			(runStepAction->GetVectorGammaConvY()).push_back((step->GetPostStepPoint()->GetPosition().y()/cm));
			(runStepAction->GetVectorGammaConvZ()).push_back((step->GetPostStepPoint()->GetPosition().z()/cm));
			(runStepAction->GetVectorGammaConvEne()).push_back((step->GetPreStepPoint()->GetKineticEnergy()/GeV));
			(runStepAction->GetVectorGammaConvSubdet()).push_back(Postsubdet);
			
			
			//			G4Event* evt = G4EventManager::GetEventManager()->GetNonconstCurrentEvent();
			//			evt->KeepTheEvent();
			//			G4cout<<"Evt n: "<< evt->GetEventID() <<" Gamma conversion in world! z= "<< step->GetPostStepPoint()->GetPosition().z()/cm<<" Gamma EnePre= "<<step->GetPreStepPoint()->GetKineticEnergy()/GeV <<" PostSubdet= "<<Postsubdet <<" Viva? "<<step->GetTrack()->GetTrackStatus() <<G4endl;
		}
	}
	
#if 0
	 if (subdet==61 && step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber()>3) {
	 G4Event* evt = G4EventManager::GetEventManager()->GetNonconstCurrentEvent();
	 evt->KeepTheEvent();
	 }

	if (subdet==64) {
		G4Event* evt = G4EventManager::GetEventManager()->GetNonconstCurrentEvent();
		evt->KeepTheEvent();
	}
#endif
	
	
	// ##############################################################################
	// ##################### TRIGGER LOGIC
	// ###############
#if 1
//	fEventAction->SetNoCriteria(6);
	for (int ii=0; ii<(int)fTriggerLogic.size(); ii++)
		if (subdet==fTriggerLogic[ii]) fEventAction->GetShowCriteria(ii)=1;
	
	/*
	if (subdet==63 ) fEventAction->GetShowCriteria(0)=1;
	if (subdet>=42 && subdet <=42) fEventAction->GetShowCriteria(1)=1;
	if (subdet>=45 && subdet <=45) fEventAction->GetShowCriteria(2)=1;
	if (subdet==51) fEventAction->GetShowCriteria(3)=1;
//	if (subdet==10) fEventAction->GetShowCriateria(4)=1;
	if (subdet==38) fEventAction->GetShowCriteria(4)=1;
	if (subdet==39) fEventAction->GetShowCriteria(5)=1;
*/
#endif
	/// ###############
	// ##############################################################################
	
	
	
	
	G4int CopyNb=step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();
	G4double DepEne=step->GetTotalEnergyDeposit()/GeV;
	G4int Pid=step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding();
	
	// ##############################################################################
	// ##################### CALORIMETER SCORING
	// ###############
	
	if (fStoreCaloEnDepFlag && ((subdet>=41 && subdet <=46) || subdet==51 || subdet==52 || subdet == 77)) {
//		std::vector<G4int>::iterator it;
		G4int CaloChannelToSearch=100*subdet+CopyNb;
		
		auto it = fChannelMap.find(CaloChannelToSearch);
		
//		it = find(fChannelMap.begin(), fChannelMap.end(),CaloChannelToSearch); //cerco l'attuale canale nella lista di quelli già visti
		if (it != fChannelMap.end()) { //se ho trovato il canale, scrivo il deposito energia nella posizione corrispondente del vettore
			(runStepAction->GetCaloEnDep())[it->second]+=DepEne;
	
			if (0 && (subdet==52 || subdet==51))		G4cout<<"DEBUG !!! subdet= "<<subdet<<" Nome= "<<step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName()<<" CopyNb="<<CopyNb<<" Cerco canale "<<CaloChannelToSearch<<" Trovato in pos= "<<it->second<<G4endl;
		}
	}
	
	/// ###############
	// ##############################################################################
	
	
	if (fEThr>0) fCutFlag=true;
	
	if (step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() == "Cerenkov") { //se sto facendo uno step di tipo cerenkov
																																													 //		G4cout<<"DEBUG Cerenkov!!!"<<G4endl;
		const std::vector<const G4Track*>* secondaries = step->GetSecondaryInCurrentStep();
		if (secondaries->size()>0) {
			for (unsigned int i=0; i<secondaries->size(); i++) { //ciclo su tutti i secondari di questo step
				if (secondaries->at(i)->GetDynamicParticle()->GetParticleDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) { //se è un fotone ottico
					if (secondaries->at(i)->GetCreatorProcess()->GetProcessName() == "Cerenkov") { //se è stato creato dal processo Cerenkov
						G4double CerFotEne=secondaries->at(i)->GetKineticEnergy()/eV;
						G4double CerFotLambda=hplanck*clight/CerFotEne;
						
						// se sono nel detector di PbGlass
						if (subdet==79 && CerFotLambda>0) {
							//							(fEventAction->AddPbGlassCere(1)); //incremento di 1 il contatore di fotoni cerenkov
						}
						// se sono nel detector di Cerenkov
						else if (subdet==80 && CerFotLambda>CerFotLambdaCut) {
							//							(runStepAction->GetCerenkovDepoOpt())[CopyNb]+=1; //incremento di 1 il contatore di fotoni cerenkov del rispettivo canale
						}
						//						G4cout<<"DEBUG Cerenkov!!! Energia fotone= "<<CerFotEne<<", lamda [um]= "<< CerFotLambda<<", subdet= "<<subdet<<  G4endl;
					}
				}
			}
		}
	}
	
	
	//##################################################
	//##################################################
	//############ CENTRAL CORE OF SCORING #############
	//##################################################
	
	
	//-- store info
	//	if (dofill && ((step->GetPostStepPoint()->GetStepStatus()==fGeomBoundary)
	//				   || (step->GetPreStepPoint()->GetStepStatus()==fGeomBoundary)) && !(Pid==22 && step->GetPreStepPoint()->GetMomentum().mag()<EThr) ) { //If Output Cut required do not store photons under a certain energy
	//#### NORMAL
	//	if (dofill && ((step->GetPostStepPoint()->GetStepStatus()==fGeomBoundary) || (step->GetPreStepPoint()->GetStepStatus()==fGeomBoundary)) && (!fCutFlag || !(Pid==22 && step->GetPreStepPoint()->GetMomentum().mag()<fEThr) )) { //If Output Cut required do not store photons under a certain energy - Logic expression: A & B & !(!C || !(D & E) )
	//### FINE NORMAL
	
	//	ALL
	//	if (dofill  && subdet!=76  && subdet!=77  && subdet!=78 && (!fCutFlag || !(Pid==22 && step->GetPreStepPoint()->GetMomentum().mag()<fEThr) )) { //If Output Cut required do not store photons under a certain energy - Logic expression: A & B & !(!C || !(D & E) )
	
	/* //tentativo di capire perchè quando si usa generatore esterno l'informazione in GetPrimaryVertex è sempre relativa alla prima riga del file di dati esterni.. PACE!
	 G4int temp=G4RunManager::GetRunManager()->GetCurrentEvent()->GetPrimaryVertex()->GetPrimary()->GetPDGcode();
	 G4double tempEne=G4RunManager::GetRunManager()->GetCurrentEvent()->GetPrimaryVertex()->GetPrimary()->GetKineticEnergy();
	 if (0&&temp!=13) G4cout<<"CIAO "<<temp<<G4endl;
	 
	 if (step->GetTrack()->GetParentID()==0 && step->GetTrack()->GetCurrentStepNumber()==1) G4cout<< "DEBUG ParentId="<< step->GetTrack()->GetParentID()<<" Part= "<<step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding()<<" Ene="<< step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/keV<<" temp= "<<temp<<" tempEne=" <<tempEne/keV<<G4endl;
	 */
	
	
	// SOLO PRE/POST - PRE
	if (dofill && (step->GetPreStepPoint()->GetStepStatus()==fGeomBoundary) && (!fCutFlag || !(Pid==22 && step->GetPreStepPoint()->GetMomentum().mag()<fEThr*GeV) )) { //If Output Cut required do not store photons under a certain energy - Logic expression: A & B & !(!C || !(D & E) )
		
		G4int iev = -999;
		const G4Event* evt = G4RunManager::GetRunManager()->GetCurrentEvent();
		if (evt) iev = evt->GetEventID();
		G4int Idp = step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding();
		G4int Ipar = step->GetTrack()->GetParentID();
		G4int Itrack = step->GetTrack()->GetTrackID();
		G4int Istep = step->GetTrack()->GetCurrentStepNumber();
		G4ThreeVector xsubdet = step->GetPreStepPoint()->GetPosition();
		G4double time = step->GetTrack()->GetGlobalTime()/ns;
		G4ThreeVector xvertex(0.,0.,0.);
		G4ThreeVector pvertexdir(0.,0.,0.);
		G4double kinev=0.;
		G4String process;
		G4int pro=0;
		//		G4int HitsCounter=0;
		fEventAction->AddNHits(1);
		
		G4ThreeVector momentum = step->GetPreStepPoint()->GetMomentum();
		G4double pmod = momentum.mag();
		G4int Inextstep=1;
		if (step->GetTrack()->GetTrackStatus()!=fAlive) Inextstep=0;
		
		pvertexdir = step->GetTrack()->GetVertexMomentumDirection();
		kinev = step->GetTrack()->GetVertexKineticEnergy();
		
		if (step->GetTrack()->GetCreatorProcess()) pro = step->GetTrack()->GetCreatorProcess()->GetProcessSubType();
		//			if (Itrack!=1) { // different from gun particle
		xvertex = step->GetTrack()->GetVertexPosition();
		
		
		G4PrimaryVertex* primaryVertex = evt->GetPrimaryVertex();
		G4PrimaryParticle* primaryParticle = primaryVertex->GetPrimary();
		G4double ke = primaryParticle->GetKineticEnergy();
		G4double xx = primaryVertex->GetPosition().x();
		G4double yy = primaryVertex->GetPosition().y();
		G4double zz = primaryVertex->GetPosition().z();
		G4double cx = primaryParticle->GetMomentumDirection().x();
		G4double cy = primaryParticle->GetMomentumDirection().y();
		G4double cz = primaryParticle->GetMomentumDirection().z();
		G4int particella=primaryParticle->GetPDGcode();
		
#if 1
		runStepAction->GetBeamX().push_back(xx/mm);
		runStepAction->GetBeamY().push_back(yy/mm);
		runStepAction->GetBeamZ().push_back(zz/mm);
		runStepAction->GetBeamCX().push_back(cx);
		runStepAction->GetBeamCY().push_back(cy);
		runStepAction->GetBeamCZ().push_back(cz);
		runStepAction->GetBeamEne().push_back(ke/GeV);
		runStepAction->GetBeamPart().push_back(particella);
#endif
		
		(runStepAction->GetSubdet()).push_back(subdet);
		
		(runStepAction->GetCopyNb()).push_back(CopyNb);
		
		(runStepAction->GetIdp()).push_back(Idp);
		(runStepAction->GetIpar()).push_back(Ipar);
		(runStepAction->GetItrack()).push_back(Itrack);
		(runStepAction->GetTime()).push_back(time);
		(runStepAction->GetVectorX()).push_back(xsubdet.x()/cm);
		(runStepAction->GetVectorY()).push_back(xsubdet.y()/cm);
		(runStepAction->GetVectorZ()).push_back(xsubdet.z()/cm);
		(runStepAction->GetVectorP()).push_back(momentum.mag()/GeV);
		(runStepAction->GetVectorPX()).push_back(momentum.x()/GeV);
		(runStepAction->GetVectorPY()).push_back(momentum.y()/GeV);
		(runStepAction->GetVectorPZ()).push_back(momentum.z()/GeV);
		(runStepAction->GetVertexX()).push_back(xvertex.x()/cm);
		(runStepAction->GetVertexY()).push_back(xvertex.y()/cm);
		(runStepAction->GetVertexZ()).push_back(xvertex.z()/cm);
		(runStepAction->GetKinev()).push_back(kinev/GeV);
		(runStepAction->GetVectorPXvdir()).push_back(pvertexdir.x()/GeV);
		(runStepAction->GetVectorPYvdir()).push_back(pvertexdir.y()/GeV);
		(runStepAction->GetVectorPZvdir()).push_back(pvertexdir.z()/GeV);
		(runStepAction->GetProcess()).push_back(pro);
		(runStepAction->GetIev()).push_back(iev);
		(runStepAction->GetStep()).push_back(Istep);
		(runStepAction->GetInextStep()).push_back(Inextstep);
		//		(runStepAction->GetNHits()).push_back(Inextstep);
		//		(runStepAction->GetItrack()).push_back(-999);
		
		
		if (step->GetPreStepPoint() && step->GetPreStepPoint()->GetStepStatus()==fGeomBoundary && step->GetPostStepPoint() && step->GetPostStepPoint()->GetStepStatus()!=fGeomBoundary) { //se la traccia NASCEVA sul bordo E NON ci moriva
			(runStepAction->GetVectorCross()).push_back(-1);
		} else	if (step->GetPostStepPoint() && step->GetPostStepPoint()->GetStepStatus()==fGeomBoundary && step->GetPreStepPoint() && step->GetPreStepPoint()->GetStepStatus()!=fGeomBoundary) { //se la traccia MORIVA sul bordo E NON ci nasceva
			(runStepAction->GetVectorCross()).push_back(1);
			//		} else 	{
			//			(runStepAction->GetVectorCross()).push_back(0);
		}else if (step->GetPreStepPoint() && step->GetPreStepPoint()->GetStepStatus()==fGeomBoundary && step->GetPostStepPoint() && step->GetPostStepPoint()->GetStepStatus()==fGeomBoundary) { //se la traccia NASCEVA sul bordo E CI MORIVA pure
			(runStepAction->GetVectorCross()).push_back(17);
			
		}
		
		
		if (SHOW) G4cout<<
			"  Evt="<<iev<<
			", IDtrack="<<Itrack<<
			", Idp="<<Idp<<
			", Ipar="<<Ipar<<
			", p="<<pmod<<
			", z="<<xsubdet[2]<<
			", subdet="<<subdet<<
			", vertex="<<xvertex[2]<<
			", process="<<process<<
			G4endl;
		/**/
	} //if(dofill)
	
	
}
