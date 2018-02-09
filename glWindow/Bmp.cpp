#include <cstring>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "Bmp.h"

using namespace image;

Bmp::Bmp() : width_(0), height_(0), bit_count_(0), data_size_(0), data_(0), dataRGB_(0),
			 error_message_("No errors.")
{
}

Bmp::Bmp(const Bmp &rhs){
	width_ = rhs.GetWidth();
	height_ = rhs.GetHeight();
	bit_count_ = rhs.GetBitCount();
	data_size_ = rhs.GetDataSize();
	error_message_ = rhs.GetError();

	if(rhs.GetData())
	{
		data_ = new unsigned char[data_size_];
		memcpy(data_, rhs.GetData(), data_size_);
	}
	else
		data_ = 0;
	if(rhs.GetDataRGB())
	{
		dataRGB_ = new unsigned char[data_size_];
		memcpy(dataRGB_, rhs.GetDataRGB(), data_size_ );
	}
	else
		dataRGB_ = 0;
}

Bmp::~Bmp()
{
	delete [] data_;
	data_ = 0;
	delete [] dataRGB_;
	dataRGB_ = 0;
}
Bmp& Bmp::operator=(const Bmp &rhs)
{
	if(this == &rhs)
		return *this;
	width_ = rhs.GetWidth();
	height_ = rhs.GetHeight();
	bit_count_ = rhs.GetBitCount();
	data_size_ = rhs.GetDataSize();
	error_message_ = rhs.GetError();

	if(rhs.GetData())
	{
		data_ = new unsigned char[data_size_];
		memcpy(data_, rhs.GetData(), data_size_);
	}
	else
		data_ = 0;
	if(rhs.GetDataRGB())
	{
		dataRGB_ = new unsigned char[data_size_];
		memcpy(dataRGB_, rhs.GetDataRGB(), data_size_);
	}
	else
		dataRGB_ = 0;
	return *this;
}	

void Bmp::Init()
{
	width_ = height_ = bit_count_ = data_size_ = 0;
	error_message_ = "No error. ";

	delete [] data_;
	data_ = 0;
	delete [] dataRGB_;
	dataRGB_ = 0;
}
void Bmp::PrintSelf() const
{	
	std::cout << "====== BMP ======\n"
			  << "Width: " <<width_ << " pixels\n"
		      << "Height: " <<height_ << " pixels\n"
			  << "Bit Count: " <<bit_count_<<" bits\n"
			  << "Data Size: " << data_size_<<" bytes\n"
			  << std::endl;
}

bool Bmp::Read(const char* file_name)
{
	this->Init();

	if(!file_name)
	{
		error_message_ = "File name is not defined (NULL pointer). ";
		return false;
	}

	std::ifstream in_file;
	in_file.open(file_name, std::ios::binary);
	
	if(!in_file.good())
	{
		error_message_ = "Failed to open a BMP file to read. ";
		return false;
	}

	char id[2];
	int file_size;
	short reserved1;
	short reserved2;
	int data_offset;
	int info_head_size;
	int width;
	int height;
	short plane_count;
	short bit_count;
	int compression;
	int data_size_with_peddings;

	in_file.read(id, 2);
	in_file.read((char*)&file_size, 4);
	in_file.read((char*)&reserved1, 4);
	in_file.read((char*)&reserved2, 4);
	in_file.read((char*)&data_offset, 4);
	in_file.read((char*)&info_head_size, 4);
	in_file.read((char*)&width, 4);
	in_file.read((char*)&height, 4);
	in_file.read((char*)&plane_count, 2);
	in_file.read((char*)&bit_count, 2);
	in_file.read((char*)&compression, 4);
	in_file.read((char*)&data_size_with_peddings, 4);

	if(id[0] != 'B' && id[1] != 'M')
	{
		in_file.close();
		error_message_ = "Magic ID is invalid. ";
		return false;
	}
	if(compression > 1)
	{
		in_file.close();
		error_message_ = "Unsupported compression. ";
		return false;
	}
	in_file.seekg(0, std::ios::end);
	file_size = (int)in_file.tellg();
	
	int paddings = (4-((width * bit_count / 8) % 4)) % 4;
	int data_size = width * abs(height) * bit_count / 8;

	data_size_with_peddings = file_size - data_offset;

	this->width_ = width;
	this->height_ = height;
	this->bit_count_ = bit_count;
	this->data_size_ = data_size;

	data_ = new unsigned char [data_size_with_peddings];
	dataRGB_ = new unsigned char [data_size];

	if(compression == 0)
	{
		in_file.seekg(data_offset, std::ios::beg);
		in_file.read((char*)data_, data_size_with_peddings);
	}
	else if(compression == 1)
	{
		int size = file_size - data_offset;
		unsigned char* encData = new unsigned char[size];
		
		in_file.seekg(data_offset, std::ios::beg);
		in_file.read((char*)encData, size);

		DecodeRLE8(encData, data_);
		delete [] encData;
	}
	in_file.close();
	if(compression == 0 && paddings > 0)
	{
		int line_width = width * bit_count / 8;

		int line_count = abs(height);
		for(int i = 1; i< line_count; i++)
		{
			memcpy(&data_[i*line_width], &data_[i*(line_width + paddings)], line_width);
		}
	}
	if(height > 0)
		FlipImage(data_, width, height, bit_count / 8);
	memcpy(dataRGB_, data_, data_size);
	if(bit_count == 24 || bit_count == 32)
		SwapRedBlue(dataRGB_, data_size, bit_count);
	return true;
}
bool Bmp::Save(const char* file_name, int w, int h, int channel_count, const unsigned char* data)
{
	error_message_ = "No error. ";
	if(!file_name || !data_)
	{
		error_message_ = "File name is not specified (NULL pointer). ";
		return false;
	}
	if(w == 0 || h == 0)
	{
		error_message_ = "Zero width or height.";
		return false;
	}

	char id[2];             // magic identifier "BM" (2 bytes)
	int file_size;           // file size in bytes (4)
	short reserved1;        // reserved 1 (2)
	short reserved2;        // reserved 2 (2)
	int data_offset;         // starting offset of bitmap data (4)
	int info_header_size;     // info header size (4)
	int width;              // image width (4)
	int height;             // image height (4)
	short plane_count;       // # of planes (2)
	short bit_count;         // # of bits per pixel (2)
	int compression;        // compression mode (4)
	int data_size_with_paddings; // bitmap data size in bytes with padding (4)
	int x_resolution;        // horizontal pixels per metre (4)
	int y_resolution;        // vertical pixels per metre (4)
	int color_count;         // # of colours used (4)
	int important_color_count;// # of important colours (4)

	int palette_size;        // size of palette block in bytes

	int paddings = (4 - ((width * channel_count) % 4)) % 4;

	int data_size = width * abs(height) * channel_count;
	
	id[0] = 'B';
	id[1] = 'M';
	reserved1 = reserved2 = 0;
	width = w;
	height = h;
	plane_count = 1;
	bit_count = channel_count * 8;
	compression = 0;
	data_size_with_paddings = data_size + (height * paddings);
	x_resolution = y_resolution = 2835;
	color_count = 0;
	important_color_count = 0;
	info_header_size = 40;
	data_offset = 54;
	file_size = data_size_with_paddings + data_offset;

	if(channel_count == 1)
	{
		color_count = 256;
		palette_size = color_count * 4;
		data_offset = 54 + palette_size;
		file_size = data_size_with_paddings + data_offset;
	}
	unsigned char* temp_data = new unsigned char [data_size];
	memcpy(temp_data, data, data_size);
	if(height<0)
		FlipImage(temp_data, width, height, channel_count);
	if(channel_count == 3 || channel_count == 4)
		SwapRedBlue(temp_data, data_size, channel_count );
	unsigned char* data_with_paddings = 0;

	if(paddings > 0)
	{
		data_with_paddings = new unsigned char [data_size_with_paddings];

		int line_width = width * channel_count;
		
		int line_count = abs(height);
		for(int i = 0; i<line_count; ++i)
		{
			memcpy(&data_with_paddings[i*(line_width + paddings)], &temp_data[i*line_width], line_width);
			for(int j = 1; j<paddings; ++j)
			{
				data_with_paddings[(i+1)*(line_width+paddings) - j] = (unsigned char)0;
			}
		}
		std::ofstream output_file;
		output_file.open(file_name, std::ios::binary);
		if(!output_file.good())
		{
			error_message_ = "Failed to open an output file.";
			return false;
		}
		
		output_file.put(id[0]);
		output_file.put(id[1]);
		output_file.write((char*)&file_size, 4);
		output_file.write((char*)&reserved1, 2);
		output_file.write((char*)&reserved2, 2);
		output_file.write((char*)&data_offset, 4);
		output_file.write((char*)&info_header_size, 4);
		output_file.write((char*)&width, 4);
		output_file.write((char*)&height, 4);
		output_file.write((char*)&plane_count, 2);
		output_file.write((char*)&bit_count, 2);
		output_file.write((char*)&compression, 4);
		output_file.write((char*)&data_size_with_paddings, 4);
		output_file.write((char*)&x_resolution, 4);
		output_file.write((char*)&y_resolution, 4);
		output_file.write((char*)&color_count, 4);
		output_file.write((char*)&important_color_count, 4);

		if(paddings == 8)
			output_file.write((char*)temp_data, data_size);
		else
			output_file.write((char*)data_with_paddings, data_size_with_paddings);
		output_file.close();
		delete [] temp_data;
		delete [] data_with_paddings;

		return true;
	}


}
bool Bmp::DecodeRLE8(const unsigned char* encData, unsigned char* outData)
{
	if(!encData || !outData)
		return false;
	unsigned char first, second;
	int i;
	bool stop = false;
	while(!stop)
	{
		first = *encData++;
		second = *encData++;
	
		if(first)
		{
			for(i = 0; i<first; ++i)
				*outData++ = second;
		}
		else
		{
			if(second == 1)
				stop = true;
			else if(second == 2)
				encData += 2;
			else
			{
				for(i = 0; i<second; ++i)
					*outData++ = *encData++;
				if(second % 2)
					encData++;
			}
		}
	}
	return true;
}


void Bmp::FlipImage(unsigned char* data, int width, int height, int channel_count)
{
	if(!data) return ;
	int line_size = width * channel_count;
	unsigned char* temp = new unsigned char [line_size];
	int half = height / 2 ;

	int line1 = 0;
	int line2 = (height-1) * line_size;

	for(int i = 0; i<half; ++i)	
	{
		memcpy(temp, &data[line1], line_size);
		memcpy(&data[line1], &data[line2], line_size);
		memcpy(&data[line2], temp, line_size);

		line1+=line_size;
		line2-=line_size;
	}
	delete [] temp;
}


void Bmp::SwapRedBlue(unsigned char* data, int data_size, int channel_count)
{
	if(!data) return ;
	if(channel_count < 3) return ;
	if(data_size % channel_count) return ;

	unsigned char temp;
	int i;

	for(i = 0; i<data_size; i+=channel_count)
	{
		temp = data[i];
		data[i] = data[i+2];
		data[i+2] = temp;
	}
}

int Bmp::GetColorCount(const unsigned char* data, int data_size)
{
	if(!data) return 0;
	const int kMax_Color = 256;
	int i ;
	int color_count = 0;
	unsigned int colors[kMax_Color];

	memset((void*)colors, 0, kMax_Color);
	for(i = 0; i<data_size; i++)
		colors[data[i]]++;
	color_count = kMax_Color;
	for(i = 0; i<kMax_Color; i++)
	{
		if(colors[i] == 0)
			color_count--;
	}

	return color_count;

}

void Bmp::BuildGrayScalePalette(unsigned char* palette, int palette_size)
{
	if(!palette) return ;

	int i, j; 
	for(i = 0, j = 0; i<palette_size; i+=4, j++)
	{
		palette[i] = palette[i+1] = palette[i+2];
		palette[i+3] = (unsigned char)0;
	}
}