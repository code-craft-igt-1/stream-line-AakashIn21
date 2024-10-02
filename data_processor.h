#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <sstream>
#include <regex>
#include <climits>

// Declarations for global variables
extern double currentTemperatureMax;
extern double currentPulseRateMax;
extern double currentSpo2Max;
extern double currentTemperatureMin;
extern double currentPulseRateMin;
extern double currentSpo2Min;
extern int movingAverageDataLimit;
extern int parameterNumber;
extern double movingTemperatureSum;
extern double movingPulseRateSum;
extern double movingSpo2Sum;
extern std::deque<double> temperatureQueue;
extern std::deque<double> pulserateQueue;
extern std::deque<double> spo2Queue;

// Function declarations
std::vector<double> extractSensorData(const std::string& line);
void printMaxInParamStream(std::vector<double>& sensorValues);
void printMinInParamStream(std::vector<double>& sensorValues);
void printMovingAverageInParamStream(std::vector<double>& sensorValues);

#endif // DATA_PROCESSOR_H
