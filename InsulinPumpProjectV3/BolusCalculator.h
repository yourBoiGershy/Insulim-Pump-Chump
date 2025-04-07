#ifndef BOLUSCALCULATOR_H
#define BOLUSCALCULATOR_H

class BolusCalculator {
public:
    float calculateCarbBolus(float carbs, float icr);
    float calculateCorrectionBolus(float currentBG, float targetBG, float correctionFactor);
    float calculateTotalBolus(float carbBolus, float correctionBolus);
    float adjustForIOB(float totalBolus, float IOB);
    float calculateImmediateBolus(float finalBolus, float immediateFraction = 0.6f);
    float calculateExtendedBolus(float finalBolus, float immediateFraction = 0.6f);
};

#endif 