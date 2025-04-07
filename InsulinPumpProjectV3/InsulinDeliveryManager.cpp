#include "InsulinDeliveryManager.h"
#include <iostream>

InsulinDeliveryManager::InsulinDeliveryManager() 
    : basalRate(1.0f), activeDelivery(false), currentBasalRate(1.0f) {}

void InsulinDeliveryManager::startBasalDelivery() {
    activeDelivery = true;
    std::cout << "Basal insulin delivery started at rate: " << currentBasalRate << " units/hour." << std::endl;
}

void InsulinDeliveryManager::suspendBasalDelivery() {
    activeDelivery = false;
    std::cout << "Basal insulin delivery suspended." << std::endl;
}

void InsulinDeliveryManager::resumeBasalDelivery() {
    activeDelivery = true;
    std::cout << "Basal insulin delivery resumed at rate: " << currentBasalRate << " units/hour." << std::endl;
}

void InsulinDeliveryManager::adjustDeliveryRate(float newRate) {
    basalRate = newRate;
    currentBasalRate = newRate;
    std::cout << "Basal delivery rate adjusted to: " << currentBasalRate << " units/hour." << std::endl;
}

bool InsulinDeliveryManager::isDelivering() const {
    return activeDelivery;
}

float InsulinDeliveryManager::getBasalRate() const {
    return basalRate;
}

void InsulinDeliveryManager::setDynamicBasalRate(float newRate) {
    currentBasalRate = newRate;
}

float InsulinDeliveryManager::getDynamicBasalRate() const {
    return currentBasalRate;
}