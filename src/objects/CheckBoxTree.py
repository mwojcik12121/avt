from tkinter import *
from tkinter import ttk

box_unchecked = "\u2610"
box_checked = "\u2611"

class CheckBoxTree(ttk.Treeview):
    def __init__(self, root, testlist, **kw):
        ttk.Treeview.__init__(self, root, **kw)
        self.testlist = testlist
        self.bind("<Double-1>", self.onDoubleClick)
        #self.bind("<Button-1>", self.onClick)

    def makeCheckList(self):
        
        self.heading('#0', text='Available tests', anchor=W)
        
        if self.testlist:
            itemid = 0
            category = self.testlist[0].type
            catid = 0
            self.insert('', END, text=box_unchecked+" "+self.testlist[0].type, iid=itemid)
            itemid += 1

            for t in self.testlist:
                if(category != t.type):
                    self.insert('',
                                END,
                                text=box_unchecked+" "+t.type,
                                iid=itemid)
                    category = t.type
                    catid = itemid
                    itemid += 1
                self.insert('', END, text=box_unchecked+" "+t.filename, iid=itemid) 
                self.move(itemid, catid, 0)
                itemid += 1
        else: self.insert('', END, text="AAAA", iid=1)

    def onDoubleClick(self, event):
        item = self.selection()[0]
        item.set(text=self.swapBox(item.text))

        if not self.parent(item):
            for c in self.get_children(item):
                item = self.swapBox(c.text)

    # def onClick(self, event):
    #     item = self.selection()[0]
    
    def swapBox(text):
        if text[5]:
            text.replace("\u2611", "\u2610")
        elif not text[5]:
            text.replace("\u2610", "\u2611")

    #def getCheckedItems()
        

