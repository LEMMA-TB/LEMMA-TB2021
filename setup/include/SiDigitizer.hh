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

  bool digitize();
  
  bool getPosition(const G4ThreeVector hitPos, G4double deposit, G4ThreeVector& digitPos, G4ThreeVector& digitPosErr);
  
private:
  
  double m_xRes;
  double m_yRes;
  
};

#endif
