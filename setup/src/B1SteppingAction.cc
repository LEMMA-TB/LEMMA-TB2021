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
//---------------------------
#include "G4ProcessType.hh"
#include "G4OpticalPhoton.hh"

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction, B1RunAction* runAction, G4bool StoreCaloEnDepFlag, G4double EThr)
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
fScoringVolume_Pb1a(0),
fScoringVolume_Pb1b(0),
fScoringVolume_Pb1c(0),
fScoringVolume_Pb2a(0),
fScoringVolume_Pb2b(0),
fScoringVolume_Pb2c(0),
fScoringVolume_Ce1(0),
fScoringVolume_Ce2(0),
fScoringVolume_Mu1(0),
fScoringVolume_Mu2(0),
fStoreCaloEnDepFlag(StoreCaloEnDepFlag),
fEThr(EThr)
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
	if (!fScoringVolume_Pb1a) {fScoringVolume_Pb1a = detectorConstruction->GetScoringVolume_Pb1a();}
	if (!fScoringVolume_Pb1b) {fScoringVolume_Pb1b = detectorConstruction->GetScoringVolume_Pb1b();}
	if (!fScoringVolume_Pb1c) {fScoringVolume_Pb1c = detectorConstruction->GetScoringVolume_Pb1c();}
	if (!fScoringVolume_Pb2a) {fScoringVolume_Pb2a = detectorConstruction->GetScoringVolume_Pb2a();}
	if (!fScoringVolume_Pb2b) {fScoringVolume_Pb2b = detectorConstruction->GetScoringVolume_Pb2b();}
	if (!fScoringVolume_Pb2c) {fScoringVolume_Pb2c = detectorConstruction->GetScoringVolume_Pb2c();}
	if (!fScoringVolume_Ce1) {fScoringVolume_Ce1 = detectorConstruction->GetScoringVolume_Ce1();}
	if (!fScoringVolume_Ce2) {fScoringVolume_Ce2 = detectorConstruction->GetScoringVolume_Ce2();}
	if (!fScoringVolume_Mu1) {fScoringVolume_Mu1 = detectorConstruction->GetScoringVolume_Mu1();}
	if (!fScoringVolume_Mu2) {fScoringVolume_Mu2 = detectorConstruction->GetScoringVolume_Mu2();}

	G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
	
	
	G4LogicalVolume* volume =
	step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
	
	G4VPhysicalVolume* ThisVol = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
	G4VPhysicalVolume* NextVol = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume();
	
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
	else if (volume==fScoringVolume_Pb1a)   {subdet=41; dofill=true;}  //
	else if (volume==fScoringVolume_Pb1b)   {subdet=42; dofill=true;}  //
	else if (volume==fScoringVolume_Pb1c)   {subdet=43; dofill=true;}  //
	else if (volume==fScoringVolume_Pb2a)   {subdet=46; dofill=true;}  //
	else if (volume==fScoringVolume_Pb2b)   {subdet=45; dofill=true;}  //
	else if (volume==fScoringVolume_Pb2c)   {subdet=44; dofill=true;}  //
	else if (volume==fScoringVolume_Ce1)   {subdet=51; dofill=true;}  //
	else if (volume==fScoringVolume_Ce2)   {subdet=52; dofill=true;}  //
	else if (volume==fScoringVolume_Mu1)   {subdet=61; dofill=true;}  //
	else if (volume==fScoringVolume_Mu2)   {subdet=62; dofill=true;}  //

	
	
	//Score energy deposition into DEVA elements (if fStoreCaloEnDepFlag true in main!)
	G4int CopyNb=step->GetPostStepPoint()->GetTouchableHandle()->GetCopyNumber();
	G4double DepEne=step->GetTotalEnergyDeposit()/GeV;
	G4int Pid=step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding();
	

	if (subdet==77 && DepEne>0 && fStoreCaloEnDepFlag) { //DEVA deposited energy - avoiding saving 0ene events spares about 20% of disk space...
		fEventAction->AddDEVAEneTot(DepEne);
		if (CopyNb==0 || CopyNb==1) {
			(runStepAction->GetDEVADepo())[0]+=DepEne;
		} else if (CopyNb==2 || CopyNb==3) {
			(runStepAction->GetDEVADepo())[1]+=DepEne;
		}
		if (CopyNb==4 || CopyNb==5) {
			(runStepAction->GetDEVADepo())[2]+=DepEne;
		}
		if (CopyNb==6 || CopyNb==7) {
			(runStepAction->GetDEVADepo())[3]+=DepEne;
		}
		if (CopyNb==8 || CopyNb==9) {
			(runStepAction->GetDEVADepo())[4]+=DepEne;
		}
		if (CopyNb==10 || CopyNb==11) {
			(runStepAction->GetDEVADepo())[5]+=DepEne;
		}
	}
	
	if (subdet==41 || subdet==42 || subdet==43 && DepEne>0 && fStoreCaloEnDepFlag) { //PbGlass TOP deposited energy
		fEventAction->AddPbGlassEne(DepEne);
	}
	
	if (subdet==80 && DepEne>0 && fStoreCaloEnDepFlag) { //Cerenkov deposited energy (only 4 of 6 channels were red): Channels go from 0 to 6 bottom-forward to top-backward wrt beam entering direction: Iacoangeli says 2,3,5,6 were on
		fEventAction->AddCerenkovEneTot(DepEne);
		if (CopyNb==0 ) {
			(runStepAction->GetCerenkovDepo())[1]+=DepEne;
		}
		if (CopyNb==1) {
			(runStepAction->GetCerenkovDepo())[2]+=DepEne;
		}
		if (CopyNb==3) {
			(runStepAction->GetCerenkovDepo())[4]+=DepEne;
		}
		if (CopyNb==4 ) {
			(runStepAction->GetCerenkovDepo())[5]+=DepEne;
		}
	}
	
	if (subdet==72 && DepEne>0 && fStoreCaloEnDepFlag) { //Scint72 deposited energy
		(runStepAction->GetScint72DepEne()).push_back(DepEne);
	}
	if (subdet==74 && DepEne>0 && fStoreCaloEnDepFlag) { //Scint74 deposited energy
		(runStepAction->GetScint74DepEne()).push_back(DepEne);
	}
	//added on 15.12.17 @ Padova - What enters DEVA
	if (NextVol && ThisVol->GetName()=="EcalDummy" && NextVol->GetName()=="Ecal") {
		runStepAction->GetDEVAInX().push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
		runStepAction->GetDEVAInY().push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
		runStepAction->GetDEVAInZ().push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
	}
	
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
							(fEventAction->AddPbGlassCere(1)); //incremento di 1 il contatore di fotoni cerenkov
						}
						// se sono nel detector di Cerenkov
						else if (subdet==80 && CerFotLambda>CerFotLambdaCut) {
							(runStepAction->GetCerenkovDepoOpt())[CopyNb]+=1; //incremento di 1 il contatore di fotoni cerenkov del rispettivo canale
						}
//						G4cout<<"DEBUG Cerenkov!!! Energia fotone= "<<CerFotEne<<", lamda [um]= "<< CerFotLambda<<", subdet= "<<subdet<<  G4endl;
					}
				}
			}
		}
	}
	
	
	
	
	//-- store info
	//	if (dofill && ((step->GetPostStepPoint()->GetStepStatus()==fGeomBoundary)
	//				   || (step->GetPreStepPoint()->GetStepStatus()==fGeomBoundary)) && !(Pid==22 && step->GetPreStepPoint()->GetMomentum().mag()<EThr) ) { //If Output Cut required do not store photons under a certain energy
	//#### NORMAL
//	if (dofill && ((step->GetPostStepPoint()->GetStepStatus()==fGeomBoundary) || (step->GetPreStepPoint()->GetStepStatus()==fGeomBoundary)) && (!fCutFlag || !(Pid==22 && step->GetPreStepPoint()->GetMomentum().mag()<fEThr) )) { //If Output Cut required do not store photons under a certain energy - Logic expression: A & B & !(!C || !(D & E) )
  //### FINE NORMAL

//	ALL
//	if (dofill  && subdet!=76  && subdet!=77  && subdet!=78 && (!fCutFlag || !(Pid==22 && step->GetPreStepPoint()->GetMomentum().mag()<fEThr) )) { //If Output Cut required do not store photons under a certain energy - Logic expression: A & B & !(!C || !(D & E) )

	// SOLO PRE/POST - PRE
	if (dofill && (step->GetPreStepPoint()->GetStepStatus()==fGeomBoundary) && (!fCutFlag || !(Pid==22 && step->GetPreStepPoint()->GetMomentum().mag()<fEThr) )) { //If Output Cut required do not store photons under a certain energy - Logic expression: A & B & !(!C || !(D & E) )
		
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
		
		//process = step->GetTrack()->GetCreatorProcess()->GetProcessName();
		if (step->GetTrack()->GetCreatorProcess()) pro = step->GetTrack()->GetCreatorProcess()->GetProcessSubType();
		//			if (Itrack!=1) { // different from gun particle
		xvertex = step->GetTrack()->GetVertexPosition();
		
		if(subdet==77) (runStepAction->GetCopyNb()).push_back(CopyNb);  //I'm interested in CopyNb only for DEVA active components (subdet==77)
		
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
		
		//		G4cout<<ke<<G4endl;
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
	
	//	} // if(preStep)
	
}
