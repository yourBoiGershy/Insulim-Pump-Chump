# Sequence Diagrams for Insulin Pump Simulator

This document contains sequence diagrams for the key scenarios in the Insulin Pump Simulator application. These diagrams illustrate the interactions between different components of the system and provide a clear visualization of the application's behavior.

## Key Requirements Addressed

1. **Manual Bolus Delivery**: Both with manually entered glucose levels and auto-populated from CGM.

2. **Personal Profiles Management**:
   - Creating and storing multiple profiles with different settings
   - Switching between profiles (at least 3 different profiles as per requirements)
   - Each profile contains settings for insulin-to-carb ratios, correction factors, and target glucose levels

3. **Control-IQ Technology**: Automatic adjustment of insulin delivery based on CGM readings and predictions.

4. **Safety Features**: Including low glucose suspension and resumption.

5. **Extended Bolus**: Delivering bolus insulin over time with specified percentages.

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

## 3. Setting Up and Managing Personal Profiles

```
User                    ProfileScreen           ProfileManager          InsulinPump          Database
  |                         |                        |                      |                     |
  |  Click Options Button   |                        |                      |                     |
  | ----------------------> |                        |                      |                     |
  |                         |                        |                      |                     |
  |  Click Profiles         |                        |                      |                     |
  | ----------------------> |                        |                      |                     |
  |                         |                        |                      |                     |
  |                         | Request Stored Profiles|                      |                     |
  |                         | ----------------------> |                      |                     |
  |                         |                        |                      |                     |
  |                         |                        | Retrieve Profiles    |                     |
  |                         |                        | -----------------------------------------> |
  |                         |                        |                      |                     |
  |                         |                        |                      | Return Profiles     |
  |                         |                        | <----------------------------------------- |
  |                         |                        |                      |                     |
  |                         | Display Profile List   |                      |                     |
  | <---------------------- |                        |                      |                     |
  |                         |                        |                      |                     |
  |  Click Create Profile   |                        |                      |                     |
  | ----------------------> |                        |                      |                     |
  |                         |                        |                      |                     |
  |  Enter Profile Name     |                        |                      |                     |
  | ----------------------> |                        |                      |                     |
  |                         |                        |                      |                     |
  |  Set Insulin-to-Carb    |                        |                      |                     |
  | ----------------------> |                        |                      |                     |
  |                         |                        |                      |                     |
  |  Set Correction Factor  |                        |                      |                     |
  | ----------------------> |                        |                      |                     |
  |                         |                        |                      |                     |
  |  Set Target BG          |                        |                      |                     |
  | ----------------------> |                        |                      |                     |
  |                         |                        |                      |                     |
  |  Set Basal Rate         |                        |                      |                     |
  | ----------------------> |                        |                      |                     |
  |                         |                        |                      |                     |
  |  Add Time Segment       |                        |                      |                     |
  | ----------------------> |                        |                      |                     |
  |                         |                        |                      |                     |
  |  Set Segment Settings   |                        |                      |                     |
  | ----------------------> |                        |                      |                     |
  |                         |                        |                      |                     |
  |  Save Profile           |                        |                      |                     |
  | ----------------------> |                        |                      |                     |
  |                         |                        |                      |                     |
  |                         | Validate Profile       |                      |                     |
  |                         | --------------------- |                       |                     |
  |                         |                        |                      |                     |
  |                         | Save Profile           |                      |                     |
  |                         | ----------------------> |                      |                     |
  |                         |                        |                      |                     |
  |                         |                        | Store Profile        |                     |
  |                         |                        | -----------------------------------------> |
  |                         |                        |                      |                     |
  |                         |                        |                      | Confirm Stored      |
  |                         |                        | <----------------------------------------- |
  |                         |                        |                      |                     |
  |                         |                        | Confirm Saved        |                     |
  |                         | <---------------------- |                      |                     |
  |                         |                        |                      |                     |
  |                         | Show Confirmation      |                      |                     |
  | <---------------------- |                        |                      |                     |
  |                         |                        |                      |                     |
  |  Activate Profile       |                        |                      |                     |
  | ----------------------> |                        |                      |                     |
  |                         |                        |                      |                     |
  |                         | Set Active Profile     |                      |                     |
  |                         | ----------------------> |                      |                     |
  |                         |                        |                      |                     |
  |                         |                        | Apply Profile        |                     |
  |                         |                        | ----------------------> |                     |
  |                         |                        |                      |                     |
  |                         |                        | Update Active Profile|                     |
  |                         |                        | -----------------------------------------> |
  |                         |                        |                      |                     |
  |                         |                        | Confirm Applied      |                     |
  |                         | <---------------------- |                      |                     |
  |                         |                        |                      |                     |
  |                         | Show Success           |                      |                     |
  | <---------------------- |                        |                      |                     |
  |                         |                        |                      |                     |
```

## 4. Switching Between Multiple Profiles

```
User                    ProfileScreen           ProfileManager          InsulinPump          Database
  |                         |                        |                      |                     |
  |  Click Options Button   |                        |                      |                     |
  | ----------------------> |                        |                      |                     |
  |                         |                        |                      |                     |
  |  Click Profiles         |                        |                      |                     |
  | ----------------------> |                        |                      |                     |
  |                         |                        |                      |                     |
  |                         | Request Stored Profiles|                      |                     |
  |                         | ----------------------> |                      |                     |
  |                         |                        |                      |                     |
  |                         |                        | Retrieve Profiles    |                     |
  |                         |                        | -----------------------------------------> |
  |                         |                        |                      |                     |
  |                         |                        |                      | Return Profiles     |
  |                         |                        | <----------------------------------------- |
  |                         |                        |                      |                     |
  |                         | Display Profile List   |                      |                     |
  |                         | (Morning, Exercise,    |                      |                     |
  |                         |  Night profiles)       |                      |                     |
  | <---------------------- |                        |                      |                     |
  |                         |                        |                      |                     |
  |  Select Exercise Profile|                        |                      |                     |
  | ----------------------> |                        |                      |                     |
  |                         |                        |                      |                     |
  |                         | Show Profile Details   |                      |                     |
  | <---------------------- |                        |                      |                     |
  |                         |                        |                      |                     |
  |  Click Activate Profile |                        |                      |                     |
  | ----------------------> |                        |                      |                     |
  |                         |                        |                      |                     |
  |                         | Set Active Profile     |                      |                     |
  |                         | ----------------------> |                      |                     |
  |                         |                        |                      |                     |
  |                         |                        | Apply Profile        |                     |
  |                         |                        | ----------------------> |                     |
  |                         |                        |                      |                     |
  |                         |                        | Update Active Profile|                     |
  |                         |                        | -----------------------------------------> |
  |                         |                        |                      |                     |
  |                         |                        | Confirm Applied      |                     |
  |                         | <---------------------- |                      |                     |
  |                         |                        |                      |                     |
  |                         | Show Success           |                      |                     |
  | <---------------------- |                        |                      |                     |
  |                         |                        |                      |                     |
  |  Return to Home         |                        |                      |                     |
  | ----------------------> |                        |                      |                     |
  |                         |                        |                      |                     |
  |                         | Switch to Home Screen  |                      |                     |
  |                         | ----------------------> |                      |                     |
  |                         |                        |                      |                     |
```

## 5. Control-IQ Technology Scenario

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

## 6. Low Glucose Suspension Scenario

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

## 7. Extended Bolus Scenario

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