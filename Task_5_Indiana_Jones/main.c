#include <stdio.h>
#include <stdlib.h>

typedef  struct Graph {
    struct Graph **kids;
    int * damage_in_room;
    int * ways_existing;
    int count_ways_from;
    int value; // ; значение на которое ослабляет амулет ловушка из этого перехода
} Graph;

int find_treasure(Graph g, int protect, int max_gold) {

    int return_max = -1;
    if (max_gold < g.value) {
        max_gold = g.value;
    }
    for (int i = 0; i < g.count_ways_from; i++) {
        if (protect - g.damage_in_room[g.ways_existing[i]] >= 0) {
            int c;
            c = find_treasure(*(g.kids[g.ways_existing[i]]), protect - g.damage_in_room[g.ways_existing[i]], max_gold);
            if (c > return_max) {
                return_max = c;
            }
        }
    }
    if (return_max > max_gold) {
        return return_max;
    } else {
        return max_gold;
    }
}

int main() {

    int p = 0; // заряд амулета;
    int n = 0; // количество комнат;
    int m = 0; // количество переходов;
    Graph *g = NULL;

    scanf("%d%d%d", &p, &n, &m);
    g = (Graph*)malloc(n * sizeof(Graph));
    if (g == NULL) {
        exit(1);
    }

    for (int i = 0; i < n; i++) { // выделение памяти и инициализация
        g[i].count_ways_from = 0;
        g[i].value = 0;
        g[i].kids = (Graph**)malloc((n)*sizeof(Graph*));
        g[i].ways_existing = (int*)malloc((n)*sizeof(int));
        g[i].damage_in_room = (int*)malloc((n)*sizeof(int));

        if (g[i].kids == NULL || g[i].ways_existing == NULL || g[i].damage_in_room == NULL) {
            exit(1);
        }

        for (int j = 0; j < n-1; j++) {
            g[i].damage_in_room[j] = -1;
            g[i].ways_existing[j] = -1;
        }
    }

    for (int i = 0; i < m; i++) { // В следующих M строках описаны переходы и ловушки в формате:
        int from = 0, dam = 0, to = 0;
        scanf("%d%d%d", &from, &to, &dam); // номер комнаты, откуда идет переход; номер комнаты, куда идет переход; значение, на которое ослабляет амулет ловушка из этого перехода;
        g[from].damage_in_room[to] = dam;
        g[from].ways_existing[g[from].count_ways_from] = to;
        g[from].kids[to] = &g[to];
        g[from].count_ways_from++;
    }

    for (int i = 0; i < n; i++) { // В следующих N строках записаны стоимости сокровищ, находящихся в соответствующих комнатах.
        scanf("%d", &g[i].value);
    }

    printf("%d", find_treasure(g[0], p, 0)); //звено графа, амулет, текущее золото

    for(int i = 0; i < n; i++) { // очищаем памятьььь
        free(g[i].kids);
        free(g[i].ways_existing);
        free(g[i].damage_in_room);
    }
    free(g);
    return 0;
}