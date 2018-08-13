#include "B1EventAction.hh"
#include "B1Run.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "HistoManager.hh"
#include "B1SteppingAction.hh"
#include "B5Analysis.hh"
#include "B1RunAction.hh"

B1EventAction::B1EventAction(B1RunAction* runAction, G4int NOfCaloChannels)
: G4UserEventAction(),
fRunAction(runAction),
fNHits(0),
fNOfCaloChannels(NOfCaloChannels)
{} 

B1EventAction::~B1EventAction(){}

void B1EventAction::BeginOfEventAction(const G4Event* evt){    
	evtNb = evt->GetEventID();
	NevTot=G4RunManager::GetRunManager()->GetCurrentRun()->GetNumberOfEventToBeProcessed();
	if ((100/fPrintModulo*evtNb)%NevTot==0) G4cout <<"\n---> Begin of Event:"<<evtNb<<" of "<<NevTot<<" Progress % is "<<(100*evtNb)/NevTot<<G4endl;
	
	(fRunAction->GetBeamX()).clear();
	(fRunAction->GetBeamY()).clear();
	(fRunAction->GetBeamZ()).clear();
	(fRunAction->GetBeamCX()).clear();
	(fRunAction->GetBeamCY()).clear();
	(fRunAction->GetBeamCZ()).clear();
	(fRunAction->GetBeamEne()).clear();
	(fRunAction->GetBeamPart()).clear();
	
	(fRunAction->GetSubdet()).clear();
	(fRunAction->GetIdp()).clear();
	(fRunAction->GetIpar()).clear();
	(fRunAction->GetItrack()).clear();
	(fRunAction->GetTime()).clear();
	(fRunAction->GetVectorX()).clear();
	(fRunAction->GetVectorY()).clear();
	(fRunAction->GetVectorZ()).clear();
	(fRunAction->GetVectorP()).clear();
	(fRunAction->GetVectorPX()).clear();
	(fRunAction->GetVectorPY()).clear();
	(fRunAction->GetVectorPZ()).clear();
	(fRunAction->GetVertexX()).clear();
	(fRunAction->GetVertexY()).clear();
	(fRunAction->GetVertexZ()).clear();
	(fRunAction->GetKinev()).clear();
	(fRunAction->GetVectorPXvdir()).clear();
	(fRunAction->GetVectorPYvdir()).clear();
	(fRunAction->GetVectorPZvdir()).clear();
	(fRunAction->GetProcess()).clear();
	(fRunAction->GetIev()).clear();
	(fRunAction->GetStep()).clear();
	(fRunAction->GetInextStep()).clear();
	(fRunAction->GetCopyNb()).clear();
	
	(fRunAction->GetCaloEnDep()).clear();
	(fRunAction->GetCaloEnDep()).assign(fNOfCaloChannels,0);
	
	(fRunAction->GetVectorCross()).clear();
	
	(fRunAction->GetVectorGammaConvX()).clear();
	(fRunAction->GetVectorGammaConvY()).clear();
	(fRunAction->GetVectorGammaConvZ()).clear();
	(fRunAction->GetVectorGammaConvEne()).clear();
	(fRunAction->GetVectorGammaConvSubdet()).clear();
	(fRunAction->GetVectorGammaConvEnePos()).clear();
	(fRunAction->GetVectorGammaConvEneEle()).clear();
	
	
	
	(fRunAction->GetVectorPbGlass1EnterEne()).clear();
	(fRunAction->GetVectorPbGlass1EnterPart()).clear();
	(fRunAction->GetVectorPbGlass1EnterX()).clear();
	(fRunAction->GetVectorPbGlass1EnterY()).clear();
	(fRunAction->GetVectorPbGlass1EnterZ()).clear();
	(fRunAction->GetVectorPbGlass1EnterPX()).clear();
	(fRunAction->GetVectorPbGlass1EnterPY()).clear();
	(fRunAction->GetVectorPbGlass1EnterPZ()).clear();
	
	(fRunAction->GetVectorPbGlass2EnterEne()).clear();
	(fRunAction->GetVectorPbGlass2EnterPart()).clear();
	(fRunAction->GetVectorPbGlass2EnterX()).clear();
	(fRunAction->GetVectorPbGlass2EnterY()).clear();
	(fRunAction->GetVectorPbGlass2EnterZ()).clear();
	(fRunAction->GetVectorPbGlass2EnterPX()).clear();
	(fRunAction->GetVectorPbGlass2EnterPY()).clear();
	(fRunAction->GetVectorPbGlass2EnterPZ()).clear();
	
	(fRunAction->GetVectorPbGlass1ExitEne()).clear();
	(fRunAction->GetVectorPbGlass1ExitPart()).clear();
	(fRunAction->GetVectorPbGlass1ExitX()).clear();
	(fRunAction->GetVectorPbGlass1ExitY()).clear();
	(fRunAction->GetVectorPbGlass1ExitZ()).clear();
	(fRunAction->GetVectorPbGlass1ExitPX()).clear();
	(fRunAction->GetVectorPbGlass1ExitPY()).clear();
	(fRunAction->GetVectorPbGlass1ExitPZ()).clear();
	
	(fRunAction->GetVectorPbGlass2ExitEne()).clear();
	(fRunAction->GetVectorPbGlass2ExitPart()).clear();
	(fRunAction->GetVectorPbGlass2ExitX()).clear();
	(fRunAction->GetVectorPbGlass2ExitY()).clear();
	(fRunAction->GetVectorPbGlass2ExitZ()).clear();
	(fRunAction->GetVectorPbGlass2ExitPX()).clear();
	(fRunAction->GetVectorPbGlass2ExitPY()).clear();
	(fRunAction->GetVectorPbGlass2ExitPZ()).clear();
	
	
	(fRunAction->GetBeamInfoX()).clear();
	(fRunAction->GetBeamInfoY()).clear();
	(fRunAction->GetBeamInfoZ()).clear();
	(fRunAction->GetBeamInfoCX()).clear();
	(fRunAction->GetBeamInfoCY()).clear();
	(fRunAction->GetBeamInfoCZ()).clear();
	(fRunAction->GetBeamInfoEne()).clear();
	(fRunAction->GetBeamInfoPart()).clear();
	
	fNHits=0;
	
}

void B1EventAction::EndOfEventAction(const G4Event* evt){
	
	auto analysisManager = G4AnalysisManager::Instance();
	
	analysisManager->FillNtupleDColumn(0,8,fNHits);
	//	analysisManager->FillNtupleDColumn(0,34,fCerenkovEneTot);
	//	analysisManager->FillNtupleIColumn(0,37,fPbGlass_PulseHeight);
	//	analysisManager->FillNtupleDColumn(0,38,fPbGlass_DepEne);
	
	analysisManager->AddNtupleRow(0);
	analysisManager->AddNtupleRow(1);
	analysisManager->AddNtupleRow(2);
	analysisManager->AddNtupleRow(3);
	
	if ((100/fPrintModulo*evtNb)%NevTot==0) G4cout <<"\n---> End of Event: "<<evt->GetEventID()<<G4endl;
	
}


