#ifndef B1SteppingAction_h
#define B1SteppingAction_h 1
#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include <vector>
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolume.hh"
#include "SiDigitizer.hh"
#include "GEMDigitizer.hh"
#include <map>

class B1EventAction;
class B1RunAction;

struct ScoringVolume {

  G4LogicalVolume* volume;
  std::string name;
  int detectorId;
  
};

typedef std::map<std::string,ScoringVolume> ScoringVolumesMap;

/// Stepping action class

class B1SteppingAction : public G4UserSteppingAction
{
public:
  B1SteppingAction(B1EventAction* eventAction, B1RunAction* runAction, G4bool StoreCaloEnDepFlag, G4bool StoreGammaConvDepFlag, G4double EThr, const std::map<G4int,G4int> & ChannelMap, G4bool DetEnterExitFlag, const std::vector<G4int>  & TriggerLogic, G4bool Aug2018Flag);
  virtual ~B1SteppingAction();
  // method from the base class
  virtual void UserSteppingAction(const G4Step*);
  
private:
  B1EventAction* fEventAction;
  B1RunAction* runStepAction;

  std::vector<std::string> m_activeVolumes;
  std::vector<int> m_detectorId;
  ScoringVolumesMap m_scoringVolumes;
  
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
  /// digitizer of each gem
  GEMDigitizer* m_gemDigitizer[7];
  
  
};

#endif
