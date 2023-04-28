#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tree {
    char * text;
    struct tree* left;
    struct tree* right;
} tree;

int elements_count(int flag) {
    static int count = 0;
    if (flag == 1) {
        count++;
    } else {
        if (flag == 0) {
            count--;
        }
    }
    return count;
}

// Добавляем новый узел
tree * add_node(tree * node, char * word) {

    if (node == NULL) {
        node = (tree *) malloc(sizeof(tree)); // выделяем память для узла
        node->text = (char*) malloc((strlen(word) + 1) * sizeof(char)); // выделяем память для слова
        strcpy(node->text, word);
        node->left = NULL;
        node->right = NULL;
        elements_count(1);
    } else {
        int cmp = strcmp(node->text, word);
        if (cmp < 0) {
            node->right = add_node(node->right, word);
        } else {
            if (cmp > 0) {
                node->left = add_node(node->left, word);
            }
        }
    }
    return node;
}

void add_left(tree* t, tree* lt) {
    if (t->left == NULL) {
        t->left = lt;
    } else {
        add_left(t->left, lt);
    }
}

tree * remove_node(tree * node, char * word) {

    if (node == NULL) { //Если не нашли слово - ничего не делаем
        return node;
    }

    int cmp = strcmp(node->text, word);

    if (cmp == 0) {
        if (node->right == NULL && node->left == NULL) {
            free(node);
            node = NULL;
            elements_count(0);
        } else if (node->left != NULL && node->right == NULL) {
            tree * tmp = node->left;
            free(node);
            node = tmp;
            elements_count(0);
        } else if (node->right != NULL) {
            tree * lt = node->left;
            tree * tmp = node->right;
            free(node);
            node = tmp;
            elements_count(0);
            if (lt != NULL)
                add_left(node, lt);
        }
    } else {
        if (node->right != NULL) {
            node->right = remove_node(node->right, word);
        }
        if (node->left != NULL) {
            node->left = remove_node(node->left, word);
        }
    }
    return node;
}

void print_levels(tree * T, int level, int now) {

    if (now != level) {
        now++;
        if (T->left != NULL) {
            print_levels(T->left, level, now);
        }
        if (T->right != NULL) {
            print_levels(T->right, level, now);
        }
    } else {
        if (T != NULL) {
            printf("%s ", T->text);
        }
    }
}

void free_tree(tree * T) {
    if (T->left != NULL) {
        free_tree(T->left);
    }
    if (T->right != NULL) {
        free_tree(T->right);
    }
    free(T);
}

// функция выделяет нужное количество памяти
void get_str(char** text, int *volume) {
    char g;
    int i = 0;
    g = getchar();
    while (g != ' ' && g != 0 && g != '\n') {
        if (i >= *volume) {
            *text = (char*) realloc(*text, 2 * i * sizeof(char));
            *volume *= 2;
        }
        (*text)[i] = g;
        g = getchar();
        i++;
    }
    if (i >= *volume) {
        *text = (char*) realloc(*text, (*volume)*sizeof(char) + 1);
    }
    (*text)[i] = 0;
}

int main() {

    char * text;
    int volume = 1;
    text = (char *) malloc(sizeof(char)); // выделяем немного памяти под будущий входной текст

    scanf("TEXT:\n");
    get_str(&text, &volume);

    tree * T = NULL; // обюявление указателя на структуру, будем передовать в функции именно указатель, дабы не захломлять стек
    int i = 0;

    while (strcmp("DELETE:", text) != 0) {
        T = add_node(T, text);
        get_str(&text, &volume);
        i++;
    }


    get_str(&text, &volume);

    while (strcmp("LEVEL:", text) != 0) {
        T = remove_node(T, text);
        get_str(&text, &volume);
    }

    free(text);
    int level;
    scanf("%d", &level);
    printf("%d\n", elements_count(2));
    print_levels(T, level, 0);

    free_tree(T);
    return 0;
}