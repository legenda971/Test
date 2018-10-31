#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

int main(void)
{
    struct dirent **namelist;
    int n;

    n = scandir(".", &namelist, NULL, alphasort);
    if (n == -1)
    {
        perror("scandir");
        exit(EXIT_FAILURE);
    }

    /* NCURSES initial */
    initscr();
    noecho();
    cbreak();

    int yMax, xMax;
    getmaxyx(stdsrc, yMax, xMax);

    WINDOW * menuwin = newwin(6, xMax-12, yMax-8, 5);
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);

    keypad(menuwin, true);

    int choise;
    int selected = 0;

    while(1){
        while (n--) {
            if(!(n - selected))
                wattron(menuwin, A_REVERSE);
            mvwprintw(menuwin, n+1, 1, namelist[n]->d_name);
            wattoff(menuwin, A_REVERSE);
            free(namelist[n]);
        }
        free(namelist);

        choise = wgetch(menuwin);

        switch(choise){
            case: KEY_UP:
              selected--;
              break;
            case: KEY_DOWN:
              selected++;
              break;
            default:
              break;
        }

        if(choise == 10)
            break;
    }

    exit(EXIT_SUCCESS);
}
