#include "map.h"

typedef enum {QTNODE, QTLEAF} QT_NODET;

typedef enum {NW, NE, SW, SE} QUADRANT;

bool aux = false;

struct map{
	QT_NODET type; // leaf or internal node
	COORD tp_left, bt_right;
	union{
		struct{ // internal node
			struct map *quadrants[4]; // NW / NE / SW / SE
		}i_node;
		struct{
			COORD p;
			CELL c;
		}leaf;
	}node;
};

// checks if the the coord c is between the boundaries of the bidimensional space
bool in_bounds(COORD c, MAP qt){
	return (c.i >= qt->tp_left.i
		    && c.i <= qt->bt_right.i
	        && c.j >= qt->tp_left.j
	        && c.j <= qt->bt_right.j);
}

MAP create_empty_qtree(COORD tp_left, COORD bt_right){
	MAP qt = (MAP)malloc(sizeof(struct map));
	if(qt == NULL) map_error("Failed to allocate memory for MAP");
	qt -> type = QTNODE;
	qt -> tp_left = tp_left;
	qt -> bt_right = bt_right;
	for (int i=0; i<4; i++) qt -> node.i_node.quadrants[i] = NULL;
	return qt;
}

// returns a new MAP
MAP create_map(int dim){
	COORD tp_left, bt_right, new_cell;
	MAP qtree;
	if(dim <= 32){
		bt_right.i = 31;
		bt_right.j = 31;
	}else{
		bt_right.i = 63;
		bt_right.j = 63;
	}
	tp_left.i = 0;
	tp_left.j = 0;
	qtree = create_empty_qtree(tp_left, bt_right);
	for(int i=0; i<dim; i++){
		for(int j=0; j<dim; j++){
			new_cell.i = i;
			new_cell.j = j;
			insert_cell(new_cell, NULL, qtree);
		}
	}
	return qtree;
}

/*
inserts a NODE in the MAP
returns -1 if the node is out of bounds or 0 if it the insertion is successful
*/
int insert_cell(COORD c, SHIP *s, MAP qt){
	COORD c1, c2; // this coordinates will represent the boundaries of new quadrants
	COORD tp_left = qt->tp_left;
	COORD bt_right = qt->bt_right;

	if(!in_bounds(c, qt)) return -1; // node out of bounds
	
	if(tp_left.i == 0 && tp_left.j == 0 && bt_right.i == 1 && bt_right.j == 1 && !aux){
	//	printf("aqui\n");
		aux = true;
		goto aqui;
	}

	
	/*
	if we can't subdivide the space any further then this is a leaf
	add the node to the tree
	*/
	if(abs(tp_left.i - bt_right.i) <= 1 && abs(tp_left.j - bt_right.j) <= 1){
		aux = false;
		qt->type = QTLEAF;
		qt->node.leaf.p = c;
		qt->node.leaf.c.ship = s;
		qt->node.leaf.c.atk_cell = UNKNOWN;
		if (s != NULL)
			qt->node.leaf.c.state = FILLED;
		else 
			qt->node.leaf.c.state = EMPTY;
		return 0;
	}


aqui:
	// recursively check the quadrant where the coordinate lies and subdivide it
	if((tp_left.i + bt_right.i)/2 >= c.i){ 		// N
		if((tp_left.j + bt_right.j)/2 >= c.j){ 	// NW
			//printf("NW\n");
			if(qt->node.i_node.quadrants[NW] == NULL){
				c2.i = (tp_left.i + bt_right.i)/2;
				c2.j = (tp_left.j + bt_right.j)/2;
		
				qt->node.i_node.quadrants[NW] = create_empty_qtree(tp_left, c2);
			}
			return insert_cell(c, s, qt->node.i_node.quadrants[NW]);
		}else{ 										// NE
			//printf("NE\n");
			if(qt->node.i_node.quadrants[NE] == NULL){
				c1.i = tp_left.i;
				c1.j = (tp_left.j + bt_right.j)/2;
				c2.i = (tp_left.i + bt_right.i)/2;
				c2.j = bt_right.j;

				qt->node.i_node.quadrants[NE] = create_empty_qtree(c1,c2);
			}
			return insert_cell(c, s, qt->node.i_node.quadrants[NE]);
		}
	}else{ 											// S
		if((tp_left.j + bt_right.j)/2 >= c.j){ 	// SW
			//printf("SW\n");
			if(qt->node.i_node.quadrants[SW] == NULL){
				c1.i = (tp_left.i + bt_right.i)/2;
				c1.j = tp_left.j;
				c2.i = bt_right.i;
				c2.j = (tp_left.j + bt_right.j)/2;

				qt->node.i_node.quadrants[SW] = create_empty_qtree(c1, c2);
			}
			return insert_cell(c, s, qt->node.i_node.quadrants[SW]);
		}else{ // SE
			//printf("SE\n");
			if(qt->node.i_node.quadrants[SE] == NULL){
				c1.i = (tp_left.i + bt_right.i)/2;
				c1.j = (tp_left.j + bt_right.j)/2;

				qt->node.i_node.quadrants[SE] = create_empty_qtree(c1, bt_right);
			}
			return insert_cell(c, s, qt->node.i_node.quadrants[SE]);
		}
	}

}

CELL *get_cell(COORD c, MAP qt){
	COORD tp_left = qt->tp_left;
	COORD bt_right = qt->bt_right;

	if(!in_bounds(c, qt)) return NULL;

	if(qt->type == QTLEAF){
		return &qt->node.leaf.c;
	} 

	if((tp_left.i + bt_right.i)/2 >= c.i){ 		// N
		if((tp_left.j + bt_right.j)/2 >= c.j){ 	// NW
			//printf("NW\n");
			if(qt->node.i_node.quadrants[NW] == NULL)
				return NULL;
			return get_cell(c, qt->node.i_node.quadrants[NW]);
		}else{ 										// NE
			//printf("NE\n");
			if(qt->node.i_node.quadrants[NE] == NULL)
				return NULL;
			return get_cell(c, qt->node.i_node.quadrants[NE]);
		}
	}else{ 											// S
		if((tp_left.j + bt_right.j)/2 >= c.j){ 	// SW
			//printf("SW\n");
			if(qt->node.i_node.quadrants[SW] == NULL)
				return NULL;
			return get_cell(c, qt->node.i_node.quadrants[SW]);
		}else{ // SE
			//printf("SE\n");
			if(qt->node.i_node.quadrants[SE] == NULL)
				return NULL;
			return get_cell(c, qt->node.i_node.quadrants[SE]);
		}
	}
}

// returns the index (unidimensional) when rotation r is applied to the point (i,j)
int rotate_point(int i, int j, int r, int dim){
    switch(r % 4){
        case 0: return i * dim + j;
        case 1: return (dim*dim - dim) + i - (j * dim);
        case 2: return (dim*dim - 1) - (i * dim) - j;
        case 3: return (dim - 1) - i + (j * dim);
    }
    return 0;
}

void print_strategy(MAP curr_map, MAP adv_map){
    CELL *curr_cell, *adv_cell;
    COORD c;

    printf("  ");
    for (int i = 0; i < dim; i++)
        printf("%.2d ", i);
    printf("\n");

    for(int i=0; i < dim; i++){
        printf("%.2d", i);
        for(int j=0; j< dim; j++){
            c.i = i; 
            c.j = j;

           if((curr_cell = get_cell(c,curr_map)) == NULL)
                map_error("Cannot get cell");

            
            ATTACK pos = curr_cell -> atk_cell;
            switch(pos){
                case UNKNOWN:
                    printf(" . ");
                    break;
                case HIT:
                    if((adv_cell = get_cell(c,adv_map)) == NULL)
                        map_error("Cannot get cell");

                    if(adv_cell->ship->sunk)
                        printf(" S ");
                    else
                        printf(" X ");
                    break;
                case MISS:
                    printf(" M ");
                    break;
            }
        }
        printf("\n");
    }
}


// set all the map cells pointing to this ship as EMPTY
void remove_ship(MAP m, int shape, int rot, int map_i, int map_j){
	CELL *c; 
	COORD p;
    for(int i = 0; i < BMAP_SIZE; i++){
        for(int j = 0; j < BMAP_SIZE; j++){
            // only set to EMPTY if this bitmap pos is an 'X' given the ship rotation			
            if(shapes[shape].bitmap[rotate_point(i, j, rot, BMAP_SIZE)] == 'X'){
				p.i = map_i + i;
				p.j = map_j + j;
				if((c = get_cell(p, m)) == NULL)
					continue;
                c -> state = EMPTY;
			}				
        }
    }

}


void free_qtree(MAP qt){
	if (qt!=NULL){
		if (qt -> type == QTNODE){
			for(int i=0; i<4; i++)
				free_qtree(qt -> node.i_node.quadrants[i]);
		}
	}		
	free(qt);
}

// recursively destroys a MAP structure
void free_map(MAP qt){
	CELL *c;
	COORD p;
	if(qt != NULL){
		// free ships
		for(int i=0; i<dim; i++){
			for(int j=0; j<dim; j++){
				p.i = i;
				p.j = j;
				if ((c = get_cell(p, qt)) == NULL)
					continue;
				if (c->state == FILLED){
                    int shape = c -> ship -> shape;
                    int rot = c -> ship -> rot;
                    COORD bmap_begin = c -> ship -> bmap_begin;				   
				    remove_ship(qt, shape, rot, bmap_begin.i, bmap_begin.j);
                    free_ship(c -> ship);
                }
			}
		}
		free_qtree(qt);
	}
}

// Call this when there is a memory related error
void map_error(char *msg){
    fprintf(stderr,"Error: %s.\n",msg);
    exit(EXIT_FAILURE);
}
