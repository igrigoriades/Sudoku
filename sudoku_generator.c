 

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <gtk/gtk.h>

void printBoard(int *sp){
	
	printf("\n+");
	for(int i=0;i<29;i++)
		printf("-");
	printf("+\n");
	
	for(int i=0; i<81; i++){
			
			if( (i!=0) && (i % 9 ==0 ) )
				printf("|\n");
			
			if( (i!=0) && (i % 27 == 0 ) ){
				printf("|");	
				for(int i=0;i<29;i++)
					printf("-");
				printf("|\n");		
			}
			
			
			if(i==80)		
				printf(" %d |", *(sp+i));
						
			else if(i % 9 ==0)
				printf("| %d ", *(sp+i));
			
			else if(i % 3 ==0 && i !=0)
				printf("| %d ", *(sp+i));
			
			else
				printf(" %d ", *(sp+i));
				
	}
	
	printf("\n+");
	for(int i=0;i<29;i++)
		printf("-");
	printf("+\n");
}

int* initBoard(){
	
	static int board[81] = {0};											//declared in heap using static
	return &board[0];
	
}

int checkRow(int row, int *sp){											//row in range 0 - 8 
	
	int offset = row * 9;
	
	int* tsp = (sp+offset);
	
	for(int i=0; i<9-1; i++)
		for(int j=i+1; j<9;j++)
			if( *(tsp+i) == *(tsp+j) && (*(tsp+i)!=0) )
				return 1;												//if dupl exist return 1
		
	return 0;
}

int checkCol(int col, int *sp){											//col in range 0 - 8 
	
	int offset = col;
	
	int* tsp = (sp+offset);
	
	for(int i=0; i<9-1; i++)
		for(int j=i+1; j<9;j++)
			if( *(tsp+(i*9)) == *(tsp+(j*9)) && (*(tsp+(i*9))!=0) )
				return 1;												//if dupl exist return 1
		
	return 0;
}

int checkBox(int box, int *sp){											//box in range 0 - 8
	
	int roffset = (box / 3) * 27;
	int coffset = (box % 3) * 3;
		
	int offset = roffset + coffset;
	int* tsp = (sp+offset);
		
	int arr[9] = {0};
	
	for(int i=0; i<3; i++){
		for(int j=0;j<3;j++){ 
			arr[j + (i*3)] = *(tsp);
			if(j!=2)
				tsp++;			
		}		
		tsp+=7;
	}
	
	for(int i=0;i<8;i++)
		for(int j=i+1;j<9;j++)
			if(  (arr[i] == arr[j]) && (arr[i] != 0)  )
				return 1;												//if dupl exist return 1

	return 0;
}

int checks(int *sp){
	
	for(int i=0; i<9; i++)
		if(checkRow(i, sp) || checkCol(i, sp) || checkBox(i, sp))
			return 1;
	
	return 0;
}

int solveBoard(int *sp){
	
	int interations = 81;												//count the interations
	int number; 
	int *tsp = sp;
	int logs[9] = {0};
	int lflag;
	int wflag;
	
	
	for(int i=0;i<=81;i++){
		
		number = (rand() % (9 - 1 + 1)) + 1;
		*tsp = number;
		
		wflag = 0;
		while(checks(sp)){
			
			interations++;
			for(int j=0;j<9;j++)
				if(logs[j] == 0){
					logs[j] = *tsp;
					lflag = j;
					break;
				}
			
			if(lflag < 8){
				number = (rand() % (9 - 1 + 1)) + 1;
				*tsp = number;
			}
			else{
				for(int j=0;j<9;j++)
					logs[j] = 0;
				
				*tsp = 0;	
				wflag = 1;
				break;
			}
		}
		
		if(wflag){
			i=i-2;
			tsp--;
			wflag = 0;
		}
		else
			tsp++;
	}
	
	return interations;
}

/*

char* cast(int sp){
	
	switch (sp){
	case 1:
		return "1";
	case 2:
		return "2";
	case 3:
		return "3";
	case 4:
		return "4";
	case 5:
		return "5";
	case 6:
		return "6";
	case 7:
		return "7";
	case 8:
		return "8";
	case 9:
		return "9";

	}
}

*/

int main(int argc, char** argv){
	
	
	int interations;
	srand(time(NULL));
	int *sp = initBoard();
	interations = solveBoard(sp);
	printBoard(sp);
	
	/*
	 
	//TODO -- gcc main.c -o main `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0` 
	int *tsp = sp;
	
	
	
	
	GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *cell[81];
    GtkWidget *checkbutton;
    GtkWidget *line;
    
    gtk_init (&argc, &argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_title (GTK_WINDOW (window), "Sudoku");
	//gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    
	grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);
    
    
    for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			
			cell[j + (i*9)] = gtk_button_new_with_label(cast(*tsp));
			gtk_grid_attach(GTK_GRID(grid),cell[j + (i*9)], j,i,1,1);
			tsp++;
		}
	}
	
	checkbutton = gtk_button_new_with_label("Solve");
	gtk_grid_attach(GTK_GRID(grid),checkbutton,10,0,1,9);
    
   
    gtk_widget_show_all(window);
    gtk_main();

	
	*/
	
	return 0;
	
}
