// RUN: %cladclang %s -lm -I%S/../../include -oGradients.out 2>&1 | FileCheck %s
// RUN: ./Gradients.out | FileCheck -check-prefix=CHECK-EXEC %s

//CHECK-NOT: {{.*error|warning|note:.*}}

#include "clad/Differentiator/Differentiator.h"
#include <cmath>

double f_add1(double x, double y) {
  return x + y;
}

// CHECK: void f_add1_grad(double x, double y, double *_result) {
// CHECK-NEXT:   _result[0UL] += 1;
// CHECK-NEXT:   _result[1UL] += 1;
// CHECK-NEXT: }

void f_add1_grad(double x, double y, double *_result);

double f_add2(double x, double y) {
  return 3*x + 4*y;
}

// CHECK: void f_add2_grad(double x, double y, double *_result) {
// CHECK-NEXT:     double _t0 = 1 * x;
// CHECK-NEXT:     double _t1 = 3 * 1;
// CHECK-NEXT:     _result[0UL] += _t1;
// CHECK-NEXT:     double _t2 = 1 * y;
// CHECK-NEXT:     double _t3 = 4 * 1;
// CHECK-NEXT:     _result[1UL] += _t3;
// CHECK-NEXT: }

void f_add2_grad(double x, double y, double *_result);

double f_add3(double x, double y) {
  return 3*x + 4*y*4;
}

// CHECK: void f_add3_grad(double x, double y, double *_result) {
// CHECK-NEXT:     double _t0 = 1 * x;
// CHECK-NEXT:     double _t1 = 3 * 1;
// CHECK-NEXT:     _result[0UL] += _t1;
// CHECK-NEXT:     double _t2 = 1 * 4;
// CHECK-NEXT:     double _t3 = _t2 * y;
// CHECK-NEXT:     double _t4 = 4 * _t2;
// CHECK-NEXT:     _result[1UL] += _t4;
// CHECK-NEXT:     double _t5 = 4 * y * 1;
// CHECK-NEXT: }

void f_add3_grad(double x, double y, double *_result);

double f_sub1(double x, double y) {
  return x - y;
}

// CHECK: void f_sub1_grad(double x, double y, double *_result) {
// CHECK-NEXT:   _result[0UL] += 1;
// CHECK-NEXT:   _result[1UL] += -1;
// CHECK-NEXT: }
void f_sub1_grad(double x, double y, double *_result);

double f_sub2(double x, double y) {
  return 3*x - 4*y;
}

// CHECK: void f_sub2_grad(double x, double y, double *_result) {
// CHECK-NEXT:     double _t0 = 1 * x;
// CHECK-NEXT:     double _t1 = 3 * 1;
// CHECK-NEXT:     _result[0UL] += _t1;
// CHECK-NEXT:     double _t2 = -1 * y;
// CHECK-NEXT:     double _t3 = 4 * -1;
// CHECK-NEXT:     _result[1UL] += _t3;
// CHECK-NEXT: }

void f_sub2_grad(double x, double y, double *_result);

double f_mult1(double x, double y) {
  return x*y;
}

// CHECK: void f_mult1_grad(double x, double y, double *_result) {
// CHECK-NEXT:    double _t0 = 1 * y;
// CHECK-NEXT:    _result[0UL] += _t0;
// CHECK-NEXT:    double _t1 = x * 1;
// CHECK-NEXT:    _result[1UL] += _t1;
// CHECK-NEXT: }

void f_mult1_grad(double x, double y, double *_result);

double f_mult2(double x, double y) {
   return 3*x*4*y;
}

// CHECK: void f_mult2_grad(double x, double y, double *_result) {
// CHECK-NEXT:    double _t0 = 1 * y;
// CHECK-NEXT:    double _t1 = _t0 * 4;
// CHECK-NEXT:    double _t2 = _t1 * x;
// CHECK-NEXT:    double _t3 = 3 * _t1;
// CHECK-NEXT:    _result[0UL] += _t3;
// CHECK-NEXT:    double _t4 = 3 * x * _t0;
// CHECK-NEXT:    double _t5 = 3 * x * 4 * 1;
// CHECK-NEXT:    _result[1UL] += _t5;
// CHECK-NEXT: }

void f_mult2_grad(double x, double y, double *_result);

double f_div1(double x, double y) {
  return x/y;
}

// CHECK: void f_div1_grad(double x, double y, double *_result) {
// CHECK-NEXT:    double _t0 = 1 / y;
// CHECK-NEXT:    _result[0UL] += _t0;
// CHECK-NEXT:    double _t1 = 1 * -x / (y * y);
// CHECK-NEXT:    _result[1UL] += _t1;
// CHECK-NEXT: }

void f_div1_grad(double x, double y, double *_result);

double f_div2(double x, double y) {
  return 3*x/(4*y);
}

// CHECK: void f_div2_grad(double x, double y, double *_result) {
// CHECK-NEXT:    double _t0 = 1 / (4 * y);
// CHECK-NEXT:    double _t1 = _t0 * x;
// CHECK-NEXT:    double _t2 = 3 * _t0;
// CHECK-NEXT:    _result[0UL] += _t2;
// CHECK-NEXT:    double _t3 = 1 * -3 * x / ((4 * y) * (4 * y));
// CHECK-NEXT:    double _t4 = _t3 * y;
// CHECK-NEXT:    double _t5 = 4 * _t3;
// CHECK-NEXT:    _result[1UL] += _t5;
// CHECK-NEXT: }

void f_div2_grad(double x, double y, double *_result);

double f_c(double x, double y) {
  return -x*y + (x + y)*(x/y) - x*x; 
}

// CHECK: void f_c_grad(double x, double y, double *_result) {
// CHECK-NEXT:    double _t0 = 1 * y;
// CHECK-NEXT:    _result[0UL] += -_t0;
// CHECK-NEXT:    double _t1 = -x * 1;
// CHECK-NEXT:    _result[1UL] += _t1;
// CHECK-NEXT:    double _t2 = 1 * (x / y);
// CHECK-NEXT:    _result[0UL] += _t2;
// CHECK-NEXT:    _result[1UL] += _t2;
// CHECK-NEXT:    double _t3 = (x + y) * 1;
// CHECK-NEXT:    double _t4 = _t3 / y;
// CHECK-NEXT:    _result[0UL] += _t4;
// CHECK-NEXT:    double _t5 = _t3 * -x / (y * y);
// CHECK-NEXT:    _result[1UL] += _t5;
// CHECK-NEXT:    double _t6 = -1 * x;
// CHECK-NEXT:    _result[0UL] += _t6;
// CHECK-NEXT:    double _t7 = x * -1;
// CHECK-NEXT:    _result[0UL] += _t7;
// CHECK-NEXT: }

void f_c_grad(double x, double y, double *_result);

double f_rosenbrock(double x, double y) {
  return (x - 1) * (x - 1) + 100 * (y - x * x) * (y - x * x);
}

// CHECK: void f_rosenbrock_grad(double x, double y, double *_result) {
// CHECK-NEXT:     double _t0 = 1 * (x - 1);
// CHECK-NEXT:     _result[0UL] += _t0;
// CHECK-NEXT:     double _t1 = (x - 1) * 1;
// CHECK-NEXT:     _result[0UL] += _t1;
// CHECK-NEXT:     double _t2 = 1 * (y - x * x);
// CHECK-NEXT:     double _t3 = _t2 * (y - x * x);
// CHECK-NEXT:     double _t4 = 100 * _t2;
// CHECK-NEXT:     _result[1UL] += _t4;
// CHECK-NEXT:     double _t5 = -_t4 * x;
// CHECK-NEXT:     _result[0UL] += _t5;
// CHECK-NEXT:     double _t6 = x * -_t4;
// CHECK-NEXT:     _result[0UL] += _t6;
// CHECK-NEXT:     double _t7 = 100 * (y - x * x) * 1;
// CHECK-NEXT:     _result[1UL] += _t7;
// CHECK-NEXT:     double _t8 = -_t7 * x;
// CHECK-NEXT:     _result[0UL] += _t8;
// CHECK-NEXT:     double _t9 = x * -_t7;
// CHECK-NEXT:     _result[0UL] += _t9;
// CHECK-NEXT: }

void f_rosenbrock_grad(double x, double y, double *_result);

double f_cond1(double x, double y) {
  return (x > y ? x : y);
}

// CHECK: void f_cond1_grad(double x, double y, double *_result) {
// CHECK-NEXT:     _Bool _t0 = x > y;
// CHECK-NEXT:     _result[0UL] += (_t0 ? 1 : 0);
// CHECK-NEXT:     _result[1UL] += (_t0 ? 0 : 1);
// CHECK-NEXT: }

void f_cond1_grad(double x, double y, double *_result);

double f_cond2(double x, double y) {
  return (x > y ? x : (y > 0 ? y : -y));
}

// CHECK: void f_cond2_grad(double x, double y, double *_result) {
// CHECK-NEXT:     _Bool _t0 = x > y;
// CHECK-NEXT:     _result[0UL] += (_t0 ? 1 : 0);
// CHECK-NEXT:     _Bool _t1 = y > 0;
// CHECK-NEXT:     _result[1UL] += (_t1 ? (_t0 ? 0 : 1) : 0);
// CHECK-NEXT:     _result[1UL] += -(_t1 ? 0 : (_t0 ? 0 : 1));
// CHECK-NEXT: }

void f_cond2_grad(double x, double y, double *_result);

double f_cond3(double x, double c) {
  return (c > 0 ? x + c : x - c);
}

// CHECK: void f_cond3_grad(double x, double c, double *_result) {
// CHECK-NEXT:     _Bool _t0 = c > 0;
// CHECK-NEXT:     _result[0UL] += (_t0 ? 1 : 0);
// CHECK-NEXT:     _result[1UL] += (_t0 ? 1 : 0);
// CHECK-NEXT:     _result[0UL] += (_t0 ? 0 : 1);
// CHECK-NEXT:     _result[1UL] += -(_t0 ? 0 : 1);
// CHECK-NEXT: }

double f_cond3_grad(double x, double c, double *_result);

double f_if1(double x, double y) {
  if (x > y)
    return x;
  else
    return y;
}

// CHECK: void f_if1_grad(double x, double y, double *_result) {
// CHECK-NEXT:     if (x > y) {
// CHECK-NEXT:         _result[0UL] += 1;
// CHECK-NEXT:     } else {
// CHECK-NEXT:         _result[1UL] += 1;
// CHECK-NEXT:     }
// CHECK-NEXT: }

double f_if1_grad(double x, double y, double *_result);

double f_if2(double x, double y) {
  if (x > y)
    return x;
  else if (y > 0)
    return y;
  else
    return -y;
}

// CHECK: void f_if2_grad(double x, double y, double *_result) {
// CHECK-NEXT:     if (x > y) {
// CHECK-NEXT:         _result[0UL] += 1;
// CHECK-NEXT:     } else {
// CHECK-NEXT:         if (y > 0) {
// CHECK-NEXT:             _result[1UL] += 1;
// CHECK-NEXT:         } else {
// CHECK-NEXT:             _result[1UL] += -1;
// CHECK-NEXT:         }
// CHECK-NEXT:     }
// CHECK-NEXT: }

void f_if2_grad(double x, double y, double *_result);

struct S {
  double c1;
  double c2;
  double f(double x, double y) {
    return c1 * x + c2 * y;
  }
   
  // CHECK: void f_grad(double x, double y, double *_result) {
  // CHECK-NEXT:   double _t0 = 1 * x;
  // CHECK-NEXT:   double _t1 = this->c1 * 1;
  // CHECK-NEXT:   _result[0UL] += _t1;
  // CHECK-NEXT:   double _t2 = 1 * y;
  // CHECK-NEXT:   double _t3 = this->c2 * 1;
  // CHECK-NEXT:  _result[1UL] += _t3;
  // CHECK-NEXT: }

  void f_grad(double x, double y, double *_result);
};

double sum_of_powers(double x, double y, double z, double p) {
  return std::pow(x, p) + std::pow(y, p) + std::pow(z, p);
}

namespace custom_derivatives {
  void sum_of_powers_grad(double x, double y, double z, double p, double* result) {
    result[0] += pow_darg0(x, p);
    result[3] += pow_darg1(x, p);
    result[1] += pow_darg0(y, p);
    result[3] += pow_darg1(y, p);
    result[2] += pow_darg0(z, p);
    result[3] += pow_darg1(z, p);
  }
}

double f_norm(double x, double y, double z, double d) {
  return std::pow(sum_of_powers(x, y, z, d), 1/d);
}

void f_norm_grad(double x, double y, double z, double d, double* _result);
// CHECK: void f_norm_grad(double x, double y, double z, double d, double *_result) {
// CHECK-NEXT:     double _grad[2] = {};
// CHECK-NEXT:     pow_grad(sum_of_powers(x, y, z, d), 1 / d, _grad);
// CHECK-NEXT:     double _t0 = 1 * _grad[0UL];
// CHECK-NEXT:     double _grad1[4] = {};
// CHECK-NEXT:     custom_derivatives::sum_of_powers_grad(x, y, z, d, _grad1);
// CHECK-NEXT:     double _t2 = _t0 * _grad1[0UL];
// CHECK-NEXT:     _result[0UL] += _t2;
// CHECK-NEXT:     double _t3 = _t0 * _grad1[1UL];
// CHECK-NEXT:     _result[1UL] += _t3;
// CHECK-NEXT:     double _t4 = _t0 * _grad1[2UL];
// CHECK-NEXT:     _result[2UL] += _t4;
// CHECK-NEXT:     double _t5 = _t0 * _grad1[3UL];
// CHECK-NEXT:     _result[3UL] += _t5;
// CHECK-NEXT:     double _t6 = 1 * _grad[1UL];
// CHECK-NEXT:     double _t7 = _t6 / d;
// CHECK-NEXT:     double _t8 = _t6 * -1 / (d * d);
// CHECK-NEXT:     _result[3UL] += _t8;
// CHECK-NEXT: }

double f_sin(double x, double y) {
  return (std::sin(x) + std::sin(y))*(x + y);
}

void f_sin_grad(double x, double y, double* _result);
// CHECK: void f_sin_grad(double x, double y, double *_result) {
// CHECK-NEXT:     double _t0 = 1 * (x + y);
// CHECK-NEXT:     double _t1 = custom_derivatives::sin_darg0(x);
// CHECK-NEXT:     double _t2 = _t0 * _t1;
// CHECK-NEXT:     _result[0UL] += _t2;
// CHECK-NEXT:     double _t3 = custom_derivatives::sin_darg0(y);
// CHECK-NEXT:     double _t4 = _t0 * _t3;
// CHECK-NEXT:     _result[1UL] += _t4;
// CHECK-NEXT:     double _t5 = (std::sin(x) + std::sin(y)) * 1;
// CHECK-NEXT:     _result[0UL] += _t5;
// CHECK-NEXT:     _result[1UL] += _t5;
// CHECK-NEXT: }

unsigned f_types(int x, float y, double z) {
  return x + y + z;
}

// CHECK: void f_types_grad(int x, float y, double z, unsigned int *_result) {
// CHECK-NEXT:   _result[0UL] += 1;
// CHECK-NEXT:   _result[1UL] += 1;
// CHECK-NEXT:   _result[2UL] += 1;
// CHECK-NEXT: }
void f_types_grad(int x, float y, double z, unsigned int *_result);

#define TEST(F, x, y) { \
  result[0] = 0; result[1] = 0;\
  clad::gradient(F);\
  F##_grad(x, y, result);\
  printf("Result is = {%.2f, %.2f}\n", result[0], result[1]); \
}
 
int main() { // expected-no-diagnostics
  double result[2];

  TEST(f_add1, 1, 1); // CHECK-EXEC: Result is = {1.00, 1.00}
  TEST(f_add2, 1, 1); // CHECK-EXEC: Result is = {3.00, 4.00}
  TEST(f_add3, 1, 1); // CHECK-EXEC: Result is = {3.00, 16.00}
  TEST(f_sub1, 1, 1); // CHECK-EXEC: Result is = {1.00, -1.00}
  TEST(f_sub2, 1, 1); // CHECK-EXEC: Result is = {3.00, -4.00}
  TEST(f_mult1, 1, 1); // CHECK-EXEC: Result is = {1.00, 1.00}
  TEST(f_mult2, 1, 1); // CHECK-EXEC: Result is = {12.00, 12.00}
  TEST(f_div1, 1, 1); // CHECK-EXEC: Result is = {1.00, -1.00}
  TEST(f_div2, 1, 1); // CHECK-EXEC: Result is = {0.75, -0.75}
  TEST(f_c, 1, 1); // CHECK-EXEC: Result is = {0.00, -2.00}
  TEST(f_rosenbrock, 1, 1); // CHECK-EXEC: Result is = {0.00, 0.00}
  TEST(f_cond1, 3, 2); // CHECK-EXEC: Result is = {1.00, 0.00}
  TEST(f_cond2, 3, -1); // CHECK-EXEC: Result is = {1.00, 0.00}
  TEST(f_cond3, 3, -1); // CHECK-EXEC: Result is = {1.00, -1.00}
  TEST(f_if1, 3, 2); // CHECK-EXEC: Result is = {1.00, 0.00}
  TEST(f_if2, -5, -4); // CHECK-EXEC: Result is = {0.00, -1.00}
  clad::gradient(&S::f);
  clad::gradient(f_norm);
  clad::gradient(f_sin);
  clad::gradient(f_types);
}

