#include "retractbeltsphase.h"
#include "commandhandlingphase.h"
RetractBeltsPhase::RetractBeltsPhase(PhaseManager* manager, Movement* movement) : CommandHandlingPhase(movement) {
    this->manager = manager;
    this->movement = movement;
}

void RetractBeltsPhase::doneWithPhase(AsyncWebServerRequest *request) {
    manager->setPhase(PhaseManager::ExtendToHome);
    manager->respondWithState(request);
}

// Mural is already hanging with its pen on the home position (e.g. dragged or jogged there),
// so the belt lengths can be derived from the home coordinates instead of homing on the screws.
void RetractBeltsPhase::resumeTopDistance(AsyncWebServerRequest *request) {
    movement->resumeTopDistance(movement->getTopDistance());
    manager->setPhase(PhaseManager::PenCalibration);
    manager->respondWithState(request);
}

const char* RetractBeltsPhase::getName() {
    return "RetractBelts";
}