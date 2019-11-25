#include "B1StackingAction.hh"
#include "HistoManager.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "B1RunAction.hh"
#include "B1EventAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalVolumeStore.hh"

B1StackingAction::B1StackingAction(B1EventAction* eventAction, B1RunAction * runAction, G4bool StoreGammaConvDepFlag)
:G4UserStackingAction(),
feventAction(eventAction),
frunAction(runAction),
fStoreGammaConvDepFlag(StoreGammaConvDepFlag)
{ }

B1StackingAction::~B1StackingAction()
{ }

G4ClassificationOfNewTrack B1StackingAction::ClassifyNewTrack(const G4Track* atrack)
{
// if (atrack->GetParentID() == 0 && atrack->GetDynamicParticle()->GetDefinition()->GetPDGEncoding() == -11 && atrack->GetVolume() != 0 ) {
// if (atrack->GetVolume()->GetName() == "Mu1" || atrack->GetVolume()->GetName() == "Mu2" ) {
//    G4cout << " trovato positrone " << atrack->GetParentID() << " " <<  atrack->GetVolume() << G4endl;
// 	}
// 	}
	if (atrack->GetParentID() == 0 && atrack->GetCurrentStepNumber()==0) { //modified by collamaf on 2017.12.29 - If is a new Primary particle - used to save info on primaries even if red by external file!
																																				 // on 2018.02.12 added StepNumberCheck to avoid counting here also new particles created thereafter (eg optical photons)
		
		frunAction->GetBeamInfoX().push_back(atrack->GetPosition().x()/mm);
		frunAction->GetBeamInfoY().push_back(atrack->GetPosition().y()/mm);
		frunAction->GetBeamInfoZ().push_back(atrack->GetPosition().z()/mm);
		frunAction->GetBeamInfoCX().push_back(atrack->GetMomentumDirection().x());
		frunAction->GetBeamInfoCY().push_back(atrack->GetMomentumDirection().y());
		frunAction->GetBeamInfoCZ().push_back(atrack->GetMomentumDirection().z());
		frunAction->GetBeamInfoEne().push_back(atrack->GetKineticEnergy()/GeV);
		frunAction->GetBeamInfoPart().push_back(atrack->GetDynamicParticle()->GetDefinition()->GetPDGEncoding());
		
		return fUrgent;
	}
	
	G4String process = "";
	if (atrack->GetCreatorProcess()->GetProcessName()) process=atrack->GetCreatorProcess()->GetProcessName();
	G4int Idp = atrack->GetDynamicParticle()->GetDefinition()->GetPDGEncoding();
	
	//Retrieve position of Magnet since we are interested in gamma converting before it
	G4VPhysicalVolume* physicalBend = G4PhysicalVolumeStore::GetInstance()->GetVolume("Mag");
	G4double zGammaConvCut=physicalBend->GetTranslation().z();
	
	// Save info on e+e- created due to gamma conversion in world volume
	if (fStoreGammaConvDepFlag && atrack->GetCurrentStepNumber()==0 && process=="conv" && atrack->GetPosition().z()<zGammaConvCut) {
		if (Idp==11) {
			(frunAction->GetVectorGammaConvEneEle()).push_back((atrack->GetKineticEnergy()/GeV));
		}
		if (Idp==-11) {
			(frunAction->GetVectorGammaConvEnePos()).push_back((atrack->GetKineticEnergy()/GeV));
		}
	}
	return fUrgent;
}

