#include "B1RunAction.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1DetectorConstruction.hh"
#include "B1Run.hh"
#include "G4AccumulableManager.hh"
#include "HistoManager.hh"
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "time.h"
#include <sstream>

B1RunAction::B1RunAction(const std::map<G4int,G4int> & ChannelMap)
: G4UserRunAction(), fChannelMap(ChannelMap)
{}

B1RunAction::~B1RunAction(){}


G4Run* B1RunAction::GenerateRun(){
	return new B1Run;
}


void B1RunAction::BeginOfRunAction(const G4Run*){
	//inform the runManager to save random number seed
	G4RunManager::GetRunManager()->SetRandomNumberStore(false);
	
	G4AccumulableManager* accumulableManager = G4AccumulableManager::Instance();
	accumulableManager->Reset();
	
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	
	G4String filename = "LemmaMC";
	filename += ".root";
	
	analysisManager->OpenFile(filename);

	// ######### PHYSICS NTUPLE
	analysisManager->CreateNtuple("LEMMA", "LemmaMCNtuple");
	
	analysisManager->CreateNtupleDColumn(0,"BeamX", RunVectorBeamX);   //0
	analysisManager->CreateNtupleDColumn(0,"BeamY", RunVectorBeamY);   //1
	analysisManager->CreateNtupleDColumn(0,"BeamZ", RunVectorBeamZ);   //2
	analysisManager->CreateNtupleDColumn(0,"BeamCX", RunVectorBeamCX);   //3
	analysisManager->CreateNtupleDColumn(0,"BeamCY", RunVectorBeamCY);   //4
	analysisManager->CreateNtupleDColumn(0,"BeamCZ", RunVectorBeamCZ);   //5
	analysisManager->CreateNtupleDColumn(0,"BeamEne", RunVectorBeamEne);   //6
	analysisManager->CreateNtupleDColumn(0,"BeamPart", RunVectorBeamPart);   //7
	
	analysisManager->CreateNtupleDColumn(0,"nhits");   //8
	
	analysisManager->CreateNtupleDColumn(0,"subdet", RunVectorSubdet);
	analysisManager->CreateNtupleDColumn(0,"Idp", RunVectorIdp);
	analysisManager->CreateNtupleDColumn(0,"Ipar", RunVectorIpar);
	analysisManager->CreateNtupleDColumn(0,"itrack", RunVectorItrack);
	analysisManager->CreateNtupleDColumn(0,"Time", RunVectorTime);
	analysisManager->CreateNtupleDColumn(0,"xh", RunVectorX);
	analysisManager->CreateNtupleDColumn(0,"yh", RunVectorY);
	analysisManager->CreateNtupleDColumn(0,"zh", RunVectorZ);
	analysisManager->CreateNtupleDColumn(0,"P", RunVectorP);
	analysisManager->CreateNtupleDColumn(0,"PX", RunVectorPX);
	analysisManager->CreateNtupleDColumn(0,"PY", RunVectorPY);
	analysisManager->CreateNtupleDColumn(0,"PZ", RunVectorPZ);
	analysisManager->CreateNtupleDColumn(0,"VertexX", RunVectorVertexX);
	analysisManager->CreateNtupleDColumn(0,"VertexY", RunVectorVertexY);
	analysisManager->CreateNtupleDColumn(0,"VertexZ", RunVectorVertexZ);
	analysisManager->CreateNtupleDColumn(0,"Kinev", RunVectorKinev);
	analysisManager->CreateNtupleDColumn(0,"PXvdir", RunVectorPXvdir);
	analysisManager->CreateNtupleDColumn(0,"PYvdir", RunVectorPYvdir);
	analysisManager->CreateNtupleDColumn(0,"PZvdir", RunVectorPZvdir);
	analysisManager->CreateNtupleDColumn(0,"Iev", RunVectorIev);
	analysisManager->CreateNtupleDColumn(0,"Step", RunVectorStep);
	analysisManager->CreateNtupleDColumn(0,"InextStep", RunVectorInextStep);
	analysisManager->CreateNtupleDColumn(0,"CopyNb", RunVectorCopyNb);
	analysisManager->CreateNtupleDColumn(0,"Calo_EnDep", RunVectorCaloEnDep);
	analysisManager->CreateNtupleIColumn(0,"Proc", RunVectorProcess);
	analysisManager->CreateNtupleDColumn(0,"BCross", RunVectorCross);
	
	analysisManager->CreateNtupleDColumn(0,"GammaConvX", RunVectorGammaConvX);
	analysisManager->CreateNtupleDColumn(0,"GammaConvY", RunVectorGammaConvY);
	analysisManager->CreateNtupleDColumn(0,"GammaConvZ", RunVectorGammaConvZ);
	analysisManager->CreateNtupleDColumn(0,"GammaConvEne", RunVectorGammaConvEne);
	analysisManager->CreateNtupleDColumn(0,"GammaConvSubdet", RunVectorGammaConvSubdet);
	analysisManager->CreateNtupleDColumn(0,"GammaConvEnePos", RunVectorGammaConvEnePos);
	analysisManager->CreateNtupleDColumn(0,"GammaConvEneEle", RunVectorGammaConvEneEle);
	
	// ######### BEAM NTUPLE
	analysisManager->CreateNtuple("Beam", "SimulatedBeamInfo");
	
	analysisManager->CreateNtupleDColumn(1, "BeamX", BeamInfoX);   //0
	analysisManager->CreateNtupleDColumn(1, "BeamY", BeamInfoY);   //1
	analysisManager->CreateNtupleDColumn(1, "BeamZ", BeamInfoZ);   //2
	analysisManager->CreateNtupleDColumn(1, "BeamCX", BeamInfoCX);   //3
	analysisManager->CreateNtupleDColumn(1, "BeamCY", BeamInfoCY);   //4
	analysisManager->CreateNtupleDColumn(1, "BeamCZ", BeamInfoCZ);   //5
	analysisManager->CreateNtupleDColumn(1, "BeamEne", BeamInfoEne);   //6
	analysisManager->CreateNtupleDColumn(1, "BeamPart", BeamInfoPart);   //7
	
	// ######### DET ENTER NTUPLE
	analysisManager->CreateNtuple("DetEnter", "WhatEntersCalos");
	analysisManager->CreateNtupleDColumn(2,"PbGl1Ene", RunVectorPbGlass1EnterEne);
	analysisManager->CreateNtupleDColumn(2,"PbGl1Part", RunVectorPbGlass1EnterPart);
	analysisManager->CreateNtupleDColumn(2,"PbGl1X", RunVectorPbGlass1EnterX);
	analysisManager->CreateNtupleDColumn(2,"PbGl1Y", RunVectorPbGlass1EnterY);
	analysisManager->CreateNtupleDColumn(2,"PbGl1Z", RunVectorPbGlass1EnterZ);
	analysisManager->CreateNtupleDColumn(2,"PbGl1PX", RunVectorPbGlass1EnterPX);
	analysisManager->CreateNtupleDColumn(2,"PbGl1PY", RunVectorPbGlass1EnterPY);
	analysisManager->CreateNtupleDColumn(2,"PbGl1PZ", RunVectorPbGlass1EnterPZ);
	
	analysisManager->CreateNtupleDColumn(2,"PbGl2Ene", RunVectorPbGlass2EnterEne);
	analysisManager->CreateNtupleDColumn(2,"PbGl2Part", RunVectorPbGlass2EnterPart);
	analysisManager->CreateNtupleDColumn(2,"PbGl2X", RunVectorPbGlass2EnterX);
	analysisManager->CreateNtupleDColumn(2,"PbGl2Y", RunVectorPbGlass2EnterY);
	analysisManager->CreateNtupleDColumn(2,"PbGl2Z", RunVectorPbGlass2EnterZ);
	analysisManager->CreateNtupleDColumn(2,"PbGl2PX", RunVectorPbGlass2EnterPX);
	analysisManager->CreateNtupleDColumn(2,"PbGl2PY", RunVectorPbGlass2EnterPY);
	analysisManager->CreateNtupleDColumn(2,"PbGl2PZ", RunVectorPbGlass2EnterPZ);
	
	analysisManager->CreateNtupleDColumn(2,"PbGlGEne", RunVectorPbGlassGEnterEne);
	analysisManager->CreateNtupleDColumn(2,"PbGlGPart", RunVectorPbGlassGEnterPart);
	analysisManager->CreateNtupleDColumn(2,"PbGlGX", RunVectorPbGlassGEnterX);
	analysisManager->CreateNtupleDColumn(2,"PbGlGY", RunVectorPbGlassGEnterY);
	analysisManager->CreateNtupleDColumn(2,"PbGlGZ", RunVectorPbGlassGEnterZ);
	analysisManager->CreateNtupleDColumn(2,"PbGlGPX", RunVectorPbGlassGEnterPX);
	analysisManager->CreateNtupleDColumn(2,"PbGlGPY", RunVectorPbGlassGEnterPY);
	analysisManager->CreateNtupleDColumn(2,"PbGlGPZ", RunVectorPbGlassGEnterPZ);
	
	// ######### DET EXIT NTUPLE
	analysisManager->CreateNtuple("DetExit", "WhatExitsCalos");
	analysisManager->CreateNtupleDColumn(3,"PbGl1Ene", RunVectorPbGlass1ExitEne);
	analysisManager->CreateNtupleDColumn(3,"PbGl1Part", RunVectorPbGlass1ExitPart);
	analysisManager->CreateNtupleDColumn(3,"PbGl1X", RunVectorPbGlass1ExitX);
	analysisManager->CreateNtupleDColumn(3,"PbGl1Y", RunVectorPbGlass1ExitY);
	analysisManager->CreateNtupleDColumn(3,"PbGl1Z", RunVectorPbGlass1ExitZ);
	analysisManager->CreateNtupleDColumn(3,"PbGl1PX", RunVectorPbGlass1ExitPX);
	analysisManager->CreateNtupleDColumn(3,"PbGl1PY", RunVectorPbGlass1ExitPY);
	analysisManager->CreateNtupleDColumn(3,"PbGl1PZ", RunVectorPbGlass1ExitPZ);
	
	analysisManager->CreateNtupleDColumn(3,"PbGl2Ene", RunVectorPbGlass2ExitEne);
	analysisManager->CreateNtupleDColumn(3,"PbGl2Part", RunVectorPbGlass2ExitPart);
	analysisManager->CreateNtupleDColumn(3,"PbGl2X", RunVectorPbGlass2ExitX);
	analysisManager->CreateNtupleDColumn(3,"PbGl2Y", RunVectorPbGlass2ExitY);
	analysisManager->CreateNtupleDColumn(3,"PbGl2Z", RunVectorPbGlass2ExitZ);
	analysisManager->CreateNtupleDColumn(3,"PbGl2PX", RunVectorPbGlass2ExitPX);
	analysisManager->CreateNtupleDColumn(3,"PbGl2PY", RunVectorPbGlass2ExitPY);
	analysisManager->CreateNtupleDColumn(3,"PbGl2PZ", RunVectorPbGlass2ExitPZ);

	analysisManager->CreateNtupleDColumn(3,"PbGlGEne", RunVectorPbGlassGExitEne);
	analysisManager->CreateNtupleDColumn(3,"PbGlGPart", RunVectorPbGlassGExitPart);
	analysisManager->CreateNtupleDColumn(3,"PbGlGX", RunVectorPbGlassGExitX);
	analysisManager->CreateNtupleDColumn(3,"PbGlGY", RunVectorPbGlassGExitY);
	analysisManager->CreateNtupleDColumn(3,"PbGlGZ", RunVectorPbGlassGExitZ);
	analysisManager->CreateNtupleDColumn(3,"PbGlGPX", RunVectorPbGlassGExitPX);
	analysisManager->CreateNtupleDColumn(3,"PbGlGPY", RunVectorPbGlassGExitPY);
	analysisManager->CreateNtupleDColumn(3,"PbGlGPZ", RunVectorPbGlassGExitPZ);
	
	// ######### FINISH NTUPLEs
	analysisManager->FinishNtuple(0);
	analysisManager->FinishNtuple(1);
	analysisManager->FinishNtuple(2);
	analysisManager->FinishNtuple(3);
	
	// ######### CREATE CALOMAP HISTO
	analysisManager->CreateH1("CaloMap","CaloMap",fChannelMap.size(),0.,fChannelMap.size());
	analysisManager->SetH1XAxisTitle(0,"Channel");
	analysisManager->SetH1YAxisTitle(0,"Detector-SubDet");
	
	for (int ii=0; ii<(int)fChannelMap.size() && G4Threading::G4GetThreadId()==-1; ii++) { //write CaloMap histo only once if MT to avoid problems
//		analysisManager->FillH1(0, ii, fChannelMap[ii]);
	}
}

void B1RunAction::EndOfRunAction(const G4Run* run){
	
	G4int nofEvents = run->GetNumberOfEvent();
	if (nofEvents == 0) return;
	
	//save histograms
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->Write();
	analysisManager->CloseFile();
	
}

