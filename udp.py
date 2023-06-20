import socket
import time
from time import sleep
import pandas as pd

filename = time.strftime("%Y%m%d-%H%M%S")
data = []

UDP_IP = "0.0.0.0" #All available IP Addresses
UDP_PORT = 4210

sock = socket.socket(socket.AF_INET, # Internet
                     socket.SOCK_DGRAM) # UDP
sock.bind((UDP_IP, UDP_PORT))

while True:
    rx_data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
    decoded_rx_data = rx_data.decode("utf-8")[:13]
    decoded_rx_data_array = decoded_rx_data.split(' ')
    data.append(decoded_rx_data_array)
    #print(data)

    #Create a DataFrame object
    df = pd.DataFrame(data, columns = ['A_X' , 'A_Y', 'A_Z' , 'G_X', 'G_Y', 'G_Z', 'Temp'])
    
    df.to_csv(filename + '.csv', index=False)
    print('DataFrame is written successfully to CSV File.')
	
	# display
    print(df)
    