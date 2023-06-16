import time
from time import sleep
import serial
import pandas as pd

filename = time.strftime("%Y%m%d-%H%M%S")
data = []

ser = serial.Serial('COM8', baudrate = 115200, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=1)

while 1:
    rx_data =ser.readline() # byte string
    decoded_rx_data = rx_data.decode("utf-8")[:13]
    decoded_rx_data_array = decoded_rx_data.split(' ')
    data.append(decoded_rx_data_array)
    print(data)
    
	#Create a DataFrame object
    df = pd.DataFrame(data, columns = ['A_X' , 'A_Y', 'A_Z' , 'G_X', 'G_Y', 'G_Z', 'Temp'])
    
    df.to_csv(filename + '.csv', index=False)
    print('DataFrame is written successfully to CSV File.')
	
	# display
    print(df)

	