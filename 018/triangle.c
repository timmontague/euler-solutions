#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct treeNode {
    int value;
    int collapsed_value;
    struct treeNode* left;
    struct treeNode* right;
} treeNode_t;

typedef struct queueNode {
    treeNode_t *this;
    struct queueNode* next;
} queueNode_t;

queueNode_t *queue_head = NULL;

void add_queue(treeNode_t *n) {
    queueNode_t *q = malloc(sizeof(queueNode_t));
    queueNode_t *temp = queue_head;
    if (!q) {
	perror("add_queue");
	exit(1);
    }
    q->this = n;
    q->next = NULL;
    if (!queue_head) {
	queue_head = q;
	return;
    }
    while (temp->next) {
	temp = temp->next;
    }
    temp->next = q;
}

treeNode_t *get_queue() {
    treeNode_t *ret;
    queueNode_t *n = queue_head;
    if (!n) {
	return NULL;
    }
    queue_head = n->next;
    ret = n->this;
    free(n);
    return ret;
}

// returns -1 if at end of file
int get_int(FILE *fd) {
    int ret = 0;
    char c;
    // chomp spaces
    do {
	c = fgetc(fd);
    } while (c == ' ' || c == '\n');
    if (c == EOF) {
	return -1;
    }
    while (c >= '0' && c <= '9') {
	ret *= 10;
	ret += c-'0';
	c = fgetc(fd);
    }
    ungetc(c, fd);
    return ret;
}

int main(int argc, const char *argv[]) {
    treeNode_t *root = NULL;

    // load tree from file
    {
	int line_len = 1;
	int i;
	FILE *fd = fopen("triangle.txt", "r");
	if (!fd) {
	    perror("fopen");
	    return 1;
	}
	while (true) {
	    treeNode_t *last = NULL;
	    for (i = 0; i < line_len; i++) {
		int val = get_int(fd);
		treeNode_t *n;
		if (val == -1) {
		    goto done;
		}
		n = malloc(sizeof(treeNode_t));
		if (!n) {
		    perror("load tree");
		    return 1;
		}
		n->value = val;
		n->collapsed_value = 0;
		n->left = NULL;
		n->right = NULL;
		add_queue(n);
		if (line_len == 1) {
		    root = n;
		    root->collapsed_value = root->value;
		} else {
		    if (last) {
			last->right = n;
		    }
		    if (i+1 < line_len) {
			treeNode_t *parent = get_queue();
			parent->left = n;
			last = parent;
		    }
		}
	    }
	    line_len++;
	}
done:
	while(get_queue());
	fclose(fd);
    }

    // collapse tree
    {
	int line_len = 1;
	int max = 0;
	int i;
	add_queue(root);
	while (true) {
	    for (i = 0; i < line_len; i++) {
		treeNode_t *n = get_queue();
		if (!n->right || !n->left) {
		    goto done2;
		}
		if (n->right->collapsed_value == 0) {
		    add_queue(n->right);
		}
		if ((n->collapsed_value + n->right->value) > n->right->collapsed_value) {
		    n->right->collapsed_value = (n->collapsed_value + n->right->value);
		    if (n->right->collapsed_value > max) {
			max = n->right->collapsed_value;
		    }
		}
		if (n->left->collapsed_value == 0) {
		    add_queue(n->left);
		}
		if ((n->collapsed_value + n->left->value) > n->left->collapsed_value) {
		    n->left->collapsed_value = (n->collapsed_value + n->left->value);
		    if (n->left->collapsed_value > max) {
			max = n->left->collapsed_value;
		    }
		}
	    }
	    line_len++;
	}
done2:
	printf("max: %d\n", max);
    }
    


    return 0;
}
