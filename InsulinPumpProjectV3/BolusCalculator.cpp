#include "BolusCalculator.h"

float BolusCalculator::calculateCarbBolus(float carbs, float icr) {
    return carbs / icr;
}

float BolusCalculator::calculateCorrectionBolus(float currentBG, float targetBG, float correctionFactor) {
    float difference = currentBG - targetBG;
    return (difference > 0) ? (difference / correctionFactor) : 0;
}

float BolusCalculator::calculateTotalBolus(float carbBolus, float correctionBolus) {
    return carbBolus + correctionBolus;
}

float BolusCalculator::adjustForIOB(float totalBolus, float IOB) {
    float finalBolus = totalBolus - IOB;
    return (finalBolus > 0) ? finalBolus : 0;
}

float BolusCalculator::calculateImmediateBolus(float finalBolus, float immediateFraction) {
    return finalBolus * immediateFraction;
}

float BolusCalculator::calculateExtendedBolus(float finalBolus, float immediateFraction) {
    return finalBolus * (1 - immediateFraction);
}