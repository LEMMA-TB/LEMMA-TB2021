//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file eventgenerator/HepMC/HepMCEx01/src/HepMCG4AsciiReader.cc
/// \brief Implementation of the HepMCG4AsciiReader class
//
// $Id: HepMCG4AsciiReader.cc 77801 2013-11-28 13:33:20Z gcosmo $
//

#include "HepMCG4AsciiReader.hh"
//#include "HepMCG4AsciiReaderMessenger.hh"

#include <iostream>
#include <fstream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
HepMCG4AsciiReader::HepMCG4AsciiReader(G4String nomefile)
//:  filename("test02.dat"), verbose(0)
:  filename(nomefile), verbose(0)
{
	asciiInput= new HepMC::IO_GenEvent(filename.c_str(), std::ios::in);
//	G4cout<<"DEBUG HEP: leggo file "<<filename.c_str()<<G4endl;
	this->Initialize();
	G4cout<<"DEBUG HEP: letto file "<<(this->GetFileName()).c_str()<<G4endl;
	//  messenger= new HepMCG4AsciiReaderMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
HepMCG4AsciiReader::~HepMCG4AsciiReader()
{
	delete asciiInput;
	//  delete messenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void HepMCG4AsciiReader::Initialize()
{
	delete asciiInput;
	
	asciiInput= new HepMC::IO_GenEvent(filename.c_str(), std::ios::in);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
HepMC::GenEvent* HepMCG4AsciiReader::GenerateHepMCEvent()
{
	HepMC::GenEvent* evt= asciiInput-> read_next_event();
	if(!evt) return 0; // no more event
//	G4cout<<"DEBUG HEP: stampo evento "<<G4endl;
	if(verbose>0) evt-> print();
	
	return evt;
}
