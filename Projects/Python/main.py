from lmc import *
from assembler import *

if __name__ == "__main__":

    instructions_path = 'exec.lmc'
    Louis = myAssembler(instructions_path)
    Logan = myLMC(memory=Louis.get_memory(),input_q=[901, 902, 705, 600, 0, 4, 5, 6, 7, 8, 9, 0])
    Logan.work(False)
    print(Logan.get_input())
    print(Logan.result())