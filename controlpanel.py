import tkinter as tk
from tkinter import *
from PIL import Image, ImageTk
import random
import serial
import time

# Root
root = tk.Tk()

# Window size
window_width = 775
window_height = 400

# Screen size
screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()

# Coordinates
x_coordinate = int((screen_width / 2) - (window_width / 2))
y_coordinate = int((screen_height / 2) - (window_height / 2))

# Window open in center of screen
root.geometry("{}x{}+{}+{}".format(window_width, window_height, x_coordinate, y_coordinate))

# Window settings (icon, title, resize)
root.iconbitmap("icons/icon.ico")
root.title("Boost Control Panel")
root.resizable(False, False)

# Default connection status
connection = False
ser = False


# Try to connect the Arduino/serial/port when program is loaded or when clicked on refresh
def start_arduino():
    global ser
    global connection

    try:
        # Connecting Arduino
        ser = serial.Serial("COM3", 9600)

        # Wait until connection is completed
        time.sleep(2)

        # Run start sequence on Arduino
        ser.write(b'run_start_sequence')

        # Change or add parameters when connected
        status_text_print.config(text="Boost is connected and active!")
        status_icon_print.config(image=status_active)
        refresh_button_print.config(image="", command="")

        laugh_button_print.config(image=laugh_active, command=run_laugh)
        wink_button_print.config(image=wink_active, command=run_wink)
        clap_button_print.config(image=clap_active, command=run_clap)
        heart_button_print.config(image=heart_active, command=run_heart)

        # Change connection status
        connection = True

    except Exception as e:
        print(e)
        # Change or add parameters when not connected
        refresh_button_print.config(image=refresh_icon, command=start_arduino)


# Closes port if connected
def close_arduino():
    if ser:
        # Run stop sequence on Arduino
        ser.write(b'run_stop_sequence')

        # Disconnecting Arduino
        ser.close()


# Status icons/images (inactive, active, refresh)
status_inactive = ImageTk.PhotoImage(Image.open("icons/not_connected.png"))
status_active = ImageTk.PhotoImage(Image.open("icons/connected.png"))
refresh_icon = ImageTk.PhotoImage(Image.open("icons/refresh.png"))

# Default status icon and text
status_icon_print = Label(image=status_inactive)
status_text_print = Label(root, font=('Ariel', 10), text="Boost is not active! Connect Boost and click on refresh.")

# Default status refresh button
refresh_button_print = tk.Button(root, borderwidth=0)

# Status icon, text and refresh button placement
status_icon_print.grid(row=0, column=0, padx=20, pady=20, sticky=tk.W)
status_text_print.grid(row=0, column=0, padx=40, pady=20, columnspan=4, sticky=tk.W)
refresh_button_print.grid(row=0, column=0, padx=20, pady=20, columnspan=4, sticky=tk.E)


# Activate a sequence on the Arduino
def run_laugh():
    # Select random sequence integer
    sequence = "run_laugh_sequence_"
    sequence_integer: int = random.randint(1, 5)

    # Creating f-String as command
    command = f"{sequence}{sequence_integer}"

    # Send command
    ser.write(command.encode())


def run_wink():
    ser.write(b'run_wink_sequence')


def run_clap():
    ser.write(b'run_clap_sequence')


def run_heart():
    ser.write(b'run_heart_sequence')


# Icons/images for buttons (inactive, active)
laugh_inactive = ImageTk.PhotoImage(Image.open("icons/laugh_inactive.png"))
laugh_active = ImageTk.PhotoImage(Image.open("icons/laugh.png"))

wink_inactive = ImageTk.PhotoImage(Image.open("icons/wink_inactive.png"))
wink_active = ImageTk.PhotoImage(Image.open("icons/wink.png"))

clap_inactive = ImageTk.PhotoImage(Image.open("icons/clap_inactive.png"))
clap_active = ImageTk.PhotoImage(Image.open("icons/clap.png"))

heart_inactive = ImageTk.PhotoImage(Image.open("icons/heart_inactive.png"))
heart_active = ImageTk.PhotoImage(Image.open("icons/heart.png"))

# Default icons/buttons
laugh_button_print = tk.Button(root, image=laugh_inactive, borderwidth=0)
wink_button_print = tk.Button(root, image=wink_inactive, borderwidth=0)
clap_button_print = tk.Button(root, image=clap_inactive, borderwidth=0)
heart_button_print = tk.Button(root, image=heart_inactive, borderwidth=0)

# Icons/buttons placement
laugh_button_print.grid(row=1, column=0, padx=10, pady=50, ipadx=10, ipady=10)
wink_button_print.grid(row=1, column=1, padx=10, pady=50, ipadx=10, ipady=10)
clap_button_print.grid(row=1, column=2, padx=10, pady=50, ipadx=10, ipady=10)
heart_button_print.grid(row=1, column=3, padx=10, pady=50, ipadx=10, ipady=10)

# Try to connect the Arduino/serial when program is loaded
start_arduino()

# Mainloop
root.mainloop()

# Closes port if connected when program is closed
close_arduino()
