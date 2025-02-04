import cv2 as cv
from pygrabber.dshow_graph import FilterGraph
import time
import numpy as np
import matplotlib.pyplot as plt
import serial
import asyncio

def getcams():

    devices = FilterGraph().get_input_devices()

    cams = {}

    for device_index, device_name in enumerate(devices):
        cams[device_name] = device_index
    return cams


class saver():
    def __init__(self, filename, width, height, fqc, output):

        self.lister = []
        self.fqc = fqc
        self.output = output
        self.arduino = serial.Serial(port = self.output, baudrate=11520)
        send = str(self.fqc) +"|"
        self.arduino.write(send.encode())
    def anal(self, frame: np.ndarray):

        frame = cv.cvtColor(frame, cv.COLOR_BGR2GRAY) #converts the frame back to grayscale to elimate the channel
        #note - I am not sure how to convert a 1 channel color image to a QImage. If you want to increase the image, whoever is reading this can try
        #and figure out how to do that and modify it for that (who knows, I might do it later), to try and increase the efficiency a little bit
        ret, frame = cv.threshold(frame, 127, 255, cv.THRESH_BINARY) #and then  binarizes it

        conts, _ = cv.findContours(frame, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE) #pulls the countor
        conts = sorted(conts, key =lambda it: cv.contourArea(it), reverse = True) #sorts them by area in reverse order
        m = cv.moments(conts[0]) #pulls the largest
        cX = int(m["m10"] / m["m00"]) #finds the midpoind
        cY = int(m["m01"] / m["m00"])
        self.lister.append(np.array((cX, cY))) #Adds it to the record of centroids
        if cX > 320: #placeholder function - replace with laser 
            self.arduino.write("12|".encode())
            print("right")
        else:
            self.arduino.write("02|".encode())
            print("left")
    def end(self):
        arr = np.array(self.lister)
        plt.scatter(arr[:,0], arr[:,1])
        plt.xlim([0,640])
        plt.ylim([0,480])
        plt.show()
        self.arduino.close()
            