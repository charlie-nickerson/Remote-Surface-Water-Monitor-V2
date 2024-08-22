import board
import busio
import digitalio
import adafruit_rfm9x
import time

# Define radio parameters.
RADIO_FREQ_MHZ = 915.0  # Frequency must match your transmitter.

# Create the I2C interface.
i2c = busio.I2C(board.SCL, board.SDA)

# Configure the SPI connection.
CS = digitalio.DigitalInOut(board.CE1)
RESET = digitalio.DigitalInOut(board.D25)

# Initialize RFM95 module.
spi = busio.SPI(board.SCK, MOSI=board.MOSI, MISO=board.MISO)
rfm9x = adafruit_rfm9x.RFM9x(spi, CS, RESET, RADIO_FREQ_MHZ)

# Optional: Set transmitter power (max is 23 dB).
# rfm9x.tx_power = 23

# Set the spread factor. Higher SF means improved reliability but reduces data rate
rfm9x.spreading_factor = 8

# Set bandwidth. Higher bandwidth increases reliability but also increases required signal strength
rfm9x.signal_bandwidth = 250000
print("LoRa Receiver Initialized...")

# Loop to continuously check for incoming messages.
while True:
    packet = rfm9x.receive(with_header=True)
    time.sleep(0.1)
    if packet is None:
        print("Waiting for a message...")
    else:
        # Received a packet!
        # Convert to string and print.
        received_message = str(packet, 'utf-8')
        print("Received message: {0}".format(received_message))
        
        # Measure RSSI Value
        rssi = rfm9x.rssi
        print("RSSI: {0} dB".format(rssi))
