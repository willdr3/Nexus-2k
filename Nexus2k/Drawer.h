#pragma once
#ifndef _DRAWER
#define _DRAWER
#include "Board.h"

using namespace System::Drawing;

ref class Drawer
{
	static array<Bitmap^>^ ball = {
		(Bitmap^)Image::FromFile("img\\free.png"),
		(Bitmap^)Image::FromFile("img\\blue.png"),
		(Bitmap^)Image::FromFile("img\\red.png"),
		(Bitmap^)Image::FromFile("img\\green.png"),
		(Bitmap^)Image::FromFile("img\\yellow.png"),
		(Bitmap^)Image::FromFile("img\\purple.png"),
		(Bitmap^)Image::FromFile("img\\bleau.png"),
		(Bitmap^)Image::FromFile("img\\selected.png"),
	};
	static Pen^ border = gcnew Pen(Color::White);
	static Pen^ outline = gcnew Pen(Color::Black);
	static Graphics^ formGraphics;
public:
	static void init(Graphics^);
	static void draw(Board&);
};

#endif