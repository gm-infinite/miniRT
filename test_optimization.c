/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_optimization.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@github.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by copilot           #+#    #+#             */
/*   Updated: 2025/01/27 00:00:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "camera.h"
#include <stdio.h>
#include <math.h>

#define TEST_TOLERANCE 0.000001

// Original sphere intersection function for testing
double	sphere_intersection_original(t_ray ray, t_sphere sphere)
{
	double					t1;
	double					t2;
	t_vector				oc;
	double					b;
	double					discriminant;

	oc = point_substract(ray.origin, sphere.origin);
	b = 2.0 * vector_dot_product(oc, ray.direction);
	discriminant = (b * b) - (4.0 * (vector_dot_product(oc, oc)
				- (sphere.radius * sphere.radius)));
	if (discriminant < 0)
		return (-1);
	t1 = (-b - sqrt(discriminant)) / 2.0;
	t2 = (-b + sqrt(discriminant)) / 2.0;
	if (t1 >= T_ZERO_THRESHOLD)
		return (t1);
	else if (t2 >= T_ZERO_THRESHOLD)
		return (t2);
	return (-1);
}

int	test_sphere_optimization(void)
{
	t_sphere	sphere_test;
	t_ray		ray;
	t_point		camera_pos;
	double		t_old, t_new;

	// Create sphere
	sphere_test = sphere(vector(1, 2, 3), 1.5);
	
	// Set camera position
	camera_pos = vector(0, 0, 0);
	
	// Create a test ray from camera
	ray = ray_constructor(vector_normalize(vector(0.5, 0.8, 1.0)), camera_pos);
	
	// Test original calculation
	t_old = sphere_intersection_original(ray, sphere_test);
	
	// Apply optimization and test new calculation
	set_sphere_relative_cam_pos(&sphere_test, camera_pos);
	t_new = sphere_intersection(ray, sphere_test);
	
	// Check if results are the same
	if ((t_old < 0 && t_new < 0) || (fabs(t_old - t_new) < TEST_TOLERANCE))
	{
		printf("✓ Sphere optimization test PASSED\n");
		printf("  Original result: %f\n", t_old);
		printf("  Optimized result: %f\n", t_new);
		return (1);
	}
	else
	{
		printf("✗ Sphere optimization test FAILED\n");
		printf("  Original result: %f\n", t_old);
		printf("  Optimized result: %f\n", t_new);
		printf("  Difference: %f\n", fabs(t_old - t_new));
		return (0);
	}
}

int	test_relative_cam_pos_calculation(void)
{
	t_sphere	sphere_test;
	t_point		camera_pos;
	t_vector	expected, actual;

	// Create sphere
	sphere_test = sphere(vector(1, 2, 3), 1.5);
	
	// Set camera position
	camera_pos = vector(5, 7, 9);
	
	// Calculate expected relative position manually
	expected = point_substract(camera_pos, sphere_test.origin);
	
	// Apply optimization
	set_sphere_relative_cam_pos(&sphere_test, camera_pos);
	actual = sphere_test.relative_cam_pos;
	
	// Check if relative_cam_pos is calculated correctly
	if (fabs(expected.x - actual.x) < TEST_TOLERANCE &&
		fabs(expected.y - actual.y) < TEST_TOLERANCE &&
		fabs(expected.z - actual.z) < TEST_TOLERANCE)
	{
		printf("✓ Relative camera position calculation test PASSED\n");
		printf("  Expected: (%.3f, %.3f, %.3f)\n", expected.x, expected.y, expected.z);
		printf("  Actual: (%.3f, %.3f, %.3f)\n", actual.x, actual.y, actual.z);
		return (1);
	}
	else
	{
		printf("✗ Relative camera position calculation test FAILED\n");
		printf("  Expected: (%.3f, %.3f, %.3f)\n", expected.x, expected.y, expected.z);
		printf("  Actual: (%.3f, %.3f, %.3f)\n", actual.x, actual.y, actual.z);
		return (0);
	}
}

int	main(void)
{
	int	calc_test_result;
	int	sphere_test_result;

	printf("Testing relative camera position optimization...\n\n");
	
	calc_test_result = test_relative_cam_pos_calculation();
	sphere_test_result = test_sphere_optimization();
	
	printf("\nTest Results:\n");
	printf("Relative position calculation: %s\n", calc_test_result ? "PASS" : "FAIL");
	printf("Sphere optimization: %s\n", sphere_test_result ? "PASS" : "FAIL");
	
	if (calc_test_result && sphere_test_result)
	{
		printf("\n🎉 All optimization tests PASSED!\n");
		printf("The relative camera position optimization is working correctly.\n");
		return (0);
	}
	else
	{
		printf("\n❌ Some tests FAILED!\n");
		return (1);
	}
}