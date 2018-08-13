#ifndef B1EventAction_h
#define B1EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"


class B1RunAction;


class B1EventAction : public G4UserEventAction
{
public:
  B1EventAction(B1RunAction* runAction, G4int NOfCaloChannels);
  virtual ~B1EventAction();    
  virtual void BeginOfEventAction(const G4Event* evt);
  virtual void EndOfEventAction(const G4Event* evt);
  G4int evtNb;
	G4int NevTot;
	
	void SetBeamX(G4double bx) {fBeamX=bx;}
	void SetBeamY(G4double by) {fBeamY=by;}
	void SetBeamZ(G4double bz) {fBeamZ=bz;}
	void SetBeamCX(G4double bcx) {fBeamCX=bcx;}
	void SetBeamCY(G4double bcy) {fBeamCY=bcy;}
	void SetBeamCZ(G4double bcz) {fBeamCZ=bcz;}
	void SetBeamEne(G4double ben) {fBeamEne=ben;}
	void SetBeamPart(G4double bpart) {fBeamPart=bpart;}
	void AddNHits(G4int bnhits) {fNHits+=bnhits;}
	
#if 0
	void AddPbGlassEne(G4double ene) {fPbGlass_DepEne+=ene;}
	void AddPbGlassCere(G4int nfot) {fPbGlass_PulseHeight+=nfot;}
#endif
//	void AddCerenkovNFot(G4double nfot) {fNCerenkov+=ene;}
	
private:
	B1RunAction* fRunAction;

	G4double fBeamX;
	G4double fBeamY;
	G4double fBeamZ;
	G4double fBeamEne;
	G4double fBeamPart;
	G4double fBeamCX;
	G4double fBeamCY;
	G4double fBeamCZ;
	G4int fNHits;
	G4int fNOfCaloChannels;
//	G4int NHitsCounter;
	G4int fPrintModulo = 1; //in percentage: write every X %

//	G4int fNCerenkov;
//	G4int fNCerenkovPbGlass;

};


#endif

    
