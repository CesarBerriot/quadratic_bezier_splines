#include "quadratic_bezier_splines.h"
#include <windows.h>
#include <hard_assert.h>

static struct qbs_vector2 compute_linear_interpolation(struct qbs_vector2, struct qbs_vector2, float);
static struct qbs_vector2 compute_offset_position(struct qbs_point);

qbs_bool qbs_validate_spline(struct qbs_point spline[], int length)
{	if(length < 2)
		return qbs_false;
	for(int i = 1; i < length; ++i)
		if(spline[i].position.x < spline[i - 1].position.x)
			return qbs_false;
	return qbs_true;
}

struct qbs_vector2 qbs_compute_position(float delta, struct qbs_point spline[], int spline_length)
{	if(delta < spline[0].position.x)
		return spline[0].position;
	if(delta > spline[spline_length - 1].position.x)
		return spline[spline_length - 1].position;
	for(int i = 1; i < spline_length; ++i)
		if(spline[i].position.x >= delta)
		{	struct qbs_vector2
				origin_position = spline[i - 1].position,
				origin_influence = compute_offset_position(spline[i - 1]),
				destination_position = spline[i].position,
				destination_influence = compute_offset_position(spline[i]);

			struct qbs_vector2 first_pass[3] =
			{	compute_linear_interpolation(origin_position, origin_influence, delta),
				compute_linear_interpolation(origin_influence, destination_influence, delta),
				compute_linear_interpolation(destination_influence, destination_position, delta)
			};

			struct qbs_vector2 second_pass[2] =
			{	compute_linear_interpolation(first_pass[0], first_pass[1], delta),
				compute_linear_interpolation(first_pass[1], first_pass[2], delta)
			};

			struct qbs_vector2 third_pass = compute_linear_interpolation(second_pass[0], second_pass[1], delta);

			return third_pass;
		}
	ha_abort("Quadratic Bezier Splines", "Invalid spline passed for position computation.");
}

static struct qbs_vector2 compute_linear_interpolation(struct qbs_vector2 origin, struct qbs_vector2 destination, float delta)
{	return (struct qbs_vector2)
	{	.x = origin.x + (destination.x - origin.x) * delta,
		.y = origin.y + (destination.y - origin.y) * delta
	};
}

static struct qbs_vector2 compute_offset_position(struct qbs_point point)
{	return (struct qbs_vector2)
	{	.x = point.position.x + point.influence_point_offset.x,
		.y = point.position.y + point.influence_point_offset.y
	};
}