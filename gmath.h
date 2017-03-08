#ifndef __GMATH_H__
#define __GMATH_H__

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//=====================================================================
// 数学库：此部分应该不用详解，熟悉 D3D 矩阵变换即可
//=====================================================================
typedef struct { float m[4][4]; } matrix_t;
typedef struct { float x, y, z, w; } vector_t;
typedef vector_t point_t;

typedef struct { 
	matrix_t world;         // 世界坐标变换
	matrix_t view;          // 摄影机坐标变换
	matrix_t projection;    // 投影变换
	matrix_t transform;     // transform = world * view * projection
	float w, h;             // 屏幕大小
}	transform_t;


int CMID(int x, int min, int max);

// 计算插值：t 为 [0, 1] 之间的数值
float interp(float x1, float x2, float t);

// | v |
float vector_length(const vector_t *v);
// z = x + y
void vector_add(vector_t *z, const vector_t *x, const vector_t *y);

// z = x - y
void vector_sub(vector_t *z, const vector_t *x, const vector_t *y);
// 矢量点乘
float vector_dotproduct(const vector_t *x, const vector_t *y);
// 矢量叉乘
void vector_crossproduct(vector_t *z, const vector_t *x, const vector_t *y);

// 矢量插值，t取值 [0, 1]
void vector_interp(vector_t *z, const vector_t *x1, const vector_t *x2, float t) ;

// 矢量归一化
void vector_normalize(vector_t *v);
// c = a + b
void matrix_add(matrix_t *c, const matrix_t *a, const matrix_t *b);
// c = a - b
void matrix_sub(matrix_t *c, const matrix_t *a, const matrix_t *b);

// c = a * b
void matrix_mul(matrix_t *c, const matrix_t *a, const matrix_t *b);
// c = a * f
void matrix_scale(matrix_t *c, const matrix_t *a, float f);
// y = x * m
void matrix_apply(vector_t *y, const vector_t *x, const matrix_t *m);
void matrix_set_identity(matrix_t *m);
void matrix_set_zero(matrix_t *m);
// 平移变换
void matrix_set_translate(matrix_t *m, float x, float y, float z);
// 缩放变换
void matrix_set_scale(matrix_t *m, float x, float y, float z);
// 旋转矩阵
void matrix_set_rotate(matrix_t *m, float x, float y, float z, float theta);

// 设置摄像机
void matrix_set_lookat(matrix_t *m, const vector_t *eye, const vector_t *at, const vector_t *up);
// D3DXMatrixPerspectiveFovLH
void matrix_set_perspective(matrix_t *m, float fovy, float aspect, float zn, float zf);

// 矩阵更新，计算 transform = world * view * projection
void transform_update(transform_t *ts);
// 初始化，设置屏幕长宽
void transform_init(transform_t *ts, int width, int height);
// 将矢量 x 进行 project 
void transform_apply(const transform_t *ts, vector_t *y, const vector_t *x);

// 检查齐次坐标同 cvv 的边界用于视锥裁剪
int transform_check_cvv(const vector_t *v);
// 归一化，得到屏幕坐标
void transform_homogenize(const transform_t *ts, vector_t *y, const vector_t *x);

#endif