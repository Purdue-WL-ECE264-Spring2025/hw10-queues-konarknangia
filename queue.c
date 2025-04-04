#include "queue.h"
#include "tile_game.h"

void enqueue(struct queue *q, struct game_state state) {
  size_t val = serialize(state);
  insert_at_tail(&q->list, val);
}

struct game_state dequeue(struct queue *q) { 
  size_t val = remove_from_head(&q->list);
  return (val == 0) ? (struct game_state){0} : deserialize(val);
}

int number_of_moves(struct game_state start) { 
  struct queue q = {0};
  enqueue(&q, start);

  while (q.list.head != NULL) {
    struct game_state cur = dequeue(&q);
    if (is_solved(cur)) {
      return cur.num_moves;
    }

    struct game_state neighbors[4];
    int count = generate_successors(cur, neighbors);

    for (int i = 0; i < count; ++i) {
      size_t next_val = serialize(neighbors[i]);
      enqueue(&q, neighbors[i]);
    }
  }
  return -1;
}
