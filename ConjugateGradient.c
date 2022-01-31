#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main()
{
    double x = (-1.5), y = (-1);
    double x_new, y_new, fk;
    double d0 = -(-400*x*y + 400*x*x*x - 2 + 2*x);
    double d1 = -(200*y - 200*x*x);
    double alpha, sigma = 0.05, rho = 0.001523, epsilon = 4;
    double gradx = -(-400*x*y + 400*x*x*x - 2 + 2*x);
    double grady = -(200*y - 200*x*x);
    double bk, gradx_old, grady_old;
    unsigned short int stop = 0, iter = 0;
    while (stop == 0)
    {
        iter = iter + 1;
        alpha = 1;
        x_new = x + alpha*d0;
        y_new = y + alpha*d1;
        fk = ((100 * (y-x*x) * (y-x*x)) + ((1-x) * (1-x)));
        while (((100 * (y_new-x_new*x_new) * (y_new-x_new*x_new)) + ((1-x) * (1-x))) > (fk + sigma*alpha*(gradx*(-gradx)+grady*(-grady))))
        {
            alpha = alpha*rho;
            x_new = x + alpha*d0;
            y_new = y + alpha*d1;
        }
        x = x_new;
        y = y_new;
        gradx_old = gradx;
        grady_old = grady;
        gradx = -(-400*x*y + 400*x*x*x - 2 + 2*x);
        grady = -(200*y - 200*x*x);
        if ((fabs(gradx) < epsilon) && (fabs(grady) < epsilon))
        {
            stop = 1;
        }
        if (iter > 10000)
        {
            stop = 1;
        }
        bk = (gradx * gradx + grady * grady)/(gradx_old * gradx_old + grady_old * grady_old);
        d0 = gradx + bk*d0;
        d1 = grady + bk*d1;
    }
    printf("X value: %f \n",x);
    printf("Y value: %f \n",y);
    printf("Number of iterations: %i \n",iter);
    return 0;
}
