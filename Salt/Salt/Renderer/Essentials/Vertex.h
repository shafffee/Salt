#pragma once


//Vertex is sent to GPU
struct Vertex {
	float pos[3];
	float color_rgba[4];
	float texture_pos[2];
	float texture_id;
};