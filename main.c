#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <stdbool.h>


//STRUCTURE

typedef struct {
    int type; //type of coefficients ('1' for float and '2' for complex)
    int len; //length of linear form
    void* coef; //coefficients
}l_form; //linear form

//HELPFUL FUNCTIONS

int max_of_two (int a, int b) { //maximum of 2 numbers
    if (a >= b) {
        return a;
    }
    else {
        return b;
    }
}

int coef_type() { //type of coefficients choice
    printf("Please choose type of elements' coefficients:\n");
    printf("(type '1' for float or '2' for complex)\n");

    int type_choice;

    do {
        scanf("%d", &type_choice);
        if ((type_choice != 1) && (type_choice != 2)) {
            printf("Please type '1' or '2'\n");
        }
    } while ((type_choice != 1) && (type_choice != 2));

    printf("\n");
    return type_choice;
}

void create_linear_form(l_form *lin, int t) { //creation of linear form
    int l;
    double cur, re, im;

    lin->type = t;

    printf("Please, type linear form length:");
    scanf("%d", &l);
    lin->len = l;


    printf("Please, type linear form coefficients\n");

    if (lin->type == 1) {
        lin->coef = malloc(lin->len * sizeof(double));
        for (int i = 0; i < lin->len; i++) {
            printf("x%d coefficient:", i);
            scanf("%lf", &cur);
            ((double*)lin->coef)[i] = cur;
        }
    }
    else {
        lin->coef = malloc(lin->len * sizeof(double complex));
        for (int i = 0; i < lin->len; i++) {
            printf("x%d coefficient:", i);
            scanf("%lf %lf", &re, &im);
            ((double complex*)lin->coef)[i] = re + im*I;
        }
    }
}

void show_linear_form (l_form lin, int t) { //visualisation of linear form
    printf("Obtained linear form:");
    if (t == 1) {
        for (int i = 0; i < lin.len - 1; i++) {
            if (((double*)lin.coef)[i] != 0) {
                if (((double*)lin.coef)[i] > 0) {
                    printf("%lfx%d + ", ((double*)lin.coef)[i], i);
                }
                else {
                    printf("(%lf)x%d + ", ((double*)lin.coef)[i], i);
                }
            }
        }
        if (((double*)lin.coef)[lin.len - 1] > 0) {
            printf("%lfx%d", ((double*)lin.coef)[lin.len - 1], lin.len - 1);
        }
        else {
            printf("(%lf)x%d", ((double*)lin.coef)[lin.len - 1], lin.len - 1);
        }
    }
    else {
        for (int i = 0; i < lin.len - 1; i++) {
            if (((double complex*)lin.coef)[i] != 0) {
                if (cimag(((double complex*)lin.coef)[i]) >= 0) {
                    printf("(%lf+%lfi)x%d + ", creal(((double complex*)lin.coef)[i]), cimag(((double complex*)lin.coef)[i]), i);
                }
                else {
                    printf("(%lf%lfi)x%d + ", creal(((double complex*)lin.coef)[i]), cimag(((double complex*)lin.coef)[i]), i);
                }
            }
        }
        if (cimag(((double complex*)lin.coef)[lin.len - 1]) >= 0) {
            printf("(%lf+%lfi)x%d", creal(((double complex*)lin.coef)[lin.len - 1]), cimag(((double complex*)lin.coef)[lin.len - 1]), lin.len - 1);
        }
        else {
            printf("(%lf%lfi)x%d", creal(((double complex*)lin.coef)[lin.len - 1]), cimag(((double complex*)lin.coef)[lin.len - 1]), lin.len - 1);
        }
    }
}

//TESTS FUNCTIONS

bool check_add(l_form *lin1, l_form *lin2, l_form *lin3) {
    double eps = 0.000001;

    if (max_of_two(lin1->len, lin2->len) != lin3->len) return false;

    if (lin3->type == 1) {
        for (int i = 0; i < lin3->len; i++) {
            if (i > lin1->len - 1) {
                if (((double*)lin2->coef)[i] - ((double*)lin3->coef)[i] >= eps) return false;
            }
            else if (i > lin2->len - 1) {
                if (((double*)lin1->coef)[i] - ((double*)lin3->coef)[i] >= eps) return false;
            }
            else {
                if (((double*)lin1->coef)[i] + ((double*)lin2->coef)[i] - ((double*)lin3->coef)[i] >= eps) return false;
            }
        }
    }
    else {
        for (int i = 0; i < lin3->len; i++) {
            if (i > lin1->len - 1) {
                if (((double complex*)lin2->coef)[i] != ((double complex*)lin3->coef)[i]) return false;
            }
            else if (i > lin2->len - 1) {
                if (((double complex*)lin1->coef)[i] != ((double complex*)lin3->coef)[i]) return false;
            }
            else {
                if (((double complex*)lin1->coef)[i] + ((double complex*)lin2->coef)[i] != ((double complex*)lin3->coef)[i]) return false;
            }
        }
    }

    return true;
}

bool check_sub(l_form *lin1, l_form *lin2, l_form *lin3) {
    double eps = 0.000001;

    if (max_of_two(lin1->len, lin2->len) != lin3->len) return false;

    if (lin3->type == 1) {
        for (int i = 0; i < lin3->len; i++) {
            if (i > lin1->len - 1) {
                if (((double*)lin2->coef)[i]*(-1) - ((double*)lin3->coef)[i] >= eps) return false;
            }
            else if (i > lin2->len - 1) {
                if (((double*)lin1->coef)[i] - ((double*)lin3->coef)[i] >= eps) return false;
            }
            else {
                if (((double*)lin1->coef)[i] - ((double*)lin2->coef)[i] - ((double*)lin3->coef)[i] >= eps) return false;
            }
        }
    }
    else {
        for (int i = 0; i < lin3->len; i++) {
            if (i > lin1->len - 1) {
                if (((double complex*)lin2->coef)[i]*(-1) != ((double complex*)lin3->coef)[i]) return false;
            }
            else if (i > lin2->len - 1) {
                if (((double complex*)lin1->coef)[i] != ((double complex*)lin3->coef)[i]) return false;
            }
            else {
                if (((double complex*)lin1->coef)[i] - ((double complex*)lin2->coef)[i] != ((double complex*)lin3->coef)[i]) return false;
            }
        }
    }

    return true;
}

bool check_float_mult(l_form *lin1, double scalar, l_form *lin2) {
    double eps = 0.000001;

    if (lin1->type != lin2->type) return false;
    if (lin1->len != lin2->len) return false;

    for (int i = 0; i < lin1->len; i++) {
        if (((double*)lin1->coef)[i] * scalar - ((double*)lin2->coef)[i] >= eps) return false;
    }

    return true;
}

bool check_complex_mult(l_form *lin1, double complex scalar, l_form *lin2) {
    if (lin1->type != lin2->type) return false;
    if (lin1->len != lin2->len) return false;

    for (int i = 0; i < lin1->len; i++) {
        if (((double complex*)lin1->coef)[i] * scalar != ((double complex*)lin2->coef)[i]) return false;
    }

    return true;
}

bool check_float_val(l_form *lin, double x0, double x1, double x2, double x3, double x4, double val) {
    double eps = 0.000001;

    if ((((double*)lin->coef)[0] * x0 + ((double*)lin->coef)[1] * x1 + ((double*)lin->coef)[2] * x2 + ((double*)lin->coef)[3] * x3 + ((double*)lin->coef)[4] * x4) - val >= eps) return false;

    return true;
}

bool check_complex_val(l_form *lin, double complex x0, double complex x1, double complex x2, double complex val) {
    if ((((double complex*)lin->coef)[0] * x0 + ((double complex*)lin->coef)[1] * x1 + ((double complex*)lin->coef)[2] * x2) != val) return false;

    return true;
}

void float_test() {
    l_form lin1, lin2, linadd, linsub, linmult;

    double x0 = 3.2;
    double x1 = 2.5;
    double x2 = -6.1;
    double x3 = -2.2;
    double x4 = 1.9;
    double scalar = 3.3;
    double val = 0.37;

    lin1.type = 1;
    lin2.type = 1;
    linadd.type = 1;
    linsub.type = 1;
    linmult.type = 1;

    lin1.len = 5;
    lin2.len = 3;
    linadd.len = 5;
    linsub.len = 5;
    linmult.len = 5;

    lin1.coef = malloc(lin1.len * sizeof(double));
    lin2.coef = malloc(lin2.len * sizeof(double));
    linadd.coef = malloc(linadd.len * sizeof(double));
    linsub.coef = malloc(linsub.len * sizeof(double));
    linmult.coef = malloc(linmult.len * sizeof(double));

    ((double*)lin1.coef)[0] = 4.3;
    ((double*)lin1.coef)[1] = 0;
    ((double*)lin1.coef)[2] = -1.7;
    ((double*)lin1.coef)[3] = 5.1;
    ((double*)lin1.coef)[4] = -6.6;

    ((double*)lin2.coef)[0] = 1.2;
    ((double*)lin2.coef)[1] = 3.7;
    ((double*)lin2.coef)[2] = -2.8;

    ((double*)linadd.coef)[0] = 5.5;
    ((double*)linadd.coef)[1] = 3.7;
    ((double*)linadd.coef)[2] = -4.5;
    ((double*)linadd.coef)[3] = 5.1;
    ((double*)linadd.coef)[4] = -6.6;

    ((double*)linsub.coef)[0] = 3.1;
    ((double*)linsub.coef)[1] = -3.7;
    ((double*)linsub.coef)[2] = 1.1;
    ((double*)linsub.coef)[3] = 5.1;
    ((double*)linsub.coef)[4] = -6.6;

    ((double*)linmult.coef)[0] = 14.19;
    ((double*)linmult.coef)[1] = 0;
    ((double*)linmult.coef)[2] = -5.61;
    ((double*)linmult.coef)[3] = 16.83;
    ((double*)linmult.coef)[4] = -21.78;

    if (check_add(&lin1, &lin2, &linadd)) printf("Add succeed\n");
    else printf("Add failed\n");

    if (check_sub(&lin1, &lin2, &linsub)) printf("Sub succeed\n");
    else printf("Sub failed\n");

    if (check_float_mult(&lin1, scalar, &linmult)) printf("Mult succeed\n");
    else printf("Mult failed\n");

    if (check_float_val(&lin1, x0, x1, x2, x3, x4, val)) printf("Value succeed\n");
    else printf("Value failed\n");
}

void complex_test() {
    l_form lin1, lin2, linadd, linsub, linmult;

    double complex x0 = 1 + 2*I;
    double complex x1 = 5 + (-4)*I;
    double complex x2 = -2 + 0*I;
    double complex scalar = -3 + 4*I;
    double complex val = 0 + 27*I;

    lin1.type = 2;
    lin2.type = 2;
    linadd.type = 2;
    linsub.type = 2;
    linmult.type = 2;

    lin1.len = 3;
    lin2.len = 5;
    linadd.len = 5;
    linsub.len = 5;
    linmult.len = 3;

    lin1.coef = malloc(lin1.len * sizeof(double complex));
    lin2.coef = malloc(lin2.len * sizeof(double complex));
    linadd.coef = malloc(linadd.len * sizeof(double complex));
    linsub.coef = malloc(linsub.len * sizeof(double complex));
    linmult.coef = malloc(linmult.len * sizeof(double complex));

    ((double complex*)lin1.coef)[0] = 5 + 3*I;
    ((double complex*)lin1.coef)[1] = 1 + 2*I;
    ((double complex*)lin1.coef)[2] = 6 + (-4)*I;

    ((double complex*)lin2.coef)[0] = 2 + (-1)*I;
    ((double complex*)lin2.coef)[1] = 7 + 0*I;
    ((double complex*)lin2.coef)[2] = 0 + 9*I;
    ((double complex*)lin2.coef)[3] = 0 + 0*I;
    ((double complex*)lin2.coef)[4] = -4 + (-7)*I;

    ((double complex*)linadd.coef)[0] = 7 + 2*I;
    ((double complex*)linadd.coef)[1] = 8 + 2*I;
    ((double complex*)linadd.coef)[2] = 6 + 5*I;
    ((double complex*)linadd.coef)[3] = 0 + 0*I;
    ((double complex*)linadd.coef)[4] = -4 + (-7)*I;

    ((double complex*)linsub.coef)[0] = 3 + 4*I;
    ((double complex*)linsub.coef)[1] = -6 + 2*I;
    ((double complex*)linsub.coef)[2] = 6 + (-13)*I;
    ((double complex*)linsub.coef)[3] = 0 + 0*I;
    ((double complex*)linsub.coef)[4] = 4 + 7*I;

    ((double complex*)linmult.coef)[0] = -27 + 11*I;
    ((double complex*)linmult.coef)[1] = -11 + (-2)*I;
    ((double complex*)linmult.coef)[2] = -2 + (36)*I;

    if (check_add(&lin1, &lin2, &linadd)) printf("Add succeed\n");
    else printf("Add failed\n");

    if (check_sub(&lin1, &lin2, &linsub)) printf("Sub succeed\n");
    else printf("Sub failed\n");

    if (check_complex_mult(&lin1, scalar, &linmult)) printf("Mult succeed\n");
    else printf("Mult failed\n");

    if (check_complex_val(&lin1, x0, x1, x2, val)) printf("Value succeed\n");
    else printf("Value failed\n");
}

//MAIN FUNCTIONS

void add (int t) { //addition of 2 linear forms
    l_form lin1, lin2, lin3; //lin1+lin2=lin3

    create_linear_form(&lin1, t);
    create_linear_form(&lin2, t);

    lin3.type = t;
    lin3.len = max_of_two(lin1.len, lin2.len);

    if (lin3.type == 1) {
        lin3.coef = malloc(lin3.len * sizeof(double));
        for (int i = 0; i < lin3.len; i++) {
            if (i > lin1.len - 1) {
                ((double*)lin3.coef)[i] = ((double*)lin2.coef)[i];
            }
            else if (i > lin2.len - 1) {
                ((double*)lin3.coef)[i] = ((double*)lin1.coef)[i];
            }
            else {
                ((double*)lin3.coef)[i] = ((double*)lin1.coef)[i] + ((double*)lin2.coef)[i];
            }
        }
    }
    else {
        lin3.coef = malloc(lin3.len * sizeof(double complex));
        for (int i = 0; i < lin3.len; i++) {
            if (i > lin1.len - 1) {
                ((double complex*)lin3.coef)[i] = ((double complex*)lin2.coef)[i];
            }
            else if (i > lin2.len - 1) {
                ((double complex*)lin3.coef)[i] = ((double complex*)lin1.coef)[i];
            }
            else {
                ((double complex*)lin3.coef)[i] = ((double complex*)lin1.coef)[i] + ((double complex*)lin2.coef)[i];
            }
        }
    }
    show_linear_form(lin3, lin3.type);
    printf("\n");
}

void sub (int t) { //subtraction of 2 linear forms
    l_form lin1, lin2, lin3; //lin1-lin2=lin3

    create_linear_form(&lin1, t);
    create_linear_form(&lin2, t);

    lin3.type = t;
    lin3.len = max_of_two(lin1.len, lin2.len);

    if (lin3.type == 1) {
        lin3.coef = malloc(lin3.len * sizeof(double));
        for (int i = 0; i < lin3.len; i++) {
            if (i > lin1.len - 1) {
                ((double*)lin3.coef)[i] = ((double*)lin2.coef)[i];
            }
            else if (i > lin2.len - 1) {
                ((double*)lin3.coef)[i] = ((double*)lin1.coef)[i];
            }
            else {
                ((double*)lin3.coef)[i] = ((double*)lin1.coef)[i] - ((double*)lin2.coef)[i];
            }
        }
    }
    else {
        lin3.coef = malloc(lin3.len * sizeof(double complex));
        for (int i = 0; i < lin3.len; i++) {
            if (i > lin1.len - 1) {
                ((double complex*)lin3.coef)[i] = (-1)*((double complex*)lin2.coef)[i];
            }
            else if (i > lin2.len - 1) {
                ((double complex*)lin3.coef)[i] = ((double complex*)lin1.coef)[i];
            }
            else {
                ((double complex*)lin3.coef)[i] = ((double complex*)lin1.coef)[i] - ((double complex*)lin2.coef)[i];
            }
        }
    }
    show_linear_form(lin3, lin3.type);
    printf("\n");
}

void mult (int t) { //multiplication of linear form by scalar
    l_form lin;
    double float_scalar, re, im;
    double complex complex_scalar;

    create_linear_form(&lin, t);

    if (lin.type == 1) {
        printf("Please, type float scalar:");
        scanf("%lf", &float_scalar);
        for (int i = 0; i < lin.len; i++) {
            ((double*)lin.coef)[i] *= float_scalar;
        }
    }
    else {
        printf("Please, type complex scalar:");
        scanf("%lf %lf", &re, &im);
        complex_scalar = re + im*I;
        for (int i = 0; i < lin.len; i++) {
            ((double complex*)lin.coef)[i] *= complex_scalar;
        }
    }
    show_linear_form(lin, lin.type);
    printf("\n");
}

void value (int t) { //calculation of linear form's value
    l_form lin;
    double float_cur, re, im, float_val = 0;
    double complex complex_cur, complex_val = 0;

    create_linear_form(&lin, t);

    if (lin.type == 1) {
        printf("Please, type float variable values\n");
        for (int i = 0; i < lin.len; i++) {
            printf("x%d:", i);
            scanf("%lf", &float_cur);
            float_val += ((double*)lin.coef)[i] * float_cur;
        }
        printf("Linear form value:%lf", float_val);
    }
    else {
        printf("Please, type complex variable values\n");
        for (int i = 0; i < lin.len; i++) {
            printf("x%d:", i);
            scanf("%lf %lf", &re, &im);
            complex_cur = re + im*I;
            complex_val += ((double complex*)lin.coef)[i] * complex_cur;
        }
        printf("Linear form value:%lf+%lfi", creal(complex_val), cimag(complex_val));
        printf("\n");
    }
}

int main() {
    int type_of_coefficients = coef_type();
    int choice;

    printf("Please, choose the operation:\n\n");
    printf("1) Addition of two linear forms\n");
    printf("2) Subtraction of two linear forms\n");
    printf("3) Multiplication of linear form by scalar\n");
    printf("4) Calculation of linear form value\n");
    printf("5) Check tests\n\n");
    printf("Type '1', '2', '3', '4' or '5'\n");

    do {
        scanf("%d", &choice);
        printf("\n");
        if ((choice != 1) && (choice != 2) && (choice != 3) && (choice != 4) && (choice != 5)) {
            printf("Type '1', '2', '3', '4' or '5'\n");
        }
    } while ((choice != 1) && (choice != 2) && (choice != 3) && (choice != 4) && (choice != 5));

    switch (choice) {
        case 1:
            add(type_of_coefficients);
            break;
        case 2:
            sub(type_of_coefficients);
            break;
        case 3:
            mult(type_of_coefficients);
            break;
        case 4:
            value(type_of_coefficients);
            break;
        case 5:
            if (type_of_coefficients == 1) {
                float_test();
            }
            else {
                complex_test();
            }
        default:
            break;
    }

    return 0;
}
