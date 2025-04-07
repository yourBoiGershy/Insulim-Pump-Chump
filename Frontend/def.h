#ifndef DEF_H
#define DEF_H

#define MAX_BATTERY 100
#define BATTERY_TIMER 10000

// Simulation constants
#define DEFAULT_GLUCOSE 5.5
#define MIN_GLUCOSE 3.0
#define MAX_GLUCOSE 10.0
#define NORMAL_GLUCOSE 7.0
#define SIMULATION_INTERVAL 1000

// CGM constants
#define CGM_INTERVAL 300 // 5 minutes in seconds
#define POINTS_PER_HOUR 12 // 5-minute intervals = 12 points per hour
#define DEFAULT_DISPLAY_HOURS 2 // Default to 2 hours view
#define MAX_DISPLAY_HOURS 6 // Maximum 6 hours of data


#endif // DEF_H
