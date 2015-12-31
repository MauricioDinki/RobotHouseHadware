# Libraries
import serial
import requests

url = 'https://young-beach-6344.herokuapp.com/movement'

def get_arduinos():
    arduinos = []
    for i in range(4):
        port = '/dev/ttyACM' + str(i)
        try:
            arduino = serial.Serial(port, baudrate=9600)
            arduinos.append(arduino)
            print "Arduino founded at port ", port
        except:
            print "Arduino doesnt found at port: ", port
    return arduinos


def get_movement_data(arduinos):
    for arduino in arduinos:
        message = arduino.readline()
        message = message.split()
        if message[1] =='detected':
            r = requests.post(url)
            print "Movement Posted ", r

arduinos = get_arduinos()
while True:
    get_movement_data(arduinos)
