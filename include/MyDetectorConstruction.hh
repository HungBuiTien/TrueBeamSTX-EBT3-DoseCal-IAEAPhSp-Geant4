#ifndef MyDetectorConstruction_h
#define MyDetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Cons.hh"

#include "G4MultiUnion.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PVReplica.hh"

#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{

public:
	MyDetectorConstruction();
	~MyDetectorConstruction();
	
	virtual G4VPhysicalVolume *Construct();
	virtual void     ConstructSDandField();

private:
	G4LogicalVolume *logicWorld;
	G4VPhysicalVolume *physWorld;
	G4LogicalVolume *fullWaterPhantomLV;

	void SetJawAperture(G4int idJaw, G4ThreeVector &centre, G4ThreeVector halfSize, G4RotationMatrix *cRotation);
	void target();
	void primaryCollimator();
	void vacuumWindow();
	void ionizationChamber();
	void mirror();
	void Jaw1X();
	void Jaw2X();
	void Jaw1Y();
	void Jaw2Y();
	void WaterPhantom();

	G4bool check_overlap = true;

};

#endif
