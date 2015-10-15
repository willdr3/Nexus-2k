/* Program Name:           Nexus 2K
* File Name:               Nexus2K
* Author:                  Dan Williamson
* Date:                    15/10/2015
* Language:                C++
* Platform:                Microsoft Visual Studio 2013
* Purpose:                 To recreate the game "Nexus2K"
* Description:             In this game there is a 9 x 9 grid of squares. When the player starts the game 3 circles are created.
*						   These circles are picked randomly from 6 colours, and placed randomly on the board. The objective is to
*						   create lines of 5 or more of the same colour. If a line of 5 or more of the same colour is made, these
*						   are deleted and the score is increased. For a coloured circle to be moved, there must be a clear path
*						   to the destination square and it can not traverse diagonally.
* Known Bugs:                                        
*
* Additional Features:     A* shortest path algorithm. Undo can go right back to start of game.
*/

#pragma once
#include "Board.h"
#include "Drawer.h"
#include "State.h"

namespace Nexus2k {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
			 System::Windows::Forms::Button^  button1;
			 System::Windows::Forms::Label^  label1;
			 Board *board;
			 Graphics^ graphics;
			 System::Windows::Forms::Timer^  timer1;
			 System::Windows::Forms::Button^  button2;
			 System::Windows::Forms::Button^  button3;
			 System::Windows::Forms::Label^  label2;
			 System::Windows::Forms::Label^  label3;
			 System::Windows::Forms::Label^  label4;
			 System::ComponentModel::IContainer^  components;
			 System::Windows::Forms::PictureBox^  pictureBox2;
			 System::Windows::Forms::Label^  label5;
			 System::Windows::Forms::Label^  label6;
			 System::Windows::Forms::Label^  label7;
			 System::Windows::Forms::PictureBox^  pictureBox3;
			 System::Windows::Forms::Label^  label8;
			 System::Windows::Forms::Label^  label9;
			 System::Media::SoundPlayer^ startPlayer;
			 int hs;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(12, 86);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(486, 450);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pictureBox1_MouseDown);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::DarkSlateBlue;
			this->button1->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->ForeColor = System::Drawing::Color::Lime;
			this->button1->Location = System::Drawing::Point(12, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(113, 31);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Start";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::LightSteelBlue;
			this->label1->Location = System::Drawing::Point(291, 18);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(72, 25);
			this->label1->TabIndex = 2;
			this->label1->Text = L"00000";
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::DarkSlateBlue;
			this->button2->Enabled = false;
			this->button2->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->ForeColor = System::Drawing::Color::Lime;
			this->button2->Location = System::Drawing::Point(12, 49);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(113, 31);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Restart";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::DarkSlateBlue;
			this->button3->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button3->ForeColor = System::Drawing::Color::Lime;
			this->button3->Location = System::Drawing::Point(404, 12);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(94, 68);
			this->button3->TabIndex = 4;
			this->button3->Text = L"Undo";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::LightSteelBlue;
			this->label2->Location = System::Drawing::Point(291, 55);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(72, 25);
			this->label2->TabIndex = 5;
			this->label2->Text = L"00000";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::LightSteelBlue;
			this->label3->Location = System::Drawing::Point(153, 18);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(82, 25);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Score: ";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::LightSteelBlue;
			this->label4->Location = System::Drawing::Point(153, 55);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(132, 25);
			this->label4->TabIndex = 7;
			this->label4->Text = L"High Score: ";
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::RoyalBlue;
			this->pictureBox2->Location = System::Drawing::Point(12, 86);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(487, 449);
			this->pictureBox2->TabIndex = 8;
			this->pictureBox2->TabStop = false;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->BackColor = System::Drawing::Color::RoyalBlue;
			this->label5->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->ForeColor = System::Drawing::Color::Lime;
			this->label5->Location = System::Drawing::Point(77, 117);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(329, 74);
			this->label5->TabIndex = 9;
			this->label5->Text = L"NEXUS 2K!";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->BackColor = System::Drawing::Color::RoyalBlue;
			this->label6->Font = (gcnew System::Drawing::Font(L"Viner Hand ITC", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->ForeColor = System::Drawing::Color::PaleGreen;
			this->label6->Location = System::Drawing::Point(77, 191);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(332, 195);
			this->label6->TabIndex = 10;
			this->label6->Text = L"Make rows of 5 or more and\r\nWatch your points grow.\r\n\r\nBeat the high score...\r\nIf"
				L" you can!";
			this->label6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->BackColor = System::Drawing::Color::RoyalBlue;
			this->label7->Font = (gcnew System::Drawing::Font(L"Viner Hand ITC", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::Color::Lime;
			this->label7->Location = System::Drawing::Point(42, 404);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(398, 96);
			this->label7->TabIndex = 11;
			this->label7->Text = L"Click the Start button to get started.\r\nClick Undo to revert your moves.\r\nClick R"
				L"eset to start fresh.";
			this->label7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::Color::Navy;
			this->pictureBox3->Location = System::Drawing::Point(12, 86);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(487, 449);
			this->pictureBox3->TabIndex = 12;
			this->pictureBox3->TabStop = false;
			this->pictureBox3->Visible = false;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->BackColor = System::Drawing::Color::Navy;
			this->label8->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 36, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->ForeColor = System::Drawing::Color::Brown;
			this->label8->Location = System::Drawing::Point(56, 141);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(384, 74);
			this->label8->TabIndex = 13;
			this->label8->Text = L"GAME OVER!";
			this->label8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label8->Visible = false;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->BackColor = System::Drawing::Color::Navy;
			this->label9->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::Color::Brown;
			this->label9->Location = System::Drawing::Point(33, 264);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(448, 105);
			this->label9->TabIndex = 14;
			this->label9->Text = L"Uh oh, you filled the board.\r\nGood effort.\r\nFeel free to play again.";
			this->label9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label9->Visible = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::Maroon;
			this->ClientSize = System::Drawing::Size(511, 547);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"Form1";
			this->Text = L"Nexus 2k";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
		board = new Board();
		graphics = pictureBox1->CreateGraphics();
		Drawer::init(graphics);
		timer1->Enabled = true;
		label2->Text = System::String::Format("{0:00000}", board->getHighScore());
		startPlayer = gcnew System::Media::SoundPlayer("start.wav");
		startPlayer->PlayLooping();
	}

	private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
		board->gameRun();
		label1->Text = System::String::Format("{0:00000}", board->getScore());
		label2->Text = System::String::Format("{0:00000}", board->getHighScore());
		if (board->getGameOver())
		{
			label8->Visible = true;
			label9->Visible = true;
			pictureBox3->Visible = true;
		}
	}
			 
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
		board->spawn();
		button1->Enabled = false;
		button2->Enabled = true;
		pictureBox2->Visible = false;
		label5->Visible = false;
		label6->Visible = false;
		label7->Visible = false;
		startPlayer->Stop();
	}

	private: System::Void pictureBox1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		board->selectCell(e->X,e->Y);
	}

	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		board->initBoard();
		button1->Enabled = true;
		button2->Enabled = false;
		label8->Visible = false;
		label9->Visible = false;
		pictureBox3->Visible = false;
	}

	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		board->undo();
	}
};
}

