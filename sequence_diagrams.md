# Sequence Diagrams for Insulin Pump Simulator

This document contains sequence diagrams for the key scenarios in the Insulin Pump Simulator application.

## 1. Manual Bolus with Manually Entered Glucose Level

```
User                    BolusScreen              HomeScreen              InsulinPump
  |                         |                        |                       |
  |  Click Bolus Button     |                        |                       |
  | ----------------------> |                        |                       |
  |                         |                        |                       |
  |  Enter Carbs            |                        |                       |
  | ----------------------> |                        |                       |
  |                         |                        |                       |
  |  Enter Glucose Level    |                        |                       |
  | ----------------------> |                        |                       |
  |                         |                        |                       |
  |  Click Calculate        |                        |                       |
  | ----------------------> |                        |                       |
  |                         |                        |                       |
  |                         | Calculate Insulin Dose |                       |
  |                         | --------------------- |                        |
  |                         |                        |                       |
  |                         | Display Calculation    |                       |
  | <---------------------- |                        |                       |
  |                         |                        |                       |
  |  Confirm Bolus          |                        |                       |
  | ----------------------> |                        |                       |
  |                         |                        |                       |
  |                         | Administer Insulin     |                       |
  |                         | ------------------------------------------------> |
  |                         |                        |                       |
  |                         | Signal Insulin Administered                    |
  |                         | ----------------------> |                       |
  |                         |                        |                       |
  |                         |                        | Update IOB Display    |
  |                         |                        | ------------------- |  |
  |                         |                        |                       |
  |                         |                        | Update Glucose Graph  |
  |                         |                        | ------------------- |  |
  |                         |                        |                       |
  |                         | Show Confirmation      |                       |
  | <---------------------- |                        |                       |
  |                         |                        |                       |
  |  Return to Home         |                        |                       |
  | ----------------------> |                        |                       |
  |                         |                        |                       |
  |                         | Switch to Home Screen  |                       |
  |                         | ----------------------> |                       |
  |                         |                        |                       |
```

## 2. Manual Bolus with Auto-populated Glucose from CGM

```
User                    BolusScreen              HomeScreen              CGM                  InsulinPump
  |                         |                        |                      |                      |
  |  Click Bolus Button     |                        |                      |                      |
  | ----------------------> |                        |                      |                      |
  |                         |                        |                      |                      |
  |                         | Request Current BG     |                      |                      |
  |                         | -------------------------------------------------------->           |
  |                         |                        |                      |                      |
  |                         |                        |                      | Return Current BG    |
  |                         | <--------------------------------------------------------           |
  |                         |                        |                      |                      |
  |                         | Auto-populate BG Field |                      |                      |
  |                         | --------------------- |                       |                      |
  |                         |                        |                      |                      |
  |  Enter Carbs            |                        |                      |                      |
  | ----------------------> |                        |                      |                      |
  |                         |                        |                      |                      |
  |  Click Calculate        |                        |                      |                      |
  | ----------------------> |                        |                      |                      |
  |                         |                        |                      |                      |
  |                         | Calculate Insulin Dose |                      |                      |
  |                         | --------------------- |                       |                      |
  |                         |                        |                      |                      |
  |                         | Display Calculation    |                      |                      |
  | <---------------------- |                        |                      |                      |
  |                         |                        |                      |                      |
  |  Confirm Bolus          |                        |                      |                      |
  | ----------------------> |                        |                      |                      |
  |                         |                        |                      |                      |
  |                         | Administer Insulin     |                      |                      |
  |                         | -------------------------------------------------------------->      |
  |                         |                        |                      |                      |
  |                         | Signal Insulin Administered                   |                      |
  |                         | ----------------------> |                      |                      |
  |                         |                        |                      |                      |
  |                         |                        | Update IOB Display   |                      |
  |                         |                        | ------------------- | |                      |
  |                         |                        |                      |                      |
  |                         |                        | Update Glucose Graph |                      |
  |                         |                        | ------------------- | |                      |
  |                         |                        |                      |                      |
  |                         | Show Confirmation      |                      |                      |
  | <---------------------- |                        |                      |                      |
  |                         |                        |                      |                      |
  |  Return to Home         |                        |                      |                      |
  | ----------------------> |                        |                      |                      |
  |                         |                        |                      |                      |
  |                         | Switch to Home Screen  |                      |                      |
  |                         | ----------------------> |                      |                      |
  |                         |                        |                      |                      |
```

## 3. Setting Up a Personal Profile

```
User                    ProfileScreen           ProfileManager          InsulinPump
  |                         |                        |                      |
  |  Click Options Button   |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |  Click Profiles         |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |  Click Create Profile   |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |  Enter Profile Name     |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |  Set Insulin-to-Carb    |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |  Set Correction Factor  |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |  Set Target BG          |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |  Set Basal Rate         |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |  Add Time Segment       |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |  Set Segment Settings   |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |  Save Profile           |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |                         | Validate Profile       |                      |
  |                         | --------------------- |                       |
  |                         |                        |                      |
  |                         | Save Profile           |                      |
  |                         | ----------------------> |                      |
  |                         |                        |                      |
  |                         |                        | Store Profile        |
  |                         |                        | ------------------- | |
  |                         |                        |                      |
  |                         |                        | Confirm Saved        |
  |                         | <---------------------- |                      |
  |                         |                        |                      |
  |                         | Show Confirmation      |                      |
  | <---------------------- |                        |                      |
  |                         |                        |                      |
  |  Activate Profile       |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |                         | Set Active Profile     |                      |
  |                         | ----------------------> |                      |
  |                         |                        |                      |
  |                         |                        | Apply Profile        |
  |                         |                        | ----------------------> |
  |                         |                        |                      |
  |                         |                        | Confirm Applied      |
  |                         | <---------------------- |                      |
  |                         |                        |                      |
  |                         | Show Success           |                      |
  | <---------------------- |                        |                      |
  |                         |                        |                      |
```

## 4. Control-IQ Technology Scenario

```
CGM                     ControlIQ               HomeScreen              InsulinPump
  |                         |                        |                      |
  | New Glucose Reading     |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |                         | Update Current BG      |                      |
  |                         | ----------------------> |                      |
  |                         |                        |                      |
  |                         |                        | Update BG Display    |
  |                         |                        | ------------------- | |
  |                         |                        |                      |
  |                         |                        | Update Graph         |
  |                         |                        | ------------------- | |
  |                         |                        |                      |
  |                         | Predict BG in 30min    |                      |
  |                         | --------------------- |                       |
  |                         |                        |                      |
  |                         | Check if BG Rising     |                      |
  |                         | --------------------- |                       |
  |                         |                        |                      |
  |                         | Increase Insulin       |                      |
  |                         | --------------------------------------------------------> |
  |                         |                        |                      |
  |                         | Update IOB             |                      |
  |                         | ----------------------> |                      |
  |                         |                        |                      |
  |                         |                        | Update IOB Display   |
  |                         |                        | ------------------- | |
  |                         |                        |                      |
  |                         | Log Event              |                      |
  |                         | ----------------------> |                      |
  |                         |                        |                      |
  |                         |                        | Add to History Log   |
  |                         |                        | ------------------- | |
  |                         |                        |                      |
```

## 5. Low Glucose Suspension Scenario

```
CGM                     ControlIQ               HomeScreen              InsulinPump
  |                         |                        |                      |
  | Low Glucose Reading     |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |                         | Update Current BG      |                      |
  |                         | ----------------------> |                      |
  |                         |                        |                      |
  |                         |                        | Update BG Display    |
  |                         |                        | ------------------- | |
  |                         |                        |                      |
  |                         |                        | Update Graph         |
  |                         |                        | ------------------- | |
  |                         |                        |                      |
  |                         | Detect Low BG (<3.9)   |                      |
  |                         | --------------------- |                       |
  |                         |                        |                      |
  |                         | Suspend Insulin        |                      |
  |                         | --------------------------------------------------------> |
  |                         |                        |                      |
  |                         | Show Alert             |                      |
  |                         | ----------------------> |                      |
  |                         |                        |                      |
  |                         |                        | Display Low BG Alert |
  |                         |                        | ------------------- | |
  |                         |                        |                      |
  |                         | Log Suspension Event   |                      |
  |                         | ----------------------> |                      |
  |                         |                        |                      |
  |                         |                        | Add to History Log   |
  |                         |                        | ------------------- | |
  |                         |                        |                      |
  | BG Rises Above 4.4      |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |                         | Resume Insulin         |                      |
  |                         | --------------------------------------------------------> |
  |                         |                        |                      |
  |                         | Log Resume Event       |                      |
  |                         | ----------------------> |                      |
  |                         |                        |                      |
  |                         |                        | Add to History Log   |
  |                         |                        | ------------------- | |
  |                         |                        |                      |
```

## 6. Extended Bolus Scenario

```
User                    BolusScreen              HomeScreen              InsulinPump
  |                         |                        |                      |
  |  Click Bolus Button     |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |  Enter Carbs (50g)      |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |  Enter Glucose (7 mmol/L)|                       |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |  Select Extended Bolus  |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |  Set 60% Now, 40% Over  |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |  Set Duration (3 hours) |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |  Click Calculate        |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |                         | Calculate Total Dose   |                      |
  |                         | (52 - 5 IOB = 47 units)|                      |
  |                         | --------------------- |                       |
  |                         |                        |                      |
  |                         | Calculate Immediate    |                      |
  |                         | (60% = 28.2 units)     |                      |
  |                         | --------------------- |                       |
  |                         |                        |                      |
  |                         | Calculate Extended     |                      |
  |                         | (40% = 18.8 units)     |                      |
  |                         | --------------------- |                       |
  |                         |                        |                      |
  |                         | Display Calculation    |                      |
  | <---------------------- |                        |                      |
  |                         |                        |                      |
  |  Confirm Bolus          |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |                         | Deliver Immediate Dose |                      |
  |                         | --------------------------------------------------------> |
  |                         |                        |                      |
  |                         | Setup Extended Delivery|                      |
  |                         | (6.27 units/hour)      |                      |
  |                         | --------------------------------------------------------> |
  |                         |                        |                      |
  |                         | Signal Insulin Started |                      |
  |                         | ----------------------> |                      |
  |                         |                        |                      |
  |                         |                        | Update IOB Display   |
  |                         |                        | ------------------- | |
  |                         |                        |                      |
  |                         |                        | Update Extended Status|
  |                         |                        | ------------------- | |
  |                         |                        |                      |
  |                         | Show Confirmation      |                      |
  | <---------------------- |                        |                      |
  |                         |                        |                      |
  |  Return to Home         |                        |                      |
  | ----------------------> |                        |                      |
  |                         |                        |                      |
  |                         | Switch to Home Screen  |                      |
  |                         | ----------------------> |                      |
  |                         |                        |                      |
```