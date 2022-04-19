1. la taille sera `100*sizeOf(char)+sizeOf(int)` : `100*1 + 4` = 104 octets 
2. la zone tout a droite sera utilisée et il n'y aura pas d'appels a malloc car il ya suffisament d'espace pour loger 80+16 à dans l'espace disponible à la fin 
```
128+16+256+16+128+16+512+16+384+16 = 1488
1488−800−800 = −112, 112 > 80+16
```
  
3. la plus grande zone que l'on peut allouer est 32 octets 
```
128+16+256+16 = 416 = tailleMax
128+16+128+16+64+16 = 368 = départ
416-368 = 48 = libre, libre - 16 = 32
```

