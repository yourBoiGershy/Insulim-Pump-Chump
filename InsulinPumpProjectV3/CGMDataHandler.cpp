#include "CGMDataHandler.h"
#include <cstdlib>
#include <ctime>

CGMDataHandler::CGMDataHandler() : currentGlucose(10.0f), cgmStatus("Disconnected") {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void CGMDataHandler::updateDiabeticGlucose(bool basalActive) {
    // simulates BG drift: if basal is active BG tends to dip otherwise it tends to rise.
    float noise = (static_cast<float>(std::rand()) / RAND_MAX) - 0.5f;
    float delta = basalActive ? (-0.5f + noise) : (0.5f + noise);
    currentGlucose += delta;
    if (currentGlucose < 2.0f) currentGlucose = 2.0f;
    if (currentGlucose > 20.0f) currentGlucose = 20.0f;
    cgmStatus = "Connected";
}

float CGMDataHandler::getCurrentGlucose() const {
    return currentGlucose;
}

float CGMDataHandler::predictGlucose(bool basalActive) {
    // if basal is active it assumes BG to dip, otherwise it will assume a rise
    float noise = (static_cast<float>(std::rand()) / RAND_MAX) - 0.5f;
    if (basalActive) {
        return currentGlucose - 0.25f + noise;
    } else {
        return currentGlucose + 0.25f + noise;
    }
}

void CGMDataHandler::reduceGlucose(float reduction) {
    currentGlucose -= reduction;
    if (currentGlucose < 2.0f) currentGlucose = 2.0f;
}

std::string CGMDataHandler::getStatus() const {
    return cgmStatus;
}