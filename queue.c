#include "queue.h"
#include "tile_game.h"
#include <stdint.h>
#include <stdlib.h>

int is_solved(struct game_state state);  
int generate_successors(struct game_state state, struct game_state neighbors[]);

void enqueue(struct queue *q, struct game_state state) {
    uint64_t val = serialize(state);
    insert_at_tail(&q->data, val);
}

struct game_state dequeue(struct queue *q) { 
    uint64_t val = remove_from_head(&q->data);
    return (val == 0) ? (struct game_state){0} : deserialize(val);
}

int number_of_moves(struct game_state start) { 
    struct queue q = {0};
    enqueue(&q, start);

    while (q.data.head != NULL) {
        struct game_state cur = dequeue(&q);
        if (is_solved(cur)) {
            return cur.num_steps;
        }

        struct game_state neighbors[4];
        int count = generate_successors(cur, neighbors);

        for (int i = 0; i < count; ++i) {
            enqueue(&q, neighbors[i]);
        }
    }
    return -1;
}
