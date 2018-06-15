#include "B1EventAction.hh"
#include "B1Run.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "HistoManager.hh"
#include "B1SteppingAction.hh"
#include "B5Analysis.hh"
#include "B1RunAction.hh"

B1EventAction::B1EventAction(B1RunAction* runAction)
  : G4UserEventAction(),
fRunAction(runAction),
fNHits(0)
{} 

B1EventAction::~B1EventAction(){}


void B1EventAction::BeginOfEventAction(const G4Event* evt){    
  G4int fPrintModulo = 1;
  evtNb = evt->GetEventID();
  if (evtNb%fPrintModulo == 0) G4cout <<"\n---> Begin of Event:"<<evtNb<<G4endl; 
  // G4cout<<"\n---> Begin of Event +++++++++++++++ === >>>>  :"<<evtNb<<G4endl;
	
	//Initialize Primaries Info to 0

	
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
	(fRunAction->GetCaloEnDep()).assign(18,0);
	
	(fRunAction->GetVectorCross()).clear();

	
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

void B1EventAction::EndOfEventAction(const G4Event*){
	
	auto analysisManager = G4AnalysisManager::Instance();

	analysisManager->FillNtupleDColumn(0,8,fNHits);
//	analysisManager->FillNtupleDColumn(0,34,fCerenkovEneTot);

//	analysisManager->FillNtupleIColumn(0,37,fPbGlass_PulseHeight);
//	analysisManager->FillNtupleDColumn(0,38,fPbGlass_DepEne);

	
	
	analysisManager->AddNtupleRow(0);
	analysisManager->AddNtupleRow(1);

	G4cout <<"\n---> End of Event:"<<G4endl;
	
}


