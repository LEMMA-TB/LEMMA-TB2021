# simulation
Geant4 simulation of LEMMA test beam, done @CERN on ~August 2017.

### HOW TO RUN
- You have to have Geant4 up and running
- type:
cd build
cmake -DGeant4_DIR=$G4INSTALL ../setup/
make
./mainMCMC
./mainMCMC ../setup/run1.mac

Please note that if any changes are done to ../setup/*.mac you need to cmake -XXX again
### GEOMETRY
The geometry is the one of the final configuration

### PRIMARY PARTICLE
The simulation is set to simulate primary positrons starting at the origin (0,0,0). It is possible to simulate a realistic beam (energy, angular and position spread), but there is a flag (SimpleFlag) in B1PrimaryGeneratorAction.cc to select the simple case of ideal beam.
There are flags in the mainMCMC.cc to generate other particles (electrons, muons) and other energies.

### OUTPUT
The simulation creates a LemmaMC.root file, in which on an event (i.e. a primary particle) by event basis it is stored:
BEAM vector (one entry per primary particle, may be more than 1):
- BeamX[]: X coordinate of primary particle [mm];
- BeamY[]: Y coordinate of primary particle [mm];
- BeamZ[]: Z coordinate of primary particle [mm];
- BeamCX[]: X directive cosine of primary particle;
- BeamCY[]: Y directive cosine  of primary particle;
- BeamCZ[]: Z directive cosine  of primary particle;
- BeamEne[]: kinetic energy of the beam [GeV];
- BeamPart[]: PDG code of primary particle (11=e-, -11=e+, 22=gamma, 13=mu-...);
- nhits: number of entries to the INTERACTIONS vector (see below) per event

INTERACTIONS vector (one entry per interaction happening at the border between two different regions, to spare CPU time and disk space):
- subdet[]: number of subdetector in which the interactio happened
- Idp[]: PDG code of particle interacting (11=e-, -11=e+, 22=gamma, 13=mu-...);
- ipar[]: parent ID of the track (0 is primary...);
- itrack[]: track ID of the track;
- Time[]: time age of the track [ns];
- xh[]: X coordinate of the interaction [cm];
- yh[]: Y coordinate of the interaction [cm];
- zh[]: Z coordinate of the interaction [cm];
- P[]: momentum of the particle [GeV];
- PX[]: X component of momentum of the particle [GeV];
- PY[]: Y component of momentum of the particle [GeV];
- PZ[]: Z component of momentum of the particle [GeV];
- VertexX[]: X component of interaction vertex vector [cm];
- VertexY[]: Y component of interaction vertex vector [cm];
- VertexZ[]: Z component of interaction vertex vector [cm];
- kinev[]: vertex kinetic energy [GeV];
- PXvdir[]: X component of momentum of interaction vertex vector [normalised to P];
- PYvdir[]: Y component of momentum of interaction vertex vector [normalised to P];
- PZvdir[]: Z component of momentum of interaction vertex vector [normalised to P];
- Iev[]: event id (in this way we also store the number of entries to the INTERACTIONS vector for each event);
- Step[]: number of current step;
- InextStep[]: is 1 if there will be another step, 0 if the particle is going to die.
- CopyNb: id of DEVA layer in which the interaction happened
- DEVEInX: X entering point in DEVA
- DEVEInY: Y entering point in DEVA
- DEVEInZ: Z entering point in DEVA
- DEVAENEXXX?: energy release in DEVA layers

Please note that due to Geant4 issues regarding multi core root output, multi thread is currently disabled (can be enabled in mainMCMC.cc, but creates N-root files named LemmaMC_t?.root)

### TO MERGE MULTIPLE ROOT OUTPUT FILES:
TChain * chain = new TChain("LEMMA")
chain->Add("LemmaMC_t*.root")
TFile *file = TFile::Open("LemmaMC2018_ProdMuP_T_Mf.root","RECREATE");
chain->CloneTree(-1,"fast");
file->Write();


TChain * chain = new TChain("LEMMA")
chain->Add("LemmaMC_t*.root")
TChain * chain2 = new TChain("Beam")
chain2->Add("LemmaMC_t*.root")
TFile *file = TFile::Open("LemmaMC2018_Pos45_T_MfCurrent650_10k_PreStepZ.root","RECREATE");
chain->CloneTree(-1,"fast");
chain2->CloneTree(-1,"fast");
file->Write();

LemmaMC2018_Pos45_T_MfCurrent650

### FILE NAMES FOR OUTPUT
TFile *file = TFile::Open("LemmaMC_Tot45PosT_bias.root","RECREATE");
TFile *file = TFile::Open("LemmaMC_Tot22PosNoT_simple.root","RECREATE");

TFile *file = TFile::Open("LemmaMC_Pos22s_NoT_Ff_calo.root","RECREATE");  //Fixed field  flipped
TFile *file = TFile::Open("LemmaMC_Pos22_NoT_M_calo.root","RECREATE");    //Map field not flipped



### OR TO READ TOGETHER WITHOUT MERGING

TChain * chain = new TChain("LEMMA")
chain->Add("LemmaMC_t*.root")
LEMMA->Draw("DEVAEneTot")

### COMANDI VARI
LEMMA->Draw("DEVAEneTot")
LEMMA->Draw("Kinev:CopyNb","subdet==77&&Idp==-11","lego")


#############################
### CHANGE-LOG
2017.09.11 Modified by collamaf (francesco.collamati@roma1.infn.it)
- added Cerenkov absorber (with generic dimensions)
- created README file
- added CalibMuonBeamFlag

2018.05.10 by collamaf
- Uploaded new geometry
- Chamber is removed from "calo table", remains orthogonal to beam (not tilted)
- Chamber is now divided into 4+4 planes
- Scoring condition is now ONLY "step->GetPreStepPoint()->GetStepStatus()==fGeomBoundary"


TODO LIST
- recuperare generatore esterno (i file ora hanno le posizioni dell'altro setup..)






