#ifndef CGMDATAHANDLER_H
#define CGMDATAHANDLER_H

#include <string>

class CGMDataHandler {
public:
    CGMDataHandler();
    // updates BG on current conditions 
    void updateDiabeticGlucose(bool basalActive);
    // return the current BG
    float getCurrentGlucose() const;
    // predict BG 30 minutes in the future based on current trend
    float predictGlucose(bool basalActive);
    // apply a reduction to BG 
    void reduceGlucose(float reduction);
    std::string getStatus() const;
private:
    float currentGlucose;
    std::string cgmStatus;
};

#endif 