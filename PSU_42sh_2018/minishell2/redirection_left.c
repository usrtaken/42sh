/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** redirection_right
*/

#include "../headers/fourty_two_sh.h"

env_modif_t run_redirect_left(linked_t *tree, env_modif_t env)
{
    char *left = leftest(tree->right);

    if (same_str(tree->command, "<") && directory(left))
        return ((env_modif_t) {env.env, 1, env.a, env.var, env.h});
    if (same_str(tree->command, "<") && 
    (!tree->right->command[0] || (tree->right->command[0] == ' ' &&
    strlen(tree->right->command) == 1) || !tree->left->command[0] ||
    (tree->left->command[0] == ' ' && strlen(tree->left->command) == 1))) {
        (!tree->right->command[0] || (tree->right->command[0] == ' '
        && strlen(tree->right->command) == 1)) ?
        my_put_err("Missing name for redirect.\n") : my_put_err("Invalid null command.\n");
        return ((env_modif_t) {env.env, 1, env.a, env.var, env.h});
    } else if (same_str(tree->command, "<"))
        env = running_left(env, tree, left);
    return (env);
}

char *getting_line(env_modif_t env, linked_t *tree)
{
    char *line = NULL;
    size_t size;

    if (isatty(0)) {
        my_putstr("? ");
        line = non_block_get(env.h, env, tree);
        line = my_strcat(line, "\n");
    } else
        getline (&line, &size, stdin);
    return (line);
}

env_modif_t run_redirect_left_twice(linked_t *tree, env_modif_t env)
{
    char *left = leftest(tree->right);

    if (same_str(tree->command, "<<") && directory(left))
        return ((env_modif_t) {env.env, 1, env.a, env.var, env.h});
    if (same_str(tree->command, "<<") && ((!tree->right->command[0] ||
    (tree->right->command[0] == ' ' && strlen(tree->right->command) == 1)) ||
    (!tree->left->command[0] || (tree->left->command[0] == ' ' &&
    strlen(tree->left->command) == 1)))) {
        (!tree->right->command[0] || (tree->right->command[0] == ' ' &&
        strlen(tree->right->command) == 1)) ?
        my_put_err("Missing name for redirect.\n")
        : my_put_err("Invalid null command.\n");
        return ((env_modif_t) {env.env, 1, env.a, env.var, env.h});
    } else if (same_str(tree->command, "<<"))
        env = running_double_left(env, tree, left);
    return (env);
}

env_modif_t running_pipe(env_modif_t env, linked_t *tree, int fd[2])
{
    int pid = fork();

    if (pid) {
        dup2(fd[0], 0);
        close(fd[1]);
        env = run_tree(tree->right, env);
    } else {
        dup2(fd[1], 1);
        close(fd[0]);
        env = run_tree(tree->left, env);
        exit (0);
    }
    return (env);
}

env_modif_t piping(linked_t *tree, env_modif_t env)
{
    int fd[2], save_entry = dup(0), save_exit = dup(1);

    if (same_str(tree->command, "|") && tree->right->command[0] &&
    tree->left->command[0]) {
        if (pipe(fd) != 0)
            return ((env_modif_t) {env.env, 84, env.a, env.var, env.h});
        env = running_pipe(env, tree, fd);
        dup2(save_entry, 0);
        dup2(save_exit, 1);
    } else if (same_str(tree->command, "|") &&
    (!tree->right->command[0] || !tree->left->command[0])) {
        my_put_err("Invalid null command.\n");
        return ((env_modif_t) {env.env, 1, env.a, env.var, env.h});
    }
    return (env);
}