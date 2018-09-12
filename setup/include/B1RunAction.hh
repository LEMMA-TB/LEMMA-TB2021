#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include <vector>
#include <map>

class G4Run;
class G4LogicalVolume;
class B1RunAction : public G4UserRunAction
{
public:
	B1RunAction(const std::map<G4int,G4int> &);
	virtual ~B1RunAction();
	virtual G4Run* GenerateRun();
	virtual void BeginOfRunAction(const G4Run*);
	virtual void   EndOfRunAction(const G4Run*);
	
	std::vector<G4double>& GetBeamX() {return RunVectorBeamX; }
	std::vector<G4double>& GetBeamY() {return RunVectorBeamY; }
	std::vector<G4double>& GetBeamZ() {return RunVectorBeamZ; }
	std::vector<G4double>& GetBeamCX() {return RunVectorBeamCX; }
	std::vector<G4double>& GetBeamCY() {return RunVectorBeamCY; }
	std::vector<G4double>& GetBeamCZ() {return RunVectorBeamCZ; }
	std::vector<G4double>& GetBeamEne() {return RunVectorBeamEne; }
	std::vector<G4double>& GetBeamPart() {return RunVectorBeamPart; }
	
	std::vector<G4double>& GetSubdet() {return RunVectorSubdet; }
	std::vector<G4double>& GetIdp() {return RunVectorIdp; }
	std::vector<G4double>& GetIpar() {return RunVectorIpar; }
	std::vector<G4double>& GetItrack() {return RunVectorItrack; }
	std::vector<G4double>& GetTime() {return RunVectorTime; }
	std::vector<G4double>& GetVectorX() {return RunVectorX; }
	std::vector<G4double>& GetVectorY() {return RunVectorY; }
	std::vector<G4double>& GetVectorZ() {return RunVectorZ; }
	std::vector<G4double>& GetVectorP() {return RunVectorP; }
	std::vector<G4double>& GetVectorPX() {return RunVectorPX; }
	std::vector<G4double>& GetVectorPY() {return RunVectorPY; }
	std::vector<G4double>& GetVectorPZ() {return RunVectorPZ; }
	std::vector<G4double>& GetVertexX() {return RunVectorVertexX; }
	std::vector<G4double>& GetVertexY() {return RunVectorVertexY; }
	std::vector<G4double>& GetVertexZ() {return RunVectorVertexZ; }
	std::vector<G4double>& GetKinev() {return RunVectorKinev; }
	std::vector<G4double>& GetVectorPXvdir() {return RunVectorPXvdir; }
	std::vector<G4double>& GetVectorPYvdir() {return RunVectorPYvdir; }
	std::vector<G4double>& GetVectorPZvdir() {return RunVectorPZvdir; }
	std::vector<G4int>& GetProcess() {return RunVectorProcess; }
	std::vector<G4double>& GetIev() {return RunVectorIev; }
	std::vector<G4double>& GetStep() {return RunVectorStep; }
	std::vector<G4double>& GetInextStep() {return RunVectorInextStep; }
	std::vector<G4double>& GetCopyNb() {return RunVectorCopyNb; }
	
	std::vector<G4double>& GetCaloEnDep() {return RunVectorCaloEnDep; }
	
	std::vector<G4double>& GetVectorCross() {return RunVectorCross; }
	
	std::vector<G4double>& GetVectorGammaConvX() {return RunVectorGammaConvX; }
	std::vector<G4double>& GetVectorGammaConvY() {return RunVectorGammaConvY; }
	std::vector<G4double>& GetVectorGammaConvZ() {return RunVectorGammaConvZ; }
	std::vector<G4double>& GetVectorGammaConvEne() {return RunVectorGammaConvEne; }
	std::vector<G4double>& GetVectorGammaConvSubdet() {return RunVectorGammaConvSubdet; }
	std::vector<G4double>& GetVectorGammaConvEnePos() {return RunVectorGammaConvEnePos; }
	std::vector<G4double>& GetVectorGammaConvEneEle() {return RunVectorGammaConvEneEle; }
	
	
	std::vector<G4double>& GetVectorPbGlass1EnterEne() {return RunVectorPbGlass1EnterEne; }
	std::vector<G4double>& GetVectorPbGlass1EnterPart() {return RunVectorPbGlass1EnterPart; }
	std::vector<G4double>& GetVectorPbGlass1EnterX() {return RunVectorPbGlass1EnterX; }
	std::vector<G4double>& GetVectorPbGlass1EnterY() {return RunVectorPbGlass1EnterY; }
	std::vector<G4double>& GetVectorPbGlass1EnterZ() {return RunVectorPbGlass1EnterZ; }
	std::vector<G4double>& GetVectorPbGlass1EnterVX() {return RunVectorPbGlass1EnterVX; }
	std::vector<G4double>& GetVectorPbGlass1EnterVY() {return RunVectorPbGlass1EnterVY; }
	std::vector<G4double>& GetVectorPbGlass1EnterVZ() {return RunVectorPbGlass1EnterVZ; }
	std::vector<G4double>& GetVectorPbGlass1EnterPX() {return RunVectorPbGlass1EnterPX; }
	std::vector<G4double>& GetVectorPbGlass1EnterPY() {return RunVectorPbGlass1EnterPY; }
	std::vector<G4double>& GetVectorPbGlass1EnterPZ() {return RunVectorPbGlass1EnterPZ; }
	
	std::vector<G4double>& GetVectorPbGlass2EnterEne() {return RunVectorPbGlass2EnterEne; }
	std::vector<G4double>& GetVectorPbGlass2EnterPart() {return RunVectorPbGlass2EnterPart; }
	std::vector<G4double>& GetVectorPbGlass2EnterX() {return RunVectorPbGlass2EnterX; }
	std::vector<G4double>& GetVectorPbGlass2EnterY() {return RunVectorPbGlass2EnterY; }
	std::vector<G4double>& GetVectorPbGlass2EnterZ() {return RunVectorPbGlass2EnterZ; }
	std::vector<G4double>& GetVectorPbGlass2EnterVX() {return RunVectorPbGlass2EnterVX; }
	std::vector<G4double>& GetVectorPbGlass2EnterVY() {return RunVectorPbGlass2EnterVY; }
	std::vector<G4double>& GetVectorPbGlass2EnterVZ() {return RunVectorPbGlass2EnterVZ; }
	std::vector<G4double>& GetVectorPbGlass2EnterPX() {return RunVectorPbGlass2EnterPX; }
	std::vector<G4double>& GetVectorPbGlass2EnterPY() {return RunVectorPbGlass2EnterPY; }
	std::vector<G4double>& GetVectorPbGlass2EnterPZ() {return RunVectorPbGlass2EnterPZ; }

	std::vector<G4double>& GetVectorPbGlassGEnterEne() {return RunVectorPbGlassGEnterEne; }
	std::vector<G4double>& GetVectorPbGlassGEnterPart() {return RunVectorPbGlassGEnterPart; }
	std::vector<G4double>& GetVectorPbGlassGEnterX() {return RunVectorPbGlassGEnterX; }
	std::vector<G4double>& GetVectorPbGlassGEnterY() {return RunVectorPbGlassGEnterY; }
	std::vector<G4double>& GetVectorPbGlassGEnterZ() {return RunVectorPbGlassGEnterZ; }
	std::vector<G4double>& GetVectorPbGlassGEnterPX() {return RunVectorPbGlassGEnterPX; }
	std::vector<G4double>& GetVectorPbGlassGEnterPY() {return RunVectorPbGlassGEnterPY; }
	std::vector<G4double>& GetVectorPbGlassGEnterPZ() {return RunVectorPbGlassGEnterPZ; }
	
	std::vector<G4double>& GetVectorPbGlass1ExitEne() {return RunVectorPbGlass1ExitEne; }
	std::vector<G4double>& GetVectorPbGlass1ExitPart() {return RunVectorPbGlass1ExitPart; }
	std::vector<G4double>& GetVectorPbGlass1ExitX() {return RunVectorPbGlass1ExitX; }
	std::vector<G4double>& GetVectorPbGlass1ExitY() {return RunVectorPbGlass1ExitY; }
	std::vector<G4double>& GetVectorPbGlass1ExitZ() {return RunVectorPbGlass1ExitZ; }
	std::vector<G4double>& GetVectorPbGlass1ExitPX() {return RunVectorPbGlass1ExitPX; }
	std::vector<G4double>& GetVectorPbGlass1ExitPY() {return RunVectorPbGlass1ExitPY; }
	std::vector<G4double>& GetVectorPbGlass1ExitPZ() {return RunVectorPbGlass1ExitPZ; }
	
	std::vector<G4double>& GetVectorPbGlass2ExitEne() {return RunVectorPbGlass2ExitEne; }
	std::vector<G4double>& GetVectorPbGlass2ExitPart() {return RunVectorPbGlass2ExitPart; }
	std::vector<G4double>& GetVectorPbGlass2ExitX() {return RunVectorPbGlass2ExitX; }
	std::vector<G4double>& GetVectorPbGlass2ExitY() {return RunVectorPbGlass2ExitY; }
	std::vector<G4double>& GetVectorPbGlass2ExitZ() {return RunVectorPbGlass2ExitZ; }
	std::vector<G4double>& GetVectorPbGlass2ExitPX() {return RunVectorPbGlass2ExitPX; }
	std::vector<G4double>& GetVectorPbGlass2ExitPY() {return RunVectorPbGlass2ExitPY; }
	std::vector<G4double>& GetVectorPbGlass2ExitPZ() {return RunVectorPbGlass2ExitPZ; }

	std::vector<G4double>& GetVectorPbGlassGExitEne() {return RunVectorPbGlassGExitEne; }
	std::vector<G4double>& GetVectorPbGlassGExitPart() {return RunVectorPbGlassGExitPart; }
	std::vector<G4double>& GetVectorPbGlassGExitX() {return RunVectorPbGlassGExitX; }
	std::vector<G4double>& GetVectorPbGlassGExitY() {return RunVectorPbGlassGExitY; }
	std::vector<G4double>& GetVectorPbGlassGExitZ() {return RunVectorPbGlassGExitZ; }
	std::vector<G4double>& GetVectorPbGlassGExitPX() {return RunVectorPbGlassGExitPX; }
	std::vector<G4double>& GetVectorPbGlassGExitPY() {return RunVectorPbGlassGExitPY; }
	std::vector<G4double>& GetVectorPbGlassGExitPZ() {return RunVectorPbGlassGExitPZ; }
	
	std::vector<G4double>& GetVectorDummy1EnterEne() {return RunVectorDummy1EnterEne; }
	std::vector<G4double>& GetVectorDummy1EnterPart() {return RunVectorDummy1EnterPart; }
	std::vector<G4double>& GetVectorDummy1EnterX() {return RunVectorDummy1EnterX; }
	std::vector<G4double>& GetVectorDummy1EnterY() {return RunVectorDummy1EnterY; }
	std::vector<G4double>& GetVectorDummy1EnterZ() {return RunVectorDummy1EnterZ; }
	std::vector<G4double>& GetVectorDummy1EnterVX() {return RunVectorDummy1EnterVX; }
	std::vector<G4double>& GetVectorDummy1EnterVY() {return RunVectorDummy1EnterVY; }
	std::vector<G4double>& GetVectorDummy1EnterVZ() {return RunVectorDummy1EnterVZ; }
	std::vector<G4double>& GetVectorDummy1EnterPX() {return RunVectorDummy1EnterPX; }
	std::vector<G4double>& GetVectorDummy1EnterPY() {return RunVectorDummy1EnterPY; }
	std::vector<G4double>& GetVectorDummy1EnterPZ() {return RunVectorDummy1EnterPZ; }
	
	std::vector<G4double>& GetVectorDummy2EnterEne() {return RunVectorDummy2EnterEne; }
	std::vector<G4double>& GetVectorDummy2EnterPart() {return RunVectorDummy2EnterPart; }
	std::vector<G4double>& GetVectorDummy2EnterX() {return RunVectorDummy2EnterX; }
	std::vector<G4double>& GetVectorDummy2EnterY() {return RunVectorDummy2EnterY; }
	std::vector<G4double>& GetVectorDummy2EnterZ() {return RunVectorDummy2EnterZ; }
	std::vector<G4double>& GetVectorDummy2EnterVX() {return RunVectorDummy2EnterVX; }
	std::vector<G4double>& GetVectorDummy2EnterVY() {return RunVectorDummy2EnterVY; }
	std::vector<G4double>& GetVectorDummy2EnterVZ() {return RunVectorDummy2EnterVZ; }
	std::vector<G4double>& GetVectorDummy2EnterPX() {return RunVectorDummy2EnterPX; }
	std::vector<G4double>& GetVectorDummy2EnterPY() {return RunVectorDummy2EnterPY; }
	std::vector<G4double>& GetVectorDummy2EnterPZ() {return RunVectorDummy2EnterPZ; }
	
	
	std::vector<G4double>& GetVectorCe1EnterEne() {return RunVectorCe1EnterEne; }
	std::vector<G4double>& GetVectorCe1EnterPart() {return RunVectorCe1EnterPart; }
	std::vector<G4double>& GetVectorCe1EnterX() {return RunVectorCe1EnterX; }
	std::vector<G4double>& GetVectorCe1EnterY() {return RunVectorCe1EnterY; }
	std::vector<G4double>& GetVectorCe1EnterZ() {return RunVectorCe1EnterZ; }
	std::vector<G4double>& GetVectorCe1EnterVX() {return RunVectorCe1EnterVX; }
	std::vector<G4double>& GetVectorCe1EnterVY() {return RunVectorCe1EnterVY; }
	std::vector<G4double>& GetVectorCe1EnterVZ() {return RunVectorCe1EnterVZ; }
	std::vector<G4double>& GetVectorCe1EnterPX() {return RunVectorCe1EnterPX; }
	std::vector<G4double>& GetVectorCe1EnterPY() {return RunVectorCe1EnterPY; }
	std::vector<G4double>& GetVectorCe1EnterPZ() {return RunVectorCe1EnterPZ; }

	std::vector<G4double>& GetVectorCe2EnterEne() {return RunVectorCe2EnterEne; }
	std::vector<G4double>& GetVectorCe2EnterPart() {return RunVectorCe2EnterPart; }
	std::vector<G4double>& GetVectorCe2EnterX() {return RunVectorCe2EnterX; }
	std::vector<G4double>& GetVectorCe2EnterY() {return RunVectorCe2EnterY; }
	std::vector<G4double>& GetVectorCe2EnterZ() {return RunVectorCe2EnterZ; }
	std::vector<G4double>& GetVectorCe2EnterVX() {return RunVectorCe2EnterVX; }
	std::vector<G4double>& GetVectorCe2EnterVY() {return RunVectorCe2EnterVY; }
	std::vector<G4double>& GetVectorCe2EnterVZ() {return RunVectorCe2EnterVZ; }
	std::vector<G4double>& GetVectorCe2EnterPX() {return RunVectorCe2EnterPX; }
	std::vector<G4double>& GetVectorCe2EnterPY() {return RunVectorCe2EnterPY; }
	std::vector<G4double>& GetVectorCe2EnterPZ() {return RunVectorCe2EnterPZ; }

	std::vector<G4double>& GetVectorS4EnterEne() {return RunVectorS4EnterEne; }
	std::vector<G4double>& GetVectorS4EnterPart() {return RunVectorS4EnterPart; }
	std::vector<G4double>& GetVectorS4EnterX() {return RunVectorS4EnterX; }
	std::vector<G4double>& GetVectorS4EnterY() {return RunVectorS4EnterY; }
	std::vector<G4double>& GetVectorS4EnterZ() {return RunVectorS4EnterZ; }
	std::vector<G4double>& GetVectorS4EnterVX() {return RunVectorS4EnterVX; }
	std::vector<G4double>& GetVectorS4EnterVY() {return RunVectorS4EnterVY; }
	std::vector<G4double>& GetVectorS4EnterVZ() {return RunVectorS4EnterVZ; }
	std::vector<G4double>& GetVectorS4EnterPX() {return RunVectorS4EnterPX; }
	std::vector<G4double>& GetVectorS4EnterPY() {return RunVectorS4EnterPY; }
	std::vector<G4double>& GetVectorS4EnterPZ() {return RunVectorS4EnterPZ; }
	
	std::vector<G4double>& GetVectorS5EnterEne() {return RunVectorS5EnterEne; }
	std::vector<G4double>& GetVectorS5EnterPart() {return RunVectorS5EnterPart; }
	std::vector<G4double>& GetVectorS5EnterX() {return RunVectorS5EnterX; }
	std::vector<G4double>& GetVectorS5EnterY() {return RunVectorS5EnterY; }
	std::vector<G4double>& GetVectorS5EnterZ() {return RunVectorS5EnterZ; }
	std::vector<G4double>& GetVectorS5EnterVX() {return RunVectorS5EnterVX; }
	std::vector<G4double>& GetVectorS5EnterVY() {return RunVectorS5EnterVY; }
	std::vector<G4double>& GetVectorS5EnterVZ() {return RunVectorS5EnterVZ; }
	std::vector<G4double>& GetVectorS5EnterPX() {return RunVectorS5EnterPX; }
	std::vector<G4double>& GetVectorS5EnterPY() {return RunVectorS5EnterPY; }
	std::vector<G4double>& GetVectorS5EnterPZ() {return RunVectorS5EnterPZ; }
	
	std::vector<G4double>& GetVectorS6EnterEne() {return RunVectorS6EnterEne; }
	std::vector<G4double>& GetVectorS6EnterPart() {return RunVectorS6EnterPart; }
	std::vector<G4double>& GetVectorS6EnterX() {return RunVectorS6EnterX; }
	std::vector<G4double>& GetVectorS6EnterY() {return RunVectorS6EnterY; }
	std::vector<G4double>& GetVectorS6EnterZ() {return RunVectorS6EnterZ; }
	std::vector<G4double>& GetVectorS6EnterVX() {return RunVectorS6EnterVX; }
	std::vector<G4double>& GetVectorS6EnterVY() {return RunVectorS6EnterVY; }
	std::vector<G4double>& GetVectorS6EnterVZ() {return RunVectorS6EnterVZ; }
	std::vector<G4double>& GetVectorS6EnterPX() {return RunVectorS6EnterPX; }
	std::vector<G4double>& GetVectorS6EnterPY() {return RunVectorS6EnterPY; }
	std::vector<G4double>& GetVectorS6EnterPZ() {return RunVectorS6EnterPZ; }
	
	std::vector<G4double>& GetVectorS7EnterEne() {return RunVectorS7EnterEne; }
	std::vector<G4double>& GetVectorS7EnterPart() {return RunVectorS7EnterPart; }
	std::vector<G4double>& GetVectorS7EnterX() {return RunVectorS7EnterX; }
	std::vector<G4double>& GetVectorS7EnterY() {return RunVectorS7EnterY; }
	std::vector<G4double>& GetVectorS7EnterZ() {return RunVectorS7EnterZ; }
	std::vector<G4double>& GetVectorS7EnterVX() {return RunVectorS7EnterVX; }
	std::vector<G4double>& GetVectorS7EnterVY() {return RunVectorS7EnterVY; }
	std::vector<G4double>& GetVectorS7EnterVZ() {return RunVectorS7EnterVZ; }
	std::vector<G4double>& GetVectorS7EnterPX() {return RunVectorS7EnterPX; }
	std::vector<G4double>& GetVectorS7EnterPY() {return RunVectorS7EnterPY; }
	std::vector<G4double>& GetVectorS7EnterPZ() {return RunVectorS7EnterPZ; }
	
	std::vector<G4double>& GetVectorMu1EnterEne() {return RunVectorMu1EnterEne; }
	std::vector<G4double>& GetVectorMu1EnterPart() {return RunVectorMu1EnterPart; }
	std::vector<G4double>& GetVectorMu1EnterX() {return RunVectorMu1EnterX; }
	std::vector<G4double>& GetVectorMu1EnterY() {return RunVectorMu1EnterY; }
	std::vector<G4double>& GetVectorMu1EnterZ() {return RunVectorMu1EnterZ; }
	std::vector<G4double>& GetVectorMu1EnterVX() {return RunVectorMu1EnterVX; }
	std::vector<G4double>& GetVectorMu1EnterVY() {return RunVectorMu1EnterVY; }
	std::vector<G4double>& GetVectorMu1EnterVZ() {return RunVectorMu1EnterVZ; }
	std::vector<G4double>& GetVectorMu1EnterPX() {return RunVectorMu1EnterPX; }
	std::vector<G4double>& GetVectorMu1EnterPY() {return RunVectorMu1EnterPY; }
	std::vector<G4double>& GetVectorMu1EnterPZ() {return RunVectorMu1EnterPZ; }
	std::vector<G4double>& GetVectorMu1EnterCopyNb() {return RunVectorMu1EnterCopyNb; }

	std::vector<G4double>& GetVectorMu2EnterEne() {return RunVectorMu2EnterEne; }
	std::vector<G4double>& GetVectorMu2EnterPart() {return RunVectorMu2EnterPart; }
	std::vector<G4double>& GetVectorMu2EnterX() {return RunVectorMu2EnterX; }
	std::vector<G4double>& GetVectorMu2EnterY() {return RunVectorMu2EnterY; }
	std::vector<G4double>& GetVectorMu2EnterZ() {return RunVectorMu2EnterZ; }
	std::vector<G4double>& GetVectorMu2EnterVX() {return RunVectorMu2EnterVX; }
	std::vector<G4double>& GetVectorMu2EnterVY() {return RunVectorMu2EnterVY; }
	std::vector<G4double>& GetVectorMu2EnterVZ() {return RunVectorMu2EnterVZ; }
	std::vector<G4double>& GetVectorMu2EnterPX() {return RunVectorMu2EnterPX; }
	std::vector<G4double>& GetVectorMu2EnterPY() {return RunVectorMu2EnterPY; }
	std::vector<G4double>& GetVectorMu2EnterPZ() {return RunVectorMu2EnterPZ; }
	std::vector<G4double>& GetVectorMu2EnterCopyNb() {return RunVectorMu2EnterCopyNb; }

	std::vector<G4double>& GetBeamInfoX() {return BeamInfoX; }
	std::vector<G4double>& GetBeamInfoY() {return BeamInfoY; }
	std::vector<G4double>& GetBeamInfoZ() {return BeamInfoZ; }
	std::vector<G4double>& GetBeamInfoCX() {return BeamInfoCX; }
	std::vector<G4double>& GetBeamInfoCY() {return BeamInfoCY; }
	std::vector<G4double>& GetBeamInfoCZ() {return BeamInfoCZ; }
	std::vector<G4double>& GetBeamInfoEne() {return BeamInfoEne; }
	std::vector<G4double>& GetBeamInfoPart() {return BeamInfoPart; }
	
	
	//	std::vector<G4double>& GetNHits() {return RunVectorNHits; }
	//	std::vector<G4double>& GetItrack() {return RunVectorItrack; }
	
	
private:
	std::vector<G4double> RunVectorBeamX;
	std::vector<G4double> RunVectorBeamY;
	std::vector<G4double> RunVectorBeamZ;
	std::vector<G4double> RunVectorBeamCX;
	std::vector<G4double> RunVectorBeamCY;
	std::vector<G4double> RunVectorBeamCZ;
	std::vector<G4double> RunVectorBeamEne;
	std::vector<G4double> RunVectorBeamPart;
	
	std::vector<G4double> RunVectorSubdet;
	std::vector<G4double> RunVectorIdp;
	std::vector<G4double> RunVectorIpar;
	std::vector<G4double> RunVectorItrack;
	std::vector<G4double> RunVectorTime;
	std::vector<G4double> RunVectorX;
	std::vector<G4double> RunVectorY;
	std::vector<G4double> RunVectorZ;
	std::vector<G4double> RunVectorP;
	std::vector<G4double> RunVectorPX;
	std::vector<G4double> RunVectorPY;
	std::vector<G4double> RunVectorPZ;
	std::vector<G4double> RunVectorVertexX;
	std::vector<G4double> RunVectorVertexY;
	std::vector<G4double> RunVectorVertexZ;
	std::vector<G4double> RunVectorKinev;
	std::vector<G4double> RunVectorPXvdir;
	std::vector<G4double> RunVectorPYvdir;
	std::vector<G4double> RunVectorPZvdir;
	std::vector<G4int> RunVectorProcess;
	std::vector<G4double> RunVectorIev;
	std::vector<G4double> RunVectorStep;
	std::vector<G4double> RunVectorInextStep;
	std::vector<G4double> RunVectorCopyNb;
	
	std::vector<G4double> RunVectorCaloEnDep;
	
	std::vector<G4double>  RunVectorGammaConvX;
	std::vector<G4double>  RunVectorGammaConvY;
	std::vector<G4double>  RunVectorGammaConvZ;
	std::vector<G4double>  RunVectorGammaConvEne;
	std::vector<G4double>	RunVectorGammaConvSubdet;
	std::vector<G4double>  RunVectorGammaConvEnePos;
	std::vector<G4double>  RunVectorGammaConvEneEle;
	
	
	
	std::vector<G4double> RunVectorPbGlass1EnterEne;
	std::vector<G4double> RunVectorPbGlass1EnterPart;
	std::vector<G4double> RunVectorPbGlass1EnterX;
	std::vector<G4double> RunVectorPbGlass1EnterY;
	std::vector<G4double> RunVectorPbGlass1EnterZ;
	std::vector<G4double> RunVectorPbGlass1EnterVX;
	std::vector<G4double> RunVectorPbGlass1EnterVY;
	std::vector<G4double> RunVectorPbGlass1EnterVZ;
	std::vector<G4double> RunVectorPbGlass1EnterPX;
	std::vector<G4double> RunVectorPbGlass1EnterPY;
	std::vector<G4double> RunVectorPbGlass1EnterPZ;
	
	std::vector<G4double> RunVectorPbGlass2EnterEne;
	std::vector<G4double> RunVectorPbGlass2EnterPart;
	std::vector<G4double> RunVectorPbGlass2EnterX;
	std::vector<G4double> RunVectorPbGlass2EnterY;
	std::vector<G4double> RunVectorPbGlass2EnterZ;
	std::vector<G4double> RunVectorPbGlass2EnterVX;
	std::vector<G4double> RunVectorPbGlass2EnterVY;
	std::vector<G4double> RunVectorPbGlass2EnterVZ;
	std::vector<G4double> RunVectorPbGlass2EnterPX;
	std::vector<G4double> RunVectorPbGlass2EnterPY;
	std::vector<G4double> RunVectorPbGlass2EnterPZ;
	
	std::vector<G4double> RunVectorPbGlassGEnterEne;
	std::vector<G4double> RunVectorPbGlassGEnterPart;
	std::vector<G4double> RunVectorPbGlassGEnterX;
	std::vector<G4double> RunVectorPbGlassGEnterY;
	std::vector<G4double> RunVectorPbGlassGEnterZ;
	std::vector<G4double> RunVectorPbGlassGEnterPX;
	std::vector<G4double> RunVectorPbGlassGEnterPY;
	std::vector<G4double> RunVectorPbGlassGEnterPZ;
	
	
	std::vector<G4double> RunVectorPbGlass1ExitEne;
	std::vector<G4double> RunVectorPbGlass1ExitPart;
	std::vector<G4double> RunVectorPbGlass1ExitX;
	std::vector<G4double> RunVectorPbGlass1ExitY;
	std::vector<G4double> RunVectorPbGlass1ExitZ;
	std::vector<G4double> RunVectorPbGlass1ExitPX;
	std::vector<G4double> RunVectorPbGlass1ExitPY;
	std::vector<G4double> RunVectorPbGlass1ExitPZ;
	
	std::vector<G4double> RunVectorPbGlass2ExitEne;
	std::vector<G4double> RunVectorPbGlass2ExitPart;
	std::vector<G4double> RunVectorPbGlass2ExitX;
	std::vector<G4double> RunVectorPbGlass2ExitY;
	std::vector<G4double> RunVectorPbGlass2ExitZ;
	std::vector<G4double> RunVectorPbGlass2ExitPX;
	std::vector<G4double> RunVectorPbGlass2ExitPY;
	std::vector<G4double> RunVectorPbGlass2ExitPZ;
	
	std::vector<G4double> RunVectorPbGlassGExitEne;
	std::vector<G4double> RunVectorPbGlassGExitPart;
	std::vector<G4double> RunVectorPbGlassGExitX;
	std::vector<G4double> RunVectorPbGlassGExitY;
	std::vector<G4double> RunVectorPbGlassGExitZ;
	std::vector<G4double> RunVectorPbGlassGExitPX;
	std::vector<G4double> RunVectorPbGlassGExitPY;
	std::vector<G4double> RunVectorPbGlassGExitPZ;
	
	//	std::vector<G4double> RunVectorCerenkovDepo;
	//	std::vector<G4int> RunVectorCerenkovDepoOpt;
	
	std::vector<G4double> RunVectorCross;
	
	std::vector<G4double> RunVectorDummy1EnterEne;
	std::vector<G4double> RunVectorDummy1EnterPart;
	std::vector<G4double> RunVectorDummy1EnterX;
	std::vector<G4double> RunVectorDummy1EnterY;
	std::vector<G4double> RunVectorDummy1EnterZ;
	std::vector<G4double> RunVectorDummy1EnterVX;
	std::vector<G4double> RunVectorDummy1EnterVY;
	std::vector<G4double> RunVectorDummy1EnterVZ;
	std::vector<G4double> RunVectorDummy1EnterPX;
	std::vector<G4double> RunVectorDummy1EnterPY;
	std::vector<G4double> RunVectorDummy1EnterPZ;

	std::vector<G4double> RunVectorDummy2EnterEne;
	std::vector<G4double> RunVectorDummy2EnterPart;
	std::vector<G4double> RunVectorDummy2EnterX;
	std::vector<G4double> RunVectorDummy2EnterY;
	std::vector<G4double> RunVectorDummy2EnterZ;
	std::vector<G4double> RunVectorDummy2EnterVX;
	std::vector<G4double> RunVectorDummy2EnterVY;
	std::vector<G4double> RunVectorDummy2EnterVZ;
	std::vector<G4double> RunVectorDummy2EnterPX;
	std::vector<G4double> RunVectorDummy2EnterPY;
	std::vector<G4double> RunVectorDummy2EnterPZ;
	
	
	std::vector<G4double> RunVectorCe1EnterEne;
	std::vector<G4double> RunVectorCe1EnterPart;
	std::vector<G4double> RunVectorCe1EnterX;
	std::vector<G4double> RunVectorCe1EnterY;
	std::vector<G4double> RunVectorCe1EnterZ;
	std::vector<G4double> RunVectorCe1EnterVX;
	std::vector<G4double> RunVectorCe1EnterVY;
	std::vector<G4double> RunVectorCe1EnterVZ;
	std::vector<G4double> RunVectorCe1EnterPX;
	std::vector<G4double> RunVectorCe1EnterPY;
	std::vector<G4double> RunVectorCe1EnterPZ;
	
	std::vector<G4double> RunVectorCe2EnterEne;
	std::vector<G4double> RunVectorCe2EnterPart;
	std::vector<G4double> RunVectorCe2EnterX;
	std::vector<G4double> RunVectorCe2EnterY;
	std::vector<G4double> RunVectorCe2EnterZ;
	std::vector<G4double> RunVectorCe2EnterVX;
	std::vector<G4double> RunVectorCe2EnterVY;
	std::vector<G4double> RunVectorCe2EnterVZ;
	std::vector<G4double> RunVectorCe2EnterPX;
	std::vector<G4double> RunVectorCe2EnterPY;
	std::vector<G4double> RunVectorCe2EnterPZ;
	
	std::vector<G4double> RunVectorS4EnterEne;
	std::vector<G4double> RunVectorS4EnterPart;
	std::vector<G4double> RunVectorS4EnterX;
	std::vector<G4double> RunVectorS4EnterY;
	std::vector<G4double> RunVectorS4EnterZ;
	std::vector<G4double> RunVectorS4EnterVX;
	std::vector<G4double> RunVectorS4EnterVY;
	std::vector<G4double> RunVectorS4EnterVZ;
	std::vector<G4double> RunVectorS4EnterPX;
	std::vector<G4double> RunVectorS4EnterPY;
	std::vector<G4double> RunVectorS4EnterPZ;

	std::vector<G4double> RunVectorS5EnterEne;
	std::vector<G4double> RunVectorS5EnterPart;
	std::vector<G4double> RunVectorS5EnterX;
	std::vector<G4double> RunVectorS5EnterY;
	std::vector<G4double> RunVectorS5EnterZ;
	std::vector<G4double> RunVectorS5EnterVX;
	std::vector<G4double> RunVectorS5EnterVY;
	std::vector<G4double> RunVectorS5EnterVZ;
	std::vector<G4double> RunVectorS5EnterPX;
	std::vector<G4double> RunVectorS5EnterPY;
	std::vector<G4double> RunVectorS5EnterPZ;
	
	std::vector<G4double> RunVectorS6EnterEne;
	std::vector<G4double> RunVectorS6EnterPart;
	std::vector<G4double> RunVectorS6EnterX;
	std::vector<G4double> RunVectorS6EnterY;
	std::vector<G4double> RunVectorS6EnterZ;
	std::vector<G4double> RunVectorS6EnterVX;
	std::vector<G4double> RunVectorS6EnterVY;
	std::vector<G4double> RunVectorS6EnterVZ;
	std::vector<G4double> RunVectorS6EnterPX;
	std::vector<G4double> RunVectorS6EnterPY;
	std::vector<G4double> RunVectorS6EnterPZ;
	
	std::vector<G4double> RunVectorS7EnterEne;
	std::vector<G4double> RunVectorS7EnterPart;
	std::vector<G4double> RunVectorS7EnterX;
	std::vector<G4double> RunVectorS7EnterY;
	std::vector<G4double> RunVectorS7EnterZ;
	std::vector<G4double> RunVectorS7EnterVX;
	std::vector<G4double> RunVectorS7EnterVY;
	std::vector<G4double> RunVectorS7EnterVZ;
	std::vector<G4double> RunVectorS7EnterPX;
	std::vector<G4double> RunVectorS7EnterPY;
	std::vector<G4double> RunVectorS7EnterPZ;

	std::vector<G4double> RunVectorMu1EnterEne;
	std::vector<G4double> RunVectorMu1EnterPart;
	std::vector<G4double> RunVectorMu1EnterX;
	std::vector<G4double> RunVectorMu1EnterY;
	std::vector<G4double> RunVectorMu1EnterZ;
	std::vector<G4double> RunVectorMu1EnterVX;
	std::vector<G4double> RunVectorMu1EnterVY;
	std::vector<G4double> RunVectorMu1EnterVZ;
	std::vector<G4double> RunVectorMu1EnterPX;
	std::vector<G4double> RunVectorMu1EnterPY;
	std::vector<G4double> RunVectorMu1EnterPZ;
	std::vector<G4double> RunVectorMu1EnterCopyNb;

	std::vector<G4double> RunVectorMu2EnterEne;
	std::vector<G4double> RunVectorMu2EnterPart;
	std::vector<G4double> RunVectorMu2EnterX;
	std::vector<G4double> RunVectorMu2EnterY;
	std::vector<G4double> RunVectorMu2EnterZ;
	std::vector<G4double> RunVectorMu2EnterVX;
	std::vector<G4double> RunVectorMu2EnterVY;
	std::vector<G4double> RunVectorMu2EnterVZ;
	std::vector<G4double> RunVectorMu2EnterPX;
	std::vector<G4double> RunVectorMu2EnterPY;
	std::vector<G4double> RunVectorMu2EnterPZ;
	std::vector<G4double> RunVectorMu2EnterCopyNb;

	std::vector<G4double> BeamInfoX;
	std::vector<G4double> BeamInfoY;
	std::vector<G4double> BeamInfoZ;
	std::vector<G4double> BeamInfoCX;
	std::vector<G4double> BeamInfoCY;
	std::vector<G4double> BeamInfoCZ;
	std::vector<G4double> BeamInfoEne;
	std::vector<G4double> BeamInfoPart;
	
	std::map<G4int,G4int> fChannelMap;
	
	//	std::vector<G4double> RunVectorNHits;
	//	std::vector<G4double> RunVectorItrack;
	
	
};


#endif

