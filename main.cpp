#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <gl/glut.h>

#define UP 1
#define Down 2
#define LEFT 3
#define RIGHT 4

// Status Variables
GLint lvl = 1;
GLint points = 0;
GLint size = 0;
GLbyte gameOver = true;
GLbyte EnableLight = true;

// Snake Variables
GLint bodyPos[2][100] = {{}};
GLint _x = 5;
GLint _z = 10;
GLint _oldX[2] = {};
GLint _oldZ[2] = {};
GLbyte direction = 0;

// Food Variables
GLint _bx = 0;
GLint _bz = 0;

// Screen variables
GLint _w = 800;
GLint _h = 550;
GLint _Giw = 0;
GLint _Gih = 0;
GLint _Gfw = 150;
GLint _Gfh = 150;

// Variables for the Camera Angle
static GLfloat view_rotx = 45.0F;
static GLfloat view_roty = 0.0F;
static GLfloat view_rotz = 0.0F;

static GLfloat headRotation = 90.0F;
static GLfloat zoom = -300.0f;
// dem small food
int smallFoodCount = 0;
int bigFoodPoints = 3; // S? ?i?m ???c th?m khi r?n ?n bigfood
int bigFoodThreshold = 5;
int bigFoodAppeared = 0;
bool isFirstTime = false;
int snakeColorState = 0; // 0 l? m?u m?c ??nh, 1 l? m?u m?i
int snakeBody = 0;
// ham hien thi ten thanh vien
void nameMembers()
{
    GLubyte Phat[5][45] = {
        {0x7c, 0x00, 0x38, 0x00, 0x38, 0x00, 0x58, 0x00, 0x9b, 0xc0, 0x99, 0xe0, 0x9c, 0xf0, 0x9c, 0xf0, 0x9c, 0xf0, 0xcc, 0xf0, 0x6d, 0xe0, 0x3f, 0x80, 0x00, 0x00}, // P

        {0x70, 0x00, 0xd8, 0xf0, 0xcc, 0x60, 0x0c, 0x60, 0x0c, 0x60, 0xec, 0x60, 0xac, 0x60, 0xaf, 0xe0, 0x8e, 0x60, 0x8e, 0x60, 0x7e, 0x60, 0x3e, 0x30}, // H

        {0x71, 0xe0, 0xc8, 0xc0, 0x9e, 0xc0, 0xad, 0xc0, 0x24, 0xc0, 0x26, 0xc0, 0x22, 0xc0, 0x33, 0xc0, 0x19, 0xc0, 0x09, 0xc0, 0x0f, 0xc0, 0x07, 0xc0, 0x00, 0x00, 0x03, 0x00, 0x01, 0x80, 0x00, 0xc0}, // A

        {0x38, 0x00, 0x46, 0x00, 0x86, 0x00, 0x96, 0x00, 0x93, 0x00, 0x63, 0x00, 0x03, 0x00, 0x33, 0x00, 0x4b, 0x00, 0x43, 0x00, 0x3f, 0xe0, 0x0f, 0xf0, 0x03, 0x10}, // T
    };

    GLubyte Huynh[6][45] = {
        {0x70, 0x00, 0xd8, 0xf0, 0xcc, 0x60, 0x0c, 0x60, 0x0c, 0x60, 0xec, 0x60, 0xac, 0x60, 0xaf, 0xe0, 0x8e,
         0x60, 0x8e, 0x60, 0x7e, 0x60, 0x3e, 0x30}, // H

        {0x00, 0x00, 0x1c, 0xf0, 0x1e, 0xe0, 0x1b, 0xc0, 0x79, 0xc0, 0x9c, 0xc0, 0x9a, 0xc0, 0x99, 0xc0, 0x98,
         0xc0, 0x98, 0xc0, 0xd8, 0xc0, 0x78, 0xc0}, // U

        {0x00, 0x00, 0x1f, 0x80, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x07, 0x00, 0x77, 0x00, 0xc7,
         0x00, 0xc7, 0x00, 0xc5, 0x00, 0xfd, 0x90, 0x78, 0xe0, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x07, 0x00, 0x06,
         0x00, 0x1e, 0x00, 0x3c, 0x00}, // Y`

        {0x70, 0x00, 0xd8, 0x20, 0xc8, 0x60, 0x08, 0xe0, 0x08, 0xe0, 0xc8, 0xa0, 0x89, 0xa0, 0x89, 0xa0, 0xcb, 0x20, 0x7b, 0x30, 0x3f, 0x30, 0x1e, 0x30}, // N

        {0x70, 0x00, 0xd8, 0xf0, 0xcc, 0x60, 0x0c, 0x60, 0x0c, 0x60, 0xec, 0x60, 0xac, 0x60, 0xaf, 0xe0, 0x8e,
         0x60, 0x8e, 0x60, 0x7e, 0x60, 0x3e, 0x30}, // H
    };

    GLubyte Tan[4][45] = {
        {0x38, 0x00, 0x46, 0x00, 0x86, 0x00, 0x96, 0x00, 0x93, 0x00, 0x63, 0x00, 0x03, 0x00, 0x33, 0x00, 0x4b, 0x00, 0x43, 0x00, 0x3f, 0xe0, 0x0f, 0xf0, 0x03, 0x10}, // T

        {0x71, 0xe0, 0xc8, 0xc0, 0x9e, 0xc0, 0xad, 0xc0, 0x24, 0xc0, 0x26, 0xc0, 0x22, 0xc0, 0x33, 0xc0, 0x19, 0xc0, 0x09, 0xc0, 0x0f, 0xc0, 0x07, 0xc0}, // A

        {0x70, 0x00, 0xd8, 0x20, 0xc8, 0x60, 0x08, 0xe0, 0x08, 0xe0, 0xc8, 0xa0, 0x89, 0xa0, 0x89, 0xa0, 0xcb, 0x20, 0x7b, 0x30, 0x3f, 0x30, 0x1e, 0x30} // N
    };
    for (int i = 0; i < 5; ++i)
    {
        glBitmap(16, 11, 0.0, 0.0, 15.0, 0.0, Phat[i]);
    }

    //    glRasterPos2i(-100, -130);
    for (int i = 0; i < 6; ++i)
    {
        glBitmap(16, 11, 0.0, 0.0, 15.0, 0.0, Huynh[i]);
    }
    //   glRasterPos2i(-100, -150);
    for (int i = 0; i < 4; ++i)
    {
        glBitmap(16, 11, 0.0, 0.0, 20.0, 0.0, Tan[i]);
    }
    glFlush();
}
void doimau()
{
    glEnable(GL_DEPTH_TEST);
    glPushMatrix();
    glRasterPos2f(0, 35);
    glColor3f(1.0, 1, 0.2);
    nameMembers();
    glPopMatrix();
}
// Configure the lightning
void initLight()
{
    // Add ambient light
    GLfloat ambientColor[] = {0.3f, 0.4f, 0.8f, 1.0f}; // nen xanh la cay
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    // Add positioned light
    GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; // con ran
    GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f};   // do toi
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    // Add directed light
    GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f};
    // Coming from the direction (-1, 0.5, 0.5)
    GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
}
// initialize the first configurations
void Initialize(void)
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.4f, 0.8f, 1.0f, 1.0f); // Change the background to sky blue
    if (EnableLight)
    {
        glEnable(GL_COLOR_MATERIAL); // Enable color
        glEnable(GL_LIGHTING);       // Enable lighting
        glEnable(GL_LIGHT0);         // Enable light #0
        glEnable(GL_LIGHT1);         // Enable light #1
        glEnable(GL_NORMALIZE);      // Automatically normalize normals
    }
}
// Configure window resize
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1, 800.0);
}
void Write(char *string)
{ // Write string on the screen
    while (*string)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++);
}
// This Function will rotate the object according to the Angles
void ManipulateViewAngle()
{
    glRotatef(view_rotx, 1.0, 0.0, 0.0); // Rotate Arround X axis
    glRotatef(view_roty, 0.0, 1.0, 0.0); // Rotate Arround Y axis
    glRotatef(view_rotz, 0.0, 0.0, 1.0); // Rotate Arround Z axis
}
// This Function will reset the snake size and location...
void Reset()
{
    _x = 5;
    _z = 10;
    direction = 0;
    lvl = 1;
    points = 0;
    size = 0;
    gameOver = false;
    view_rotx = 45.0F;
    view_roty = 0.0F;
    view_rotz = 0.0F;
    headRotation = 90.0F;
    //     isFirstTime = true;
}
// Display a welcome screen
void WelcomeScreen()
{
    char tmp_str[40];

    glRasterPos2f(-30, 60);
    glColor3f(1, 0, 0.1);
    Write("=========Cac Thanh Vien Nhom =========");
    //	nameMembers();
    doimau();
    glRasterPos2f(-6, 10);
    Write("========= Snake Game=========");
    glRasterPos2f(-60, 0);
    Write("=========To Start Playing please press Enter =========");
}
void DrawSnake()
{
    int i;
    // Drawing the head & the plane
    glPushMatrix();
    ManipulateViewAngle();
    // This will draw the plane that the snake will run on.
    glPushMatrix();
    // glColor3f(1,0,0); //Color it red
    // glColor3f(1, 0.7, 0.2); //mau con ran
    glColor3f(1, 0.7, 0.2);
    glColor3f(0.0, 0.6, 0.2); // mau nen xanh la cay
    glTranslatef(75.0, -16.0, 75.0);
    glScalef(155, 5.0, 155);
    glutSolidCube(1);
    glPopMatrix();
    // Here we will draw the Head of the snake
    //    glColor3f(0,1,0);//Color it red  than ran mau do
    if (snakeBody == 0)
    {
        glColor3f(1, 0, 0); // M?u m?c ??nh l? ??
    }
    else
    {
        glColor3f(1, 1, 0); // M?u m?i (v? d?: m?u xanh l? c?y)
    }
    glTranslatef(_x, -10.0, _z); // Give it the location according to _x & _z
    glScalef(0.5, 0.5, 0.5);
    glutSolidSphere(10, 20, 20); // Draw the head as a sphere a litle bit bigger than the body spheres
    glRotatef(headRotation, 0.0, 1.0, 0.0);
    if (snakeBody == 1)
    {
        glColor3f(1, 1, 0); // cai mui ran
    }
    else
        glColor3f(1, 0, 0); // cai mui ran

    glTranslatef(0, 0.0, 6.0);
    glScalef(0.8, 1.0, 1.0);
    glutSolidCone(10, 10, 20, 20);
    glColor3f(1, 1, 1);
    glTranslatef(-4.0, 10.0, 0.0);
    glScalef(0.3, 0.3, 0.3);
    glutSolidSphere(10, 20, 20);
    glTranslatef(26.0, 0.0, 0.0);
    glutSolidSphere(10, 20, 20);
    glPopMatrix();

    // Drawing the body
    for (i = 0; i < size; i++)
    { // Loop throw the size and draw spheres representing the body
        glPushMatrix();
        ManipulateViewAngle();
        glTranslatef(bodyPos[0][i], -10.0, bodyPos[1][i]); // this will locate the spheres
        // glColor3f(1,1,0);//Color Red
        if (snakeBody == 0)
        {
            glColor3f(1, 0, 0); // Color Red
        }
        else
        {
            glColor3f(1, 1, 0); // Color Red
        }
        glScalef(0.5, 0.5, 0.5);
        glutSolidSphere(7, 20, 20);
        glPopMatrix();
    }
}
void DrawFood()
{
    // Draw the Sphere representing the Food for the snake
    glPushMatrix();
    ManipulateViewAngle();
    glTranslatef(_bx, -10.0, _bz);
    glColor3f(0, 1, 1); // blue
    glScalef(0.5, 0.5, 0.5);
    glutSolidSphere(7, 20, 20);
    glPopMatrix();
}

void BigFood()
{
    // Draw the Big Food (similar to DrawFood with adjustments)
    glPushMatrix();
    ManipulateViewAngle();
    glTranslatef(_bx, -10.0, _bz);
    glColor3f(0, 0, 1);      // Blue color
    glScalef(0.6, 0.6, 0.6); // Increase the scale to make it bigger
    glutSolidSphere(10, 20, 20);
    glPopMatrix();
}

void GameStatus()
{
    char tmp_str[40];
    glColor3f(0.8, 0.2, 0);
    glRasterPos2f(5, 20);
    sprintf(tmp_str, "Snake Game");
    Write(tmp_str);
    // Print the status of the game on the screen
    glColor3f(0, 0, 0);
    glRasterPos2f(5, 10);
    sprintf(tmp_str, "Level: %d Points: %d", lvl, points);
    Write(tmp_str);
}
// Generates Random Numbers for the location of the food that the snake will eat
int RandomNumber(int high, int low)
{
    return (rand() % (high - low)) + low;
}
// Generate the New Food that the snake will eat
void newFood()
{
    time_t seconds;
    time(&seconds);
    srand((unsigned int)seconds);
    _bx = RandomNumber(_Gfw - _Giw, _Giw + 10);
    _bz = RandomNumber(_Gfh - _Gih, _Gih + 10);
}
// This Function Will Check for Collision
//  kiem tra va cham
bool collision()
{
    int i;
    for (i = 0; i < size; i++)
    {
        if ((bodyPos[0][i] == _x && bodyPos[1][i] == _z) ||
            //((bodyPos[0][i] >= _x) && (bodyPos[0][i] <= _x + 5) && (bodyPos[1][i] >= _z) && (bodyPos[1][i] <= _z + 5)) ||
            //((bodyPos[0][i] <= _x) && (bodyPos[0][i] >= _x - 5) && (bodyPos[1][i] <= _z) && (bodyPos[1][i] >= _z - 5)) ||
            //((bodyPos[0][i] <= _x) && (bodyPos[0][i] >= _x - 5) && (bodyPos[1][i] >= _z) && (bodyPos[1][i] <= _z + 5)) ||
            ((bodyPos[0][i] >= _x) && (bodyPos[0][i] <= _x + 5) && (bodyPos[1][i] <= _z) && (bodyPos[1][i] >= _z - 5)))
            return true;
    }
    return false;
}
// H?m ki?m tra v? chuy?n ??i gi?a c?c nh? v? c?c l?n
// H?m ki?m tra v? v? th?c ?n
void checkAndDrawFood()
{
    if (isFirstTime || (points % 5 == 0))
    {
        if (!isFirstTime)
        {
            BigFood();
            isFirstTime = true;
        }
        // ??t bi?n isFirstTime v? false sau khi hi?n th? c?c l?n
        isFirstTime = false;
    }
    else
    {
        DrawFood();
    }
}
// This Function will move the snake according to the directions
// Taken from the Keyboard keys
void Run(int value)
{
    if (smallFoodCount >= bigFoodThreshold)
    {
        //   bigFoodAppeared = 1;  // ??t bi?n ?? v? c?c l?n
        //   smallFoodCount = 0;   // ??t l?i s? l??ng c?c nh? ?? ?n
    }
    int i;
    _oldX[1] = _x;
    _oldZ[1] = _z;
    switch (direction)
    {
    case RIGHT:
        headRotation = 90;
        _x += 6;
        if (_x > _Gfw - 2)
            _x = _Giw - 1; // This will check if the snake is going into the border so it will appear on the other side
        break;
    case LEFT:
        headRotation = -90;
        _x -= 6;
        if (_x < 0)
            _x = _Gfw - 2; // This will check if the snake is going into the border so it will appear on the other side
        break;
    case UP:
        headRotation = 0;
        _z += 6;
        if (_z > _Gfh - 2)
            _z = _Gih - 1; // This will check if the snake is going into the border so it will appear on the other side
        break;
    case Down:
        headRotation = 180;
        _z -= 6;
        if (_z < 2)
            _z = _Gfh - 2; // This will check if the snake is going into the border so it will appear on the other side
        break;
    }
    // Checks for Collisoin if yes Game Over
    if (collision())
        gameOver = true;
    // Checks if the snake ate the food (check the X and Y)
    //  If yes it will increase the points & the size of the snake & create a new food
    if ((_x == _bx && _z == _bz) ||
        ((_x >= _bx) && (_x <= _bx + 4) && (_z >= _bz) && (_z <= _bz + 4)) ||
        ((_x <= _bx) && (_x >= _bx - 4) && (_z <= _bz) && (_z >= _bz - 4)) ||
        ((_x <= _bx) && (_x >= _bx - 4) && (_z >= _bz) && (_z <= _bz + 4)) ||
        ((_x >= _bx) && (_x <= _bx + 4) && (_z <= _bz) && (_z >= _bz - 4)))
    {
        points++;
        if (points < 100)
            size++;
        if (points % 5 == 0 && lvl < 15)
            lvl++;
        printf("Congratulations! You reached level %d!\n", lvl); // In th?ng b?o level l?n m?n h?nh console
        // ??ng th?i, n?u mu?n in th?ng b?o v? vi?c t?ng ?? d?i r?n, b?n c? th? s? d?ng printf t??ng t?.
        printf("Your snake length increased to %d!\n", size); // V? d?: in th?ng b?o v? vi?c t?ng ?? d?i r?n
        newFood();
    }
    if ((_x == _bx && _z == _bz) ||
        ((_x >= _bx) && (_x <= _bx + 4) && (_z >= _bz) && (_z <= _bz + 4)) ||
        ((_x <= _bx) && (_x >= _bx - 4) && (_z <= _bz) && (_z >= _bz - 4)) ||
        ((_x <= _bx) && (_x >= _bx - 4) && (_z >= _bz) && (_z <= _bz + 4)) ||
        ((_x >= _bx) && (_x <= _bx + 4) && (_z <= _bz) && (_z >= _bz - 4)))
    {
        points += bigFoodPoints; // Th?m ?i?m khi ?n bigfood
        if (points < 100)
            size + 1000;
        if (points % 5 == 0 && lvl < 15)
            lvl++;
        newFood();
    }
    // tao hieu ung di chuyen
    for (i = 0; i < size; i++)
    { // Save the positions of the body parts
        _oldX[0] = _oldX[1];
        _oldZ[0] = _oldZ[1];
        _oldX[1] = bodyPos[0][i];
        _oldZ[1] = bodyPos[1][i];
        bodyPos[0][i] = _oldX[0];
        bodyPos[1][i] = _oldZ[0];
    }

    // Set the Timer
    int delayTime = 150;

    if (lvl >= 5 && lvl < 10)
    {
        delayTime = 100; // T?ng t?c ?? ch?y khi ??t level 5
    }
    else if (lvl >= 10)
    {
        delayTime = 200; // T?ng t?c ?? ch?y th?m khi ??t level 10
    }
    else if (lvl >= 15)
    {
        delayTime = 90;
    }
    else if (lvl >= 20)
    {
        delayTime = 50;
    }
    else if (lvl >= 30)
    {
        delayTime = 35;
    }
    glutTimerFunc(delayTime, Run, 0);
}

void Display(void)
{ // Draw Function
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (EnableLight)
        initLight();

    glTranslatef(-60.0, 40.0, zoom);
    // Check if the value of the Flag "Game Over is not True it will continue the game"
    if (!gameOver)
    {
        GameStatus();
        checkAndDrawFood();
        DrawSnake();
    }
    else
        WelcomeScreen();
    // Updates the screen
    glutPostRedisplay();
    glutSwapBuffers();
}
void Special(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_RIGHT:
        if (direction != LEFT)
            direction = RIGHT;
        break;
    case GLUT_KEY_LEFT:
        if (direction != RIGHT)
            direction = LEFT;
        break;
    case GLUT_KEY_UP:
        if (direction != UP)
            direction = Down;
        break;
    case GLUT_KEY_DOWN:
        if (direction != Down)
            direction = UP;
        break;
    }
    printf("snakeColorState: %d\n", snakeColorState);
}
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 13:
        Reset();
        glutPostRedisplay();
        break;
    // ESC to Exit
    case 27:
        exit(0);
        break;
    case 's':
        snakeColorState = 1;
        printf("Pressed 's', snakeColorState: %d\n", snakeColorState);
        break;
    case 'a':
        snakeColorState = 0;
        printf("Pressed 'a', snakeColorState: %d\n", snakeColorState);
        break;
    case 'z':
        snakeBody = 1;
        printf("Pressed '1', snakeColorState: %d\n", snakeBody);
        break;
    case 'x':
        snakeBody = 0;
        printf("Pressed '0', snakeColorState: %d\n", snakeBody);
        break;
    default:
        break;
    }
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(_w, _h);
    glutInitWindowPosition(80, 80);
    glutCreateWindow("Snake Game");
    Initialize();
    glutSpecialFunc(Special);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(Display);
    glutReshapeFunc(resize);
    //  glutKeyboardFunc(keyPressed);
    newFood();
    Run(0);
    glutMainLoop();
}

