#pragma once
#define uint unsigned int
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
	using namespace System::Runtime::InteropServices;


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
	private: System::Windows::Forms::Button^  b_servStart;
	protected:
					 TcpClient^ client;
					 TcpListener^ listner;
					 StreamReader^ sr;
					 cli::array<unsigned char,1>^ KBbuff;
					 array<Byte>^ aesKey;
					 array<Byte>^ aesIV;

					 array<Byte>^ desKey;
					 array<Byte>^ desIV;

					 array<Byte>^ rijKey;
					 array<Byte>^ rijIV;


	public: System::Windows::Forms::Label^  l_servStatus;

							 System::Threading::Thread^ servThread;
	private: System::Windows::Forms::TextBox^  textBox2;

	private:
		/// <summary>
		/// Требуется переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;
		bool servAlive;
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Обязательный метод для поддержки конструктора - не изменяйте
		/// содержимое данного метода при помощи редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->b_servStart = (gcnew System::Windows::Forms::Button());
			this->l_servStatus = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// b_servStart
			// 
			this->b_servStart->Location = System::Drawing::Point(12, 12);
			this->b_servStart->Name = L"b_servStart";
			this->b_servStart->Size = System::Drawing::Size(75, 23);
			this->b_servStart->TabIndex = 0;
			this->b_servStart->Text = L"go server";
			this->b_servStart->UseVisualStyleBackColor = true;
			this->b_servStart->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// l_servStatus
			// 
			this->l_servStatus->AutoSize = true;
			this->l_servStatus->BackColor = System::Drawing::Color::Chartreuse;
			this->l_servStatus->Font = (gcnew System::Drawing::Font(L"Tahoma", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->l_servStatus->ForeColor = System::Drawing::Color::DarkSlateGray;
			this->l_servStatus->Location = System::Drawing::Point(12, 75);
			this->l_servStatus->Name = L"l_servStatus";
			this->l_servStatus->Size = System::Drawing::Size(111, 14);
			this->l_servStatus->TabIndex = 4;
			this->l_servStatus->Text = L"Сервер запущен";
			this->l_servStatus->Visible = false;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(12, 92);
			this->textBox2->Multiline = true;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(197, 128);
			this->textBox2->TabIndex = 3;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(447, 229);
			this->Controls->Add(this->l_servStatus);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->b_servStart);
			this->Name = L"Form1";
			this->Text = L"Remote server";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_FormClosing);
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
						 servThread = gcnew System::Threading::Thread( gcnew System::Threading::ThreadStart(this, &Form1::ThreadProc ));
 						 KBbuff = gcnew cli::array<unsigned char,1>(1024);
						 AesManaged^ aesInst = gcnew AesManaged();
						 aesKey = aesInst->Key;
						 aesIV = aesInst->IV;
						 DES^ desInst = gcnew DESCryptoServiceProvider;
						 desKey = desInst->Key;
						 desIV = desInst->IV;
						 RijndaelManaged^ rijInst = gcnew RijndaelManaged();
						 rijKey = rijInst->Key;
						 rijIV = rijInst->IV;
 					 }


					 int clientDataEncParse(String^ clientData){
						 int enc, clientDataEncIndx = clientData->IndexOf("enc=");
						 if (clientDataEncIndx != -1) {
							 enc = Convert::ToInt32(clientData->Substring(clientDataEncIndx+4, 1));
						 } else {
							 enc = 0;
						 }
						 return enc;
					 };
					 
					 
						 String^ clientDataErrorSet(String^ _token, int _error) {
							 String^ newData = L"";
							 String^ tokenPath = _token+L".tkn";
							 String^ clientData = File::ReadAllText(tokenPath);
							 if (_error < 0 || _error> 1) {
								 return clientData;
							 }
							 int clientDataErrIndx = clientData->IndexOf("error=");
							 if (clientDataErrIndx != -1) {
								 newData = clientData->Substring(0, clientDataErrIndx+6) + _error + clientData->Substring(clientDataErrIndx+7);
							 } else {
								 newData = clientData+L"error="+_error+L"\n";
							 }
							 File::WriteAllText(tokenPath, newData);
							 return newData;
					 };

					 String^ clientDataEncSet(String^ _token, int _enc) {
						 String^ newData = L"";
						 String^ tokenPath = _token+L".tkn";
						 String^ clientData = File::ReadAllText(tokenPath);
						 if (_enc < 1 || _enc> 3) {
							 return clientData;
						 }
						 int clientDataEncIndx = clientData->IndexOf("enc=");
						 if (clientDataEncIndx != -1) {
							 newData = clientData->Substring(0, clientDataEncIndx+4) + _enc + clientData->Substring(clientDataEncIndx+5);
						 } else {
							 newData = clientData+L"enc="+_enc+L"\n";
						 }
						 File::WriteAllText(tokenPath, newData);
						 return newData;
					 };

					  void ThreadProc() { 
							String^ token; 
							String^ clientData ;
							int enc, error;
							if(!servAlive)
								return;
							listner = gcnew TcpListener(gcnew IPEndPoint(IPAddress::Parse("127.0.0.1"), 3000));
							listner->Start();
							TcpClient^ client = listner->AcceptTcpClient();
							Socket^ sock = client->Client;
							sr = gcnew StreamReader(client->GetStream());
						 try
						 {
							 while (servAlive)
							 {
								 String^ msg="";
								 sock->Receive(KBbuff);
								 for(int i=0; i<KBbuff->Length; i+=2) {
									 msg+=Char(KBbuff[i]);
								 }
								 Array::Clear(KBbuff,0,1024);
								 int queryIndx=msg->IndexOf(L"HELO", 0);
								 if( queryIndx == 0) {
									 sock->LocalEndPoint->ToString();
		 									token = Convert::ToString((gcnew Random)->Next(100000, 999999));
											File::WriteAllText(token+".tkn", L"handle="+sock->Handle+"\n");
											msg = L"SET TOKEN " + token;
												//Saving to stream
												//MemoryStream^ ms = gcnew MemoryStream(msg);
											//Sending stream bytes (array<unsigned char>) via socket
											sock->SendTo(System::Text::Encoding::Unicode->GetBytes(msg), client->Client->RemoteEndPoint);
								 } else if (msg->IndexOf(L"TOKEN") == 0 && msg->IndexOf(L";") == 12) {
									 token = msg->Substring(6, 6);
									 clientData = File::ReadAllText(token+L".tkn");
								 } else {
									 client->Close();
									 sock->Close();
								 }

									 queryIndx=msg->IndexOf(L"?", 0);
									 if (queryIndx != -1) {
									 String^ query=msg->Substring(queryIndx+1);
									 array<String^>^ params = query->Split(L'&');
									 for (int i=0; i<params->Length; i++)
									 {
										 int equalIndx = params[i]->IndexOf(L"=");
										 if(equalIndx != -1) {
											 String^ param = (params[i]->Split(' '))[0];
											 String^ key = param->Split('=')[0];
											 String^ val = param->Split('=')[1];
											  
											 if ( key ==  L"enc" ) {
												enc=Int32::Parse(val);
												clientData = clientDataEncSet(token, enc);
												}

 											 if ( key ==   L"error" ){
												 error = Int32::Parse(val);
												 clientData = clientDataErrorSet(token, enc);
												} 
											 		 
												
										 } else 
										  MessageBox::Show(params[i]);
									 }
									 enc = clientDataEncParse(clientData);
									 if (enc) {
										 String^ exampleData = L"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Morbi sodales sem sed facilisis cursus. Mauris pulvinar imperdiet quam, id vestibulum quam commodo vitae. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Pellentesque arcu risus, consequat nec nibh placerat, pellentesque tristique diam. Vivamus vel enim semper, elementum libero at, sollicitudin enim. In cursus venenatis nulla, eu aliquam magna aliquam et. In libero ligula, faucibus rutrum arcu a, pretium lacinia dolor. Nunc sit amet volutpat tortor, nec sollicitudin est. Morbi non risus convallis, pellentesque neque id, aliquet magna. Pellentesque sagittis felis sapien, ut rhoncus risus vestibulum ultricies.";
										 array<Byte>^ encrypted;
										 //Saving to stream
										 MemoryStream^ ms = gcnew MemoryStream();

										 switch(enc) {
										 case ENC_AES:
											 encrypted = AesExample::EncryptStringToBytes_Aes(exampleData, aesKey, aesIV);
											 break;
										 case ENC_DES:
											 encrypted = DesExample::EncryptData(exampleData, desKey, desIV);
											 break;
										 case ENC_RIJNDAEL:
											 encrypted = RijndaelExample::encryptStringToBytes_AES(exampleData, rijKey, rijIV);
											 break;
										 }

										 //Sending stream bytes (array<unsigned char>) via socket
										 sock->SendTo(encrypted,client->Client->RemoteEndPoint);
										 // 													 StreamWriter ^sw=gcnew StreamWriter(client->GetStream());
										 // 													 sw->Write(gbuf);
									 }
									 }
							 }
						 }
						 catch (Exception^ ex)
						 {
							 MessageBox::Show(L"Соединение разорвано!");	
						   listner->Stop();
							 client->Close();
							 sr->Close();
							ThreadProc();
						 }
 						 listner->Stop();
						 client->Close();
						 sr->Close();

					 };

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
					 if(servThread->IsAlive) {
						 servAlive = false;
						 l_servStatus->Visible=true;
						 l_servStatus->Text=L"Сервер останавливается";
						 servThread->Abort(1);
					 } else {
						 servAlive = true;
						 servThread->Start();
						 l_servStatus->Visible=true;
						 l_servStatus->Text=L"Сервер запущен";
					 }
				 }
private: System::Void Form1_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
					 servAlive = false;
					 if (servThread->IsAlive)
						 servThread->Abort();
					 try
					 {
// 						 servThread->Interrupt();
						 StreamWriter^ sw = gcnew StreamWriter(client->GetStream());
						 sw->AutoFlush = true;
						 sw->WriteLine("");
					 }
					 catch (Exception^ ex)
					 {
						 MessageBox::Show("disconnect");
					 }
				 }

};
}

