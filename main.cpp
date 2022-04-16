#include <GL/glut.h>
#include <stdlib.h>
#include <set>
#include <iostream>

using namespace std;

int phyWidth = 700;
int phyHeight = 700;
int logWidth = 100;
int logHeight = 100;
int centerX = logWidth/2;
int centerY = logHeight/2;
int wid = 10;
int hei = 5;
int text_x = 34;
int text_y = 82;
int btn_y1 = 53;
int btn_y2 = 29;
int text2_x = 34;
int text2_y = 95;
int g_x = 7.5, g_y = 5, g_wid = 85;
int status = 0, i = 0;
typedef pair<int, int> coords;
set<coords> arr[1000];
int aux[50][50];

void printSome(char *str, int x, int y) {
    glRasterPos2d(x, y);
    for(int i = 0; i < strlen(str); i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    glFlush();
}

void menu(){
    //Welcome text
    glColor3f(1.0, 1.0, 1.0);
    printSome("Conway's Game of Life", text_x, text_y);

    //Button 1
    glColor3f(0.439, 0.573, 0.745);
    glBegin(GL_POLYGON);
        glVertex2i(centerX - wid, btn_y1 - hei);
        glVertex2i(centerX - wid, btn_y1 + hei);
        glVertex2i(centerX + wid, btn_y1 + hei);
        glVertex2i(centerX + wid, btn_y1 - hei);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2i(centerX - wid + 1, btn_y1 - hei + 1);
        glVertex2i(centerX - wid + 1, btn_y1 + hei - 1);
        glVertex2i(centerX + wid - 1, btn_y1 + hei - 1);
        glVertex2i(centerX + wid - 1, btn_y1 - hei + 1);
    glEnd();
    glColor3f(0.439, 0.573, 0.745);
    printSome("Play", centerX - 3, btn_y1 - 1);

    //Button 2
    glColor3f(0.439, 0.573, 0.745);
    glBegin(GL_POLYGON);
        glVertex2i(centerX - wid, btn_y2 - hei);
        glVertex2i(centerX - wid, btn_y2 + hei);
        glVertex2i(centerX + wid, btn_y2 + hei);
        glVertex2i(centerX + wid, btn_y2 - hei);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2i(centerX - wid + 1, btn_y2 - hei + 1);
        glVertex2i(centerX - wid + 1, btn_y2 + hei - 1);
        glVertex2i(centerX + wid - 1, btn_y2 + hei - 1);
        glVertex2i(centerX + wid - 1, btn_y2 - hei + 1);
    glEnd();
    glColor3f(0.439, 0.573, 0.745);
    printSome("Exit", centerX - 3, btn_y2 - 1);
}

void grid(){
    //grid
    glColor3f(0.0, 0.0, 0.0);
    printSome("Conway's Game of Life", text2_x, text2_y);
    glBegin(GL_LINES);
        for (int i = 0; i < 51; i++){
            glVertex2f(g_x + (g_wid * i)/50.0, g_y);
            glVertex2f(g_x + (g_wid * i)/50.0, g_y + g_wid);
        }
        for (int i = 0; i < 51; i++){
            glVertex2f(g_x, g_y + (g_wid * i)/50.0);
            glVertex2f(g_x + g_wid, g_y + (g_wid * i)/50.0);
        }
    glEnd();

    //boxes
    glColor3f(0.0, 0.635, 0.91);
    for (auto it = arr[i].begin(); it != arr[i].end(); it++){
        glBegin(GL_POLYGON);
            glVertex2f(g_x + (*it).first*(g_wid/50.0) + 0.0715, g_y + (*it).second*(g_wid/50.0) + 0.0715);
            glVertex2f(g_x + (*it).first*(g_wid/50.0) + (g_wid/50.0) - 0.0715, g_y + (*it).second*(g_wid/50.0) + 0.0715);
            glVertex2f(g_x + (*it).first*(g_wid/50.0) + (g_wid/50.0) - 0.0715, g_y + (*it).second*(g_wid/50.0) + (g_wid/50.0) - 0.0715);
            glVertex2f(g_x + (*it).first*(g_wid/50.0) + 0.0715, g_y + (*it).second*(g_wid/50.0) + (g_wid/50.0) - 0.0715);
        glEnd();
    }
}

void init2D(){
    glClearColor(0.784, 0.749, 0.906, 1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, logWidth, 0.0, logHeight);
}

void Display(){
    glClear(GL_COLOR_BUFFER_BIT);
    if (!status)
        menu();
    else
        grid();
    glutSwapBuffers();
    glFlush();
}

float mouseXX, mouseYY;
void mouseClick(int btn, int state, int x, int y){
    if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        mouseXX = x;
        mouseXX = 1.0 * mouseXX * logWidth / glutGet(GLUT_WINDOW_WIDTH);
        mouseYY = glutGet(GLUT_WINDOW_HEIGHT) - y;
        mouseYY = 1.0 * mouseYY * logHeight / glutGet(GLUT_WINDOW_HEIGHT);
        if(!status && mouseXX >= (centerX - wid) && mouseXX <= (centerX + wid) && mouseYY >= (btn_y1 - hei) && mouseYY <= (btn_y1 + hei)){
            if (i == 0)
                cout << "Please select alive boxes" << endl;
            else
                cout << "Resuming game" << endl;
            status = 1;
            glClearColor(1.0, 1.0, 1.0, 1.0);
        }
        else if(!status && mouseXX >= (centerX - wid) && mouseXX <= (centerX + wid) && mouseYY >= (btn_y2 - hei) && mouseYY <= (btn_y2 + hei)){
            exit(1);
        }
        else if ((status) && (mouseXX > g_x) && (mouseXX < g_x + g_wid) && (mouseYY > g_y) && (mouseYY < g_y + g_wid)){
            coords coord((mouseXX - g_x)*50.0/g_wid, (mouseYY - g_y)*50.0/g_wid);
            auto it = arr[i].find(coord);
            if (it != arr[i].end()){
                cout << "Unselected " << coord.first << " " << coord.second << endl;
                arr[i].erase(it);
            }
            else{
                cout << "Selected " << coord.first << " " << coord.second << endl;
                arr[i].insert(coord);
            }
        }
        glutPostRedisplay();
    }
}

void specialKeyboard(int key, int x, int y){
    if(key == GLUT_KEY_F1 && status){
        cout << "Reset, please select alive boxes" << endl;
        arr[0].clear();
        i = 0;
    }
    else if (key == GLUT_KEY_F2 && status){
        cout << "Menu" << endl;
        status = 0;
        glClearColor(0.784, 0.749, 0.906, 1.0);
    }
    else if (key == GLUT_KEY_LEFT && i){
        i--;
        cout << "Undo, Round " << i << endl;
    }
    else if (key == GLUT_KEY_RIGHT){
        for (auto it = arr[i].begin(); it != arr[i].end(); it++){
            for (int j = -1; j < 2; j++){
                for (int k = -1; k < 2; k++){
                    int x = (*it).first - j;
                    int y = (*it).second - k;
                    if ((x < 0) || (x > 49) || (y < 0) || y > 49)
                        continue;
                    else if ((j == 0) && (k == 0))
                        aux[x][y] += 10;
                    else
                        aux[x][y]++;
                }
            }
        }
        i++;
        cout << "Round " << i << endl;
        arr[i].clear();
        for (int j = 0; j < 50; j++){
            for (int k = 0; k < 50; k++){
                if (((aux[j][k]%10 == 2) && (aux[j][k]/10%10)) || (aux[j][k]%10 == 3)){
                    arr[i].insert(coords(j, k));
                }
            }
        }
        memset(aux, 0, sizeof(aux));
    }
    glutPostRedisplay();
}

int main( int argc, char ** argv){
    memset(aux, 0, sizeof(aux));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(phyWidth, phyHeight);
    glutCreateWindow("Conway's Game of Life");
    init2D();
    glutDisplayFunc(Display);
    glutMouseFunc(mouseClick);
    glutSpecialFunc(specialKeyboard);
    glutMainLoop();
}
