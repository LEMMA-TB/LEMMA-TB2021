#include "TBDetectorConstruction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4MagneticField.hh"
#include "G4FieldManager.hh"
#include "G4UniformMagField.hh"
#include "G4GDMLParser.hh"
#include "PurgMagTabulatedField3D.hh"
#include "G4ChannelingOptrMultiParticleChangeCrossSection.hh"

TBDetectorConstruction::TBDetectorConstruction(G4String fileName) :
  m_fileName(fileName),
  m_fMagField(0)
{ }


TBDetectorConstruction::~TBDetectorConstruction()
{}

G4VPhysicalVolume* TBDetectorConstruction::Construct()
{
  G4VPhysicalVolume* world = NULL;

  G4GDMLParser parser;
  parser.Read(m_fileName,false);

  world = parser.GetWorldVolume();

  std::cout << "Number of objects in the world: " << world->GetMultiplicity() << std::endl;
  
  return world;
}

bool TBDetectorConstruction::importGeometry()
{
  
  return true;
}

bool TBDetectorConstruction::exportGeometry(G4VPhysicalVolume* physVol)
{
  G4GDMLParser parser;

  parser.Write("output.gdml",physVol,false);
  
  return true;
}


void TBDetectorConstruction::ConstructSDandField(){
  if( m_channeling==true ){
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
//  if(m_fMagField>=0) { //Means I want to use the map with this value of current
//    G4cout<<"lemmaDEBUG zoffset= "<<zOffset<<G4endl;
//    G4double fActualCurrent=700;
//    if (m_fMagField!=1) fActualCurrent=-m_fMagField;
//    if (m_fFlipFieldFlag) fActualCurrent*=-1;
//
//    G4MagneticField* PurgMagField= new PurgMagTabulatedField3D("MBPL_FieldMap700A.table",  zOffset+00*cm, m_fFlipFieldFlag, fActualCurrent);
//    m_fField.Put(PurgMagField);
//    G4cout<<"#### Magnetic field according to map has been requested, with a actual current of : "<<fActualCurrent<<G4endl;
//    
//    G4FieldManager* pFieldMgr =
//      G4TransportationManager::GetTransportationManager()->GetFieldManager();
//    
//    pFieldMgr->SetDetectorField(m_fField.Get());
//    pFieldMgr->CreateChordFinder(m_fField.Get());
//  }
//  else
//    { //fixed constant map has been requested
      G4double fieldValue=fabs(m_fMagField*CLHEP::tesla);
      if (m_fFlipFieldFlag) fieldValue*=-1;
      G4cout<<"#### Constant Magnetic field has been requested, with a value of : "<<fieldValue/tesla<<G4endl;
      
      G4UniformMagField* myField = new G4UniformMagField(G4ThreeVector(0., fieldValue, 0.));
      G4LogicalVolume* logicBend = G4LogicalVolumeStore::GetInstance()->GetVolume("Mag");
      G4FieldManager* localfieldMgr = new G4FieldManager(myField);
      logicBend->SetFieldManager(localfieldMgr,true);
      localfieldMgr->CreateChordFinder(myField);
      //  }
  //	*/
  
}
