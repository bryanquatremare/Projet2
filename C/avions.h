typedef struct plane plane;

void loadPlane(char *path, char *plane);
void swapPlane(int col, int row, char *planeToPrint, char **table, plane plane);

char getch();