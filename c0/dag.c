# include"cutoff_ast.h"

static char rcsid[] = "$Id: dag.c,v 1.1 2002/08/28 23:12:42 drh Exp $";

#define iscall(op) (generic(op) == CALL \
	|| IR->mulops_calls \
	&& (generic(op)==DIV||generic(op)==MOD||generic(op)==MUL) \
	&& ( optype(op)==U  || optype(op)==I))
static Node forest;
static struct dag {
	struct node node;
	struct dag *hlink;
} *buckets[16];
int nodecount;
static Tree firstarg;
int assignargs = 1;
int prunetemps = -1;
static Node *tail;

static int depth = 0;
static Node replace( Node );
static Node prune( Node );
static Node asgnnode( Symbol, Node );
static struct dag *dagnode( int, Node, Node, Symbol );
static Symbol equated( Symbol );
static void fixup( Node );
static void labelnode( int );
static void list( Node );
static void killnodes( Symbol );
static Node node( int, Node, Node, Symbol );
static void printdag1( Node, int, int );
static void printnode( Node, int, int );
static void reset( void );
static Node tmpnode( Node );
static void typestab( Symbol, void * );
static Node undag( Node );
static Node visit( Node, int );
static void unlist( void );