import unittest
from unittest.mock import patch
from read_sensor_data import read_sensor_data, collect_sensor_data, send_sensor_data

class TestSensorFunctions(unittest.TestCase):
    
    def test_read_sensor_data(self):
        # Test if the sensor data is within the expected range
        for _ in range(10):
            data = read_sensor_data(1)
            self.assertGreaterEqual(data, 0)
            self.assertLessEqual(data, 100)

    def test_collect_sensor_data_length(self):
        # Test if the collect_sensor_data function returns 50 readings
        readings = collect_sensor_data()
        self.assertEqual(len(readings), 50)

    def test_collect_sensor_data_content(self):
        # Test if the data returned has the correct structure
        readings = collect_sensor_data()
        for sensor1, sensor2, sensor3 in readings:
            self.assertIsInstance(sensor1, float)
            self.assertIsInstance(sensor2, float)
            self.assertIsInstance(sensor3, float)

    @patch('builtins.print')  # Mock the print function
    def test_send_sensor_data(self, mock_print):
        # Test if send_sensor_data prints the correct output
        send_sensor_data()
        
        # Check that print was called 50 times
        self.assertEqual(mock_print.call_count, 50)
        
        # Validate that the first call's output is in the expected format
        first_call_args = mock_print.call_args_list[0][0][0]
        self.assertTrue("Sensor 1:" in first_call_args)
        self.assertTrue("Sensor 2:" in first_call_args)
        self.assertTrue("Sensor 3:" in first_call_args)

if __name__ == "__main__":
    unittest.main()
