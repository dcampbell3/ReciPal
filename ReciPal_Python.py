import requests
from bs4 import BeautifulSoup
from setup import *
import serial
import sys
import time

#https://www.foodnetwork.com/recipes/food-network-kitchen/air-fryer-steak-with-garlic-herb-butter-8351429

print(color.YELLOW+"INITIATING CONNECTION TO ARDUINO"+color.END)
try:
    ser = serial.Serial('/dev/tty.usbmodem143101', 9600)
except:
    print(color.RED+"ERROR: COULD NOT CONNECT TO ARDUINO"+color.END)
else:
    print(color.GREEN+"CONNECTION COMPLETE"+color.END)

    ser.flushInput()

    url = input("Enter URL to Food Network Recipe: ")


    page = requests.get(url)
    soup = BeautifulSoup(page.text, "html.parser")

    ingredients = [i.text for i in soup.find_all('span', class_='o-Ingredients__a-Ingredient--CheckboxLabel')[1:]]

    steps = [i.text.strip() for i in soup.find_all("li", class_= 'o-Method__m-Step')]

    sent_str = ""

    for i in range(len(ingredients)): 
        ser.write((blockText(ingredients[i]) + "=").encode()) 
        time.sleep(0.1)
        sent_str += blockText(ingredients[i]) + "="

    for i in range(len(steps)): 
        ser.write((blockText(steps[i]) + "=").encode())
        time.sleep(0.5)
        sent_str += blockText(steps[i]) + "="

    print(color.GREEN+"DATA SENT"+color.END)
    #print(sent_str)


