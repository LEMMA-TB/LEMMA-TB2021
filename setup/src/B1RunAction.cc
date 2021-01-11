#include "B1RunAction.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1DetectorConstruction.hh"
#include "B1DetectorConstructionAug.hh"
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
#include <map>

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
	analysisManager->CreateNtupleDColumn(0,"xhit", RunVectorX);
	analysisManager->CreateNtupleDColumn(0,"yhit", RunVectorY);
	analysisManager->CreateNtupleDColumn(0,"zhit", RunVectorZ);
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

	/// digit variables (dimension can be different from the one of the hits )
	analysisManager->CreateNtupleDColumn(0,"xDig",RunVectorXDig);
	analysisManager->CreateNtupleDColumn(0,"yDig",RunVectorYDig);
	analysisManager->CreateNtupleDColumn(0,"zDig",RunVectorZDig);
	analysisManager->CreateNtupleDColumn(0,"xErrDig",RunVectorXErrDig);
	analysisManager->CreateNtupleDColumn(0,"yErrDig",RunVectorYErrDig);
	analysisManager->CreateNtupleDColumn(0,"zErrDig",RunVectorZErrDig);
	analysisManager->CreateNtupleIColumn(0,"digHitIndex",RunVectorDigHitIndex);
	
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
	analysisManager->CreateNtupleDColumn(2,"PbGl1VX", RunVectorPbGlass1EnterVX);
	analysisManager->CreateNtupleDColumn(2,"PbGl1VY", RunVectorPbGlass1EnterVY);
	analysisManager->CreateNtupleDColumn(2,"PbGl1VZ", RunVectorPbGlass1EnterVZ);
	analysisManager->CreateNtupleDColumn(2,"PbGl1PX", RunVectorPbGlass1EnterPX);
	analysisManager->CreateNtupleDColumn(2,"PbGl1PY", RunVectorPbGlass1EnterPY);
	analysisManager->CreateNtupleDColumn(2,"PbGl1PZ", RunVectorPbGlass1EnterPZ);
	
	analysisManager->CreateNtupleDColumn(2,"PbGl2Ene", RunVectorPbGlass2EnterEne);
	analysisManager->CreateNtupleDColumn(2,"PbGl2Part", RunVectorPbGlass2EnterPart);
	analysisManager->CreateNtupleDColumn(2,"PbGl2X", RunVectorPbGlass2EnterX);
	analysisManager->CreateNtupleDColumn(2,"PbGl2Y", RunVectorPbGlass2EnterY);
	analysisManager->CreateNtupleDColumn(2,"PbGl2Z", RunVectorPbGlass2EnterZ);
	analysisManager->CreateNtupleDColumn(2,"PbGl2VX", RunVectorPbGlass2EnterVX);
	analysisManager->CreateNtupleDColumn(2,"PbGl2VY", RunVectorPbGlass2EnterVY);
	analysisManager->CreateNtupleDColumn(2,"PbGl2VZ", RunVectorPbGlass2EnterVZ);
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
	
	analysisManager->CreateNtupleDColumn(2,"Ce1Ene", RunVectorCe1EnterEne);
	analysisManager->CreateNtupleDColumn(2,"Ce1Part", RunVectorCe1EnterPart);
	analysisManager->CreateNtupleDColumn(2,"Ce1X", RunVectorCe1EnterX);
	analysisManager->CreateNtupleDColumn(2,"Ce1Y", RunVectorCe1EnterY);
	analysisManager->CreateNtupleDColumn(2,"Ce1Z", RunVectorCe1EnterZ);
	analysisManager->CreateNtupleDColumn(2,"Ce1VX", RunVectorCe1EnterVX);
	analysisManager->CreateNtupleDColumn(2,"Ce1VY", RunVectorCe1EnterVY);
	analysisManager->CreateNtupleDColumn(2,"Ce1VZ", RunVectorCe1EnterVZ);
	analysisManager->CreateNtupleDColumn(2,"Ce1PX", RunVectorCe1EnterPX);
	analysisManager->CreateNtupleDColumn(2,"Ce1PY", RunVectorCe1EnterPY);
	analysisManager->CreateNtupleDColumn(2,"Ce1PZ", RunVectorCe1EnterPZ);

	analysisManager->CreateNtupleDColumn(2,"Ce2Ene", RunVectorCe2EnterEne);
	analysisManager->CreateNtupleDColumn(2,"Ce2Part", RunVectorCe2EnterPart);
	analysisManager->CreateNtupleDColumn(2,"Ce2X", RunVectorCe2EnterX);
	analysisManager->CreateNtupleDColumn(2,"Ce2Y", RunVectorCe2EnterY);
	analysisManager->CreateNtupleDColumn(2,"Ce2Z", RunVectorCe2EnterZ);
	analysisManager->CreateNtupleDColumn(2,"Ce2VX", RunVectorCe2EnterVX);
	analysisManager->CreateNtupleDColumn(2,"Ce2VY", RunVectorCe2EnterVY);
	analysisManager->CreateNtupleDColumn(2,"Ce2VZ", RunVectorCe2EnterVZ);
	analysisManager->CreateNtupleDColumn(2,"Ce2PX", RunVectorCe2EnterPX);
	analysisManager->CreateNtupleDColumn(2,"Ce2PY", RunVectorCe2EnterPY);
	analysisManager->CreateNtupleDColumn(2,"Ce2PZ", RunVectorCe2EnterPZ);

	analysisManager->CreateNtupleDColumn(2,"Dummy0Ene", RunVectorDummy0EnterEne);
	analysisManager->CreateNtupleDColumn(2,"Dummy0Part", RunVectorDummy0EnterPart);
	analysisManager->CreateNtupleDColumn(2,"Dummy0X", RunVectorDummy0EnterX);
	analysisManager->CreateNtupleDColumn(2,"Dummy0Y", RunVectorDummy0EnterY);
	analysisManager->CreateNtupleDColumn(2,"Dummy0Z", RunVectorDummy0EnterZ);
	analysisManager->CreateNtupleDColumn(2,"Dummy0VX", RunVectorDummy0EnterVX);
	analysisManager->CreateNtupleDColumn(2,"Dummy0VY", RunVectorDummy0EnterVY);
	analysisManager->CreateNtupleDColumn(2,"Dummy0VZ", RunVectorDummy0EnterVZ);
	analysisManager->CreateNtupleDColumn(2,"Dummy0PX", RunVectorDummy0EnterPX);
	analysisManager->CreateNtupleDColumn(2,"Dummy0PY", RunVectorDummy0EnterPY);
	analysisManager->CreateNtupleDColumn(2,"Dummy0PZ", RunVectorDummy0EnterPZ);
	
	analysisManager->CreateNtupleDColumn(2,"Dummy1Ene", RunVectorDummy1EnterEne);
	analysisManager->CreateNtupleDColumn(2,"Dummy1Part", RunVectorDummy1EnterPart);
	analysisManager->CreateNtupleDColumn(2,"Dummy1X", RunVectorDummy1EnterX);
	analysisManager->CreateNtupleDColumn(2,"Dummy1Y", RunVectorDummy1EnterY);
	analysisManager->CreateNtupleDColumn(2,"Dummy1Z", RunVectorDummy1EnterZ);
	analysisManager->CreateNtupleDColumn(2,"Dummy1VX", RunVectorDummy1EnterVX);
	analysisManager->CreateNtupleDColumn(2,"Dummy1VY", RunVectorDummy1EnterVY);
	analysisManager->CreateNtupleDColumn(2,"Dummy1VZ", RunVectorDummy1EnterVZ);
	analysisManager->CreateNtupleDColumn(2,"Dummy1PX", RunVectorDummy1EnterPX);
	analysisManager->CreateNtupleDColumn(2,"Dummy1PY", RunVectorDummy1EnterPY);
	analysisManager->CreateNtupleDColumn(2,"Dummy1PZ", RunVectorDummy1EnterPZ);
	
	analysisManager->CreateNtupleDColumn(2,"Dummy2Ene", RunVectorDummy2EnterEne);
	analysisManager->CreateNtupleDColumn(2,"Dummy2Part", RunVectorDummy2EnterPart);
	analysisManager->CreateNtupleDColumn(2,"Dummy2X", RunVectorDummy2EnterX);
	analysisManager->CreateNtupleDColumn(2,"Dummy2Y", RunVectorDummy2EnterY);
	analysisManager->CreateNtupleDColumn(2,"Dummy2Z", RunVectorDummy2EnterZ);
	analysisManager->CreateNtupleDColumn(2,"Dummy2VX", RunVectorDummy2EnterVX);
	analysisManager->CreateNtupleDColumn(2,"Dummy2VY", RunVectorDummy2EnterVY);
	analysisManager->CreateNtupleDColumn(2,"Dummy2VZ", RunVectorDummy2EnterVZ);
	analysisManager->CreateNtupleDColumn(2,"Dummy2PX", RunVectorDummy2EnterPX);
	analysisManager->CreateNtupleDColumn(2,"Dummy2PY", RunVectorDummy2EnterPY);
	analysisManager->CreateNtupleDColumn(2,"Dummy2PZ", RunVectorDummy2EnterPZ);
	
	analysisManager->CreateNtupleDColumn(2,"S4Ene", RunVectorS4EnterEne);
	analysisManager->CreateNtupleDColumn(2,"S4Part", RunVectorS4EnterPart);
	analysisManager->CreateNtupleDColumn(2,"S4X", RunVectorS4EnterX);
	analysisManager->CreateNtupleDColumn(2,"S4Y", RunVectorS4EnterY);
	analysisManager->CreateNtupleDColumn(2,"S4Z", RunVectorS4EnterZ);
	analysisManager->CreateNtupleDColumn(2,"S4VX", RunVectorS4EnterVX);
	analysisManager->CreateNtupleDColumn(2,"S4VY", RunVectorS4EnterVY);
	analysisManager->CreateNtupleDColumn(2,"S4VZ", RunVectorS4EnterVZ);
	analysisManager->CreateNtupleDColumn(2,"S4PX", RunVectorS4EnterPX);
	analysisManager->CreateNtupleDColumn(2,"S4PY", RunVectorS4EnterPY);
	analysisManager->CreateNtupleDColumn(2,"S4PZ", RunVectorS4EnterPZ);
	
	analysisManager->CreateNtupleDColumn(2,"S5Ene", RunVectorS5EnterEne);
	analysisManager->CreateNtupleDColumn(2,"S5Part", RunVectorS5EnterPart);
	analysisManager->CreateNtupleDColumn(2,"S5X", RunVectorS5EnterX);
	analysisManager->CreateNtupleDColumn(2,"S5Y", RunVectorS5EnterY);
	analysisManager->CreateNtupleDColumn(2,"S5Z", RunVectorS5EnterZ);
	analysisManager->CreateNtupleDColumn(2,"S5VX", RunVectorS5EnterVX);
	analysisManager->CreateNtupleDColumn(2,"S5VY", RunVectorS5EnterVY);
	analysisManager->CreateNtupleDColumn(2,"S5VZ", RunVectorS5EnterVZ);
	analysisManager->CreateNtupleDColumn(2,"S5PX", RunVectorS5EnterPX);
	analysisManager->CreateNtupleDColumn(2,"S5PY", RunVectorS5EnterPY);
	analysisManager->CreateNtupleDColumn(2,"S5PZ", RunVectorS5EnterPZ);
	
	analysisManager->CreateNtupleDColumn(2,"S6Ene", RunVectorS6EnterEne);
	analysisManager->CreateNtupleDColumn(2,"S6Part", RunVectorS6EnterPart);
	analysisManager->CreateNtupleDColumn(2,"S6X", RunVectorS6EnterX);
	analysisManager->CreateNtupleDColumn(2,"S6Y", RunVectorS6EnterY);
	analysisManager->CreateNtupleDColumn(2,"S6Z", RunVectorS6EnterZ);
	analysisManager->CreateNtupleDColumn(2,"S6VX", RunVectorS6EnterVX);
	analysisManager->CreateNtupleDColumn(2,"S6VY", RunVectorS6EnterVY);
	analysisManager->CreateNtupleDColumn(2,"S6VZ", RunVectorS6EnterVZ);
	analysisManager->CreateNtupleDColumn(2,"S6PX", RunVectorS6EnterPX);
	analysisManager->CreateNtupleDColumn(2,"S6PY", RunVectorS6EnterPY);
	analysisManager->CreateNtupleDColumn(2,"S6PZ", RunVectorS6EnterPZ);
	
	analysisManager->CreateNtupleDColumn(2,"S7Ene", RunVectorS7EnterEne);
	analysisManager->CreateNtupleDColumn(2,"S7Part", RunVectorS7EnterPart);
	analysisManager->CreateNtupleDColumn(2,"S7X", RunVectorS7EnterX);
	analysisManager->CreateNtupleDColumn(2,"S7Y", RunVectorS7EnterY);
	analysisManager->CreateNtupleDColumn(2,"S7Z", RunVectorS7EnterZ);
	analysisManager->CreateNtupleDColumn(2,"S7VX", RunVectorS7EnterVX);
	analysisManager->CreateNtupleDColumn(2,"S7VY", RunVectorS7EnterVY);
	analysisManager->CreateNtupleDColumn(2,"S7VZ", RunVectorS7EnterVZ);
	analysisManager->CreateNtupleDColumn(2,"S7PX", RunVectorS7EnterPX);
	analysisManager->CreateNtupleDColumn(2,"S7PY", RunVectorS7EnterPY);
	analysisManager->CreateNtupleDColumn(2,"S7PZ", RunVectorS7EnterPZ);

	analysisManager->CreateNtupleDColumn(2,"T1Ene", RunVectorT1EnterEne);
	analysisManager->CreateNtupleDColumn(2,"T1Part", RunVectorT1EnterPart);
	analysisManager->CreateNtupleDColumn(2,"T1X", RunVectorT1EnterX);
	analysisManager->CreateNtupleDColumn(2,"T1Y", RunVectorT1EnterY);
	analysisManager->CreateNtupleDColumn(2,"T1Z", RunVectorT1EnterZ);
	analysisManager->CreateNtupleDColumn(2,"T1VX", RunVectorT1EnterVX);
	analysisManager->CreateNtupleDColumn(2,"T1VY", RunVectorT1EnterVY);
	analysisManager->CreateNtupleDColumn(2,"T1VZ", RunVectorT1EnterVZ);
	analysisManager->CreateNtupleDColumn(2,"T1PX", RunVectorT1EnterPX);
	analysisManager->CreateNtupleDColumn(2,"T1PY", RunVectorT1EnterPY);
	analysisManager->CreateNtupleDColumn(2,"T1PZ", RunVectorT1EnterPZ);

	analysisManager->CreateNtupleDColumn(2,"T2Ene", RunVectorT2EnterEne);
	analysisManager->CreateNtupleDColumn(2,"T2Part", RunVectorT2EnterPart);
	analysisManager->CreateNtupleDColumn(2,"T2X", RunVectorT2EnterX);
	analysisManager->CreateNtupleDColumn(2,"T2Y", RunVectorT2EnterY);
	analysisManager->CreateNtupleDColumn(2,"T2Z", RunVectorT2EnterZ);
	analysisManager->CreateNtupleDColumn(2,"T2VX", RunVectorT2EnterVX);
	analysisManager->CreateNtupleDColumn(2,"T2VY", RunVectorT2EnterVY);
	analysisManager->CreateNtupleDColumn(2,"T2VZ", RunVectorT2EnterVZ);
	analysisManager->CreateNtupleDColumn(2,"T2PX", RunVectorT2EnterPX);
	analysisManager->CreateNtupleDColumn(2,"T2PY", RunVectorT2EnterPY);
	analysisManager->CreateNtupleDColumn(2,"T2PZ", RunVectorT2EnterPZ);

	analysisManager->CreateNtupleDColumn(2,"T3Ene", RunVectorT3EnterEne);
	analysisManager->CreateNtupleDColumn(2,"T3Part", RunVectorT3EnterPart);
	analysisManager->CreateNtupleDColumn(2,"T3X", RunVectorT3EnterX);
	analysisManager->CreateNtupleDColumn(2,"T3Y", RunVectorT3EnterY);
	analysisManager->CreateNtupleDColumn(2,"T3Z", RunVectorT3EnterZ);
	analysisManager->CreateNtupleDColumn(2,"T3VX", RunVectorT3EnterVX);
	analysisManager->CreateNtupleDColumn(2,"T3VY", RunVectorT3EnterVY);
	analysisManager->CreateNtupleDColumn(2,"T3VZ", RunVectorT3EnterVZ);
	analysisManager->CreateNtupleDColumn(2,"T3PX", RunVectorT3EnterPX);
	analysisManager->CreateNtupleDColumn(2,"T3PY", RunVectorT3EnterPY);
	analysisManager->CreateNtupleDColumn(2,"T3PZ", RunVectorT3EnterPZ);

	analysisManager->CreateNtupleDColumn(2,"T4Ene", RunVectorT4EnterEne);
	analysisManager->CreateNtupleDColumn(2,"T4Part", RunVectorT4EnterPart);
	analysisManager->CreateNtupleDColumn(2,"T4X", RunVectorT4EnterX);
	analysisManager->CreateNtupleDColumn(2,"T4Y", RunVectorT4EnterY);
	analysisManager->CreateNtupleDColumn(2,"T4Z", RunVectorT4EnterZ);
	analysisManager->CreateNtupleDColumn(2,"T4VX", RunVectorT4EnterVX);
	analysisManager->CreateNtupleDColumn(2,"T4VY", RunVectorT4EnterVY);
	analysisManager->CreateNtupleDColumn(2,"T4VZ", RunVectorT4EnterVZ);
	analysisManager->CreateNtupleDColumn(2,"T4PX", RunVectorT4EnterPX);
	analysisManager->CreateNtupleDColumn(2,"T4PY", RunVectorT4EnterPY);
	analysisManager->CreateNtupleDColumn(2,"T4PZ", RunVectorT4EnterPZ);

	analysisManager->CreateNtupleDColumn(2,"T5Ene", RunVectorT5EnterEne);
	analysisManager->CreateNtupleDColumn(2,"T5Part", RunVectorT5EnterPart);
	analysisManager->CreateNtupleDColumn(2,"T5X", RunVectorT5EnterX);
	analysisManager->CreateNtupleDColumn(2,"T5Y", RunVectorT5EnterY);
	analysisManager->CreateNtupleDColumn(2,"T5Z", RunVectorT5EnterZ);
	analysisManager->CreateNtupleDColumn(2,"T5VX", RunVectorT5EnterVX);
	analysisManager->CreateNtupleDColumn(2,"T5VY", RunVectorT5EnterVY);
	analysisManager->CreateNtupleDColumn(2,"T5VZ", RunVectorT5EnterVZ);
	analysisManager->CreateNtupleDColumn(2,"T5PX", RunVectorT5EnterPX);
	analysisManager->CreateNtupleDColumn(2,"T5PY", RunVectorT5EnterPY);
	analysisManager->CreateNtupleDColumn(2,"T5PZ", RunVectorT5EnterPZ);

	analysisManager->CreateNtupleDColumn(2,"T6Ene", RunVectorT6EnterEne);
	analysisManager->CreateNtupleDColumn(2,"T6Part", RunVectorT6EnterPart);
	analysisManager->CreateNtupleDColumn(2,"T6X", RunVectorT6EnterX);
	analysisManager->CreateNtupleDColumn(2,"T6Y", RunVectorT6EnterY);
	analysisManager->CreateNtupleDColumn(2,"T6Z", RunVectorT6EnterZ);
	analysisManager->CreateNtupleDColumn(2,"T6VX", RunVectorT6EnterVX);
	analysisManager->CreateNtupleDColumn(2,"T6VY", RunVectorT6EnterVY);
	analysisManager->CreateNtupleDColumn(2,"T6VZ", RunVectorT6EnterVZ);
	analysisManager->CreateNtupleDColumn(2,"T6PX", RunVectorT6EnterPX);
	analysisManager->CreateNtupleDColumn(2,"T6PY", RunVectorT6EnterPY);
	analysisManager->CreateNtupleDColumn(2,"T6PZ", RunVectorT6EnterPZ);


	analysisManager->CreateNtupleDColumn(2,"Mu1Ene", RunVectorMu1EnterEne);
	analysisManager->CreateNtupleDColumn(2,"Mu1Part", RunVectorMu1EnterPart);
	analysisManager->CreateNtupleDColumn(2,"Mu1X", RunVectorMu1EnterX);
	analysisManager->CreateNtupleDColumn(2,"Mu1Y", RunVectorMu1EnterY);
	analysisManager->CreateNtupleDColumn(2,"Mu1Z", RunVectorMu1EnterZ);
	analysisManager->CreateNtupleDColumn(2,"Mu1VX", RunVectorMu1EnterVX);
	analysisManager->CreateNtupleDColumn(2,"Mu1VY", RunVectorMu1EnterVY);
	analysisManager->CreateNtupleDColumn(2,"Mu1VZ", RunVectorMu1EnterVZ);
	analysisManager->CreateNtupleDColumn(2,"Mu1PX", RunVectorMu1EnterPX);
	analysisManager->CreateNtupleDColumn(2,"Mu1PY", RunVectorMu1EnterPY);
	analysisManager->CreateNtupleDColumn(2,"Mu1PZ", RunVectorMu1EnterPZ);
	analysisManager->CreateNtupleDColumn(2,"Mu1CopyNb", RunVectorMu1EnterCopyNb);

	analysisManager->CreateNtupleDColumn(2,"Mu2Ene", RunVectorMu2EnterEne);
	analysisManager->CreateNtupleDColumn(2,"Mu2Part", RunVectorMu2EnterPart);
	analysisManager->CreateNtupleDColumn(2,"Mu2X", RunVectorMu2EnterX);
	analysisManager->CreateNtupleDColumn(2,"Mu2Y", RunVectorMu2EnterY);
	analysisManager->CreateNtupleDColumn(2,"Mu2Z", RunVectorMu2EnterZ);
	analysisManager->CreateNtupleDColumn(2,"Mu2VX", RunVectorMu2EnterVX);
	analysisManager->CreateNtupleDColumn(2,"Mu2VY", RunVectorMu2EnterVY);
	analysisManager->CreateNtupleDColumn(2,"Mu2VZ", RunVectorMu2EnterVZ);
	analysisManager->CreateNtupleDColumn(2,"Mu2PX", RunVectorMu2EnterPX);
	analysisManager->CreateNtupleDColumn(2,"Mu2PY", RunVectorMu2EnterPY);
	analysisManager->CreateNtupleDColumn(2,"Mu2PZ", RunVectorMu2EnterPZ);
	analysisManager->CreateNtupleDColumn(2,"Mu2CopyNb", RunVectorMu2EnterCopyNb);

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
#if 0
	for (int ii=0; ii<(int)fChannelMap.size() && G4Threading::G4GetThreadId()==-1; ii++) { //write CaloMap histo only once if MT to avoid problems
//		analysisManager->FillH1(0, ii, fChannelMap[ii]);
	}
	
//	auto iter = Mappa.find((41+ii)*100);
	for (std::map<G4int,G4int>::iterator iter= fChannelMap.begin(); G4Threading::G4GetThreadId()==-1&& iter!=fChannelMap.end(); ++iter) {
		G4cout<<"ITERATORE first= "<<iter->first<<" second= "<<iter->second<<G4endl;
	}
#endif
	
	
}

void B1RunAction::EndOfRunAction(const G4Run* run){
	
	G4int nofEvents = run->GetNumberOfEvent();
	if (nofEvents == 0) return;
	
	//save histograms
	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	analysisManager->Write();
	analysisManager->CloseFile();
	
}

