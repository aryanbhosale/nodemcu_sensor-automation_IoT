# nodemcu_sensor-automation_IoT
Interfacing NodeMCU v3(ESP8266) with MPU6050 (IMU sensor with acceleration and gyroscope along with temperature) and DS18B20 (temperature sensor)


Resource Link: https://drive.google.com/drive/folders/1sUM9tPUtah8djTZy5WYI-h7uo4lOehVA?usp=drive_link
	This is a link with all the necessary files that are used in this project

Downloading the Arduino IDE
We will be using the Arduino IDE 2 for this project
To install it, go to this website https://www.arduino.cc/en/software > Under “Nightly Builds” select your OS and follow the download instructions in the downloaded executable file

Downloading the necessary libraries in the Arduino IDE
Open the Arduino IDE > Click the icon shown in the image below

Type “adafruit mpu6050” in the searchbox and hit enter > install the library
Then type “Adafruit Unified Sensor” and scroll all the way down to find the library and install it
Now search for “Adafruit Bus IO” and install it
Search for “OneWire” and install it
Finally search for “DallasTemperature” and install it
Note that some of the libraries might ask you to install other libraries to support it, click on “Install all” in such cases
Click on the “Select Board” dropdown from the top-left of the Arduino IDE and select “Select Other Board and Port” > Type “nodemcu” in the searchbox and select the option in the image

For choosing ports, you will be required to plugin your ESP8266 using a micro-USB Serial Cable and choose the COMx(x=integer) besides which “(USB)” is mentioned like in the following image, note that your COM might be different from that in the image


Note: If you’ve reached till here, your Arduino IDE setup is complete. In the next part of this documentation you will find 2 methods to log sensor data into a spreadsheet, namely the Google Sheets way, and the Excel spreadsheet way.


Google Sheets Method
Microsoft Excel Method
Allows real-time viewing of changes in the sensor data
Takes at least 2 seconds to log new sensor data in its cells
Uses the Google Spreadsheets Apps Script to write JavaScript code to allow the automation of logging external data
Can view sensor data after the code stops running, real time viewing not possible
Is faster than Google Sheets Method, takes less than 2 seconds to log data in its cells
Uses Serial Communication using a UDP web server to automate logging external data



D. The Google Sheets Method
In the Arduino IDE, paste the code mentioned in the file “gsheet_esp.ino” from the drive link provided at the top. There are a few changes you will need to make here in the following lines, in line 32 and 33, replace the text inside the double quotes to your WiFi/Hotspot name and Password. There is a very important change on line 39 also, but we’ll get back to it later. For now, just compile the code to see whether it’s free of errors or not by clicking the tick mark on the top-left of the Arduino IDE as shown in the image below


Once you’re sure that there are no errors, go to google spreadsheets by typing “sheet.new” in your google search > Change the name from “Untitled Spreadsheet”(just click on it on the top-left of the screen and start typing the new name) to “ESP8266_data” > Change the sheet name from “Sheet1”(bottom-left of your screen, just right click on it and click “Rename”) to “Data” > Click on “Extensions” > “Apps Script” > Paste the code present in the file “code.gs” which is available in the drive link provided 
There are a few changes to be made in the code, on line 2, replace “YOUR_SHEET_ID” with the ID of your Google Sheet which you just created > Go to your Google Sheet > in the URL, copy this much portion of it as mentioned in the image below, the portion after /d/….till the portion before…. /edit, copy it and paste it there


In your Apps Script file, click “Deploy” > “New deployment” > Click the Settings gear symbol next to “Select type” and select “web app” > Add an optional description and select the “only myself” dropdown and select “Anyone” > Click on “Deploy” > Click “Authorize Access” > Select your Google Account from the modal that opens and select “Allow” for everything it asks > Copy the “Deployment ID” as shown in the image below

Paste this Deployment ID in line 39 of your gsheet_esp.ino in your Arduino IDE

Connections:

Connect the Signal Pin(yellow) from DS18B20 Temperature Sensor to D3(GPIO0) instead of D2(GPIO4)-->as shown in the picture given below, also connect the GND and 3V Vcc to any of the available ports on the ESP8266 NodeMCU


Run the code by clicking the rightward arrow on the top-left of the screen next to the verify icon which you’d clicked before to check for errors, wait till it finishes booting by 100%, then go to your Google Sheets, you will be able to see real time updates from the ESP8266 of the sensor data

E. The Microsoft Excel Method

Installing important libraries:Open the command line(Type cmd after pressing the windows icon and hit enter) > 
i. Type “pip install python-time” and hit enter
ii. Type “pip install pyserial” and hit enter
iii. Type “pip install pandas” and hit enter
iv. Type “pip install openpyxl” and hit enter

Go to Arduino IDE and paste the code mentioned in “excel_esp.ino” in the drive link provided
Here there are only 2 changes in the code at lines 32 and 33 where you have to replace the text inside the double quotes to your WiFi/Hotspot name and password where it’s mentioned
Click on the tick mark icon on the top-left of the screen to check the code for errors, once confirmed that the code is error-free, creat a folder on your Desktop screen > Go inside that folder > Create a new file called ser.py and paste the code in “ser.py” provided inside the drive link > Run this code(type “python ser.py” in the terminal of that folder and hit enter) only after running your Arduino IDE code 
Note: Sometimes while running the ser.py it might throw some error about data format, it’s okay, it only happens because of the Connection Confirmation Byte Strings that are sent before the actual data, try running the code using the same command at least 6-7 times till it runs

You will see a new file being created in that folder which you just created with all the necessary data in it once you stop the python code

DO NOT OPEN THE FILE WHILE THE PROGRAM IS RUNNING, IT MIGHT LEAD TO ERRORS


