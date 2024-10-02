#include "./data_processor.h"

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
