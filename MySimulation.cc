// This is the program to simulate Gamma ART-6000TM
// Version: 2.0
// Date: 02/09/2022
// Author: Hung Bui Tien
// Email: hungbuitien19081997@gmail.com
// Organization: Hanoi University of Science and Technology 


#include <iostream>
#include "G4Types.hh"

#include "G4RunManagerFactory.hh"

#include "G4Types.hh"
#include "Randomize.hh"
#include "G4SteppingVerbose.hh"

#include "G4UImanager.hh"
#include "G4UIcommand.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "MyDetectorConstruction.hh"
#include "PhysicsList.hh"
#include "FTFP_BERT.hh"
#include "MyActionInitialization.hh"
#include "G4GenericBiasingPhysics.hh"

#include "G4ScoringManager.hh"
#include "RE03UserScoreWriter.hh"
#include <ctime>
int main(int argc, char** argv)
{

	// Detect interactive mode (if no macro provided) and define UI session
    	//
	G4UIExecutive* ui = 0;

	// Choose the Random engine and reset the seed (before the RunManager)
	G4int seconds = time(NULL);
	G4Random::setTheSeed(seconds);

	// Construct the default run manager
	auto* runManager = G4RunManagerFactory::CreateRunManager();
	G4int nThreads = 1;
	runManager->SetNumberOfThreads(nThreads);

	// Activate UI-command base scorer
 	G4ScoringManager * scManager = G4ScoringManager::GetScoringManager();
 	scManager->SetVerboseLevel(1);
	//scManager->SetScoreWriter(new RE03UserScoreWriter());

	// Set mandatory initialization classes
	//
	auto detConstruction = new MyDetectorConstruction();
	runManager->SetUserInitialization(detConstruction);

	//auto phys = new PhysicsList();
	G4VModularPhysicsList* phys = new FTFP_BERT;	
	runManager->SetUserInitialization(phys);

	auto actionInitialization = new MyActionInitialization();
	runManager->SetUserInitialization(actionInitialization);


	// Initialize G4 kernel
	//
	runManager->Initialize();

	// Process macro or start UI session
	//
	if (argc == 1)
	{
		ui = new G4UIExecutive(argc, argv);
	}

	// Initialize visualization
	//
	G4VisManager* visManager = new G4VisExecutive();
	visManager->Initialize();

	// Get the pointer to the User Interface manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();

	if (ui)
	{
		// interactive mode : define UI session
		UImanager->ApplyCommand("/control/execute vis.mac");
		ui->SessionStart();
		delete ui;
	}
	else
	{
		// batch mode
		G4String command = "/control/execute ";
		G4String fileName = argv[1];
		UImanager->ApplyCommand(command + fileName);
	}
	
	delete visManager;
	delete runManager;

	return 0;
}