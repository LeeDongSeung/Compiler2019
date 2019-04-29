/****************************************************/
/* File: util.c                                     */
/* Utility function implementation                  */
/* for the TINY compiler                            */
/* Compiler Construction: Principles and Practice   */
/* Kenneth C. Louden                                */
/****************************************************/

#include "globals.h"
#include "util.h"

/* Procedure printToken prints a token 
 * and its lexeme to the listing file
 */
void printToken( TokenType token, const char* token_string )
{
  switch (token)
    {
	case IF:
	fprintf(listing,"\tIF\t\t%s\n",token_string);
	break;
	case ELSE:
	fprintf(listing,"\tELSE\t\t%s\n",token_string);
	break;
	case INT:
	fprintf(listing,"\tINT\t\t%s\n",token_string);
	break;
	case VOID:
	fprintf(listing,"\tVOID\t\t%s\n",token_string);
	break;
	case RETURN:
	fprintf(listing,"\tRETURN\t\t%s\n",token_string);
	break;
	case WHILE:
	fprintf(listing,"\tWHILE\t\t%s\n",token_string);
	break;
	case ASSIGN:
	fprintf(listing,"\t=\t\t%s\n",token_string);
	break;
	case LT:
	fprintf(listing,"\t<\t\t%s\n",token_string);
	break;
	case EQ:
	fprintf(listing,"\t==\t\t%s\n",token_string);
	break;
	case LTEQ:
	fprintf(listing,"\t<=\t\t%s\n",token_string);
	break;
	case GT:
	fprintf(listing,"\t>\t\t%s\n",token_string);
	break;
	case GTEQ:
	fprintf(listing,"\t>=\t\t%s\n",token_string);
	break;
	case NOTEQ:
	fprintf(listing,"\t!=\t\t%s\n",token_string);
	break;
	case LPAREN:
	fprintf(listing,"\t(\t\t%s\n",token_string);
	break;
	case RPAREN:
	fprintf(listing,"\t)\t\t%s\n",token_string);
	break;
	case SEMI :
	fprintf(listing,"\t;\t\t%s\n",token_string);
	break;
	case COMMA:
	fprintf(listing,"\t,\t\t%s\n",token_string);
	break;
	case LBRACE:
	fprintf(listing,"\t{\t\t%s\n",token_string);
	break;
	case RBRACE:
	fprintf(listing,"\t}\t\t%s\n",token_string);
	break;
	case LBRACKET:
	fprintf(listing,"\t[\t\t%s\n",token_string);
	break;
	case RBRACKET:
	fprintf(listing,"\t]\t\t%s\n",token_string);
	break;
	case PLUS:
	fprintf(listing,"\t+\t\t%s\n",token_string);
	break;
	case MINUS:
	fprintf(listing,"\t-\t\t%s\n",token_string);
	break;
	case TIMES:
	fprintf(listing,"\t*\t\t%s\n",token_string);
	break;
	case OVER:
	fprintf(listing,"\t/\t\t%s\n",token_string);
	break;
	case ENDFILE:
	fprintf(listing,"\tEOF\t\t%s\n",token_string);
	break;
	case NUM:
	fprintf(listing,"\tNUM\t\t%s\n",token_string);
	break;
	case ID:
	fprintf(listing,"\tID\t\t%s\n",token_string);
	break;
	case ERROR:
	fprintf(listing,"\tERROR\t\t%s\n",token_string);
	break;
	//COMMENT?
	//20190322!!!!!!!!!!!!
	case COMMENT_ERROR:
	fprintf(listing,"\tERROR\t\tComment Error\n");
	break;
	default: /*should never happen*/
	fprintf(listing,"Unknown token: %d\n",token);
	break;
	}
}

/* Function newStmtNode creates a new statement
 * node for syntax tree construction
 */
TreeNode * newStmtNode(StmtKind kind)
{
  TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else
    {
      for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
      t->sibling = NULL;
      t->nodekind = StmtK;
      t->kind.stmt = kind;
      t->lineno = lineno;
    }
  return t;
}

/* Function newExpNode creates a new expression 
 * node for syntax tree construction
 */
TreeNode * newExpNode(ExpKind kind)
{
  TreeNode * t = (TreeNode *) malloc(sizeof(TreeNode));
  int i;
  if (t==NULL)
    fprintf(listing, "Out of memory error at line %d\n",lineno);
  else
    {
      for (i=0;i<MAXCHILDREN;i++) t->child[i] = NULL;
      t->sibling = NULL;
      t->nodekind = ExpK;
      t->kind.exp = kind;
      t->lineno = lineno;
      t->type = Void;
    }
  return t;
}


/* Function copy_string allocates and makes a new
 * copy of an existing string
 */
char * copy_string(char * s)
{
  int n;
  char * t;
  if (s==NULL) return NULL;
  n = strlen(s)+1;
  t = malloc(n);
  if (t==NULL)
    fprintf(listing,"Out of memory error at line %d\n",lineno);
  else
    strcpy(t, s);
  return t;
}

/* Variable indentno is used by printTree to
 * store current number of spaces to indent
 */
static int indentno = 0;
/* we can track all the number of indent using static int
 * indentno!
 */
/* macros to increase/decrease indentation */
#define INDENT indentno+=2
#define UNINDENT indentno-=2

/* printSpaces indents by printing spaces */
static void printSpaces(void)
{
  int i;
  for (i=0;i<indentno;i++)
    fprintf(listing," ");
}

/* procedure printTree prints a syntax tree to the 
 * listing file using indentation to indicate subtrees
 */
/* TODO: Need to edit for each kind */
void printTree( TreeNode * tree )
{
  int i;
  INDENT;
  while (tree != NULL)
    {
      printSpaces();
      if(tree->nodekind==StmtK)
        {
          switch (tree->kind.stmt)
            {
            case IfK:
              fprintf(listing, "If\n");
              break;
            case IterK:
              fprintf(listing, "Iter: %s\n",tree->attr.name);
              break;
			case RetK:
			  fprintf(listing,"return\n");
			  break;
			case CompK:
			  fprintf(listing,"Comp\n");
			  break;
            default:
              fprintf(listing,"Unknown ExpNode kind\n");
              break;
            }
		}
       else if(tree->nodekind== ExpK)
		{
          switch (tree->kind.exp)
            {
            case OpK:
              fprintf(listing, "Op: ");
              printToken(tree->attr.op,"\0");
			  break;
            case ConstK:
              fprintf(listing, "Const: %d\n",tree->attr.val);
              break;
            case IdK:
              fprintf(listing, "Id: %s\n",tree->attr.name);
              break;
            default:
              fprintf(listing,"Unknown ExpNode kind\n");
              break;
            }
        }
        else{

		  fprintf(listing,"Unknown Node kind\n");
        }
	
    	for (i = 0; i < MAXCHILDREN; i++)
       		 printTree(tree->child[i]);
      	tree = tree->sibling;
    }
  UNINDENT;
}
