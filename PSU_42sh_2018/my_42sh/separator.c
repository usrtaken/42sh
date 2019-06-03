/*
** EPITECH PROJECT, 2019
** PSU_42sh_2018
** File description:
** separator
*/

#include "../headers/fourty_two_sh.h"

linked_t *oring(char *line, linked_t *tree)
{
    for (int i = 0; i < my_strlen(line); i++) {
        if (line[i] == '|' && line[i + 1] == '|') {
            tree->command = my_strcat("\0", "||");
            tree->left = tree_built(before_sign(line, '|'), tree->left);
            tree->right = tree_built(after_sign(line, '|'), tree->right);
            return (tree);
        }
    }
    return (anding(line, tree));
}

linked_t *anding(char *line, linked_t *tree)
{
    for (int i = 0; i < my_strlen(line); i++) {
        if (line[i] == '&' && line[i + 1] == '&') {
            tree->command = my_strcat("\0", "&&");
            tree->left = tree_built(before_sign(line, '&'), tree->left);
            tree->right = tree_built(after_sign(line, '&'), tree->right);
            return (tree);
        }
    }
    return (sign_left(line, tree));
}

env_modif_t run_and(linked_t *tree, env_modif_t env)
{
    if (same_str(tree->command, "&&")) {
        if (tree->left->command[0] && !(tree->left->command[0] == ' ' &&
        strlen(tree->left->command) == 1) && (!tree->right->command[0] ||
        (tree->right->command[0] == ' ' &&
        strlen(tree->right->command) == 1))) {
            my_put_err("Invalid null command.\n");
            return ((env_modif_t) {env.env, 1, env.a, env.var, env.h});
        }
        if (tree->left->command[0] && !(tree->left->command[0] == ' ' &&
        strlen(tree->left->command) == 1))
            env = run_tree(tree->left, env);
        if (tree->right->command[0] && !(tree->right->command[0] == ' ' &&
        strlen(tree->right->command) == 1) && (env.sortie == 0 ||
        !tree->left->command[0]))
            env = run_tree(tree->right, env);
    }
    return (env);
}

env_modif_t run_or(linked_t *tree, env_modif_t env)
{
    if (same_str(tree->command, "||")) {
        if ((!tree->left->command[0] ||(tree->left->command[0] == ' ' &&
        strlen(tree->left->command) == 1)) || (!tree->right->command[0] ||
        (tree->right->command[0] == ' ' &&
        strlen(tree->right->command) == 1))) {
            my_put_err("Invalid null command.\n");
            return ((env_modif_t) {env.env, 1, env.a, env.var, env.h});
        }
        env = run_tree(tree->left, env);
        if (env.sortie != 0)
            env = run_tree(tree->right, env);
    }
    return (env);
}