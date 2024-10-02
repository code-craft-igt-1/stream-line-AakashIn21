#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <cmath>
#include "data_processor.h"

void testExtractSensorData() {
    std::string sensorLine = "Sensor 1: 98.60, Sensor 2: 72.15, Sensor 3: 95.50";
    std::vector<double> expectedValues = {98.60, 72.15, 95.50};
    std::vector<double> extractedValues = extractSensorData(sensorLine);

    assert(extractedValues.size() == expectedValues.size());
    for (size_t i = 0; i < expectedValues.size(); ++i) {
        assert(extractedValues[i] == expectedValues[i]);
    }

    std::cout << "testExtractSensorData passed!" << std::endl;
}

void testMaxValues() {
    std::vector<double> sensorValues1 = {98.6, 72.15, 95.50};
    std::vector<double> sensorValues2 = {99.5, 75.20, 96.00};

    currentTemperatureMax = INT_MIN;
    currentPulseRateMax = INT_MIN;
    currentSpo2Max = INT_MIN;

    printMaxInParamStream(sensorValues1);
    assert(currentTemperatureMax == 98.6);
    assert(currentPulseRateMax == 72.15);
    assert(currentSpo2Max == 95.50);

    printMaxInParamStream(sensorValues2);
    assert(currentTemperatureMax == 99.5);
    assert(currentPulseRateMax == 75.20);
    assert(currentSpo2Max == 96.00);

    std::cout << "testMaxValues passed!" << std::endl;
}

void testMinValues() {
    std::vector<double> sensorValues1 = {98.6, 72.15, 95.50};
    std::vector<double> sensorValues2 = {97.5, 70.10, 94.00};

    currentTemperatureMin = INT_MAX;
    currentPulseRateMin = INT_MAX;
    currentSpo2Min = INT_MAX;

    printMinInParamStream(sensorValues1);
    assert(currentTemperatureMin == 98.6);
    assert(currentPulseRateMin == 72.15);
    assert(currentSpo2Min == 95.50);

    printMinInParamStream(sensorValues2);
    assert(currentTemperatureMin == 97.5);
    assert(currentPulseRateMin == 70.10);
    assert(currentSpo2Min == 94.00);

    std::cout << "testMinValues passed!" << std::endl;
}

void testMovingAverage() {
    movingTemperatureSum = 0;
    movingPulseRateSum = 0;
    movingSpo2Sum = 0;
    temperatureQueue.clear();
    pulserateQueue.clear();
    spo2Queue.clear();

    std::vector<std::vector<double>> sensorData = {
        {98.6, 72.15, 95.50},
        {98.7, 72.25, 95.60},
        {98.8, 72.35, 95.70},
        {98.9, 72.45, 95.80},
        {99.0, 72.55, 95.90}
    };

    for (auto& sensorValues : sensorData) {
        printMovingAverageInParamStream(sensorValues);
    }

    double expectedTempAvg = (98.6 + 98.7 + 98.8 + 98.9 + 99.0) / 5.0;
    double expectedPulseAvg = (72.15 + 72.25 + 72.35 + 72.45 + 72.55) / 5.0;
    double expectedSpo2Avg = (95.50 + 95.60 + 95.70 + 95.80 + 95.90) / 5.0;

    double actualTempAvg = (movingTemperatureSum + 98.6) / 5;  // adding first data again becasue it is being removed in printMovingAverageInParamStream after processing.
    double actualPulseRateAvg = (movingPulseRateSum + 72.15) / 5;
    double actualSpo2Avg = (movingSpo2Sum + 95.50) / 5;
    double tolerance = 0.001;  // Define a tolerance for floating-point comparison
    
    assert(fabs(actualTempAvg - expectedTempAvg) < tolerance);
    
    std::cout << "testMovingAverage passed!" << std::endl;
}

int main() {
    // Run all tests
    testExtractSensorData();
    testMaxValues();
    testMinValues();
    testMovingAverage();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
