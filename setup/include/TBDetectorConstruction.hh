#ifndef TBDetectorConstruction_h
#define TBDetectorConstruction_h 

#include "globals.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4cache.hh"

class G4MagneticField;

class TBDetectorConstruction : public G4VUserDetectorConstruction 
{
public:
  TBDetectorConstruction(G4String fileName);
  virtual ~TBDetectorConstruction();

  virtual G4VPhysicalVolume* Construct();
  virtual void ConstructSDandField();
  
  G4bool importGeometry();
  G4bool exportGeometry(G4VPhysicalVolume* physVol);

  void SetChanneling(G4bool channeling, G4String ctype) { m_channeling = channeling; m_ctype = ctype; return; }
  G4bool GetChanneling() {return m_channeling;}
  
private:

  G4String m_fileName;

  G4bool m_channeling;
  G4String m_ctype;
  G4bool m_fFlipFieldFlag;
  G4double m_fMagField;

  G4Cache<G4MagneticField*> m_fField;  //pointer to the thread-local fields

};

#endif
