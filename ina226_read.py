import time
from ina226.i2c import I2CAdapter #ensure pip install ina226 is done
from ina226.ina226 import INA226
import csv

ina_devices = [INA226(i2c_adapter, address) for address in addresses]

# Prepare for data logging
with open('data_log.csv', mode='w') as log_file:
    data_writer = csv.writer(log_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
    # Write the header
    data_writer.writerow(['Timestamp', 'Device', 'Voltage (V)', 'Current (mA)', 'Power (mW)'])

    while True:
        for i, ina in enumerate(ina_devices):
            voltage = ina.voltage()
            current = ina.current()
            power = ina.power()
            timestamp = time.strftime("%Y-%m-%d %H:%M:%S")  # Get current time
            print(f"[{timestamp}] Device {i}: Voltage: {voltage} V, Current: {current} mA, Power: {power} mW")

            # Log the data
            data_writer.writerow([timestamp, f'Device {i}', voltage, current, power])

        time.sleep(1)  # delay between readings