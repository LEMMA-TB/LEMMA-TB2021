#include "B1DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Material.hh"
#include "G4PVReplica.hh"
#include <G4UIcommand.hh>
#include <G4String.hh>
#include "G4CrystalExtension.hh"
#include "G4ExtendedMaterial.hh"
#include "G4LogicalCrystalVolume.hh"
#include "G4ChannelingMaterialData.hh"
#include "G4ChannelingOptrMultiParticleChangeCrossSection.hh"
#include "PurgMagTabulatedField3D.hh"
#include "G4LogicalVolumeStore.hh"
//------------------------------
//#include "G4PhysicalVolumeStore.hh"
#include "G4RegionStore.hh"
#include <G4Region.hh>
#include "G4ProductionCuts.hh"
//------------------------------
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4Transform3D.hh"
#include <G4ChordFinder.hh>
#include "G4PhysicalVolumeStore.hh"
#include "G4VPhysicalVolume.hh"
#include "G4SubtractionSolid.hh"


B1DetectorConstruction::B1DetectorConstruction(G4bool TargetFlag, G4bool FlipFieldFlag, G4double MagField, G4double GeometryZoom, G4bool AllVacFlag)
: G4VUserDetectorConstruction(),
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
fScoringVolume_S4(0),
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
fTargetFlag(TargetFlag),
fFlipFieldFlag(FlipFieldFlag),
fMagField(MagField),
fGeometryZoom(GeometryZoom),
fAllVacFlag(AllVacFlag)
{}


B1DetectorConstruction::~B1DetectorConstruction()
{}


G4VPhysicalVolume* B1DetectorConstruction::Construct(){
	
	// =============================
	// Detector parameters and size
	// =============================
	
	//--> WORLD:
	G4double world_sizeX = 8*m;
	G4double world_sizeY = 8*m;
	G4double world_sizeZ = 80*m;
	
	//--> Si Telescopes (T-C):
	G4double ZoomFactor=fGeometryZoom;
	G4double T1_sizeX = ZoomFactor*1.9*cm;
	G4double T1_sizeY = ZoomFactor*1.9*cm;
	G4double T1_sizeZ = 0.6*mm;
	
	G4double T2_sizeX = ZoomFactor*1.9*cm;
	G4double T2_sizeY = ZoomFactor*1.9*cm;
	G4double T2_sizeZ = 0.6*mm;
	
	G4double C0_sizeX = ZoomFactor*9.3*cm;
	G4double C0_sizeY = ZoomFactor*9.3*cm;
	G4double C0_sizeZ = 0.8*mm;
	
	G4double C1_sizeX = ZoomFactor*9.3*cm;
	G4double C1_sizeY = ZoomFactor*9.3*cm;
	G4double C1_sizeZ = 0.8*mm;
	
	G4double C2_sizeX = ZoomFactor*8*cm;
	G4double C2_sizeY = ZoomFactor*8*cm;
	G4double C2_sizeZ = 1.*mm;
	
	G4double C3_sizeX = ZoomFactor*8*cm;
	G4double C3_sizeY = ZoomFactor*8*cm;
	G4double C3_sizeZ = 1.*mm;
	
	G4double C4_sizeX = ZoomFactor*9.3*cm;
	G4double C4_sizeY = ZoomFactor*9.3*cm;
	G4double C4_sizeZ = 0.8*mm;
	
	G4double C5_sizeX = ZoomFactor*9.3*cm;
	G4double C5_sizeY = ZoomFactor*9.3*cm;
	G4double C5_sizeZ = 0.8*mm;
	
	G4double C6_sizeX = ZoomFactor*9*cm;
	G4double C6_sizeY = ZoomFactor*9*cm;
	G4double C6_sizeZ = 1*mm;
	G4double C6_DistComp=1*mm;
	
	G4double C7_sizeX = ZoomFactor*9*cm;
	G4double C7_sizeY = ZoomFactor*9*cm;
	G4double C7_sizeZ = 1*mm;
	G4double C7_DistComp=1*mm;
	
	
	//--> Be amorphous crystal target:
	G4double target_R = 2.5*cm;
	G4double target_Z = 60*mm; //was "30" till 2017.12.29
	
	//--> dipole magnet
	G4double Mag_R = 100.*cm;
	G4double Mag_sizeY = 40.*cm;
	G4double startAngle = 0.*deg;
	G4double spanningAngle = 360.*deg;
	
	//--> Beam Pipes
	G4double BP1_R = 10*cm;
	G4double BP1_sizeZ = 220*cm;
	G4double BP2_R = 10*cm;
	G4double BP2_sizeZ = 758*cm; //was 800
	G4double BP_AluThickness=5*mm;
	
	// Scintillator A behind T1
	G4double ScintA_sizeX = ZoomFactor*10*cm;
	G4double ScintA_sizeY = ZoomFactor*10*cm;
	G4double ScintA_sizeZ = 1*cm;
	
	// Scintillator B behind C4C5
	G4double ScintB_sizeX = ZoomFactor*10*cm;
	G4double ScintB_sizeY = ZoomFactor*10*cm;
	G4double ScintB_sizeZ = 1*cm;
	
	// Scintillator B behind C4C5
	G4double ScintC_sizeX = ZoomFactor*31*cm;
	G4double ScintC_sizeY = ZoomFactor*15*cm;
	G4double ScintC_sizeZ = 1*cm;
	
	
	// Lead Glass :
	G4double LeadGlass_sizeX = 11.5*cm;
	G4double LeadGlass_sizeY = 11.5*cm;
	G4double LeadGlass_sizeZ = 37*cm;
	
	G4double LeadGlass_sizeXt = 11.5*cm; //10.5 for trapezoid
	G4double LeadGlass_sizeYt = 11.5*cm;
	G4double LeadGlass_sizeXb = 11.5*cm;
	G4double LeadGlass_sizeYb = 11.5*cm;
	
	// Cerenkov counter and its various elements:
	G4double Cerenkov_sizeX = 30*cm;
	G4double Cerenkov_sizeY = 30*cm;
	G4double Cerenkov_sizeZ = 891.6*mm; //was 86.6
	G4double Cerenkov_AluZ = 4*mm;
	G4double Cerenkov_SiOX = 11*2.54*cm; //8 inches
	G4double Cerenkov_SiOZ = 2.54*cm; //1 inch
	G4double Cerenkov_SiOY = Cerenkov_SiOZ;
	G4double Cerenkov_SiOXtilt = 2.54*cm; //1 inch
	G4double Cerenkov_SiOZtilt = 2.54*cm; //1 inch
	G4double Cerenkov_SiOYtilt = 3*2.54*cm; //3 inches
	G4double Cerenkov_DistAluFirst=45*mm;
	G4double Cerenkov_DistFirst=4*mm;
	G4double Cerenkov_DistAroundSiO=2.4*mm;
	G4double Cerenkov_Wx=11*25.4*mm; //tungsten blocks size
	G4double Cerenkov_Wy=3*25.4*mm;
	G4double Cerenkov_Wz=10*mm;
	
	//New Muon Chambers:
	G4double Mu_sizeX=70*cm; //was 65 until 2018.05.11 - 73.7, 42.5cm dist +4 +4 morte
	G4double Mu_sizeY=84*cm;
	G4double Mu_sizeZ=1.3*cm; //?? 1.3 single layer
	G4double Mu_gapZ=77*cm; //was 34.6 cm before TB
	G4double Mu_distX=47*cm;
	G4double Mu_deadX=1*cm;
	G4double MuLatShield_sizeX=10*cm;
	G4double MuLatShield_sizeY=100*cm;
	G4double MuLatShield_sizeZ=40*cm;
	
	//Calorimeter holding table:
	G4double CaloTable1_sizeX=80*cm;
	G4double CaloTable2_sizeX=60*cm;
	G4double CaloTable_sizeY=Mu_sizeY;
	G4double CaloTable_sizeZ=140*cm; //actually is 160, but who cares since this one is not the physical!
	
	// Distances and offsets
	G4double DistPbCe=10*cm;
	G4double XOffSetLeadGlass=1.2*cm;
	//	G4double XOffSetShield2=15*cm; //towards center
	G4double XOffSetC6=C6_sizeX/3.;
	G4double YOffSetC6=C6_sizeY/2.;
	G4double Mu_offsetX=0*cm; //total offset of the MuChamber structure
	G4double Mu_shiftX=0*2*cm; //symmetrical: Mu1 towards up, Mu2 towards down
	G4double Mu2_shiftX=4*cm;
	G4double CaloTable_centerOffset=10*cm;
	
	// shield wall:
	G4double shield_sizeX = 1.62/2.*m;
	G4double shield_sizeY = 0.8*m;
	G4double shield_sizeZ = 0.4*m;
	
	// ============
	//   positions - OF CENTERS
	// ============
	
	G4double xT1=0*cm; //Det 10
	G4double xBP1=0*cm;
	G4double xT2=0*cm; //Det 20
	G4double xTarg=0*cm; //Be target
	G4double xC0=0*cm; //Det
	G4double xBP2=0*cm; //Det
	G4double xC1=0*cm; //Det
	G4double xMag=0*cm; //Det
	G4double xC2=8*cm; //Det //position from Tommaso was 8 up to 11-lug-18 (before change in B) - 7 if B=1.62T - 8 if Current=600
	G4double xC3=-xC2; //Det
	G4double xC4=14*cm; //Det //position from Tommaso was 16 up to 11-lug-18 (before change in B) - 14 if B=1.62T - 15 if current=600
	G4double xC5=-xC4; //Det
	G4double xC6=21*cm+XOffSetC6; //Det //position from Tommaso was 22 up to 11-lug-18 (before change in B) - 19 if B=1.62T - 22 if current=600
	G4double xC7=-xC6; //Det
	G4double xS2=22*cm;
	G4double xPb1a=XOffSetLeadGlass+-LeadGlass_sizeX-CaloTable_centerOffset; //Det
	G4double xPb2a=-xPb1a; //Det
	G4double xPb1b=XOffSetLeadGlass+0*cm-CaloTable_centerOffset; //Det
	G4double xPb2b=-xPb1b; //Det
	G4double xPb1c=XOffSetLeadGlass+LeadGlass_sizeX-CaloTable_centerOffset; //Det
	G4double xPb2c=-xPb1c; //Det
	G4double xCe1=0-CaloTable_centerOffset; //Det
	G4double xCe2=-xCe1; //Det
											 //	G4double xMu1=53*cm; //Det - was 48 up to 06-07-2018, was 37 up to 11-lug-18 (before change in B)
											 //	G4double xMu2=-xMu1; //Det
	G4double xMu1=Mu_offsetX+Mu_distX/2.+Mu_deadX+ Mu_sizeX/2.-Mu_shiftX;
	G4double xMu2=Mu_offsetX-Mu_distX/2.-Mu_deadX- Mu_sizeX/2.+Mu_shiftX; //Det
	G4double xCaloTable1=30.8*cm+CaloTable_centerOffset+1*cm; //Det - Was 42 up to 2018.07.04, 34 before moving forward calos
	G4double xCaloTable2=-xCaloTable1; //Det
	G4double xMuLatShield1=xMu1-Mu_sizeX/2.-MuLatShield_sizeX/2.;
	G4double xMuLatShield2=-xMuLatShield1;
	G4double xShield1=12*cm+shield_sizeX/2.; //!!!! number is distance edge-central beam axis //I wanted 27
	G4double xShield2=-28.3*cm-shield_sizeX/2.; //I wanted 10
	G4double xS4=xMu1-Mu_sizeX/2.+ -1*cm+ScintC_sizeX/2.;

	if (ZoomFactor>1) {
		xC2=C2_sizeX/2.;
		xC3=-C3_sizeX/2.;
		xC4=C4_sizeX/2.;
		xC5=-C5_sizeX/2.;
		xC6=2*C6_sizeX/2.;
		xC7=-2*C7_sizeX/2.;
	}
	
	
	G4double yT1=0*cm; //Det 10
	G4double yBP1=0*cm; //Det
	G4double yT2=0*cm; //Det 20
	G4double yTarg=0*cm; //Be target
	G4double yC0=0*cm; //Det
	G4double yBP2=0*cm; //Det
	G4double yC1=0*cm; //Det
	G4double yMag=0*cm; //Det
	G4double yC2=0*cm; //Det
	G4double yC3=yC2; //Det
	G4double yC4=0*cm; //Det
	G4double yC5=yC4; //Det
	G4double yC6=0*cm+YOffSetC6; //Det
	G4double yC7=yC6; //Det
	G4double yS4=0*cm;
	G4double yPb1a=0*cm; //Det
	G4double yPb2a=yPb1a; //Det
	G4double yPb1b=0*cm; //Det
	G4double yPb2b=yPb1b; //Det
	G4double yPb1c=0*cm; //Det
	G4double yPb2c=yPb1c; //Det
	G4double yCe1=0*cm; //Det
	G4double yCe2=yCe1; //Det
	G4double yMu1=0*cm; //Det
	G4double yMu2=yMu1; //Det
	G4double yMuLatShield1=0*cm;
	G4double yMuLatShield2=0*cm;
	G4double yCaloTable1=0; //Det
	G4double yCaloTable2=-yCaloTable1; //Det
	G4double yShield1=0;
	G4double yShield2=0;
	
	
	G4double zT1=84.6*cm; //Det 10
	G4double zBP1=220*cm; //Det
	G4double zT2=444.5*cm; //Det 20
	G4double zTarg=453.5*cm; //Be target
	G4double zC0=569.5*cm; //Det
	G4double zBP2=1000*cm; //Det
	G4double zC1=1526.2*cm; //Det - was 1500 until 2018-07-12 but is the exact border of the table -> 1510
	G4double zMag=1719.3*cm; //Det
	G4double zC2=1880.3*cm; //Det - was 1780 until 2018-07-12 but is the exact border of the table -> 1790
	G4double zC3=zC2; //Det
	G4double zC4=2002.6*cm; //Det TBC
	G4double zC5=zC4; //Det
	G4double zC6=2134.0*cm; //Det - was 2050 until 2018-07-12 but there is still room in the platform -> 2080
	G4double zC7=zC6; //Det
	G4double zPb1a=-CaloTable_sizeZ/2. +LeadGlass_sizeZ/2.; //Det
	G4double zPb2a=zPb1a; //Det
	G4double zPb1b=-CaloTable_sizeZ/2. +LeadGlass_sizeZ/2.; //Det
	G4double zPb2b=zPb1b; //Det
	G4double zPb1c=-CaloTable_sizeZ/2. +LeadGlass_sizeZ/2.; //Det
	G4double zPb2c=zPb1c; //Det
	G4double zPbG=35.95*m;
	G4double zCe1=-CaloTable_sizeZ/2. +LeadGlass_sizeZ + Cerenkov_sizeZ/2. + DistPbCe; //Det
	G4double zCe2=zCe1; //Det
	G4double ZCaloTableStart=2150*cm+10.8*cm; //was 2220 until 2018-07-12, but we need space for concrete walle before chambers, 2160 is good if 40cm of shield is enough, 2115, 2160 up to 2018.08.14
	G4double zCaloTable=ZCaloTableStart+CaloTable_sizeZ/2.; //Det The table starts at 2220
	G4double zMu1=2373.6*cm; //2383.65 Det =was 23656.5 before TB - was zCaloTable+CaloTable_sizeZ/2.+Mu_sizeZ/2.+DistTableMu
	G4double zMu2=zMu1; //Det
	G4double zMuLatShield1=zMu1+MuLatShield_sizeZ/2.;
	G4double zMuLatShield2=zMuLatShield1;
	G4double zShield1=2327.5*cm+shield_sizeZ/2.;
	G4double zShield2=zShield1;
	G4double zS4=zMu1+Mu_sizeZ*4+20.8*cm;
	
	// ============
	//   Positioning Vectors
	// ============
	
	G4ThreeVector posT1  = G4ThreeVector(xT1,yT1,zT1); // Subdet
	G4ThreeVector posS1  = G4ThreeVector(xT1,yT1,zT1-ScintA_sizeZ/2-0.5*cm); // Subdet
	G4ThreeVector posBP1  = G4ThreeVector(xBP1,yBP1,zBP1); // Subdet
	G4ThreeVector posT2  = G4ThreeVector(xT2,yT2,zT2); // Subdet
	G4ThreeVector posTarg  = G4ThreeVector(xTarg,yTarg,zTarg); // Subdet
	G4ThreeVector posC0  = G4ThreeVector(xC0,yC0,zC0); // Subdet
	G4ThreeVector posBP2  = G4ThreeVector(xBP2,yBP2,zBP2); // Subdet
	G4ThreeVector posC1  = G4ThreeVector(xC1,yC1,zC1); // Subdet
	G4ThreeVector posMag  = G4ThreeVector(xMag,yMag,zMag); // Subdet
	G4ThreeVector posC2  = G4ThreeVector(xC2,yC2,zC2); // Subdet
	G4ThreeVector posC3  = G4ThreeVector(xC3,yC3,zC3); // Subdet
	G4ThreeVector posC4  = G4ThreeVector(xC4,yC4,zC4); // Subdet
	G4ThreeVector posC5  = G4ThreeVector(xC5,yC5,zC5); // Subdet
	G4ThreeVector posC6  = G4ThreeVector(xC6,yC6,zC6); // Subdet
	G4ThreeVector posC6a  = G4ThreeVector(xC6+C6_DistComp/2+C6_sizeX/2.,yC6+C6_DistComp/2+C6_sizeY/2.,zC6); // Subdet
	G4ThreeVector posC6b  = G4ThreeVector(xC6-C6_DistComp/2-C6_sizeX/2.,yC6+C6_DistComp/2+C6_sizeY/2.,zC6); // Subdet
	G4ThreeVector posC6c  = G4ThreeVector(xC6-C6_DistComp/2-C6_sizeX/2.,yC6-C6_DistComp/2-C6_sizeY/2.,zC6); // Subdet
	G4ThreeVector posC6d  = G4ThreeVector(xC6+C6_DistComp/2+C6_sizeX/2.,yC6-C6_DistComp/2-C6_sizeY/2.,zC6); // Subdet
																																																					//	G4ThreeVector posS2  = G4ThreeVector(xC6,yC6,zC6+ScintA_sizeZ/2+0.5*cm); // Subdet
	G4ThreeVector posS2  = G4ThreeVector(xC4,yC4,zC4+ScintA_sizeZ/2+0.5*cm); // Subdet
	G4ThreeVector posS4  = G4ThreeVector(xS4,yS4,zS4); // Subdet

	G4ThreeVector posC7  = G4ThreeVector(xC7,yC7,zC7); // Subdet
	G4ThreeVector posC7a  = G4ThreeVector(xC7+C7_DistComp/2+C7_sizeX/2.,yC7+C7_DistComp/2+C7_sizeY/2.,zC7); // Subdet
	G4ThreeVector posC7b  = G4ThreeVector(xC7-C7_DistComp/2-C7_sizeX/2.,yC7+C7_DistComp/2+C7_sizeY/2.,zC7); // Subdet
	G4ThreeVector posC7c  = G4ThreeVector(xC7-C7_DistComp/2-C7_sizeX/2.,yC7-C7_DistComp/2-C7_sizeY/2.,zC7); // Subdet
	G4ThreeVector posC7d  = G4ThreeVector(xC7+C7_DistComp/2+C7_sizeX/2.,yC7-C7_DistComp/2-C7_sizeY/2.,zC7); // Subdet
																																																					//	G4ThreeVector posS3  = G4ThreeVector(xS3,yC7,zC7+ScintA_sizeZ/2+0.5*cm); // Subdet
	G4ThreeVector posS3  = G4ThreeVector(xC5,yC5,zC5+ScintA_sizeZ/2+0.5*cm); // Subdet
	G4ThreeVector posPb1a  = G4ThreeVector(xPb1a,yPb1a,zPb1a); // Subdet
	G4ThreeVector posPb1b  = G4ThreeVector(xPb1b,yPb1b,zPb1b); // Subdet
	G4ThreeVector posPb1c  = G4ThreeVector(xPb1c,yPb1c,zPb1c); // Subdet
	G4ThreeVector posPb2a  = G4ThreeVector(xPb2a,yPb2a,zPb2a); // Subdet
	G4ThreeVector posPb2b  = G4ThreeVector(xPb2b,yPb2b,zPb2b); // Subdet
	G4ThreeVector posPb2c  = G4ThreeVector(xPb2c,yPb2c,zPb2c); // Subdet
	G4ThreeVector posCe1  = G4ThreeVector(xCe1,yCe1,zCe1); // Subdet
	G4ThreeVector posCe2  = G4ThreeVector(xCe2,yCe2,zCe2); // Subdet
	G4ThreeVector posMu1  = G4ThreeVector(xMu1,yMu1,zMu1); // Subdet
	G4ThreeVector posMu2  = G4ThreeVector(xMu2,yMu2,zMu2); // Subdet
	G4ThreeVector posCaloTable1  = G4ThreeVector(xCaloTable1,yCaloTable1,zCaloTable); // Subdet
	G4ThreeVector posCaloTable2  = G4ThreeVector(xCaloTable2,yCaloTable2,zCaloTable); // Subdet
	G4ThreeVector posMuLatShield1 = G4ThreeVector(xMuLatShield1,yMuLatShield1,zMuLatShield1); // Subdet
	G4ThreeVector posMuLatShield2 = G4ThreeVector(xMuLatShield2,yMuLatShield2,zMuLatShield2); // Subdet
	G4ThreeVector posShield1  = G4ThreeVector(xShield1,yShield1,zShield1); // Subdet
	G4ThreeVector posShield2  = G4ThreeVector(xShield2,yShield2,zShield2); // Subdet
	
	G4ThreeVector posPbG  = G4ThreeVector(0,0,zPbG); // Subdet
	
	
	// ################################
	// CERENKOV DETECTOR ELEMENTS
	G4double zCe01Si[8];
	
	zCe01Si[0]=-Cerenkov_sizeZ/2.+Cerenkov_AluZ + Cerenkov_DistAluFirst+ Cerenkov_DistFirst + Cerenkov_DistAroundSiO +Cerenkov_SiOZ/2;
	zCe01Si[1]=zCe01Si[0] +Cerenkov_SiOZ/2 + 2*Cerenkov_DistAroundSiO + 3*Cerenkov_Wz + Cerenkov_SiOZ/2 ;
	zCe01Si[2]=zCe01Si[1] +Cerenkov_SiOZ/2 + 2*Cerenkov_DistAroundSiO + 5*Cerenkov_Wz + Cerenkov_SiOZ/2 ;
	zCe01Si[3]=zCe01Si[2] +Cerenkov_SiOZ/2 + 2*Cerenkov_DistAroundSiO + 5*Cerenkov_Wz + Cerenkov_SiOZ/2 ;
	zCe01Si[4]=zCe01Si[3] +Cerenkov_SiOZ/2 + 2*Cerenkov_DistAroundSiO + 5*Cerenkov_Wz + Cerenkov_SiOZ/2 ;
	zCe01Si[5]=zCe01Si[4] +Cerenkov_SiOZ/2 + 2*Cerenkov_DistAroundSiO + 5*Cerenkov_Wz + Cerenkov_SiOZ/2 ;
	zCe01Si[6]=zCe01Si[5] +Cerenkov_SiOZ/2 + 2*Cerenkov_DistAroundSiO + 30*Cerenkov_Wz + Cerenkov_SiOZ/2 ;
	zCe01Si[7]=zCe01Si[6] +Cerenkov_SiOZ/2 + 2*Cerenkov_DistAroundSiO + 3*Cerenkov_Wz + Cerenkov_SiOZ/2 ;
	G4double zCe01Graf=zCe01Si[5]+5*cm;
	
	G4double yCe01Si[3] ={-Cerenkov_SiOY, 0, Cerenkov_SiOY};
	
	// First 3 slices: 0, 1, 2
	G4double zCe01W[56];
	zCe01W[0]=zCe01Si[0] + Cerenkov_SiOZ/2 + Cerenkov_DistAroundSiO + Cerenkov_Wz/2.;
	zCe01W[1]=zCe01W[0] + Cerenkov_Wz;
	zCe01W[2]=zCe01W[1] + Cerenkov_Wz;
	
	// 5 slices: 3, 4, 5, 6, 7
	zCe01W[3]=zCe01Si[1] + Cerenkov_SiOZ/2 + Cerenkov_DistAroundSiO + Cerenkov_Wz/2.;
	for (int ii=0; ii<4; ii++) zCe01W[4+ii]=zCe01W[3] + (1+ii)*Cerenkov_Wz;
	
	// 5 slices: 8, 9, 10, 11, 12
	zCe01W[8]=zCe01Si[2] + Cerenkov_SiOZ/2 + Cerenkov_DistAroundSiO + Cerenkov_Wz/2.;
	for (int ii=0; ii<4; ii++) zCe01W[9+ii]=zCe01W[8] + (1+ii)*Cerenkov_Wz;
	
	// 5 slices:  13, 14, 15, 16, 17
	zCe01W[13]=zCe01Si[3] + Cerenkov_SiOZ/2 + Cerenkov_DistAroundSiO + Cerenkov_Wz/2.;
	for (int ii=0; ii<4; ii++) zCe01W[14+ii]=zCe01W[13] + (1+ii)*Cerenkov_Wz;
	
	// 5 slices:  18, 19, 20, 21, 22
	zCe01W[18]=zCe01Si[4] + Cerenkov_SiOZ/2 + Cerenkov_DistAroundSiO + Cerenkov_Wz/2.;
	for (int ii=0; ii<4; ii++) zCe01W[19+ii]=zCe01W[18] + (1+ii)*Cerenkov_Wz;
	
	
	// 30 slices:  from 23 to 52
	zCe01W[23]=zCe01Si[5] + Cerenkov_SiOZ/2 + Cerenkov_DistAroundSiO + Cerenkov_Wz/2.;
	for (int ii=0; ii<29; ii++) zCe01W[24+ii]=zCe01W[23] + (1+ii)*Cerenkov_Wz;
	
	// last 3 slices: 53, 54, 55
	zCe01W[53]=zCe01Si[6] + Cerenkov_SiOZ/2 + Cerenkov_DistAroundSiO + Cerenkov_Wz/2.;
	for (int ii=0; ii<2; ii++) zCe01W[54+ii]=zCe01W[53] + (1+ii)*Cerenkov_Wz;
	
	G4double xCe01SiTilt[8];
	G4double yCe01SiTilt[8];
	
	for (int ii=0; ii<8; ii++) {
		xCe01SiTilt[ii]=(3.5-ii)*Cerenkov_SiOXtilt;
		yCe01SiTilt[ii]=0;
	}
	
	G4ThreeVector posCeAlu1  = G4ThreeVector(0, 0,-Cerenkov_sizeZ/2.+Cerenkov_AluZ/2.); //in Cerenkov mother volume
	
	G4ThreeVector *posCeSiO[8][3];
	for (int ii=0; ii<8; ii++ ) {
		for (int jj=0; jj<3; jj++) posCeSiO[ii][jj]= new G4ThreeVector(0,yCe01Si[jj],zCe01Si[ii]);
	}
	G4ThreeVector *posCeW[56];
	for (int ii=0; ii<56; ii++ ) {
		posCeW[ii]= new G4ThreeVector(0,0,zCe01W[ii]);
	}
	
	G4ThreeVector *posCe1Graf[3];
	for (int jj=0; jj<3; jj++) posCe1Graf[jj]=new G4ThreeVector(0, yCe01Si[jj], zCe01Graf);
	
	G4ThreeVector *posCeSiOTilt[8][2];
	for (int ii=0; ii<8; ii++ ) {
		posCeSiOTilt[ii][0]= new G4ThreeVector(xCe01SiTilt[ii],yCe01SiTilt[ii],zCe01Si[0]);
		posCeSiOTilt[ii][1]= new G4ThreeVector(xCe01SiTilt[ii],yCe01SiTilt[ii],zCe01Si[7]);
	}
	
	G4ThreeVector posCeAlu2  = G4ThreeVector(0, 0,Cerenkov_sizeZ/2.-Cerenkov_AluZ/2.); //in Cerenkov mother volume
	
	//##################################
	
	// Tilt angle of calos
	G4double AngleRot=3*CLHEP::deg;
	
	G4RotationMatrix* Rot1=new G4RotationMatrix;
	Rot1->rotateY(-AngleRot);
	
	G4RotationMatrix* Rot2=new G4RotationMatrix;
	Rot2->rotateY(AngleRot);
	/*
	 G4RotationMatrix* rotEcal;
	 //		rotEcal->rotateY(EcalAngle); // add rotation angle of the crystal here
	 
	 G4Transform3D translateEcal = HepGeom::Translate3D(0*7*cm*sin(EcalAngle), 0, 0*-7*cm*cos(EcalAngle));
	 G4Transform3D rotateEcal(rotEcal,posC1);
	 */
	
	
	// ================
	// define materials
	// ================
	
	G4NistManager* nist = G4NistManager::Instance();
	G4Material* vuoto = nist->FindOrBuildMaterial("G4_Galactic");
	G4Material* aria = nist->FindOrBuildMaterial("G4_AIR");
	G4Material* berillio = nist->FindOrBuildMaterial("G4_Be");
	G4Material* silicio = nist->FindOrBuildMaterial("G4_Si");
	G4Material* ferro = nist->FindOrBuildMaterial("G4_Fe");
	G4Material* plastica = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
	G4Material* alluminium = nist->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");
	G4Material* piombo = nist->FindOrBuildMaterial("G4_Pb");
	G4Material* Tungsteno = nist->FindOrBuildMaterial("G4_W");
	
	
	
	
	// Use NIST database for elements and materials whereever possible.
	G4Element* C  = nist->FindOrBuildElement("C");
	G4Element* Si = nist->FindOrBuildElement("Si");
	G4Element* Cr = nist->FindOrBuildElement("Cr");
	G4Element* Mn = nist->FindOrBuildElement("Mn");
	G4Element* Fe = nist->FindOrBuildElement("Fe");
	G4Element* Ni = nist->FindOrBuildElement("Ni");
	// Define materials not in NIST
	G4double density;
	G4int ncomponents;
	G4double fractionmass;
	G4Material* StainlessSteel = new G4Material("StainlessSteel", density= 8.06*g/cm3, ncomponents=6);
	StainlessSteel->AddElement(C, fractionmass=0.001);
	StainlessSteel->AddElement(Si, fractionmass=0.007);
	StainlessSteel->AddElement(Cr, fractionmass=0.18);
	StainlessSteel->AddElement(Mn, fractionmass=0.01);
	StainlessSteel->AddElement(Fe, fractionmass=0.712);
	StainlessSteel->AddElement(Ni, fractionmass=0.09);
	
	
	
	
	// ================
	// Optical parameters for Cerenkov detectors
	// ================
	
	//Cerenkov counter
	const G4int nCerPointsCer = 7;
	G4double photonEnergyCer[nCerPointsCer] = {6.2*eV, 3.1*eV, 1.55*eV, 1*eV, .775*eV, .517*eV, .387*eV};
	G4double refractiveIndex_silica[nCerPointsCer] = {1.5, 1.48, 1.457, 1.446, 1.44, 1.43, 1.411 };
	G4MaterialPropertiesTable* silicaOP = new G4MaterialPropertiesTable();
	silicaOP->AddProperty("RINDEX", photonEnergyCer, refractiveIndex_silica, nCerPointsCer);
	
	//Lead Glass counter
	const G4int nCerPointsPb = 1;
	//	G4double photonEnergyPb[nCerPointsPb] = {6.2*eV, 2.85*eV, 2.55*eV, 2.27*eV, 2.10*eV, 1.88*eV, .387*eV};
	//	G4double refractiveIndex_Pb[nCerPointsPb] = {1.674, 1.674, 1.661, 1.652, 1.648, 1.642, 1.642};
	G4double photonEnergyPb[nCerPointsPb]={2.11577*eV}; //586nm
	G4double refractiveIndex_Pb[nCerPointsPb]={1.8467};
	//as referenced in:
	/*
	 SF57 lead glass, from Schott Glaswerke, Hattenbergstrasse 10, D-6500 Mainz 1, Germany. This glass has the following properties: 75% by weight PbO, density 5.54 g cm−3, X0 = 1.50 cm, and refractive index 1.8467 at λ = 586 nm.
	 https://www.sciencedirect.com/science/article/pii/0168900291905474
	 */
	G4MaterialPropertiesTable* PBOP = new G4MaterialPropertiesTable();
	PBOP->AddProperty("RINDEX", photonEnergyPb, refractiveIndex_Pb, nCerPointsPb);
	//	PBOP->AddProperty("RINDEX", photonEnergyCer, refractiveIndex_silica, nCerPointsCer);
	
	//	if (fCalibMuMBeamFlag || fElectronBeamFlag) berillio=nist->FindOrBuildMaterial("G4_Galactic");;  //if MuonBeam case I want no target
	if (!fTargetFlag) berillio=nist->FindOrBuildMaterial("G4_Galactic");;  //if I do not want the target
																																				 //--PbWO4 G-CAL crystal (CMS)
	G4double A,Z,d;
	d=8.28*g/cm3;
	A=16.00*g/mole; Z=8; G4Element* elO = new G4Element("Oxygen","O2",Z,A);
	A=183.84*g/mole; Z=74; G4Element* elW = new G4Element("Tungsten","W",Z,A);
	A=207.20*g/mole; Z=82; G4Element* elPb = new G4Element("Lead","Pb",Z,A);
	G4Material* PbWO4= new G4Material("PbWO4",d,3);
	G4int natoms;
	PbWO4->AddElement(elO,natoms=4);
	PbWO4->AddElement(elW,natoms=1);
	PbWO4->AddElement(elPb,natoms=1);
	
	G4Element* elSi = new G4Element("Silicon" ,"Si" , 14., 28.09*g/mole);
	
	G4Material* SiO2 =
	new G4Material("quartz",d= 2.200*g/cm3, natoms=2);
	SiO2->AddElement(elSi, natoms=1);
	SiO2->AddElement(elO , natoms=2);
	//	SiO2->SetMaterialPropertiesTable(silicaOP);  //toggle cerenkov in SiO2
	
	A=1.008*g/mole; Z=1; G4Element* elH = new G4Element("Hydrogen","H",Z,A);
	A=12.011*g/mole; Z=6; G4Element* elC = new G4Element("Carbon","C",Z,A);
	//Epoxy (for FR4 )
	d = 1.2*g/cm3;
	G4Material* Epoxy = new G4Material("Epoxy" , d, 2);
	Epoxy->AddElement(elH, natoms=2);
	Epoxy->AddElement(elC, natoms=2);
	
	
	//FR4 (Glass + Epoxy)
	d = 1.86*g/cm3;
	G4Material* FR4 = new G4Material("FR4"  , d, 2);
	FR4->AddMaterial(SiO2, 0.528);
	FR4->AddMaterial(Epoxy, 0.472);
	
	// lead glass
	G4Material* PbGl = new G4Material("Lead Glass", d= 3.85*g/cm3,
																		natoms=2);
	PbGl->AddElement(elPb, 0.5316);
	PbGl->AddMaterial(SiO2, 0.4684);
	//	PbGl->SetMaterialPropertiesTable(silicaOP);  //toggle cerenkov in PbGlass - CHECK I leave silicaOP because real PbGlass parameter seem not to work
	
	G4bool checkOverlaps = true;
	
	//toggle to put all materials to vaccum, to study trajectory of primary beam
	if (fAllVacFlag) {
		G4cout<<"ATTENTION! ALL MATERIALS ARE SET TO VACUUM TO SHOW PRIMARY TRACKS BEHAVIOUR!!!"<<G4endl;
		silicio=vuoto;
		//	berillio=vuoto;
		aria=vuoto;
		PbGl=vuoto;
		alluminium=vuoto;
		SiO2=vuoto;
		ferro=vuoto;
		Tungsteno=vuoto;
		piombo=vuoto;
	}
	
	// ================
	// build detector
	// ================
	
	//-- WORLD
	G4Box* solidWorld = new G4Box("World",world_sizeX/2,world_sizeY/2,world_sizeZ/2);
	G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, aria, "World");
	G4VPhysicalVolume* physWorld = new G4PVPlacement
	(0,                    // no rotation
	 G4ThreeVector(),       // centre position
	 logicWorld,            // its logical volume
	 "World",               // its name
	 0,                     // its mother volume
	 false,                 // no boolean operation
	 0,                     // copy number
	 checkOverlaps);        // overlaps checking
	G4LogicalVolume* logicTarg;
	G4LogicalCrystalVolume* crystalLogic;
	
	//-- TARGET
	if ( channeling==true ){
		//-- Crystal TARGET
		G4double crystalSizeXY = 50. * CLHEP::millimeter;
		G4double crystalSizeZ = 1. * CLHEP::millimeter; // modify crystal size along beam
		G4Box* crystalSolid = new G4Box("crystal.solid",crystalSizeXY/2.,crystalSizeXY/2.,crystalSizeZ/2.);
		//   G4Material* silicon = G4NistManager::Instance()->FindOrBuildMaterial("G4_Si");
		G4ExtendedMaterial* Crystal = new G4ExtendedMaterial("crystal.material",silicio);
		Crystal->RegisterExtension(std::unique_ptr<G4CrystalExtension>(new G4CrystalExtension(Crystal)));
		G4CrystalExtension* crystalExtension = (G4CrystalExtension*)Crystal->RetrieveExtension("crystal");
		crystalExtension->SetUnitCell(new G4CrystalUnitCell(5.43 * CLHEP::angstrom,
																												5.43 * CLHEP::angstrom,
																												5.43 * CLHEP::angstrom,
																												CLHEP::halfpi,
																												CLHEP::halfpi,
																												CLHEP::halfpi,
																												227));
		Crystal->RegisterExtension(std::unique_ptr<G4ChannelingMaterialData>(new G4ChannelingMaterialData("channeling")));
		G4ChannelingMaterialData* crystalChannelingData = (G4ChannelingMaterialData*)Crystal->RetrieveExtension("channeling");
		crystalChannelingData->SetFilename("data/Si220pl");
		crystalChannelingData->SetBR(G4ThreeVector(0.,0.,0.)); // add bending radius here
		crystalLogic = new G4LogicalCrystalVolume(crystalSolid,Crystal,"crystal.logic");
		G4RotationMatrix* rot = new G4RotationMatrix;
		rot->rotateX(0.E-6 * CLHEP::rad); // add rotation angle of the crystal here
		new G4PVPlacement(rot,posTarg,crystalLogic,"crystal.physic",logicWorld,false,0);
	}
	else{
		//-- amorphous Be TARGET
		G4Tubs* geoTarg = new G4Tubs("Target",0,target_R,target_Z/2.,startAngle,spanningAngle);
		logicTarg = new G4LogicalVolume(geoTarg, berillio, "Target");
		new G4PVPlacement(0,posTarg,logicTarg,"Target",logicWorld,false,0,checkOverlaps);
	}
	
	//-- Scint1 (pre T1) (subdet=)
	G4Box* geoS1 = new G4Box("S1", ScintA_sizeX/2, ScintA_sizeY/2, ScintA_sizeZ/2);
	G4LogicalVolume* logicS1 = new G4LogicalVolume(geoS1, plastica, "S1");
	new G4PVPlacement(0,posS1,logicS1,"S1",logicWorld,false,0,checkOverlaps);
	
	//-- T1-Si (subdet=)
	G4Box* geoT1 = new G4Box("T1", T1_sizeX/2, T1_sizeY/2, T1_sizeZ/2);
	G4LogicalVolume* logicT1 = new G4LogicalVolume(geoT1, silicio, "T1");
	new G4PVPlacement(0,posT1,logicT1,"T1",logicWorld,false,0,checkOverlaps);
	
	
	//-- Beam Pipe between T1 and T2
	G4Tubs* geoBP1 = new G4Tubs("BP1",0*cm,BP1_R,BP1_sizeZ/2.,startAngle,spanningAngle);
	G4LogicalVolume* logicBP1 = new G4LogicalVolume(geoBP1,vuoto,"BP1");
	new G4PVPlacement(0,posBP1,logicBP1,"BP1",logicWorld,false,0,checkOverlaps);
	
	
	//-- T2-Si (subdet=)
	G4Box* geoT2 = new G4Box("T2",  T2_sizeX/2, T2_sizeY/2, T2_sizeZ/2);
	G4LogicalVolume* logicT2 = new G4LogicalVolume(geoT2, silicio, "T2");
	new G4PVPlacement(0,posT2,logicT2,"T2",logicWorld,false,0,checkOverlaps);
	
	//-- C0 ()
	G4Box* geoC0 = new G4Box("C0",  C0_sizeX/2, C0_sizeY/2, C0_sizeZ/2);
	G4LogicalVolume* logicC0 = new G4LogicalVolume(geoC0, silicio, "C0");
	new G4PVPlacement(0,posC0,logicC0,"C0",logicWorld,false,0,checkOverlaps);
	
	//-- Beam Pipe between C0 and C1 (supposed)
	G4Tubs* geoBP2 = new G4Tubs("BP2",0*cm,BP2_R,BP2_sizeZ/2.,startAngle,spanningAngle);
	G4LogicalVolume* logicBP2 = new G4LogicalVolume(geoBP2,vuoto,"BP2");
	new G4PVPlacement(0,posBP2,logicBP2,"BP2",logicWorld,false,0,checkOverlaps);
	
	//-- Beam Pipe between C0 and C1 (supposed) EXT Al
	G4Tubs* geoBP2ext = new G4Tubs("BP2ext",BP2_R, BP2_R+BP_AluThickness, BP2_sizeZ/2.,startAngle,spanningAngle);
	G4LogicalVolume* logicBP2ext = new G4LogicalVolume(geoBP2ext,StainlessSteel ,"BP2ext");
	new G4PVPlacement(0,posBP2,logicBP2ext,"BP2ext",logicWorld,false,0,checkOverlaps);
	
	
	//-- C1 ()
	G4Box* geoC1 = new G4Box("C1",  C1_sizeX/2, C1_sizeY/2, C1_sizeZ/2);
	G4LogicalVolume* logicC1 = new G4LogicalVolume(geoC1, silicio, "C1");
	new G4PVPlacement(0,posC1,logicC1,"C1",logicWorld,false,0,checkOverlaps);
	
	//Bending Magnet
	G4Tubs* geoMag = new G4Tubs("Mag",0*cm,Mag_R,Mag_sizeY/2.,startAngle,spanningAngle);
	G4RotationMatrix *MagRot = new G4RotationMatrix;
	MagRot->rotateX(90.*deg);
	G4LogicalVolume* logicMag = new G4LogicalVolume(geoMag,aria,"Mag");
	new G4PVPlacement(MagRot,posMag,logicMag,"Mag",logicWorld,false,0,checkOverlaps);
	
	//-- C2 ()
	G4Box* geoC2 = new G4Box("C2",  C2_sizeX/2, C2_sizeY/2, C2_sizeZ/2);
	G4LogicalVolume* logicC2 = new G4LogicalVolume(geoC2, silicio, "C2");
	new G4PVPlacement(0,posC2,logicC2,"C2",logicWorld,false,0,checkOverlaps);
	
	//-- C3 ()
	G4Box* geoC3 = new G4Box("C3",  C3_sizeX/2, C3_sizeY/2, C3_sizeZ/2);
	G4LogicalVolume* logicC3 = new G4LogicalVolume(geoC3, silicio, "C3");
	new G4PVPlacement(0,posC3,logicC3,"C3",logicWorld,false,0,checkOverlaps);
	
	//-- C4 ()
	G4Box* geoC4 = new G4Box("C4",  C4_sizeX/2, C4_sizeY/2, C4_sizeZ/2);
	G4LogicalVolume* logicC4 = new G4LogicalVolume(geoC4, silicio, "C4");
	new G4PVPlacement(0,posC4,logicC4,"C4",logicWorld,false,0,checkOverlaps);
	
	//-- C5 ()
	G4Box* geoC5 = new G4Box("C5",  C5_sizeX/2, C5_sizeY/2, C5_sizeZ/2);
	G4LogicalVolume* logicC5 = new G4LogicalVolume(geoC5, silicio, "C5");
	new G4PVPlacement(0,posC5,logicC5,"C5",logicWorld,false,0,checkOverlaps);
	
	//-- C6 ()
	G4Box* geoC6 = new G4Box("C6",  C6_sizeX/2, C6_sizeY/2, C6_sizeZ/2);
	G4LogicalVolume* logicC6 = new G4LogicalVolume(geoC6, silicio, "C6");
	//	new G4PVPlacement(0,posC6,logicC6,"C6",logicWorld,false,0,checkOverlaps);
	new G4PVPlacement(0,posC6a,logicC6,"C6a",logicWorld,false,0,checkOverlaps);
	new G4PVPlacement(0,posC6b,logicC6,"C6b",logicWorld,false,0,checkOverlaps);
	new G4PVPlacement(0,posC6c,logicC6,"C6c",logicWorld,false,0,checkOverlaps);
	new G4PVPlacement(0,posC6d,logicC6,"C6d",logicWorld,false,0,checkOverlaps);
	
	//-- C7 ()
	G4Box* geoC7 = new G4Box("C7",  C7_sizeX/2, C7_sizeY/2, C7_sizeZ/2);
	G4LogicalVolume* logicC7 = new G4LogicalVolume(geoC7, silicio, "C7");
	//	new G4PVPlacement(0,posC7,logicC7,"C7",logicWorld,false,0,checkOverlaps);
	new G4PVPlacement(0,posC7a,logicC7,"C7a",logicWorld,false,0,checkOverlaps);
	new G4PVPlacement(0,posC7b,logicC7,"C7b",logicWorld,false,0,checkOverlaps);
	new G4PVPlacement(0,posC7c,logicC7,"C7c",logicWorld,false,0,checkOverlaps);
	new G4PVPlacement(0,posC7d,logicC7,"C7d",logicWorld,false,0,checkOverlaps);
	
	//-- Scint2 (post C6) (subdet=)
	G4Box* geoS2 = new G4Box("S2", ScintB_sizeX/2, ScintB_sizeY/2, ScintB_sizeZ/2);
	G4LogicalVolume* logicS2 = new G4LogicalVolume(geoS2, plastica, "S2");
	new G4PVPlacement(0,posS2,logicS2,"S2",logicWorld,false,0,checkOverlaps);
	
	//-- Scint3 (post C7) (subdet=)
	G4Box* geoS3 = new G4Box("S3", ScintB_sizeX/2, ScintB_sizeY/2, ScintB_sizeZ/2);
	G4LogicalVolume* logicS3 = new G4LogicalVolume(geoS3, plastica, "S3");
	new G4PVPlacement(0,posS3,logicS3,"S3",logicWorld,false,0,checkOverlaps);
	
	// ########## CALORIMETERS
	
	//-- Calorimeter table 1 (subdet=)angle
	G4Box* geoCaloTable1 = new G4Box("CaloTable1", CaloTable1_sizeX/2, CaloTable_sizeY/2, CaloTable_sizeZ/2);
	G4LogicalVolume* logicCaloTable1 = new G4LogicalVolume(geoCaloTable1, aria, "CaloTable1");
	new G4PVPlacement(Rot1,posCaloTable1,logicCaloTable1,"CaloTable1",logicWorld,false,0,checkOverlaps);
	
	//-- Calorimeter table 2 (subdet=)
	G4Box* geoCaloTable2 = new G4Box("CaloTable2", CaloTable2_sizeX/2, CaloTable_sizeY/2, CaloTable_sizeZ/2);
	G4LogicalVolume* logicCaloTable2 = new G4LogicalVolume(geoCaloTable2, aria, "CaloTable2");
	new G4PVPlacement(Rot2,posCaloTable2,logicCaloTable2,"CaloTable2",logicWorld,false,0,checkOverlaps);
	
	//-- LeadGlass 1a
	//	G4Box* solidPb1a = new G4Box("Pb1a",LeadGlass_sizeX/2,LeadGlass_sizeY/2,LeadGlass_sizeZ/2);
	G4Trd* solidPb1a = new G4Trd("Pb1a",LeadGlass_sizeXt/2,LeadGlass_sizeXb/2,LeadGlass_sizeYt/2,LeadGlass_sizeYb/2,LeadGlass_sizeZ/2);
	G4LogicalVolume* logicPb1a = new G4LogicalVolume(solidPb1a, PbGl,"Pb1a");
	new G4PVPlacement(0,posPb1a,logicPb1a,"Pb1a",logicCaloTable1,false,0,checkOverlaps);
	
	
	//-- LeadGlass 1b
	//	G4Box* solidPb1b = new G4Box("Pb1b",LeadGlass_sizeX/2,LeadGlass_sizeY/2,LeadGlass_sizeZ/2);
	G4Trd* solidPb1b = new G4Trd("Pb1b",LeadGlass_sizeXt/2,LeadGlass_sizeXb/2,LeadGlass_sizeYt/2,LeadGlass_sizeYb/2,LeadGlass_sizeZ/2);
	G4LogicalVolume* logicPb1b = new G4LogicalVolume(solidPb1b, PbGl,"Pb1b");
	new G4PVPlacement(0,posPb1b,logicPb1b,"Pb1b",logicCaloTable1,false,0,checkOverlaps);
	
	//-- LeadGlass 1c
	//	G4Box* solidPb1c = new G4Box("Pb1c",LeadGlass_sizeX/2,LeadGlass_sizeY/2,LeadGlass_sizeZ/2);
	G4Trd* solidPb1c = new G4Trd("Pb1c",LeadGlass_sizeXt/2,LeadGlass_sizeXb/2,LeadGlass_sizeYt/2,LeadGlass_sizeYb/2,LeadGlass_sizeZ/2);
	G4LogicalVolume* logicPb1c = new G4LogicalVolume(solidPb1c, PbGl,"Pb1c");
	new G4PVPlacement(0,posPb1c,logicPb1c,"Pb1c",logicCaloTable1,false,0,checkOverlaps);
	
	//-- LeadGlass 2a
	//	G4Box* solidPb2a = new G4Box("Pb2a",LeadGlass_sizeX/2,LeadGlass_sizeY/2,LeadGlass_sizeZ/2);
	G4Trd* solidPb2a = new G4Trd("Pb2a",LeadGlass_sizeXt/2,LeadGlass_sizeXb/2,LeadGlass_sizeYt/2,LeadGlass_sizeYb/2,LeadGlass_sizeZ/2);
	G4LogicalVolume* logicPb2a = new G4LogicalVolume(solidPb2a, PbGl,"Pb2a");
	new G4PVPlacement(0,posPb2a,logicPb2a,"Pb2a",logicCaloTable2,false,0,checkOverlaps);
	
	//-- LeadGlass 2b
	//	G4Box* solidPb2b = new G4Box("Pb2b",LeadGlass_sizeX/2,LeadGlass_sizeY/2,LeadGlass_sizeZ/2);
	G4Trd* solidPb2b = new G4Trd("Pb2b",LeadGlass_sizeXt/2,LeadGlass_sizeXb/2,LeadGlass_sizeYt/2,LeadGlass_sizeYb/2,LeadGlass_sizeZ/2);
	G4LogicalVolume* logicPb2b = new G4LogicalVolume(solidPb2b, PbGl,"Pb2b");
	new G4PVPlacement(0,posPb2b,logicPb2b,"Pb2b",logicCaloTable2,false,0,checkOverlaps);
	
	//-- LeadGlass 2c
	//	G4Box* solidPb2c = new G4Box("Pb2c",LeadGlass_sizeX/2,LeadGlass_sizeY/2,LeadGlass_sizeZ/2);
	G4Trd* solidPb2c = new G4Trd("Pb2c",LeadGlass_sizeXt/2,LeadGlass_sizeXb/2,LeadGlass_sizeYt/2,LeadGlass_sizeYb/2,LeadGlass_sizeZ/2);
	G4LogicalVolume* logicPb2c = new G4LogicalVolume(solidPb2c, PbGl,"Pb2c");
	new G4PVPlacement(0,posPb2c,logicPb2c,"Pb2c",logicCaloTable2,false,0,checkOverlaps);
	
	
	
	//-- LeadGlass fot Photons
	G4Trd* solidPbG = new G4Trd("PbG",LeadGlass_sizeXt/2,LeadGlass_sizeXb/2,LeadGlass_sizeYt/2,LeadGlass_sizeYb/2,LeadGlass_sizeZ/2);
	G4LogicalVolume* logicPbG = new G4LogicalVolume(solidPbG, PbGl,"PbG");
	new G4PVPlacement(0,posPbG,logicPbG,"PbG",logicWorld,false,0,checkOverlaps);
	
	
	
	//-- Cerenkov counter n 1
	G4Box* solidCe1 = new G4Box("Ce1",Cerenkov_sizeX/2,Cerenkov_sizeY/2,Cerenkov_sizeZ/2);
	G4LogicalVolume* logicCe1 = new G4LogicalVolume(solidCe1, aria,"Ce1");
	new G4PVPlacement(0,posCe1,logicCe1,"Ce1",logicCaloTable1,false,0,checkOverlaps);
	
	//-- Cerenkov counter elements
	G4Box* solidCe1Alu = new G4Box("Ce1Alu",Cerenkov_sizeX/2,Cerenkov_sizeY/2,Cerenkov_AluZ/2);
	G4LogicalVolume* logicCe1Alu = new G4LogicalVolume(solidCe1Alu,  alluminium,"Ce1Alu");
	new G4PVPlacement(0,posCeAlu1,logicCe1Alu,"Ce1Alu1",logicCe1,false,1,checkOverlaps);
	new G4PVPlacement(0,posCeAlu2,logicCe1Alu,"Ce1Alu2",logicCe1,false,2,checkOverlaps);
	
	G4Box* solidCe1SiO = new G4Box("Ce1SiO",Cerenkov_SiOX/2,Cerenkov_SiOY/2,Cerenkov_SiOZ/2);
	G4LogicalVolume* logicCe1SiO = new G4LogicalVolume(solidCe1SiO,  SiO2,"Ce1SiO");
	
	
	for (int ii=0; ii<8; ii++) {
		int kk=0;
		for (int jj=0; jj<3; jj++) {
			G4String VolName="Ce1SiO";
			G4String SubName[3]={"a","b","c"};
			new G4PVPlacement(0,*posCeSiO[ii][jj],logicCe1SiO,VolName.append(std::to_string(ii) + SubName[jj]),logicCe1,false,kk++,checkOverlaps);
		}
	}
	
	
	G4Box* solidCe1W = new G4Box("Ce1W",Cerenkov_Wx/2,Cerenkov_Wy/2,Cerenkov_Wz/2);
	G4LogicalVolume* logicCe1W = new G4LogicalVolume(solidCe1W, Tungsteno,"Ce1W");
	
	for (int ii=0; ii<8; ii++) {
		int kk=0;
		G4String VolName="Ce1W";
		new G4PVPlacement(0,*posCeW[ii],logicCe1W,VolName.append(""/*std::to_string(ii)*/),logicCe1,false,kk++,checkOverlaps);
	}
	for (int ii=53; ii<56; ii++) {
		int kk=0;
		G4String VolName="Ce1W";
		new G4PVPlacement(0,*posCeW[ii],logicCe1W,VolName.append(""/*std::to_string(ii)*/),logicCe1,false,kk++,checkOverlaps);
	}
	
	//-- Cerenkov graphite bars
	G4Box* solidCe1Gr = new G4Box("Ce1Gr",Cerenkov_SiOX/2,Cerenkov_SiOY/2,Cerenkov_SiOZ/2);
	G4LogicalVolume* logicCe1Gr = new G4LogicalVolume(solidCe1Gr, aria,"Ce1");
	for (int jj=0; jj<3; jj++) {
		G4String VolName="Ce1Graf";
		G4String SubName[3]={"a","b","c"};
		new G4PVPlacement(0,*posCe1Graf[jj],logicCe1Gr,VolName.append(SubName[jj]),logicCe1,false,99,checkOverlaps);
	}
	
	
	
	//-- Cerenkov counter n 2
	G4Box* solidCe2 = new G4Box("Ce2",Cerenkov_sizeX/2,Cerenkov_sizeY/2,Cerenkov_sizeZ/2);
	G4LogicalVolume* logicCe2 = new G4LogicalVolume(solidCe2, aria,"Ce2");
	new G4PVPlacement(0,posCe2,logicCe2,"Ce2",logicCaloTable2,false,0,checkOverlaps);
	
	//-- Cerenkov counter elements
	G4Box* solidCe2Alu = new G4Box("Ce2Alu",Cerenkov_sizeX/2,Cerenkov_sizeY/2,Cerenkov_AluZ/2);
	G4LogicalVolume* logicCe2Alu = new G4LogicalVolume(solidCe2Alu,  alluminium,"Ce2Alu");
	new G4PVPlacement(0,posCeAlu1,logicCe2Alu,"Ce2Alu1",logicCe2,false,1,checkOverlaps);
	new G4PVPlacement(0,posCeAlu2,logicCe2Alu,"Ce2Alu2",logicCe2,false,2,checkOverlaps);
	
	G4Box* solidCe2SiO = new G4Box("Ce2SiO",Cerenkov_SiOX/2,Cerenkov_SiOY/2,Cerenkov_SiOZ/2);
	G4LogicalVolume* logicCe2SiO = new G4LogicalVolume(solidCe2SiO,  SiO2,"Ce2SiO");
	for (int ii=1; ii<7; ii++) {
		int kk=0;
		for (int jj=0;  jj<3; jj++) {
			if ((ii==1)||(ii==6)) {
				G4String VolName="Ce2SiO";
				G4String SubName[3]={"a","b","c"};
				new G4PVPlacement(0,*posCeSiO[ii][jj],logicCe2SiO,VolName.append(std::to_string(ii) + SubName[jj]),logicCe2,false,8+kk++,checkOverlaps);
//				new G4PVPlacement(0,*posCeSiO[ii][jj],logicCe2SiO,VolName.append(std::to_string(ii) + SubName[jj]),logicCe2,false,8+((ii-1)*3+jj),checkOverlaps); //before TB with all channels
				//			G4cout<<"Normali= "<<8+((ii-1)*3+jj)<<G4endl;
			}
		}
	}
	
	G4Box* solidCe2SiOtilt = new G4Box("Ce2SiOtilt",Cerenkov_SiOXtilt/2,Cerenkov_SiOYtilt/2,Cerenkov_SiOZtilt/2);
	G4LogicalVolume* logicCe2SiOtilt = new G4LogicalVolume(solidCe2SiOtilt,  SiO2,"Ce2SiOtilt");
	for (int ii=0; ii<2; ii++) {
		for (int jj=0; jj<8; jj++) {
			G4String VolName="Ce2SiOtilt";
			G4String SubName[8]={"a","b","c","d", "e", "f", "g", "h"};
			new G4PVPlacement(0,*posCeSiOTilt[jj][ii],logicCe2SiOtilt,VolName.append(std::to_string(ii) + SubName[jj]),logicCe2,false,ii*14+(jj),checkOverlaps);
//			new G4PVPlacement(0,*posCeSiOTilt[jj][ii],logicCe2SiOtilt,VolName.append(std::to_string(ii) + SubName[jj]),logicCe2,false,ii*26+(jj),checkOverlaps); //Before TB with all channels
			//			G4cout<<"Tiltati= "<<ii*26+(jj)<<G4endl;
			
		}
	}
	
	G4Box* solidCe2W = new G4Box("Ce2W",Cerenkov_Wx/2,Cerenkov_Wy/2,Cerenkov_Wz/2);
	G4LogicalVolume* logicCe2W = new G4LogicalVolume(solidCe2W,  Tungsteno,"Ce2W");
	for (int ii=0; ii<8; ii++) {
		int kk=0;
		G4String VolName="Ce2W";
		new G4PVPlacement(0,*posCeW[ii],logicCe2W,VolName.append(""/*std::to_string(ii)*/),logicCe2,false,kk++,checkOverlaps);
	}
	for (int ii=53; ii<56; ii++) {
		int kk=0;
		G4String VolName="Ce2W";
		new G4PVPlacement(0,*posCeW[ii],logicCe2W,VolName.append(""/*std::to_string(ii)*/),logicCe2,false,kk++,checkOverlaps);
	}
	
	
	// ############## END OF CALORIMETERS
	
	//-- Shield Wall (Fe) before chambers
	G4Box* shield = new G4Box("Shield",shield_sizeX/2, shield_sizeY/2, shield_sizeZ/2);
	G4LogicalVolume* logicShield = new G4LogicalVolume(shield, ferro, "Shield");
	new G4PVPlacement(0,posShield1,logicShield,"Shield1",logicWorld,false,0,checkOverlaps);
	new G4PVPlacement(0,posShield2,logicShield,"Shield2",logicWorld,false,0,checkOverlaps);
	
	//-- Muon chamber 1
	G4Box* solidMu1 = new G4Box("Mu1",Mu_sizeX/2,Mu_sizeY/2,Mu_sizeZ/2);
	G4LogicalVolume* logicMu1 = new G4LogicalVolume(solidMu1, aria,"Mu1");
	
	//-- Muon chamber 2
	G4Box* solidMu2 = new G4Box("Mu2",Mu_sizeX/2,Mu_sizeY/2,Mu_sizeZ/2);
	G4LogicalVolume* logicMu2 = new G4LogicalVolume(solidMu2, aria,"Mu2");
	
	for (int ii=0; ii<4; ii++) {
		new G4PVPlacement(0, G4ThreeVector(posMu1.x(), posMu1.y(), posMu1.z()+(ii+0.5)*Mu_sizeZ),logicMu1,"Mu1",logicWorld,false,ii,checkOverlaps);
		new G4PVPlacement(0, G4ThreeVector(posMu2.x(), posMu2.y(), posMu2.z()+(ii+0.5)*Mu_sizeZ),logicMu2,"Mu2",logicWorld,false,ii,checkOverlaps);
	}
	for (int ii=4; ii<8; ii++) {
		new G4PVPlacement(0, G4ThreeVector(posMu1.x(), posMu1.y(), posMu1.z()+(ii+0.5)*Mu_sizeZ+Mu_gapZ),logicMu1,"Mu1",logicWorld,false,ii,checkOverlaps);
		new G4PVPlacement(0, G4ThreeVector(posMu2.x()-Mu2_shiftX, posMu2.y(), posMu2.z()+(ii+0.5)*Mu_sizeZ+Mu_gapZ),logicMu2,"Mu2",logicWorld,false,ii,checkOverlaps);
	}
	

	//-- Scint4 (between layers of Mu1)
	G4Box* geoS4 = new G4Box("S4", ScintC_sizeX/2, ScintC_sizeY/2, ScintC_sizeZ/2);
	G4LogicalVolume* logicS4 = new G4LogicalVolume(geoS4, plastica, "S4");
	new G4PVPlacement(0,posS4,logicS4,"S4",logicWorld,false,0,checkOverlaps);
	
	
	/*
	 G4cout<<"##################################\nSUMMARIZING GEOMETRY\n"<<G4endl;
	 G4cout<<"physCe2Fe->z="<<physCe2Fe->GetTranslation().z()<<G4endl;
	 */
	
	// ###################################################################################
	// ###################################################################################
	
	
	if( channeling==true ){
		fScoringVolume_Targ = crystalLogic;
	}else{
		fScoringVolume_Targ = logicTarg;
	}
	
	fScoringVolume_S1=logicS1;
	fScoringVolume_T1=logicT1;
	fScoringVolume_T2=logicT2;
	fScoringVolume_C0=logicC0;
	fScoringVolume_C1=logicC1;
	fScoringVolume_C2=logicC2;
	fScoringVolume_C3=logicC3;
	fScoringVolume_C4=logicC4;
	fScoringVolume_C5=logicC5;
	fScoringVolume_C6=logicC6;
	fScoringVolume_C7=logicC7;
	fScoringVolume_S2=logicS2;
	fScoringVolume_S3=logicS3;
	fScoringVolume_S4=logicS4;
	fScoringVolume_Pb1a=logicPb1a;
	fScoringVolume_Pb1b=logicPb1b;
	fScoringVolume_Pb1c=logicPb1c;
	fScoringVolume_Pb2a=logicPb2a;
	fScoringVolume_Pb2b=logicPb2b;
	fScoringVolume_Pb2c=logicPb2c;
	fScoringVolume_PbG=logicPbG;
	//	fScoringVolume_Ce1=logicCe1;
	//	fScoringVolume_Ce2=logicCe2;
	fScoringVolume_Ce1=logicCe1SiO;
	fScoringVolume_Ce2tilt=logicCe2SiOtilt;
	fScoringVolume_Ce2=logicCe2SiO;
	fScoringVolume_Mu1=logicMu1;
	fScoringVolume_Mu2=logicMu2;
	
	G4cout<<" ... Detector construction DONE !"<<G4endl;
	return physWorld;
}


void B1DetectorConstruction::ConstructSDandField(){
	if( channeling==true ){
		G4LogicalVolume* crystalLogic = G4LogicalVolumeStore::GetInstance()->GetVolume("crystal.logic");
		G4ChannelingOptrMultiParticleChangeCrossSection* testMany = new G4ChannelingOptrMultiParticleChangeCrossSection();
		testMany->AttachTo(crystalLogic);
		G4cout << " Attaching biasing operator " << testMany->GetName()
		<< " to logical volume " << crystalLogic->GetName()
		<< G4endl;
	}
	
	
	// =============================
	//       MAGNETIC FIELD
	// =============================
	// Conventional sign: non-flipped field sends positrons towards "up"
	G4VPhysicalVolume* physicalBend = G4PhysicalVolumeStore::GetInstance()->GetVolume("Mag");
	G4double zOffset=physicalBend->GetTranslation().z();
	//	/*
	if(fMagField>=0) { //Means I want to use the map with this value of current
		G4cout<<"lemmaDEBUG zoffset= "<<zOffset<<G4endl;
		G4double fActualCurrent=700;
		if (fMagField!=1) fActualCurrent=-fMagField;
		if (fFlipFieldFlag) fActualCurrent*=-1;
		//		G4MagneticField* PurgMagField= new PurgMagTabulatedField3D("MappaBTB.TABLE",  -zOffset+100*cm);
		//		G4MagneticField* PurgMagField= new PurgMagTabulatedField3D("MappaBTB.TABLE",  zOffset+00*cm, fFlipFieldFlag, fActualCurrent);
		G4MagneticField* PurgMagField= new PurgMagTabulatedField3D("MBPL_FieldMap700A.table",  zOffset+00*cm, fFlipFieldFlag, fActualCurrent);
		fField.Put(PurgMagField);
		G4cout<<"#### Magnetic field according to map has been requested, with a actual current of : "<<fActualCurrent<<G4endl;
		
		G4FieldManager* pFieldMgr =
		G4TransportationManager::GetTransportationManager()->GetFieldManager();
		
		pFieldMgr->SetDetectorField(fField.Get());
		pFieldMgr->CreateChordFinder(fField.Get());
	}
	else
	{ //fixed constant map has been requested
		G4double fieldValue=fabs(fMagField*tesla);
		if (fFlipFieldFlag) fieldValue*=-1;
		G4cout<<"#### Constant Magnetic field has been requested, with a value of : "<<fieldValue/tesla<<G4endl;
		
		G4UniformMagField* myField = new G4UniformMagField(G4ThreeVector(0., fieldValue, 0.));
		G4LogicalVolume* logicBend = G4LogicalVolumeStore::GetInstance()->GetVolume("Mag");
		G4FieldManager* localfieldMgr = new G4FieldManager(myField);
		logicBend->SetFieldManager(localfieldMgr,true);
		localfieldMgr->CreateChordFinder(myField);
	}
	//	*/
	
}
