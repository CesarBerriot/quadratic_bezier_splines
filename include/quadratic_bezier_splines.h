#pragma once

typedef enum { qbs_false, qbs_true } qbs_bool;

struct qbs_vector2
{	float x;
	float y;
};

struct qbs_point
{	struct qbs_vector2 position;
	struct qbs_vector2 influence_point_offset;
};

qbs_bool qbs_validate_spline(struct qbs_point spline[], int length);
struct qbs_vector2 qbs_compute_position(float delta, struct qbs_point spline[], int spline_length);
