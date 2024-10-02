#include "data_processor.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

// Global variables
double currentTemperatureMax = INT_MIN;
double currentPulseRateMax = INT_MIN;
double currentSpo2Max = INT_MIN;
double currentTemperatureMin = INT_MAX;
double currentPulseRateMin = INT_MAX;
double currentSpo2Min = INT_MAX;
int movingAverageDataLimit = 5;
int parameterNumber = 3;
double movingTemperatureSum = 0;
double movingPulseRateSum = 0;
double movingSpo2Sum = 0;
std::deque<double> temperatureQueue;
std::deque<double> pulserateQueue;
std::deque<double> spo2Queue;

// Function to extract numbers from the sensor output line
vector<double> extractSensorData(const std::string& line) {
    vector<double> data;

    // Regular expression to match floating-point numbers (including decimals)
    std::regex regexPattern(R"((\d+\.\d+))");
    std::sregex_iterator iter(line.begin(), line.end(), regexPattern);
    std::sregex_iterator end;

    while (iter != end) {
        // Convert the matched string to a double and store it
        data.push_back(std::stod(iter->str()));
        ++iter;
    }

    return data;
}

void printMaxInParamStream(vector<double>& sensorValues) {
    if (sensorValues.size() == parameterNumber) {  // Ensure there are 3 sensor values
        currentTemperatureMax = std::max(sensorValues[0], currentTemperatureMax);
        currentPulseRateMax = std::max(sensorValues[1], currentPulseRateMax);
        currentSpo2Max = std::max(sensorValues[2], currentSpo2Max);
        cout<<"Maximum Temparature reading: "<<currentTemperatureMax<<", ";
        cout<<"Maximum Pulse Rate reading: "<<currentPulseRateMax<<", ";
        cout<<"Maximum Pulse Rate reading: "<<currentSpo2Max<<endl;
    }
}

void printMinInParamStream(vector<double>& sensorValues) {
    if (sensorValues.size() == parameterNumber) {
        currentTemperatureMin = std::min(sensorValues[0], currentTemperatureMin);
        currentPulseRateMin = std::min(sensorValues[1], currentPulseRateMin);
        currentSpo2Min = std::min(sensorValues[2], currentSpo2Min);
        cout<<"Minimum Temparature reading: "<<currentTemperatureMin<<", ";
        cout<<"Minimum Pulse Rate reading: "<<currentPulseRateMin<<", ";
        cout<<"Minimum Pulse Rate reading: "<<currentSpo2Min<<endl;
    }
}

void printMovingAverageInParamStream(vector<double>& sensorValues) {
    temperatureQueue.push_back(sensorValues[0]);
    movingTemperatureSum += sensorValues[0];
    pulserateQueue.push_back(sensorValues[1]);
    movingPulseRateSum += sensorValues[1];
    spo2Queue.push_back(sensorValues[2]);
    movingSpo2Sum += sensorValues[2];

    if(temperatureQueue.size() == movingAverageDataLimit) {
        double temperatureMovingAveage = movingTemperatureSum / movingAverageDataLimit;
        double pulseRateMovingAveage = movingPulseRateSum / movingAverageDataLimit;
        double spo2MovingAveage = movingSpo2Sum / movingAverageDataLimit;

        cout<<"Temperature Moving Average: "<<temperatureMovingAveage<<", ";
        cout<<"PulseRate Moving Average: "<<pulseRateMovingAveage<<", ";
        cout<<"Spo2 Moving Average: "<<spo2MovingAveage<<endl;

        movingTemperatureSum -= temperatureQueue.front();
        movingPulseRateSum -= pulserateQueue.front();
        movingSpo2Sum -= spo2Queue.front();

        temperatureQueue.pop_front();
        pulserateQueue.pop_front();
        spo2Queue.pop_front();
    }
    else {
        cout<<"Temperature Moving Average: "<<"No Data Available"<<", ";
        cout<<"PulseRate Moving Average: "<<"No Data Available"<<", ";
        cout<<"Spo2 Moving Average: "<<"No Data Available"<<endl;
    }
}

int main() {
    string line;
    // Read input data (from pipe)
    while (std::getline(cin, line)) {
        vector<double> sensorValues = extractSensorData(line);
        printMaxInParamStream(sensorValues);
        printMinInParamStream(sensorValues);
        printMovingAverageInParamStream(sensorValues);
    }

    return 0;
}
