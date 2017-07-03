#ifndef __MATRIX_H
#define __MATRIX_H

struct Matrix
{
    double m[4][4];

    /*

       m[0][0-2] = x-axis
       m[1][0-2] = y-axis
       m[2][0-2] = z-axis
       m[3][0-2] = position (origin)

       m[0][3] = 0.0
       m[1][3] = 0.0
       m[2][3] = 0.0
       m[3][3] = 1.0

*/

    void Identity();
    void MultToGl();

    void SetRotation(const Vector& axis, double angle);
    void MoveTo(double x, double y, double z)                                { m[3][0] = x; m[3][1] = y; m[3][2] = z; };
    double PosX()                                                            { return m[3][0]; };
    double PosY()                                                            { return m[3][1]; };
    double PosZ()                                                            { return m[3][2]; };
    void PosX(double x)                                                      { m[3][0] = x; };
    void PosY(double y)                                                      { m[3][1] = y; };
    void PosZ(double z)                                                      { m[3][2] = z; };
};

Matrix operator*(const Matrix& m1, const Matrix& m2);
Vector operator*(const Matrix& m, const Vector& v);


/*

   /a b c\   /1 2 3\   /11 12 13\
   |d e f| = |4 5 6| * |14 15 16|
   \g h i/   \7 8 9/   \17 18 19/


   a = 1 * 11 + 4 * 12 + 7 * 13;
   b = 2 * 11 + 5 * 12 + 8 * 13;

   f = 3 * 14 + 6 * 15 + 9 * 16;

   /1 2 3\   /a\
   (a b c) = |4 5 6| * |d|
   \7 8 9/   \g/


   a = 1 * a + 2 * d + 3 * g;
   b = 4 * a + 5 * d + 6 * g;
   c = 7 * a + 8 * d + 9 * g;

*/

#endif // __MATRIX_H
