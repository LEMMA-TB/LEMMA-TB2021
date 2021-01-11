/*
  Interface class for the TB digitizers
*/
#ifndef IDIGITIZER_H
#define IDIGITIZER_H

#include "G4Types.hh"
#include "G4ThreeVector.hh"
#include "G4LorentzVector.hh"

class IDigitizer
{
  
 public:

  virtual bool getPosition(const G4ThreeVector hitPos, G4double deposit, G4ThreeVector& digitPos, G4ThreeVector& digitPosErr) = 0;
  
  virtual bool getEnergyAndPosition(const G4ThreeVector hitPos, const G4LorentzVector hitMom,
				    G4double deposit, G4ThreeVector& digitPos, G4double& energy) = 0;
  
};  // IDigitizer

#endif

