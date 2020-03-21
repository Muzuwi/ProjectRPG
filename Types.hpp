#pragma once
#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <cassert>
#include <cstddef>
#include <cstdint>

enum class Direction {
	Up,
	Down,
	Left,
	Right
};

typedef sf::Vector2<int> Vec2i;
typedef sf::Vector2<unsigned> Vec2u;
typedef sf::Vector2<float> Vec2f;
typedef sf::Vector2<double> Vec2d;

template<class T>
class Array2D {
	std::vector<std::vector<T>> data;
	unsigned m_x, m_y;
public:
	~Array2D() = default;

	Array2D() {
		m_x = 0;
		m_y = 0;
	}

	Array2D(unsigned x, unsigned y) {
		this->resize(x, y);
	}

	Array2D(const Array2D& arr) {
		this->resize(arr.m_x, arr.m_y);
		for(size_t i = 0; i < m_x; i++) {
			for(size_t j = 0; j < m_y; j++) {
				data[i][j] = arr.data[i][j];
			}
		}
	}

	std::vector<T>& operator[](size_t index) {
		return data[index];
	}

	void resize(unsigned x, unsigned y) {
		m_x = x;
		m_y = y;
		data.resize(x);
		for(size_t i = 0; i < x; i++) data[i].resize(y);
	}

	unsigned getX() const { return m_x; }
	unsigned getY() const { return m_y; }
};