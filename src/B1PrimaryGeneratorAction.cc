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
//
/// \file B1PrimaryGeneratorAction.cc
/// \brief Implementation of the B1PrimaryGeneratorAction class

#include "B1PrimaryGeneratorAction.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <iostream>
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1PrimaryGeneratorAction::B1PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fParticleGun(0)
{
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="neutron");
  fParticleGun->SetParticleDefinition(particle);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1PrimaryGeneratorAction::~B1PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//A solid spherical source - by AIT
void B1PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4double radius=100*cm;
  G4double x0=G4RandGauss::shoot();
  G4double y0=G4RandGauss::shoot();
  G4double z0=G4RandGauss::shoot();
  G4double n0=sqrt(pow(x0,2)+pow(y0,2)+pow(z0,2));
  x0 = radius*(x0/n0); 
  y0 = radius*(y0/n0);
  z0 = radius*(z0/n0); 
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
  G4double x1=0;
  G4double y1=0;
  G4double z1=0;
  G4double mx = x0-x1;
  G4double my = y0-y1;
  G4double mz = z0-z1;
  G4double mn = sqrt(pow(mx,2)+pow(my,2)+pow(mz,2));
  mx = mx/mn;
  my = my/mn;
  mz = mz/mn;    
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(mx,my,mz));
  G4double Energy=14*MeV;
  fParticleGun->SetParticleEnergy(Energy);
  fParticleGun->GeneratePrimaryVertex(anEvent);
  }
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

