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
// $Id: MonoChromActionInitialization.cc 68058 2013-03-13 14:47:43Z gcosmo $
//
/// \file MonoChromActionInitialization.cc
/// \brief Implementation of the MonoChromActionInitialization class

#include "MonoChromActionInitialization.hh"
#include "MonoChromPrimaryGeneratorAction.hh"
#include "MonoChromRunAction.hh"
#include "MonoChromSteppingAction.hh"
#include "MonoChromStackingAction.hh"
#include "MonoChromSteppingVerbose.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MonoChromActionInitialization::MonoChromActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MonoChromActionInitialization::~MonoChromActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MonoChromActionInitialization::BuildForMaster() const
{
  SetUserAction(new MonoChromRunAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MonoChromActionInitialization::Build() const
{
  SetUserAction(new MonoChromPrimaryGeneratorAction());
  SetUserAction(new MonoChromRunAction());
  SetUserAction(new MonoChromSteppingAction());
  SetUserAction(new MonoChromStackingAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VSteppingVerbose*
               MonoChromActionInitialization::InitializeSteppingVerbose() const
{
  return new MonoChromSteppingVerbose();
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
