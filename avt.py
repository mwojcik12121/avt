# main program file

from tkinter import *

import src.views as views

window = Tk()
window.resizable(False, False)
views.initializeTestSelectionWindow(window)

window.mainloop()