/*
** EPITECH PROJECT, 2019
** my_str_to_wordtab.c
** File description:
** my_str_to_wordtab.c
*/

#include "n4s.h"
#include "my.h"

int count_word(char *str, char c)
{
    int i;
    int n;

    i = 0;
    n = 1;
    while (str[i] != '\0' && str[i] != '\n') {
        if (str[i] == c && str[i + 1] != '\0')
            n++;
        i++;
    }
    return (n);
}

int my_strlen_space(char *str, tab_t *tab)
{
    int i = 0;

    while (str[tab->pos + i] != '\0' && str[tab->pos + i] != tab->c)
        i++;
    tab->pos = tab->pos + i + 1;
    return (i);
}

void init_tab(tab_t *tab, char c)
{
    tab->pos = 0;
    tab->c = c;
}

char **fill_tab2b(char c, char **tab, char *str)
{
    int lines = 0;
    int cols = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c && str[i + 1] == '\0') {
            tab[lines][cols] = '\0';
            tab[lines + 1] = NULL;
            return (tab);
        }
        else if ((str[i] == c)) {
            tab[lines++][cols] = '\0';
            cols = 0;
        } else {
            tab[lines][cols++] = str[i];
        }
    }
    tab[lines][cols] = '\0';
    tab[lines + 1] = NULL;
    return (tab);
}

char **my_str_to_wordtab(char *str, char c)
{
    tab_t tab_s;
    char **tab = NULL;

    init_tab(&tab_s, c);
    tab = malloc(sizeof(char *) * (count_word(str, c) + 2));
    if (tab == NULL)
        return (NULL);
    for (int i = 0; i < count_word(str, c); i++) {
        tab[i] = malloc(sizeof(char) * (my_strlen_space(str, &tab_s) + 1));
        if (tab[i] == NULL)
            return (NULL);
    }
    tab = fill_tab2b(c, tab, str);
    return (tab);
}