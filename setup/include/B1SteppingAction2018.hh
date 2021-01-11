#ifndef B1SteppingAction2018_h
#define B1SteppingAction2018_h 1
#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include <vector>
#include "G4SystemOfUnits.hh"
#include "SiDigitizer.hh"
#include <map>


class B1EventAction;
class B1RunAction;
class G4LogicalVolume;

/// Stepping action class

class B1SteppingAction2018 : public G4UserSteppingAction
{
public:
  B1SteppingAction2018(B1EventAction* eventAction, B1RunAction* runAction, G4bool StoreCaloEnDepFlag, G4bool StoreGammaConvDepFlag, G4double EThr, const std::map<G4int,G4int> & ChannelMap, G4bool DetEnterExitFlag, const std::vector<G4int>  & TriggerLogic, G4bool Aug2018Flag);
  virtual ~B1SteppingAction2018();
  // method from the base class
  virtual void UserSteppingAction(const G4Step*);
  
private:
  B1EventAction* fEventAction;
  B1RunAction* runStepAction;
  
  G4LogicalVolume*  fScoringVolume_S1;
  G4LogicalVolume*  fScoringVolume_T1;
  G4LogicalVolume*  fScoringVolume_T2;
  G4LogicalVolume*  fScoringVolume_T3;
  G4LogicalVolume*  fScoringVolume_Targ;
  G4LogicalVolume*  fScoringVolume_Dummy;
  G4LogicalVolume*  fScoringVolume_C0;
  G4LogicalVolume*  fScoringVolume_T4;
  G4LogicalVolume*  fScoringVolume_T5;
  G4LogicalVolume*  fScoringVolume_T6;
  G4LogicalVolume*  fScoringVolume_C1;
  G4LogicalVolume*  fScoringVolume_C2;
  G4LogicalVolume*  fScoringVolume_C3;
  G4LogicalVolume*  fScoringVolume_C4;
  G4LogicalVolume*  fScoringVolume_C5;
  G4LogicalVolume*  fScoringVolume_C6;
  G4LogicalVolume*  fScoringVolume_C7;
  G4LogicalVolume*  fScoringVolume_S2;
  G4LogicalVolume*  fScoringVolume_S3;
  G4LogicalVolume*  fScoringVolume_S4;
  G4LogicalVolume*  fScoringVolume_S5;
  G4LogicalVolume*  fScoringVolume_S6;
  G4LogicalVolume*  fScoringVolume_S7;
  G4LogicalVolume*  fScoringVolume_Pb1a;
  G4LogicalVolume*  fScoringVolume_Pb1b;
  G4LogicalVolume*  fScoringVolume_Pb1c;
  G4LogicalVolume*  fScoringVolume_Pb2a;
  G4LogicalVolume*  fScoringVolume_Pb2b;
  G4LogicalVolume*  fScoringVolume_Pb2c;
  G4LogicalVolume*  fScoringVolume_PbG;
  G4LogicalVolume*  fScoringVolume_CeH;
  G4LogicalVolume*  fScoringVolume_CeV;
  G4LogicalVolume*  fScoringVolume_CeVtilt;
  G4LogicalVolume*  fScoringVolume_Mu1;
  G4LogicalVolume*  fScoringVolume_Mu2;
  
  G4bool fStoreCaloEnDepFlag;
  G4bool fStoreGammaConvDepFlag;
  
  G4double fEThr;
  G4bool fCutFlag=false;
  
  G4bool fAug2018Flag;
  
  std::map<G4int,G4int> fChannelMap;
  G4bool fDetEnterExitFlag;
  std::vector<G4int>  fTriggerLogic;
  
  G4bool m_readGeoFromFile;


  // set of the digitizers
  SiDigitizer* m_siDigitizer;
  
  
};

#endif
