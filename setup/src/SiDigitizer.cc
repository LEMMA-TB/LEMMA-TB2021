#include "SiDigitizer.hh"

#include "Randomize.hh"

SiDigitizer::SiDigitizer() :
  m_xRes(0.007),
  m_yRes(0.007)
{

}

bool SiDigitizer::digitize()
{

  HitMap hitMap = this->getHitMap();
  for ( auto it : hitMap ) {
    Digit newDigit;
    G4ThreeVector digitPos;
    G4ThreeVector digitPosError;
    
    /// get the digit for each hit
    if ( getPosition(it.second.position,0.0,digitPos,digitPosError)  ) {
      newDigit.position = digitPos;
      newDigit.error = digitPosError;
      newDigit.energy = 0.0;
      newDigit.hitIndexVector.push_back(it.second.index);
    }
    else {
      std::cout << "ERROR Could not digitize in SiDigitizer" << std::endl;
    }
  }
  
  return true;
}

bool SiDigitizer::getPosition(const G4ThreeVector hitPos, G4double deposit, G4ThreeVector& digitPos, G4ThreeVector& digitPosErr)
{

  double res = m_xRes;
  double test = G4RandFlat::shoot();
  if (test>0.3) {
    res=res*2.;
  }

  
  G4double dx = G4RandGauss::shoot(0.0,res);
  G4double dy = G4RandGauss::shoot(0.0,res);

  digitPos.setX(hitPos.x()+dx);
  digitPos.setY(hitPos.y()+dy);
  digitPos.setZ(hitPos.z());

  digitPosErr.setX(res);
  digitPosErr.setY(res);
  digitPosErr.setZ(0.0);

  /// false to be added (inefficiencies)
  return true;
  
}

