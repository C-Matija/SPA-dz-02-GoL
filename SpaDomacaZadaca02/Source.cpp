#include <SFML/Graphics.hpp>
#include <ctime>

using namespace std;
using namespace sf;

int gen_rnd(int min, int max)
{
	return rand() % (max - min + 1) + min;
}

const int sirina = 800;
const int visina = 600;
int max_broj_stanica = sirina*visina;

int generacija1[sirina + 1][visina + 1];
int generacija2[sirina + 1][visina + 1];
bool stanica = 0;
int prva_generacija = 1;
int koja_generacija = 0;
int velicina = 3;

void stanice()
{
	srand(time(nullptr));

	for (int i = 1; i <= max_broj_stanica; i++)
	{
		int random = gen_rnd(1, 4);

		if (random == 4)
		{
			int x = rand() % sirina;
			int y = rand() % visina;
			generacija1[y][x] = 1;
		}
	}
}


void gen1(int x, int y)
{
	int susjedi = 0;
	if (generacija1[x - 1][y - 1] == 1)
	{
		susjedi++;
	}
	if (generacija1[x - 1][y] == 1)
	{
		susjedi++;
	}
	if (generacija1[x - 1][y + 1] == 1)
	{
		susjedi++;
	}
	if (generacija1[x][y - 1] == 1)
	{
		susjedi++;
	}
	if (generacija1[x][y + 1] == 1)
	{
		susjedi++;
	}
	if (generacija1[x + 1][y - 1] == 1)
	{
		susjedi++;
	}
	if (generacija1[x + 1][y] == 1)
	{
		susjedi++;
	}
	if (generacija1[x + 1][y + 1] == 1)
	{
		susjedi++;
	}

	if (generacija1[x][y] == 1)
	{
		if (susjedi < 2)
		{
			generacija2[x][y] = 0;
		}
		if (susjedi > 3)
		{
			generacija2[x][y] = 0;
		}
		if (susjedi == 2 || susjedi == 3)
		{
			generacija2[x][y] = 1;
		}
	}

	if (generacija1[x][y] == 0)
	{
		if (susjedi == 3)
		{
			generacija2[x][y] = 1;
		}
	}
}

void gen2(int i, int j)
{
	int susjedi = 0;
	if (generacija2[i - 1][j - 1] == 1)
	{
		susjedi++;
	}
	if (generacija2[i - 1][j] == 1)
	{
		susjedi++;
	}
	if (generacija2[i - 1][j + 1] == 1)
	{
		susjedi++;
	}
	if (generacija2[i][j - 1] == 1)
	{
		susjedi++;
	}
	if (generacija2[i][j + 1] == 1)
	{
		susjedi++;
	}
	if (generacija2[i + 1][j - 1] == 1)
	{
		susjedi++;
	}
	if (generacija2[i + 1][j] == 1)
	{
		susjedi++;
	}
	if (generacija2[i + 1][j + 1] == 1)
	{
		susjedi++;
	}

	if (generacija2[i][j] == 1)
	{
		if (susjedi < 2)
		{
			generacija1[i][j] = 0;
		}
		if (susjedi > 3)
		{
			generacija1[i][j] = 0;
		}
		if (susjedi == 2 || susjedi == 3)
		{
			generacija1[i][j] = 1;
		}
	}
	if (generacija2[i][j] == 0)
	{
		if (susjedi == 3)
		{
			generacija1[i][j] = 1;
		}
	}
}

int main()
{
	Clock clock;

	sf::RenderWindow window(sf::VideoMode(sirina, visina), "Hello, SFML world. Game of life!");
	window.setFramerateLimit(60);

	Texture img_stanica;
	img_stanica.loadFromFile("Stanica.png");
	Sprite St(img_stanica);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (stanica == 0)
		{
			stanice();
			stanica = 1;
		}

		window.clear(Color::White);

		for (int i = 1; i <= visina; i++)
		{
			for (int j = 1; j <= sirina; j++)
			{
				if (prva_generacija == 1)
				{
					if (koja_generacija == 1)
					{
						gen1(i, j);
					}
					else if (koja_generacija == 2)
					{
						gen2(i, j);
					}
				}
				if (prva_generacija == 0)
				{
					prva_generacija = 1;
				}
			}
		}
		if (koja_generacija == 1)
		{
			koja_generacija = 2;
			for (int i = 1; i <= visina; i++)
			{
				for (int j = 1; j <= sirina; j++)
				{
					generacija1[i][j] = 0;
				}
			}
		}
		else
		{
			koja_generacija = 1;
			for (int i = 1; i <= visina; i++)
			{
				for (int j = 1; j <= sirina; j++)
				{
					generacija2[i][j] = 0;
				}
			}
		}
		if (koja_generacija == 1)
		{
			for (int i = 1; i <= visina; i++)
			{
				for (int j = 1; j <= sirina; j++)
				{
					if (generacija1[i][j] == 1)
					{
						St.setPosition(j * velicina, i * velicina);
						window.draw(St);
					}
				}
			}
		}
		else if (koja_generacija == 2)
		{
			for (int i = 1; i <= visina; i++)
			{
				for (int j = 1; j <= sirina; j++)
				{
					if (generacija2[i][j] == 1)
					{
						St.setPosition(j * velicina, i * velicina);
						window.draw(St);
					}
				}
			}
		}

		window.display();
	}

	return 0;
}