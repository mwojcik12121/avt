import src.objects.CheckBoxTree as cbt
from tkinter import *
from tkinter import ttk
import src.importer as importer

def initializeTestSelectionWindow(window):
    window.title('AVT - Test selection')
    window.geometry('800x600')

    left = ttk.Frame(window, padding=10, border=20)
    right = ttk.Frame(window, padding=10, border=20)
    
    # initialize test selection field
    tests = refreshTestList(left)

    # initialize test description field
    
    # place all elements on the grid
    left.grid(column=0, row=0)
    right.grid(column=1, row=0)
    
    tests.grid(row=0, column=0, sticky=NW)

    rspeed = Checkbutton(left, text="Include reaction speed").grid(column=0, row=2, sticky=W)
    idacc = Checkbutton(left, text="Include identification accuracy").grid(column=0, row=3, sticky=W)
    rmacc = Checkbutton(left, text="Include neutralization accuracy").grid(column=0, row=4, sticky=W)
    
    add = Button(left, text="Add test", command=window.destroy, width=30, height=2).grid(column=0, row=5)
    ref = Button(left, text="Refresh list", command=refreshTestList(left), width=30, height=2).grid(column=0, row=6)
    test = Button(left, text="Start testing", command=window.destroy, width=30, height=2).grid(column=0, row=7)

    description = Text(right, padx=10, pady=10, width=50, wrap=WORD)
    description.grid(column=0, row=0, sticky=NSEW)
    
    description.insert(END, "TEST SP-0033\n\n")
    description.insert(END, "ID: 0033\n")
    description.insert(END, "Type: Spyware\n\n")
    description.insert(END, "This is a test file of a spyware attack. Here you would find a brief description of a selected test")

# refresh test list based on current "testfiles" folder contents
def refreshTestList(window):
    tests = importer.importTestInfo(window)
    tests.makeCheckList()
    return tests

def setSelectionDescription():
    a = a
    
