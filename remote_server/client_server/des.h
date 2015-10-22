using namespace System;
using namespace System::IO;
using namespace System::Security::Cryptography;


public ref class DesExample
{
public:
static array<Byte>^ EncryptData( String^ text, array<Byte>^desKey, array<Byte>^desIV )
{
	array<Byte>^ encrypted;
	//Create the file streams to handle the input and output files.
	MemoryStream^ fin = gcnew MemoryStream(System::Text::Encoding::Unicode->GetBytes(text));
	MemoryStream^ fout = gcnew MemoryStream();
	//fout->SetLength( 0 );

	//Create variables to help with read and write.
	array<Byte>^bin = gcnew array<Byte>(100);
	long rdlen = 0; //This is the total number of bytes written.

	long totlen = (long)fin->Length; //This is the total length of the input file.

	int len; //This is the number of bytes to be written at a time.

	DES^ des = gcnew DESCryptoServiceProvider;
	CryptoStream^ encStream = gcnew CryptoStream( fout,des->CreateEncryptor( desKey, desIV ),CryptoStreamMode::Write );
	StreamWriter^ swEncrypt = gcnew StreamWriter(encStream );
	Console::WriteLine( "Encrypting..." );

	//Read from the input file, then encrypt and write to the output file.
	swEncrypt->Write(text);
	swEncrypt->Flush();
	encrypted = fout->ToArray();

	swEncrypt->Close();
	encStream->Close();
	fout->Close();
	fin->Close();
	return encrypted;
}


static String^ DecryptData( String^ text, array<Byte>^desKey, array<Byte>^desIV )
{
	array<Byte>^ encrypted;
	String^ decrypted;
	//Create the file streams to handle the input and output files.
	MemoryStream^ fin = gcnew MemoryStream(System::Text::Encoding::Unicode->GetBytes(text));
	MemoryStream^ fout = gcnew MemoryStream();
	//fout->SetLength( 0 );

	//Create variables to help with read and write.
	array<Byte>^bin = gcnew array<Byte>(100);
	long rdlen = 0; //This is the total number of bytes written.

	long totlen = (long)fin->Length; //This is the total length of the input file.

	int len; //This is the number of bytes to be written at a time.

	DES^ des = gcnew DESCryptoServiceProvider;
	CryptoStream^ encStream = gcnew CryptoStream( fout,des->CreateDecryptor( desKey, desIV ),CryptoStreamMode::Write );
	StreamWriter^ swEncrypt = gcnew StreamWriter(encStream );
	Console::WriteLine( "Encrypting..." );

	//Read from the input file, then encrypt and write to the output file.
	swEncrypt->Write(text);
	encrypted = fout->ToArray();
	for(int i=0; i<encrypted->Length; i+=2) {
		decrypted+=Char(encrypted[i]);
	}
	encStream->Close();
	fout->Close();
	fin->Close();
	return decrypted;
}
};