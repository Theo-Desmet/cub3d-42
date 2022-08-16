/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbordere <bbordere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:11:12 by bbordere          #+#    #+#             */
/*   Updated: 2022/08/16 15:52:51 by bbordere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <random>
#include <iostream>
#include <tuple>
#include <random>
#include <fstream>
#include <stdlib.h>
#include <dirent.h>


#define MINWIDTH  3
#define MINHEIGHT  3

class Rectangle
{
	private:
		const int				x1;
		const int				y1;
		const int				x2;
		const int				y2;
		const unsigned int		area;
		
	public:
		Rectangle();
		Rectangle(int x1, int y1, int x2, int y2);
		~Rectangle();
		std::tuple<int, int, int, int> getCoord(void) const;
		int	getX1(void) const;
		int	getY1(void) const;
		int	getX2(void) const;
		int	getY2(void) const;
		unsigned int getArea(void) const;
};

Rectangle::Rectangle():
	x1(0), y1(0), x2(0), y2(0), area(0)
{
	
}

Rectangle::Rectangle(int x1, int y1, int x2, int y2):
	x1(x1), y1(y1), x2(x2), y2(y2), area((x2 - x1 + 1) * (y2 - y1 + 1))
{
}

Rectangle::~Rectangle()
{
	
}

int	Rectangle::getX1(void) const
{
	return (const_cast<int&>(this->x1));
}

int	Rectangle::getY1(void) const
{
	return (this->y1);
}

int	Rectangle::getX2(void) const
{
	return (this->x2);
}

int	Rectangle::getY2(void) const
{
	return (this->y2);
}

unsigned int Rectangle::getArea(void) const
{
	return (this->area);
}

std::ostream& operator<<(std::ostream &output, Rectangle const &rect)
{
	output << "(" << rect.getX1() << ", " << rect.getY1() << ", " << rect.getX2() << ", " << rect.getY2() << ")";
	return (output);
}

std::ostream& operator<<(std::ostream &output, Rectangle const *rect)
{
	output << "(" << rect->getX1() << ", " << rect->getY1() << ", " << rect->getX2() << ", " << rect->getY2() << ")";
	return (output);
}

void	printLevel(const std::vector<std::vector<int>> &level)
{
	for (std::size_t i = 0; i < level.size(); i++)
	{
		for (std::size_t j = 0; j < level[0].size(); j++)
			std::cout << (level[i][j] == 1 ? "1" : " ");
		std::cout << std::endl;
	}
}

std::vector<std::vector <int>> *initLevel(int width, int height)
{
	std::vector<std::vector <int>> *level;

	level = new std::vector<std::vector <int>>(height, std::vector<int>(width, 0));
	for (int i = 0; i < height; i++)
	{
		(*level)[i][0] = 1;
		(*level)[i][width - 1] = 1;
		for (int j = 0; j < width; j++)
		{
			(*level)[0][j] = 1;
			(*level)[height - 1][j] = 1;
		}	
	}
	return (level);
}

int		randIntRange(int min, int max)
{
	std::random_device	rd;
	std::default_random_engine eng(rd());
	std::uniform_int_distribution<int> distr(min, max);
	return (distr(eng));
}

void	subdivide(Rectangle rect, std::vector<std::vector <int>> *level);

void	subdivideVertical(std::vector<std::vector <int>> *level, Rectangle rect)
{
	int					r = randIntRange(rect.getX1() + MINWIDTH, rect.getX2() - MINWIDTH);
	for (int i = rect.getY1(); i <= rect.getY2(); i++)
		(*level)[i][r] = 1;
	subdivide(Rectangle(rect.getX1(), rect.getY1(), r - 1, rect.getY2()), level);
	subdivide(Rectangle(r + 1, rect.getY1(), rect.getX2(), rect.getY2()), level);
	
	int	doorY = randIntRange(rect.getY1() + 1, rect.getY2() - 1);
	(*level)[doorY][r] = 3;
	if ((*level)[doorY][r + 2] == 1)
		(*level)[doorY][r + 2] = 4;
	if ((*level)[doorY][r - 2] == 1)
		(*level)[doorY][r - 2] = 4;
	if ((*level)[doorY][r + 1] == 1)
		(*level)[doorY][r + 1] = 4;
	if ((*level)[doorY][r - 1] == 1)
		(*level)[doorY][r - 1] = 4;
}



void	subdivideHorizontal(std::vector<std::vector <int>> *level, Rectangle rect)
{

	int					r = randIntRange(rect.getY1() + MINHEIGHT, rect.getY2() - MINHEIGHT);

	for (int i = rect.getX1(); i <= rect.getX2(); i++)
		(*level)[r][i] = 1;
	subdivide(Rectangle(rect.getX1(), rect.getY1(), rect.getX2(), r - 1), level);
	subdivide(Rectangle(rect.getX1(), r + 1, rect.getX2(), rect.getY2()), level);
	
	int	doorX = randIntRange(rect.getX1() + 1, rect.getX2() - 1);
	(*level)[r][doorX] = 3;
	if ((*level)[r - 2][doorX] == 1)
		(*level)[r - 2][doorX] = 4;
	if ((*level)[r + 2][doorX] == 1)
		(*level)[r + 2][doorX] = 4;
	if ((*level)[r - 1][doorX] == 1)
		(*level)[r - 1][doorX] = 4;
	if ((*level)[r + 1][doorX] == 1)
		(*level)[r + 1][doorX] = 4;
}



void	subdivide(Rectangle rect, std::vector<std::vector <int>> *level)
{
	std::random_device r_gen;
	int	w = rect.getX2() - rect.getX1() + 1;
	int	h = rect.getY2() - rect.getY1() + 1;
	
	if (w > h && w > (MINWIDTH * 2 + 1))
		subdivideVertical(level, rect);
	else if (h >= (MINHEIGHT * 2 + 1))
		subdivideHorizontal(level, rect);
}

std::vector<std::vector <int>> *inverseLevel(std::vector<std::vector <int>> const *level)
{
	std::vector<std::vector <int>> *inversed;

	inversed = new std::vector<std::vector <int>>(level->size(), std::vector<int>((*level)[0].size(), 0));
	for (std::size_t i = 0; i < inversed->size(); i++)
		for (std::size_t j = 0; j < (*inversed)[0].size(); j++)
			if ((*level)[i][j] == 0)
				(*inversed)[i][j] = 1;
	return (inversed);				
}

unsigned int	countTotalRectArea(std::vector<std::vector <int>> const *level)
{
	unsigned int res = 0;
	for (std::size_t i = 0; i < (*level).size(); i++)
		for (std::size_t j = 0; j < (*level)[0].size(); j++)
			res += (*level)[i][j] == 1 ? 1 : 0;
	return (res);	
}

void			markRect(Rectangle rect, std::vector<std::vector <int>> *level)
{
	for (int i = rect.getX1(); i <= rect.getX2(); i++)
		for (int j = rect.getY1(); j <= rect.getY2(); j++)
			(*level)[j][i] = 2;	
}

Rectangle	*findNextRect(std::vector<std::vector <int>> *level)
{
	std::size_t	w = (*level)[0].size();
	std::size_t	h = (*level).size();
	bool		found = false;
	int			x1, y1, x2, y2;
	x1 = 0; y1 = 0;
	x2 = w - 1; y2 = h - 1;
	for (std::size_t i = 0; i < w; i++)
	{
		for (std::size_t j = 0; j < h; j++)
		{
			if ((*level)[j][i] == 1)
			{
				x1 = i;
				y1 = j;
				found = true;
				break;
			}
		}
		if (found)
			break;		
	}
	for (int i = x1; i <= x2; i++)
	{
		if ((*level)[y1][i] != 1)
		{
			x2 = i - 1;
			return (new Rectangle(x1, y1, x2, y2));
		}
		for (int j = y1; j <= y2; j++)
		{
			if ((*level)[j][i] != 1)
			{
				y2 = j - 1;
				break;
			}
		}
	}
	return (new Rectangle(x1, y1, x2, y2));
}

std::vector<Rectangle *>	*getRects(std::vector<std::vector <int>> *level)
{
	std::vector<Rectangle *>	*rects = new std::vector<Rectangle *>;
	unsigned int			area = 0;
	unsigned int			total = countTotalRectArea(level);

	while (area < total)
	{
		Rectangle	*temp = findNextRect(level);
		(*rects).push_back(temp);
		markRect(*temp, level);
		area += (*temp).getArea();
	}
	return (rects);
}

Rectangle *getBiggestRect(std::vector<Rectangle *>	*rects)
{
	unsigned int	max = 0;
	Rectangle		*biggest;

	for (std::size_t i = 0; i < (*rects).size(); i++)
	{
		if ((*rects)[i]->getArea() > max)
		{
			max = (*rects)[i]->getArea();
			biggest = (*rects)[i];
		}
	}
	return (biggest);
}

template <typename N>
N randomRange(N min, N max)
{
	std::random_device	random;
	N range = max - min + 1;
	return (random() % range + min);
}

template <typename T>
typename T::iterator choice(T *container)
{
	int	end = container->size() - 1;
	return (container->begin() + randomRange<int>(0, end));
}

std::vector<std::vector <int>> *generateLevel(int const mapWidth, int const mapHeight)
{
	std::vector<std::vector <int>> *level;

	level = initLevel(mapWidth, mapHeight);
	subdivide(Rectangle(1, 1, mapWidth - 2, mapHeight - 2), level);
	std::vector<std::vector <int>> *inversed;
	inversed = inverseLevel(level);

	std::vector<Rectangle *>	*rects = getRects(inversed);
	Rectangle					*biggest = getBiggestRect(rects);
	unsigned	int				area = biggest->getArea();
	int							it = -1;
	while (area >= (static_cast<unsigned int>((mapHeight * mapWidth)  / 6)) && ++it < 50)
	{
		subdivide(*biggest, level);
		rects = getRects(inverseLevel(level));
		biggest = getBiggestRect(rects);
		area = biggest->getArea();
	}
	
	std::vector<int> directions = {5, 6, 7, 8};
	int x = randomRange<int>(1, level->size() - 2);
	int y = randomRange<int>(1, level[0].size() - 2);
	while ((*level)[y][x] == 1)
	{
		x = randomRange<int>(1, level->size() - 2);
		y = randomRange<int>(1, level[0].size() - 2);
	}
	std::vector<int>::iterator	element = choice(&directions);
	(*level)[y][x] = *element;

	for (std::size_t i = 0; i < (*rects).size(); i++)
		delete (*rects)[i];
	delete rects;
	delete inversed;
	return (level);
}

#define WALL_CHAR "1"
#define EMPTY_CHAR "0"
#define DOOR_CHAR "0"

void	exportPlayerSpawn(std::fstream &file, int dir)
{
	std::vector<std::string> directions = {"W", "E", "N", "S"};
	file << directions[dir % 5];
}

void	exportLevelToFile(std::vector<std::vector <int>> const level, std::fstream &file)
{
	for (std::size_t i = 0; i < level.size(); i++)
	{
		for (std::size_t j = 0; j < level[0].size(); j++)
		{
			switch (level[i][j])
			{
				case 1:
					file << WALL_CHAR;
					break;
				case 3:
					if ((randIntRange(0, 1) % 2 == 1) && ((level[i + 1][j] == 1 && level[i - 1][j] == 1) || (level[i][j + 1] == 1 && level[i][j - 1] == 1)))
						file << DOOR_CHAR;
					else
						file << EMPTY_CHAR;
					break;
				case 5: case 6: case 7: case 8:
					exportPlayerSpawn(file, level[i][j]);
					break;

				default:
					file << EMPTY_CHAR;
					break;
			}
		}
		file << std::endl;
	}
}

std::vector<std::string>	*getTexturesFiles(std::string const dir)
{
	std::vector<std::string>	*files = new std::vector<std::string>;
	DIR *direc;
	struct dirent *dirhead;
	if ((direc = opendir(dir.c_str())))
		while ((dirhead = readdir(direc)))
			if (std::string(dirhead->d_name).find(".xpm") != std::string::npos)
				files->push_back(dir + std::string(dirhead->d_name));
	closedir(direc);
	return (files);
}



void	exportHeaderToFile(std::fstream &file, std::string const dirname)
{
	std::string	directions[] = {"NO", "SO", "WE", "EA"};
	std::vector<std::string> *textures = getTexturesFiles(dirname);
	for (size_t	i = 0; i < 4; i++)
	{
		std::vector<std::string>::iterator	element = choice(textures);
		file << directions[i] << " " << *element << std::endl;
		textures->erase(element);
	}
	delete textures;
	file << std::endl << "F ";
	for (size_t	i = 0; i < 2; i++)
		file << randomRange<int>(0, 255) << ", ";
	file << randomRange<int>(0, 255);
	file << std::endl << "C ";
	for (size_t	i = 0; i < 2; i++)
		file << randomRange<int>(0, 255) << ", ";
	file << randomRange<int>(0, 255) << std::endl << std::endl;
}

void	exportToFile(int const mapWidth, int const mapHeight, std::string const filename, std::string const dirPath)
{
	std::fstream	file;
	std::vector<std::vector <int>> *level;

	file.open(filename, std::ios_base::out);
	if (!file)
	{
		std::cout << "Can't create or open file !" << std::endl;
		exit(EXIT_FAILURE);
	}
	exportHeaderToFile(file, dirPath);
	level = generateLevel(mapWidth, mapHeight);
	exportLevelToFile(*level, file);
	file.close();
	delete level;
}

int main(int ac, char **av)
{
	(void)ac;
	(void)av;
	exportToFile(25, 25, "test.cub", "./");
	// std::vector<std::string> *files = getTexturesFiles(".");
	return 0;
}
