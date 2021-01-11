/* 
   Digitizer for the silicon trackers
*/

#ifndef SIDIGITIZER_H
#define SIDIGITIZER_H

#include "IDigitizer.hh"

class SiDigitizer :
  public IDigitizer {
  
public:

  SiDigitizer();
  virtual ~SiDigitizer() {};

  void getPosition(const G4ThreeVector hitPos, G4double deposit, G4ThreeVector& digitPos, G4ThreeVector& digitPosErr);
  
  void getEnergyAndPosition(const G4ThreeVector hitPos, const G4LorentzVector hitMom,
			    G4double deposit, G4ThreeVector& digitPos, G4double& energy);
  
private:
  
  double m_xRes;
  double m_yRes;
  
};

#endif
