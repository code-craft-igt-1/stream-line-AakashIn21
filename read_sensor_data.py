import random
import time

def read_sensor_data(sensor_id):
    # Simulating sensor data reading
    return random.uniform(0, 100)  # Returns a random float between 0 and 100

def collect_sensor_data():
    sensor_readings = []
    for _ in range(50):
        # Read data from sensors
        sensor1_data = read_sensor_data(1)
        sensor2_data = read_sensor_data(2)
        sensor3_data = read_sensor_data(3)
        
        # Collect the data
        sensor_readings.append((sensor1_data, sensor2_data, sensor3_data))
        
        # Optional: Sleep for a short duration (e.g., 1 second) to simulate time between readings
        #time.sleep(1)
        
    return sensor_readings

def send_sensor_data():
    readings = collect_sensor_data()
    for sensor1, sensor2, sensor3 in readings:
        print(f"Sensor 1: {sensor1:.2f}, Sensor 2: {sensor2:.2f}, Sensor 3: {sensor3:.2f}")

if __name__ == "__main__":
    send_sensor_data()
