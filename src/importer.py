from src.objects.Test import Test
from src.objects.Test import TestDescription as td
import src.objects.CheckBoxTree as cbt
import logging
import os
import re
    
# imports test information for test selection
def importTestInfo(root):

    # tests are stored in avt/testfiles
    files = os.listdir(os.getcwd()+"/testfiles")
    testlist = list()

    # add files with valid names and correct internal structures
    for t in files:
        if re.search("[A-Z]-[0-9]", t):
            test = validateLineFormat(t)
            if test:
                testlist.append(test)

    testlist = sorted(testlist, key = lambda x: (x.type, x.id))
    
    return cbt.CheckBoxTree(root, testlist)

# validate internal file format
def validateLineFormat(filepath):

    fileopen = open(os.getcwd()+"/testfiles/"+filepath, "r")

    file = fileopen.read().splitlines()
    
    filename = os.path.basename(fileopen.name)
    id = ""
    type = ""
    description = ""

    try:
        for idx, line in enumerate(file):
            if idx == 0 and line != "TEST":
                raise Exception("Invalid file format!")
            if idx == 1:
                if re.search("^[0-9]{4};[a-zA-Z]+;$", line):
                    data = line.split(';')
                    id = data[0]
                    type = data[1]
                    difficulty = data[2]
                else:
                    raise Exception("Invalid file format!")
            if idx == 2 and line != "`":
                raise Exception("Invalid file format!")
            if idx == 3:
                description = line
            if idx == 4 and line != "`":
                raise Exception("Invalid file format!")
            if idx > 4: break
    except Exception as e:
        print(e)
        return None

    return td(filename, id, type, difficulty, description)
            