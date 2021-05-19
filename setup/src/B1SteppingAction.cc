#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "TBDetectorConstruction.hh"
#include "HistoManager.hh"
#include "B1RunAction.hh"
#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4EventManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalVolumeStore.hh"

//---------------------------
#include "G4ProcessType.hh"
#include "G4OpticalPhoton.hh"

#define FLAG2018A

using namespace std;

B1SteppingAction::B1SteppingAction(B1EventAction* eventAction, B1RunAction* runAction, G4bool StoreCaloEnDepFlag, G4bool StoreGammaConvDepFlag, G4double EThr, G4bool DetEnterExitFlag, const std::vector<G4int>  & TriggerLogic)
 : G4UserSteppingAction(),
   fEventAction(eventAction),
   runStepAction(runAction),
   fStoreCaloEnDepFlag(StoreCaloEnDepFlag),
   fStoreGammaConvDepFlag(StoreGammaConvDepFlag),
   fEThr(EThr),
   fDetEnterExitFlag(DetEnterExitFlag),
   fTriggerLogic(TriggerLogic),
   m_readGeoFromFile(true)
{

  // create the digitizers
  m_siDigitizer = new SiDigitizer();
  for (int i=0 ; i<7 ; ++i ) {
    m_gemDigitizer[i] = new GEMDigitizer();
  }
  
  m_activeVolumes = {"S1","T1","T2","T3","Target","T4","T5","T6",
    "GEM1_DRIFT","GEM1_GAS","GEM1_RO",
    "Mag",
    "GEM2_NEGX_DRIFT","GEM2_NEGX_GAS","GEM2_NEGX_RO","GEM2_POSX_DRIFT","GEM2_POSX_GAS","GEM2_POSX_RO",
    "GEM3_NEGX_DRIFT","GEM3_NEGX_GAS","GEM3_NEGX_RO","GEM3_POSX_DRIFT","GEM3_POSX_GAS","GEM3_POSX_RO",
    "GEM4_NEGX_DRIFT","GEM4_NEGX_GAS","GEM4_NEGX_RO","GEM4_POSX_DRIFT","GEM4_POSX_GAS","GEM4_POSX_RO",
    "Pb1a","Pb1b","Pb1c","Ce1","Pb2a","Pb2b","Pb2c","Ce2","Mu1","Mu2","Dummy0","Dummy1"};

  m_detectorId = {9,10,11,12,25,20,21,22,
    -1,31,-1,
    -1,
    -1,33,-1,-1,32,-1,
    -1,35,-1,-1,34,-1,
    -1,37,-1,-1,36,-1,
    41,42,43,52,44,45,46,51,
    61,62,100,101
  };

  // Ce1 is VERSA ( a X>0 ), subdetector 52 (CaloTable1)
  std::vector<std::string> caloVChannelNames =
    {"CeVW","CeVAlu1","CeVAlu2",
     "CeVSiOtilt0a","CeVSiOtilt0b","CeVSiOtilt0c","CeVSiOtilt0d","CeVSiOtilt0e","CeVSiOtilt0f","CeVSiOtilt0g","CeVSiOtilt0h",
     "CeVSiO1a","CeVSiO1b","CeVSiO1c",
     "CeVSiO6a","CeVSiO6b","CeVSiO6c",
     "CeVSiOtilt1a","CeVSiOtilt1b","CeVSiOtilt1c","CeVSiOtilt1d","CeVSiOtilt1e","CeVSiOtilt1f","CeVSiOtilt1g","CeVSiOtilt1h"};


  std::vector<int> caloVCopyId =
    {10,0,9,
     1,1,1,1,1,1,1,1,
     2,2,2,
     3,3,3,
     4,4,4,4,4,4,4,4};

  std::vector<int> caloVChannelId =
    {0,0,0,
     16,16,17,17,18,18,19,19,
     10,10,10,
     11,11,11,
     20,20,21,21,22,22,23,23};

  // Ce2 is HORSA ( a X<0 ), subdetector 51 (CaloTable2)
  std::vector<std::string> caloHChannelNames =
    {"CeHW","CeHAlu1","CeHAlu2",
     "CeHSiO0a","CeHSiO0b","CeHSiO0c",
     "CeHSiO1a","CeHSiO1b","CeHSiO1c",
     "CeHSiO2a","CeHSiO2b","CeHSiO2c",
     "CeHSiO3a","CeHSiO3b","CeHSiO3c",
     "CeHSiO4a","CeHSiO4b","CeHSiO4c",
     "CeHSiO5a","CeHSiO5b","CeHSiO5c",
     "CeHSiO6a","CeHSiO6b","CeHSiO6c",
     "CeHSiO7a","CeHSiO7b","CeHSiO7c"};

  std::vector<int> caloHCopyId =
    {10,0,9,
     1,1,1,
     2,2,2,
     3,3,3,
     4,4,4,
     5,5,5,
     6,6,6,
     7,7,7,
     8,8,8 };
     
  std::vector<int> caloHChannelId =
    {0,1,2,
     12,12,12,
     12,12,12,
     13,13,13,
     13,13,13,
     14,14,14,
     14,14,14,
     15,15,15,
     15,15,15  };

  //// build the map of the calo channels
  int ih = 0;
  for ( auto it : caloHChannelNames )
    {
      m_caloChannelsMap[0].insert(std::pair<std::string,int>(it,caloHChannelId[ih]));
      m_caloLayersMap[0].insert(std::pair<std::string,int>(it,caloHCopyId[ih]));
	++ih;
    }
  //// build the map of the calo channels
  int iv = 0;
  for ( auto it : caloVChannelNames )
    {
      m_caloChannelsMap[1].insert(std::pair<std::string,int>(it,caloVChannelId[iv]));
      m_caloLayersMap[1].insert(std::pair<std::string,int>(it,caloVCopyId[iv]));
	++iv;
    }
  

}


B1SteppingAction::~B1SteppingAction()
{
  delete m_siDigitizer;
  for (int i=0 ; i<7 ; ++i ) {
    delete m_gemDigitizer[i];
  }
}

void B1SteppingAction::UserSteppingAction(const G4Step* step){
  const G4double hplanck=4.136e-15; //eV*s
  const G4double clight=3e14; //um/s
  const G4double CerFotLambdaCut=0.2; //in [um], cut due to PMT sensitivity
  
  const TBDetectorConstruction* tbDetectorConstruction;
  
  G4String worldName;
  
  if (m_readGeoFromFile && m_scoringVolumes.size()==0 ) {
    tbDetectorConstruction = static_cast<const TBDetectorConstruction*> (G4RunManager::GetRunManager()->GetUserDetectorConstruction());
    worldName="World_PV";
    for ( unsigned int i = 0 ; i<m_activeVolumes.size() ; ++i ) {
      if ( m_scoringVolumes.find(m_activeVolumes[i]) == m_scoringVolumes.end() ) {
	
	ScoringVolume svol;
	svol.volume = tbDetectorConstruction->getScoringVolume(m_activeVolumes[i]);
	svol.name   = m_activeVolumes[i];
	svol.detectorId = m_detectorId[i];
	std::cout << "ADDING a new scoring volume with detectorId, name: " << svol.detectorId << " "
		  << svol.name << std::endl;
	m_scoringVolumes.insert(std::pair<std::string,ScoringVolume>(svol.name,svol));

	/// get the position of the physica volume
	G4VPhysicalVolume* physVol = tbDetectorConstruction->getPhysicalVolume(m_activeVolumes[i]);

	if (svol.detectorId==31) {
	  m_gemDigitizer[0]->setPhysicalVolume(physVol);
	  m_gemDigitizer[0]->setBase(100,100);
	  m_gemDigitizer[0]->setSize(100);
	  m_gemDigitizer[0]->setPitch(0.260);
	  m_gemDigitizer[0]->setMeasY(true);
	}
	else if (svol.detectorId==32) {
	  m_gemDigitizer[1]->setPhysicalVolume(physVol);
	  m_gemDigitizer[1]->setBase(100,100);
	  m_gemDigitizer[1]->setSize(100);
	  m_gemDigitizer[1]->setPitch(0.260);
	  m_gemDigitizer[1]->setMeasY(true);
	}
	else if (svol.detectorId==33) {
	  m_gemDigitizer[2]->setPhysicalVolume(physVol);
	  m_gemDigitizer[2]->setBase(100,100);
	  m_gemDigitizer[2]->setSize(100);
	  m_gemDigitizer[2]->setPitch(0.260);
	  m_gemDigitizer[2]->setMeasY(true);
	}
	else if (svol.detectorId==34) {
	  m_gemDigitizer[3]->setPhysicalVolume(physVol);
	  m_gemDigitizer[3]->setBase(483.3,636.2);
	  m_gemDigitizer[3]->setSize(391);
	  m_gemDigitizer[3]->setPitch(1.260);
	  m_gemDigitizer[3]->setMeasY(false);
	}
	else if (svol.detectorId==35) {
	  m_gemDigitizer[4]->setPhysicalVolume(physVol);
	  m_gemDigitizer[4]->setBase(483.3,636.2);
	  m_gemDigitizer[4]->setSize(391);
	  m_gemDigitizer[4]->setPitch(1.260);
	  m_gemDigitizer[4]->setMeasY(false);
	}
	else if (svol.detectorId==36) {
	  m_gemDigitizer[5]->setPhysicalVolume(physVol);
	  m_gemDigitizer[5]->setBase(636.8,788.9);
	  m_gemDigitizer[5]->setSize(391);
	  m_gemDigitizer[5]->setPitch(1.660);
	  m_gemDigitizer[5]->setMeasY(false);
	}
	else if (svol.detectorId==37) {
	  m_gemDigitizer[6]->setPhysicalVolume(physVol);
	  m_gemDigitizer[6]->setBase(636.8,788.9);
	  m_gemDigitizer[6]->setSize(391);
	  m_gemDigitizer[6]->setPitch(1.660);
	  m_gemDigitizer[6]->setMeasY(false);
	}
	
      }
      else {
	std::cout << "ERROR: volume already present: " << m_activeVolumes[i] << std::endl;
      }   
      
    }
  } 
    
  
  G4LogicalVolume* volume =
    step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  
  G4VPhysicalVolume* ThisVol = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
  G4VPhysicalVolume* NextVol = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume();
  
  if (fDetEnterExitFlag) {
    
    // ########################
    
    // What enters Dummy0
    if (NextVol && ThisVol->GetName()==worldName && ( NextVol->GetName()=="Dummy0") ) {
      (runStepAction->GetVectorDummy0EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
      (runStepAction->GetVectorDummy0EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
      (runStepAction->GetVectorDummy0EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
      (runStepAction->GetVectorDummy0EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
      (runStepAction->GetVectorDummy0EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
      (runStepAction->GetVectorDummy0EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
      (runStepAction->GetVectorDummy0EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
      (runStepAction->GetVectorDummy0EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
      (runStepAction->GetVectorDummy0EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
      (runStepAction->GetVectorDummy0EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
      (runStepAction->GetVectorDummy0EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
    }
    
    // What enters Dummy1
    if (NextVol && ThisVol->GetName()==worldName && ( NextVol->GetName()=="Dummy1") ) {
      (runStepAction->GetVectorDummy1EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
      (runStepAction->GetVectorDummy1EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
      (runStepAction->GetVectorDummy1EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
      (runStepAction->GetVectorDummy1EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
      (runStepAction->GetVectorDummy1EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
      (runStepAction->GetVectorDummy1EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
      (runStepAction->GetVectorDummy1EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
      (runStepAction->GetVectorDummy1EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
      (runStepAction->GetVectorDummy1EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
      (runStepAction->GetVectorDummy1EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
      (runStepAction->GetVectorDummy1EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
    }
    // What enters Dummy2
    if (NextVol && ThisVol->GetName()==worldName && ( NextVol->GetName()=="Dummy2") ) {
      (runStepAction->GetVectorDummy2EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
      (runStepAction->GetVectorDummy2EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
      (runStepAction->GetVectorDummy2EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
      (runStepAction->GetVectorDummy2EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
      (runStepAction->GetVectorDummy2EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
      (runStepAction->GetVectorDummy2EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
      (runStepAction->GetVectorDummy2EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
      (runStepAction->GetVectorDummy2EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
      (runStepAction->GetVectorDummy2EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
      (runStepAction->GetVectorDummy2EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
      (runStepAction->GetVectorDummy2EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
    }
    // What enters Ce1
    if (NextVol && ThisVol->GetName()=="CaloTable1" && ( NextVol->GetName()=="Ce1") ) {
      (runStepAction->GetVectorCe1EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
      (runStepAction->GetVectorCe1EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
      (runStepAction->GetVectorCe1EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
      (runStepAction->GetVectorCe1EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
      (runStepAction->GetVectorCe1EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
      (runStepAction->GetVectorCe1EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
      (runStepAction->GetVectorCe1EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
      (runStepAction->GetVectorCe1EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
      (runStepAction->GetVectorCe1EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
      (runStepAction->GetVectorCe1EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
      (runStepAction->GetVectorCe1EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
    }
    // What enters Ce2
    if (NextVol && ThisVol->GetName()=="CaloTable2" && ( NextVol->GetName()=="Ce2") ) {
      (runStepAction->GetVectorCe2EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
      (runStepAction->GetVectorCe2EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
      (runStepAction->GetVectorCe2EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
      (runStepAction->GetVectorCe2EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
      (runStepAction->GetVectorCe2EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
      (runStepAction->GetVectorCe2EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
      (runStepAction->GetVectorCe2EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
      (runStepAction->GetVectorCe2EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
      (runStepAction->GetVectorCe2EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
      (runStepAction->GetVectorCe2EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
      (runStepAction->GetVectorCe2EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
    }
    // What enters S4
    if (NextVol && ThisVol->GetName()==worldName && ( NextVol->GetName()=="S4") ) {
      (runStepAction->GetVectorS4EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
      (runStepAction->GetVectorS4EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
      (runStepAction->GetVectorS4EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
      (runStepAction->GetVectorS4EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
      (runStepAction->GetVectorS4EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
      (runStepAction->GetVectorS4EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
      (runStepAction->GetVectorS4EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
      (runStepAction->GetVectorS4EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
      (runStepAction->GetVectorS4EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
      (runStepAction->GetVectorS4EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
      (runStepAction->GetVectorS4EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
    }
    // What enters S5
    if (NextVol && ThisVol->GetName()==worldName && ( NextVol->GetName()=="S5") ) {
      (runStepAction->GetVectorS5EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
      (runStepAction->GetVectorS5EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
      (runStepAction->GetVectorS5EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
      (runStepAction->GetVectorS5EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
      (runStepAction->GetVectorS5EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
      (runStepAction->GetVectorS5EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
      (runStepAction->GetVectorS5EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
      (runStepAction->GetVectorS5EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
      (runStepAction->GetVectorS5EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
      (runStepAction->GetVectorS5EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
      (runStepAction->GetVectorS5EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
    }
    // What enters S6
    if (NextVol && ThisVol->GetName()==worldName && ( NextVol->GetName()=="S6") ) {
      (runStepAction->GetVectorS6EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
      (runStepAction->GetVectorS6EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
      (runStepAction->GetVectorS6EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
      (runStepAction->GetVectorS6EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
      (runStepAction->GetVectorS6EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
      (runStepAction->GetVectorS6EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
      (runStepAction->GetVectorS6EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
      (runStepAction->GetVectorS6EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
      (runStepAction->GetVectorS6EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
      (runStepAction->GetVectorS6EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
      (runStepAction->GetVectorS6EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
    }
    // What enters S7
    if (NextVol && ThisVol->GetName()==worldName && ( NextVol->GetName()=="S7") ) {
      (runStepAction->GetVectorS7EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
      (runStepAction->GetVectorS7EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
      (runStepAction->GetVectorS7EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
      (runStepAction->GetVectorS7EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
      (runStepAction->GetVectorS7EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
      (runStepAction->GetVectorS7EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
      (runStepAction->GetVectorS7EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
      (runStepAction->GetVectorS7EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
      (runStepAction->GetVectorS7EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
      (runStepAction->GetVectorS7EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
      (runStepAction->GetVectorS7EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
    }
    
    // What enters T1
    if (NextVol && ThisVol->GetName()==worldName && ( NextVol->GetName()=="T1") ) {
      (runStepAction->GetVectorT1EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
      (runStepAction->GetVectorT1EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
      (runStepAction->GetVectorT1EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
      (runStepAction->GetVectorT1EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
      (runStepAction->GetVectorT1EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
      (runStepAction->GetVectorT1EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
      (runStepAction->GetVectorT1EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
      (runStepAction->GetVectorT1EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
      (runStepAction->GetVectorT1EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
      (runStepAction->GetVectorT1EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
      (runStepAction->GetVectorT1EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
      
    }
    // What enters T2
    if (NextVol && ThisVol->GetName()==worldName && ( NextVol->GetName()=="T2") ) {
      (runStepAction->GetVectorT2EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
      (runStepAction->GetVectorT2EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
      (runStepAction->GetVectorT2EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
      (runStepAction->GetVectorT2EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
      (runStepAction->GetVectorT2EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
      (runStepAction->GetVectorT2EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
      (runStepAction->GetVectorT2EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
      (runStepAction->GetVectorT2EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
      (runStepAction->GetVectorT2EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
      (runStepAction->GetVectorT2EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
      (runStepAction->GetVectorT2EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
    }
    // What enters T3
    if (NextVol && ThisVol->GetName()==worldName && ( NextVol->GetName()=="T3") ) {
      (runStepAction->GetVectorT3EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
      (runStepAction->GetVectorT3EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
      (runStepAction->GetVectorT3EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
      (runStepAction->GetVectorT3EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
      (runStepAction->GetVectorT3EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
      (runStepAction->GetVectorT3EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
      (runStepAction->GetVectorT3EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
      (runStepAction->GetVectorT3EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
      (runStepAction->GetVectorT3EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
      (runStepAction->GetVectorT3EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
      (runStepAction->GetVectorT3EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
    }
    // What enters T4
    if (NextVol && ThisVol->GetName()==worldName && ( NextVol->GetName()=="T4") ) {
      (runStepAction->GetVectorT4EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
      (runStepAction->GetVectorT4EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
      (runStepAction->GetVectorT4EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
      (runStepAction->GetVectorT4EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
      (runStepAction->GetVectorT4EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
      (runStepAction->GetVectorT4EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
      (runStepAction->GetVectorT4EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
      (runStepAction->GetVectorT4EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
      (runStepAction->GetVectorT4EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
      (runStepAction->GetVectorT4EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
      (runStepAction->GetVectorT4EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
    }
    // What enters T5
    if (NextVol && ThisVol->GetName()==worldName && ( NextVol->GetName()=="T5") ) {
      (runStepAction->GetVectorT5EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
      (runStepAction->GetVectorT5EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
      (runStepAction->GetVectorT5EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
      (runStepAction->GetVectorT5EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
      (runStepAction->GetVectorT5EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
      (runStepAction->GetVectorT5EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
      (runStepAction->GetVectorT5EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
      (runStepAction->GetVectorT5EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
      (runStepAction->GetVectorT5EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
      (runStepAction->GetVectorT5EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
      (runStepAction->GetVectorT5EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
    }
    // What enters T6
    if (NextVol && ThisVol->GetName()==worldName && ( NextVol->GetName()=="T6") ) {
      (runStepAction->GetVectorT6EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
      (runStepAction->GetVectorT6EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
      (runStepAction->GetVectorT6EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
      (runStepAction->GetVectorT6EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
      (runStepAction->GetVectorT6EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
      (runStepAction->GetVectorT6EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
      (runStepAction->GetVectorT6EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
      (runStepAction->GetVectorT6EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
      (runStepAction->GetVectorT6EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
      (runStepAction->GetVectorT6EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
      (runStepAction->GetVectorT6EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
    }
    
    
    // What enters Mu1
    if (NextVol && ThisVol->GetName()==worldName && ( NextVol->GetName()=="Mu1") ) {
      
      (runStepAction->GetVectorMu1EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
      (runStepAction->GetVectorMu1EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
      (runStepAction->GetVectorMu1EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
      (runStepAction->GetVectorMu1EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
      (runStepAction->GetVectorMu1EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
      (runStepAction->GetVectorMu1EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
      (runStepAction->GetVectorMu1EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
      (runStepAction->GetVectorMu1EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
      (runStepAction->GetVectorMu1EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
      (runStepAction->GetVectorMu1EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
      (runStepAction->GetVectorMu1EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
      (runStepAction->GetVectorMu1EnterCopyNb()).push_back(step->GetPostStepPoint()->GetTouchableHandle()->GetCopyNumber());
    }
    // What enters Mu2
    if (NextVol && ThisVol->GetName()==worldName && ( NextVol->GetName()=="Mu2") ) {
      (runStepAction->GetVectorMu2EnterEne()).push_back(step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/GeV);
      (runStepAction->GetVectorMu2EnterPart()).push_back(step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
      (runStepAction->GetVectorMu2EnterX()).push_back(step->GetPostStepPoint()->GetPosition().x()/cm);
      (runStepAction->GetVectorMu2EnterY()).push_back(step->GetPostStepPoint()->GetPosition().y()/cm);
      (runStepAction->GetVectorMu2EnterZ()).push_back(step->GetPostStepPoint()->GetPosition().z()/cm);
      (runStepAction->GetVectorMu2EnterVX()).push_back(step->GetTrack()->GetVertexPosition().x()/cm);
      (runStepAction->GetVectorMu2EnterVY()).push_back(step->GetTrack()->GetVertexPosition().y()/cm);
      (runStepAction->GetVectorMu2EnterVZ()).push_back(step->GetTrack()->GetVertexPosition().z()/cm);
      (runStepAction->GetVectorMu2EnterPX()).push_back(step->GetPostStepPoint()->GetMomentum().x()/GeV);
      (runStepAction->GetVectorMu2EnterPY()).push_back(step->GetPostStepPoint()->GetMomentum().y()/GeV);
      (runStepAction->GetVectorMu2EnterPZ()).push_back(step->GetPostStepPoint()->GetMomentum().z()/GeV);
      (runStepAction->GetVectorMu2EnterCopyNb()).push_back(step->GetPostStepPoint()->GetTouchableHandle()->GetCopyNumber());
    }
  }
  
  
  G4bool SHOW = false;
  G4bool dofill = false;
  G4int subdet=-1;
  G4int caloChannel=-1;
  G4int CopyNb=step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber();

  // find the correct subdetector ID
  for ( auto it : m_scoringVolumes ) {
    if ( volume == it.second.volume ) {
      subdet = it.second.detectorId;
      dofill=true;
      break;
    }
    /// if not found among the scoring volumes check the calo components
    for (unsigned int i=0 ; i<2 ; i++ ) {
      auto it_calo = m_caloChannelsMap[i].find(ThisVol->GetName());
      if ( it_calo != m_caloChannelsMap[i].end() ) {
	subdet = 51+i;
	caloChannel = it_calo->second;
      }
      auto it_calo_layer = m_caloLayersMap[i].find(ThisVol->GetName());
      if ( it_calo_layer != m_caloLayersMap[i].end() ) {
	CopyNb = it_calo_layer->second;
      }
    }
  }
  
  if (fStoreGammaConvDepFlag && NextVol) { //Like "subdet", but for PostStep volume
    G4LogicalVolume* Postvolume =	NextVol->GetLogicalVolume();
    G4int Postsubdet=0;
    
    // find the correct subdetector ID
    for ( auto it : m_scoringVolumes ) {
      if ( Postvolume == it.second.volume ) {
	Postsubdet = it.second.detectorId;
	break;
      }
    }
    
    
    G4VPhysicalVolume* physicalBend = G4PhysicalVolumeStore::GetInstance()->GetVolume("Mag");
    G4double zGammaConvCut=physicalBend->GetTranslation().z();
    
    // If we have a Gamma Conversion before magnet...
    if (step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding()==22 && step->GetPostStepPoint()->GetProcessDefinedStep() && step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() == "conv" && step->GetPostStepPoint()->GetPosition().z()<zGammaConvCut) {
      
      (runStepAction->GetVectorGammaConvX()).push_back((step->GetPostStepPoint()->GetPosition().x()/cm));
      (runStepAction->GetVectorGammaConvY()).push_back((step->GetPostStepPoint()->GetPosition().y()/cm));
      (runStepAction->GetVectorGammaConvZ()).push_back((step->GetPostStepPoint()->GetPosition().z()/cm));
      (runStepAction->GetVectorGammaConvEne()).push_back((step->GetPreStepPoint()->GetKineticEnergy()/GeV));
      (runStepAction->GetVectorGammaConvSubdet()).push_back(Postsubdet);
      
      
      //			G4Event* evt = G4EventManager::GetEventManager()->GetNonconstCurrentEvent();
      //			evt->KeepTheEvent();
      //			G4cout<<"Evt n: "<< evt->GetEventID() <<" Gamma conversion in world! z= "<< step->GetPostStepPoint()->GetPosition().z()/cm<<" Gamma EnePre= "<<step->GetPreStepPoint()->GetKineticEnergy()/GeV <<" PostSubdet= "<<Postsubdet <<" Viva? "<<step->GetTrack()->GetTrackStatus() <<G4endl;
    }
  }
  
#if 0
  if (subdet==61 && step->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber()>3) {
    G4Event* evt = G4EventManager::GetEventManager()->GetNonconstCurrentEvent();
    evt->KeepTheEvent();
  }
  
  if (subdet==64) {
    G4Event* evt = G4EventManager::GetEventManager()->GetNonconstCurrentEvent();
    evt->KeepTheEvent();
  }
#endif
  
  // ##############################################################################
  // ##################### TRIGGER LOGIC
  // ###############
#if 1
  //	fEventAction->SetNoCriteria(6);
  for (int ii=0; ii<(int)fTriggerLogic.size(); ii++)
    if (subdet==fTriggerLogic[ii]) fEventAction->GetShowCriteria(ii)=1;
  
  /*
    if (subdet==63 ) fEventAction->GetShowCriteria(0)=1;
    if (subdet>=42 && subdet <=42) fEventAction->GetShowCriteria(1)=1;
    if (subdet>=45 && subdet <=45) fEventAction->GetShowCriteria(2)=1;
    if (subdet==51) fEventAction->GetShowCriteria(3)=1;
    //	if (subdet==10) fEventAction->GetShowCriateria(4)=1;
    if (subdet==38) fEventAction->GetShowCriteria(4)=1;
    if (subdet==39) fEventAction->GetShowCriteria(5)=1;
  */
#endif
  /// ###############
  // ##############################################################################
    
  
  G4double DepEne=step->GetTotalEnergyDeposit()/GeV;
  G4int Pid=step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding();


  // ##############################################################################
  // ##################### CALORIMETER SCORING
  // ###############
  if (fStoreCaloEnDepFlag && ((subdet>=41 && subdet <=46) || subdet==51 || subdet==52 || subdet == 77)) {

    if ( caloChannel != -1 ) { 
      (runStepAction->GetCaloEnDep())[caloChannel]+=DepEne;
    }
    
  }

  /// ###############
  // ##############################################################################
  
  
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
	      //							(fEventAction->AddPbGlassCere(1)); //incremento di 1 il contatore di fotoni cerenkov
	    }
	    // se sono nel detector di Cerenkov
	    else if (subdet==80 && CerFotLambda>CerFotLambdaCut) {

	    }
	    //						G4cout<<"DEBUG Cerenkov!!! Energia fotone= "<<CerFotEne<<", lamda [um]= "<< CerFotLambda<<", subdet= "<<subdet<<  G4endl;
	  }
	}
      }
    }
  }
  
  
  //##################################################
  //##################################################
  //############ CENTRAL CORE OF SCORING #############
  //##################################################
  
  
  //-- store info
  //	if (dofill && ((step->GetPostStepPoint()->GetStepStatus()==fGeomBoundary)
  //				   || (step->GetPreStepPoint()->GetStepStatus()==fGeomBoundary)) && !(Pid==22 && step->GetPreStepPoint()->GetMomentum().mag()<EThr) ) { //If Output Cut required do not store photons under a certain energy
  //#### NORMAL
  //	if (dofill && ((step->GetPostStepPoint()->GetStepStatus()==fGeomBoundary) || (step->GetPreStepPoint()->GetStepStatus()==fGeomBoundary)) && (!fCutFlag || !(Pid==22 && step->GetPreStepPoint()->GetMomentum().mag()<fEThr) )) { //If Output Cut required do not store photons under a certain energy - Logic expression: A & B & !(!C || !(D & E) )
  //### FINE NORMAL
  
  //	ALL
  //	if (dofill  && subdet!=76  && subdet!=77  && subdet!=78 && (!fCutFlag || !(Pid==22 && step->GetPreStepPoint()->GetMomentum().mag()<fEThr) )) { //If Output Cut required do not store photons under a certain energy - Logic expression: A & B & !(!C || !(D & E) )
  
  /* //tentativo di capire perchè quando si usa generatore esterno l'informazione in GetPrimaryVertex è sempre relativa alla prima riga del file di dati esterni.. PACE!
     G4int temp=G4RunManager::GetRunManager()->GetCurrentEvent()->GetPrimaryVertex()->GetPrimary()->GetPDGcode();
     G4double tempEne=G4RunManager::GetRunManager()->GetCurrentEvent()->GetPrimaryVertex()->GetPrimary()->GetKineticEnergy();
     if (0&&temp!=13) G4cout<<"CIAO "<<temp<<G4endl;
     
     if (step->GetTrack()->GetParentID()==0 && step->GetTrack()->GetCurrentStepNumber()==1) G4cout<< "DEBUG ParentId="<< step->GetTrack()->GetParentID()<<" Part= "<<step->GetTrack()->GetDynamicParticle()->GetDefinition()->GetPDGEncoding()<<" Ene="<< step->GetTrack()->GetDynamicParticle()->GetKineticEnergy()/keV<<" temp= "<<temp<<" tempEne=" <<tempEne/keV<<G4endl;
  */
  
  
  // SOLO PRE/POST - PRE
  if (dofill && (step->GetPreStepPoint()->GetStepStatus()==fGeomBoundary) && (!fCutFlag || !(Pid==22 && step->GetPreStepPoint()->GetMomentum().mag()<fEThr*GeV) )) { //If Output Cut required do not store photons under a certain energy - Logic expression: A & B & !(!C || !(D & E) )
    
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
    
    if (step->GetTrack()->GetCreatorProcess()) pro = step->GetTrack()->GetCreatorProcess()->GetProcessSubType();
    //			if (Itrack!=1) { // different from gun particle
    xvertex = step->GetTrack()->GetVertexPosition();
    
    
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
    
    (runStepAction->GetCopyNb()).push_back(CopyNb);
    
    (runStepAction->GetIdp()).push_back(Idp);
    (runStepAction->GetIpar()).push_back(Ipar);
    (runStepAction->GetItrack()).push_back(Itrack);
    (runStepAction->GetTime()).push_back(time);
    (runStepAction->GetVectorX()).push_back(xsubdet.x()/mm);
    (runStepAction->GetVectorY()).push_back(xsubdet.y()/mm);
    (runStepAction->GetVectorZ()).push_back(xsubdet.z()/mm);
    (runStepAction->GetVectorP()).push_back(momentum.mag()/GeV);
    (runStepAction->GetVectorPX()).push_back(momentum.x()/GeV);
    (runStepAction->GetVectorPY()).push_back(momentum.y()/GeV);
    (runStepAction->GetVectorPZ()).push_back(momentum.z()/GeV);
    (runStepAction->GetVertexX()).push_back(xvertex.x()/mm);
    (runStepAction->GetVertexY()).push_back(xvertex.y()/mm);
    (runStepAction->GetVertexZ()).push_back(xvertex.z()/mm);
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
    
    /// here add the digitization block
    /// digitize and fill the ntuple
    bool digi = false;
    G4ThreeVector digitPos,digitPosErr;
    if ( (subdet >= 10 && subdet <= 12) || (subdet >=20 && subdet <=22 ) ) { 
      digi = m_siDigitizer->getPosition(xsubdet,0.0,digitPos,digitPosErr);
    }
    else if (subdet >= 31 && subdet<=37 ) { 
      int idig = subdet-31;
      digi = m_gemDigitizer[idig]->getPosition(xsubdet,0.0,digitPos,digitPosErr);
    }

    if ( digi ) {
      runStepAction->GetXDig().push_back(digitPos.x());
      runStepAction->GetYDig().push_back(digitPos.y());
      runStepAction->GetZDig().push_back(digitPos.z());
      runStepAction->GetXErrDig().push_back(digitPosErr.x());
      runStepAction->GetYErrDig().push_back(digitPosErr.y());
      runStepAction->GetZErrDig().push_back(digitPosErr.z());
      runStepAction->GetDigSubdet().push_back(subdet);
      /// get the corresponding hit index
      int hitIndex = runStepAction->GetStep().size()-1;
      runStepAction->GetDigHitIndex().push_back(hitIndex);
    }
    
   
    
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
  
  
}
