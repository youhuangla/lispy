/*************************************************************************
> File Name: prompt.c
> Author: 
> Mail: 
> Created Time: Thu 20 May 2021 05:01:36 PM CST
************************************************************************/

#include <stdio.h>
#include "mpc.h"
/* Declare a buffer for user input of size 2048 */
static char input[2048];

int main(int argc, char** argv) {
    /* Create Some Parsers */
    mpc_parser_t* Number   = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr     = mpc_new("expr");
    mpc_parser_t* Lispy    = mpc_new("lispy");

    /* Define them with the following Language */
    mpca_lang(MPCA_LANG_DEFAULT,
              "                                                     \
              number   : /-?[0-9]+/ ;                             \
              operator : '+' | '-' | '*' | '/' ;                  \
              expr     : <number> | '(' <operator> <expr>+ ')' ;  \
              lispy    : /^/ <operator> <expr>+ /$/ ;             \
              ",
              Number, Operator, Expr, Lispy);
    /* Print Version and Exit Information */
    puts("Lispy Version 0.0.0.0.1");
    puts("Press Ctrl+c to Exit\n");

    /* In a never ending loop */
    while (1) {

        /* Output our prompt */
        fputs("lispy> ", stdout);

        /* Read a line of user input of maximum size 2048 */
        fgets(input, 2048, stdin);

        /* Echo input back to user */
        /* Attempt to Parse the user Input */
        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lispy, &r)) {
            /* On Success Print the AST */
            mpc_ast_print(r.output);
            mpc_ast_delete(r.output);

        } else {
            /* Otherwise Print the Error */
            mpc_err_print(r.error);
            mpc_err_delete(r.error);

        }
        /* Undefine and Delete our Parsers */
        mpc_cleanup(4, Number, Operator, Expr, Lispy);
    }

    return 0;

}
