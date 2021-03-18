#include "G4MTRunManager.hh"
#include "G4RunManager.hh"  
//----------------------------------
#include "G4UImanager.hh"
#include "G4Run.hh"
#include "B1DetectorConstruction.hh"
#include "B1DetectorConstructionAug.hh"
#include "TBDetectorConstruction.hh"
#include "B1ActionInitialization.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4VUserPhysicsList.hh"
#include "PhysicsList.hh"
#include "B1RunAction.hh"
#include "B1StackingAction.hh"
#include "SteppingVerbose.hh"
#include "Randomize.hh"
#include "time.h"
#include "G4AnnihiToMuPair.hh"
#include "G4PhysListFactory.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4ChannelingPhysics.hh"
#include "G4GenericBiasingPhysics.hh"
#include "G4ProcessTable.hh"
#include "G4EmStandardPhysicsSS.hh"
#include "G4SystemOfUnits.hh"
//------------------------------
//#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
//#endif
#include "G4VisExecutive.hh"

//#ifdef G4UI_USE
#include "G4UIExecutive.hh"
//#endif

#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>
#include <vector>


using namespace std;

int main(int argc,char** argv)
{
	// Define both MT and ST RunManager to be able to choose later which one to use
	G4MTRunManager* runManagerMT ;
	G4RunManager* runManager ;
	
	// ##############################################################################
	// ##################### FLAG DEFINITION TO CHOOSE THE DESIRED CONFIGURATION
	// ##############################################################################
	// ################### These are defaults, can be overridden by command line ####
	// ###############
	
	G4bool CalibMuMBeamFlag=true;  //switching on this flag generates mu- primary beam, otherwise e+. The SimpleFlag is still considered for the beam distribution
	G4bool CalibMuPBeamFlag=false;  //switching on this flag generates mu+ primary beam, otherwise e+. The SimpleFlag is still considered for the beam distribution
	G4bool ProdMuonBeamFlag=false;  //switching on this flag generates mu- beam at the end of the target, to simulate the muon production: E in 15-30 GeV, along Z
	G4bool ElectronBeamFlag=false;  //switching on this flag generates e- beam, otherwise e+. The SimpleFlag is still considered for the beam distribution
	G4double BeamEnergy=22.5*GeV; //Primary Beam Energy (18, 22, 26 GeV options for e+ calibration) - 45 GeV for real TB
	G4bool SimpleFlag=false; //Generates a "simple-ideal" beam: no spread, no emittance...
	G4double BeamDP=0.017; //was 0.01, but Mario obtained 1.7%
	
	//Flags to force use of externally generated primary files (for bhabha and muon pair production)
	//Note that the filename is provided in PrimaryGenAction (path must be relative to where the code runs (eg build directory))
	//These flags ovverride previous ones (CalibMuMBeamFlag, ElectronBeamFlag etc) and also BeamEnergy
	G4bool ExtSourceFlagBha=false;
	G4bool ExtSourceFlagMu=false;
	
	G4int TargMat = 0; //0 is Be, 1 is C
	G4double TargDZ = 6*cm; //default total length for target
	G4bool TargetFlag=true; //Place or not the target
	G4bool FlipFieldFlag=false; //non-flipped (=false) field sends positrons towards down in the sketc, flipped (=true) sends positrons up
	//	G4double MagField=700; //running current (in A) of the magnet. If negative is the exact magnetic field to be used as constant
	G4double MagField=-2; //updated on 2018.08.15 @CERN, since there is no map for this magnet, we plan to run it @ 580A, was -1.7476 T during TB2018a
	G4bool AllVacFlag=false; //Set all materials (except Target) to air, to see what happens to primary particles
	G4double RootCutThr=1; //Flag to cut on output file: photons with energy lower than this value (in GeV) will not be written. Set negative to write them all
	G4double GeometryZoom=1; //Transverse zoom of trackers (Ts and Cs det)
	
	G4bool StoreCaloEnDepFlag=true; //to disable scoring of energy deposition (gamma, e+, e-, total) in calorimeters (sparing ~15% of disk space)
	G4bool StoreGammaConvFlag=true; //To enable the storing on information on gamma conversion position and energy
	G4bool DetEnterExitFlag=true; //To enable scoring of what eneters and exits PbGlass and Cerenkov detectors
	
	G4bool MTFlag=false; //Toggle Multi Thread running
	G4int NProcInput=1; // default value for number of threads requested (1-> SingleT, <0-> all threads MultiT, X-> X threads)
	
	G4bool Aug2018Flag=false; //To choose TB2018a (aug) geometry

	G4bool ReadGeoFromFile=true;
	G4String GeoFileName="layout.gdml";
	
	G4bool VisFlag=false; //To enable visualization
	G4int NoOfPrimToGen=10000, Verbose=0;
	G4String MacroName="";
	G4String FileNameLabel="";
	G4UIExecutive* ui = 0;
	
	// ###############
	// ##################### END: FLAG DEFINITION TO CHOOSE THE DESIRED CONFIGURATION
	// ##############################################################################
	
	// ##############################################################################
	// ##################### COMMAND LINE PARAMETERS INPUT
	// ###############
	
	for(int i=1;i<argc;i++)
		if(argv[i][0] =='-')
		{
			G4String option(argv[i]);
			G4cout<<"option: "<<i<<" "<<option<<G4endl;
			if(option.compare("-CalibMuM")==0)
			{
				CalibMuMBeamFlag=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-CalibMuP")==0)
			{
				CalibMuPBeamFlag=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-ProdMu")==0)
			{
				ProdMuonBeamFlag=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-Ele")==0)
			{
				ElectronBeamFlag=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-BeamEne")==0)
			{
				BeamEnergy=strtod (argv[++i], NULL)*GeV;;
			}
			else if(option.compare("-BeamDP")==0)
			{
				BeamDP=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-Simple")==0)
			{
				SimpleFlag=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-Target")==0)
			{
				TargetFlag=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-TargMat")==0)
			{
				TargMat=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-TargDZ")==0)
			{
				TargDZ=strtod (argv[++i], NULL)*cm;;
			}
			else if(option.compare("-FlipField")==0)
			{
				FlipFieldFlag=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-MagField")==0)
			{
				MagField=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-Calo")==0)
			{
				StoreCaloEnDepFlag=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-GammaConv")==0)
			{
				StoreGammaConvFlag=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-ExtBhaBha")==0)
			{
				ExtSourceFlagBha=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-ExtMuMu")==0)
			{
				ExtSourceFlagMu=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-Aug2018")==0)
			{
				Aug2018Flag=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-DetZoom")==0)
			{
				GeometryZoom=strtod (argv[++i], NULL);;
			}
			else if(option.compare("-NPrim")==0)
			{
				NoOfPrimToGen=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-Verbose")==0)
			{
				Verbose=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-Vis")==0)
			{
				VisFlag=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-NProc")==0)
			{
				NProcInput=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-AllVac")==0)
			{
				AllVacFlag=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-DetEnterExit")==0)
			{
				DetEnterExitFlag=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-Label")==0)
			{
				FileNameLabel= argv[++i];;
			}
		}
		else
		{
			MacroName = argv[i]; //If I found a macro (without trailing "-") it means that I do NOT want visualization
			//VisFlag=false; 
		}
	
	std::vector<G4int>  TriggerLogic={65, 66};
	
	// ###############
	// ##################### END: COMMAND LINE PARAMETERS INPUT
	// ##############################################################################
	
	
	G4Random::setTheEngine(new CLHEP::RanecuEngine);
	G4long seed = time(NULL);
	if (VisFlag) seed=12345; //If vis was requested same always the same seed to have reproducibility
	G4Random::setTheSeed(seed);
	
	if (NProcInput==1) MTFlag=false;
	
	if (MTFlag) {
		runManagerMT= new G4MTRunManager;
		if (NProcInput<0 || NProcInput>G4Threading::G4GetNumberOfCores()) runManagerMT->SetNumberOfThreads( G4Threading::G4GetNumberOfCores() );
		else 		runManagerMT->SetNumberOfThreads( NProcInput );
	} else {
		runManager= new G4RunManager;
	}
	
	// ##############################################################################
	// ##################### PREPARE CALO-MAP VECTOR
	// ###############
	
#if 1
	std::vector<G4int> ChannelMap={4100, 4200, 4300, 4400, 4500, 4600}; //PbGlasses
	
	for (int ii=0; ii<34; ii++) { //Ce1 (34 channels)
		ChannelMap.push_back(5100+ii);
	}
	for (int ii=0; ii<24; ii++) { //Ce2 (24 channels)
		ChannelMap.push_back(5200+ii);
	}
	ChannelMap.push_back(7700);
#endif
	
	std::map<G4int,G4int> Mappa;
	
#if 1
	Mappa[4100]=0;
	Mappa[4200]=1;
	Mappa[4300]=2;
	Mappa[4400]=3;
	Mappa[4500]=4;
	Mappa[4600]=5;
	
	Mappa[7700]=6;
	
	Mappa[5100]=10;
	Mappa[5101]=10;
	Mappa[5102]=10;
	Mappa[5103]=11;
	Mappa[5104]=11;
	Mappa[5105]=11;
	
	
	Mappa[5119]=12;
	Mappa[5120]=12;
	Mappa[5121]=12;
	Mappa[5122]=13;
	Mappa[5123]=13;
	Mappa[5124]=13;
	
	
	Mappa[5200]=14;
	Mappa[5201]=15;
	Mappa[5202]=16;
	Mappa[5203]=16;
	Mappa[5204]=16;
	Mappa[5205]=17;
	Mappa[5206]=17;
	Mappa[5207]=17;
	
	Mappa[5208]=18;
	Mappa[5209]=18;
	Mappa[5210]=18;
	
	Mappa[5211]=19;
	Mappa[5212]=19;
	Mappa[5213]=19;
	
	Mappa[5214]=20;
	Mappa[5215]=21;
	Mappa[5216]=22;
	Mappa[5217]=22;
	Mappa[5218]=22;
	Mappa[5219]=23;
	Mappa[5220]=23;
	Mappa[5221]=23;
	
	
#endif
	G4int NDumChannels=1;
	G4int NTotChannels=Mappa[5221]+1+NDumChannels;
	
	// ###############
	// ##################### END: PREPARE CALO-MAP VECTOR
	// ##############################################################################
	G4cout<<"DIMENSIONE MAPPA: size= "<<Mappa.size()<<G4endl;
	
	G4cout<<"DIMENSIONE MAPPA: max element = "<<NTotChannels<<G4endl;
	
#if 0
	for (int ii=0; ii<ChannelMap.size(); ii++) G4cout<<"MAPPA vector: i= "<<ii<<" channel= "<<ChannelMap.at(ii)<<G4endl;
	
	//	std::vector<int>::iterator iteratore;
	for (int ii=0; ii<3; ii++) {
		//		iteratore = find(Mappa.begin(), Mappa.end(),4100+ii);
		auto iter = Mappa.find((41+ii)*100);
		if (iter != Mappa.end()) G4cout<<"MAPPA map: i= "<<ii<<" looking for "<< (41+ii)*100<<" iter->first= "<<iter->first<<" iter->second= "<<iter->second<<" Mappa[]= "<<Mappa[(41+ii)*100]<<G4endl;
	}
#endif
	
	
	
	// ##############################################################################
	// ##################### PHYSICS LIST AND DETECTOR CONSTRUCTION
	// ###############
	
	G4bool FTFP = false; // standard Geant4 PhysicsList
	G4bool channeling = false;
	G4String ctype = "Si" ;  // "C" or "Si"
	
	//Define both DetConst (Aug/Sept)
	B1DetectorConstruction* detector;
	B1DetectorConstructionAug* detectorAug;
	TBDetectorConstruction* tbDetector;
	
	if ( ReadGeoFromFile )  {
	  G4cout<<"Initializing geometry from GDML file: " << GeoFileName << G4endl;
	  tbDetector = new TBDetectorConstruction(GeoFileName);
	  
	}
	else if (!ReadGeoFromFile && !Aug2018Flag) { // september 2018 setup
		G4cout<<"September Geometry required"<<G4endl;
		detector=new B1DetectorConstruction( TargetFlag, FlipFieldFlag, MagField, GeometryZoom, AllVacFlag, TargMat, TargDZ);
		detector->SetChanneling(channeling,ctype);
	}
	else { //august 2018 setup
		G4cout<<"August Geometry required"<<G4endl;
		detectorAug =new B1DetectorConstructionAug( TargetFlag, FlipFieldFlag, MagField, GeometryZoom, AllVacFlag);		detectorAug->SetChanneling(channeling,ctype);
	}
	
	if ( FTFP ){
		G4PhysListFactory *physListFactory = new G4PhysListFactory();
		G4VModularPhysicsList* physics =
		physListFactory->GetReferencePhysList("FTFP_BERT_EMV"); // default
		physics->SetVerboseLevel(1);
		if(channeling){
			G4GenericBiasingPhysics* biasingPhysics = new G4GenericBiasingPhysics();
			physics->RegisterPhysics(new G4ChannelingPhysics());
			//physics->ReplacePhysics(new G4EmStandardPhysicsSS());
			biasingPhysics->PhysicsBiasAllCharged();
			physics->RegisterPhysics(biasingPhysics);
			//          detector->SetChanneling(true);
		}
		if (MTFlag) {
			runManagerMT->SetUserInitialization(physics);
		} else {
			runManager->SetUserInitialization(physics);
		}
	} else { // use my own PhysicsList.cc
		if (MTFlag) {
			runManagerMT->SetUserInitialization(new PhysicsList());
		} else {
			runManager->SetUserInitialization(new PhysicsList());
		}
	}
	
	// ###############
	// ##################### END: PHYSICS LIST AND DETECTOR CONSTRUCTION
	// ##############################################################################
	
	  if (ReadGeoFromFile) {
	    if ( MTFlag ) {
	      runManagerMT->SetUserInitialization(tbDetector);
	      runManagerMT->SetUserInitialization(new B1ActionInitialization(BeamEnergy, BeamDP, CalibMuMBeamFlag, CalibMuPBeamFlag, ProdMuonBeamFlag, ElectronBeamFlag, SimpleFlag, StoreCaloEnDepFlag, StoreGammaConvFlag, ExtSourceFlagBha, ExtSourceFlagMu, RootCutThr, Mappa, DetEnterExitFlag, NTotChannels, TriggerLogic, TargMat , TargDZ, Aug2018Flag));
	      runManagerMT->Initialize();  // init kernel
	    } else {
	      runManager->SetUserInitialization(tbDetector);
	      runManager->SetUserInitialization(new B1ActionInitialization(BeamEnergy, BeamDP, CalibMuMBeamFlag, CalibMuPBeamFlag, ProdMuonBeamFlag, ElectronBeamFlag, SimpleFlag, StoreCaloEnDepFlag, StoreGammaConvFlag, ExtSourceFlagBha, ExtSourceFlagMu, RootCutThr, Mappa, DetEnterExitFlag, NTotChannels, TriggerLogic, TargMat , TargDZ, Aug2018Flag));
	      runManager->Initialize();  // init kernel
	    }
	    
	  }
	  else {
	    if (MTFlag) {
	      
	      
	      if (!Aug2018Flag) 	runManagerMT->SetUserInitialization(detector);
	      else runManagerMT->SetUserInitialization(detectorAug);
	      runManagerMT->SetUserInitialization(new B1ActionInitialization(BeamEnergy, BeamDP, CalibMuMBeamFlag, CalibMuPBeamFlag, ProdMuonBeamFlag, ElectronBeamFlag, SimpleFlag, StoreCaloEnDepFlag, StoreGammaConvFlag, ExtSourceFlagBha, ExtSourceFlagMu, RootCutThr, Mappa, DetEnterExitFlag, NTotChannels, TriggerLogic, TargMat , TargDZ, Aug2018Flag));
	      runManagerMT->Initialize();  // init kernel
	    } else {
	      if (!Aug2018Flag) 	runManager->SetUserInitialization(detector);
	      else runManager->SetUserInitialization(detectorAug);
	      runManager->SetUserInitialization(new B1ActionInitialization(BeamEnergy,BeamDP, CalibMuMBeamFlag, CalibMuPBeamFlag, ProdMuonBeamFlag, ElectronBeamFlag, SimpleFlag, StoreCaloEnDepFlag,StoreGammaConvFlag, ExtSourceFlagBha, ExtSourceFlagMu, RootCutThr, Mappa, DetEnterExitFlag,NTotChannels, TriggerLogic,  TargMat, TargDZ, Aug2018Flag));
	      runManager->Initialize();  // init kernel
	    }
	  }

	
	  G4VisManager* visManager ;
if (VisFlag) {	
//#ifdef G4VIS_USE
	// Initialize visualization
	visManager = new G4VisExecutive;
	visManager->Initialize();
//#endif
	}
	// Get the pointer to the User Interface manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();
	
	if ( VisFlag ) { //Prepare for vis
		ui = new G4UIExecutive(argc, argv);
	}
	
	if ( ! ui ) {
		// batch mode
		if (MacroName!="") {
			G4String command = "/control/execute ";
			UImanager->ApplyCommand(command+MacroName);
		} else {
			UImanager->ApplyCommand("/tracking/verbose " + std::to_string(Verbose));
			UImanager->ApplyCommand("/run/beamOn " + std::to_string(NoOfPrimToGen));
		}
	}
	else {
		// interactive mode
		UImanager->ApplyCommand("/control/execute init_vis.mac");
		ui->SessionStart();
		delete ui;
	}
	
	//RETRIEVE RUN TO GET THE NUMBER OF EVENTS I AM SIMULATING
	const G4Run* run;
	if (MTFlag) {
		run=runManagerMT->GetCurrentRun();
	}
	else {
		run=runManager->GetCurrentRun();
	}
	
	// ##############################################################################
	// ##################### PREPARE OUTPUT FILENAME
	// ###############
	
	G4String OutputFilename = "Lemma2018MC";
	
	if(Aug2018Flag) OutputFilename.append("_Aug");
	
	//Primary particle info
	if (ExtSourceFlagMu) OutputFilename.append("_MuMu");
	else if (ExtSourceFlagBha) OutputFilename.append("_Bhabha");
	else if (ElectronBeamFlag) OutputFilename.append("_Ele"+ std::to_string(G4int (BeamEnergy)) );
	else if (CalibMuMBeamFlag) OutputFilename.append("_CalibMuM"+ std::to_string(G4int (BeamEnergy)) );
	else if (CalibMuPBeamFlag) OutputFilename.append("_CalibMuP"+ std::to_string(G4int (BeamEnergy)) );
	else if (ProdMuonBeamFlag) OutputFilename.append("_ProdMuP");
	else OutputFilename.append("_Pos"+ std::to_string(G4int (BeamEnergy)) );
	if (SimpleFlag) OutputFilename.append("_simple");
	if (BeamDP!=0.017) OutputFilename.append("_DP"+ std::to_string(G4int (1000*BeamDP)) );
	
	//Target ?
	if (TargetFlag) {
		OutputFilename.append("_T");
		if (TargMat==0) OutputFilename.append("Be");
		else if (TargMat==1) OutputFilename.append("C");
		OutputFilename.append("_"+ std::to_string(G4int (TargDZ/mm)) );
	}
	else  OutputFilename.append("_NoT");
	
	//Magnetic field
	if (MagField>=0) {
		OutputFilename.append("_FieldM"); //Map
		if (MagField!=700) OutputFilename.append(std::to_string(G4int (-MagField*100) )); //Map: if different from default current (700) write its value
	} else  {
		OutputFilename.append("_FieldF");
		if ((!Aug2018Flag&& MagField!=-2) || Aug2018Flag) OutputFilename.append(std::to_string(G4int (-MagField*100) )); //Fixed: write the fixed value used
	}
	if (FlipFieldFlag) OutputFilename.append("f");
	
	//Geometry options
	if (GeometryZoom!=1) OutputFilename.append("_Z" + std::to_string(G4int (GeometryZoom) ));
	if (AllVacFlag) OutputFilename.append("_VAC");
	
	//Scoring options
	if (StoreCaloEnDepFlag) OutputFilename.append("_calo");
	if (StoreGammaConvFlag) OutputFilename.append("_gconv");
	
	if (FileNameLabel!="") OutputFilename.append("_" + FileNameLabel);
	
	//Number of generated primaries
	OutputFilename.append("_N" + std::to_string ((G4int) (run->GetNumberOfEventToBeProcessed())));
	
	// ###############
	// ##################### END: PREPARE OUTPUT FILENAME
	// ##############################################################################
	
	if (VisFlag) {
		//#ifdef G4VIS_USE
		delete visManager;
		//#endif
	}
	
	if (MTFlag) {
		delete runManagerMT;
	}
	else {
		delete runManager;
	}
	
	// ##############################################################################
	// ##################### PREPARE FILE ANALYSIS SCRIPT
	// ###############
	
	std::ofstream CommandOutput("ProcessFiles.C", std::ios::out);
	
	if (MTFlag) {
		CommandOutput<<
		"{\n TFile *_file = TFile::Open(\"LemmaMC.root\");\n TH1D* CaloMap2=(TH1D*)CaloMap->Clone(\"CaloMap2\");\n TChain * chain = new TChain(\"LEMMA\");\n	chain->Add(\"LemmaMC_t*.root\");\n TChain * chain2 = new TChain(\"Beam\");\n	chain2->Add(\"LemmaMC_t*.root\"); \n TChain * chain3 = new TChain(\"DetEnter\");\n	chain3->Add(\"LemmaMC_t*.root\");\n TChain * chain4 = new TChain(\"DetExit\");\n	chain4->Add(\"LemmaMC_t*.root\"); \nTFile *file = TFile::Open(\""<< OutputFilename<<".root\",\"RECREATE\");\n 	chain->CloneTree(-1,\"fast\"); \n 	chain2->CloneTree(-1,\"fast\");\n 	chain3->CloneTree(-1,\"fast\");\n 	chain4->CloneTree(-1,\"fast\");\n file->Write();\n CaloMap2->SetName(\"CaloMap\");\n CaloMap2->Write();\n  gSystem->Exec(\"rm LemmaMC*.root\");\n }"
		<<G4endl;
		G4cout<<"\n##################################### \n##################################### \n########### TO CREATE PROPER ROOT FILE FOR THIS SIMULATION \n   root -l ProcessFiles.C \n##################################### \n root -l "<<OutputFilename<<".root \n#####################################"<<G4endl;
	} else {
		CommandOutput<<
		"{\n mv LemmaMC.root "<< OutputFilename<<".root\n } "
		<<G4endl;
		G4cout<<"\n##################################### \n##################################### \n########### TO CREATE PROPER ROOT FILE FOR THIS SIMULATION \nmv LemmaMC.root "<< OutputFilename<<".root\n##################################### \n root -l "<<OutputFilename<<".root \n##################################### "<<G4endl;
		
	}
	
	// ###############
	// ##################### END: PREPARE FILE ANALYSIS SCRIPT
	// ##############################################################################
	
	return 0;
}
