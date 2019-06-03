/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** run_binary
*/

#include "../headers/fourty_two_sh.h"

char *leftest(linked_t *tree)
{
    int i = 0;

    if (tree->left)
        return (leftest(tree->left));
    for (; tree->command[i] == ' ' || tree->command[i] == '\t'; i++);
    return (&tree->command[i]);
}

env_modif_t run_semicolon(linked_t *tree, env_modif_t env)
{
    if (same_str(tree->command, ";")) {
        if (tree->left->command[0])
            env = run_tree(tree->left, env);
        if (tree->right->command[0])
            env = run_tree(tree->right, env);
    }
    return (env);
}

env_modif_t run_redirect_right(linked_t *tree, env_modif_t env)
{
    char *left = leftest(tree->right);

    left = delete_last_space(left);
    if (same_str(tree->command, ">") && directory(left))
        return ((env_modif_t) {env.env, 1, env.a, env.var, env.h});
    if (same_str(tree->command, ">") && ((!tree->right->command[0] ||
    (tree->right->command[0] == ' ' && strlen(tree->right->command) == 1)) ||
    (!tree->left->command[0] || (tree->left->command[0] == ' ' &&
    strlen(tree->left->command) == 1)))) {
        (!tree->right->command[0] || (tree->right->command[0] == ' ' &&
        strlen(tree->right->command) == 1)) ?
        my_put_err("Missing name for redirect.\n")
        : my_put_err("Invalid null command.\n");
        return ((env_modif_t) {env.env, 1, env.a, env.var, env.h});
    } else if (same_str(tree->command, ">") &&
    !same_str(tree->right->command, "&2"))
        env = running_right(env, tree, left);
    if (same_str(tree->right->command, "&2"))
        env = error_output_right(tree, env);
    return (env);
}

env_modif_t run_redirect_right_twice(linked_t *tree, env_modif_t env)
{
    char *left = leftest(tree->right);

    if (same_str(tree->command, ">>") && directory(left))
        return ((env_modif_t) {env.env, 1, env.a, env.var, env.h});
    if (same_str(tree->command, ">>") && ((!tree->right->command[0] ||
    (tree->right->command[0] == ' ' && strlen(tree->right->command) == 1)) ||
    (!tree->left->command[0] || (tree->left->command[0] == ' ' &&
    strlen(tree->left->command) == 1)))) {
        (!tree->right->command[0] || (tree->right->command[0] == ' ' &&
        strlen(tree->right->command) == 1)) ?
        my_put_err("Missing name for redirect.\n")
        : my_put_err("Invalid null command.\n");
        return ((env_modif_t) {env.env, 1, env.a, env.var, env.h});
    } else if (same_str(tree->command, ">>"))
        env = running_double_right(env, tree, left);
    return (env);
}

env_modif_t run_tree(linked_t *tree, env_modif_t env)
{
    if (!same_str(tree->command, "|") && !same_str(tree->command, ";") &&
    !same_str(tree->command, "<") && !same_str(tree->command, "<<") &&
    !same_str(tree->command, ">") && !same_str(tree->command, ">>") &&
    !same_str(tree->command, "&&") && !same_str(tree->command, "||"))
        return (my_sh_second(tree->command, env));
    env = run_semicolon(tree, env);
    env = run_or(tree, env);
    env = run_and(tree, env);
    env = run_redirect_right(tree, env);
    env = run_redirect_right_twice(tree, env);
    env = run_redirect_left(tree, env);
    env = run_redirect_left_twice(tree, env);
    env = piping(tree, env);
    return (env);
}