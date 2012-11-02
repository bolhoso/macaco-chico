#include <stdio.h>
#include <assert.h>

// TODO: implement diagonal moves


/**************************************************
 *         THE BIG AND FAT CHALLENGES             *
 *                                                *
 * Develop and test each part!                    *
 * Validate development while building code       *
 * Explain what you're doing while you code       *
 *                                                *
 *************************************************/

#define WALL '*'
#define END  '+'

// TODO: isn't it possible to make directions easier to manipulate?
// they can be an increment of X or Y
enum directions {DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT};

struct pos {
	char y, x;
	enum directions d;
};

#define MAX_LIN 8
#define MAX_COL 16

// TODO: read maze from file
// 1 2
// MAZE
char maze[MAX_LIN][MAX_COL] = {
	{'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'},
	{' ', ' ', ' ', '*', ' ', ' ', '*', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '+'},
	{'*', ' ', '*', '*', '*', ' ', ' ', '*', '*', ' ', '*', ' ', '*', '*', '*', '*'},
	{'*', ' ', '*', ' ', ' ', ' ', '*', '*', '*', ' ', '*', ' ', '*', ' ', '*', '*'},
	{'*', ' ', '*', ' ', '*', ' ', '*', ' ', '*', ' ', '*', ' ', '*', ' ', ' ', '*'},
	{'*', ' ', '*', ' ', '*', ' ', '*', ' ', '*', '*', '*', ' ', '*', '*', ' ', '*'},
	{'*', ' ', ' ', ' ', '*', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '*'},
	{'*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*'}
};


/*
 * Check if a move is within bounds or not
 */
int check_bounds (struct pos *p) {
	return !((p->x <= 0 && p->d == DIR_LEFT) ||
		(p->x >= MAX_COL - 1 && p->d == DIR_RIGHT) ||
		(p->y <= 0 && p->d == DIR_UP) ||
		(p->y >= MAX_LIN - 1 && p->d == DIR_DOWN));
}

/*
 * Check if it's possible to move from current (x, y) in direction d
 */
int can_move (char maze[MAX_LIN][MAX_COL], struct pos p) {
	switch (p.d) {
		case DIR_RIGHT: p.x++; break;
		case DIR_LEFT:  p.x--; break;
		case DIR_UP:    p.y--; break;
		case DIR_DOWN:  p.y++; break;
	}

	// have the bounds been respected after moving?
	if (!check_bounds (&p)) {
		return 0;
	}

	// we can move unless we have a wall
	return maze[p.y][p.x] != WALL;
}

/*
 * Make a move from (x, y) in direction d and reset the direction
 */
void move_and_reset (struct pos *p) {
	switch (p->d) {
		case DIR_RIGHT:
			p->x++; break;
		case DIR_LEFT:
			p->x--; break;
		case DIR_UP:
			p->y--; break;
		case DIR_DOWN:
			p->y++; break;
	}

	p->d = DIR_UP;
}

// TODO: nof_moves!
#define SOLUTION_FOUND -1
int solve_maze_recur (char maze[MAX_LIN][MAX_COL], struct pos pos) {

	// First of all, check bounds
	struct pos *p = &pos;
	if (check_bounds (&pos)) {
		return 0;
	} 
	
	// Have we found the exit?
	// TODO: how do we tell the end from a common re
	if (maze[pos.y][pos.x] == END) {
		printf ("Hoooray! Solution found! We're at (%d, %d).\n", pos.x, pos.y);
		return SOLUTION_FOUND;
	}

	// Change the current coordinate according to the direction and reset
	// direction
	move_and_reset (&pos);

	// Now, try moving in the 4 directions
	while (pos.d <= DIR_RIGHT) {
		printf ("-> %d", pos.d);
		if (can_move (maze, pos)) {
			if (solve_maze_recur (maze, pos) == SOLUTION_FOUND) {
				return SOLUTION_FOUND;
			}
		}

		// Back from the recursion, try another direction
		pos.d++;
	}

	return 0;
}

int solve_maze (char maze[MAX_LIN][MAX_COL]) {
	struct pos start = {1, 0, 0};


	return solve_maze_recur (maze, start);
}

void test_check_bounds() {
	struct pos p1 = {0, 0, DIR_LEFT};
	assert (!check_bounds(&p1));

	struct pos p2 = {0, 0, DIR_RIGHT};
	assert (check_bounds(&p2));

	struct pos p3 = {0, 0, DIR_DOWN};
	assert (check_bounds(&p3));

	struct pos p4 = {0, 0, DIR_UP};
	assert (!check_bounds(&p4));
}

void test_check_move () {
	struct pos p1 = {1, 0, DIR_RIGHT};
	assert (!can_move(maze, p1));
}

int main () {
	int moves = solve_maze (maze);

	
	return 0;
}
