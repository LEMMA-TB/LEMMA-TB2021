#ifndef B1SteppingAction_h
#define B1SteppingAction_h 1
#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include <vector>
#include "G4SystemOfUnits.hh"

class B1EventAction;
class B1RunAction;
class G4LogicalVolume;

/// Stepping action class

class B1SteppingAction : public G4UserSteppingAction
{
public:
	B1SteppingAction(B1EventAction* eventAction, B1RunAction* runAction, G4bool StoreCaloEnDepFlag, G4double EThr, const std::vector<G4int> & ChannelMap, G4bool DetEnterExitFlag);
	virtual ~B1SteppingAction();
	// method from the base class
	virtual void UserSteppingAction(const G4Step*);
	
private:
	B1EventAction* fEventAction;
	B1RunAction* runStepAction;

	G4LogicalVolume*  fScoringVolume_S1;
	G4LogicalVolume*  fScoringVolume_T1;
	G4LogicalVolume*  fScoringVolume_T2;
	G4LogicalVolume*  fScoringVolume_Targ;
	G4LogicalVolume*  fScoringVolume_C0;
	G4LogicalVolume*  fScoringVolume_C1;
	G4LogicalVolume*  fScoringVolume_C2;
	G4LogicalVolume*  fScoringVolume_C3;
	G4LogicalVolume*  fScoringVolume_C4;
	G4LogicalVolume*  fScoringVolume_C5;
	G4LogicalVolume*  fScoringVolume_C6;
	G4LogicalVolume*  fScoringVolume_C7;
	G4LogicalVolume*  fScoringVolume_S2;
	G4LogicalVolume*  fScoringVolume_S3;
	G4LogicalVolume*  fScoringVolume_Pb1a;
	G4LogicalVolume*  fScoringVolume_Pb1b;
	G4LogicalVolume*  fScoringVolume_Pb1c;
	G4LogicalVolume*  fScoringVolume_Pb2a;
	G4LogicalVolume*  fScoringVolume_Pb2b;
	G4LogicalVolume*  fScoringVolume_Pb2c;
	G4LogicalVolume*  fScoringVolume_Ce1;
	G4LogicalVolume*  fScoringVolume_Ce1tilt;
	G4LogicalVolume*  fScoringVolume_Ce2;
	G4LogicalVolume*  fScoringVolume_Mu1;
	G4LogicalVolume*  fScoringVolume_Mu2;

	G4bool fStoreCaloEnDepFlag;
	
	
	G4double fEThr;
	G4bool fCutFlag=false;
	
//	static const int ChannelMapRaw[]={410, 420, 430, 440, 450, 460, 510, 511, 512, 513, 514, 515, 520, 521, 522, 523, 524, 525};
//	std::vector<int> ChannelMap(ChannelMapRaw, ChannelMapRaw + sizeof(ChannelMapRaw)/sizeof(ChannelMapRaw[0]));
//	std::vector<int> ChannelMap={4100, 4200, 4300, 4400, 4500, 4600, 5100, 5101, 5102, 5103, 5104, 5105, 5200, 5201, 5202, 5203, 5204, 5205};
	std::vector<int> fChannelMap;
	G4bool fDetEnterExitFlag;
};

#endif
