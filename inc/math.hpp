#pragma once

#include <iostream>

/**
 * @brief This struct represents a 2D vector.
 * A 2D vector is a vector with two components, x and y.
 * This struct is used to represent a 2D vector in the game.
 * It is used to store information about the vector, such as
 * its x and y components. - Copilot
 */
struct Vector2f
{
	//Vector2f()
	//:x(0.0f), y(0.0f)
	//{}

	/**
	 * @brief Construct a new Vector 2f object.
	 * 
	 * @param p_x X Position of the vector.
	 * @param p_y Y Position of the vector.
	 */
	Vector2f(float p_x, float p_y)
	:x(p_x), y(p_y)
	{}

	void print()
	{
		std::cout << x << ", " << y << std::endl;
	}

	float x, y;
};