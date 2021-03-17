#ifndef TBDetectorConstruction_h
#define TBDetectorConstruction_h 

#include "globals.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4cache.hh"
#include "G4GDMLParser.hh"

#include <map>

class G4MagneticField;
class G4GDMLParser;

class TBDetectorConstruction : public G4VUserDetectorConstruction 
{
public:
  TBDetectorConstruction(G4String fileName);
  virtual ~TBDetectorConstruction();

  virtual G4VPhysicalVolume* Construct();
  virtual void ConstructSDandField();
  
  G4bool exportGeometry(G4VPhysicalVolume* physVol);

  G4LogicalVolume* getScoringVolume(G4String volName) const;
  G4VPhysicalVolume* getPhysicalVolume(G4String volName) const;
  
  void SetChanneling(G4bool channeling, G4String ctype) { m_channeling = channeling; m_ctype = ctype; return; }
  G4bool GetChanneling() {return m_channeling;}
  
private:

  G4GDMLParser m_parser;
  G4String m_fileName;

  G4bool m_channeling;
  G4String m_ctype;
  G4bool m_fFlipFieldFlag;
  G4double m_fMagField;

  G4Cache<G4MagneticField*> m_fField;  //pointer to the thread-local fields

  // pointers to the logical volumes
  std::map<G4String,G4LogicalVolume*> m_logicalVolumes;

  // pointers to the logical volumes
  std::map<G4String,G4VPhysicalVolume*> m_physicalVolumes;

};

#endif
