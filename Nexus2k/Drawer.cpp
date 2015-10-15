#include "stdafx.h"
#include "Drawer.h"


void Drawer::init(System::Drawing::Graphics^ g)
{
	formGraphics = g;
}

void Drawer::draw(Board &b)
{
	for (int i = 0; i < BOARD_WIDTH; i++)
	{
		for (int j = 0; j < BOARD_HEIGHT; j++)
		{
			TextureBrush^ brush = gcnew TextureBrush(ball[b.cellContent(i, j)]);
			formGraphics->FillRectangle(brush, i * 40, j * 40, 40, 40);
			delete brush;
		}
	}
}