#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"  
#endif
//----------------------------------
#include "G4UImanager.hh"
#include "G4Run.hh"
#include "B1DetectorConstruction.hh"
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
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>
#include <vector>

using namespace std;

int main(int argc,char** argv)
{
	
	G4Random::setTheEngine(new CLHEP::RanecuEngine);
	G4long seed = time(NULL);
	G4Random::setTheSeed(seed);
	
	G4bool MTFlag=FALSE;
	//#ifdef G4MULTITHREADED
#if 0
	MTFlag=TRUE;
	G4MTRunManager* runManager = new G4MTRunManager;
	runManager->SetNumberOfThreads( G4Threading::G4GetNumberOfCores() );
#else
	G4RunManager* runManager = new G4RunManager;
#endif
	
	// FLAG DEFINITION TO CHOOSE THE DESIRED CONFIGURATION - These are defaults, can be overridden by command line
	G4bool CalibMuonBeamFlag=false;  //switching on this flag generates mu- beam, otherwise e+. The SimpleFlag in PrimGenAction is still considered for the beam distribution
	G4bool ProdMuonBeamFlag=false;  //switching on this flag generates mu- beam at the end of the target, to simulate the muon production: E in 15-30 GeV, along Z
	G4bool ElectronBeamFlag=false;  //switching on this flag generates e- beam, otherwise e+. The SimpleFlag in PrimGenAction is still considered for the beam distribution
	G4double BeamEnergy=45.*GeV; //Primary Beam Energy (18, 22, 26 GeV options for e+ calibration) - 45 GeV for real TB
	G4bool SimpleFlag=false;
	G4bool TargetFlag=true;
	G4bool FlipFieldFlag=true; //non-flipped (=false) field sends positrons towards down in the sketc, flipped (=true) sends positrons up
	G4bool MagMapFlag=true;
	G4bool StoreCaloEnDepFlag=false; //to disable scoring of energy deposition (gamma, e+, e-, total) in calorimeters (sparing ~15% of disk space)
																	 //Flags to force use of externally generated primary files (for bhabha and muon pair production)
																	 //Note that the filename is provided in PrimaryGenAction (path must be relative to where the code runs (eg build directory))
																	 //These flags ovverride previous ones (CalibMuonBeamFlag, ElectronBeamFlag etc) and also BeamEnergy
	G4bool ExtSourceFlagBha=false;
	G4bool ExtSourceFlagMu=false;
	
	//Flag to cut on output file: photons with energy lower than this value will not be written. Set negative to write them all
	G4double RootCutThr=1*GeV;
	G4double GeometryZoom=1; //Transverse zoom of trackers (Ts and Cs det)
	
	
	G4bool VisFlag=false;
	G4int NoOfPrimToGen=100, Verbose=0;
	G4String MacroName="";
	G4String FileNameLabel="";
	G4UIExecutive* ui = 0;
	
	
	for(int i=1;i<argc;i++)
		if(argv[i][0] =='-')
		{
			G4String option(argv[i]);
			G4cout<<"option: "<<i<<" "<<option<<G4endl;
			if(option.compare("-CalibMu")==0)
			{
				CalibMuonBeamFlag=stoi (argv[++i], NULL);;
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
			else if(option.compare("-Simple")==0)
			{
				SimpleFlag=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-Target")==0)
			{
				TargetFlag=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-FlipField")==0)
			{
				MagMapFlag=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-MapField")==0)
			{
				TargetFlag=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-Calo")==0)
			{
				StoreCaloEnDepFlag=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-ExtBhaBha")==0)
			{
				ExtSourceFlagBha=stoi (argv[++i], NULL);;
			}
			else if(option.compare("-ExtMuMu")==0)
			{
				ExtSourceFlagMu=stoi (argv[++i], NULL);;
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
			else if(option.compare("-Label")==0)
			{
				FileNameLabel= argv[++i];;
			}
		}
		else
		{
			MacroName = argv[i]; //se ho trovato una macro (senza il "-" davanti) significa che NON voglio l'interattivo
			VisFlag=false;
		}
	
	
//	std::vector<G4int> ChannelMap={4100, 4200, 4300, 4400, 4500, 4600, 5100, 5101, 5102, 5103, 5104, 5105, 5200, 5201, 5202, 5203, 5204, 5205};
	std::vector<G4int> ChannelMap={4100, 4200, 4300, 4400, 4500, 4600};

	for (int ii=0; ii<34; ii++) {
		ChannelMap.push_back(5100+ii);
	}

	for (int ii=0; ii<24; ii++) {
		ChannelMap.push_back(5200+ii);
	}
	
	//==================================================
	G4bool FTFP = false; // standard Geant4 PhysicsList
	G4bool channeling = false;
	G4String ctype = "Si" ;  // "C" or "Si"
													 //==================================================
	B1DetectorConstruction* detector =new B1DetectorConstruction( TargetFlag, FlipFieldFlag, MagMapFlag, GeometryZoom);
	detector->SetChanneling(channeling,ctype);
	
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
		runManager->SetUserInitialization(physics);
	} else { // use my own PhysicsList.cc
		runManager->SetUserInitialization(new PhysicsList());
	}
	
	runManager->SetUserInitialization(detector);
	runManager->SetUserInitialization(new B1ActionInitialization(BeamEnergy, CalibMuonBeamFlag, ProdMuonBeamFlag, ElectronBeamFlag, SimpleFlag, StoreCaloEnDepFlag,ExtSourceFlagBha, ExtSourceFlagMu, RootCutThr, ChannelMap));

	runManager->Initialize();  // init kernel

	
	
#ifdef G4VIS_USE
	// Initialize visualization
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();
#endif
	
	// Get the pointer to the User Interface manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();
	
	if ( VisFlag ) { //Prepare for vis
		ui = new G4UIExecutive(argc, argv);
	}
	
	if ( ! ui ) {
		// batch mode
		if (MacroName!="") {
			G4String command = "/control/execute ";
			//		G4String fileName = argv[13];
			UImanager->ApplyCommand(command+MacroName);
		} else {
			UImanager->ApplyCommand("/tracking/verbose " + std::to_string(Verbose));
			UImanager->ApplyCommand("/run/beamOn " + std::to_string(NoOfPrimToGen));
			//			UImanager->ApplyCommand("/run/beamOn 100");
		}
	}
	else {
		// interactive mode
		UImanager->ApplyCommand("/control/execute init_vis.mac");
		ui->SessionStart();
		delete ui;
	}
	
	//RETRIEVE RUN TO GET THE NUMBER OF EVENTS I AM SIMULATING
	const G4Run* run=runManager->GetCurrentRun();
	//	run->SetNumberOfEventToBeProcessed(17); // does not work
	G4String OutputFilename = "LemmaMC2018";
	G4String OutputFilenameFirstNote ="";
	OutputFilename.append(OutputFilenameFirstNote);
	
	
	if (ExtSourceFlagMu) OutputFilename.append("_MuMu");
	else if (ExtSourceFlagBha) OutputFilename.append("_Bhabha");
	else if (ElectronBeamFlag) OutputFilename.append("_Ele"+ std::to_string(G4int (BeamEnergy)) );
	else if (CalibMuonBeamFlag) OutputFilename.append("_CalibMuM"+ std::to_string(G4int (BeamEnergy)) );
	else if (ProdMuonBeamFlag) OutputFilename.append("_ProdMuM");
	else OutputFilename.append("_Pos"+ std::to_string(G4int (BeamEnergy)) );
	
	if (SimpleFlag) OutputFilename.append("_simple");
	
	if (TargetFlag) OutputFilename.append("_T");
	else  OutputFilename.append("_NoT");
	
	if (MagMapFlag) OutputFilename.append("_M"); //Map
	else  OutputFilename.append("_F"); //Fixed
	
	if (FlipFieldFlag) OutputFilename.append("f");
	
	if (StoreCaloEnDepFlag) OutputFilename.append("_calo");
	
	if (GeometryZoom!=1) OutputFilename.append("_Z" + std::to_string(G4int (GeometryZoom) ));
	
	G4String OutputFilenameSecondNote ="";
	if (FileNameLabel!="") OutputFilename.append("_" + FileNameLabel);
	OutputFilename.append("_N" + std::to_string ((G4int) (run->GetNumberOfEventToBeProcessed())));
	OutputFilename.append(OutputFilenameSecondNote);
	
#ifdef G4VIS_USE
	delete visManager;
#endif
	delete runManager;
	
	if (MTFlag) {
		G4cout<<
		"\n ##################################### \n ##################################### \n########### TO CREATE PROPER ROOT FILE FOR THIS SIMULATION \n TChain * chain = new TChain(\"LEMMA\");\n	chain->Add(\"LemmaMC_t*.root\");\n TChain * chain2 = new TChain(\"Beam\");\n	chain2->Add(\"LemmaMC_t*.root\")\n ;TFile *file = TFile::Open(\""<< OutputFilename<<".root\",\"RECREATE\");\n 	chain->CloneTree(-1,\"fast\"); \n 	chain2->CloneTree(-1,\"fast\");\n file->Write();\n ##################################### \n ##################################### "
		<<G4endl;
		//	"########### TO ANALYZE THIS SIMULATION \n TChain * chain = new TChain(\"LEMMA\");\n	chain->Add(\"LemmaMC_t*.root\");\n TChain * chain2 = new TChain(\"Beam\");\n	chain2->Add(\"LemmaMC_t*.root\")\n ;TFile *file = TFile::Open(\"LemmaMC2018_MuMuBert_T_MfCurrent650_10k_PreStepZ_Large.root\",\"RECREATE\");\n 	chain->CloneTree(-1,\"fast\"); \n 	chain2->CloneTree(-1,\"fast\");\n file->Write(); "
	} else {
		
		G4cout<<
		"\n ##################################### \n ##################################### \n ########### TO CREATE PROPER ROOT FILE FOR THIS SIMULATION \n mv LemmaMC.root "<< OutputFilename<<".root\n ##################################### \n ##################################### "
		<<G4endl;
		
	}
	
	return 0;
	
	
}
