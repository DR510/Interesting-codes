#include <ncurses.h>
#include <stdlib.h>

const char items[3][10] = {
    "Start", //начало игры
    "Settings", //выбор поля
    "Exit"
};
const char window[4][10] = { 
     "25x25", //раземры поля
     "40x40", 
     "60x60", 
     "Exit"
};

enum  SnakeGo{
	up = 0,
	down = 0,
	right = 0,
	left = 0
};

struct SnakeNode{ // Храним тут тело змеи.
	struct SnakeNode *next;
	int x,y;
    	
};


int ch;
int score;
unsigned choise_window = 0;
int window_max = 2;
bool food_eat = false;
int hx = 6;
int hy = 6;
int fx = 4;
int fy = 4;


int draw_window()// Отрисовка  границ поля
{
   for(int i = 1;i<window_max+1;i++)
    {

       for(int j =1;j<window_max+1;j++)
        {
           mvaddch(1,j,'*');
           mvaddch(i,1,'*');
           mvaddch(window_max,j,'*');
           mvaddch(i,window_max,'*');          
        }
     }


}
int game_over()
{

}
int add_elem() // Вызываем, если змея что-то съела.
{
	
	
}

int snake()
{


    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);

    clear();
    refresh();

   

    for (;;)
    {
       mvprintw(1,window_max+1,"Сords [%d : %d] ",hy,hx);
       mvprintw(2,window_max+1,"Score: [%d] ",score);
       mvprintw(3,window_max+1,"FoodCord: [%d : %d] ",fy,fx);
	   
       mvaddch(hy, hx, '+');
         draw_window();
         if (food_eat == true) 
         {
            fx = rand()% (window_max-3);
            fy = rand()% (window_max-3);
            food_eat = false;
         }
         mvprintw(fy,fx,"о");        
        int ch = getch();
       
        if ((ch == KEY_DOWN)&&(hy<window_max))  hy++;
        if ((ch == KEY_UP) &&(hy<window_max))   hy--;
        if ((ch == KEY_LEFT)&&(hx<window_max))  hx--;
        if ((ch == KEY_RIGHT)&&(hx<window_max)) hx++;
        if (( hx == fx)&&(hy == fy)) { food_eat = true; score++; add_elem(); };
        if (ch == KEY_BACKSPACE) return 0;
        if ((hy>=window_max)||(hx>=window_max)||(hy<=1)||(hx<=1)) return 0;
        clear();
        refresh();
}    

}

int choose_window()// Выбор размерности поля
{
initscr();
choise_window = 0;
curs_set(0);
keypad(stdscr, true);

while (true)
  {
     clear();
	
       mvprintw(0, 1,"You choosed: [ %d x %d ] \n",window_max,window_max); //?
        for ( unsigned i = 0; i < 4; i++ ) //Проходим по всем элементам меню
        {
            if ( i == choise_window ){ //Если текущий элемент совпадает с выбором пользователя
                addch('>'); //Выводим указатель
               
            }
            else{          
                addch(' '); //Иначе выводим " ", для равновесия
                 }
            printw("%s\n", window[i], "%s\n");
            
        }



      switch ( getch() )
        {
            
            case KEY_UP:
                if ( choise_window ) //Если возможно, переводим указатель вверх
                     choise_window--; 
                break;
            case KEY_DOWN:
                if (  choise_window != 3) //Если возможно, переводим указатель вниз
                     choise_window++;
                break;

             case KEY_BACKSPACE: // Функциональная клавиша
                   if ( choise_window == 0) { window_max = 25;  return 0; }
                   if (choise_window == 1){ window_max = 40;  return 0; }
                   if (choise_window == 2){ window_max = 60;  return 0; }
                   if (choise_window == 3){ return 0;                  }
                    break;
                                                          
                     
                       
        }
   }
}



int main()
{
    initscr();

    unsigned choice = 0; //Выбор пользователя

    curs_set(0); //"Убиваем" курсор
    keypad(stdscr, true);  //Включаем режим удобной работы с функциональными клавишами, другими словами KEY_UP и KEY_DOWN без этого не работали бы
    

    while ( true )
    {
        clear();
        for ( unsigned i = 0; i < 3; i++ ) //Проходим по всем элементам меню
        {
            if ( i == choice ){ //Если текущий элемент совпадает с выбором пользователя
                addch('>'); //Выводим указатель
               
            }
            else{          
                addch(' '); //Иначе выводим " ", для равновесия
                 }
            printw("%s\n", items[i], "%s\n");
        }

        //Получаем нажатие пользователя
        switch ( getch() )
        {
            
            case KEY_UP:
                if ( choice ) //Если возможно, переводим указатель вверх
                    choice--; 
                break;
            case KEY_DOWN:
                if ( choice != 2) //Если возможно, переводим указатель вниз
                    choice++;
                break;

             case KEY_BACKSPACE: // Функциональная клавиша
                       if (choice == 2) // элемент exit
                        {
                            endwin(); 
                            return 0;
                        }
                        else
                        {
                           if (choice == 1) choose_window(); // элемент Settings     
                             if (choice == 0)  snake();  // элемент Start
                        }                                       
                      break;
                       
        }
    }

    endwin();
    return 0;
}


