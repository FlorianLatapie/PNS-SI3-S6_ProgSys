
// Ces fonctions ci-dessous ne servent à rien pour effectuer le tri

// Calcul itératif de la suite de Fibonacci
long foo(long n) {
  long first = 0, second = 1;

  long tmp;
  while (n--) {
    tmp = first+second;
    first = second;
    second = tmp;
  }
  return first;
}

// Calcul récursif de la suite de Fibonacci
long bar(long n) {
  if (n < 2)
    return n;
  else
    return bar(n-1) + bar(n-2);
}

// Calcul itératif du PGCD (algorithme d'Euclide)
long baz(long a, long b) {
  long r;
  
  while (b > 0) {
    r = a % b;
    a = b;
    b = r;
  }
  return a;
}

// Calcul récursif du PGCD (algorithme d'Euclide)
long qux(long a, long b) {
  long r;
  
  r = a % b;
  if (r == 0)
    return b;
  else
    return qux(b, r);
}