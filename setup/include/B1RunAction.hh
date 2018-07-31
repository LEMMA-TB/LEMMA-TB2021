#ifndef B1RunAction_h
#define B1RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include <vector>


class G4Run;
class G4LogicalVolume;
class B1RunAction : public G4UserRunAction
{
  public:
    B1RunAction(const std::vector<G4int> &);
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
	std::vector<G4double>& GetVectorPbGlass1EnterPX() {return RunVectorPbGlass1EnterPX; }
	std::vector<G4double>& GetVectorPbGlass1EnterPY() {return RunVectorPbGlass1EnterPY; }
	std::vector<G4double>& GetVectorPbGlass1EnterPZ() {return RunVectorPbGlass1EnterPZ; }
	
	std::vector<G4double>& GetVectorPbGlass2EnterEne() {return RunVectorPbGlass2EnterEne; }
	std::vector<G4double>& GetVectorPbGlass2EnterPart() {return RunVectorPbGlass2EnterPart; }
	std::vector<G4double>& GetVectorPbGlass2EnterX() {return RunVectorPbGlass2EnterX; }
	std::vector<G4double>& GetVectorPbGlass2EnterY() {return RunVectorPbGlass2EnterY; }
	std::vector<G4double>& GetVectorPbGlass2EnterZ() {return RunVectorPbGlass2EnterZ; }
	std::vector<G4double>& GetVectorPbGlass2EnterPX() {return RunVectorPbGlass2EnterPX; }
	std::vector<G4double>& GetVectorPbGlass2EnterPY() {return RunVectorPbGlass2EnterPY; }
	std::vector<G4double>& GetVectorPbGlass2EnterPZ() {return RunVectorPbGlass2EnterPZ; }
	
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
	std::vector<G4double> RunVectorPbGlass1EnterPX;
	std::vector<G4double> RunVectorPbGlass1EnterPY;
	std::vector<G4double> RunVectorPbGlass1EnterPZ;
	
	std::vector<G4double> RunVectorPbGlass2EnterEne;
	std::vector<G4double> RunVectorPbGlass2EnterPart;
	std::vector<G4double> RunVectorPbGlass2EnterX;
	std::vector<G4double> RunVectorPbGlass2EnterY;
	std::vector<G4double> RunVectorPbGlass2EnterZ;
	std::vector<G4double> RunVectorPbGlass2EnterPX;
	std::vector<G4double> RunVectorPbGlass2EnterPY;
	std::vector<G4double> RunVectorPbGlass2EnterPZ;
	
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
	
	//	std::vector<G4double> RunVectorCerenkovDepo;
//	std::vector<G4int> RunVectorCerenkovDepoOpt;

	std::vector<G4double> RunVectorCross;

	
	
	std::vector<G4double> BeamInfoX;
	std::vector<G4double> BeamInfoY;
	std::vector<G4double> BeamInfoZ;
	std::vector<G4double> BeamInfoCX;
	std::vector<G4double> BeamInfoCY;
	std::vector<G4double> BeamInfoCZ;
	std::vector<G4double> BeamInfoEne;
	std::vector<G4double> BeamInfoPart;
	
	std::vector<G4int> fChannelMap;
	
//	std::vector<G4double> RunVectorNHits;
//	std::vector<G4double> RunVectorItrack;

	
};


#endif

