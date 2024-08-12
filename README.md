## Lentokenttäkamera -projekti

pi@raspberrypi:~/git/airportsystem/raspberry-codes/arduino-listener $ crontab -l
# Edit this file to introduce tasks to be run by cron.
#
# Each task to run has to be defined through a single line
# indicating with different fields when the task will be run
# and what command to run for the task
#
# To define the time you can provide concrete values for
# minute (m), hour (h), day of month (dom), month (mon),
# and day of week (dow) or use '*' in these fields (for 'any').
#
# Notice that tasks will be started based on the cron's system
# daemon's notion of time and timezones.
#
# Output of the crontab jobs (including errors) is sent through
# email to the user the crontab file belongs to (unless redirected).
#
# For example, you can run a backup of all your user accounts
# at 5 a.m every week with:
# 0 5 * * 1 tar -zcf /var/backups/home.tgz /home/
#
# For more information see the manual pages of crontab(5) and cron(8)
#
# m h  dom mon dow   command
* * * * * /usr/bin/python3 /home/pi/git/airportsystem/raspberry-codes/arduino-listener.py > /home/pi/git/airportsystem/raspberry-codes/arduino-listener/weather
* * * * * /usr/bin/scp /home/pi/git/airportsystem/raspberry-codes/arduino-listener/weather.txt jusju@softala.haaga-helia.fi:
pi@raspberrypi:~/git/airportsystem/raspberry-codes/arduino-listener $


import serial

ser = serial.Serial('/dev/ttyACM0', 9600)  # Open serial port

while True:
    if ser.in_waiting > 0:
        data = ser.readline()
        try:
            decoded_data = data.decode('utf-8', errors='ignore').rstrip()
            print(decoded_data)
            with open('example.txt', 'w') as file:
                file.write(decoded_data)
        except UnicodeDecodeError as e:
            print(f'Decoding error: {e}. Raw data: {data}')


