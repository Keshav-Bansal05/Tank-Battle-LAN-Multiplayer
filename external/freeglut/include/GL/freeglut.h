#ifndef __FREEGLUT_H__
#define __FREEGLUT_H__

/*
 * freeglut.h
 *
 * The freeglut library include file
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PAWEL W. OLSZTA BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

/* The freeglut and GLUT API versions */
#define  FREEGLUT             1
#define  GLUT_API_VERSION     4
#define  GLUT_XLIB_IMPLEMENTATION 13

/* Simple stub for freeglut - this is just a placeholder */

/* Basic callbacks */
void glutDisplayFunc(void (*func)(void));
void glutReshapeFunc(void (*func)(int width, int height));
void glutKeyboardFunc(void (*func)(unsigned char key, int x, int y));
void glutKeyboardUpFunc(void (*func)(unsigned char key, int x, int y));
void glutSpecialFunc(void (*func)(int key, int x, int y));
void glutSpecialUpFunc(void (*func)(int key, int x, int y));
void glutMouseFunc(void (*func)(int button, int state, int x, int y));
void glutMotionFunc(void (*func)(int x, int y));
void glutPassiveMotionFunc(void (*func)(int x, int y));
void glutIdleFunc(void (*func)(void));

/* Window management */
int glutCreateWindow(const char *title);
void glutInitWindowSize(int width, int height);
void glutInitDisplayMode(unsigned int mode);
void glutMainLoop(void);
void glutPostRedisplay(void);
void glutSwapBuffers(void);

/* Initialization */
void glutInit(int *argcp, char **argv);

/* Special keys */
#define GLUT_KEY_F1                        0x0001
#define GLUT_KEY_F2                        0x0002
#define GLUT_KEY_F3                        0x0003
#define GLUT_KEY_F4                        0x0004
#define GLUT_KEY_F5                        0x0005
#define GLUT_KEY_F6                        0x0006
#define GLUT_KEY_F7                        0x0007
#define GLUT_KEY_F8                        0x0008
#define GLUT_KEY_F9                        0x0009
#define GLUT_KEY_F10                       0x000A
#define GLUT_KEY_F11                       0x000B
#define GLUT_KEY_F12                       0x000C
#define GLUT_KEY_LEFT                      0x0064
#define GLUT_KEY_UP                        0x0065
#define GLUT_KEY_RIGHT                     0x0066
#define GLUT_KEY_DOWN                      0x0067
#define GLUT_KEY_PAGE_UP                   0x0068
#define GLUT_KEY_PAGE_DOWN                 0x0069
#define GLUT_KEY_HOME                      0x006A
#define GLUT_KEY_END                       0x006B
#define GLUT_KEY_INSERT                    0x006C

/* Mouse buttons */
#define GLUT_LEFT_BUTTON                   0x0000
#define GLUT_MIDDLE_BUTTON                 0x0001
#define GLUT_RIGHT_BUTTON                  0x0002
#define GLUT_DOWN                          0x0000
#define GLUT_UP                            0x0001

/* Display mode */
#define GLUT_RGB                           0x0000
#define GLUT_RGBA                          0x0000
#define GLUT_DOUBLE                        0x0002
#define GLUT_DEPTH                         0x0010

/* Shapes */
void glutSolidCube(GLdouble size);
void glutWireCube(GLdouble size);
void glutSolidSphere(GLdouble radius, GLint slices, GLint stacks);
void glutWireSphere(GLdouble radius, GLint slices, GLint stacks);
void glutSolidCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
void glutWireCone(GLdouble base, GLdouble height, GLint slices, GLint stacks);
void glutSolidCylinder(GLdouble radius, GLdouble height, GLint slices, GLint stacks);
void glutWireCylinder(GLdouble radius, GLdouble height, GLint slices, GLint stacks);

#endif /* __FREEGLUT_H__ */
