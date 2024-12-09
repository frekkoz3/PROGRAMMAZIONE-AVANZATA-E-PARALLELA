from collections import defaultdict
from copy import deepcopy

class Polynomial:
  def __init__(self, coeffs):
    self.__coeffs = defaultdict(int, deepcopy(coeffs))

  def __getitem__(self, k):
    return self.__coeffs[k]

  def __setitem__(self, k, v):
    self.__coeffs[k] = v

  def __call__(self, x):
    val = 0
    for k in self.__coeffs:
      val += self[k] * ( x ** k )
    return val

  def __add__(self, other):

    if isinstance(other, (int, float)):
      cofs = Polynomial(self.__coeffs)
      cofs[0] += other
      return cofs
    
    if isinstance(other, Polynomial):
      cofs = Polynomial(self.__coeffs)
      for k in other.__coeffs:
        cofs[k] += other[k]
      return cofs
    
    raise TypeError ('Other must be of type Polynomial, int or float')
  
  def __sub__(self, other):
    if isinstance(other, (int, float)):
      cofs = Polynomial(self.__coeffs)
      cofs[0] -= other
      return cofs
    
    if isinstance(other, Polynomial):
      cofs = Polynomial(self.__coeffs)
      for k in other.__coeffs:
        cofs[k] -= other[k]
      return cofs
    
    raise TypeError ('Other must be of type Polynomial, int or float')

  def __mul__(self, other):
    if isinstance(other, (int, float)):
      cofs = Polynomial(self.__coeffs)
      for k in cofs:
        cofs[k]*= other
      return cofs
    
    if isinstance(other, Polynomial):
      cofs = defaultdict(int)
      for k1 in self.__coeffs:
        for k2 in other.__coeffs:
          cofs[k1+k2] += self[k1] * other[k2]
      return Polynomial(cofs)
    
    raise TypeError ('Other must be of type Polynomial, int or float')

  def __pow__(self, n):

    if not isinstance(n, int):
      raise TypeError('N must be an integer')
    
    if n < 0:
      raise TypeError('N must be positive')
    
    pol = Polynomial(self.__coeffs)
    for i in range (n-1):
      pol = pol*pol
    
    return pol

  def derivative(self):
    cofs = defaultdict(int)
    for k in self.__coeffs:
      if k - 1 < 0:
        continue
      cofs[k-1] = k * self.__coeffs[k]
    return Polynomial(cofs)

  def __str__(self):
    s = ''
    for k in self.__coeffs:
      if k == 0:
        s += f' +{self.__coeffs[k]}'
      elif k == 1:
        s += f' +{self.__coeffs[k]}x'
      else:
        if self.__coeffs[k] == - 1 :
          s += f' x^{k}'
        elif self.__coeffs[k] == 1:
          s += f' +x^{k}'
        elif self.__coeffs[k] < 0:
          s += f' {self.__coeffs[k]}x^{k}'
        else:
          s += f' +{self.__coeffs[k]}x^{k}'
    return s


def newton_raphson(p, x, n_iter=20):
  x_t = x
  for i in range (n_iter):
    x_t = x_t - (p(x_t)/p.derivative()(x_t))
  return x_t

if __name__ == "__main__":
  p = Polynomial({4: 2, 3: 5, 1: 6, 0: -2})
  q = Polynomial({3: 1, 2: 0.5, 1: -1, 0: 3})
  print(f"p = {p}")
  print(f"q = {q}")
  print(f"p+q = {p+q}")
  print(f"p*q = {p*q}")
  print(f"p^2 = {p**2}")
  print(f"p(3) = {p(3)}")
  print(f"(p+q)(20) = {(p+q)(20)}")
  print(f"p' = {p.derivative()}")
  x = newton_raphson(p, 5)
  print(f"p({x}) = {p(x)}")