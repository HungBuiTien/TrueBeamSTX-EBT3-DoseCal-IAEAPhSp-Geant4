#include "MyPrimaryGenerator.hh"
#include "G4Event.hh"
#include "G4IAEAphspReader.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	G4String fileName="Varian_TrueBeam6MV_05";
	theIAEAReader = new G4IAEAphspReader(fileName);

	// Shift phase space plane
	G4ThreeVector psfShift(0., 0.,-50*cm);
	//theIAEAReader->SetGlobalPhspTranslation(psfShift);
	theIAEAReader->SetTimesRecycled(0); // particles used 0+1 times
	
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	if (theIAEAReader) delete theIAEAReader;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event* anEvent)
{
    theIAEAReader->GeneratePrimaryVertex(anEvent);
}

