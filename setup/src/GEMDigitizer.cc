#include "GEMDigitizer.hh"

#include "Randomize.hh"

GEMDigitizer::GEMDigitizer() :
  m_minBase(0.0),
  m_maxBase(0.0),
  m_minPitch(0.0),
  m_ySize(0.0)
{

}


bool GEMDigitizer::digitize()
{

  return true;
}


bool GEMDigitizer::getPosition(const G4ThreeVector hitPos, G4double deposit, G4ThreeVector& digitPos, G4ThreeVector& digitPosErr)
{

  G4ThreeVector physVolPosition = this->getPhysicalVolume()->GetTranslation();
  // get the local y position to get the pitch
  double ypos = hitPos.y()-physVolPosition.y()+m_ySize/2.;

  int nstrip = m_minBase/m_minPitch;
  double maxPitch = m_maxBase/((double) nstrip);
  
  /// get the pitch at the height
  double pitch = m_minPitch + (ypos/m_ySize)*(maxPitch-m_minPitch);

  double test = G4RandFlat::shoot();
  if ( test>0.5 ) {
    pitch = pitch*2.0;
  }

  double xres = pitch/sqrt(12);
  double yres = 0.0;
  if ( this->getMeasY() ) {
    yres = xres;
  }
  
  G4double dx = G4RandGauss::shoot(0.0,xres);
  G4double dy = G4RandGauss::shoot(0.0,yres);

  digitPos.setX(hitPos.x()+dx);
  if (this->getMeasY()) { 
    digitPos.setY(hitPos.y()+dy);
  }
  else {
    digitPos.setY(physVolPosition.y());
  }

  digitPos.setZ(hitPos.z());

  digitPosErr.setX(xres);
  digitPosErr.setY(yres);
  digitPosErr.setZ(0.0);

  /// false to be added (inefficiencies)
  

  return true;
  
}

