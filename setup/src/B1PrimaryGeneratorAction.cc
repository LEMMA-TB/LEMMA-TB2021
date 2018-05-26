#include "B1PrimaryGeneratorAction.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
//#define HEPFLAG //Toggle this flag to enable HepMC External generator at pre-processor level
#ifdef HEPFLAG
#include "HepMCG4AsciiReader.hh"
#endif

B1PrimaryGeneratorAction::B1PrimaryGeneratorAction(B1EventAction* eventAction, G4double BeamEnergy, G4bool CalibMuonBeamFlag, G4bool ProdMuonBeamFlag, G4bool ElectronBeamFlag, G4bool SimpleFlag, G4bool ExtSourceFlagBha, G4bool ExtSourceFlagMu)
: G4VUserPrimaryGeneratorAction(),
fParticleGun(0),
fEnvelopeBox(0),
evtPrimAction(eventAction),
fBeamEnergy(BeamEnergy),
fCalibMuonBeamFlag(CalibMuonBeamFlag),
fProdMuonBeamFlag(ProdMuonBeamFlag),
fElectronBeamFlag(ElectronBeamFlag),
fSimpleFlag(SimpleFlag),
fExtSourceFlagBha(ExtSourceFlagBha),
fExtSourceFlagMu(ExtSourceFlagMu)
{
	G4int n_particle = 1;
	fParticleGun  = new G4ParticleGun(n_particle);
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName;
	
	G4ParticleDefinition* particle;
	particle = particleTable->FindParticle(particleName="e+"); //Primary Positron Beam

	//	hepmcAscii = new HepMCG4AsciiReader();

	
	if(fExtSourceFlagBha) {
		G4cout<<"# # # # # # # # # # # # # # # # # # # # # # # # # # # "<<G4endl<<"I am using as primary particles externally generated e+e- bhabha pairs"<<G4endl;
//		hepmcAscii = new HepMCG4AsciiReader("ExtDataBhabha.dat"); //path must be relative to where the code runs (eg build directory)
#ifdef HEPFLAG
		hepmcAscii = new HepMCG4AsciiReader("ExtData_ep.dat"); //path must be relative to where the code runs (eg build directory)
#endif
	} else if(fExtSourceFlagMu) {
		G4cout<<"# # # # # # # # # # # # # # # # # # # # # # # # # # # "<<G4endl<<"I am using as primary particles externally generated mu+mu- pairs"<<G4endl;
//		hepmcAscii = new HepMCG4AsciiReader("ExtDataBhabha.dat");
#ifdef HEPFLAG
//		hepmcAscii = new HepMCG4AsciiReader("ExtData_mm.dat");
		hepmcAscii = new HepMCG4AsciiReader("ExtData_mm.dat"); //path must be relative to where the code runs (eg build directory)

#endif
	} else {
		if(fCalibMuonBeamFlag) {
			particle = particleTable->FindParticle(particleName="mu-"); //Primary Muon Beam
			G4cout<<"I am simulating a Mu- primary beam of energy "<<fBeamEnergy/GeV<<" GeV"<<G4endl;
		} else if(fProdMuonBeamFlag) {
			particle = particleTable->FindParticle(particleName="mu+"); //Primary Muon Beam for Calib after Target
			G4cout<<"I am simulating a Mu+ primary beam of energy in 15-30 GeV to simulate pair production STARTING AFTER THE TARGET"<<G4endl;
		}else if(fElectronBeamFlag) {
			particle = particleTable->FindParticle(particleName="e-"); //Primary Electron Beam
			G4cout<<"I am simulating a e- primary beam of energy "<<fBeamEnergy/GeV<<" GeV"<<G4endl;
		} else {
			particle = particleTable->FindParticle(particleName="e+"); //Primary Positron Beam
			G4cout<<"I am simulating a e+ primary beam of energy "<<fBeamEnergy/GeV<<" GeV"<<G4endl;
		}
	}
	fParticleGun->SetParticleDefinition(particle);
}


B1PrimaryGeneratorAction::~B1PrimaryGeneratorAction()
{
	delete fParticleGun;
}


void B1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	// COLLIMATOR and SHOOT
	// ====================
	
	G4double x0,y0,z0;
	//  G4double cut = 2.*mm; // collimator dimension
	G4double sizeX = 10*mm;
	G4double sizeY = 10*mm;
	//-- Gaussian shoot
	//   --------------
	//  while (1>0){ //
	//  x0 = G4RandGauss::shoot(0.,sizeX);
	//  y0 = G4RandGauss::shoot(0.,sizeY);
	//    if ( abs(x0)<cut && abs(y0)<cut ) break;
	//    }
	z0 = -1*mm; //was -1.e-5 until 6.4.18, but is inside T1!!!
	
	if (fProdMuonBeamFlag) {
		
		G4VPhysicalVolume* physTarget = G4PhysicalVolumeStore::GetInstance()->GetVolume("Target");
		G4double zTargetEnd=physTarget->GetTranslation().z();
		/*
		 G4LogicalVolume* logicTarget = G4LogicalVolumeStore::GetInstance()->GetVolume("Targ");
		 G4Tubs * bersaglio= NULL;
		 bersaglio = dynamic_cast<G4Tubs*>(logicTarget->GetSolid());
		 */
		G4double DZTarget=3*cm;
		G4double ProdMuonBeamStart=zTargetEnd+DZTarget;
		z0=ProdMuonBeamStart;
	}
	
	
	
	G4double p_smear;
	G4double EnergySpread;
	
	if (fSimpleFlag) {
		p_smear = 0;
		EnergySpread = 0.0;
		sizeX=0;
		sizeY=0;
	} else 	{
		p_smear = 170.e-6;
		EnergySpread = 0.01;
		sizeX = 20*mm;
		sizeY = 20*mm;
		
	}
	
	if (fProdMuonBeamFlag) {
		sizeX=1*cm;
		sizeY=1*cm;
	}
	
	
	//-- Uniform shoot
	//----------------
	
	
	x0 = sizeX * (G4UniformRand()-0.5);
	y0 = sizeY * (G4UniformRand()-0.5);
	

	
	fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0)); // GUN POSITION
	
	
	//-- ENERGY and ANGULAR SPREAD
	//   =========================
	
	G4double px_smear = G4RandGauss::shoot(0.,p_smear);
	G4double py_smear = G4RandGauss::shoot(0.,p_smear);
	
	if (fProdMuonBeamFlag) {
		px_smear=0;
		py_smear=0;
	}
	
	
	//  G4double px_smear = p_smear*(G4UniformRand()-0.5);
	//  G4double py_smear = p_smear*(G4UniformRand()-0.5);
	fParticleGun->SetParticleMomentumDirection(G4ThreeVector(px_smear,py_smear,1-px_smear*px_smear-py_smear*py_smear));
	// DA MATTIA DIVERGENZA ~140urad
	// no energy spread
	G4double Energy0=fBeamEnergy;
	
	/*
	if(fCalibMuonBeamFlag) {
		Energy0 = 22.*GeV; //Primary Muon Beam
	} else if(fElectronBeamFlag) {
		Energy0 = 22.*GeV; //Primary Electron Beam
	} else {
		Energy0 = 45.*GeV; //Primary Positron Beam (18, 22, 26 GeV options for calibration) - 45 GeV for real TB
	}
	*/
	//	G4double EnergySpread = 0.0; //0.01
	G4double Energy = G4RandGauss::shoot(Energy0, Energy0*EnergySpread);
	
	if (fProdMuonBeamFlag) {
		Energy=22.5*GeV+ ( 15*GeV* (G4UniformRand()-0.5));
	}
	
	fParticleGun->SetParticleEnergy(Energy);
	

	/*
	 -- energy spread:
	 G4double Energy = 45*GeV;
	 G4double sigmaE = 0.01*Energy;
	 Energy = G4RandGauss::shoot(Energy,sigmaE);
	 fParticleGun->SetParticleEnergy(Energy);
  */
//
	
	if (fExtSourceFlagBha || fExtSourceFlagMu) {
//		G4cout<<"SPARO DA FUORI"<<G4endl;
#ifdef HEPFLAG
		hepmcAscii->GeneratePrimaryVertex(anEvent);
#endif
	}	else {
//		G4cout<<"SPARO SORGENTE STANDARD"<<G4endl;

		fParticleGun->GeneratePrimaryVertex(anEvent);
	}
	
}


