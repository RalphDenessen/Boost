from tkinter import *
from tkinter import ttk
from tkinter.ttk import Progressbar
from PIL import Image, ImageTk
import tkinter as tk
import os

# Tkinter root
root = tk.Tk()

# Window settings
root.overrideredirect(True)
root.resizable(False, False)

# Window size
window_width = 500
window_height = 300

# Screen size
screen_width = root.winfo_screenwidth()
screen_height = root.winfo_screenheight()

# Coordinates
x_coordinate = int((screen_width / 2) - (window_width / 2))
y_coordinate = int((screen_height / 2) - (window_height / 2))

# Window open in center of screen
root.geometry("{}x{}+{}+{}".format(window_width, window_height, x_coordinate, y_coordinate))

# Window background color
root.config(background="#2F6C60")

# Logo and information
logo_image = ImageTk.PhotoImage(Image.open("icons/logo.png"))
logo_image_print = Label(root, image=logo_image, bg="#2F6C60")
logo_image_print.place(x=82, y=65)

# Progressbar with text
progress_label = Label(root, text="Loading... ", font=("Source Code Pro", 11, "bold"), fg="#FFFFFF", bg="#2F6C60")
progress_label.place(x=190, y=255)

progress = ttk.Style()
progress.theme_use("alt")
progress.configure("red.Horizontal.TProgressbar", background="#3D3D3D", troughcolor="#2F6C60")
progress = Progressbar(root, orient=HORIZONTAL, length=501, mode="determinate", style="red.Horizontal.TProgressbar")

progress.place(y=290)


# If done with loader (when i = 10)
def done():
    # Close root window/loop
    root.withdraw()
    # Open the Control Panel
    os.system("controlpanel.py")
    # Destroy root window/loop
    root.destroy()


# Percent as i
i = 1


# Loader (until i = 10)
def loader():
    global i
    if i <= 10:
        txt = "Loading... " + (str(10*i)+"%")
        progress_label.config(text=txt)
        progress_label.after(350, loader)
        progress["value"] = 10*i
        i += 1
    else:
        # Start done
        done()


# Start loader
loader()

# Tkinter mainloop
root.mainloop()
