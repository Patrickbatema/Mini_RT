/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit-test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:07:54 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/18 15:36:30 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <criterion.h>

Test(matrix_operations, matrix_equality)
{
	float		elementsA[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
				15, 16};
	float		elementsB[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
				15, 16};
	t_matrix	A;
	t_matrix	B;

	A = create_matrix(4, 4, elementsA);
	B = create_matrix(4, 4, elementsB);
	cr_assert(matrices_equal(A, B),
		"Identical matrices are not considered equal.");
	free_matrix(&A);
	free_matrix(&B);
}

Test(matrix_operations, multiplying_a_matrix_by_the_identity_matrix)
{
    t_matrix A = create_matrix(4, 4, (float[16]){0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32});
    t_matrix identity = identity_matrix();
    t_matrix result = multiply_matrices(A, identity);
    cr_assert(matrices_equal(result, A), "Multiplying by the identity matrix should return the original matrix.");
    free_matrix(&A);
    free_matrix(&result);
}

Test(matrix_operations, multiplying_the_identity_matrix_by_a_tuple)
{
    t_tuple a = tuple(1, 2, 3, 4);
    t_matrix identity = identity_matrix();
    t_tuple result = multiply_matrix_tuple(identity, a);
    cr_assert(tuple_equals(result, a), "Multiplying the identity matrix by a tuple should return the original tuple.");
    free_matrix(&identity);
}

Test(matrix_operations, transposing_a_matrix)
{
    
    float elementsA[] = {0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8};
    t_matrix A = {4, 4, malloc(16 * sizeof(float))};
    ft_memcpy(A.elements, elementsA, 16 * sizeof(float)); 

    
    float elementsExpected[] = {0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8};
    t_matrix expected = {4, 4, malloc(16 * sizeof(float))};
   ft_memcpy(expected.elements, elementsExpected, 16 * sizeof(float));

    
    t_matrix result = transpose_matrix(A);

    
    for (int i = 0; i < 16; i++) { 
        cr_assert_eq(result.elements[i], expected.elements[i], "Element at index %d is %f but expected %f", 
                     i, result.elements[i], expected.elements[i]);
    }

    
    free(A.elements);
    free(expected.elements);
    free(result.elements); 
}


Test(matrix_operations, determinant_of_2x2_matrix)
{
    t_matrix matrix = {
        .rows = 2,
        .cols = 2,
        .elements = (float[]){4, 3, 6, 8} 
    };

    float det = determinant(matrix);

    cr_assert_float_eq(det, 14, 0.001, "Expected determinant to be 14, but got %f", det);
}

Test(matrix_operations, submatrix_of_3x3_is_2x2) {
    t_matrix A = {
        .rows = 3,
        .cols = 3,
        .elements = (float[]){1, 5, 0, -3, 2, 7, 0, 6, -3}
    };

    t_matrix expected = {
        .rows = 2,
        .cols = 2,
        .elements = (float[]){-3, 2, 0, 6} 
    };

    t_matrix result = submatrix(A, 0, 2);

    int i = 0;
    while (i < expected.rows * expected.cols)
    {
        cr_assert_float_eq(result.elements[i], expected.elements[i], 0.001, "Element %d is %f but expected %f", i, result.elements[i], expected.elements[i]);
        i++;
    }
    free(result.elements);
}

Test(matrix_operations, submatrix_of_4x4_is_3x3)
{
    t_matrix A = {
        .rows = 4,
        .cols = 4,
        .elements = (float[]){-6, 1, 1, 6, -8, 5, 8, 6, -1, 0, 8, 2, -7, 1, -1, 1}
    };

    t_matrix expected = {
        .rows = 3,
        .cols = 3,
        .elements = (float[]){-6, 1, 6, -8, 8, 6, -7, -1, 1}
    };

    t_matrix result = submatrix(A, 2, 1);

    int i = 0;
    while (i < expected.rows * expected.cols) {
        cr_assert_float_eq(result.elements[i], expected.elements[i], 0.001, "Element %d is %f but expected %f", i, result.elements[i], expected.elements[i]);
        i++;
    }
    free(result.elements);
}

Test(matrix_operations, calculating_minor_of_3x3_matrix)
{
    t_matrix A = {
        .rows = 3,
        .cols = 3,
        .elements = malloc(9 * sizeof(float))
    };
    
    int i = 0;
    float elementsA[] = {3, 5, 0, 2, -1, -7, 6, -1, 5};
    while (i < 9) 
    {
        A.elements[i] = elementsA[i];
        i++;
    }

    t_matrix B = submatrix(A, 1, 0);

    float detB = determinant(B);
    cr_assert_float_eq(detB, 25, 0.001, "Determinant of B was expected to be 25, but got %f", detB);

    float minorA = minor(A, 1, 0);
    cr_assert_float_eq(minorA, 25, 0.001, "Minor of A, removing row 1 and col 0, was expected to be 25, but got %f", minorA);

    free(A.elements);
    free(B.elements);
}

Test(matrix_operations, calculating_cofactor_of_3x3_matrix)
{
    t_matrix A = {
        .rows = 3,
        .cols = 3,
        .elements = malloc(9 * sizeof(float))
    };
    A.elements[0] = 3; A.elements[1] = 5; A.elements[2] = 0;
    A.elements[3] = 2; A.elements[4] = -1; A.elements[5] = -7;
    A.elements[6] = 6; A.elements[7] = -1; A.elements[8] = 5;

    float minorA_00 = minor(A, 0, 0);
    float cofactorA_00 = cofactor(A, 0, 0);
    cr_assert_float_eq(minorA_00, -12, 0.001);
    cr_assert_float_eq(cofactorA_00, -12, 0.001);

    float minorA_10 = minor(A, 1, 0);
    float cofactorA_10 = cofactor(A, 1, 0);
    cr_assert_float_eq(minorA_10, 25, 0.001);
    cr_assert_float_eq(cofactorA_10, -25, 0.001);

    free(A.elements);
}

Test(determinant_tests, determinant_of_3x3_matrix)
{
    t_matrix A = {
        .rows = 3,
        .cols = 3,
        .elements = malloc(9 * sizeof(float))
    };
    float elements[] = {1, 2, 6, -5, 8, -4, 2, 6, 4};
    int i = 0;
    while (i < 9)
    {
        A.elements[i] = elements[i];
        i++;
    }
    cr_expect_eq(cofactor(A, 0, 0), 56, "Expected cofactor(A, 0, 0) to be 56");
    cr_expect_eq(cofactor(A, 0, 1), 12, "Expected cofactor(A, 0, 1) to be 12");
    cr_expect_eq(cofactor(A, 0, 2), -46, "Expected cofactor(A, 0, 2) to be -46");
    cr_expect_eq(determinant(A), -196, "Expected determinant(A) to be -196");

    free(A.elements);
}

Test(determinant_tests, determinant_of_4x4_matrix)
{
    t_matrix A = {
        .rows = 4,
        .cols = 4,
        .elements = malloc(16 * sizeof(float))
    };
    float elements[] = {-2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9};
    int i = 0;
    while (i < 16)
    {
        A.elements[i] = elements[i];
        i++;
    }

    cr_expect_eq(cofactor(A, 0, 0), 690, "Expected cofactor(A, 0, 0) to be 690");
    cr_expect_eq(cofactor(A, 0, 1), 447, "Expected cofactor(A, 0, 1) to be 447");
    cr_expect_eq(cofactor(A, 0, 2), 210, "Expected cofactor(A, 0, 2) to be 210");
    cr_expect_eq(cofactor(A, 0, 3), 51, "Expected cofactor(A, 0, 3) to be 51");
    cr_expect_eq(determinant(A), -4071, "Expected determinant(A) to be -4071");

    free(A.elements);
}

Test(matrix_tests, invertible_matrix)
{
    t_matrix A = { .rows = 4, .cols = 4, .elements = (float[]){ 6, 4, 4, 4, 5, 5, 7, 6, 4, -9, 3, -7, 9, 1, 7, -6 } };
    cr_assert_eq(determinant(A), -2120);
    cr_assert(is_invertible(A));
}

Test(matrix_tests, noninvertible_matrix)
{
    t_matrix A = { .rows = 4, .cols = 4, .elements = (float[]){ -4, 2, -2, -3, 9, 6, 2, 6, 0, -5, 1, -5, 0, 0, 0, 0 } };
    cr_assert_eq(determinant(A), 0);
    cr_assert_not(is_invertible(A));
}

Test(matrix_tests, calculating_inverse_of_matrix)
{
    t_matrix A = { .rows = 4, .cols = 4, .elements = (float[]){ -5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4 } };
    t_matrix B = inverse(A);
    cr_assert_float_eq(determinant(A), 532, 0.001);
    cr_assert_float_eq(cofactor(A, 2, 3), -160, 0.001);
    cr_assert_float_eq(B.elements[3 * B.cols + 2], -160.0 / 532, 0.001);
    cr_assert_float_eq(cofactor(A, 3, 2), 105, 0.001);
    cr_assert_float_eq(B.elements[2 * B.cols + 3], 105.0 / 532, 0.001);

    int i = 0;
    float expected_elements[] = { 0.21805, 0.45113, 0.24060, -0.04511, -0.80827, -1.45677, -0.44361, 0.52068, -0.07895, -0.22368, -0.05263, 0.19737, -0.52256, -0.81391, -0.30075, 0.30639 };
    while (i < 16) {
        cr_assert_float_eq(B.elements[i], expected_elements[i], 0.001, "Element %d is %f but expected %f", i, B.elements[i], expected_elements[i]);
        i++;
    }

    free(B.elements);
}

Test(matrix_inverse_tests, calculating_the_inverse_of_another_matrix)
{
    t_matrix A = {
        .rows = 4,
        .cols = 4,
        .elements = malloc(16 * sizeof(float))
    };
    float elementsA[] = {8, -5, 9, 2, 7, 5, 6, 1, -6, 0, 9, 6, -3, 0, -9, -4};
    ft_memcpy(A.elements, elementsA, 16 * sizeof(float));

    t_matrix expected = {
        .rows = 4,
        .cols = 4,
        .elements = malloc(16 * sizeof(float))
    };
    float elementsExpected[] = {-0.15385, -0.15385, -0.28205, -0.53846, -0.07692, 0.12308, 0.02564, 0.03077, 0.35897, 0.35897, 0.43590, 0.92308, -0.69231, -0.69231, -0.76923, -1.92308};
    ft_memcpy(expected.elements, elementsExpected, 16 * sizeof(float));

    t_matrix B = inverse(A);

    int i = 0;
    while (i < 16)
    {
        cr_assert_float_eq(B.elements[i], expected.elements[i], 0.0001);
        i++;
    }

    free(A.elements);
    free(B.elements);
    free(expected.elements);
}

Test(matrix_inverse_tests, multiplying_a_product_by_its_inverse)
{
    t_matrix A = {
        .rows = 4,
        .cols = 4,
        .elements = malloc(16 * sizeof(float))
    };
    float elementsA[] = {3, -9, 7, 3, 3, -8, 2, -9, -4, 4, 4, 1, -6, 5, -1, 1};
    int i = 0;
    while (i < 16) {
        A.elements[i] = elementsA[i];
        i++;
    }

    t_matrix B = {
        .rows = 4,
        .cols = 4,
        .elements = malloc(16 * sizeof(float))
    };
    float elementsB[] = {8, 2, 2, 2, 3, -1, 7, 0, 7, 0, 5, 4, 6, -2, 0, 5};
    i = 0;
    while (i < 16)
    {
        B.elements[i] = elementsB[i];
        i++;
    }
    t_matrix C = multiply_matrices(A, B);
    t_matrix B_inv = inverse(B);
    t_matrix result = multiply_matrices(C, B_inv);

    i = 0;
    while (i < 16)
    {
        cr_assert_float_eq(result.elements[i], A.elements[i], 0.0001, "Element %d is %f but expected %f", i, result.elements[i], A.elements[i]);
        i++;
    }
    free(A.elements);
    free(B.elements);
    free(C.elements);
    free(B_inv.elements);
    free(result.elements);
}
Test(matrix_transformations, multiplying_by_translation_matrix)
{
    t_matrix transform = translation(5, -3, 2);
    t_tuple p = point(-3, 4, 5);

    t_tuple result = multiply_matrix_tuple(transform, p);

    t_tuple expected = point(2, 1, 7);

    cr_assert_float_eq(result.x, expected.x, 0.0001);
    cr_assert_float_eq(result.y, expected.y, 0.0001);
    cr_assert_float_eq(result.z, expected.z, 0.0001);
    cr_assert_float_eq(result.w, expected.w, 0.0001);

    free(transform.elements);
}
Test(matrix_transformations, multiplying_by_inverse_of_translation_matrix)
{
    t_matrix transform = translation(5, -3, 2);
    t_matrix inv = inverse(transform);
    t_tuple p = point(-3, 4, 5);
    t_tuple result = multiply_matrix_tuple(inv, p);

    t_tuple expected = point(-8, 7, 3);

    cr_assert_float_eq(result.x, expected.x, 0.0001, "Expected x of %f, got %f", expected.x, result.x);
    cr_assert_float_eq(result.y, expected.y, 0.0001, "Expected y of %f, got %f", expected.y, result.y);
    cr_assert_float_eq(result.z, expected.z, 0.0001, "Expected z of %f, got %f", expected.z, result.z);
    cr_assert_float_eq(result.w, expected.w, 0.0001, "Expected w of %f, got %f", expected.w, result.w);

    free(transform.elements);
    free(inv.elements);
}

Test(matrix_transformations, translation_does_not_affect_vectors)
{
    t_matrix transform = translation(5, -3, 2);
    t_tuple v = vector(-3, 4, 5);
    
   
    t_tuple result = multiply_matrix_tuple(transform, v);
    cr_assert_float_eq(result.x, v.x, 0.0001, "X component should remain unchanged. Expected %f, got %f", v.x, result.x);
    cr_assert_float_eq(result.y, v.y, 0.0001, "Y component should remain unchanged. Expected %f, got %f", v.y, result.y);
    cr_assert_float_eq(result.z, v.z, 0.0001, "Z component should remain unchanged. Expected %f, got %f", v.z, result.z);
    cr_assert_float_eq(result.w, v.w, 0.0001, "W component (indicating a vector) should remain 0. Expected %f, got %f", v.w, result.w);

    free(transform.elements);
}

Test(matrix_transformations, scaling_matrix_applied_to_point)
{
    t_matrix transform = scaling(2, 3, 4);
    t_tuple p = point(-4, 6, 8);
    t_tuple result = multiply_matrix_tuple(transform, p);

    t_tuple expected = point(-8, 18, 32);

    cr_assert_float_eq(result.x, expected.x, 0.0001);
    cr_assert_float_eq(result.y, expected.y, 0.0001);
    cr_assert_float_eq(result.z, expected.z, 0.0001);
    cr_assert_float_eq(result.w, expected.w, 0.0001);

    free(transform.elements);
}

Test(matrix_transformations, scaling_matrix_applied_to_vector)
{
    t_matrix transform = scaling(2, 3, 4);
    t_tuple v = vector(-4, 6, 8);
    t_tuple result = multiply_matrix_tuple(transform, v);

    t_tuple expected = vector(-8, 18, 32);

    cr_assert_float_eq(result.x, expected.x, 0.0001);
    cr_assert_float_eq(result.y, expected.y, 0.0001);
    cr_assert_float_eq(result.z, expected.z, 0.0001);
    cr_assert_float_eq(result.w, expected.w, 0.0001);

    free(transform.elements);
}

Test(matrix_transformations, inverse_scaling_matrix_applied_to_vector)
{
    t_matrix transform = scaling(2, 3, 4);
    t_matrix inv = inverse(transform);
    t_tuple v = vector(-4, 6, 8);
    t_tuple result = multiply_matrix_tuple(inv, v);

    t_tuple expected = vector(-2, 2, 2);

    cr_assert_float_eq(result.x, expected.x, 0.0001);
    cr_assert_float_eq(result.y, expected.y, 0.0001);
    cr_assert_float_eq(result.z, expected.z, 0.0001);
    cr_assert_float_eq(result.w, expected.w, 0.0001);

    free(transform.elements);
    free(inv.elements);
}

Test(matrix_transformations, reflection_is_scaling_by_negative_value)
{
    t_matrix transform = scaling(-1, 1, 1);
    t_tuple p = point(2, 3, 4);
    t_tuple result = multiply_matrix_tuple(transform, p);

    t_tuple expected = point(-2, 3, 4);

    cr_assert_float_eq(result.x, expected.x, 0.0001, "X component after reflection incorrect. Expected %f, got %f", expected.x, result.x);
    cr_assert_float_eq(result.y, expected.y, 0.0001, "Y component should remain unchanged. Expected %f, got %f", expected.y, result.y);
    cr_assert_float_eq(result.z, expected.z, 0.0001, "Z component should remain unchanged. Expected %f, got %f", expected.z, result.z);
    cr_assert_float_eq(result.w, expected.w, 0.0001, "W component (indicating a point) should remain 1. Expected %f, got %f", expected.w, result.w);

    free(transform.elements);
}


Test(matrix_transformations, rotating_point_around_x_axis)
{
    t_tuple p = point(0, 1, 0);
    t_matrix half_quarter = rotation_x(M_PI / 4);
    t_matrix full_quarter = rotation_x(M_PI / 2);

    t_tuple half_rotated = multiply_matrix_tuple(half_quarter, p);
    t_tuple full_rotated = multiply_matrix_tuple(full_quarter, p);

    cr_assert_float_eq(half_rotated.x, 0, 0.0001);
    cr_assert_float_eq(half_rotated.y, sqrt(2)/2, 0.0001);
    cr_assert_float_eq(half_rotated.z, sqrt(2)/2, 0.0001);

    cr_assert_float_eq(full_rotated.x, 0, 0.0001);
    cr_assert_float_eq(full_rotated.y, 0, 0.0001);
    cr_assert_float_eq(full_rotated.z, 1, 0.0001);

    free(half_quarter.elements);
    free(full_quarter.elements);
}

Test(matrix_transformations, inverse_rotating_point_around_x_axis)
{
    t_tuple p = point(0, 1, 0);
    t_matrix half_quarter = rotation_x(M_PI / 4);
    t_matrix inv = inverse(half_quarter);

    t_tuple inv_rotated = multiply_matrix_tuple(inv, p);

    cr_assert_float_eq(inv_rotated.x, 0, 0.0001);
    cr_assert_float_eq(inv_rotated.y, sqrt(2)/2, 0.0001);
    cr_assert_float_eq(inv_rotated.z, -sqrt(2)/2, 0.0001);

    free(half_quarter.elements);
    free(inv.elements);
}


Test(matrix_transformations, rotating_point_around_y_axis)
{
    t_tuple p = point(0, 0, 1);
    t_matrix half_quarter = rotation_y(M_PI / 4);
    t_matrix full_quarter = rotation_y(M_PI / 2);

    t_tuple half_rotated = multiply_matrix_tuple(half_quarter, p);
    t_tuple full_rotated = multiply_matrix_tuple(full_quarter, p);

    cr_assert_float_eq(half_rotated.x, sqrt(2)/2, 0.0001, "Expected x to be √2/2, got %f", half_rotated.x);
    cr_assert_float_eq(half_rotated.y, 0, 0.0001, "Expected y to be 0, got %f", half_rotated.y);
    cr_assert_float_eq(half_rotated.z, sqrt(2)/2, 0.0001, "Expected z to be √2/2, got %f", half_rotated.z);

    cr_assert_float_eq(full_rotated.x, 1, 0.0001, "Expected x to be 1, got %f", full_rotated.x);
    cr_assert_float_eq(full_rotated.y, 0, 0.0001, "Expected y to be 0, got %f", full_rotated.y);
    cr_assert_float_eq(full_rotated.z, 0, 0.0001, "Expected z to be 0, got %f", full_rotated.z);

    free(half_quarter.elements);
    free(full_quarter.elements);
}



Test(matrix_transformations, shearing_transformation_moves_x_in_proportion_to_y)
{
    t_matrix transform = shearing(1, 0, 0, 0, 0, 0);
    t_tuple p = point(2, 3, 4);
    t_tuple result = multiply_matrix_tuple(transform, p);

    cr_assert_float_eq(result.x, 5, 0.0001, "After shearing, x should be 5, got %f", result.x);
    cr_assert_float_eq(result.y, 3, 0.0001, "Y should remain unchanged, got %f", result.y);
    cr_assert_float_eq(result.z, 4, 0.0001, "Z should remain unchanged, got %f", result.z);

    free(transform.elements);
}

Test(matrix_transformations, shearing_transformation_moves_x_in_proportion_to_z)
{
    t_matrix transform = shearing(0, 1, 0, 0, 0, 0);
    t_tuple p = point(2, 3, 4);
    t_tuple result = multiply_matrix_tuple(transform, p);
    cr_assert_float_eq(result.x, 6, 0.0001);
    cr_assert_float_eq(result.y, 3, 0.0001);
    cr_assert_float_eq(result.z, 4, 0.0001);
    free(transform.elements);
}

Test(matrix_transformations, shearing_transformation_moves_y_in_proportion_to_x)
{
    t_matrix transform = shearing(0, 0, 1, 0, 0, 0);
    t_tuple p = point(2, 3, 4);
    t_tuple result = multiply_matrix_tuple(transform, p);
    cr_assert_float_eq(result.x, 2, 0.0001);
    cr_assert_float_eq(result.y, 5, 0.0001);
    cr_assert_float_eq(result.z, 4, 0.0001);
    free(transform.elements);
}

Test(matrix_transformations, shearing_transformation_moves_y_in_proportion_to_z)
{
    t_matrix transform = shearing(0, 0, 0, 1, 0, 0);
    t_tuple p = point(2, 3, 4);
    t_tuple result = multiply_matrix_tuple(transform, p);
    cr_assert_float_eq(result.x, 2, 0.0001);
    cr_assert_float_eq(result.y, 7, 0.0001);
    cr_assert_float_eq(result.z, 4, 0.0001);
    free(transform.elements);
}

Test(matrix_transformations, shearing_transformation_moves_z_in_proportion_to_x)
{
    t_matrix transform = shearing(0, 0, 0, 0, 1, 0);
    t_tuple p = point(2, 3, 4);
    t_tuple result = multiply_matrix_tuple(transform, p);
    cr_assert_float_eq(result.x, 2, 0.0001);
    cr_assert_float_eq(result.y, 3, 0.0001);
    cr_assert_float_eq(result.z, 6, 0.0001);
    free(transform.elements);
}

Test(matrix_transformations, shearing_transformation_moves_z_in_proportion_to_y)
{
    t_matrix transform = shearing(0, 0, 0, 0, 0, 1);
    t_tuple p = point(2, 3, 4);
    t_tuple result = multiply_matrix_tuple(transform, p);
    cr_assert_float_eq(result.x, 2, 0.0001);
    cr_assert_float_eq(result.y, 3, 0.0001);
    cr_assert_float_eq(result.z, 7, 0.0001);
    free(transform.elements);
}

