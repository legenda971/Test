#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <string.h>

int main(void) {
    /*
    http://www.gnu.org/software/libc/manual/html_node/Directory-Entries.html

    struct dirent {
        ino_t          d_ino;        inode number 
        off_t          d_off;        offset to the next dirent
        unsigned short d_reclen;     length of this record 
        unsigned char  d_type;       type of file; not supported
                                       by all file system types 
        char           d_name[256];  filename 
    }
    */
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
    getmaxyx(stdscr, yMax, xMax);

    WINDOW * menuwin = newwin(yMax - 1, xMax-1, 1, 1);
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);

    keypad(menuwin, true);

    int choise;
    int selected = 0;

    while(1){
        
        for(int i = 0; i < n; i++){
            if(i == selected)
                wattron(menuwin, A_REVERSE);

            char type[10];
            /* TYPE */
            #define TYPE(x) case x: strcpy(type, #x); break;
            switch(namelist[i]->d_type){
                TYPE(DT_DIR)
                TYPE(DT_REG)

                default:
                  strcpy(type, "DT_DEF");
                  break;
            }
            #undef TYPE

            mvwprintw(menuwin, i+2, 1, "%-15s | %s |", namelist[i]->d_name, type);
            wattroff(menuwin, A_REVERSE);
        }

        choise = wgetch(menuwin);

        switch(choise){
            case KEY_UP:
              if(selected > 0)
                selected--;
              break;
            case KEY_DOWN:
              if(selected < (n-1))  
                selected++;
              break;
            default:
              break;
        }

        if(choise == 10)
            break;
    }


    while(n--)
        free(namelist[n]);
    free(namelist);

    endwin();
    exit(EXIT_SUCCESS);
}
