#ifndef INSULINDELIVERYMANAGER_H
#define INSULINDELIVERYMANAGER_H

class InsulinDeliveryManager {
public:
    InsulinDeliveryManager();
    void startBasalDelivery();
    void suspendBasalDelivery();
    void resumeBasalDelivery();
    void adjustDeliveryRate(float newRate);
    bool isDelivering() const;
    float getBasalRate() const;
    void setDynamicBasalRate(float newRate);
    float getDynamicBasalRate() const;
private:
    float basalRate;         
    bool activeDelivery;
    float currentBasalRate;  
};

#endif 