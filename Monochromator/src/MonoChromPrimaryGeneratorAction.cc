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
/// \file MonoChrom/src/MonoChromPrimaryGeneratorAction.cc
/// \brief Implementation of the MonoChromPrimaryGeneratorAction class
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "MonoChromPrimaryGeneratorAction.hh"
#include "MonoChromPrimaryGeneratorMessenger.hh"

#include "Randomize.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MonoChromPrimaryGeneratorAction::MonoChromPrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(), 
   fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun = new G4ParticleGun(n_particle);

  //create a messenger for this class
  fGunMessenger = new MonoChromPrimaryGeneratorMessenger(this);

  //default kinematic
  //
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  //G4ParticleDefinition* particle = particleTable->FindParticle("e+");
  G4ParticleDefinition* particle = particleTable->FindParticle("opticalphoton");
  
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleTime(0.0*ns);
  
  G4ThreeVector p000(0.0*m,0.0*m,-0.499*m);
  G4ThreeVector v001(0,0,1);
  
  fParticleGun->SetParticlePosition(p000);
  fParticleGun->SetParticleMomentumDirection(v001);

  
  fParticleGun->SetParticleEnergy(2.25*eV); // 550 nm
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MonoChromPrimaryGeneratorAction::~MonoChromPrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fGunMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MonoChromPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  SetOptPhotonPolar();

  fParticleGun->GeneratePrimaryVertex(anEvent);
  
  // G4double energies[] = {1.70*eV,2.05*eV,2.15*eV,2.30*eV,2.50*eV,
// 			 2.65*eV,3.00*eV};
  
//   G4double energies[] = {1.68*eV,3.25*eV};
  
//   G4double energy;
//   G4int    steps  = 20;

//   for (int i = 0 ; i < steps; i++){
//     energy = energies[0] + (G4double)i*(energies[1]-energies[0])/steps;
//     G4cout << " energy = " << energy << G4endl;
//     fParticleGun->SetParticleEnergy(energy);
//     fParticleGun->GeneratePrimaryVertex(anEvent);
//   }



}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MonoChromPrimaryGeneratorAction::SetOptPhotonPolar()
{
  
  G4cout << "\n Setting Polarisation \n " << G4endl;
  
  G4double angle = G4UniformRand() * 360.0*deg;
  SetOptPhotonPolar(angle);
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MonoChromPrimaryGeneratorAction::SetOptPhotonPolar(G4double angle)
{
 if (fParticleGun->GetParticleDefinition()->GetParticleName()!="opticalphoton")
   {
     G4cout << "--> warning from PrimaryGeneratorAction::SetOptPhotonPolar() :"
               "the particleGun is not an opticalphoton" << G4endl;
     return;
   }

 G4ThreeVector normal (1., 0., 0.);
 G4ThreeVector kphoton = fParticleGun->GetParticleMomentumDirection();
 G4ThreeVector product = normal.cross(kphoton);
 G4double modul2       = product*product;
 
 G4ThreeVector e_perpend (0., 0., 1.);
 if (modul2 > 0.) e_perpend = (1./std::sqrt(modul2))*product;
 G4ThreeVector e_paralle    = e_perpend.cross(kphoton);
 
 G4ThreeVector polar = std::cos(angle)*e_paralle + std::sin(angle)*e_perpend;
 fParticleGun->SetParticlePolarization(polar);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
