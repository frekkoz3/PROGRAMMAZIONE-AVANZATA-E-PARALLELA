class BadOperandException(Exception):
    pass

class IllegalOperationException(Exception):
    pass

from lmc import Memory

class OperationsTranslator():
    def __init__(self):
        self.__operations = {'ADD' : 100, 'SUB' : 200, 'STA' : 300, 'LDA' : 500, 'BRA' : 600, 'BRZ' : 700, 'BRP' : 800, 'INP' : 901, 'OUT' : 902, 'HLT':0, 'DAT' : 0}
    
    def __getitem__(self, key):
        if key not in self.__operations.keys():
            print("Not a valid key.")
            raise BadOperandException
        return self.__operations[key]
        
class myAssembler():
    def __init__(self, instructions_path):
        self.__operations = ['ADD', 'SUB', 'STA', 'LDA', 'BRA', 'BRZ', 'BRP', 'INP', 'OUT', 'HLT', 'DAT']
        self.__instructions = self.instruction_from_file(instructions_path)
        if len(self.__instructions) > 100:
            print("There are too many instructions")
            raise BadOperandException
        self.preprocess_instructions()
        self.__labels = {}
        self.preprocess_labels()
        self.__memory = Memory()
        self.assemble()
        
    def instruction_from_file(self, path):
        file = open(path, 'r')
        instructions = file.read().split("\n")
        actual_instructions = []
        for instr in instructions:
            if instr.split() == []:
                continue
            if instr.split()[0] == "//":
                continue
            actual_instructions.append(instr)
        return actual_instructions

    def preprocess_instructions(self):
        for i, instruction in enumerate(self.__instructions):
            comment_index = instruction.find("//")
            if comment_index != -1:
                self.__instructions[i] = self.__instructions[i][:comment_index]
            self.__instructions[i] = self.__instructions[i].upper()

    def preprocess_labels(self):
        for i, instruction in enumerate(self.__instructions):
            components = instruction.split()
            if len(components) == 3:
                self.__labels[components[0]] = i
            if len(components) == 2 and components[1] in self.__operations:
                self.__labels[components[0]] = i
    
    def assemble(self):
        for i, instruction in enumerate(self.__instructions):
            components = instruction.split()
            op, idx = '', ''
            label_op = False
            if len(components) == 3:
                op = components[1]
                idx = components[2]
            if len(components) == 2 and components[1] in self.__operations:
                op = components[1]
                idx = '0'
            if len(components) == 2 and components[0] in self.__operations:
                op = components[0]
                idx = components[1]
            if len(components) == 1:
                op = components[0]
                idx = '0'
            if len(components) == 0:
                break
            if idx in self.__labels.keys():
                label_op = True
            elif not idx.isnumeric():
                print("Label not defined.")
                raise IllegalOperationException
            translator = OperationsTranslator()
            op_value = translator[op]
            idx_value = self.__labels[idx] if label_op else int(idx)
            self.__memory[i] = op_value + int(idx_value)
    
    def get_memory(self):
        return self.__memory.asList()

if __name__ == "__main__":

    pass