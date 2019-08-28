#include "B1PrimaryGeneratorAction.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#define HEPFLAG //Toggle this flag to enable HepMC External generator at pre-processor level - disable on muoncoll.lnf server
#ifdef HEPFLAG
#include "HepMCG4AsciiReader.hh"
#endif

B1PrimaryGeneratorAction::B1PrimaryGeneratorAction(G4double BeamEnergy,G4double BeamDP, G4bool CalibMuMBeamFlag, G4bool CalibMuPBeamFlag, G4bool ProdMuonBeamFlag, G4bool ElectronBeamFlag, G4bool SimpleFlag, G4bool ExtSourceFlagBha, G4bool ExtSourceFlagMu,  G4int TargMat, G4double TargDZ)
: G4VUserPrimaryGeneratorAction(),
fParticleGun(0),
fBeamEnergy(BeamEnergy),
fBeamDP(BeamDP),
fCalibMuMBeamFlag(CalibMuMBeamFlag),
fCalibMuPBeamFlag(CalibMuPBeamFlag),
fProdMuonBeamFlag(ProdMuonBeamFlag),
fElectronBeamFlag(ElectronBeamFlag),
fSimpleFlag(SimpleFlag),
fExtSourceFlagBha(ExtSourceFlagBha),
fExtSourceFlagMu(ExtSourceFlagMu),
fTargMat(TargMat),
fTargDZ(TargDZ)
{
	G4int n_particle = 1;
	fParticleGun  = new G4ParticleGun(n_particle);
	G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
	G4String particleName;
	
	G4ParticleDefinition* particle;
	particle = particleTable->FindParticle(particleName="e+"); //Primary Positron Beam by default
	
//	G4cout<<"  fTargMat = "<< fTargMat<<G4endl;
//	G4cout<<"  fTargDZ = "<< fTargDZ<<G4endl;

	if(fExtSourceFlagBha) {
		G4cout<<"# # # # # # # # # # # # # # # # # # # # # # # # # # # "<<G4endl<<"I am using as primary particles externally generated e+e- bhabha pairs"<<G4endl;
#ifdef HEPFLAG
		if (fTargMat==0 || (fTargMat==1 && fTargDZ==6*cm))
			hepmcAscii = new HepMCG4AsciiReader("ExtData_ep-prepared-Be6cmLEMMA18-2.0.dat"); //path must be relative to where the code runs (eg build directory)
		else if (fTargMat==1)
			hepmcAscii = new HepMCG4AsciiReader("ExtData_ep-prepared-C2cmLEMMA18-2.0.dat"); //path must be relative to where the code runs (eg build directory)
#endif
	} else if(fExtSourceFlagMu) {
		G4cout<<"# # # # # # # # # # # # # # # # # # # # # # # # # # # "<<G4endl<<"I am using as primary particles externally generated mu+mu- pairs"<<G4endl;
#ifdef HEPFLAG
		if (fTargMat==0 || (fTargMat==1 && fTargDZ==6*cm))
//			hepmcAscii = new HepMCG4AsciiReader("ExtData_mm-prepared-Be6cmLEMMA18-2.0.dat"); //path must be relative to where the code runs (eg build directory)
//			hepmcAscii = new HepMCG4AsciiReader("ExtData_mm-prepared-Be6cmLEMMA18-2.0AddPos.dat"); //path must be relative to where the code runs (eg build directory) NORMAL
//		hepmcAscii = new HepMCG4AsciiReader("ExtData_mm-prepared-Be6cmLEMMA18-2.0-GausGaus.dat"); //path must be relative to where the code runs (eg build directory) - 16.05.2019 by abertolin
			//hepmcAscii = new HepMCG4AsciiReader("ExtData_mm-prepared-cylinder.dat"); //path must be relative to where the code runs (eg build directory) - 25.07.2019 by abertolin for 2018 august test beam
			hepmcAscii = new HepMCG4AsciiReader("ExtData_mm-prepared+multscat.dat"); //path must be relative to where the code runs (eg build directory) - 25.07.2019 by abertolin for 2018 august test beam

//			hepmcAscii = new HepMCG4AsciiReader("ExtData_mm-prepared-Check2018.dat"); //path must be relative to where the code runs (eg build directory) - 27.08.2019 by abertolin for 2018 august test beam quello di agosto 2018 per trovare l'errore

		else if (fTargMat==1)
			hepmcAscii = new HepMCG4AsciiReader("ExtData_mm-prepared-C2cmLEMMA18-2.0.dat"); //path must be relative to where the code runs (eg build directory)
		
		
//		hepmcAscii = new HepMCG4AsciiReader("Camilla.dat"); //path must be relative to where the code runs (eg build directory)
#endif
	} else {
		if(fCalibMuMBeamFlag) {
			particle = particleTable->FindParticle(particleName="mu-"); //Primary Muon Beam
			G4cout<<"I am simulating a Mu- primary beam of energy "<<fBeamEnergy/GeV<<" GeV"<<G4endl;
		} else if(fCalibMuPBeamFlag) {
			particle = particleTable->FindParticle(particleName="mu+"); //Primary Muon Beam
			G4cout<<"I am simulating a Mu+ primary beam of energy "<<fBeamEnergy/GeV<<" GeV"<<G4endl;
		} else if(fProdMuonBeamFlag) {
			particle = particleTable->FindParticle(particleName="mu+"); //Primary Muon Beam produced after Target
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
	//-- Beam parameters
	//----------------
	G4double x0,y0,z0;
	G4double sizeX = 10*mm;
	G4double sizeY = 10*mm;
	
	z0 = -1*mm; //was -1.e-5 until 6.4.18, but is inside T1!!!
	
	if (fProdMuonBeamFlag) { //If produced muon beam has been requested, retrieve target location to start particles after it
		G4VPhysicalVolume* physTarget = G4PhysicalVolumeStore::GetInstance()->GetVolume("Target");
		G4double zTargetCenter=physTarget->GetTranslation().z();
		G4LogicalVolume* logicTarget = G4LogicalVolumeStore::GetInstance()->GetVolume("Target");
		G4Tubs * bersaglio= (G4Tubs*)(logicTarget->GetSolid());
		
		G4double DZTarget=bersaglio->GetZHalfLength();
		G4double ProdMuonBeamStart=zTargetCenter+DZTarget;
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
		p_smear = 170.e-6; //unclear source - 2017: DA MATTIA DIVERGENZA ~140urad
//		EnergySpread = 0.01; //1%
		EnergySpread = fBeamDP; //1%
		sizeX = 10*mm;
		sizeY = 10*mm;
	}
	
	if (fProdMuonBeamFlag) {
		sizeX=1*cm;
		sizeY=1*cm;
	}
	
	//-- Gaussian shoot
	//   --------------
//	while (1>0){ //
		x0 = G4RandGauss::shoot(0.,sizeX);
		y0 = G4RandGauss::shoot(0.,sizeY);
//		if ( abs(x0)<cut && abs(y0)<cut ) break;
//	}
	
	//-- Uniform shoot
	//----------------
//  x0 = sizeX * (G4UniformRand()-0.5);
//	y0 = sizeY * (G4UniformRand()-0.5);
	
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
	
	G4double Energy0=fBeamEnergy;
	
	G4double Energy = G4RandGauss::shoot(Energy0, Energy0*EnergySpread);
	
	if (fProdMuonBeamFlag) {
		Energy=22.5*GeV+ ( 15*GeV* (G4UniformRand()-0.5)); //22.5 + 15 for flat in 15-30 GeV - put 24.5 + 17... to have 16-33
//		Energy=24.5*GeV+ ( 17*GeV* (G4UniformRand()-0.5)); //22.5 + 15 for flat in 15-30 GeV - put 24.5 + 17... to have 16-33
	}
	
	fParticleGun->SetParticleEnergy(Energy);
	
	if (fExtSourceFlagBha || fExtSourceFlagMu) {
#ifdef HEPFLAG
		hepmcAscii->GeneratePrimaryVertex(anEvent);
#endif
	}	else {
		fParticleGun->GeneratePrimaryVertex(anEvent);
	}
	
}


