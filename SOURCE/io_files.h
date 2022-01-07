/*!
file:	io_files.h
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	functions declarations to read and write files

	Copyright © 2020 DigiPen, All rights reserved.
*//*____________________________________________________________*/
#ifndef	IO_FILES_H
#define IO_FILES_H

#define IO_FILES_DEBUG			0
#include <stdarg.h>

/*!
@brief	struct to store 2D array and totals rows

		to get the length of the string, use strlen(strData[rows]) - 1
		-> -1 because a byte of memory is used to store the null terminator 
		'\0' at the end of the string

		str[rows][length_of_string] -> To get individual character
		str[rows] -> To get the string data in that specific row
*//*________________________________________________________________________________________*/
typedef struct FileDataStruct
{
	char** str;						// dynamic 2D string array
	unsigned rows;					// the number of rows in the 2D array
} FileDataStruct;

typedef FileDataStruct* FileData;

FileData ReadFiles(const char* fileName);
FileData ReadFixedRandom(const char* fileName, unsigned totalWords);
void WriteInt(const char* fileName, const char* mode, int counts, ...);
void WriteFloat(const char* fileName, const char* mode, int counts, ...);
void WriteString(const char* fileName, const char* mode, int counts, ...);
void FreeFileData(FileData* fd);

#endif