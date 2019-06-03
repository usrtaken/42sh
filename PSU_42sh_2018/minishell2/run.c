/*
** EPITECH PROJECT, 2019
** PSU_minishell2_2018
** File description:
** run
*/

#include "../headers/minishell2.h"

env_modif_t running_double_left(env_modif_t env, linked_t *tree, char *left)
{
    char *line = NULL, *all_enter = NULL;

    while (!same_str(line, left)) {
        line = getting_line(env, tree);
        if (!all_enter)
            all_enter = my_strcpy(all_enter, line);
        else if (!same_str(my_strcat(left, "\n"), line))
            all_enter = my_strcat(all_enter, line);
        line[my_strlen(line) - 1] = 0;
    }
    env = create_doing(all_enter, env, tree, line);
    return (env);
}

env_modif_t running_right(env_modif_t env, linked_t *tree, char *left)
{
    int keep_exit = dup(1);
    int fd = open(left, O_CREAT | O_WRONLY | O_TRUNC);
    
    chmod(left, S_IRWXU);
    dup2(fd, 1);
    env = run_tree(tree->left, env);
    dup2(keep_exit, 1);
    close(fd);
    return (env);
}

env_modif_t running_double_right(env_modif_t env, linked_t *tree, char *left)
{
    int fd, keep_exit = dup(1);

    fd = open(left, O_WRONLY | O_APPEND);
    if (fd == -1)
        fd = open(left, O_CREAT | O_WRONLY);
    chmod(left, S_IRWXU);
    dup2(fd, 1);
    env = run_tree(tree->left, env);
    dup2(keep_exit, 1);
    close(fd);
    return (env);
}

env_modif_t running_left(env_modif_t env, linked_t *tree, char *left)
{
    int fd, keep_entry = dup(0);

    fd = open(left, O_RDONLY);
    if (!exist(fd, left))
        return ((env_modif_t) {env.env, 1, env.a, env.var, env.h});
    dup2(fd, 0);
    env = run_tree(tree->left, env);
    dup2(keep_entry, 0);
    close(fd);
    return (env);
}