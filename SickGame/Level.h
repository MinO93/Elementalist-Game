#pragma once
#include <string>
#include <iostream>
#include <fstream>


class Level
{
public:

	void LoadLevel(std::string Map);
	void DeleteMapData();
	int* GetMapData() const;
	int GetMapSize_x() const;
	int GetMapSize_y() const;

private:
	int * m_MapData;
	int m_MapSize_x;
	int m_MapSize_y;

};

