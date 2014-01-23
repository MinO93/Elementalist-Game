#include "Level.h"

#include "MemoryLeak.h"

void Level::LoadLevel(std::string Map)
{
	
	std::cout << Map << " is loading..." << std::endl;
	std::ifstream loadingmap;
	loadingmap.open(Map);

	int size_counter = 0;
	int old_x_counter = 0;
	int	x_counter = 0;
	int y_counter = 0;

	int scrap = 0;

	bool Map_Complete = false;

	//Kollar om banan har en "8000" i txt dokumentet
	while(!loadingmap.eof())
	{
		loadingmap >> scrap;
		if(scrap == 8000)
		{
			Map_Complete = true;
		}

	}

	loadingmap.close();
	scrap = 0;

	loadingmap.open(Map);
	if(Map_Complete == true)
	{
		while(scrap != 8000)
		{
			loadingmap >> scrap;
			x_counter++;
			size_counter++;

			if(scrap == 100)
			{
				x_counter--;
				size_counter--;

				if( y_counter != 0)
				{
					if(old_x_counter != x_counter)
					{
						std::cout << "The row: " << y_counter << " dont have same X-number as the row: " << y_counter+1 << std::endl;
					}
				}

				old_x_counter = x_counter;
				y_counter++;
				x_counter = 0;
			}
		}
	
		size_counter--;
	}
	else
	{
		std::cout << "Your map dont have any -8000-ID in dokument" << Map << std::endl;
	}
	loadingmap.close();
	
	std::cout << "MapSize:  " << old_x_counter << " x " << y_counter << " Blocks"<<std::endl;
	std::cout << Map << " is complete!" << std::endl;
	std::cout << std::endl;
	
	loadingmap.open(Map);
	int i  = 0;

	m_MapSize_x = old_x_counter;
	m_MapSize_y = y_counter;

	m_MapData = new int[size_counter];

	while (size_counter > i)
	{
		loadingmap >>  scrap;

		m_MapData[i] = scrap;
		i++;

		if(scrap == 100 || scrap == 8000)
		{
			i--;
		}
	}

	loadingmap.close();
	
}

void Level::DeleteMapData()
{
	delete m_MapData;
} 

int* Level::GetMapData() const
{

	int * fisk = m_MapData;
	return m_MapData;
}

int Level::GetMapSize_x() const
{
	return m_MapSize_x;
}

int Level::GetMapSize_y() const
{
	return m_MapSize_y;
}