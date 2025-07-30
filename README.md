```c
typedef union {
    int iNombre;
    char cSigne;
} Type_valeur;

typedef struct Sommet {
    Type_valeur valeur;
    struct Sommet *fils_g, *fils_d;
} Sommet;

typedef Sommet *Arbre;

        *
       / \
      +   -
     / \ / \
    12 15 * 3
          / \
         7  10
