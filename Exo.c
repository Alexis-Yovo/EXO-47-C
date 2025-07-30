// Évaluation d'une expression arithmétique représentée par un arbre binaire

#include <stdio.h>
#include <stdlib.h>

// === Définition des structures ===
typedef union {
    int iNombre;
    char cSigne;
} Type_valeur;

typedef struct Sommet {
    Type_valeur valeur;
    struct Sommet *fils_g, *fils_d;
} Sommet;

typedef Sommet *Arbre;

// === Fonctions de construction (nécessaires pour tester) ===
Arbre construire_feuille(int n) {
    Arbre a = (Arbre)malloc(sizeof(Sommet));
    if (!a) {
        fprintf(stderr, "Erreur d'allocation\n");
        exit(1);
    }
    a->valeur.iNombre = n;
    a->fils_g = NULL;
    a->fils_d = NULL;
    return a;
}

Arbre construire_noeud(char op, Arbre gauche, Arbre droite) {
    Arbre a = (Arbre)malloc(sizeof(Sommet));
    if (!a) {
        fprintf(stderr, "Erreur d'allocation\n");
        exit(1);
    }
    a->valeur.cSigne = op;
    a->fils_g = gauche;
    a->fils_d = droite;
    return a;
}

// ===  Fonction eval ===
/**
 * @brief Évalue récursivement la valeur de l'expression arithmétique.
 * @param tree Arbre binaire représentant l'expression
 * @return Résultat entier de l'expression
 */
int eval(Arbre tree) {
    if (tree == NULL) {
        fprintf(stderr, "Erreur : arbre vide\n");
        exit(1);
    }

    // Cas de base : feuille (nombre)
    if (tree->fils_g == NULL && tree->fils_d == NULL) {
        return tree->valeur.iNombre;
    }

    // Évaluer les sous-arbres
    int gauche = eval(tree->fils_g);
    int droite = eval(tree->fils_d);
    char op = tree->valeur.cSigne;

    switch (op) {
        case '+': return gauche + droite;
        case '-': return gauche - droite;
        case '*': return gauche * droite;
        case '/':
            if (droite == 0) {
                fprintf(stderr, "Erreur : division par zéro\n");
                exit(1);
            }
            return gauche / droite;
        default:
            fprintf(stderr, "Erreur : opérateur inconnu '%c'\n", op);
            exit(1);
    }
}

// === Fonction main ===
int main() {
    printf("🧪 Test de l'exercice 47 : évaluation d'expression arithmétique\n\n");

    // Construction manuelle de l'arbre pour : (12 + 15) * ((7 * 10) - 3)
    Arbre tree = construire_noeud('*',
        construire_noeud('+', construire_feuille(12), construire_feuille(15)),
        construire_noeud('-',
            construire_noeud('*', construire_feuille(7), construire_feuille(10)),
            construire_feuille(3)
        )
    );

    int resultat = eval(tree);
    printf("✅ Expression : (12 + 15) * ((7 * 10) - 3)\n");
    printf("📊 Résultat : %d\n", resultat);  // Attendu : 249

    return 0;
}
