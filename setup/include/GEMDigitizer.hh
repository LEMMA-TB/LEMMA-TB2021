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

  bool digitize();
  
  bool getPosition(const G4ThreeVector hitPos, G4double deposit, G4ThreeVector& digitPos, G4ThreeVector& digitPosErr);
  
  void setPitch(double minPitch) {m_minPitch=minPitch;}
  double getPitch() {return m_minPitch;}
  
  void setBase(double minBase, double maxBase) {m_minBase=minBase; m_maxBase=maxBase;}
  double getMinBase() {return m_minBase;}
  double getMaxBase() {return m_maxBase;}

  void setSize(double ySize) {m_ySize=ySize;}
  double getSize() {return m_ySize;}
  
private:

  double m_minBase;
  double m_maxBase;

  double m_minPitch;
  
  double m_ySize;

};

#endif
