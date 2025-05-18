#ifdef UNICODE
#undef UNICODE
#endif

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <chrono>
#include <algorithm>
#include <functional>
#include "NetworkManager.h"

#undef max
#undef min

void glutSolidCube(float size)
{
    float halfSize = size / 2.0f;

    glBegin(GL_QUADS);

    // Front face
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-halfSize, -halfSize, halfSize);
    glVertex3f(halfSize, -halfSize, halfSize);
    glVertex3f(halfSize, halfSize, halfSize);
    glVertex3f(-halfSize, halfSize, halfSize);

    // Back face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f(-halfSize, halfSize, -halfSize);
    glVertex3f(halfSize, halfSize, -halfSize);
    glVertex3f(halfSize, -halfSize, -halfSize);

    // Top face
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-halfSize, halfSize, -halfSize);
    glVertex3f(-halfSize, halfSize, halfSize);
    glVertex3f(halfSize, halfSize, halfSize);
    glVertex3f(halfSize, halfSize, -halfSize);

    // Bottom face
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f(halfSize, -halfSize, -halfSize);
    glVertex3f(halfSize, -halfSize, halfSize);
    glVertex3f(-halfSize, -halfSize, halfSize);

    // Right face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(halfSize, -halfSize, -halfSize);
    glVertex3f(halfSize, halfSize, -halfSize);
    glVertex3f(halfSize, halfSize, halfSize);
    glVertex3f(halfSize, -halfSize, halfSize);

    // Left face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-halfSize, -halfSize, -halfSize);
    glVertex3f(-halfSize, -halfSize, halfSize);
    glVertex3f(-halfSize, halfSize, halfSize);
    glVertex3f(-halfSize, halfSize, -halfSize);

    glEnd();
}

void glutSolidSphere(float radius, int slices, int stacks)
{
    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluSphere(quadric, radius, slices, stacks);
    gluDeleteQuadric(quadric);
}

// Draw a character using OpenGL primitives in a retro pixel style
void DrawCharacter(float x, float y, char c, float r, float g, float b)
{
    // Character width and height - pixel-perfect for retro look
    float width = 16.0f;
    float height = 24.0f;

    // Draw character background (black) for better contrast
    // In the new projection, y increases upward
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // Set the text color based on passed parameters, defaulting to yellow
    // if no specific color is provided
    if (r == 0.0f && g == 0.0f && b == 0.0f)
    {
        // Default to bright yellow for maximum visibility
        glColor3f(1.0f, 1.0f, 0.0f);
    }
    else
    {
        glColor3f(r, g, b);
    }

    // Draw the character using lines with pixel-perfect thickness
    glLineWidth(2.0f); // Consistent thickness for retro look

    switch (c)
    {
    case '1':
        // Draw number 1
        glBegin(GL_LINES);
        glVertex2f(x + width / 2, y);
        glVertex2f(x + width / 2, y + height);
        glVertex2f(x + width / 4, y + height / 4);
        glVertex2f(x + width / 2, y);
        glEnd();
        break;

    case '2':
        // Draw number 2
        glBegin(GL_LINE_STRIP);
        glVertex2f(x + width / 4, y + height * 3 / 4);
        glVertex2f(x + width / 2, y + height);
        glVertex2f(x + width * 3 / 4, y + height * 3 / 4);
        glVertex2f(x + width / 4, y + height / 4);
        glVertex2f(x + width * 3 / 4, y);
        glEnd();
        break;

    case '3':
        // Draw number 3
        glBegin(GL_LINE_STRIP);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width * 3 / 4, y + height / 2);
        glVertex2f(x + width / 2, y + height / 2);
        glEnd();
        glBegin(GL_LINE_STRIP);
        glVertex2f(x + width * 3 / 4, y + height / 2);
        glVertex2f(x + width * 3 / 4, y);
        glVertex2f(x + width / 4, y);
        glEnd();
        break;

    case '4':
        // Draw number 4
        glBegin(GL_LINES);
        glVertex2f(x + width * 3 / 4, y);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width * 3 / 4, y + height / 2);
        glVertex2f(x + width / 4, y + height / 2);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width / 4, y + height / 2);
        glEnd();
        break;

    case 'S':
    case 's':
        // Draw letter S
        glBegin(GL_LINE_STRIP);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width / 4, y + height / 2);
        glVertex2f(x + width * 3 / 4, y + height / 2);
        glVertex2f(x + width * 3 / 4, y);
        glVertex2f(x + width / 4, y);
        glEnd();
        break;

    case 'C':
    case 'c':
        // Draw letter C
        glBegin(GL_LINE_STRIP);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width * 3 / 4, y);
        glEnd();
        break;

    case 'D':
    case 'd':
        // Draw letter D
        glBegin(GL_LINES);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width * 2 / 3, y + height);
        glVertex2f(x + width * 2 / 3, y + height);
        glVertex2f(x + width * 3 / 4, y + height * 2 / 3);
        glVertex2f(x + width * 3 / 4, y + height * 2 / 3);
        glVertex2f(x + width * 3 / 4, y + height / 3);
        glVertex2f(x + width * 3 / 4, y + height / 3);
        glVertex2f(x + width * 2 / 3, y);
        glVertex2f(x + width * 2 / 3, y);
        glVertex2f(x + width / 4, y);
        glEnd();
        break;

    case 'N':
    case 'n':
        // Draw letter N
        glBegin(GL_LINES);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width * 3 / 4, y);
        glVertex2f(x + width * 3 / 4, y);
        glVertex2f(x + width * 3 / 4, y + height);
        glEnd();
        break;

    case 'E':
    case 'e':
        // Draw letter E
        glBegin(GL_LINES);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width / 4, y + height / 2);
        glVertex2f(x + width * 2 / 3, y + height / 2);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width * 3 / 4, y);
        glEnd();
        break;

    case 'T':
    case 't':
        // Draw letter T
        glBegin(GL_LINES);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width / 2, y + height);
        glVertex2f(x + width / 2, y);
        glEnd();
        break;

    case 'W':
    case 'w':
        // Draw letter W
        glBegin(GL_LINES);
        glVertex2f(x + width / 5, y + height);
        glVertex2f(x + width * 2 / 5, y);
        glVertex2f(x + width * 2 / 5, y);
        glVertex2f(x + width / 2, y + height / 2);
        glVertex2f(x + width / 2, y + height / 2);
        glVertex2f(x + width * 3 / 5, y);
        glVertex2f(x + width * 3 / 5, y);
        glVertex2f(x + width * 4 / 5, y + height);
        glEnd();
        break;

    case 'O':
    case 'o':
        // Draw letter O
        glBegin(GL_LINE_LOOP);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width * 3 / 4, y);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width / 4, y + height);
        glEnd();
        break;

    case 'R':
    case 'r':
        // Draw letter R
        glBegin(GL_LINES);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width * 3 / 4, y + height / 2);
        glVertex2f(x + width * 3 / 4, y + height / 2);
        glVertex2f(x + width / 4, y + height / 2);
        glVertex2f(x + width / 4, y + height / 2);
        glVertex2f(x + width * 3 / 4, y);
        glEnd();
        break;

    case 'K':
    case 'k':
        // Draw letter K
        glBegin(GL_LINES);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width / 4, y + height / 2);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width / 4, y + height / 2);
        glVertex2f(x + width * 3 / 4, y);
        glEnd();
        break;

    case 'M':
    case 'm':
        // Draw letter M
        glBegin(GL_LINES);
        glVertex2f(x + width / 5, y);
        glVertex2f(x + width / 5, y + height);
        glVertex2f(x + width / 5, y + height);
        glVertex2f(x + width / 2, y + height / 2);
        glVertex2f(x + width / 2, y + height / 2);
        glVertex2f(x + width * 4 / 5, y + height);
        glVertex2f(x + width * 4 / 5, y + height);
        glVertex2f(x + width * 4 / 5, y);
        glEnd();
        break;

    case 'U':
    case 'u':
        // Draw letter U
        glBegin(GL_LINES);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width / 4, y + height / 4);
        glVertex2f(x + width / 4, y + height / 4);
        glVertex2f(x + width * 3 / 4, y + height / 4);
        glVertex2f(x + width * 3 / 4, y + height / 4);
        glVertex2f(x + width * 3 / 4, y + height);
        glEnd();
        break;

    case 'P':
    case 'p':
        // Draw letter P
        glBegin(GL_LINES);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width * 3 / 4, y + height / 2);
        glVertex2f(x + width * 3 / 4, y + height / 2);
        glVertex2f(x + width / 4, y + height / 2);
        glEnd();
        break;

    case 'V':
    case 'v':
        // Draw letter V
        glBegin(GL_LINES);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width / 2, y);
        glVertex2f(x + width / 2, y);
        glVertex2f(x + width * 3 / 4, y + height);
        glEnd();
        break;

    case 'F':
    case 'f':
        // Draw letter F
        glBegin(GL_LINES);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width / 4, y + height / 2);
        glVertex2f(x + width * 2 / 3, y + height / 2);
        glEnd();
        break;

    case 'L':
    case 'l':
        // Draw letter L
        glBegin(GL_LINES);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width * 3 / 4, y);
        glEnd();
        break;

    case 'I':
    case 'i':
        // Draw letter I
        glBegin(GL_LINES);
        glVertex2f(x + width / 2, y);
        glVertex2f(x + width / 2, y + height);
        glVertex2f(x + width / 3, y + height);
        glVertex2f(x + width * 2 / 3, y + height);
        glVertex2f(x + width / 3, y);
        glVertex2f(x + width * 2 / 3, y);
        glEnd();
        break;

    case 'G':
    case 'g':
        // Draw letter G
        glBegin(GL_LINE_STRIP);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width * 3 / 4, y);
        glVertex2f(x + width * 3 / 4, y + height / 2);
        glVertex2f(x + width / 2, y + height / 2);
        glEnd();
        break;

    case 'A':
    case 'a':
        // Draw letter A
        glBegin(GL_LINES);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width / 2, y + height);
        glVertex2f(x + width / 2, y + height);
        glVertex2f(x + width * 3 / 4, y);
        glVertex2f(x + width / 3, y + height / 2);
        glVertex2f(x + width * 2 / 3, y + height / 2);
        glEnd();
        break;

    case 'B':
    case 'b':
        // Draw letter B
        glBegin(GL_LINES);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width * 2 / 3, y + height);
        glVertex2f(x + width * 2 / 3, y + height);
        glVertex2f(x + width * 3 / 4, y + height * 3 / 4);
        glVertex2f(x + width * 3 / 4, y + height * 3 / 4);
        glVertex2f(x + width * 2 / 3, y + height / 2);
        glVertex2f(x + width * 2 / 3, y + height / 2);
        glVertex2f(x + width / 4, y + height / 2);
        glVertex2f(x + width * 2 / 3, y + height / 2);
        glVertex2f(x + width * 3 / 4, y + height / 4);
        glVertex2f(x + width * 3 / 4, y + height / 4);
        glVertex2f(x + width * 2 / 3, y);
        glVertex2f(x + width * 2 / 3, y);
        glVertex2f(x + width / 4, y);
        glEnd();
        break;

    case '5':
        // Draw number 5
        glBegin(GL_LINE_STRIP);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width / 4, y + height / 2);
        glVertex2f(x + width * 3 / 4, y + height / 2);
        glVertex2f(x + width * 3 / 4, y);
        glVertex2f(x + width / 4, y);
        glEnd();
        break;

    case '6':
        // Draw number 6
        glBegin(GL_LINE_STRIP);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width * 3 / 4, y);
        glVertex2f(x + width * 3 / 4, y + height / 2);
        glVertex2f(x + width / 4, y + height / 2);
        glEnd();
        break;

    case '7':
        // Draw number 7
        glBegin(GL_LINE_STRIP);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width / 2, y);
        glEnd();
        break;

    case '8':
        // Draw number 8
        glBegin(GL_LINE_LOOP);
        glVertex2f(x + width / 4, y + height / 2);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width * 3 / 4, y + height / 2);
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(x + width / 4, y + height / 2);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width * 3 / 4, y);
        glVertex2f(x + width * 3 / 4, y + height / 2);
        glEnd();
        break;

    case '9':
        // Draw number 9
        glBegin(GL_LINE_STRIP);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width * 3 / 4, y);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width / 4, y + height / 2);
        glVertex2f(x + width * 3 / 4, y + height / 2);
        glEnd();
        break;

    case '0':
        // Draw number 0
        glBegin(GL_LINE_LOOP);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width * 3 / 4, y);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width / 4, y + height);
        glEnd();
        break;

    case 'H':
    case 'h':
        // Draw letter H
        glBegin(GL_LINES);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width * 3 / 4, y);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width / 4, y + height / 2);
        glVertex2f(x + width * 3 / 4, y + height / 2);
        glEnd();
        break;

    case 'J':
    case 'j':
        // Draw letter J
        glBegin(GL_LINES);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width * 3 / 4, y + height / 4);
        glVertex2f(x + width * 3 / 4, y + height / 4);
        glVertex2f(x + width / 2, y);
        glVertex2f(x + width / 2, y);
        glVertex2f(x + width / 4, y + height / 4);
        glEnd();
        break;

    case 'Q':
    case 'q':
        // Draw letter Q
        glBegin(GL_LINE_LOOP);
        glVertex2f(x + width / 4, y + height / 4);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width * 3 / 4, y + height / 4);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(x + width / 2, y + height / 4);
        glVertex2f(x + width * 3 / 4, y);
        glEnd();
        break;

    case 'X':
    case 'x':
        // Draw letter X
        glBegin(GL_LINES);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width * 3 / 4, y);
        glEnd();
        break;

    case 'Y':
    case 'y':
        // Draw letter Y
        glBegin(GL_LINES);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width / 2, y + height / 2);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width / 2, y + height / 2);
        glVertex2f(x + width / 2, y + height / 2);
        glVertex2f(x + width / 2, y);
        glEnd();
        break;

    case 'Z':
    case 'z':
        // Draw letter Z
        glBegin(GL_LINE_STRIP);
        glVertex2f(x + width / 4, y + height);
        glVertex2f(x + width * 3 / 4, y + height);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width * 3 / 4, y);
        glEnd();
        break;

    case '.':
        // Draw period - make it larger and more visible
        glPointSize(5.0f);
        glBegin(GL_POINTS);
        glVertex2f(x + width / 2, y + height / 5);
        glEnd();
        break;

    case ',':
        // Draw comma
        glPointSize(5.0f);
        glBegin(GL_POINTS);
        glVertex2f(x + width / 2, y + height / 5);
        glEnd();
        glBegin(GL_LINES);
        glVertex2f(x + width / 2, y + height / 5);
        glVertex2f(x + width / 3, y);
        glEnd();
        break;

    case ':':
        // Draw colon
        glPointSize(5.0f);
        glBegin(GL_POINTS);
        glVertex2f(x + width / 2, y + height / 4);
        glVertex2f(x + width / 2, y + height * 3 / 4);
        glEnd();
        break;

    case '-':
        // Draw hyphen/minus
        glBegin(GL_LINES);
        glVertex2f(x + width / 4, y + height / 2);
        glVertex2f(x + width * 3 / 4, y + height / 2);
        glEnd();
        break;

    case '_':
        // Draw underscore
        glBegin(GL_LINES);
        glVertex2f(x + width / 4, y + height / 5);
        glVertex2f(x + width * 3 / 4, y + height / 5);
        glEnd();
        break;

    case '/':
        // Draw forward slash
        glBegin(GL_LINES);
        glVertex2f(x + width / 4, y);
        glVertex2f(x + width * 3 / 4, y + height);
        glEnd();
        break;

    case '\\':
        // Draw backslash
        glBegin(GL_LINES);
        glVertex2f(x + width * 3 / 4, y);
        glVertex2f(x + width / 4, y + height);
        glEnd();
        break;

    case '@':
        // Draw at symbol
        glBegin(GL_LINE_LOOP);
        glVertex2f(x + width * 3 / 4, y + height * 2 / 3);
        glVertex2f(x + width * 3 / 4, y + height / 3);
        glVertex2f(x + width / 4, y + height / 3);
        glVertex2f(x + width / 4, y + height * 2 / 3);
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex2f(x + width / 2, y + height / 2);
        glVertex2f(x + width * 2 / 3, y + height / 2);
        glVertex2f(x + width * 2 / 3, y + height * 3 / 5);
        glVertex2f(x + width / 2, y + height * 3 / 5);
        glEnd();
        break;

    case ' ':
        // Space - do nothing
        break;

    default:
        // For any other character, draw a visible representation
        // Draw a hash/pound symbol
        glBegin(GL_LINES);
        // Horizontal lines
        glVertex2f(x + width / 4, y + height * 2 / 3);
        glVertex2f(x + width * 3 / 4, y + height * 2 / 3);
        glVertex2f(x + width / 4, y + height / 3);
        glVertex2f(x + width * 3 / 4, y + height / 3);
        // Vertical lines
        glVertex2f(x + width / 3, y + height);
        glVertex2f(x + width / 3, y);
        glVertex2f(x + width * 2 / 3, y + height);
        glVertex2f(x + width * 2 / 3, y);
        glEnd();
        break;
    }

    glLineWidth(1.0f); // Reset line width
}

// GLUT font definitions
void *GLUT_BITMAP_HELVETICA_12 = nullptr;

// Constants
const int INITIAL_WINDOW_WIDTH = 1024;
const int INITIAL_WINDOW_HEIGHT = 768;
const char *WINDOW_TITLE = "Enhanced Tank Battle Simulation";

// Global variables
HWND hWnd;
HDC hDC;
HGLRC hRC;
bool running = true;
bool keys[256] = {false};
bool specialKeys[256] = {false};
int mouseX = 0, mouseY = 0;
bool mouseLeftDown = false;
bool mouseRightDown = false;
bool isFullscreen = false;
RECT windowedRect; // Store window position/size when switching to fullscreen
int currentWidth = INITIAL_WINDOW_WIDTH;
int currentHeight = INITIAL_WINDOW_HEIGHT;

// Time tracking
std::chrono::high_resolution_clock::time_point lastFrameTime;
float deltaTime = 0.0f;

// Tank properties
struct Tank
{
    float x = 0.0f;
    float y = 0.5f;
    float z = 0.0f;
    float bodyRotation = 0.0f;
    float turretRotation = 0.0f;
    float speed = 0.0f;
    float maxSpeed = 10.0f;
    float acceleration = 15.0f;
    float deceleration = 20.0f;
    float rotationSpeed = 100.0f;
    float turretRotationSpeed = 120.0f;
    int health = 100;
    int maxHealth = 100;
    float reloadTime = 0.5f;
    float currentReloadTime = 0.0f;
    bool canFire = true;
};

// Camera properties
struct Camera
{
    float distance = 10.0f;
    float height = 5.0f;
    float angle = 0.0f;
    float smoothFactor = 5.0f;
    float targetX = 0.0f;
    float targetY = 0.0f;
    float targetZ = 0.0f;
    float currentX = 0.0f;
    float currentY = 0.0f;
    float currentZ = 0.0f;
};

// Bullet properties
struct Bullet
{
    float x, y, z;
    float dirX, dirY, dirZ;
    float speed;
    float lifetime;
    bool active;
    int damage;
    float rotation; // Rotation for spinning shells
    float scale;    // Size of the bullet
    int type;       // 0 = AP (armor piercing), 1 = HE (high explosive)
};

// Particle properties
struct Particle
{
    float x, y, z;
    float dirX, dirY, dirZ;
    float speed;
    float size;
    float lifetime;
    float maxLifetime;
    float r, g, b, a;
    bool active;
};

// Structure for terrain objects like trees and rocks
struct TerrainObject
{
    float x, z;     // Position
    float y;        // Height (calculated from terrain)
    float scale;    // Size scaling
    int type;       // 0 = tree, 1 = rock, 2 = bush
    float rotation; // Y-axis rotation
};

// Terrain properties
struct Terrain
{
    int width = 100;
    int length = 100;
    float *heightMap = nullptr;
    std::vector<TerrainObject> objects;

    Terrain()
    {
        // Initialize height map
        heightMap = new float[width * length];
        for (int i = 0; i < width * length; i++)
        {
            heightMap[i] = 0.0f;
        }

        // Generate some hills
        for (int i = 0; i < 15; i++) // Increased number of hills
        {
            int centerX = rand() % width;
            int centerZ = rand() % length;
            float height = (rand() % 100) / 100.0f * 6.0f; // Increased max height
            float radius = (rand() % 100) / 100.0f * 20.0f + 5.0f;

            for (int x = 0; x < width; x++)
            {
                for (int z = 0; z < length; z++)
                {
                    float distance = sqrt(pow(x - centerX, 2) + pow(z - centerZ, 2));
                    if (distance < radius)
                    {
                        float factor = (radius - distance) / radius;
                        heightMap[x + z * width] += height * factor;
                    }
                }
            }
        }

        // Add some valleys/craters
        for (int i = 0; i < 8; i++)
        {
            int centerX = rand() % width;
            int centerZ = rand() % length;
            float depth = -((rand() % 100) / 100.0f * 2.0f); // Negative for depression
            float radius = (rand() % 100) / 100.0f * 15.0f + 5.0f;

            for (int x = 0; x < width; x++)
            {
                for (int z = 0; z < length; z++)
                {
                    float distance = sqrt(pow(x - centerX, 2) + pow(z - centerZ, 2));
                    if (distance < radius)
                    {
                        float factor = (radius - distance) / radius;
                        heightMap[x + z * width] += depth * factor;
                    }
                }
            }
        }

        // Generate terrain objects (trees, rocks, bushes)
        generateTerrainObjects();
    }

    // Generate random terrain objects
    void generateTerrainObjects()
    {
        // Clear existing objects
        objects.clear();

        // Define the safe zone around the player spawn (center)
        float safeZoneRadius = 15.0f;

        // Add trees (reduced count for better performance)
        for (int i = 0; i < 20; i++) // Reduced from 80 to 20
        {
            TerrainObject obj;

            // Random position
            obj.x = (rand() % (width - 10)) - (width / 2) + 5.0f;
            obj.z = (rand() % (length - 10)) - (length / 2) + 5.0f;

            // Check if in safe zone (don't place objects too close to spawn)
            float distFromCenter = sqrt(obj.x * obj.x + obj.z * obj.z);
            if (distFromCenter < safeZoneRadius)
            {
                continue; // Skip this object
            }

            obj.y = getHeight(obj.x, obj.z);
            obj.scale = (rand() % 50) / 100.0f + 0.8f; // 0.8 to 1.3 scale
            obj.type = 0;                              // Tree
            obj.rotation = (rand() % 360) * 3.14159f / 180.0f;

            objects.push_back(obj);
        }

        // Add rocks (reduced count for better performance)
        for (int i = 0; i < 15; i++) // Reduced from 40 to 15
        {
            TerrainObject obj;

            // Random position
            obj.x = (rand() % (width - 10)) - (width / 2) + 5.0f;
            obj.z = (rand() % (length - 10)) - (length / 2) + 5.0f;

            // Check if in safe zone
            float distFromCenter = sqrt(obj.x * obj.x + obj.z * obj.z);
            if (distFromCenter < safeZoneRadius)
            {
                continue; // Skip this object
            }

            obj.y = getHeight(obj.x, obj.z);
            obj.scale = (rand() % 60) / 100.0f + 0.5f; // 0.5 to 1.1 scale
            obj.type = 1;                              // Rock
            obj.rotation = (rand() % 360) * 3.14159f / 180.0f;

            objects.push_back(obj);
        }

        // Add bushes (reduced count for better performance)
        for (int i = 0; i < 10; i++) // Reduced from 60 to 10
        {
            TerrainObject obj;

            // Random position
            obj.x = (rand() % (width - 10)) - (width / 2) + 5.0f;
            obj.z = (rand() % (length - 10)) - (length / 2) + 5.0f;

            obj.y = getHeight(obj.x, obj.z);
            obj.scale = (rand() % 40) / 100.0f + 0.3f; // 0.3 to 0.7 scale
            obj.type = 2;                              // Bush
            obj.rotation = (rand() % 360) * 3.14159f / 180.0f;

            objects.push_back(obj);
        }
    }

    ~Terrain()
    {
        delete[] heightMap;
    }

    float getHeight(float x, float z) const
    {
        // Convert world coordinates to terrain coordinates
        float terrainX = (x + width / 2.0f);
        float terrainZ = (z + length / 2.0f);

        // Clamp to terrain boundaries
        terrainX = std::max(0.0f, std::min(terrainX, (float)width - 1.0f));
        terrainZ = std::max(0.0f, std::min(terrainZ, (float)length - 1.0f));

        // Get the four nearest points
        int x1 = (int)terrainX;
        int z1 = (int)terrainZ;
        int x2 = std::min(x1 + 1, width - 1);
        int z2 = std::min(z1 + 1, length - 1);

        // Calculate fractional parts
        float fracX = terrainX - x1;
        float fracZ = terrainZ - z1;

        // Bilinear interpolation
        float h1 = heightMap[x1 + z1 * width];
        float h2 = heightMap[x2 + z1 * width];
        float h3 = heightMap[x1 + z2 * width];
        float h4 = heightMap[x2 + z2 * width];

        float h12 = h1 * (1 - fracX) + h2 * fracX;
        float h34 = h3 * (1 - fracX) + h4 * fracX;

        return h12 * (1 - fracZ) + h34 * fracZ;
    }
};

// Game objects
Tank playerTank;
Tank remoteTank; // Tank controlled by the remote player
Camera camera;
std::vector<Bullet> bullets;
std::vector<Particle> particles;
Terrain terrain;

// Game state
bool gameOver = false;
bool playerWon = false;
bool showGameOverScreen = false;
bool showRetryButton = false;

// Shader variables
GLuint shaderProgram = 0;
GLuint vertexShader = 0;
GLuint fragmentShader = 0;

// Networking
NetworkManager networkManager;
bool isNetworked = false;
bool isServer = false;
std::string serverIP = "127.0.0.1";
std::string networkStatus = "Not Connected";
std::vector<std::string> chatMessages;
std::string inputBuffer;
bool showNetworkMenu = false;
bool inputActive = false;

// Function prototypes
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void EnableOpenGL(HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC);
void InitGame();
void UpdateGame();
void RenderGame();
void DrawTank(const Tank &tank);
void DrawBullets();
void DrawParticles();
void DrawTerrain();
void DrawHUD();
void DrawNetworkMenu();
void DrawGameOverScreen();
void FireBullet();
void CreateExplosion(float x, float y, float z, int particleCount);
void UpdateCamera();
void UpdateParticles();
void DrawText(float x, float y, const std::string &text, float r, float g, float b);
void DrawSimpleText(float x, float y, const std::string &text, float r, float g, float b);
void ResizeWindow(int width, int height);
void ToggleFullscreen();
void ResetGame();

// Networking functions
void InitializeNetworking();
void StartServer();
void ConnectToServer(const std::string &ip);
void DisconnectFromNetwork();
void SendTankState();
void SendBulletFired(const Bullet &bullet);
void HandleNetworkMessage(MessageType type, const void *data, int size);
void HandleConnect(bool success);
void HandleDisconnect();
void UpdateNetworking();

// Main function
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASS wc;
    MSG msg;

    // Register window class
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "EnhancedTankGame";
    RegisterClass(&wc);

    // Create main window
    hWnd = CreateWindow(
        "EnhancedTankGame", WINDOW_TITLE,
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
        INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

    // Enable OpenGL
    EnableOpenGL(hWnd, &hDC, &hRC);

    // Initialize game
    InitGame();

    // Show the window
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Switch to fullscreen mode by default
    ToggleFullscreen();

    // Initialize time tracking
    lastFrameTime = std::chrono::high_resolution_clock::now();

    // Message loop
    while (running)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                running = false;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // Calculate delta time
            auto currentTime = std::chrono::high_resolution_clock::now();
            deltaTime = std::chrono::duration<float>(currentTime - lastFrameTime).count();
            lastFrameTime = currentTime;

            // Cap delta time to prevent physics issues
            if (deltaTime > 0.1f)
                deltaTime = 0.1f;

            // Update and render the game
            UpdateGame();
            RenderGame();
            SwapBuffers(hDC);

            // Add a small delay to prevent 100% CPU usage
            Sleep(1);
        }
    }

    // Shutdown
    DisableOpenGL(hWnd, hDC, hRC);
    DestroyWindow(hWnd);

    return msg.wParam;
}

// Window procedure
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    case WM_SIZE:
        // Handle window resizing
        ResizeWindow(LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_KEYDOWN:
        keys[wParam] = true;
        if (wParam == VK_ESCAPE)
        {
            if (showNetworkMenu || inputActive)
            {
                // Close the network menu or input field
                showNetworkMenu = false;
                inputActive = false;
                inputBuffer.clear();
            }
            else
            {
                PostQuitMessage(0);
            }
        }
        else if (wParam == VK_CONTROL)
        {
            // Toggle network menu
            showNetworkMenu = !showNetworkMenu;
            inputActive = false;
            inputBuffer.clear();

            // Debug message
            std::cout << "Network menu toggled: " << (showNetworkMenu ? "ON" : "OFF") << std::endl;
        }
        else if (wParam == VK_F11 && !keys[wParam])
        {
            // Toggle fullscreen mode
            ToggleFullscreen();
        }
        else if (inputActive)
        {
            // Handle text input
            if (wParam == VK_RETURN)
            {
                // Process the input
                if (inputBuffer.length() > 0)
                {
                    if (inputBuffer.substr(0, 7) == "connect")
                    {
                        // Extract IP address
                        size_t pos = inputBuffer.find(' ');
                        if (pos != std::string::npos && pos + 1 < inputBuffer.length())
                        {
                            // Get the raw IP string exactly as entered
                            std::string rawIP = inputBuffer.substr(pos + 1);

                            // Trim any whitespace from the beginning and end
                            size_t start = rawIP.find_first_not_of(" \t\r\n");
                            size_t end = rawIP.find_last_not_of(" \t\r\n");

                            if (start != std::string::npos && end != std::string::npos)
                            {
                                serverIP = rawIP.substr(start, end - start + 1);
                            }
                            else
                            {
                                serverIP = rawIP; // Use as is if no whitespace found
                            }

                            // Connect using the cleaned IP
                            ConnectToServer(serverIP);
                        }
                        else
                        {
                            std::cout << "====================================" << std::endl;
                            std::cout << "ERROR: Invalid connect command format" << std::endl;
                            std::cout << "INPUT BUFFER: \"" << inputBuffer << "\"" << std::endl;
                            std::cout << "POSITION OF SPACE: " << (pos == std::string::npos ? -1 : static_cast<int>(pos)) << std::endl;
                            std::cout << "EXPECTED FORMAT: connect 192.168.1.1" << std::endl;
                            std::cout << "====================================" << std::endl;
                        }
                    }
                    else if (inputBuffer == "host")
                    {
                        StartServer();
                    }
                    else if (inputBuffer == "disconnect")
                    {
                        DisconnectFromNetwork();
                    }
                    else if (inputBuffer.substr(0, 4) == "say " && inputBuffer.length() > 4)
                    {
                        // Send chat message
                        if (networkManager.IsConnected())
                        {
                            networkManager.SendTextMessage(inputBuffer.substr(4));
                            chatMessages.push_back("You: " + inputBuffer.substr(4));
                            // Limit chat history
                            if (chatMessages.size() > 10)
                            {
                                chatMessages.erase(chatMessages.begin());
                            }
                        }
                    }
                }

                // Clear input
                inputActive = false;
                inputBuffer.clear();
            }
            else if (wParam == VK_BACK && !inputBuffer.empty())
            {
                // Handle backspace
                inputBuffer.pop_back();
            }
            else if (wParam == VK_DECIMAL || wParam == VK_OEM_PERIOD)
            {
                // Handle numpad dot (VK_DECIMAL) and regular keyboard dot (VK_OEM_PERIOD)
                std::cout << "DOT KEY PRESSED: " << (wParam == VK_DECIMAL ? "NUMPAD DOT" : "REGULAR DOT") << std::endl;
                inputBuffer += '.';
            }
            else if (wParam >= VK_NUMPAD0 && wParam <= VK_NUMPAD9)
            {
                // Handle numpad digits
                char digit = '0' + (wParam - VK_NUMPAD0);
                std::cout << "NUMPAD DIGIT PRESSED: " << digit << std::endl;
                inputBuffer += digit;
            }
            else if (wParam >= 32 && wParam <= 126)
            {
                // Printable ASCII characters
                std::cout << "REGULAR KEY PRESSED: '" << (char)wParam << "' (ASCII: " << wParam << ")" << std::endl;
                inputBuffer += (char)wParam;
            }
        }
        else if (showNetworkMenu)
        {
            if (wParam == '1')
            {
                // Start server
                StartServer();
            }
            else if (wParam == '2')
            {
                // Connect to server (show input field)
                inputActive = true;
                inputBuffer = "connect ";
            }
            else if (wParam == '3')
            {
                // Disconnect
                DisconnectFromNetwork();
            }
            else if (wParam == '4')
            {
                // Send chat message
                inputActive = true;
                inputBuffer = "say ";
            }
        }
        break;
    case WM_KEYUP:
        keys[wParam] = false;
        break;
    case WM_LBUTTONDOWN:
        mouseLeftDown = true;
        break;
    case WM_LBUTTONUP:
        mouseLeftDown = false;
        break;
    case WM_RBUTTONDOWN:
        mouseRightDown = true;
        break;
    case WM_RBUTTONUP:
        mouseRightDown = false;
        break;
    case WM_MOUSEMOVE:
        mouseX = LOWORD(lParam);
        mouseY = HIWORD(lParam);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Enable OpenGL
void EnableOpenGL(HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int format;

    // Get the device context
    *hDC = GetDC(hWnd);

    // Set the pixel format for the DC
    ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    format = ChoosePixelFormat(*hDC, &pfd);
    SetPixelFormat(*hDC, format, &pfd);

    // Create and enable the render context
    *hRC = wglCreateContext(*hDC);
    wglMakeCurrent(*hDC, *hRC);

    // Set up the viewport
    glViewport(0, 0, currentWidth, currentHeight);

    // Set up the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)currentWidth / (double)currentHeight, 0.1, 1000.0);

    // Switch back to modelview matrix
    glMatrixMode(GL_MODELVIEW);

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Set up light 0
    GLfloat light_position[] = {100.0f, 100.0f, 100.0f, 1.0f};
    GLfloat light_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    // Enable color material
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // Enable blending for particles
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Disable OpenGL
void DisableOpenGL(HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
}

// Initialize game
void InitGame()
{
    // Initialize player tank
    playerTank.x = 0.0f;
    playerTank.y = 0.5f;
    playerTank.z = 0.0f;
    playerTank.bodyRotation = 0.0f;
    playerTank.turretRotation = 0.0f;
    playerTank.speed = 0.0f;
    playerTank.health = 100;

    // Initialize remote tank (for multiplayer)
    remoteTank = playerTank;
    remoteTank.x = 10.0f; // Start at a different position
    remoteTank.z = 10.0f;

    // Initialize camera
    camera.distance = 10.0f;
    camera.height = 5.0f;
    camera.angle = 0.0f;
    camera.targetX = playerTank.x;
    camera.targetY = playerTank.y;
    camera.targetZ = playerTank.z;
    camera.currentX = playerTank.x - camera.distance;
    camera.currentY = playerTank.y + camera.height;
    camera.currentZ = playerTank.z;

    // Reserve space for bullets and particles
    bullets.reserve(100);
    particles.reserve(1000);

    // Set random seed
    srand(GetTickCount());

    // Initialize networking
    InitializeNetworking();

    std::cout << "Enhanced Tank Battle Simulation initialized!" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  W/Up Arrow: Move forward" << std::endl;
    std::cout << "  S/Down Arrow: Move backward" << std::endl;
    std::cout << "  A/Left Arrow: Rotate left" << std::endl;
    std::cout << "  D/Right Arrow: Rotate right" << std::endl;
    std::cout << "  Mouse: Aim turret" << std::endl;
    std::cout << "  Left Mouse Button/Space: Fire" << std::endl;
    std::cout << "  CTRL: Toggle Network Menu" << std::endl;
    std::cout << "  ESC: Exit" << std::endl;
}

// Update game state
void UpdateGame()
{
    // If game is over, only process networking and skip gameplay updates
    if (gameOver)
    {
        // Still update networking to ensure sync between clients
        if (isNetworked && networkManager.IsConnected())
        {
            UpdateNetworking();
        }

        // Update particles for visual effects
        UpdateParticles();

        // Update camera
        UpdateCamera();

        return;
    }

    // Update tank movement with realistic physics
    float moveX = 0.0f, moveZ = 0.0f;
    float rotateY = 0.0f;

    // Track the current terrain slope under the tank
    float terrainHeightFront = terrain.getHeight(
        playerTank.x + 2.0f * sin(playerTank.bodyRotation * 3.14159f / 180.0f),
        playerTank.z + 2.0f * cos(playerTank.bodyRotation * 3.14159f / 180.0f));

    float terrainHeightBack = terrain.getHeight(
        playerTank.x - 2.0f * sin(playerTank.bodyRotation * 3.14159f / 180.0f),
        playerTank.z - 2.0f * cos(playerTank.bodyRotation * 3.14159f / 180.0f));

    // Calculate slope angle (affects acceleration and max speed)
    float slopeAngle = atan2(terrainHeightFront - terrainHeightBack, 4.0f);
    float slopeFactor = sin(slopeAngle);

    // Handle keyboard input for tank movement
    if (keys['W'] || keys[VK_UP])
    {
        // Accelerate forward with slope effect
        float effectiveAcceleration = playerTank.acceleration - slopeFactor * 20.0f;
        playerTank.speed += effectiveAcceleration * deltaTime;

        // Limit max speed based on slope
        float effectiveMaxSpeed = playerTank.maxSpeed * (1.0f - fabs(slopeFactor) * 0.5f);
        if (playerTank.speed > effectiveMaxSpeed)
            playerTank.speed = effectiveMaxSpeed;
    }
    else if (keys['S'] || keys[VK_DOWN])
    {
        // Accelerate backward with slope effect
        float effectiveAcceleration = playerTank.acceleration + slopeFactor * 20.0f;
        playerTank.speed -= effectiveAcceleration * deltaTime;

        // Backward speed is slower than forward
        float effectiveMaxSpeed = (playerTank.maxSpeed / 2.0f) * (1.0f - fabs(slopeFactor) * 0.5f);
        if (playerTank.speed < -effectiveMaxSpeed)
            playerTank.speed = -effectiveMaxSpeed;
    }
    else
    {
        // Apply slope effect when no input (roll downhill)
        playerTank.speed += slopeFactor * 10.0f * deltaTime;

        // Apply friction/deceleration
        if (playerTank.speed > 0.0f)
        {
            playerTank.speed -= playerTank.deceleration * deltaTime;
            if (playerTank.speed < 0.0f && slopeFactor <= 0.0f)
                playerTank.speed = 0.0f;
        }
        else if (playerTank.speed < 0.0f)
        {
            playerTank.speed += playerTank.deceleration * deltaTime;
            if (playerTank.speed > 0.0f && slopeFactor >= 0.0f)
                playerTank.speed = 0.0f;
        }
    }

    // Calculate rotation speed based on tank speed
    // Slower rotation at higher speeds for realism
    float speedFactor = fabs(playerTank.speed) / playerTank.maxSpeed;
    float effectiveRotationSpeed = playerTank.rotationSpeed * (1.0f - speedFactor * 0.7f);

    // Handle rotation input
    if (keys['A'] || keys[VK_LEFT])
    {
        // Rotate left (fixed to be correct direction)
        rotateY = effectiveRotationSpeed * deltaTime;

        // Add slight sideways friction when turning at speed
        if (fabs(playerTank.speed) > 2.0f)
        {
            playerTank.speed *= (1.0f - 0.2f * deltaTime);
        }
    }
    if (keys['D'] || keys[VK_RIGHT])
    {
        // Rotate right (fixed to be correct direction)
        rotateY = -effectiveRotationSpeed * deltaTime;

        // Add slight sideways friction when turning at speed
        if (fabs(playerTank.speed) > 2.0f)
        {
            playerTank.speed *= (1.0f - 0.2f * deltaTime);
        }
    }

    // Apply rotation with inertia effect
    static float rotationInertia = 0.0f;
    rotationInertia = rotationInertia * 0.9f + rotateY * 0.1f;
    playerTank.bodyRotation += rotationInertia;

    // Normalize rotation to 0-360 degrees
    while (playerTank.bodyRotation >= 360.0f)
        playerTank.bodyRotation -= 360.0f;
    while (playerTank.bodyRotation < 0.0f)
        playerTank.bodyRotation += 360.0f;

    // Calculate movement direction based on tank rotation
    float radians = playerTank.bodyRotation * 3.14159f / 180.0f;
    moveX = playerTank.speed * sin(radians) * deltaTime;
    moveZ = playerTank.speed * cos(radians) * deltaTime;

    // Add engine sound effect based on speed (not implemented)
    // float engineVolume = fabs(playerTank.speed) / playerTank.maxSpeed;
    // float enginePitch = 0.8f + engineVolume * 0.4f;

    // Calculate new position
    float newX = playerTank.x + moveX;
    float newZ = playerTank.z + moveZ;

    // Check world boundaries (keep tank within terrain)
    float worldBoundary = terrain.width / 2.0f - 5.0f; // 5 unit buffer from edge

    if (newX > worldBoundary)
        newX = worldBoundary;
    if (newX < -worldBoundary)
        newX = -worldBoundary;
    if (newZ > worldBoundary)
        newZ = worldBoundary;
    if (newZ < -worldBoundary)
        newZ = -worldBoundary;

    // Check collision with terrain objects
    bool collision = false;
    float tankRadius = 2.0f; // Tank collision radius

    for (const auto &obj : terrain.objects)
    {
        // Skip small bushes (can drive over them)
        if (obj.type == 2 && obj.scale < 0.5f)
            continue;

        // Calculate object radius based on type and scale
        float objRadius = 0.0f;
        switch (obj.type)
        {
        case 0: // Tree
            objRadius = 0.8f * obj.scale;
            break;
        case 1: // Rock
            objRadius = 0.7f * obj.scale;
            break;
        case 2: // Bush
            objRadius = 0.5f * obj.scale;
            break;
        }

        // Calculate distance between tank and object
        float dx = newX - obj.x;
        float dz = newZ - obj.z;
        float distSquared = dx * dx + dz * dz;

        // Check if collision occurs
        float minDist = tankRadius + objRadius;
        if (distSquared < minDist * minDist)
        {
            collision = true;

            // Calculate collision response (push tank away)
            float dist = sqrt(distSquared);
            if (dist > 0.0f)
            {
                float pushX = dx / dist;
                float pushZ = dz / dist;
                float pushAmount = minDist - dist;

                // Apply push vector
                newX += pushX * pushAmount * 1.1f; // Add a bit extra to prevent sticking
                newZ += pushZ * pushAmount * 1.1f;

                // Reduce speed on collision
                playerTank.speed *= 0.8f;
            }
        }
    }

    // Check collision with remote tank (if connected)
    if (isNetworked && networkManager.IsConnected())
    {
        // Calculate distance between tanks
        float dx = newX - remoteTank.x;
        float dz = newZ - remoteTank.z;
        float distSquared = dx * dx + dz * dz;

        // Check if collision occurs
        float minDist = tankRadius * 2; // Both tanks have the same radius
        if (distSquared < minDist * minDist)
        {
            collision = true;

            // Calculate collision response (push tanks away from each other)
            float dist = sqrt(distSquared);
            if (dist > 0.0f)
            {
                float pushX = dx / dist;
                float pushZ = dz / dist;
                float pushAmount = minDist - dist;

                // Apply push vector to player tank
                newX += pushX * pushAmount * 0.55f; // Split the push between both tanks
                newZ += pushZ * pushAmount * 0.55f;

                // Reduce speed on collision
                playerTank.speed *= 0.8f;

                // Send updated position immediately to avoid desync
                if (pushAmount > 0.1f) // Only send if significant push
                {
                    NetworkTankState state;
                    state.x = newX;
                    state.y = playerTank.y;
                    state.z = newZ;
                    state.bodyRotation = playerTank.bodyRotation;
                    state.turretRotation = playerTank.turretRotation;
                    state.health = playerTank.health;

                    networkManager.SendTankState(state);
                }
            }
        }
    }

    // Apply movement with boundary and collision check
    playerTank.x = newX;
    playerTank.z = newZ;

    // Update tank's Y position based on terrain height
    playerTank.y = terrain.getHeight(playerTank.x, playerTank.z) + 0.5f;

    // Update turret rotation based on mouse position
    float centerX = currentWidth / 2.0f;
    float centerY = currentHeight / 2.0f;
    // Fix the inverted controls by negating dx
    float dx = -(mouseX - centerX); // Negate dx to fix inverted controls
    float dy = centerY - mouseY;
    float targetTurretRotation = atan2(dx, dy) * 180.0f / 3.14159f - playerTank.bodyRotation;

    // Normalize target rotation to -180 to 180 degrees
    while (targetTurretRotation > 180.0f)
        targetTurretRotation -= 360.0f;
    while (targetTurretRotation < -180.0f)
        targetTurretRotation += 360.0f;

    // Smoothly rotate turret towards target
    float turretRotDiff = targetTurretRotation - playerTank.turretRotation;

    // Normalize difference to -180 to 180 degrees
    while (turretRotDiff > 180.0f)
        turretRotDiff -= 360.0f;
    while (turretRotDiff < -180.0f)
        turretRotDiff += 360.0f;

    // Apply rotation with speed limit
    float maxTurretRotation = playerTank.turretRotationSpeed * deltaTime;
    if (turretRotDiff > maxTurretRotation)
        playerTank.turretRotation += maxTurretRotation;
    else if (turretRotDiff < -maxTurretRotation)
        playerTank.turretRotation -= maxTurretRotation;
    else
        playerTank.turretRotation = targetTurretRotation;

    // Normalize turret rotation
    while (playerTank.turretRotation >= 360.0f)
        playerTank.turretRotation -= 360.0f;
    while (playerTank.turretRotation < 0.0f)
        playerTank.turretRotation += 360.0f;

    // Update reload timer
    if (!playerTank.canFire)
    {
        playerTank.currentReloadTime += deltaTime;
        if (playerTank.currentReloadTime >= playerTank.reloadTime)
        {
            playerTank.canFire = true;
            playerTank.currentReloadTime = 0.0f;
        }
    }

    // Handle firing
    if ((keys[VK_SPACE] || mouseLeftDown) && playerTank.canFire)
    {
        FireBullet();
        playerTank.canFire = false;
        playerTank.currentReloadTime = 0.0f;
    }

    // Update networking
    if (isNetworked && networkManager.IsConnected())
    {
        UpdateNetworking();
    }

    // Update bullets
    for (size_t i = 0; i < bullets.size(); i++)
    {
        if (bullets[i].active)
        {
            // Store previous position for trail effect
            float prevX = bullets[i].x;
            float prevY = bullets[i].y;
            float prevZ = bullets[i].z;

            // Move bullet with slight gravity effect
            bullets[i].dirY -= 0.05f * deltaTime; // Slight gravity effect

            // Normalize direction vector again after applying gravity
            float dirLength = sqrt(bullets[i].dirX * bullets[i].dirX +
                                   bullets[i].dirY * bullets[i].dirY +
                                   bullets[i].dirZ * bullets[i].dirZ);
            bullets[i].dirX /= dirLength;
            bullets[i].dirY /= dirLength;
            bullets[i].dirZ /= dirLength;

            // Apply movement
            bullets[i].x += bullets[i].dirX * bullets[i].speed * deltaTime;
            bullets[i].y += bullets[i].dirY * bullets[i].speed * deltaTime;
            bullets[i].z += bullets[i].dirZ * bullets[i].speed * deltaTime;

            // Update lifetime
            bullets[i].lifetime -= deltaTime;

            // Create small trail particles occasionally
            if (rand() % 3 == 0)
            {
                Particle trailParticle;

                // Position between current and previous position
                float trailPos = (rand() % 100) / 100.0f; // 0.0 to 1.0
                trailParticle.x = prevX + (bullets[i].x - prevX) * trailPos;
                trailParticle.y = prevY + (bullets[i].y - prevY) * trailPos;
                trailParticle.z = prevZ + (bullets[i].z - prevZ) * trailPos;

                // Small random movement
                trailParticle.dirX = ((rand() % 100) / 100.0f - 0.5f) * 0.5f;
                trailParticle.dirY = ((rand() % 100) / 100.0f) * 0.5f; // Upward bias
                trailParticle.dirZ = ((rand() % 100) / 100.0f - 0.5f) * 0.5f;

                // Set particle properties
                trailParticle.speed = 0.5f;
                trailParticle.size = (rand() % 100) / 100.0f * 0.1f + 0.05f;
                trailParticle.lifetime = (rand() % 100) / 100.0f * 0.3f + 0.1f;
                trailParticle.maxLifetime = trailParticle.lifetime;

                // Smoke trail color
                trailParticle.r = 0.6f;
                trailParticle.g = 0.6f;
                trailParticle.b = 0.6f;
                trailParticle.a = 0.4f;

                trailParticle.active = true;

                // Add particle to list
                particles.push_back(trailParticle);
            }

            // Check for terrain collision
            float terrainHeight = terrain.getHeight(bullets[i].x, bullets[i].z);
            if (bullets[i].y <= terrainHeight)
            {
                // Create explosion at impact point
                CreateExplosion(bullets[i].x, terrainHeight, bullets[i].z, 80);

                bullets[i].active = false;
                continue; // Skip further checks
            }

            // Check for collision with terrain objects
            for (const auto &obj : terrain.objects)
            {
                // Skip small bushes
                if (obj.type == 2 && obj.scale < 0.5f)
                    continue;

                // Calculate object radius based on type and scale
                float objRadius = 0.0f;
                switch (obj.type)
                {
                case 0: // Tree
                    objRadius = 0.8f * obj.scale;
                    break;
                case 1: // Rock
                    objRadius = 0.7f * obj.scale;
                    break;
                case 2: // Bush
                    objRadius = 0.5f * obj.scale;
                    break;
                }

                // Calculate distance between bullet and object
                float dx = bullets[i].x - obj.x;
                float dy = bullets[i].y - obj.y;
                float dz = bullets[i].z - obj.z;
                float distSquared = dx * dx + dy * dy + dz * dz;

                // Check if collision occurs
                float bulletRadius = 0.1f;
                float minDist = bulletRadius + objRadius;
                if (distSquared < minDist * minDist)
                {
                    // Create explosion at impact point
                    CreateExplosion(bullets[i].x, bullets[i].y, bullets[i].z, 60);
                    bullets[i].active = false;
                    break; // Exit the loop
                }
            }

            // Check for collision with player tank
            float dx = bullets[i].x - playerTank.x;
            float dy = bullets[i].y - (playerTank.y + 0.5f); // Tank center
            float dz = bullets[i].z - playerTank.z;
            float distSquared = dx * dx + dy * dy + dz * dz;

            float bulletRadius = 0.1f;
            float tankRadius = 1.5f;

            // Check if bullet hit player tank
            if (distSquared < (bulletRadius + tankRadius) * (bulletRadius + tankRadius))
            {
                // Create explosion at impact point
                CreateExplosion(bullets[i].x, bullets[i].y, bullets[i].z, 100);

                // Only apply damage if this is a remote bullet (to prevent self-damage)
                // We identify remote bullets by checking if they were not fired by the player
                bool isRemoteBullet = false;

                // If we're in a networked game, check if this is a remote bullet
                if (isNetworked && networkManager.IsConnected())
                {
                    // Calculate the distance from the bullet to the remote tank's position
                    float remoteDx = bullets[i].x - remoteTank.x;
                    float remoteDy = bullets[i].y - (remoteTank.y + 0.5f);
                    float remoteDz = bullets[i].z - remoteTank.z;
                    float remoteDistSquared = remoteDx * remoteDx + remoteDy * remoteDy + remoteDz * remoteDz;

                    // If the bullet is closer to the remote tank than to the player tank,
                    // it's likely a player bullet (not a remote bullet)
                    isRemoteBullet = (remoteDistSquared > distSquared);
                }

                if (isRemoteBullet)
                {
                    int damage = 20;
                    playerTank.health -= damage;

                    // Ensure health doesn't go below 0
                    if (playerTank.health < 0)
                        playerTank.health = 0;

                    // Send tank state update immediately to sync health
                    if (isNetworked && networkManager.IsConnected())
                    {
                        // Send tank state with updated health
                        NetworkTankState state;
                        state.x = playerTank.x;
                        state.y = playerTank.y;
                        state.z = playerTank.z;
                        state.bodyRotation = playerTank.bodyRotation;
                        state.turretRotation = playerTank.turretRotation;
                        state.health = playerTank.health;
                        networkManager.SendTankState(state);

                        // Also send a bullet hit notification
                        NetworkBulletHit hit;
                        hit.damage = damage;
                        hit.isPlayerHit = true; // Player was hit
                        networkManager.SendBulletHit(hit);
                    }

                    // Check if player tank is destroyed
                    if (playerTank.health <= 0)
                    {
                        // Player lost - update local game state
                        gameOver = true;
                        playerWon = false;
                        showGameOverScreen = true;
                        showRetryButton = true;

                        // Send game over state to remote player
                        if (isNetworked && networkManager.IsConnected())
                        {
                            // Send game over state
                            NetworkGameState gameState;
                            gameState.gameOver = true;
                            gameState.playerWon = false; // Player lost
                            networkManager.SendGameState(gameState);
                        }
                    }
                }

                bullets[i].active = false;
                continue;
            }

            // Check for collision with remote tank (if in networked game)
            if (isNetworked && networkManager.IsConnected())
            {
                dx = bullets[i].x - remoteTank.x;
                dy = bullets[i].y - (remoteTank.y + 0.5f); // Tank center
                dz = bullets[i].z - remoteTank.z;
                distSquared = dx * dx + dy * dy + dz * dz;

                if (distSquared < (bulletRadius + tankRadius) * (bulletRadius + tankRadius))
                {
                    // Create explosion at impact point
                    CreateExplosion(bullets[i].x, bullets[i].y, bullets[i].z, 100);

                    // Only apply damage if this is a player bullet (to prevent self-damage)
                    // We identify player bullets by checking if they were not fired by the remote player
                    bool isPlayerBullet = false;

                    // Calculate the distance from the bullet to the player tank's position
                    float playerDx = bullets[i].x - playerTank.x;
                    float playerDy = bullets[i].y - (playerTank.y + 0.5f);
                    float playerDz = bullets[i].z - playerTank.z;
                    float playerDistSquared = playerDx * playerDx + playerDy * playerDy + playerDz * playerDz;

                    // If the bullet is closer to the player tank than to the remote tank,
                    // it's likely a player bullet
                    isPlayerBullet = (playerDistSquared < distSquared);

                    if (isPlayerBullet)
                    {
                        // Apply damage to remote tank (1/3 of max health)
                        int damage = 20;
                        remoteTank.health -= damage;

                        // Ensure health doesn't go below 0
                        if (remoteTank.health < 0)
                            remoteTank.health = 0;

                        // Send bullet hit notification
                        NetworkBulletHit hit;
                        hit.damage = damage;
                        hit.isPlayerHit = false; // Remote player was hit
                        networkManager.SendBulletHit(hit);

                        // Check if remote tank is destroyed
                        if (remoteTank.health <= 0)
                        {
                            // Player won - update local game state
                            gameOver = true;
                            playerWon = true;
                            showGameOverScreen = true;
                            showRetryButton = true;

                            // Send game over state to remote player
                            NetworkGameState gameState;
                            gameState.gameOver = true;
                            gameState.playerWon = true; // Player won
                            networkManager.SendGameState(gameState);
                        }
                    }

                    bullets[i].active = false;
                    continue;
                }
            }

            // Remove bullets that have expired
            if (bullets[i].lifetime <= 0.0f)
            {
                bullets[i].active = false;
            }
        }
    }

    // Remove inactive bullets
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
                       [](const Bullet &b)
                       { return !b.active; }),
        bullets.end());

    // Update particles
    UpdateParticles();

    // Update camera
    UpdateCamera();
}

// Update particles
void UpdateParticles()
{
    for (size_t i = 0; i < particles.size(); i++)
    {
        if (particles[i].active)
        {
            // Move particle
            particles[i].x += particles[i].dirX * particles[i].speed * deltaTime;
            particles[i].y += particles[i].dirY * particles[i].speed * deltaTime;
            particles[i].z += particles[i].dirZ * particles[i].speed * deltaTime;

            // Apply gravity
            particles[i].dirY -= 9.8f * deltaTime;

            // Update lifetime
            particles[i].lifetime -= deltaTime;

            // Update alpha based on lifetime
            particles[i].a = particles[i].lifetime / particles[i].maxLifetime;

            // Check for terrain collision
            float terrainHeight = terrain.getHeight(particles[i].x, particles[i].z);
            if (particles[i].y <= terrainHeight)
            {
                particles[i].y = terrainHeight;
                particles[i].dirY *= -0.5f; // Bounce with energy loss
                particles[i].speed *= 0.8f; // Slow down on bounce
            }

            // Remove particles that have expired
            if (particles[i].lifetime <= 0.0f)
            {
                particles[i].active = false;
            }
        }
    }

    // Remove inactive particles
    particles.erase(
        std::remove_if(particles.begin(), particles.end(),
                       [](const Particle &p)
                       { return !p.active; }),
        particles.end());
}

// Update camera position
void UpdateCamera()
{
    // Update camera target to follow tank
    camera.targetX = playerTank.x;
    camera.targetY = playerTank.y + 1.0f; // Slightly above tank
    camera.targetZ = playerTank.z;

    // Calculate camera angle based on tank rotation and mouse input
    // This allows the player to look around while still following the tank
    static float cameraAngleOffset = 0.0f;

    // Allow camera rotation with right mouse button
    if (mouseRightDown)
    {
        // Calculate mouse movement from center
        float mouseDeltaX = (mouseX - currentWidth / 2) * 0.1f;

        // Apply to camera angle offset
        cameraAngleOffset = mouseDeltaX;
    }
    else
    {
        // Gradually return to center when not holding right mouse
        cameraAngleOffset *= 0.95f;
    }

    // Apply the offset to the camera angle
    float cameraAngle = playerTank.bodyRotation + cameraAngleOffset;

    // Convert to radians
    float radians = cameraAngle * 3.14159f / 180.0f;

    // Calculate desired camera position with offset
    float desiredX = playerTank.x - camera.distance * sin(radians);
    float desiredY = playerTank.y + camera.height;
    float desiredZ = playerTank.z - camera.distance * cos(radians);

    // Check for collision with terrain
    float terrainHeight = terrain.getHeight(desiredX, desiredZ) + 1.0f; // Keep camera above terrain
    if (desiredY < terrainHeight)
    {
        desiredY = terrainHeight;
    }

    // Check for collision with objects (simplified)
    for (const auto &obj : terrain.objects)
    {
        if (obj.type == 0)
        { // Only check trees
            float dx = desiredX - obj.x;
            float dz = desiredZ - obj.z;
            float distSquared = dx * dx + dz * dz;

            // If camera would be inside a tree, adjust it
            if (distSquared < 2.0f * 2.0f && desiredY < obj.y + 5.0f)
            {
                // Push camera away from tree
                float dist = sqrt(distSquared);
                if (dist > 0.1f)
                {
                    float pushX = dx / dist;
                    float pushZ = dz / dist;
                    float pushAmount = 2.0f - dist;

                    desiredX += pushX * pushAmount;
                    desiredZ += pushZ * pushAmount;
                }
            }
        }
    }

    // Apply camera shake when firing or when hit
    static float cameraShake = 0.0f;

    // Decrease shake over time
    cameraShake *= 0.9f;

    // Add random shake
    if (cameraShake > 0.01f)
    {
        desiredX += ((rand() % 100) / 100.0f - 0.5f) * cameraShake;
        desiredY += ((rand() % 100) / 100.0f - 0.5f) * cameraShake;
        desiredZ += ((rand() % 100) / 100.0f - 0.5f) * cameraShake;
    }

    // Smoothly interpolate camera position with variable smoothing
    // Use faster smoothing when tank is moving to keep up
    float speedFactor = (fabs(playerTank.speed) / 5.0f);
    if (speedFactor > 1.0f)
        speedFactor = 1.0f; // Manual min function
    float dynamicSmoothFactor = camera.smoothFactor * (1.0f + speedFactor);

    camera.currentX += (desiredX - camera.currentX) * dynamicSmoothFactor * deltaTime;
    camera.currentY += (desiredY - camera.currentY) * dynamicSmoothFactor * deltaTime;
    camera.currentZ += (desiredZ - camera.currentZ) * dynamicSmoothFactor * deltaTime;
}

// Create a muzzle flash effect
void CreateMuzzleFlash(float x, float y, float z, float angle)
{
    // Create bright flash particles at the muzzle
    for (int i = 0; i < 15; i++)
    {
        Particle newParticle;

        // Position particle at muzzle
        newParticle.x = x;
        newParticle.y = y;
        newParticle.z = z;

        // Random direction in a cone from the muzzle - now pointing in the direction of the turret
        float spreadAngle = 30.0f; // Degrees
        float randomAngle = angle + ((rand() % 100) / 100.0f - 0.5f) * spreadAngle;
        float randomElevation = ((rand() % 100) / 100.0f - 0.5f) * spreadAngle;

        float speed = (rand() % 100) / 100.0f * 5.0f + 2.0f;

        // Convert to radians
        float radRandomAngle = randomAngle * 3.14159f / 180.0f;
        float radRandomElevation = randomElevation * 3.14159f / 180.0f;

        // Particles go in the direction of the turret, parallel to the ground
        // This matches the bullet's forward direction
        newParticle.dirX = sin(radRandomAngle) * cos(radRandomElevation) * speed;
        newParticle.dirY = sin(radRandomElevation) * speed * 0.1f; // Very slight vertical variation
        newParticle.dirZ = cos(radRandomAngle) * cos(radRandomElevation) * speed;

        // Set particle properties
        newParticle.speed = speed;
        newParticle.size = (rand() % 100) / 100.0f * 0.2f + 0.05f;
        newParticle.lifetime = (rand() % 100) / 100.0f * 0.2f + 0.05f; // Very short lifetime
        newParticle.maxLifetime = newParticle.lifetime;

        // Bright yellow/white for muzzle flash
        newParticle.r = 1.0f;
        newParticle.g = 0.9f;
        newParticle.b = 0.5f;
        newParticle.a = 1.0f;

        newParticle.active = true;

        // Add particle to list
        particles.push_back(newParticle);
    }

    // Add some smoke particles
    for (int i = 0; i < 10; i++)
    {
        Particle newParticle;

        // Position particle at muzzle with slight offset
        newParticle.x = x + ((rand() % 100) / 100.0f - 0.5f) * 0.1f;
        newParticle.y = y + ((rand() % 100) / 100.0f - 0.5f) * 0.1f;
        newParticle.z = z + ((rand() % 100) / 100.0f - 0.5f) * 0.1f;

        // Random direction in a cone from the muzzle - now pointing in the direction of the turret
        float spreadAngle = 20.0f; // Degrees
        float randomAngle = angle + ((rand() % 100) / 100.0f - 0.5f) * spreadAngle;
        float randomElevation = ((rand() % 100) / 100.0f - 0.3f) * spreadAngle; // Slight upward bias

        float speed = (rand() % 100) / 100.0f * 2.0f + 1.0f;

        // Convert to radians
        float radRandomAngle = randomAngle * 3.14159f / 180.0f;
        float radRandomElevation = randomElevation * 3.14159f / 180.0f;

        // Smoke particles go in the direction of the turret with upward drift
        newParticle.dirX = sin(radRandomAngle) * cos(radRandomElevation) * speed;
        newParticle.dirY = sin(radRandomElevation) * speed + 0.2f; // Upward drift
        newParticle.dirZ = cos(radRandomAngle) * cos(radRandomElevation) * speed;

        // Set particle properties
        newParticle.speed = speed;
        newParticle.size = (rand() % 100) / 100.0f * 0.3f + 0.1f;
        newParticle.lifetime = (rand() % 100) / 100.0f * 0.8f + 0.4f; // Longer than flash
        newParticle.maxLifetime = newParticle.lifetime;

        // Gray smoke
        newParticle.r = 0.5f;
        newParticle.g = 0.5f;
        newParticle.b = 0.5f;
        newParticle.a = 0.7f;

        newParticle.active = true;

        // Add particle to list
        particles.push_back(newParticle);
    }
}

// Fire a bullet from the tank
void FireBullet()
{
    Bullet newBullet;

    // COMPLETELY REVISED BULLET SPAWNING LOGIC
    // We'll use a more direct approach to calculate the exact barrel tip position

    // Step 1: Define the barrel tip position in local space
    // The barrel is pointing straight down from the mantlet
    float barrelTipLocalX = 0.0f;
    float barrelTipLocalY = -5.5f; // Total length of barrel pointing downward
    float barrelTipLocalZ = 0.0f;

    // Step 2: Calculate the world position of the turret center
    float turretWorldX = playerTank.x;
    float turretWorldY = playerTank.y + 0.7f; // Turret height from tank base
    float turretWorldZ = playerTank.z;

    // Step 3: Calculate the turret rotation in world space
    float turretRadians = (playerTank.bodyRotation + playerTank.turretRotation) * 3.14159f / 180.0f;

    // Step 4: Calculate the mantlet position in world space
    float mantletWorldX = turretWorldX + 0.7f * sin(turretRadians); // 0.7f is distance to mantlet
    float mantletWorldY = turretWorldY + 0.2f;                      // 0.2f is mantlet height from turret center
    float mantletWorldZ = turretWorldZ + 0.7f * cos(turretRadians);

    // Step 5: Calculate the barrel tip position in world space
    // Since the barrel points straight down, we just subtract the barrel length from the mantlet Y
    float bulletX = mantletWorldX;
    float bulletY = mantletWorldY + barrelTipLocalY; // Add because barrelTipLocalY is negative
    float bulletZ = mantletWorldZ;

    // Step 6: Instead of spawning the bullet at the exact barrel tip (which is pointing down),
    // we'll spawn it at a position that makes sense for a forward-firing tank
    // We'll use the mantlet position but offset it forward and slightly downward

    // Reset the bullet position to the mantlet
    bulletX = mantletWorldX;
    bulletY = mantletWorldY - 0.2f; // Slightly below the mantlet
    bulletZ = mantletWorldZ;

    // Add a forward offset in the direction the turret is facing
    float forwardOffsetDistance = 1.5f; // Large enough to clear the tank completely
    bulletX += forwardOffsetDistance * sin(turretRadians);
    bulletZ += forwardOffsetDistance * cos(turretRadians);

    // Set final bullet position
    newBullet.x = bulletX;
    newBullet.y = bulletY;
    newBullet.z = bulletZ;

    // Set bullet direction parallel to the ground (XZ-plane) in the direction the turret is facing
    // This simulates a real tank where shells travel horizontally regardless of barrel tilt

    // Direction vector components for horizontal movement (parallel to ground)
    // Using the turret's forward direction for bullet movement
    newBullet.dirX = sin(turretRadians);
    newBullet.dirY = 0.0f; // Perfectly horizontal (parallel to ground)
    newBullet.dirZ = cos(turretRadians);

    // Reduce bullet speed to make it more visible and trackable
    newBullet.speed = 30.0f; // Slower speed for better visual tracking

    // Normalize direction vector
    float length = sqrt(newBullet.dirX * newBullet.dirX +
                        newBullet.dirY * newBullet.dirY +
                        newBullet.dirZ * newBullet.dirZ);
    newBullet.dirX /= length;
    newBullet.dirY /= length;
    newBullet.dirZ /= length;

    // Set bullet properties - these are now set earlier for clarity
    // newBullet.speed is already set to 60.0f above
    newBullet.lifetime = 20.0f; // Even longer lifetime to travel further and be more visible
    newBullet.active = true;
    newBullet.damage = 30; // Increased damage

    // Set new bullet properties - store the turret angle for proper orientation
    newBullet.rotation = turretRadians * 180.0f / 3.14159f; // Store rotation in degrees
    newBullet.scale = 0.25f;                                // Reduced size for better proportions

    // Set bullet type (AP - armor piercing)
    newBullet.type = 0; // Always use AP shells for consistency

    // Add bullet to list
    bullets.push_back(newBullet);

    // Create muzzle flash effect at the bullet spawn position
    // This ensures the muzzle flash appears at the correct position
    CreateMuzzleFlash(newBullet.x, newBullet.y, newBullet.z, turretRadians);

    // Send bullet to remote player if connected
    if (isNetworked && networkManager.IsConnected())
    {
        SendBulletFired(newBullet);
    }

    // Add recoil effect to tank
    playerTank.speed -= 1.0f; // Stronger recoil for more realism
}

// Create an explosion effect
void CreateExplosion(float x, float y, float z, int particleCount)
{
    // Create initial blast particles (bright flash)
    for (int i = 0; i < particleCount / 4; i++)
    {
        Particle newParticle;

        // Position particle at explosion center with slight randomness
        newParticle.x = x + ((rand() % 100) / 100.0f - 0.5f) * 0.2f;
        newParticle.y = y + ((rand() % 100) / 100.0f - 0.5f) * 0.2f;
        newParticle.z = z + ((rand() % 100) / 100.0f - 0.5f) * 0.2f;

        // Random direction in all directions
        float angle = (rand() % 360) * 3.14159f / 180.0f;
        float elevation = (rand() % 180) * 3.14159f / 180.0f;
        float speed = (rand() % 100) / 100.0f * 15.0f + 10.0f; // Faster initial blast

        newParticle.dirX = sin(angle) * sin(elevation) * speed;
        newParticle.dirY = cos(elevation) * speed;
        newParticle.dirZ = cos(angle) * sin(elevation) * speed;

        // Set particle properties
        newParticle.speed = speed;
        newParticle.size = (rand() % 100) / 100.0f * 0.3f + 0.2f;
        newParticle.lifetime = (rand() % 100) / 100.0f * 0.3f + 0.1f; // Short lifetime for flash
        newParticle.maxLifetime = newParticle.lifetime;

        // Set particle color (bright yellow/white for initial flash)
        newParticle.r = 1.0f;
        newParticle.g = 0.9f;
        newParticle.b = 0.5f;
        newParticle.a = 1.0f;

        newParticle.active = true;

        // Add particle to list
        particles.push_back(newParticle);
    }

    // Create fire particles
    for (int i = 0; i < particleCount / 2; i++)
    {
        Particle newParticle;

        // Position particle at explosion center with randomness
        newParticle.x = x + ((rand() % 100) / 100.0f - 0.5f) * 0.5f;
        newParticle.y = y + ((rand() % 100) / 100.0f - 0.5f) * 0.5f;
        newParticle.z = z + ((rand() % 100) / 100.0f - 0.5f) * 0.5f;

        // Random direction with bias upward
        float angle = (rand() % 360) * 3.14159f / 180.0f;
        float elevation = ((rand() % 100) / 100.0f * 90.0f); // 0-90 degrees (upward bias)
        float speed = (rand() % 100) / 100.0f * 8.0f + 3.0f;

        newParticle.dirX = sin(angle) * sin(elevation) * speed;
        newParticle.dirY = cos(elevation) * speed;
        newParticle.dirZ = cos(angle) * sin(elevation) * speed;

        // Set particle properties
        newParticle.speed = speed;
        newParticle.size = (rand() % 100) / 100.0f * 0.6f + 0.2f;
        newParticle.lifetime = (rand() % 100) / 100.0f * 1.0f + 0.5f;
        newParticle.maxLifetime = newParticle.lifetime;

        // Set particle color (orange/red for fire)
        float redness = (rand() % 30) / 100.0f + 0.7f; // 0.7-1.0
        newParticle.r = redness;
        newParticle.g = (rand() % 60) / 100.0f + 0.2f; // 0.2-0.8
        newParticle.b = (rand() % 20) / 100.0f;        // 0.0-0.2
        newParticle.a = 1.0f;

        newParticle.active = true;

        // Add particle to list
        particles.push_back(newParticle);
    }

    // Create smoke particles
    for (int i = 0; i < particleCount / 2; i++)
    {
        Particle newParticle;

        // Position particle at explosion center with more randomness
        newParticle.x = x + ((rand() % 100) / 100.0f - 0.5f) * 1.0f;
        newParticle.y = y + ((rand() % 100) / 100.0f) * 0.5f; // Mostly above
        newParticle.z = z + ((rand() % 100) / 100.0f - 0.5f) * 1.0f;

        // Random direction with strong upward bias
        float angle = (rand() % 360) * 3.14159f / 180.0f;
        float elevation = ((rand() % 100) / 100.0f * 45.0f); // 0-45 degrees (strong upward)
        float speed = (rand() % 100) / 100.0f * 3.0f + 1.0f; // Slower for smoke

        newParticle.dirX = sin(angle) * sin(elevation) * speed;
        newParticle.dirY = cos(elevation) * speed;
        newParticle.dirZ = cos(angle) * sin(elevation) * speed;

        // Set particle properties
        newParticle.speed = speed;
        newParticle.size = (rand() % 100) / 100.0f * 1.0f + 0.5f;     // Larger for smoke
        newParticle.lifetime = (rand() % 100) / 100.0f * 2.5f + 1.5f; // Longer lifetime
        newParticle.maxLifetime = newParticle.lifetime;

        // Set particle color (dark gray for smoke)
        float darkness = (rand() % 40) / 100.0f + 0.2f; // 0.2-0.6
        newParticle.r = darkness;
        newParticle.g = darkness;
        newParticle.b = darkness;
        newParticle.a = 0.7f; // Semi-transparent

        newParticle.active = true;

        // Add particle to list
        particles.push_back(newParticle);
    }

    // Create debris particles
    for (int i = 0; i < particleCount / 4; i++)
    {
        Particle newParticle;

        // Position particle at explosion center
        newParticle.x = x;
        newParticle.y = y;
        newParticle.z = z;

        // Random direction in all directions but with more horizontal spread
        float angle = (rand() % 360) * 3.14159f / 180.0f;
        float elevation = ((rand() % 140) - 70) * 3.14159f / 180.0f; // -70 to 70 degrees
        float speed = (rand() % 100) / 100.0f * 12.0f + 5.0f;

        newParticle.dirX = sin(angle) * cos(elevation) * speed;
        newParticle.dirY = sin(elevation) * speed;
        newParticle.dirZ = cos(angle) * cos(elevation) * speed;

        // Set particle properties
        newParticle.speed = speed;
        newParticle.size = (rand() % 100) / 100.0f * 0.3f + 0.1f; // Smaller for debris
        newParticle.lifetime = (rand() % 100) / 100.0f * 2.0f + 1.0f;
        newParticle.maxLifetime = newParticle.lifetime;

        // Set particle color (brown/black for debris)
        newParticle.r = (rand() % 30) / 100.0f + 0.1f;  // 0.1-0.4
        newParticle.g = (rand() % 20) / 100.0f + 0.05f; // 0.05-0.25
        newParticle.b = (rand() % 10) / 100.0f;         // 0.0-0.1
        newParticle.a = 1.0f;

        newParticle.active = true;

        // Add particle to list
        particles.push_back(newParticle);
    }

    // Create shockwave effect (ring of particles expanding outward)
    int shockwaveParticles = 36; // One every 10 degrees
    for (int i = 0; i < shockwaveParticles; i++)
    {
        Particle newParticle;

        // Position particle at explosion center
        newParticle.x = x;
        newParticle.y = y + 0.1f; // Slightly above ground
        newParticle.z = z;

        // Direction in a circle around the explosion
        float angle = (i * 360.0f / shockwaveParticles) * 3.14159f / 180.0f;
        float speed = 8.0f; // Fast expanding ring

        newParticle.dirX = sin(angle) * speed;
        newParticle.dirY = 0.0f; // Flat along the ground
        newParticle.dirZ = cos(angle) * speed;

        // Set particle properties
        newParticle.speed = speed;
        newParticle.size = 0.2f;
        newParticle.lifetime = 0.5f; // Short lifetime
        newParticle.maxLifetime = newParticle.lifetime;

        // Set particle color (white/yellow for shockwave)
        newParticle.r = 1.0f;
        newParticle.g = 0.8f;
        newParticle.b = 0.3f;
        newParticle.a = 0.8f;

        newParticle.active = true;

        // Add particle to list
        particles.push_back(newParticle);
    }
}

// Render the game
void RenderGame()
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the camera (third-person view)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        camera.currentX, camera.currentY, camera.currentZ, // Eye position
        camera.targetX, camera.targetY, camera.targetZ,    // Look-at position
        0.0f, 1.0f, 0.0f                                   // Up vector
    );

    // Draw the terrain
    DrawTerrain();

    // Draw the tank
    DrawTank(playerTank);

    // Draw remote tank if connected
    if (isNetworked && networkManager.IsConnected())
    {
        DrawTank(remoteTank);
    }

    // Draw bullets
    DrawBullets();

    // Draw particles
    DrawParticles();

    // Draw HUD
    DrawHUD();

    // Draw network menu if active
    if (showNetworkMenu)
    {
        DrawNetworkMenu();
    }

    // Draw game over screen if active
    if (showGameOverScreen)
    {
        DrawGameOverScreen();
    }

    // Draw input field if active
    if (inputActive)
    {
        DrawText(10, currentHeight - 30, "> " + inputBuffer, 1.0f, 1.0f, 1.0f);
    }

    // Draw network status
    if (isNetworked)
    {
        std::string status = networkManager.IsConnected() ? "Connected to " + networkManager.GetPeerAddress() : "Not connected";
        DrawText(10, currentHeight - 50, "Network: " + status, 0.0f, 1.0f, 0.0f);

        // Draw chat messages
        int y = currentHeight - 70;
        for (const auto &msg : chatMessages)
        {
            DrawText(10, y, msg, 1.0f, 1.0f, 0.0f);
            y -= 20;
        }
    }
}

// Draw modern tank hull
void DrawTankHull(const Tank &tank)
{
    // Set material properties for tank body
    GLfloat matAmbient[] = {0.25f, 0.28f, 0.15f, 1.0f};
    GLfloat matDiffuse[] = {0.3f, 0.35f, 0.2f, 1.0f};
    GLfloat matSpecular[] = {0.1f, 0.1f, 0.1f, 1.0f};
    GLfloat matShininess[] = {5.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

    // Main hull body - more angular and realistic
    glPushMatrix();
    glScalef(1.8f, 0.5f, 2.5f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Upper hull - sloped for realism
    glPushMatrix();
    glTranslatef(0.0f, 0.3f, 0.0f);

    // Draw upper hull as a custom shape with angled sides
    glBegin(GL_QUADS);

    // Top face
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-0.8f, 0.2f, -1.1f);
    glVertex3f(0.8f, 0.2f, -1.1f);
    glVertex3f(0.8f, 0.2f, 1.1f);
    glVertex3f(-0.8f, 0.2f, 1.1f);

    // Front face (sloped)
    glNormal3f(0.0f, 0.7071f, 0.7071f);
    glVertex3f(-0.8f, 0.2f, 1.1f);
    glVertex3f(0.8f, 0.2f, 1.1f);
    glVertex3f(0.9f, -0.2f, 1.3f);
    glVertex3f(-0.9f, -0.2f, 1.3f);

    // Rear face (sloped)
    glNormal3f(0.0f, 0.7071f, -0.7071f);
    glVertex3f(0.8f, 0.2f, -1.1f);
    glVertex3f(-0.8f, 0.2f, -1.1f);
    glVertex3f(-0.9f, -0.2f, -1.3f);
    glVertex3f(0.9f, -0.2f, -1.3f);

    // Left face (sloped)
    glNormal3f(-0.7071f, 0.7071f, 0.0f);
    glVertex3f(-0.8f, 0.2f, -1.1f);
    glVertex3f(-0.8f, 0.2f, 1.1f);
    glVertex3f(-0.9f, -0.2f, 1.3f);
    glVertex3f(-0.9f, -0.2f, -1.3f);

    // Right face (sloped)
    glNormal3f(0.7071f, 0.7071f, 0.0f);
    glVertex3f(0.8f, 0.2f, 1.1f);
    glVertex3f(0.8f, 0.2f, -1.1f);
    glVertex3f(0.9f, -0.2f, -1.3f);
    glVertex3f(0.9f, -0.2f, 1.3f);

    glEnd();
    glPopMatrix();

    // Front glacis plate (heavily sloped armor)
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, 1.3f);
    glRotatef(-60.0f, 1.0f, 0.0f, 0.0f);
    glScalef(1.8f, 0.1f, 0.6f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Rear deck
    glPushMatrix();
    glTranslatef(0.0f, 0.1f, -1.3f);
    glRotatef(30.0f, 1.0f, 0.0f, 0.0f);
    glScalef(1.8f, 0.1f, 0.4f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Engine deck (raised section at back)
    glPushMatrix();
    glTranslatef(0.0f, 0.3f, -0.8f);
    glScalef(1.6f, 0.2f, 0.8f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Add engine grill details
    glPushMatrix();
    glTranslatef(0.0f, 0.4f, -0.8f);

    // Set material for grill (darker)
    GLfloat grillMat[] = {0.1f, 0.1f, 0.1f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, grillMat);

    // Draw engine grills
    glBegin(GL_LINES);
    for (float x = -0.7f; x <= 0.7f; x += 0.1f)
    {
        glVertex3f(x, 0.01f, -0.3f);
        glVertex3f(x, 0.01f, 0.3f);
    }
    for (float z = -0.3f; z <= 0.3f; z += 0.1f)
    {
        glVertex3f(-0.7f, 0.01f, z);
        glVertex3f(0.7f, 0.01f, z);
    }
    glEnd();
    glPopMatrix();

    // Add side skirts (armor panels along sides)
    glPushMatrix();
    glTranslatef(0.0f, -0.1f, 0.0f);

    // Reset material for side skirts
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);

    // Left side skirt
    glPushMatrix();
    glTranslatef(-0.95f, 0.0f, 0.0f);
    glScalef(0.1f, 0.3f, 2.3f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Right side skirt
    glPushMatrix();
    glTranslatef(0.95f, 0.0f, 0.0f);
    glScalef(0.1f, 0.3f, 2.3f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();
}

// Draw the tank
void DrawTank(const Tank &tank)
{
    glPushMatrix();

    // Position and rotate the tank
    glTranslatef(tank.x, tank.y, tank.z);
    glRotatef(tank.bodyRotation, 0.0f, 1.0f, 0.0f);

    // Draw the improved tank hull
    DrawTankHull(tank);

    // Draw modern tank turret - centered on tank
    glPushMatrix();
    glTranslatef(0.0f, 0.5f, 0.0f); // Centered position on tank
    glRotatef(tank.turretRotation, 0.0f, 1.0f, 0.0f);

    // Set material properties for turret
    GLfloat turretAmbient[] = {0.2f, 0.25f, 0.12f, 1.0f};
    GLfloat turretDiffuse[] = {0.25f, 0.3f, 0.15f, 1.0f};
    GLfloat turretSpecular[] = {0.1f, 0.1f, 0.1f, 1.0f};
    GLfloat turretShininess[] = {10.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, turretAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, turretDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, turretSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, turretShininess);

    // Main turret body - more angular and realistic
    // Draw as a custom shape with angled sides for modern look
    glBegin(GL_QUADS);

    // Turret base dimensions
    float width = 1.0f;
    float height = 0.4f;
    float length = 1.4f;
    float frontTaper = 0.3f; // How much the front narrows

    // Bottom face
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-width / 2, 0.0f, -length / 2);
    glVertex3f(width / 2, 0.0f, -length / 2);
    glVertex3f(width / 2, 0.0f, length / 2);
    glVertex3f(-width / 2, 0.0f, length / 2);

    // Top face - tapered at front
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-width / 2, height, -length / 2);
    glVertex3f(width / 2, height, -length / 2);
    glVertex3f(width / 2 - frontTaper, height, length / 2);
    glVertex3f(-width / 2 + frontTaper, height, length / 2);

    // Front face - tapered
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-width / 2, 0.0f, length / 2);
    glVertex3f(width / 2, 0.0f, length / 2);
    glVertex3f(width / 2 - frontTaper, height, length / 2);
    glVertex3f(-width / 2 + frontTaper, height, length / 2);

    // Back face
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(width / 2, 0.0f, -length / 2);
    glVertex3f(-width / 2, 0.0f, -length / 2);
    glVertex3f(-width / 2, height, -length / 2);
    glVertex3f(width / 2, height, -length / 2);

    // Left face
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(-width / 2, 0.0f, -length / 2);
    glVertex3f(-width / 2, 0.0f, length / 2);
    glVertex3f(-width / 2 + frontTaper, height, length / 2);
    glVertex3f(-width / 2, height, -length / 2);

    // Right face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(width / 2, 0.0f, length / 2);
    glVertex3f(width / 2, 0.0f, -length / 2);
    glVertex3f(width / 2, height, -length / 2);
    glVertex3f(width / 2 - frontTaper, height, length / 2);

    glEnd();

    // Turret top - slightly raised center section
    glPushMatrix();
    glTranslatef(0.0f, height + 0.05f, 0.0f);
    glScalef(0.7f, 0.1f, 0.9f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Commander's cupola (hatch on top)
    glPushMatrix();
    glTranslatef(0.0f, height + 0.15f, -0.4f);

    // Cupola base
    GLUquadricObj *quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
    gluCylinder(quadric, 0.25f, 0.25f, 0.1f, 12, 2);

    // Cupola top
    glTranslatef(0.0f, 0.0f, 0.05f);
    gluDisk(quadric, 0.0f, 0.25f, 12, 1);

    // Hatch details - periscopes
    GLfloat periscopeMat[] = {0.1f, 0.1f, 0.1f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, periscopeMat);

    glPushMatrix();
    glTranslatef(0.1f, 0.05f, 0.0f);
    glScalef(0.05f, 0.05f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.1f, 0.05f, 0.0f);
    glScalef(0.05f, 0.05f, 0.05f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPopMatrix();

    // Gunner's sight (on right side)
    glPushMatrix();
    glTranslatef(0.4f, height + 0.1f, 0.2f);

    GLfloat sightMat[] = {0.1f, 0.1f, 0.1f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sightMat);

    glScalef(0.1f, 0.1f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Main gun mantlet (gun shield) - centered on turret
    glPushMatrix();
    glTranslatef(0.0f, 0.2f, 0.7f); // Centered position

    // Reset material for mantlet
    glMaterialfv(GL_FRONT, GL_AMBIENT, turretAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, turretDiffuse);

    // Draw mantlet as a rounded shield - now facing downward
    glPushMatrix();
    // Draw a cylinder for the mantlet that's oriented downward
    glRotatef(0.0f, 1.0f, 0.0f, 0.0f); // Rotate to point downward
    gluCylinder(quadric, 0.3f, 0.3f, 0.2f, 16, 2);
    glPopMatrix();

    // Main cannon - positioned exactly in the center of the turret
    GLfloat cannonMat[] = {0.1f, 0.1f, 0.1f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cannonMat);

    glPushMatrix();
    // Position at exact center (0,0,0 relative to mantlet)
    // Now pointing straight downward
    glRotatef(0.0f, 1.0f, 0.0f, 0.0f); // Rotate to point downward

    // Cannon base (wider)
    gluCylinder(quadric, 0.15f, 0.13f, 0.3f, 12, 4);

    // Main cannon barrel - longer and more detailed
    glTranslatef(0.0f, 0.0f, 0.3f);
    gluCylinder(quadric, 0.13f, 0.11f, 2.0f, 12, 6);

    // Thermal sleeve (modern tanks have a covering over part of the barrel)
    GLfloat sleeveMat[] = {0.15f, 0.15f, 0.15f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, sleeveMat);
    glTranslatef(0.0f, 0.0f, 0.3f);
    gluCylinder(quadric, 0.14f, 0.14f, 1.0f, 12, 2);

    // Return to cannon material
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cannonMat);

    // Muzzle brake (more detailed)
    glTranslatef(0.0f, 0.0f, 1.7f);
    gluCylinder(quadric, 0.14f, 0.14f, 0.2f, 12, 2);

    // Muzzle brake vents
    glPushMatrix();
    // Vents now need to be rotated differently to be perpendicular to barrel
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

    // Top vent
    glTranslatef(0.0f, 0.1f, 0.0f);
    gluCylinder(quadric, 0.05f, 0.05f, 0.14f, 8, 2);

    // Bottom vent
    glTranslatef(0.0f, -0.2f, 0.0f);
    gluCylinder(quadric, 0.05f, 0.05f, 0.14f, 8, 2);

    glPopMatrix();

    gluDeleteQuadric(quadric);
    glPopMatrix();

    glPopMatrix(); // End mantlet

    // Add a coaxial machine gun next to main gun
    glPushMatrix();
    glTranslatef(0.2f, 0.2f, 0.7f);
    // Rotate to point downward
    glRotatef(0.0f, 1.0f, 0.0f, 0.0f);

    GLfloat mgMat[] = {0.05f, 0.05f, 0.05f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, mgMat);

    GLUquadricObj *mgQuadric = gluNewQuadric();
    gluCylinder(mgQuadric, 0.04f, 0.04f, 0.5f, 8, 2);
    gluDeleteQuadric(mgQuadric);
    glPopMatrix();

    // Add a commander's machine gun on top
    glPushMatrix();
    glTranslatef(0.0f, height + 0.25f, -0.4f);
    glRotatef(30.0f, 0.0f, 1.0f, 0.0f);

    GLUquadricObj *cmgQuadric = gluNewQuadric();
    gluCylinder(cmgQuadric, 0.03f, 0.03f, 0.4f, 8, 2);
    gluDeleteQuadric(cmgQuadric);
    glPopMatrix();

    // Add smoke grenade launchers on sides of turret
    glPushMatrix();
    glTranslatef(0.5f, 0.2f, 0.0f);

    GLfloat grenadeMat[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, grenadeMat);

    // Draw launcher tubes
    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, -0.3f + i * 0.2f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

        GLUquadricObj *grenadeQuadric = gluNewQuadric();
        gluCylinder(grenadeQuadric, 0.04f, 0.04f, 0.15f, 8, 2);
        gluDeleteQuadric(grenadeQuadric);
        glPopMatrix();
    }

    glPopMatrix();

    // Mirror on other side
    glPushMatrix();
    glTranslatef(-0.5f, 0.2f, 0.0f);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);

    // Draw launcher tubes
    for (int i = 0; i < 4; i++)
    {
        glPushMatrix();
        glTranslatef(0.0f, 0.0f, -0.3f + i * 0.2f);
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

        GLUquadricObj *grenadeQuadric = gluNewQuadric();
        gluCylinder(grenadeQuadric, 0.04f, 0.04f, 0.15f, 8, 2);
        gluDeleteQuadric(grenadeQuadric);
        glPopMatrix();
    }

    glPopMatrix();

    glPopMatrix(); // End turret

    // Draw tank tracks and running gear
    // Set material properties for tracks
    GLfloat trackAmbient[] = {0.1f, 0.1f, 0.1f, 1.0f};
    GLfloat trackDiffuse[] = {0.15f, 0.15f, 0.15f, 1.0f};
    GLfloat trackSpecular[] = {0.3f, 0.3f, 0.3f, 1.0f};
    GLfloat trackShininess[] = {20.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, trackAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, trackDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, trackSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, trackShininess);

    // Track animation based on tank speed
    float trackOffset = fmodf(tank.speed * GetTickCount() * 0.0001f, 1.0f);
    float wheelRotation = tank.speed * GetTickCount() * 0.01f;

    // Draw left track assembly
    glPushMatrix();
    glTranslatef(-0.95f, -0.3f, 0.0f);

    // Track base (continuous band)
    glPushMatrix();

    // Draw track path - more realistic with proper contour
    // Top straight section
    glPushMatrix();
    glTranslatef(0.0f, 0.15f, 0.0f);
    glScalef(0.2f, 0.05f, 2.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Bottom straight section
    glPushMatrix();
    glTranslatef(0.0f, -0.15f, 0.0f);
    glScalef(0.2f, 0.05f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Front curved section
    GLUquadricObj *trackQuadric = gluNewQuadric();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(trackQuadric, 0.3f, 0.3f, 0.2f, 12, 1);
    glPopMatrix();

    // Rear curved section
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -1.0f);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(trackQuadric, 0.3f, 0.3f, 0.2f, 12, 1);
    glPopMatrix();

    glPopMatrix(); // End track path

    // Track segments (individual links)
    for (float z = -1.1f; z <= 1.1f; z += 0.15f)
    {
        float adjustedZ = z + trackOffset;
        // Wrap around for continuous track effect
        if (adjustedZ > 1.1f)
            adjustedZ -= 2.2f;
        if (adjustedZ < -1.1f)
            adjustedZ += 2.2f;

        // Calculate y position based on z to follow the track path
        float y = 0.0f;
        if (adjustedZ > 0.7f)
        {
            // Front curve
            float angle = (adjustedZ - 0.7f) * 90.0f / 0.4f;
            y = 0.15f * cos(angle * 3.14159f / 180.0f);
        }
        else if (adjustedZ < -0.7f)
        {
            // Rear curve
            float angle = (adjustedZ + 0.7f) * 90.0f / 0.4f;
            y = 0.15f * cos(angle * 3.14159f / 180.0f);
        }
        else if (adjustedZ > 0.0f)
        {
            // Top straight section
            y = 0.15f;
        }
        else
        {
            // Bottom straight section
            y = -0.15f;
        }

        glPushMatrix();
        glTranslatef(0.0f, y, adjustedZ);

        // Rotate track segments to follow the curve
        if (adjustedZ > 0.7f)
        {
            float angle = (adjustedZ - 0.7f) * 90.0f / 0.4f;
            glRotatef(angle, 1.0f, 0.0f, 0.0f);
        }
        else if (adjustedZ < -0.7f)
        {
            float angle = (adjustedZ + 0.7f) * 90.0f / 0.4f;
            glRotatef(-angle, 1.0f, 0.0f, 0.0f);
        }
        else if (adjustedZ > 0.0f)
        {
            glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
        }
        else
        {
            glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
        }

        // Draw track segment
        glPushMatrix();
        glScalef(0.25f, 0.05f, 0.14f);
        glutSolidCube(1.0f);
        glPopMatrix();

        // Draw track teeth/cleats
        glPushMatrix();
        glTranslatef(0.0f, -0.05f, 0.0f);
        glScalef(0.25f, 0.03f, 0.08f);
        glutSolidCube(1.0f);
        glPopMatrix();

        glPopMatrix();
    }

    // Set material for wheels
    GLfloat wheelAmbient[] = {0.15f, 0.15f, 0.15f, 1.0f};
    GLfloat wheelDiffuse[] = {0.2f, 0.2f, 0.2f, 1.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, wheelAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, wheelDiffuse);

    // Drive sprocket (front wheel)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.0f);
    glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);

    // Wheel hub
    GLUquadricObj *wheelQuadric = gluNewQuadric();
    gluQuadricNormals(wheelQuadric, GLU_SMOOTH);

    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(wheelQuadric, 0.15f, 0.15f, 0.1f, 12, 2);
    glPopMatrix();

    // Wheel rim
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluDisk(wheelQuadric, 0.15f, 0.3f, 12, 2);
    glPopMatrix();

    // Sprocket teeth
    for (int i = 0; i < 8; i++)
    {
        glPushMatrix();
        glRotatef(i * 45.0f, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, 0.3f, 0.0f);
        glScalef(0.05f, 0.1f, 0.1f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    glPopMatrix(); // End drive sprocket

    // Idler wheel (rear)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -1.0f);
    glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);

    // Wheel hub
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(wheelQuadric, 0.15f, 0.15f, 0.1f, 12, 2);
    glPopMatrix();

    // Wheel rim
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluDisk(wheelQuadric, 0.15f, 0.3f, 12, 2);
    glPopMatrix();

    glPopMatrix(); // End idler wheel

    // Road wheels (middle wheels)
    for (float z = -0.7f; z <= 0.7f; z += 0.35f)
    {
        glPushMatrix();
        glTranslatef(0.0f, -0.15f, z);
        glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);

        // Wheel hub
        glPushMatrix();
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        gluCylinder(wheelQuadric, 0.08f, 0.08f, 0.08f, 8, 2);
        glPopMatrix();

        // Wheel rim
        glPushMatrix();
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        gluDisk(wheelQuadric, 0.08f, 0.22f, 8, 2);
        glPopMatrix();

        // Wheel outer face details
        glPushMatrix();
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, 0.08f);
        gluDisk(wheelQuadric, 0.0f, 0.08f, 8, 1);
        glPopMatrix();

        glPopMatrix();
    }

    // Return track rollers (top wheels)
    for (float z = -0.6f; z <= 0.6f; z += 0.4f)
    {
        glPushMatrix();
        glTranslatef(0.0f, 0.15f, z);
        glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);

        // Roller
        glPushMatrix();
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        gluCylinder(wheelQuadric, 0.06f, 0.06f, 0.05f, 8, 1);
        glPopMatrix();

        // Roller ends
        glPushMatrix();
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        gluDisk(wheelQuadric, 0.0f, 0.06f, 8, 1);
        glPopMatrix();

        glPushMatrix();
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, 0.05f);
        gluDisk(wheelQuadric, 0.0f, 0.06f, 8, 1);
        glPopMatrix();

        glPopMatrix();
    }

    gluDeleteQuadric(wheelQuadric);
    glPopMatrix(); // End left track assembly

    // Draw right track assembly (mirror of left)
    glPushMatrix();
    glTranslatef(0.95f, -0.3f, 0.0f);

    // Track base (continuous band)
    glPushMatrix();

    // Draw track path - more realistic with proper contour
    // Top straight section
    glPushMatrix();
    glTranslatef(0.0f, 0.15f, 0.0f);
    glScalef(0.2f, 0.05f, 2.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Bottom straight section
    glPushMatrix();
    glTranslatef(0.0f, -0.15f, 0.0f);
    glScalef(0.2f, 0.05f, 2.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Front curved section
    GLUquadricObj *trackQuadric2 = gluNewQuadric();
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(trackQuadric2, 0.3f, 0.3f, 0.2f, 12, 1);
    glPopMatrix();

    // Rear curved section
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -1.0f);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(trackQuadric2, 0.3f, 0.3f, 0.2f, 12, 1);
    glPopMatrix();

    glPopMatrix(); // End track path

    // Track segments (individual links)
    for (float z = -1.1f; z <= 1.1f; z += 0.15f)
    {
        float adjustedZ = z + trackOffset;
        // Wrap around for continuous track effect
        if (adjustedZ > 1.1f)
            adjustedZ -= 2.2f;
        if (adjustedZ < -1.1f)
            adjustedZ += 2.2f;

        // Calculate y position based on z to follow the track path
        float y = 0.0f;
        if (adjustedZ > 0.7f)
        {
            // Front curve
            float angle = (adjustedZ - 0.7f) * 90.0f / 0.4f;
            y = 0.15f * cos(angle * 3.14159f / 180.0f);
        }
        else if (adjustedZ < -0.7f)
        {
            // Rear curve
            float angle = (adjustedZ + 0.7f) * 90.0f / 0.4f;
            y = 0.15f * cos(angle * 3.14159f / 180.0f);
        }
        else if (adjustedZ > 0.0f)
        {
            // Top straight section
            y = 0.15f;
        }
        else
        {
            // Bottom straight section
            y = -0.15f;
        }

        glPushMatrix();
        glTranslatef(0.0f, y, adjustedZ);

        // Rotate track segments to follow the curve
        if (adjustedZ > 0.7f)
        {
            float angle = (adjustedZ - 0.7f) * 90.0f / 0.4f;
            glRotatef(angle, 1.0f, 0.0f, 0.0f);
        }
        else if (adjustedZ < -0.7f)
        {
            float angle = (adjustedZ + 0.7f) * 90.0f / 0.4f;
            glRotatef(-angle, 1.0f, 0.0f, 0.0f);
        }
        else if (adjustedZ > 0.0f)
        {
            glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
        }
        else
        {
            glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
        }

        // Draw track segment
        glPushMatrix();
        glScalef(0.25f, 0.05f, 0.14f);
        glutSolidCube(1.0f);
        glPopMatrix();

        // Draw track teeth/cleats
        glPushMatrix();
        glTranslatef(0.0f, -0.05f, 0.0f);
        glScalef(0.25f, 0.03f, 0.08f);
        glutSolidCube(1.0f);
        glPopMatrix();

        glPopMatrix();
    }

    // Set material for wheels
    glMaterialfv(GL_FRONT, GL_AMBIENT, wheelAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, wheelDiffuse);

    // Drive sprocket (front wheel)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 1.0f);
    glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);

    // Wheel hub
    GLUquadricObj *wheelQuadric2 = gluNewQuadric();
    gluQuadricNormals(wheelQuadric2, GLU_SMOOTH);

    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(wheelQuadric2, 0.15f, 0.15f, 0.1f, 12, 2);
    glPopMatrix();

    // Wheel rim
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluDisk(wheelQuadric2, 0.15f, 0.3f, 12, 2);
    glPopMatrix();

    // Sprocket teeth
    for (int i = 0; i < 8; i++)
    {
        glPushMatrix();
        glRotatef(i * 45.0f, 0.0f, 0.0f, 1.0f);
        glTranslatef(0.0f, 0.3f, 0.0f);
        glScalef(0.05f, 0.1f, 0.1f);
        glutSolidCube(1.0f);
        glPopMatrix();
    }

    glPopMatrix(); // End drive sprocket

    // Idler wheel (rear)
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -1.0f);
    glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);

    // Wheel hub
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(wheelQuadric2, 0.15f, 0.15f, 0.1f, 12, 2);
    glPopMatrix();

    // Wheel rim
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluDisk(wheelQuadric2, 0.15f, 0.3f, 12, 2);
    glPopMatrix();

    glPopMatrix(); // End idler wheel

    // Road wheels (middle wheels)
    for (float z = -0.7f; z <= 0.7f; z += 0.35f)
    {
        glPushMatrix();
        glTranslatef(0.0f, -0.15f, z);
        glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);

        // Wheel hub
        glPushMatrix();
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        gluCylinder(wheelQuadric2, 0.08f, 0.08f, 0.08f, 8, 2);
        glPopMatrix();

        // Wheel rim
        glPushMatrix();
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        gluDisk(wheelQuadric2, 0.08f, 0.22f, 8, 2);
        glPopMatrix();

        // Wheel outer face details
        glPushMatrix();
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, 0.08f);
        gluDisk(wheelQuadric2, 0.0f, 0.08f, 8, 1);
        glPopMatrix();

        glPopMatrix();
    }

    // Return track rollers (top wheels)
    for (float z = -0.6f; z <= 0.6f; z += 0.4f)
    {
        glPushMatrix();
        glTranslatef(0.0f, 0.15f, z);
        glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);

        // Roller
        glPushMatrix();
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        gluCylinder(wheelQuadric2, 0.06f, 0.06f, 0.05f, 8, 1);
        glPopMatrix();

        // Roller ends
        glPushMatrix();
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        gluDisk(wheelQuadric2, 0.0f, 0.06f, 8, 1);
        glPopMatrix();

        glPushMatrix();
        glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, 0.05f);
        gluDisk(wheelQuadric2, 0.0f, 0.06f, 8, 1);
        glPopMatrix();

        glPopMatrix();
    }

    gluDeleteQuadric(wheelQuadric2);
    glPopMatrix(); // End right track assembly

    // Add exhaust pipes
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(0.6f, 0.4f, -1.0f);

    GLUquadricObj *exhaustQuadric = gluNewQuadric();
    gluCylinder(exhaustQuadric, 0.08f, 0.08f, 0.3f, 8, 2);

    // Add exhaust smoke if tank is moving
    if (fabs(tank.speed) > 0.5f)
    {
        glDisable(GL_LIGHTING);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glTranslatef(0.0f, 0.0f, 0.3f);

        // Draw smoke puffs
        for (float offset = 0.0f; offset < 1.0f; offset += 0.2f)
        {
            float alpha = 1.0f - offset;
            float size = 0.1f + offset * 0.2f;

            glColor4f(0.3f, 0.3f, 0.3f, alpha * 0.7f);
            glPushMatrix();
            glTranslatef(0.0f, offset * 0.5f, offset);
            gluSphere(exhaustQuadric, size, 8, 8);
            glPopMatrix();
        }

        glDisable(GL_BLEND);
        glEnable(GL_LIGHTING);
    }

    gluDeleteQuadric(exhaustQuadric);
    glPopMatrix(); // End exhaust

    glPopMatrix(); // End tank
}

// Draw bullets
void DrawBullets()
{
    // Enable lighting for realistic bullets
    glEnable(GL_LIGHTING);

    for (const auto &bullet : bullets)
    {
        if (bullet.active)
        {
            glPushMatrix();
            glTranslatef(bullet.x, bullet.y, bullet.z);

            // Align bullet with its direction of travel
            // Calculate the angle in the XZ plane (yaw) based on the bullet's direction vector
            float directionYaw = atan2(bullet.dirX, bullet.dirZ) * 180.0f / 3.14159f;

            // Rotate to match the bullet's actual direction of travel
            glRotatef(directionYaw, 0.0f, 1.0f, 0.0f);

            // Rotate to align the missile's long axis with its direction of travel
            // No need for 90-degree rotation as we're using the actual direction vector

            // Add rotation for spinning shell effect - slower rotation for realism
            glRotatef(GetTickCount() * 0.2f, 0.0f, 0.0f, 1.0f);

            // Scale based on bullet size - adjusted for better proportions
            glScalef(bullet.scale * 1.5f, bullet.scale * 1.5f, bullet.scale * 2.0f);

            // Set material properties for missile-like appearance
            GLfloat missileMat[] = {0.3f, 0.3f, 0.3f, 1.0f}; // Darker gray for missile body
            GLfloat missileSpec[] = {0.7f, 0.7f, 0.7f, 1.0f};
            GLfloat missileShin[] = {70.0f};
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, missileMat);
            glMaterialfv(GL_FRONT, GL_SPECULAR, missileSpec);
            glMaterialfv(GL_FRONT, GL_SHININESS, missileShin);

            GLUquadricObj *quadric = gluNewQuadric();
            gluQuadricNormals(quadric, GLU_SMOOTH);

            // Rotate 90 degrees to align the missile properly with its direction of travel
            // This is needed because the gluCylinder creates cylinders along the Z-axis
            glRotatef(90.0f, 0.0f, 1.0f, 0.0f);

            // Draw missile-like projectile

            // Main missile body (cylindrical)
            gluCylinder(quadric, 0.15f, 0.15f, 1.0f, 16, 4);

            // Base cap with exhaust
            glPushMatrix();
            // Rim at base
            GLfloat exhaustRimMat[] = {0.4f, 0.4f, 0.4f, 1.0f};
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, exhaustRimMat);
            gluDisk(quadric, 0.1f, 0.15f, 16, 2);

            // Exhaust nozzle (concave)
            GLfloat exhaustMat[] = {0.2f, 0.2f, 0.2f, 1.0f};
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, exhaustMat);
            gluDisk(quadric, 0.0f, 0.1f, 16, 2);
            glPopMatrix();

            // Missile nose cone - more aerodynamic
            glPushMatrix();
            glTranslatef(0.0f, 0.0f, 1.0f);

            // Nose cone has different color
            GLfloat noseMat[] = {0.7f, 0.1f, 0.1f, 1.0f}; // Red nose cone
            GLfloat noseSpec[] = {0.9f, 0.9f, 0.9f, 1.0f};
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, noseMat);
            glMaterialfv(GL_FRONT, GL_SPECULAR, noseSpec);

            // Longer, more pointed nose cone
            gluCylinder(quadric, 0.15f, 0.0f, 0.5f, 16, 4);
            glPopMatrix();

            // Add guidance fins at the base
            GLfloat finMat[] = {0.5f, 0.5f, 0.5f, 1.0f};
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, finMat);

            // Draw 4 fins
            for (int i = 0; i < 4; i++)
            {
                glPushMatrix();
                glRotatef(i * 90.0f, 0.0f, 0.0f, 1.0f);

                glBegin(GL_TRIANGLES);
                // Fin
                glNormal3f(0.0f, 1.0f, 0.0f);
                glVertex3f(0.15f, 0.0f, 0.1f); // Fin root front
                glVertex3f(0.15f, 0.0f, 0.4f); // Fin root back
                glVertex3f(0.35f, 0.0f, 0.2f); // Fin tip
                glEnd();

                glPopMatrix();
            }

            // Add colored band in the middle
            GLfloat bandMat[] = {0.9f, 0.6f, 0.1f, 1.0f}; // Orange band
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, bandMat);

            glPushMatrix();
            glTranslatef(0.0f, 0.0f, 0.5f);
            gluCylinder(quadric, 0.16f, 0.16f, 0.1f, 16, 2);
            glPopMatrix();

            gluDeleteQuadric(quadric);

            // Draw enhanced rocket exhaust and smoke trail
            glDisable(GL_LIGHTING);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            // Draw rocket exhaust flame - now properly aligned with missile direction
            float flameLength = 0.8f;

            // Inner bright flame
            glBegin(GL_TRIANGLE_FAN);
            glColor4f(1.0f, 0.9f, 0.3f, 0.9f); // Bright yellow core
            glVertex3f(0.0f, 0.0f, 0.0f);      // Flame origin at exhaust

            glColor4f(1.0f, 0.5f, 0.0f, 0.0f); // Fade to transparent orange
            for (int i = 0; i <= 12; i++)
            {
                float angle = i * (2.0f * 3.14159f / 12.0f);
                float x = 0.1f * sin(angle);
                float y = 0.1f * cos(angle);
                glVertex3f(x, y, -flameLength);
            }
            glEnd();

            // Outer flame and smoke
            glBegin(GL_TRIANGLE_FAN);
            glColor4f(1.0f, 0.5f, 0.0f, 0.7f); // Orange
            glVertex3f(0.0f, 0.0f, 0.0f);      // Flame origin

            glColor4f(0.5f, 0.5f, 0.5f, 0.0f); // Fade to transparent gray
            for (int i = 0; i <= 12; i++)
            {
                float angle = i * (2.0f * 3.14159f / 12.0f);
                float x = 0.2f * sin(angle);
                float y = 0.2f * cos(angle);
                glVertex3f(x, y, -flameLength * 1.5f);
            }
            glEnd();

            // Draw smoke trail as a series of transparent quads
            float trailLength = 5.0f; // Much longer trail
            int segments = 15;
            float segmentLength = trailLength / segments;

            for (int i = 0; i < segments; i++)
            {
                float z = -(flameLength + i * segmentLength);
                float alpha = 0.3f * (1.0f - (float)i / segments); // Fade out
                float width = 0.1f + 0.3f * (float)i / segments;   // Widen as it goes back

                // Smoke color transitions from dark gray to light gray
                float grayValue = 0.4f + 0.3f * (float)i / segments;
                glColor4f(grayValue, grayValue, grayValue, alpha);

                glBegin(GL_QUADS);
                glVertex3f(-width, -width, z);
                glVertex3f(width, -width, z);
                glVertex3f(width, width, z);
                glVertex3f(-width, width, z);
                glEnd();
            }

            glEnable(GL_LIGHTING);
            glDisable(GL_BLEND);

            glPopMatrix();
        }
    }
}

// Draw particles
void DrawParticles()
{
    glDisable(GL_LIGHTING);
    glDepthMask(GL_FALSE);

    for (const auto &particle : particles)
    {
        if (particle.active)
        {
            glPushMatrix();
            glTranslatef(particle.x, particle.y, particle.z);

            // Make particles always face the camera (billboarding)
            glColor4f(particle.r, particle.g, particle.b, particle.a);
            glPointSize(particle.size * 10.0f);
            glBegin(GL_POINTS);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glEnd();

            glPopMatrix();
        }
    }

    glDepthMask(GL_TRUE);
    glEnable(GL_LIGHTING);
}

// Draw a tree
void DrawTree(float x, float y, float z, float scale, float rotation)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotation * 180.0f / 3.14159f, 0.0f, 1.0f, 0.0f);
    glScalef(scale, scale, scale);

    // Draw trunk
    glColor3f(0.5f, 0.35f, 0.05f);
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    GLUquadricObj *quadric = gluNewQuadric();
    gluCylinder(quadric, 0.2f, 0.15f, 1.5f, 8, 4);
    glPopMatrix();

    // Draw foliage (cone)
    glColor3f(0.0f, 0.5f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadric, 0.0f, 1.0f, 2.0f, 8, 4);
    glPopMatrix();

    // Draw more foliage
    glPushMatrix();
    glTranslatef(0.0f, 1.8f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(quadric, 0.0f, 0.7f, 1.5f, 8, 4);
    glPopMatrix();

    gluDeleteQuadric(quadric);
    glPopMatrix();
}

// Draw a rock
void DrawRock(float x, float y, float z, float scale, float rotation)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotation * 180.0f / 3.14159f, 0.0f, 1.0f, 0.0f);
    glScalef(scale, scale * 0.7f, scale);

    // Draw rock as an irregular shape
    glColor3f(0.5f, 0.5f, 0.5f);

    glBegin(GL_TRIANGLES);
    // Front face
    glNormal3f(0.0f, 0.5f, 1.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.3f, 0.6f);
    glVertex3f(0.0f, 0.5f, 0.4f);

    // Right face
    glNormal3f(1.0f, 0.5f, 0.0f);
    glVertex3f(0.5f, -0.3f, 0.6f);
    glVertex3f(0.6f, -0.4f, -0.5f);
    glVertex3f(0.0f, 0.5f, 0.4f);

    // Back face
    glNormal3f(0.0f, 0.5f, -1.0f);
    glVertex3f(0.6f, -0.4f, -0.5f);
    glVertex3f(-0.4f, -0.5f, -0.5f);
    glVertex3f(0.0f, 0.5f, -0.3f);

    // Left face
    glNormal3f(-1.0f, 0.5f, 0.0f);
    glVertex3f(-0.4f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.1f, 0.5f, 0.0f);

    // Bottom face
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.3f, 0.6f);
    glVertex3f(0.6f, -0.4f, -0.5f);

    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.6f, -0.4f, -0.5f);
    glVertex3f(-0.4f, -0.5f, -0.5f);
    glEnd();

    glPopMatrix();
}

// Draw a bush
void DrawBush(float x, float y, float z, float scale, float rotation)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glRotatef(rotation * 180.0f / 3.14159f, 0.0f, 1.0f, 0.0f);
    glScalef(scale, scale, scale);

    // Draw bush as a cluster of spheres
    glColor3f(0.0f, 0.4f, 0.0f);

    GLUquadricObj *quadric = gluNewQuadric();

    // Main bush body
    gluSphere(quadric, 0.6f, 8, 8);

    // Additional smaller spheres
    glPushMatrix();
    glTranslatef(0.4f, 0.2f, 0.0f);
    gluSphere(quadric, 0.4f, 8, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.3f, 0.1f, 0.3f);
    gluSphere(quadric, 0.35f, 8, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0f, 0.3f, -0.4f);
    gluSphere(quadric, 0.3f, 8, 8);
    glPopMatrix();

    gluDeleteQuadric(quadric);
    glPopMatrix();
}

// Draw terrain
void DrawTerrain()
{
    // Draw terrain as a grid of quads
    glEnable(GL_LIGHTING);

    int step = 5; // Draw every 5th vertex for performance

    for (int x = 0; x < terrain.width - step; x += step)
    {
        for (int z = 0; z < terrain.length - step; z += step)
        {
            float worldX1 = x - terrain.width / 2.0f;
            float worldZ1 = z - terrain.length / 2.0f;
            float worldX2 = (x + step) - terrain.width / 2.0f;
            float worldZ2 = (z + step) - terrain.length / 2.0f;

            float y1 = terrain.heightMap[x + z * terrain.width];
            float y2 = terrain.heightMap[(x + step) + z * terrain.width];
            float y3 = terrain.heightMap[x + (z + step) * terrain.width];
            float y4 = terrain.heightMap[(x + step) + (z + step) * terrain.width];

            // Calculate average height for this quad
            float avgHeight = (y1 + y2 + y3 + y4) / 4.0f;

            // Set color based on height (green for low areas, brown for higher)
            if (avgHeight < 0.5f)
            {
                glColor3f(0.0f, 0.5f, 0.0f); // Dark green for low areas
            }
            else if (avgHeight < 2.0f)
            {
                glColor3f(0.2f, 0.6f, 0.1f); // Medium green for medium areas
            }
            else if (avgHeight < 4.0f)
            {
                glColor3f(0.3f, 0.5f, 0.2f); // Olive green for higher areas
            }
            else
            {
                glColor3f(0.5f, 0.4f, 0.3f); // Brown for highest areas
            }

            // Calculate normal for lighting
            glBegin(GL_QUADS);

            // Calculate normal for this quad
            float nx = (y1 - y2) + (y3 - y4);
            float ny = 2.0f * step;
            float nz = (y1 - y3) + (y2 - y4);
            float len = sqrt(nx * nx + ny * ny + nz * nz);
            nx /= len;
            ny /= len;
            nz /= len;

            glNormal3f(nx, ny, nz);

            // Draw quad
            glVertex3f(worldX1, y1, worldZ1);
            glVertex3f(worldX2, y2, worldZ1);
            glVertex3f(worldX2, y4, worldZ2);
            glVertex3f(worldX1, y3, worldZ2);

            glEnd();
        }
    }

    // Draw terrain border/wall to visually show the boundaries
    glColor3f(0.5f, 0.3f, 0.2f);
    float wallHeight = 10.0f;
    float worldSize = terrain.width / 2.0f;

    // Draw four walls
    glBegin(GL_QUADS);
    // North wall
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-worldSize, 0.0f, -worldSize);
    glVertex3f(worldSize, 0.0f, -worldSize);
    glVertex3f(worldSize, wallHeight, -worldSize);
    glVertex3f(-worldSize, wallHeight, -worldSize);

    // South wall
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(-worldSize, 0.0f, worldSize);
    glVertex3f(-worldSize, wallHeight, worldSize);
    glVertex3f(worldSize, wallHeight, worldSize);
    glVertex3f(worldSize, 0.0f, worldSize);

    // East wall
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(worldSize, 0.0f, -worldSize);
    glVertex3f(worldSize, 0.0f, worldSize);
    glVertex3f(worldSize, wallHeight, worldSize);
    glVertex3f(worldSize, wallHeight, -worldSize);

    // West wall
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-worldSize, 0.0f, -worldSize);
    glVertex3f(-worldSize, wallHeight, -worldSize);
    glVertex3f(-worldSize, wallHeight, worldSize);
    glVertex3f(-worldSize, 0.0f, worldSize);
    glEnd();

    // Draw terrain objects (trees, rocks, bushes)
    for (const auto &obj : terrain.objects)
    {
        switch (obj.type)
        {
        case 0: // Tree
            DrawTree(obj.x, obj.y, obj.z, obj.scale, obj.rotation);
            break;
        case 1: // Rock
            DrawRock(obj.x, obj.y, obj.z, obj.scale, obj.rotation);
            break;
        case 2: // Bush
            DrawBush(obj.x, obj.y, obj.z, obj.scale, obj.rotation);
            break;
        }
    }
}

// Draw network menu
void DrawNetworkMenu()
{

    // Switch to 2D orthographic projection
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    // Fix the mirrored text by using a standard orthographic projection
    glOrtho(0, currentWidth, 0, currentHeight, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Draw semi-transparent background with border
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Calculate menu dimensions - centered with proper proportions
    float menuWidth = currentWidth * 0.6f;   // Slightly wider for better text display
    float menuHeight = currentHeight * 0.7f; // Taller for more content
    float menuLeft = (currentWidth - menuWidth) / 2.0f;
    float menuRight = menuLeft + menuWidth;
    float menuBottom = (currentHeight - menuHeight) / 2.0f;
    float menuTop = menuBottom + menuHeight;

    // Draw semi-transparent dark background for retro look
    glColor4f(0.0f, 0.0f, 0.1f, 0.9f); // Very dark blue, more opaque
    glBegin(GL_QUADS);
    glVertex2f(menuLeft, menuBottom);
    glVertex2f(menuRight, menuBottom);
    glVertex2f(menuRight, menuTop);
    glVertex2f(menuLeft, menuTop);
    glEnd();

    // Draw yellow border with pixel-perfect thickness
    glColor4f(1.0f, 1.0f, 0.0f, 1.0f); // Bright yellow border
    glLineWidth(4.0f);                 // Thicker for better visibility
    glBegin(GL_LINE_LOOP);
    glVertex2f(menuLeft, menuBottom);
    glVertex2f(menuRight, menuBottom);
    glVertex2f(menuRight, menuTop);
    glVertex2f(menuLeft, menuTop);
    glEnd();

    // Draw inner border for retro look
    glColor4f(1.0f, 1.0f, 0.0f, 0.7f); // Brighter yellow for inner border
    glLineWidth(2.0f);                 // Thicker inner border
    glBegin(GL_LINE_LOOP);
    glVertex2f(menuLeft + 8, menuBottom + 8);
    glVertex2f(menuRight - 8, menuBottom + 8);
    glVertex2f(menuRight - 8, menuTop - 8);
    glVertex2f(menuLeft + 8, menuTop - 8);
    glEnd();

    // Draw horizontal separator lines
    glColor4f(1.0f, 1.0f, 0.0f, 0.7f); // Yellow for separator
    glLineWidth(2.0f);

    // Top separator (below status)
    glBegin(GL_LINES);
    glVertex2f(menuLeft + 20, menuTop - 50);
    glVertex2f(menuRight - 20, menuTop - 50);
    glEnd();

    // Bottom separator (above footer)
    glBegin(GL_LINES);
    glVertex2f(menuLeft + 20, menuBottom + 50);
    glVertex2f(menuRight - 20, menuBottom + 50);
    glEnd();

    // Create a custom DrawRetroText function for this menu
    auto DrawRetroText = [&](float x, float y, const std::string &text, bool centered = false, bool isTitle = false, bool isHighlighted = false)
    {
        float textX = x;
        if (centered)
        {
            // Approximate centering based on text length and wider character width
            textX = x - (text.length() * 11.0f);
        }

        // Choose text color based on highlight status
        float textR = 1.0f;
        float textG = isHighlighted ? 0.5f : 1.0f; // Less green for highlighted text (more orange)
        float textB = isHighlighted ? 0.0f : 0.0f;

        // Draw text with black shadow and white outline for better readability
        if (isTitle)
        {
            // Black shadow for depth
            glColor3f(0.0f, 0.0f, 0.0f);
            DrawSimpleText(textX + 2, y - 2, text, 0.0f, 0.0f, 0.0f);

            // White outline for title text (thicker)
            glColor3f(1.0f, 1.0f, 1.0f);
            for (int dx = -2; dx <= 2; dx++)
            {
                for (int dy = -2; dy <= 2; dy++)
                {
                    if ((abs(dx) == 2 || abs(dy) == 2) && !(abs(dx) == 2 && abs(dy) == 2))
                    { // Only draw the outer edge
                        DrawSimpleText(textX + dx, y + dy, text, 1.0f, 1.0f, 1.0f);
                    }
                }
            }

            // Draw colored text on top
            DrawSimpleText(textX, y, text, textR, textG, textB);
        }
        else
        {
            // Black shadow for depth
            glColor3f(0.0f, 0.0f, 0.0f);
            DrawSimpleText(textX + 2, y - 2, text, 0.0f, 0.0f, 0.0f);

            // White outline for normal text
            glColor3f(1.0f, 1.0f, 1.0f);
            DrawSimpleText(textX - 1, y, text, 1.0f, 1.0f, 1.0f);
            DrawSimpleText(textX + 1, y, text, 1.0f, 1.0f, 1.0f);
            DrawSimpleText(textX, y - 1, text, 1.0f, 1.0f, 1.0f);
            DrawSimpleText(textX, y + 1, text, 1.0f, 1.0f, 1.0f);

            // Draw colored text on top
            DrawSimpleText(textX, y, text, textR, textG, textB);
        }
    };

    // Calculate menu center for alignment
    float menuCenterX = menuLeft + (menuWidth / 2.0f);

    // Draw title at the top of the menu
    DrawRetroText(menuCenterX, menuTop - 40, "TANK BATTLE NETWORK", true, true);

    // Draw horizontal separator below title
    glColor4f(1.0f, 1.0f, 0.0f, 0.7f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(menuLeft + 20, menuTop - 60);
    glVertex2f(menuRight - 20, menuTop - 60);
    glEnd();

    // Draw status below the title
    std::string statusText = "STATUS: ";
    if (isNetworked)
    {
        if (networkManager.IsConnected())
        {
            statusText += "CONNECTED";
            // Draw status text with highlight
            DrawRetroText(menuLeft + 40, menuTop - 90, statusText, false, false, true);
        }
        else
        {
            statusText += "WAITING";
            // Draw status text with yellow
            DrawRetroText(menuLeft + 40, menuTop - 90, statusText);
        }
    }
    else
    {
        statusText += "OFFLINE";
        // Draw status text with normal yellow
        DrawRetroText(menuLeft + 40, menuTop - 90, statusText);
    }

    // Display current IP information
    if (isNetworked)
    {
        std::string ipInfo;
        if (isServer)
        {
            // Get local IP address - simplified to avoid hostent issues
            ipInfo = "SERVER IP: 127.0.0.1";

            // Display the port number
            ipInfo += " (PORT: ";
            ipInfo += DEFAULT_PORT;
            ipInfo += ")";
        }
        else
        {
            ipInfo = "CONNECTED TO: " + serverIP;
        }

        // Draw IP information with larger spacing between characters
        // DrawRetroText(menuLeft + 40, menuTop - 130, ipInfo);
    }

    // Draw menu title above options
    DrawRetroText(menuCenterX, menuTop - 180, "OPTIONS", true, true);

    // Draw horizontal separator below section title
    glColor4f(1.0f, 1.0f, 0.0f, 0.7f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(menuLeft + 20, menuTop - 200);
    glVertex2f(menuRight - 20, menuTop - 200);
    glEnd();

    // Calculate option positions
    float optionSpacing = 60.0f; // Increased spacing for better readability
    float optionStartY = menuTop - 240;
    float optionX = menuLeft + 60; // Increased indent

    // Draw menu options with retro styling
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Option 1: START SERVER
    float y = optionStartY;
    DrawRetroText(optionX, y, "1. START SERVER");

    // Option 2: CONNECT TO SERVER
    y -= optionSpacing;
    DrawRetroText(optionX, y, "2. CONNECT TO SERVER");

    // Option 3: DISCONNECT
    y -= optionSpacing;
    DrawRetroText(optionX, y, "3. DISCONNECT");

    // Option 4: SEND CHAT MESSAGE
    y -= optionSpacing;
    DrawRetroText(optionX, y, "4. SEND CHAT MESSAGE");

    // Draw footer text
    DrawRetroText(menuCenterX, menuBottom + 40, "NETWORK MENU", true);

    glDisable(GL_BLEND);

    // Restore 3D projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

// Draw HUD
void DrawHUD()
{
    // Switch to 2D orthographic projection for HUD
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    // Fix the mirrored text by using a standard orthographic projection
    glOrtho(0, currentWidth, 0, currentHeight, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Draw health bar - adjust Y coordinates for the new projection
    int healthBarWidth = 200;
    int healthBarHeight = 20;
    int healthBarX = 20;
    int healthBarY = currentHeight - 40; // Position from the bottom

    // Health bar background
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
    glVertex2f(healthBarX, healthBarY);
    glVertex2f(healthBarX + healthBarWidth, healthBarY);
    glVertex2f(healthBarX + healthBarWidth, healthBarY + healthBarHeight);
    glVertex2f(healthBarX, healthBarY + healthBarHeight);
    glEnd();

    // Health bar fill
    float healthPercent = (float)playerTank.health / (float)playerTank.maxHealth;
    glColor3f(1.0f - healthPercent, healthPercent, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(healthBarX, healthBarY);
    glVertex2f(healthBarX + healthBarWidth * healthPercent, healthBarY);
    glVertex2f(healthBarX + healthBarWidth * healthPercent, healthBarY + healthBarHeight);
    glVertex2f(healthBarX, healthBarY + healthBarHeight);
    glEnd();

    // Draw minimap - adjust Y coordinates for the new projection
    int minimapSize = 150;
    int minimapX = currentWidth - minimapSize - 20;
    int minimapY = currentHeight - minimapSize - 20; // Position from the bottom

    // Minimap background
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
    glVertex2f(minimapX, minimapY);
    glVertex2f(minimapX + minimapSize, minimapY);
    glVertex2f(minimapX + minimapSize, minimapY + minimapSize);
    glVertex2f(minimapX, minimapY + minimapSize);
    glEnd();

    // Minimap border
    glColor3f(0.5f, 0.5f, 0.5f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(minimapX, minimapY);
    glVertex2f(minimapX + minimapSize, minimapY);
    glVertex2f(minimapX + minimapSize, minimapY + minimapSize);
    glVertex2f(minimapX, minimapY + minimapSize);
    glEnd();

    // Draw player tank on minimap - adjust for the new projection
    float minimapScale = minimapSize / (float)terrain.width;
    float tankMinimapX = minimapX + (playerTank.x + terrain.width / 2.0f) * minimapScale;
    float tankMinimapY = minimapY + (playerTank.z + terrain.length / 2.0f) * minimapScale;

    // Tank position
    glColor3f(0.0f, 1.0f, 0.0f);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glVertex2f(tankMinimapX, tankMinimapY);
    glEnd();

    // Tank direction
    float dirX = sin(playerTank.bodyRotation * 3.14159f / 180.0f) * 5.0f;
    float dirY = -cos(playerTank.bodyRotation * 3.14159f / 180.0f) * 5.0f; // Negate Y for the new projection
    glBegin(GL_LINES);
    glVertex2f(tankMinimapX, tankMinimapY);
    glVertex2f(tankMinimapX + dirX, tankMinimapY + dirY);
    glEnd();

    // Draw crosshair at the center of the screen
    int crosshairSize = 10;
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(currentWidth / 2 - crosshairSize, currentHeight / 2);
    glVertex2f(currentWidth / 2 + crosshairSize, currentHeight / 2);
    glVertex2f(currentWidth / 2, currentHeight / 2 - crosshairSize);
    glVertex2f(currentWidth / 2, currentHeight / 2 + crosshairSize);
    glEnd();

    // Restore 3D projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

// Initialize networking
void InitializeNetworking()
{
    // Initialize Winsock
    if (!NetworkManager::Initialize())
    {
        std::cerr << "Failed to initialize Winsock" << std::endl;
        return;
    }

    // Set up callbacks
    networkManager.SetMessageCallback(HandleNetworkMessage);
    networkManager.SetConnectCallback(HandleConnect);
    networkManager.SetDisconnectCallback(HandleDisconnect);

    std::cout << "Networking initialized" << std::endl;
    std::cout << "Press N to open network menu" << std::endl;
}

// Start server
void StartServer()
{
    if (networkManager.StartServer())
    {
        isNetworked = true;
        isServer = true;
        networkStatus = "Server started, waiting for client";
        std::cout << "Server started" << std::endl;
    }
    else
    {
        networkStatus = "Failed to start server";
        std::cout << "Failed to start server" << std::endl;
    }
}

// Connect to server
void ConnectToServer(const std::string &ip)
{
    // Log connection attempt
    std::cout << "Attempting to connect to: " << ip << std::endl;

    if (networkManager.ConnectToServer(ip))
    {
        isNetworked = true;
        isServer = false;
        serverIP = ip;
        networkStatus = "Connecting to " + ip;
        std::cout << "Connection attempt successful to " << ip << std::endl;
    }
    else
    {
        networkStatus = "Failed to connect to " + ip;
        std::cout << "Connection attempt failed to " << ip << std::endl;
    }
}

// Disconnect from network
void DisconnectFromNetwork()
{
    if (isNetworked)
    {
        if (networkManager.IsConnected())
        {
            networkManager.SendMessage(MessageType::DISCONNECT, nullptr, 0);
        }
        isNetworked = false;
        networkStatus = "Disconnected";
        chatMessages.clear();
        std::cout << "Disconnected from network" << std::endl;
    }
}

// Send tank state
void SendTankState()
{
    if (isNetworked && networkManager.IsConnected())
    {
        NetworkTankState state;
        state.x = playerTank.x;
        state.y = playerTank.y;
        state.z = playerTank.z;
        state.bodyRotation = playerTank.bodyRotation;
        state.turretRotation = playerTank.turretRotation;
        state.health = playerTank.health;

        networkManager.SendTankState(state);
    }
}

// Send bullet fired
void SendBulletFired(const Bullet &bullet)
{
    if (isNetworked && networkManager.IsConnected())
    {
        NetworkBulletState state;
        state.x = bullet.x;
        state.y = bullet.y;
        state.z = bullet.z;
        state.dirX = bullet.dirX;
        state.dirY = bullet.dirY;
        state.dirZ = bullet.dirZ;
        state.damage = bullet.damage;

        networkManager.SendBulletFired(state);
    }
}

// Handle network message
void HandleNetworkMessage(MessageType type, const void *data, int size)
{
    switch (type)
    {
    case MessageType::TANK_UPDATE:
        if (size == sizeof(NetworkTankState))
        {
            const NetworkTankState *state = static_cast<const NetworkTankState *>(data);
            remoteTank.x = state->x;
            remoteTank.y = state->y;
            remoteTank.z = state->z;
            remoteTank.bodyRotation = state->bodyRotation;
            remoteTank.turretRotation = state->turretRotation;
            remoteTank.health = state->health;
        }
        break;

    case MessageType::BULLET_FIRED:
        if (size == sizeof(NetworkBulletState))
        {
            const NetworkBulletState *state = static_cast<const NetworkBulletState *>(data);

            // Create a new bullet
            Bullet newBullet;
            newBullet.x = state->x;
            newBullet.y = state->y;
            newBullet.z = state->z;
            newBullet.dirX = state->dirX;
            newBullet.dirY = state->dirY;
            newBullet.dirZ = state->dirZ;
            newBullet.speed = 30.0f; // Same as local bullets
            newBullet.lifetime = 5.0f;
            newBullet.scale = 0.25f;
            newBullet.active = true;
            newBullet.damage = state->damage;

            // Add to bullets list
            bullets.push_back(newBullet);

            // Create muzzle flash effect
            CreateExplosion(state->x, state->y, state->z, 20);
        }
        break;

    case MessageType::BULLET_HIT:
        if (size == sizeof(NetworkBulletHit))
        {
            const NetworkBulletHit *hit = static_cast<const NetworkBulletHit *>(data);

            // Apply damage based on who was hit
            if (hit->isPlayerHit)
            {
                // Remote player is telling us they were hit by our bullet
                // We don't need to do anything here as they've already updated their health
                std::cout << "Remote player was hit by our bullet for " << hit->damage << " damage" << std::endl;
            }
            else
            {
                // Remote player is telling us we were hit by their bullet
                playerTank.health -= hit->damage;

                // Ensure health doesn't go below 0
                if (playerTank.health < 0)
                    playerTank.health = 0;

                std::cout << "We were hit by remote player's bullet for " << hit->damage << " damage" << std::endl;
                std::cout << "Our health is now " << playerTank.health << std::endl;

                // Check if player tank is destroyed
                if (playerTank.health <= 0)
                {
                    // Player lost
                    gameOver = true;
                    playerWon = false;
                    showGameOverScreen = true;
                    showRetryButton = true;
                }
            }
        }
        break;

    case MessageType::GAME_STATE:
        if (size == sizeof(NetworkGameState))
        {
            const NetworkGameState *state = static_cast<const NetworkGameState *>(data);

            // Update game state
            if (state->gameOver)
            {
                gameOver = true;
                playerWon = !state->playerWon; // Invert because the message is from the other player's perspective
                showGameOverScreen = true;
                showRetryButton = true;

                std::cout << "Game over! " << (playerWon ? "You won!" : "You lost!") << std::endl;
            }
        }
        break;

    case MessageType::GAME_RESET:
        // Reset the game
        ResetGame();
        break;

    case MessageType::CHAT_MESSAGE:
        if (size > 0)
        {
            std::string message = static_cast<const char *>(data);
            chatMessages.push_back("Peer: " + message);

            // Limit chat history
            if (chatMessages.size() > 10)
            {
                chatMessages.erase(chatMessages.begin());
            }
        }
        break;

    default:
        break;
    }
}

// Handle connect
void HandleConnect(bool success)
{
    if (success)
    {
        networkStatus = "Connected";
        std::cout << "Connected to peer" << std::endl;

        // Reset remote tank position
        remoteTank.x = -playerTank.x;
        remoteTank.z = -playerTank.z;
        remoteTank.y = terrain.getHeight(remoteTank.x, remoteTank.z) + 0.5f;
    }
    else
    {
        networkStatus = "Connection failed";
        std::cout << "Connection failed" << std::endl;
    }
}

// Handle disconnect
void HandleDisconnect()
{
    networkStatus = "Disconnected";
    std::cout << "Disconnected from peer" << std::endl;
}

// Update networking
void UpdateNetworking()
{
    // Send tank state periodically
    static float lastUpdateTime = 0.0f;
    lastUpdateTime += deltaTime;

    if (lastUpdateTime >= 0.05f)
    { // 20 updates per second
        SendTankState();
        lastUpdateTime = 0.0f;
    }
}

// Reset the game
void ResetGame()
{
    std::cout << "Resetting game..." << std::endl;

    // Reset game state
    gameOver = false;
    playerWon = false;
    showGameOverScreen = false;
    showRetryButton = false;

    // Reset player tank
    playerTank.x = 0.0f;
    playerTank.y = 0.0f;
    playerTank.z = 0.0f;
    playerTank.bodyRotation = 0.0f;
    playerTank.turretRotation = 0.0f;
    playerTank.speed = 0.0f;
    playerTank.health = playerTank.maxHealth;
    playerTank.canFire = true;
    playerTank.currentReloadTime = 0.0f;

    // Reset remote tank with proper positioning
    if (isNetworked && isServer)
    {
        // Server places remote tank at opposite position
        remoteTank.x = 20.0f;
        remoteTank.z = 20.0f;
        remoteTank.bodyRotation = 225.0f; // Facing toward player
    }
    else
    {
        // Client places remote tank at opposite position
        remoteTank.x = -20.0f;
        remoteTank.z = -20.0f;
        remoteTank.bodyRotation = 45.0f; // Facing toward player
    }

    // Set common remote tank properties
    remoteTank.y = terrain.getHeight(remoteTank.x, remoteTank.z) + 0.5f;
    remoteTank.turretRotation = remoteTank.bodyRotation;
    remoteTank.speed = 0.0f;
    remoteTank.health = remoteTank.maxHealth;

    // Clear bullets
    bullets.clear();

    // Clear particles
    particles.clear();

    // Reset camera
    camera.distance = 10.0f;
    camera.height = 5.0f;
    camera.smoothFactor = 5.0f;

    // Send tank state to sync with remote player
    if (isNetworked && networkManager.IsConnected())
    {
        // Send multiple times to ensure it gets through
        for (int i = 0; i < 3; i++)
        {
            SendTankState();
            Sleep(50); // Small delay between sends
        }
    }

    std::cout << "Game reset complete!" << std::endl;
}

// Draw game over screen
void DrawGameOverScreen()
{
    if (!showGameOverScreen)
        return;

    // Switch to 2D orthographic projection
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    // Fix the mirrored text by using a standard orthographic projection
    glOrtho(0, currentWidth, 0, currentHeight, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Draw semi-transparent background with border
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Calculate menu dimensions - centered with proper proportions
    float menuWidth = currentWidth * 0.6f;
    float menuHeight = currentHeight * 0.4f;
    float menuLeft = (currentWidth - menuWidth) / 2.0f;
    float menuRight = menuLeft + menuWidth;
    float menuBottom = (currentHeight - menuHeight) / 2.0f;
    float menuTop = menuBottom + menuHeight;

    // Draw semi-transparent dark background
    glColor4f(0.0f, 0.0f, 0.1f, 0.9f);
    glBegin(GL_QUADS);
    glVertex2f(menuLeft, menuBottom);
    glVertex2f(menuRight, menuBottom);
    glVertex2f(menuRight, menuTop);
    glVertex2f(menuLeft, menuTop);
    glEnd();

    // Draw border
    glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
    glLineWidth(4.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(menuLeft, menuBottom);
    glVertex2f(menuRight, menuBottom);
    glVertex2f(menuRight, menuTop);
    glVertex2f(menuLeft, menuTop);
    glEnd();

    // Draw inner border
    glColor4f(1.0f, 1.0f, 0.0f, 0.7f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(menuLeft + 8, menuBottom + 8);
    glVertex2f(menuRight - 8, menuBottom + 8);
    glVertex2f(menuRight - 8, menuTop - 8);
    glVertex2f(menuLeft + 8, menuTop - 8);
    glEnd();

    // Calculate menu center for alignment
    float menuCenterX = menuLeft + (menuWidth / 2.0f);

    // Create a custom DrawRetroText function for this menu (similar to the one in DrawNetworkMenu)
    auto DrawRetroText = [&](float x, float y, const std::string &text, bool centered = false, bool isTitle = false, bool isHighlighted = false)
    {
        float textX = x;
        if (centered)
        {
            // Approximate centering based on text length and wider character width
            textX = x - (text.length() * 11.0f);
        }

        // Choose text color based on highlight status
        float textR = 1.0f;
        float textG = isHighlighted ? 0.5f : 1.0f; // Less green for highlighted text (more orange)
        float textB = isHighlighted ? 0.0f : 0.0f;

        // Draw text with black shadow and white outline for better readability
        if (isTitle)
        {
            // Black shadow for depth
            glColor3f(0.0f, 0.0f, 0.0f);
            DrawSimpleText(textX + 2, y - 2, text, 0.0f, 0.0f, 0.0f);

            // White outline for title text (thicker)
            glColor3f(1.0f, 1.0f, 1.0f);
            for (int dx = -2; dx <= 2; dx++)
            {
                for (int dy = -2; dy <= 2; dy++)
                {
                    if ((abs(dx) == 2 || abs(dy) == 2) && !(abs(dx) == 2 && abs(dy) == 2))
                    { // Only draw the outer edge
                        DrawSimpleText(textX + dx, y + dy, text, 1.0f, 1.0f, 1.0f);
                    }
                }
            }

            // Draw colored text on top
            DrawSimpleText(textX, y, text, textR, textG, textB);
        }
        else
        {
            // Black shadow for depth
            glColor3f(0.0f, 0.0f, 0.0f);
            DrawSimpleText(textX + 2, y - 2, text, 0.0f, 0.0f, 0.0f);

            // White outline for normal text
            glColor3f(1.0f, 1.0f, 1.0f);
            DrawSimpleText(textX - 1, y, text, 1.0f, 1.0f, 1.0f);
            DrawSimpleText(textX + 1, y, text, 1.0f, 1.0f, 1.0f);
            DrawSimpleText(textX, y - 1, text, 1.0f, 1.0f, 1.0f);
            DrawSimpleText(textX, y + 1, text, 1.0f, 1.0f, 1.0f);

            // Draw colored text on top
            DrawSimpleText(textX, y, text, textR, textG, textB);
        }
    };

    // Calculate the vertical center of the menu for better positioning
    float menuCenterY = menuBottom + (menuHeight / 2.0f);

    // Calculate retry button dimensions first (we'll draw it later)
    float buttonWidth = 200.0f;
    float buttonHeight = 50.0f; // Slightly taller button for better visibility
    float buttonLeft = menuCenterX - (buttonWidth / 2.0f);
    float buttonRight = buttonLeft + buttonWidth;
    // Position the button with proper spacing from the top text
    float buttonBottom = menuCenterY - (buttonHeight / 2.0f); // Center vertically in the lower half
    float buttonTop = buttonBottom + buttonHeight;

    // Store button position for mouse click detection
    static float retryButtonLeft = buttonLeft;
    static float retryButtonRight = buttonRight;
    static float retryButtonBottom = buttonBottom;
    static float retryButtonTop = buttonTop;

    // Draw retry button background first (so it's behind everything)
    if (showRetryButton)
    {
        // Draw button background
        glColor4f(0.2f, 0.2f, 0.3f, 0.9f);
        glBegin(GL_QUADS);
        glVertex2f(buttonLeft, buttonBottom);
        glVertex2f(buttonRight, buttonBottom);
        glVertex2f(buttonRight, buttonTop);
        glVertex2f(buttonLeft, buttonTop);
        glEnd();

        // Draw button border
        glColor4f(1.0f, 1.0f, 0.0f, 1.0f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
        glVertex2f(buttonLeft, buttonBottom);
        glVertex2f(buttonRight, buttonBottom);
        glVertex2f(buttonRight, buttonTop);
        glVertex2f(buttonLeft, buttonTop);
        glEnd();
    }

    // Draw result message as the main title
    std::string resultMessage = playerWon ? "YOU WIN" : "YOU LOSE";
    DrawRetroText(menuCenterX, menuTop - 40, resultMessage, true, true, playerWon);

    // Draw horizontal separator below title
    glColor4f(1.0f, 1.0f, 0.0f, 0.7f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    glVertex2f(menuLeft + 20, menuTop - 60);
    glVertex2f(menuRight - 20, menuTop - 60);
    glEnd();

    // Draw retry button text last (so it's on top of everything)
    if (showRetryButton)
    {
        // Use a higher z-order for the button text by temporarily adjusting the depth range
        glDepthRange(0.0, 0.1); // Bring text closer to viewer

        // Draw button text with enhanced visibility
        // First draw a larger outline for better visibility
        glColor3f(0.0f, 0.0f, 0.0f);
        for (int dx = -3; dx <= 3; dx++)
        {
            for (int dy = -3; dy <= 3; dy++)
            {
                if ((abs(dx) == 3 || abs(dy) == 3) && !(abs(dx) == 3 && abs(dy) == 3))
                {
                    DrawSimpleText(menuCenterX - (5 * 11.0f) + dx, buttonBottom + 15 + dy, "RETRY", 0.0f, 0.0f, 0.0f);
                }
            }
        }

        // Draw white glow around text
        glColor3f(1.0f, 1.0f, 1.0f);
        for (int dx = -2; dx <= 2; dx++)
        {
            for (int dy = -2; dy <= 2; dy++)
            {
                if ((abs(dx) == 2 || abs(dy) == 2) && !(abs(dx) == 2 && abs(dy) == 2))
                {
                    DrawSimpleText(menuCenterX - (5 * 11.0f) + dx, buttonBottom + 15 + dy, "RETRY", 1.0f, 1.0f, 1.0f);
                }
            }
        }

        // Draw the actual text in bright yellow
        DrawSimpleText(menuCenterX - (5 * 11.0f), buttonBottom + 15, "RETRY", 1.0f, 1.0f, 0.0f);

        // Add a pulsing effect to make the button more noticeable
        static float pulseTime = 0.0f;
        pulseTime += deltaTime;
        float pulseScale = 1.0f + 0.1f * sin(pulseTime * 5.0f);

        // Draw an additional highlight around the button
        glColor4f(1.0f, 1.0f, 0.0f, 0.3f + 0.2f * sin(pulseTime * 5.0f));
        glLineWidth(3.0f * pulseScale);
        glBegin(GL_LINE_LOOP);
        glVertex2f(buttonLeft - 5, buttonBottom - 5);
        glVertex2f(buttonRight + 5, buttonBottom - 5);
        glVertex2f(buttonRight + 5, buttonTop + 5);
        glVertex2f(buttonLeft - 5, buttonTop + 5);
        glEnd();

        // Reset depth range
        glDepthRange(0.0, 1.0);

        // Check if mouse is clicked on the retry button
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
        {
            POINT mousePos;
            GetCursorPos(&mousePos);
            ScreenToClient(hWnd, &mousePos);

            // Convert to OpenGL coordinates (y is inverted)
            float mouseX = static_cast<float>(mousePos.x);
            float mouseY = currentHeight - static_cast<float>(mousePos.y);

            if (mouseX >= retryButtonLeft && mouseX <= retryButtonRight &&
                mouseY >= retryButtonBottom && mouseY <= retryButtonTop)
            {
                // Reset the game
                ResetGame();

                // Send game reset message to remote player
                if (isNetworked && networkManager.IsConnected())
                {
                    networkManager.SendGameReset();
                }
            }
        }
    }

    // Restore 3D projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

// Draw text on screen
void DrawText(float x, float y, const std::string &text, float r, float g, float b)
{
    // Just use our DrawSimpleText function for consistency
    DrawSimpleText(x, y, text, r, g, b);
}

// Draw simple text using our custom character renderer with retro styling
void DrawSimpleText(float x, float y, const std::string &text, float r, float g, float b)
{
    // Switch to 2D orthographic projection for text
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    // Fix the mirrored text by using a standard orthographic projection
    glOrtho(0, currentWidth, 0, currentHeight, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Calculate the correct y-coordinate for the new projection
    // In the new projection, y=0 is at the bottom, not the top
    float adjustedY = currentHeight - y;

    // Character width and spacing - adjusted for retro look
    float charWidth = 18.0f;  // Slightly wider for better readability
    float charSpacing = 4.0f; // More spacing between characters
    float totalTextWidth = text.length() * (charWidth + charSpacing);

    // Draw a semi-transparent background for better text visibility
    glColor4f(0.0f, 0.0f, 0.0f, 0.5f); // Semi-transparent black
    glBegin(GL_QUADS);
    glVertex2f(x - 5, adjustedY - 25);
    glVertex2f(x + totalTextWidth + 5, adjustedY - 25);
    glVertex2f(x + totalTextWidth + 5, adjustedY + 5);
    glVertex2f(x - 5, adjustedY + 5);
    glEnd();

    // Draw each character using our custom DrawCharacter function
    float charX = x;
    float charY = adjustedY - 20; // Position characters with proper vertical alignment

    // Convert text to uppercase for retro style
    std::string upperText = text;
    for (size_t i = 0; i < upperText.length(); i++)
    {
        upperText[i] = toupper(upperText[i]);
    }

    // First draw a black outline for better visibility
    for (size_t i = 0; i < upperText.length(); i++)
    {
        // Draw black outline
        DrawCharacter(charX - 1, charY - 1, upperText[i], 0.0f, 0.0f, 0.0f);
        DrawCharacter(charX + 1, charY - 1, upperText[i], 0.0f, 0.0f, 0.0f);
        DrawCharacter(charX - 1, charY + 1, upperText[i], 0.0f, 0.0f, 0.0f);
        DrawCharacter(charX + 1, charY + 1, upperText[i], 0.0f, 0.0f, 0.0f);

        // Move to next character position
        charX += (charWidth + charSpacing);
    }

    // Reset for the colored text
    charX = x;

    // Now draw the actual colored text on top
    for (size_t i = 0; i < upperText.length(); i++)
    {
        // Use the specified color, or default to bright yellow if no color specified
        float useR = (r > 0.0f) ? r : 1.0f;
        float useG = (g > 0.0f) ? g : 1.0f;
        float useB = (b > 0.0f) ? b : 0.0f;

        // Draw the character with the specified color
        DrawCharacter(charX, charY, upperText[i], useR, useG, useB);

        // Move to next character position with proper spacing
        charX += (charWidth + charSpacing);
    }

    glDisable(GL_BLEND);

    // Restore 3D projection
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

// Resize window and update OpenGL viewport
void ResizeWindow(int width, int height)
{
    // Update current dimensions
    currentWidth = width;
    currentHeight = height;

    // Update OpenGL viewport
    glViewport(0, 0, width, height);

    // Update projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 0.1, 1000.0);

    // Switch back to modelview matrix
    glMatrixMode(GL_MODELVIEW);
}

// Toggle between fullscreen and windowed mode
void ToggleFullscreen()
{
    if (!isFullscreen)
    {
        // Store current window position and size
        GetWindowRect(hWnd, &windowedRect);

        // Switch to fullscreen mode
        DEVMODE dmScreenSettings;
        memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
        dmScreenSettings.dmSize = sizeof(dmScreenSettings);
        dmScreenSettings.dmPelsWidth = GetSystemMetrics(SM_CXSCREEN);
        dmScreenSettings.dmPelsHeight = GetSystemMetrics(SM_CYSCREEN);
        dmScreenSettings.dmBitsPerPel = 32;
        dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        // Apply fullscreen settings
        if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) == DISP_CHANGE_SUCCESSFUL)
        {
            // Change window style to borderless
            SetWindowLong(hWnd, GWL_STYLE, WS_POPUP);
            SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_APPWINDOW);

            // Set window position and size to cover the entire screen
            SetWindowPos(hWnd, HWND_TOP, 0, 0,
                         GetSystemMetrics(SM_CXSCREEN),
                         GetSystemMetrics(SM_CYSCREEN),
                         SWP_SHOWWINDOW);

            // Update window dimensions
            ResizeWindow(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));

            isFullscreen = true;
        }
    }
    else
    {
        // Switch back to windowed mode
        ChangeDisplaySettings(NULL, 0);

        // Restore window style
        SetWindowLong(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
        SetWindowLong(hWnd, GWL_EXSTYLE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

        // Restore window position and size
        SetWindowPos(hWnd, HWND_TOP,
                     windowedRect.left, windowedRect.top,
                     windowedRect.right - windowedRect.left,
                     windowedRect.bottom - windowedRect.top,
                     SWP_SHOWWINDOW);

        // Update window dimensions
        ResizeWindow(windowedRect.right - windowedRect.left, windowedRect.bottom - windowedRect.top);

        isFullscreen = false;
    }
}
