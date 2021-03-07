/* 
   Digitizer for the GEM trackers
*/

#ifndef GEMDIGITIZER_H
#define GEMDIGITIZER_H

#include "IDigitizer.hh"

class GEMDigitizer :
  public IDigitizer {
  
public:

  GEMDigitizer();
  virtual ~GEMDigitizer() {};

  bool getPosition(const G4ThreeVector hitPos, G4double deposit, G4ThreeVector& digitPos, G4ThreeVector& digitPosErr);
  
  bool getEnergyAndPosition(const G4ThreeVector hitPos, const G4LorentzVector hitMom,
			    G4double deposit, G4ThreeVector& digitPos, G4double& energy);
  
private:
  
  double m_xRes;
  double m_yRes;
  
};

#endif
