#ifndef B1DetectorConstruction_h
#define B1DetectorConstruction_h 1
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4Cache.hh"
#include "G4MagneticField.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class PurgMagTabulatedField3D;

class B1DetectorConstruction : public G4VUserDetectorConstruction
{
public:
	B1DetectorConstruction(G4bool TargetFlag, G4bool FlipFieldFlag, G4double MagField, G4double GeometryZoom, G4bool AllVacFlag);
	virtual ~B1DetectorConstruction();
	virtual G4VPhysicalVolume* Construct();
	virtual void ConstructSDandField();

	G4LogicalVolume* GetScoringVolume_S1() const { return fScoringVolume_S1; }
	G4LogicalVolume* GetScoringVolume_T1() const { return fScoringVolume_T1; }
	G4LogicalVolume* GetScoringVolume_T2() const { return fScoringVolume_T2; }
	G4LogicalVolume* GetScoringVolume_Targ()   const { return fScoringVolume_Targ; }
	G4LogicalVolume* GetScoringVolume_C0() const { return fScoringVolume_C0; }
	G4LogicalVolume* GetScoringVolume_C1() const { return fScoringVolume_C1; }
	G4LogicalVolume* GetScoringVolume_C2() const { return fScoringVolume_C2; }
	G4LogicalVolume* GetScoringVolume_C3() const { return fScoringVolume_C3; }
	G4LogicalVolume* GetScoringVolume_C4() const { return fScoringVolume_C4; }
	G4LogicalVolume* GetScoringVolume_C5() const { return fScoringVolume_C5; }
	G4LogicalVolume* GetScoringVolume_C6() const { return fScoringVolume_C6; }
	G4LogicalVolume* GetScoringVolume_C7() const { return fScoringVolume_C7; }
	G4LogicalVolume* GetScoringVolume_S2() const { return fScoringVolume_S2; }
	G4LogicalVolume* GetScoringVolume_S3() const { return fScoringVolume_S3; }
	G4LogicalVolume* GetScoringVolume_S4() const { return fScoringVolume_S4; }
	G4LogicalVolume* GetScoringVolume_S5() const { return fScoringVolume_S5; }
	G4LogicalVolume* GetScoringVolume_S6() const { return fScoringVolume_S6; }
	G4LogicalVolume* GetScoringVolume_S7() const { return fScoringVolume_S7; }
	G4LogicalVolume* GetScoringVolume_Pb1a() const { return fScoringVolume_Pb1a; }
	G4LogicalVolume* GetScoringVolume_Pb1b() const { return fScoringVolume_Pb1b; }
	G4LogicalVolume* GetScoringVolume_Pb1c() const { return fScoringVolume_Pb1c; }
	G4LogicalVolume* GetScoringVolume_Pb2a() const { return fScoringVolume_Pb2a; }
	G4LogicalVolume* GetScoringVolume_Pb2b() const { return fScoringVolume_Pb2b; }
	G4LogicalVolume* GetScoringVolume_Pb2c() const { return fScoringVolume_Pb2c; }
	G4LogicalVolume* GetScoringVolume_PbG() const { return fScoringVolume_PbG; }
	G4LogicalVolume* GetScoringVolume_CeH() const { return fScoringVolume_CeH; }
	G4LogicalVolume* GetScoringVolume_CeV() const { return fScoringVolume_CeV; }
	G4LogicalVolume* GetScoringVolume_CeVtilt() const { return fScoringVolume_CeVtilt; }
	G4LogicalVolume* GetScoringVolume_Mu1() const { return fScoringVolume_Mu1; }
	G4LogicalVolume* GetScoringVolume_Mu2() const { return fScoringVolume_Mu2; }
	G4bool GetHorsaVersaFlip() {return HorsaVersaFlip;}


protected:
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
	G4LogicalVolume*	fScoringVolume_CeVtilt;
	G4LogicalVolume*  fScoringVolume_Mu1;
	G4LogicalVolume*  fScoringVolume_Mu2;



private:
	G4bool channeling;
	G4String ctype;
//	G4bool fCalibMuMBeamFlag;
//	G4bool fElectronBeamFlag;
	G4bool fTargetFlag;
	G4bool fFlipFieldFlag;
	G4double fMagField;
	G4double fGeometryZoom;
	G4bool fAllVacFlag;
	G4bool HorsaVersaFlip=false;

public:
	void SetChanneling(bool aBool, G4String aString) {
		channeling=aBool;
		ctype=aString;};
	G4bool GetChanneling() {return channeling;};
	G4Cache<G4MagneticField*> fField;  //pointer to the thread-local fields
	
};

#endif
