using namespace System;
using namespace System::IO;
using namespace System::Security::Cryptography;

	public ref class AesExample
	{
		static array<Byte>^ EncryptStringToBytes_Aes(String^ plainText, array<Byte>^ Key, array<Byte>^ IV)
		{
			// Check arguments.
			if (plainText == "" || plainText->Length <= 0)
				throw gcnew ArgumentNullException("plainText");
			if (Key == nullptr || Key->Length <= 0)
				throw gcnew ArgumentNullException("Key");
			if (IV == nullptr || IV->Length <= 0)
				throw gcnew ArgumentNullException("Key");
			array<Byte>^ encrypted;
			// Create an AesManaged object
			// with the specified key and IV.
			AesManaged^ aesAlg = gcnew AesManaged();
			aesAlg->Key = Key;
			aesAlg->IV = IV;

				// Create a decrytor to perform the stream transform.
				ICryptoTransform^ encryptor = aesAlg->CreateEncryptor(aesAlg->Key, aesAlg->IV);
				// Create the streams used for encryption.
				MemoryStream^ msEncrypt = gcnew MemoryStream();
				CryptoStream^ csEncrypt = gcnew CryptoStream(msEncrypt, encryptor, CryptoStreamMode::Write);
				StreamWriter^ swEncrypt = gcnew StreamWriter(csEncrypt);
				
				//Write all data to the stream.
				swEncrypt->Write(plainText);
				encrypted = msEncrypt->ToArray();

			// Return the encrypted bytes from the memory stream.
			return encrypted;

		}

		static String^ DecryptStringFromBytes_Aes(array<Byte>^ cipherText, array<Byte>^ Key, array<Byte>^ IV)
		{
			// Check arguments.
			if (cipherText == nullptr || cipherText->Length <= 0)
				throw gcnew ArgumentNullException("cipherText");
			if (Key == nullptr || Key->Length <= 0)
				throw gcnew ArgumentNullException("Key");
			if (IV == nullptr || IV->Length <= 0)
				throw gcnew ArgumentNullException("Key");

			// Declare the string used to hold
			// the decrypted text.
			String^ plaintext = "";

			// Create an AesManaged object
			// with the specified key and IV.
			AesManaged^ aesAlg = gcnew AesManaged();
			aesAlg->Key = Key;
			aesAlg->IV = IV;
			// Create a decrytor to perform the stream transform.
			ICryptoTransform^ decryptor = aesAlg->CreateDecryptor(aesAlg->Key, aesAlg->IV);
			
			// Create the streams used for decryption.
			MemoryStream^ msDecrypt = gcnew MemoryStream(cipherText);
			CryptoStream^ csDecrypt = gcnew CryptoStream(msDecrypt, decryptor, CryptoStreamMode::Read);
			StreamReader^ srDecrypt = gcnew StreamReader(csDecrypt);

			// Read the decrypted bytes from the decrypting stream
			// and place them in a string.
			plaintext = srDecrypt->ReadToEnd();

			return plaintext;

		}
	};

