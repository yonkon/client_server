#pragma once
#define ENC_AES 1
#define ENC_DES 2
#define ENC_RIJNDAEL 3
#include "aes.h"
#include "rijnadel.h"
#include "des.h"

namespace client_server {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System;
	using namespace System::Collections::Generic;
	using namespace System::Text;
	using namespace System::Net::Sockets;
	using namespace System::Net;
	using namespace System::IO;


	/// <summary>
	/// Сводка для Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Button^  b_clientStart;
	protected: 

	protected: 

	protected: 

					 TcpClient^ client;
					 TcpListener^ listner;
					 StreamReader^ sr;
					  StreamWriter^ sw;
						Socket^ sock;
						array<unsigned char>^ MBBuf;
						MemoryStream^ ms;

	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  b_clientSend;

	private: System::Windows::Forms::Label^  l_clientStatus;
	private: 

					 System::Threading::Thread^ servThread;
	private: System::Windows::Forms::Panel^  p_menu;
	private: System::Windows::Forms::Panel^  p_screen;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Button^  bSetSize;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::RadioButton^  rb_rij;
	private: System::Windows::Forms::RadioButton^  rb_des;
	private: System::Windows::Forms::RadioButton^  rb_aes;
	private: System::Windows::Forms::CheckBox^  cb_error;
					 int token;
	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->b_clientStart = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->b_clientSend = (gcnew System::Windows::Forms::Button());
			this->l_clientStatus = (gcnew System::Windows::Forms::Label());
			this->p_menu = (gcnew System::Windows::Forms::Panel());
			this->rb_rij = (gcnew System::Windows::Forms::RadioButton());
			this->rb_des = (gcnew System::Windows::Forms::RadioButton());
			this->rb_aes = (gcnew System::Windows::Forms::RadioButton());
			this->cb_error = (gcnew System::Windows::Forms::CheckBox());
			this->bSetSize = (gcnew System::Windows::Forms::Button());
			this->p_screen = (gcnew System::Windows::Forms::Panel());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->p_menu->SuspendLayout();
			this->p_screen->SuspendLayout();
			this->SuspendLayout();
			// 
			// b_clientStart
			// 
			this->b_clientStart->Location = System::Drawing::Point(33, 13);
			this->b_clientStart->Name = L"b_clientStart";
			this->b_clientStart->Size = System::Drawing::Size(75, 23);
			this->b_clientStart->TabIndex = 0;
			this->b_clientStart->Text = L"go client";
			this->b_clientStart->UseVisualStyleBackColor = true;
			this->b_clientStart->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// textBox1
			// 
			this->textBox1->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->textBox1->Location = System::Drawing::Point(0, 43);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(439, 261);
			this->textBox1->TabIndex = 1;
			// 
			// b_clientSend
			// 
			this->b_clientSend->Location = System::Drawing::Point(33, 42);
			this->b_clientSend->Name = L"b_clientSend";
			this->b_clientSend->Size = System::Drawing::Size(75, 23);
			this->b_clientSend->TabIndex = 0;
			this->b_clientSend->Text = L"Stop";
			this->b_clientSend->UseVisualStyleBackColor = true;
			this->b_clientSend->Visible = false;
			this->b_clientSend->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// l_clientStatus
			// 
			this->l_clientStatus->AutoSize = true;
			this->l_clientStatus->BackColor = System::Drawing::Color::Chartreuse;
			this->l_clientStatus->Dock = System::Windows::Forms::DockStyle::Top;
			this->l_clientStatus->Font = (gcnew System::Drawing::Font(L"Tahoma", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->l_clientStatus->ForeColor = System::Drawing::Color::DarkSlateGray;
			this->l_clientStatus->Location = System::Drawing::Point(0, 0);
			this->l_clientStatus->Name = L"l_clientStatus";
			this->l_clientStatus->Size = System::Drawing::Size(115, 14);
			this->l_clientStatus->TabIndex = 2;
			this->l_clientStatus->Text = L" Клиент запущен";
			this->l_clientStatus->Visible = false;
			// 
			// p_menu
			// 
			this->p_menu->Controls->Add(this->rb_rij);
			this->p_menu->Controls->Add(this->rb_des);
			this->p_menu->Controls->Add(this->rb_aes);
			this->p_menu->Controls->Add(this->cb_error);
			this->p_menu->Controls->Add(this->bSetSize);
			this->p_menu->Controls->Add(this->b_clientStart);
			this->p_menu->Controls->Add(this->b_clientSend);
			this->p_menu->Dock = System::Windows::Forms::DockStyle::Left;
			this->p_menu->Location = System::Drawing::Point(0, 0);
			this->p_menu->Name = L"p_menu";
			this->p_menu->Size = System::Drawing::Size(142, 304);
			this->p_menu->TabIndex = 3;
			// 
			// rb_rij
			// 
			this->rb_rij->AutoSize = true;
			this->rb_rij->Location = System::Drawing::Point(3, 128);
			this->rb_rij->Name = L"rb_rij";
			this->rb_rij->Size = System::Drawing::Size(124, 17);
			this->rb_rij->TabIndex = 5;
			this->rb_rij->Text = L"Шифровать Rijndael";
			this->rb_rij->UseVisualStyleBackColor = true;
			// 
			// rb_des
			// 
			this->rb_des->AutoSize = true;
			this->rb_des->Location = System::Drawing::Point(3, 105);
			this->rb_des->Name = L"rb_des";
			this->rb_des->Size = System::Drawing::Size(108, 17);
			this->rb_des->TabIndex = 5;
			this->rb_des->Text = L"Шифровать DES";
			this->rb_des->UseVisualStyleBackColor = true;
			// 
			// rb_aes
			// 
			this->rb_aes->AutoSize = true;
			this->rb_aes->Checked = true;
			this->rb_aes->Location = System::Drawing::Point(3, 82);
			this->rb_aes->Name = L"rb_aes";
			this->rb_aes->Size = System::Drawing::Size(107, 17);
			this->rb_aes->TabIndex = 5;
			this->rb_aes->TabStop = true;
			this->rb_aes->Text = L"Шифровать AES";
			this->rb_aes->UseVisualStyleBackColor = true;
			// 
			// cb_error
			// 
			this->cb_error->AutoSize = true;
			this->cb_error->Location = System::Drawing::Point(3, 158);
			this->cb_error->Name = L"cb_error";
			this->cb_error->Size = System::Drawing::Size(135, 17);
			this->cb_error->TabIndex = 4;
			this->cb_error->Text = L"Ошибка в сообщении";
			this->cb_error->UseVisualStyleBackColor = true;
			// 
			// bSetSize
			// 
			this->bSetSize->Location = System::Drawing::Point(33, 200);
			this->bSetSize->Name = L"bSetSize";
			this->bSetSize->Size = System::Drawing::Size(75, 23);
			this->bSetSize->TabIndex = 3;
			this->bSetSize->Text = L"Принять";
			this->bSetSize->UseVisualStyleBackColor = true;
			this->bSetSize->Click += gcnew System::EventHandler(this, &Form1::bSetSize_Click);
			// 
			// p_screen
			// 
			this->p_screen->Controls->Add(this->textBox1);
			this->p_screen->Controls->Add(this->l_clientStatus);
			this->p_screen->Dock = System::Windows::Forms::DockStyle::Fill;
			this->p_screen->Location = System::Drawing::Point(142, 0);
			this->p_screen->Name = L"p_screen";
			this->p_screen->Size = System::Drawing::Size(439, 304);
			this->p_screen->TabIndex = 4;
			this->p_screen->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseDown);
			this->p_screen->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseUp);
			// 
			// timer1
			// 
			this->timer1->Interval = 200;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(581, 304);
			this->Controls->Add(this->p_screen);
			this->Controls->Add(this->p_menu);
			this->Name = L"Form1";
			this->Text = L"Remote client";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseDown);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Form1_MouseUp);
			this->p_menu->ResumeLayout(false);
			this->p_menu->PerformLayout();
			this->p_screen->ResumeLayout(false);
			this->p_screen->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
						 MBBuf = gcnew array<unsigned char>(1240*1240*8);
						 token = -1;
					 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
						 client = gcnew TcpClient();
						 l_clientStatus->Visible=true;
						 try{
							 client->Connect(gcnew IPEndPoint(IPAddress::Parse("127.0.0.1"), 3000));
							 sock = client->Client;
							  sw = gcnew StreamWriter(client->GetStream());
								sw->AutoFlush = true;
								//sw->WriteLine("HELO");
							 //timer1->Start();
								sock->SendTo( System::Text::Encoding::Unicode->GetBytes(L"HELO"), client->Client->RemoteEndPoint);
								sock->Receive(MBBuf , SocketFlags::None);
							 	this->b_clientSend->Visible=true;
						 } catch (Exception^ ex)
						 {
							 MessageBox::Show("Connection error. Server unavailable :'(");
						 }
						  String^ answer = System::Text::Encoding::Unicode->GetString(MBBuf);
							int settokenInd = answer->IndexOf(L"SET TOKEN ");
							if( settokenInd == 0) {
								token = Convert::ToInt32(answer->Substring(10));
							}
					

						 /*client->Close();*/
					 }

					 //ручная отправка
	private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
						 if(timer1->Enabled) {
							 b_clientSend->Text=L"Start";
							 timer1->Stop();
						 } else {
							 b_clientSend->Text=L"Stop";
							 timer1->Start();
						 }
					 }

private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
					if(sock)
						sock->Close();
					 if(client)
						 client->Close();
				 }
				 public:

private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
//TODO: make onmousemove()
//  					 String^ temp =(L"GET?move="+xx+L";"+yy+"&get=gray");
					 String^ temp =(L"GET?get=gray");
					 try
					 {
						 sock->SendTo( System::Text::Encoding::Unicode->GetBytes(temp), client->Client->RemoteEndPoint);
						 sock->Receive(MBBuf , SocketFlags::None);

						 if(ms) {
							 ms->Flush();
							 ms->Read(MBBuf,0,0);
						 }
						 else {
							 ms = gcnew MemoryStream(MBBuf);
						 }
						 
						// sw->WriteLine(L"GET?move="+xx+L";"+yy);
 					 }
					 catch (Exception^ ex)
					 {
						 this->Close();
						 MessageBox::Show("Send error");
					 }

				 }
private: System::Void bSetSize_Click(System::Object^  sender, System::EventArgs^  e) {
					 String^ query = L"TOKEN " + token + ";\n?";
					 int enc = 0, err = 0;
					 if (rb_aes->Checked)
						 enc = ENC_AES;
					 if (rb_des->Checked)
						 enc = ENC_DES;
					 if (rb_rij->Checked)
						 enc = ENC_RIJNDAEL;
					 if (cb_error->Checked)
						 err = 1;
					 query += L"enc="+enc + L"&error=" + err;
					 try{
						 sock->SendTo( System::Text::Encoding::Unicode->GetBytes(query), client->Client->RemoteEndPoint);

						 sock->Receive(MBBuf , SocketFlags::None);

						 if(ms) {
							 ms->Flush();
							 ms->Read(MBBuf,0,0);
						 }
						 else {
							 ms = gcnew MemoryStream(MBBuf);
						 }
						 textBox1->Text = System::Text::Encoding::Unicode->GetString(MBBuf);
					 }
					 catch(Exception^ ex) {
						 MessageBox::Show(ex->StackTrace, ex->Message);
					 }					 
				 }

private: System::Void Form1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
					 ;
				 }

private: System::Void Form1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
					 ;
				 }


};
}

