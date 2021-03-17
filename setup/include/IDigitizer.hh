/*
  Interface class for the TB digitizers
*/
#ifndef IDIGITIZER_H
#define IDIGITIZER_H

#include "G4Types.hh"
#include "G4ThreeVector.hh"
#include "G4LorentzVector.hh"
#include "G4VPhysicalVolume.hh"

#include <map>
#include <vector>

struct Hit {

  G4ThreeVector position;
  G4double deposit;
  int index;
  
};

struct Digit {

  G4ThreeVector position;
  G4ThreeVector error;
  G4double energy;
  std::vector<int> hitIndexVector;
  
};

typedef std::map<int,Hit> HitMap;
typedef std::map<int,Digit> DigitMap;

class IDigitizer
{
  
public:
  
  virtual bool addHit(int subdet, const G4ThreeVector hitPos, G4double deposit, int index);

  virtual bool addDigit(int subdet, const G4ThreeVector digitPos, G4ThreeVector digitPosError,
			G4double energy, std::vector<int> hitIndexVector);

  virtual HitMap getHitMap() {return m_hitMap;}
  virtual DigitMap getDigitMap() {return m_digitMap;}
  
  virtual bool digitize() = 0;
  
  virtual bool getPosition(const G4ThreeVector hitPos, G4double deposit, G4ThreeVector& digitPos, G4ThreeVector& digitPosErr) = 0;

  virtual void setPhysicalVolume(G4VPhysicalVolume* physVol) {m_physicalVolume=physVol;}
  virtual G4VPhysicalVolume* getPhysicalVolume() {return m_physicalVolume;}

  virtual void setMeasY(bool measY) {m_measY=measY;}
  virtual bool getMeasY() {return m_measY;}
  
private:
  
  HitMap m_hitMap;
  DigitMap m_digitMap;

  /// physical volume of the detector
  /// to be digitized
  G4VPhysicalVolume* m_physicalVolume;

  bool m_measY;
  
};  // IDigitizer


inline bool IDigitizer::addHit(int subdet, const G4ThreeVector hitPos,
			       G4double deposit, int index) {
  Hit newHit;
  newHit.position = hitPos;
  newHit.deposit = deposit;
  newHit.index = index;
  m_hitMap.insert(std::pair<int,Hit>(subdet,newHit));
  return true;
}

inline bool IDigitizer::addDigit(int subdet, const G4ThreeVector digitPos,
				 G4ThreeVector digitPosError, G4double energy,
				 std::vector<int> hitIndexVector) {
  Digit newDigit;
  newDigit.position = digitPos;
  newDigit.error    = digitPosError;
  newDigit.energy = energy;
  newDigit.hitIndexVector = hitIndexVector;
  m_digitMap.insert(std::pair<int,Digit>(subdet,newDigit));
  return true;
}


#endif

