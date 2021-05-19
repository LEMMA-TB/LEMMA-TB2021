#include "B1EventAction.hh"
#include "B1Run.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "HistoManager.hh"
#include "B1SteppingAction.hh"
#include "B5Analysis.hh"
#include "B1RunAction.hh"

B1EventAction::B1EventAction(B1RunAction* runAction, const std::vector<G4int>  & TriggerLogic )
: G4UserEventAction(),
fRunAction(runAction),
fNHits(0),
fTriggerLogic(TriggerLogic)

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
	(fRunAction->GetCaloEnDep()).assign(30,0);
	
	(fRunAction->GetVectorCross()).clear();
	
	(fRunAction->GetVectorGammaConvX()).clear();
	(fRunAction->GetVectorGammaConvY()).clear();
	(fRunAction->GetVectorGammaConvZ()).clear();
	(fRunAction->GetVectorGammaConvEne()).clear();
	(fRunAction->GetVectorGammaConvSubdet()).clear();
	(fRunAction->GetVectorGammaConvEnePos()).clear();
	(fRunAction->GetVectorGammaConvEneEle()).clear();

	(fRunAction->GetXDig()).clear();
	(fRunAction->GetYDig()).clear();
	(fRunAction->GetZDig()).clear();
	(fRunAction->GetXErrDig()).clear();
	(fRunAction->GetYErrDig()).clear();
	(fRunAction->GetZErrDig()).clear();
	(fRunAction->GetDigSubdet()).clear();
	(fRunAction->GetDigHitIndex()).clear();
	
	
	(fRunAction->GetVectorPbGlass1EnterEne()).clear();
	(fRunAction->GetVectorPbGlass1EnterPart()).clear();
	(fRunAction->GetVectorPbGlass1EnterX()).clear();
	(fRunAction->GetVectorPbGlass1EnterY()).clear();
	(fRunAction->GetVectorPbGlass1EnterZ()).clear();
	(fRunAction->GetVectorPbGlass1EnterVX()).clear();
	(fRunAction->GetVectorPbGlass1EnterVY()).clear();
	(fRunAction->GetVectorPbGlass1EnterVZ()).clear();
	(fRunAction->GetVectorPbGlass1EnterPX()).clear();
	(fRunAction->GetVectorPbGlass1EnterPY()).clear();
	(fRunAction->GetVectorPbGlass1EnterPZ()).clear();
	
	(fRunAction->GetVectorPbGlass2EnterEne()).clear();
	(fRunAction->GetVectorPbGlass2EnterPart()).clear();
	(fRunAction->GetVectorPbGlass2EnterX()).clear();
	(fRunAction->GetVectorPbGlass2EnterY()).clear();
	(fRunAction->GetVectorPbGlass2EnterZ()).clear();
	(fRunAction->GetVectorPbGlass2EnterVX()).clear();
	(fRunAction->GetVectorPbGlass2EnterVY()).clear();
	(fRunAction->GetVectorPbGlass2EnterVZ()).clear();
	(fRunAction->GetVectorPbGlass2EnterPX()).clear();
	(fRunAction->GetVectorPbGlass2EnterPY()).clear();
	(fRunAction->GetVectorPbGlass2EnterPZ()).clear();
	
	(fRunAction->GetVectorPbGlassGEnterEne()).clear();
	(fRunAction->GetVectorPbGlassGEnterPart()).clear();
	(fRunAction->GetVectorPbGlassGEnterX()).clear();
	(fRunAction->GetVectorPbGlassGEnterY()).clear();
	(fRunAction->GetVectorPbGlassGEnterZ()).clear();
	(fRunAction->GetVectorPbGlassGEnterPX()).clear();
	(fRunAction->GetVectorPbGlassGEnterPY()).clear();
	(fRunAction->GetVectorPbGlassGEnterPZ()).clear();
	
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
	
	(fRunAction->GetVectorPbGlassGExitEne()).clear();
	(fRunAction->GetVectorPbGlassGExitPart()).clear();
	(fRunAction->GetVectorPbGlassGExitX()).clear();
	(fRunAction->GetVectorPbGlassGExitY()).clear();
	(fRunAction->GetVectorPbGlassGExitZ()).clear();
	(fRunAction->GetVectorPbGlassGExitPX()).clear();
	(fRunAction->GetVectorPbGlassGExitPY()).clear();
	(fRunAction->GetVectorPbGlassGExitPZ()).clear();

	(fRunAction->GetVectorDummy0EnterEne()).clear();
	(fRunAction->GetVectorDummy0EnterPart()).clear();
	(fRunAction->GetVectorDummy0EnterX()).clear();
	(fRunAction->GetVectorDummy0EnterY()).clear();
	(fRunAction->GetVectorDummy0EnterZ()).clear();
	(fRunAction->GetVectorDummy0EnterVX()).clear();
	(fRunAction->GetVectorDummy0EnterVY()).clear();
	(fRunAction->GetVectorDummy0EnterVZ()).clear();
	(fRunAction->GetVectorDummy0EnterPX()).clear();
	(fRunAction->GetVectorDummy0EnterPY()).clear();
	(fRunAction->GetVectorDummy0EnterPZ()).clear();
	
	(fRunAction->GetVectorDummy1EnterEne()).clear();
	(fRunAction->GetVectorDummy1EnterPart()).clear();
	(fRunAction->GetVectorDummy1EnterX()).clear();
	(fRunAction->GetVectorDummy1EnterY()).clear();
	(fRunAction->GetVectorDummy1EnterZ()).clear();
	(fRunAction->GetVectorDummy1EnterVX()).clear();
	(fRunAction->GetVectorDummy1EnterVY()).clear();
	(fRunAction->GetVectorDummy1EnterVZ()).clear();
	(fRunAction->GetVectorDummy1EnterPX()).clear();
	(fRunAction->GetVectorDummy1EnterPY()).clear();
	(fRunAction->GetVectorDummy1EnterPZ()).clear();

	(fRunAction->GetVectorDummy2EnterEne()).clear();
	(fRunAction->GetVectorDummy2EnterPart()).clear();
	(fRunAction->GetVectorDummy2EnterX()).clear();
	(fRunAction->GetVectorDummy2EnterY()).clear();
	(fRunAction->GetVectorDummy2EnterZ()).clear();
	(fRunAction->GetVectorDummy2EnterVX()).clear();
	(fRunAction->GetVectorDummy2EnterVY()).clear();
	(fRunAction->GetVectorDummy2EnterVZ()).clear();
	(fRunAction->GetVectorDummy2EnterPX()).clear();
	(fRunAction->GetVectorDummy2EnterPY()).clear();
	(fRunAction->GetVectorDummy2EnterPZ()).clear();
	
	(fRunAction->GetVectorCe1EnterEne()).clear();
	(fRunAction->GetVectorCe1EnterPart()).clear();
	(fRunAction->GetVectorCe1EnterX()).clear();
	(fRunAction->GetVectorCe1EnterY()).clear();
	(fRunAction->GetVectorCe1EnterZ()).clear();
	(fRunAction->GetVectorCe1EnterVX()).clear();
	(fRunAction->GetVectorCe1EnterVY()).clear();
	(fRunAction->GetVectorCe1EnterVZ()).clear();
	(fRunAction->GetVectorCe1EnterPX()).clear();
	(fRunAction->GetVectorCe1EnterPY()).clear();
	(fRunAction->GetVectorCe1EnterPZ()).clear();

	(fRunAction->GetVectorCe2EnterEne()).clear();
	(fRunAction->GetVectorCe2EnterPart()).clear();
	(fRunAction->GetVectorCe2EnterX()).clear();
	(fRunAction->GetVectorCe2EnterY()).clear();
	(fRunAction->GetVectorCe2EnterZ()).clear();
	(fRunAction->GetVectorCe2EnterVX()).clear();
	(fRunAction->GetVectorCe2EnterVY()).clear();
	(fRunAction->GetVectorCe2EnterVZ()).clear();
	(fRunAction->GetVectorCe2EnterPX()).clear();
	(fRunAction->GetVectorCe2EnterPY()).clear();
	(fRunAction->GetVectorCe2EnterPZ()).clear();
	
	(fRunAction->GetVectorS4EnterEne()).clear();
	(fRunAction->GetVectorS4EnterPart()).clear();
	(fRunAction->GetVectorS4EnterX()).clear();
	(fRunAction->GetVectorS4EnterY()).clear();
	(fRunAction->GetVectorS4EnterZ()).clear();
	(fRunAction->GetVectorS4EnterVX()).clear();
	(fRunAction->GetVectorS4EnterVY()).clear();
	(fRunAction->GetVectorS4EnterVZ()).clear();
	(fRunAction->GetVectorS4EnterPX()).clear();
	(fRunAction->GetVectorS4EnterPY()).clear();
	(fRunAction->GetVectorS4EnterPZ()).clear();
	
	(fRunAction->GetVectorS5EnterEne()).clear();
	(fRunAction->GetVectorS5EnterPart()).clear();
	(fRunAction->GetVectorS5EnterX()).clear();
	(fRunAction->GetVectorS5EnterY()).clear();
	(fRunAction->GetVectorS5EnterZ()).clear();
	(fRunAction->GetVectorS5EnterVX()).clear();
	(fRunAction->GetVectorS5EnterVY()).clear();
	(fRunAction->GetVectorS5EnterVZ()).clear();
	(fRunAction->GetVectorS5EnterPX()).clear();
	(fRunAction->GetVectorS5EnterPY()).clear();
	(fRunAction->GetVectorS5EnterPZ()).clear();
	
	(fRunAction->GetVectorS6EnterEne()).clear();
	(fRunAction->GetVectorS6EnterPart()).clear();
	(fRunAction->GetVectorS6EnterX()).clear();
	(fRunAction->GetVectorS6EnterY()).clear();
	(fRunAction->GetVectorS6EnterZ()).clear();
	(fRunAction->GetVectorS6EnterVX()).clear();
	(fRunAction->GetVectorS6EnterVY()).clear();
	(fRunAction->GetVectorS6EnterVZ()).clear();
	(fRunAction->GetVectorS6EnterPX()).clear();
	(fRunAction->GetVectorS6EnterPY()).clear();
	(fRunAction->GetVectorS6EnterPZ()).clear();
	
	(fRunAction->GetVectorS7EnterEne()).clear();
	(fRunAction->GetVectorS7EnterPart()).clear();
	(fRunAction->GetVectorS7EnterX()).clear();
	(fRunAction->GetVectorS7EnterY()).clear();
	(fRunAction->GetVectorS7EnterZ()).clear();
	(fRunAction->GetVectorS7EnterVX()).clear();
	(fRunAction->GetVectorS7EnterVY()).clear();
	(fRunAction->GetVectorS7EnterVZ()).clear();
	(fRunAction->GetVectorS7EnterPX()).clear();
	(fRunAction->GetVectorS7EnterPY()).clear();
	(fRunAction->GetVectorS7EnterPZ()).clear();

	(fRunAction->GetVectorT1EnterEne()).clear();
	(fRunAction->GetVectorT1EnterPart()).clear();
	(fRunAction->GetVectorT1EnterX()).clear();
	(fRunAction->GetVectorT1EnterY()).clear();
	(fRunAction->GetVectorT1EnterZ()).clear();
	(fRunAction->GetVectorT1EnterVX()).clear();
	(fRunAction->GetVectorT1EnterVY()).clear();
	(fRunAction->GetVectorT1EnterVZ()).clear();
	(fRunAction->GetVectorT1EnterPX()).clear();
	(fRunAction->GetVectorT1EnterPY()).clear();
	(fRunAction->GetVectorT1EnterPZ()).clear();

	(fRunAction->GetVectorT2EnterEne()).clear();
	(fRunAction->GetVectorT2EnterPart()).clear();
	(fRunAction->GetVectorT2EnterX()).clear();
	(fRunAction->GetVectorT2EnterY()).clear();
	(fRunAction->GetVectorT2EnterZ()).clear();
	(fRunAction->GetVectorT2EnterVX()).clear();
	(fRunAction->GetVectorT2EnterVY()).clear();
	(fRunAction->GetVectorT2EnterVZ()).clear();
	(fRunAction->GetVectorT2EnterPX()).clear();
	(fRunAction->GetVectorT2EnterPY()).clear();
	(fRunAction->GetVectorT2EnterPZ()).clear();

	(fRunAction->GetVectorT3EnterEne()).clear();
	(fRunAction->GetVectorT3EnterPart()).clear();
	(fRunAction->GetVectorT3EnterX()).clear();
	(fRunAction->GetVectorT3EnterY()).clear();
	(fRunAction->GetVectorT3EnterZ()).clear();
	(fRunAction->GetVectorT3EnterVX()).clear();
	(fRunAction->GetVectorT3EnterVY()).clear();
	(fRunAction->GetVectorT3EnterVZ()).clear();
	(fRunAction->GetVectorT3EnterPX()).clear();
	(fRunAction->GetVectorT3EnterPY()).clear();
	(fRunAction->GetVectorT3EnterPZ()).clear();

	(fRunAction->GetVectorT4EnterEne()).clear();
	(fRunAction->GetVectorT4EnterPart()).clear();
	(fRunAction->GetVectorT4EnterX()).clear();
	(fRunAction->GetVectorT4EnterY()).clear();
	(fRunAction->GetVectorT4EnterZ()).clear();
	(fRunAction->GetVectorT4EnterVX()).clear();
	(fRunAction->GetVectorT4EnterVY()).clear();
	(fRunAction->GetVectorT4EnterVZ()).clear();
	(fRunAction->GetVectorT4EnterPX()).clear();
	(fRunAction->GetVectorT4EnterPY()).clear();
	(fRunAction->GetVectorT4EnterPZ()).clear();

	(fRunAction->GetVectorT5EnterEne()).clear();
	(fRunAction->GetVectorT5EnterPart()).clear();
	(fRunAction->GetVectorT5EnterX()).clear();
	(fRunAction->GetVectorT5EnterY()).clear();
	(fRunAction->GetVectorT5EnterZ()).clear();
	(fRunAction->GetVectorT5EnterVX()).clear();
	(fRunAction->GetVectorT5EnterVY()).clear();
	(fRunAction->GetVectorT5EnterVZ()).clear();
	(fRunAction->GetVectorT5EnterPX()).clear();
	(fRunAction->GetVectorT5EnterPY()).clear();
	(fRunAction->GetVectorT5EnterPZ()).clear();
	
	(fRunAction->GetVectorT6EnterEne()).clear();
	(fRunAction->GetVectorT6EnterPart()).clear();
	(fRunAction->GetVectorT6EnterX()).clear();
	(fRunAction->GetVectorT6EnterY()).clear();
	(fRunAction->GetVectorT6EnterZ()).clear();
	(fRunAction->GetVectorT6EnterVX()).clear();
	(fRunAction->GetVectorT6EnterVY()).clear();
	(fRunAction->GetVectorT6EnterVZ()).clear();
	(fRunAction->GetVectorT6EnterPX()).clear();
	(fRunAction->GetVectorT6EnterPY()).clear();
	(fRunAction->GetVectorT6EnterPZ()).clear();

	(fRunAction->GetVectorMu1EnterEne()).clear();
	(fRunAction->GetVectorMu1EnterPart()).clear();
	(fRunAction->GetVectorMu1EnterX()).clear();
	(fRunAction->GetVectorMu1EnterY()).clear();
	(fRunAction->GetVectorMu1EnterZ()).clear();
	(fRunAction->GetVectorMu1EnterVX()).clear();
	(fRunAction->GetVectorMu1EnterVY()).clear();
	(fRunAction->GetVectorMu1EnterVZ()).clear();
	(fRunAction->GetVectorMu1EnterPX()).clear();
	(fRunAction->GetVectorMu1EnterPY()).clear();
	(fRunAction->GetVectorMu1EnterPZ()).clear();
	
	(fRunAction->GetVectorMu2EnterEne()).clear();
	(fRunAction->GetVectorMu2EnterPart()).clear();
	(fRunAction->GetVectorMu2EnterX()).clear();
	(fRunAction->GetVectorMu2EnterY()).clear();
	(fRunAction->GetVectorMu2EnterZ()).clear();
	(fRunAction->GetVectorMu2EnterVX()).clear();
	(fRunAction->GetVectorMu2EnterVY()).clear();
	(fRunAction->GetVectorMu2EnterVZ()).clear();
	(fRunAction->GetVectorMu2EnterPX()).clear();
	(fRunAction->GetVectorMu2EnterPY()).clear();
	(fRunAction->GetVectorMu2EnterPZ()).clear();
	
	(fRunAction->GetBeamInfoX()).clear();
	(fRunAction->GetBeamInfoY()).clear();
	(fRunAction->GetBeamInfoZ()).clear();
	(fRunAction->GetBeamInfoCX()).clear();
	(fRunAction->GetBeamInfoCY()).clear();
	(fRunAction->GetBeamInfoCZ()).clear();
	(fRunAction->GetBeamInfoEne()).clear();
	(fRunAction->GetBeamInfoPart()).clear();
	
	
	fNHits=0;
	fNoCriteria=fTriggerLogic.size();

	ResetShowCriteria();

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
	
	//	if ((1000/fPrintModulo*evtNb)%NevTot==0) G4cout <<"\n---> End of Event: "<<evt->GetEventID()<<G4endl;
	
	//	if (fShowCriteria1==TRUE && fShowCriteria2==TRUE && fShowCriteria3==TRUE) {
	//it = find(AllMothers.begin(), AllMothers.end(),temp);
	G4double somma=0;
	for (int ii=0; ii<fNoCriteria; ii++) somma+=fShowCriteria[ii];
	if (somma==fNoCriteria) {
	  G4Event* evt2 = G4EventManager::GetEventManager()->GetNonconstCurrentEvent();
	  evt2->KeepTheEvent();
	}
	
}


