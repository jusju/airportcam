import serial

ser = serial.Serial('/dev/ttyACM0', 9600)  # Open serial port

while True:
    if ser.in_waiting > 0:
        data = ser.readline()
        try:
            decoded_data = data.decode('utf-8', errors='ignore').rstrip()
            print(decoded_data)
            with open('example.txt', 'a') as file:
                file.write(decoded_data)
        except UnicodeDecodeError as e:
            print(f'Decoding error: {e}. Raw data: {data}')
