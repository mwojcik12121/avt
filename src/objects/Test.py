class TestDescription:
    def __init__(self, filename, id, type, difficulty, description):
        self.filename = filename
        self.id = id
        self.type = type
        self.difficulty = difficulty
        self.description = description

class Test:
    def __init__(self, description, code):
        self.description = description
        self.code = code

    def execute():
        a = 1
