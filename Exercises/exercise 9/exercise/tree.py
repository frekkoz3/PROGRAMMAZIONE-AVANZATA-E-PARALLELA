import random
from os import path, getcwd
from ctypes import cdll, c_bool, c_float, c_int, pointer, POINTER, Structure


class Node:
  
  def __init__(self, key, value):
    self.key = key
    self.value = value
    self.dx = None
    self.sx = None

  def search(self, key):
    if self.key == key:
      return self.value
    if key < self.key and self.sx is not None:
      return self.sx.search(key)
    if key > self.key and self.dx is not None:
      return self.dx.search(key)
    return None

  def insert(self, key, value):
    if self.key == key:
      self.value = value
    if key < self.key:
      if self.sx == None:
        self.sx = Node(key, value)
      else:
        self.sx.insert(key, value)
    if key > self.key:
      if self.dx == None:
        self.dx = Node(key, value)
      else:
        self.dx.insert(key, value)
      
  def __str__(self):
    s = f"key : {self.key} - value : {self.value}"
    if self.sx is not None or self.dx is not None:
      s = f"({str(self.sx)}, key : {self.key} - value : {self.value} , {str(self.dx)})"
    return s

class BinarySearchTree:
  def __init__(self):
    self.root = None

  def search(self, key):
    if self.root == None:
      return None
    return self.root.search(key)

  def insert(self, key, value):
    if self.root == None:
      self.root = Node(key, value)
    else:
      self.root.insert(key, value)

  def __str__(self):
    return str(self.root)



class CTreeNode(Structure):
  pass

CTreeNode._fields_ = [("key", c_int), ("value", c_float),
                      ("left", POINTER(CTreeNode)), ("right", POINTER(CTreeNode))]


class CTree:
  code = None

  def __init__(self):
    if CTree.code is None:
      CTree.code = cdll.LoadLibrary(path.join(getcwd(), "libtree.so"))
      CTree.code.insert.argtypes = [POINTER(CTreeNode), c_int, c_float]
      CTree.code.insert.restype = POINTER(CTreeNode)
      CTree.code.search.argtypes = [POINTER(CTreeNode), c_int, POINTER(c_float)]
      CTree.code.search.restype = c_bool
      CTree.code.destroy.argtypes = [POINTER(CTreeNode)]
    self.root = POINTER(CTreeNode)()

  def search(self, key): 
    res = c_float() 
    if CTree.code.search(self.root, c_int(key), pointer(res)):
      return res.value
    return None

  def insert(self, key, value):
    self.root = CTree.code.insert(self.root, c_int(key), c_float(value))

  def __str__(self):
    def print_node(node):
      if not node: # se node è falso significa che punta ad un null
        return str(None)  
      s = f"key : {node.contents.key} - value : {node.contents.value}"
      if node.contents.left or not node.contents.right:
        s = f"({print_node(node.contents.left)}, key : {node.contents.key} - value : {node.contents.value} , {print_node(node.contents.right)})"
      return s  
    return print_node(self.root)

  def __del__(self):
    CTree.code.destroy(self.root)


if __name__ == "__main__":
  pairs = [(random.randint(0, 30), (random.random()*10 // 1)) for _ in range(5)]
  print(pairs)
  searches = [random.randint(0, 30) for i in range(10)]
  print("Python only:")
  bst = BinarySearchTree()
  for p in pairs:
    bst.insert(p[0], p[1])
  for k in searches:
    print(f"Searching for {k}: {bst.search(k)}")
  print(bst)
  # Decommentare per la parte extra
  print("Calling C:")
  cbst = CTree()
  for p in pairs:
    cbst.insert(p[0], p[1])
  for k in searches:
    print(f"Searching for {k}: {cbst.search(k)}")
  print(cbst)