class BadOperandException(Exception):
    pass

class IllegalInstructionException(Exception):
    pass

class ProgramCounter():

    def __init__(self):
        self.__counter = 0
    
    def __add__(self, n): # this is the normal increment
        if not isinstance(n, int):
            print(f"Excepted an integer. {type(n)} received instead.")
            raise BadOperandException
        self.__counter = (self.__counter + n) % 1000
        return self.__counter
    
    def __mul__(self, n): # this is the branch
        if not isinstance(n, int):
            print(f"Excepted an integer. {type(n)} received instead.")
            raise BadOperandException
        self.__counter = (n % 1000)
        return self.__counter

    def __str__(self):
        return str(self.__counter)   
    
class Memory():

    def __init__(self):
        self.__items = [0]*100

    def __getitem__(self, k):
        if not isinstance(k, int):
            print("Index must be an integer.")
            raise BadOperandException
        if k < 0 or k > 99:
            print("Index out of range. [range 0 - 99]")
            raise BadOperandException
        return self.__items[k]

    def __setitem__(self, k, n):
        if not isinstance(n, int):
            print("Value must be an integer.")
            raise BadOperandException      
        if n < 0 or n > 999:      
            print("Value is either too small or too big [range 0 - 999].")
            raise BadOperandException      
        self.__items[k] = n

class Queque():
    def __init__(self, items = None):
        self.__items = []
        if items != None:
            if not isinstance(items, list):
                print("Need a list to initialize a Queque.")
                raise BadOperandException
            for l in list:
                if not isinstance(l, int):
                    print("Need a list of integer to initialize a Queque.")
                    raise BadOperandException
                if l < 0 or l > 999:
                    print("Need a list of integer  in the range [0 - 999] to initialize a Queque.")
                    raise BadOperandException
            self.item == items
    
    def append(self, n):
        if not isinstance(n, int):
            print("Value must be an integer.")
            raise BadOperandException 
        if n < 0 or n > 999:
            print("Value must be an integer in the range [0 - 999]")
            raise BadOperandException  
        self.__items.append(n)

    def pop(self):
        return self.__items.pop()
    
    def __add__(self, n):
        self.append(n)
        return self
    
    def __str__(self):
        return str(self.__items)

class myLMC():

    def __init__(self, input_q, input_m): # input as list !!
        self.__memory = Memory(input_m)
        self.__accumulator = 0
        self.__program_counter = ProgramCounter()
        self.__input_queque = Queque(input_q)
        self.__output_queque = Queque()
        self.__flag = 0 
        self.__working = True

    def __add__(self, k):
        self.__accumulator = self.__accumulator + self.__memory[k]
        self.__flag = self.__accumulator > 999
        self.__accumulator = self.__accumulator%1000
    
    def __sub__(self, k):
        self.__accumulator = self.__accumulator - self.__memory[k]
        self.__flag = self.__accumulator < 0
        self.__accumulator = self.__accumulator%1000

    def store(self, k):
        self.__memory[k] = self.__accumulator
    
    def load(self, k):
        self.__accumulator = self.__memory[k]
    
    def branch(self, k):
        self.__program_counter *= k
    
    def branch_ifzero(self, k):
        if not self.__flag and self.__accumulator == 0:
            self.branch(k)

    def branch_ifpositive(self, k):
        if not self.__flag:
            self.branch(k)
    
    def input(self):
        self.__accumulator = self.__input_queque.pop()
    
    def output(self):
        self.__output_queque += self.__accumulator
    
    def halt(self, k):
        self.__working = False

    def work(self):
        while self.__working:
            instruction = self.__memory[self.__program_counter]
            radix = instruction//100
            index = instruction%100
            if radix == 1:
                self.__add__(index)
            elif radix == 2:
                self.__sub__(index)
            elif radix == 3:
                self.store(index)
            elif radix == 5:
                self.load(index)
            elif radix == 6:
                self.branch(index)
            elif radix == 7:
                self.branch_ifzero(index)
            elif radix == 8:
                self.branch_ifpositive(index)
            elif instruction == 901:
                self.input()
            elif instruction == 902:
                self.output()
            elif radix == 0:
                self.halt()
            else:
                raise IllegalInstructionException