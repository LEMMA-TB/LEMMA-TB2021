#include "GEMDigitizer.hh"

#include "Randomize.hh"

GEMDigitizer::GEMDigitizer() :
  m_xRes(0.200),
  m_yRes(0.200)
{

}



bool GEMDigitizer::getPosition(const G4ThreeVector hitPos, G4double deposit, G4ThreeVector& digitPos, G4ThreeVector& digitPosErr)
{

  G4double dx = G4RandGauss::shoot(0.0,m_xRes);
  G4double dy = G4RandGauss::shoot(0.0,m_yRes);

  digitPos.setX(hitPos.x()+dx);
  digitPos.setY(hitPos.y()+dy);
  digitPos.setZ(hitPos.z());

  digitPosErr.setX(m_xRes);
  digitPosErr.setY(m_yRes);
  digitPosErr.setZ(0.0);

  /// false to be added (inefficiencies)
  return true;
  
}

bool GEMDigitizer::getEnergyAndPosition(const G4ThreeVector hitPos, const G4LorentzVector hitMom,
				       G4double deposit, G4ThreeVector& digitPos, G4double& energy)
{

  /// false to be added (inefficiencies)
  return true;
  
}
