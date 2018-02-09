#ifndef IMAGE_BMP_H
#define IMAGE_BMP_H
#include <string>

namespace image{
	class Bmp
	{
	public:
		Bmp();
		Bmp(const Bmp &rhs);
		~Bmp();
		Bmp& operator=(const Bmp &rhs);

		bool Read(const char* file_name);

		bool Save(const char* file_name, int width, int height, int channel_count, const unsigned char* data);

		int GetWidth() const;
		int GetHeight() const;
		int GetBitCount() const;
		int GetDataSize() const;

		const unsigned char* GetData() const;
		const unsigned char* GetDataRGB() const;

		void PrintSelf() const;
		const char* GetError() const;
	private:
		void Init();

		static bool DecodeRLE8(const unsigned char* encData, unsigned char* data );
		static void FlipImage(unsigned char* data, int width, int height, int channel_count );
		static void SwapRedBlue(unsigned char* data, int data_size, int channel_count );
		static int GetColorCount(const unsigned char* data, int data_size);
		static void BuildGrayScalePalette(unsigned char* palette, int palette_size);

		int width_;
		int height_;
		int bit_count_;
		int data_size_;
		unsigned char* data_;
		unsigned char* dataRGB_;
		std::string error_message_;
	
	};
	inline int Bmp::GetWidth() const { return width_; };
	inline int Bmp::GetHeight() const { return height_; };

	inline int Bmp::GetBitCount() const { return bit_count_; };
	
	inline int Bmp::GetDataSize() const { return data_size_; };
	inline const unsigned char* Bmp::GetData() const { return data_; };
	inline const unsigned char* Bmp::GetDataRGB() const { return dataRGB_; };

	inline const char* Bmp::GetError() const { return error_message_.c_str(); };

			
}




#endif


