/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example_optimization_usage.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@github.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 00:00:00 by copilot           #+#    #+#             */
/*   Updated: 2025/01/27 00:00:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "camera.h"

/*
 * Example demonstrating the relative camera position optimization.
 * 
 * Before optimization:
 * - For each ray cast to each object, calculate ray.origin - object.origin
 * - This happens thousands/millions of times during rendering
 * 
 * After optimization:
 * - Calculate camera.origin - object.origin ONCE per object during setup
 * - Use the pre-calculated value during ray intersections
 * - Significant performance improvement, especially for complex scenes
 */

void	example_setup_scene_with_optimization(void)
{
	t_camera	camera;
	t_sphere	sphere1;
	t_sphere	sphere2;
	t_cylinder	cylinder1;

	// Setup camera at position (0, 0, -5) looking forward
	camera.origin = vector(0, 0, -5);
	camera.direction = vector(0, 0, 1);
	camera.fov = 60;

	// Create objects
	sphere1 = sphere(vector(2, 0, 0), 1.0);
	sphere2 = sphere(vector(-2, 0, 2), 1.5);
	cylinder1 = cylinder(vector(0, 1, 0), vector(0, 0, 5), 0.5, 3.0);

	// IMPORTANT: Set up transformation matrix for cylinder before optimization
	transform_matrix(&cylinder1);

	// Apply the optimization: pre-calculate relative camera positions
	set_sphere_relative_cam_pos(&sphere1, camera.origin);
	set_sphere_relative_cam_pos(&sphere2, camera.origin);
	set_cylinder_relative_cam_pos(&cylinder1, camera.origin);

	// Now when rendering, intersection functions will use pre-calculated values
	// instead of computing ray.origin - object.origin for each ray
	
	/*
	 * Performance benefit example:
	 * - For a 1000x1000 image with 3 objects: 3,000,000 calculations avoided
	 * - For cylinders: additional transformation calculations avoided per ray
	 * - Memory trade-off: 3 doubles per object vs. millions of calculations
	 */
}

/*
 * Example of the intersection improvement:
 * 
 * OLD sphere_intersection():
 * oc = point_substract(ray.origin, sphere.origin);  // Calculated every time
 * 
 * NEW sphere_intersection():
 * oc = sphere.relative_cam_pos;  // Pre-calculated value used
 * 
 * Similar optimization applies to cylinder intersections with additional
 * transformation matrix calculations being pre-computed.
 */