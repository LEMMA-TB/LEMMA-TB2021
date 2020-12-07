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

  virtual void getPosition(const G4ThreeVector hitPos, G4double deposit, G4ThreeVector& digitPos) = 0;

  virtual void getEnergyAndPosition(const G4ThreeVector hitPos, const G4LorentzVector hitMom,
				    G4double deposit, G4ThreeVector& digitPos, G4double& energy) = 0;
  
};  // IDigitizer

#endif

