/*!
file:	io_files.c
author:	Wong Man Cong

email:	w.mancong@digipen.edu

brief:	function definitions to read and write files

	Copyright © 2020 DigiPen, All rights reserved.
*//*__________________________________________________________________________________________________________*/
/* !	Pointer for using fopen		!

fopen modes: Modes for accessing file
		  r: Opens for reading. If the file doesn't exist or
			 cannot be found, the fopen_s call fails

		  w: Opens an empty file for writing. If the given file
			 exists, it's contents are destoryed

		  a: Opens for writing at the end of the file (appending) 
		     without removing the end-of-file (EOF) marker before 
			 new data is written to the file. Creates the file if it doesn't exist.

		 r+: Opens for both reading and writing. The file must exist.

		 w+: Opens an empty file for both reading and writing. If the file exists, 
			 its contents are destroyed.

		 a+: Opens for reading and appending. The appending operation includes the 
		     removal of the EOF marker before new data is written to the file. 
			 The EOF marker isn't restored after writing is completed. Creates the 
			 file if it doesn't exist.
*//*__________________________________________________________________________________________________________*/
#include "common_headers.h"
#include "io_files.h"

#define CHAR_SIZE						2048
#define STORE_SIZE_INT					((CHAR_BIT * sizeof(int) - 1) / 3 + 2)

//FileData* collector = NULL;			// used to clear memory later on
//unsigned collectorSize = 0;			// keep track of the size of the collector

/*!
@brief	Function to read and store data from file

@param	fileName: file path to the file

@return	FileData that stores a dynamic 2D array and 
		the total number of rows in the array
*//*__________________________________________________________________________________________________________*/
FileData ReadFiles(const char* fileName)
{
	FILE* stream;
	errno_t err = fopen_s(&stream, fileName, "r");

	if (!err)
	{
#if IO_FILES_DEBUG
		printf("The file '%s' was opened successfully\n", fileName);
#endif
	}
	else
	{
#if IO_FILES_DEBUG
		printf("The file '%s' was not opened successfully\n", fileName);
#endif
		return NULL;
	}

	//// if collector is initialised, reallocate block of memory
	//if (collector)
	//{
	//	collector = (FileData*)realloc(collector, ++collectorSize * sizeof(FileData));
	//}
	//// assign new block of memory
	//else
	//{
	//	collector = (FileData*)malloc(++collectorSize * sizeof(FileData));
	//}

	char** strData = (char**)malloc(sizeof(char*));

	char buffer[CHAR_SIZE];
	unsigned size = 0, index = 0;

	while (fgets(buffer, CHAR_SIZE, stream))
	{
		char** tmp = strData;
		strData = (char**)malloc(++size * sizeof(char*));
		memcpy_s(strData, size * sizeof(char*), tmp, (size - 1) * sizeof(char*));
		free(tmp);

		if (strData)
		{
			int len = (int)strlen(buffer) + 1;
			*(strData + index) = (char*)malloc((unsigned)len * sizeof(char) + 1);

			strcpy_s(strData[index], len, buffer);

			// replace last char of '\n' with '\0'
			*(*(strData + index++) + len - 1) = '\0';
		}
	}
	fclose(stream);

	for (unsigned i = 0; i < size - 1; ++i)
	{
		if(strData + i)
			*(*(strData + i) + (int)strlen(*(strData + i)) - 1) = '\0';
	}

	FileData fData = (FileData)malloc(sizeof(FileDataStruct));
	if (!fData)
	{
		for (unsigned i = 0; i < size; ++i)
		{
			if (strData + i)
			{
				free(*(strData + i));
				*(strData + i) = NULL;
			}
		}
		free(strData);
		strData = NULL;

		return NULL;
	}
	fData->str = strData;
	fData->rows = size;
	//collector[collectorSize - 1] = fData;

	return fData;
}

void SwapIO_Order(int** tmp, unsigned first, unsigned second)
{
	int temp = *((*tmp) + first);
	*((*tmp) + first) = *((*tmp) + second);
	*((*tmp) + second) = temp;
}

void IO_FileSort(int** tmp, unsigned total)
{
	for (unsigned i = 0; i < total - 1; ++i)
	{
		Boolean swapped = False;
		for (unsigned j = 0; j < total - i - 1; ++j)
		{
			if (*((*tmp) + j) > *((*tmp) + ((size_t)j + 1)))
			{
				SwapIO_Order(tmp, j, j + 1);
				swapped = True;
			}
		}
		if (swapped)
			break;
	}
}

/*!
@brief	Function to read fixed number of words fileName. Randomize the words

@param	fileName: file path to the file
		totalWords: total number of words to store in struct FileData

@return	FileData that stores a dynamic 2D array and the total number of rows in the array
*//*__________________________________________________________________________________________________________*/
FileData ReadFixedRandom(const char* fileName, unsigned totalWords)
{
	FILE* stream;
	errno_t err = fopen_s(&stream, fileName, "r");

	if (!err)
	{
#if IO_FILES_DEBUG
		printf("The file '%s' was opened successfully\n", fileName);
#endif
	}
	else
	{
#if IO_FILES_DEBUG
		printf("The file '%s' was not opened successfully\n", fileName);
#endif
		return NULL;
	}

	unsigned total = 0;
	char buffer[CHAR_SIZE];
	// total rows in txt file (not efficient but fk it)
	while (fgets(buffer, CHAR_SIZE, stream))
		++total;
	fclose(stream);

	if (totalWords > total)
		return NULL;

	// temp storage to store random numbers
	int* tmp = (int*)malloc(totalWords * sizeof(int));
	// give tmp storage default values of -1
	for (unsigned i = 0; i < totalWords; ++i)
		*(tmp + i) = 0;

	unsigned tmp_index = 0;

	while (tmp_index < totalWords)
	{
		int puts = 1;
		int random = CP_Random_RangeInt(1, total);

		for (unsigned j = 0; j < totalWords; ++j)
		{
			if (*(tmp + j) == random)
			{
				puts = 0;
				break;
			}
		}
		if (!puts)
			continue;
		*(tmp + tmp_index++) = random;
	}

	// after randomising order of the words, time to store it in
	for (unsigned i = 0; i < totalWords; ++i)
		IO_FileSort(&tmp, totalWords);

	//for (unsigned i = 0; i < totalWords; ++i)
	//	printf("%d ", *(tmp + i));

	// open the file agn
	int line_number = 1, index = 0;	// current line of the file
	tmp_index = 0;
	err = fopen_s(&stream, fileName, "r");

	if (!err)
	{
#if IO_FILES_DEBUG
		printf("The file '%s' was opened successfully\n", fileName);
#endif
	}
	else
	{
#if IO_FILES_DEBUG
		printf("The file '%s' was not opened successfully\n", fileName);
#endif
		return NULL;
	}

	char** strData = (char**)malloc(sizeof(char*));

	while (fgets(buffer, CHAR_SIZE, stream))
	{
		if ((line_number++) != *(tmp + tmp_index))
			continue;

		char** tmp2 = strData;
		strData = (char**)malloc(++tmp_index * sizeof(char*));
		memcpy_s(strData, tmp_index * sizeof(char*), tmp2, (tmp_index - 1) * sizeof(char*));
		free(tmp2);

		if (strData)
		{
			int len = (int)strlen(buffer) + 1;
			*(strData + index) = (char*)malloc((unsigned)len * sizeof(char) + 1);

			strcpy_s(strData[index], len, buffer);

			// replace last char of '\n' with '\0'
			*(*(strData + index++) + len - 1) = '\0';
		}
	}
	fclose(stream);
	free(tmp);

	for (unsigned i = 0; i < totalWords; ++i)
	{
		if(strData + i)
			*(*(strData + i) + (int)strlen(*(strData + i)) - 1) = '\0';
	}

	FileData fData = (FileData)malloc(sizeof(FileDataStruct));
	if (!fData)
	{
		for (unsigned i = 0; i < totalWords; ++i)
		{
			if (strData + i)
			{
				free(*(strData + i));
				*(strData + i) = NULL;
			}
		}
		free(strData);
		strData = NULL;

		return NULL;
	}
	fData->str = strData;
	fData->rows = totalWords;

	return fData;
}

/*!
@brief	Save int data.

@param	fileName: path to the file (Provide with directory like -> "directoryName/.../fileName")

		mode: "w" -> destory the contents inside the file (if file exist)
			  and write new contents over it. If it doesn't exist, new file will be
			  created in the solution folder

			  "a" -> append new data at the new line to existing file. If file does
			  not exist, create a new file in the solution folder
*//*__________________________________________________________________________________________________________*/
void WriteInt(const char* fileName, const char* mode, int counts, ...)
{
	FILE* stream;
	errno_t err;

	if (strcmp(mode, "w") && strcmp(mode, "a"))
	{
#if IO_FILES_DEBUG
		printf("Unable to WriteInt.\nNo such command '%s'\n", mode);
#endif
		return;
	}
	else
	{
		err = fopen_s(&stream, fileName, mode);
	}

	if (!err)
	{
#if IO_FILES_DEBUG
		printf("The file '%s' was opened successfully\n", fileName);
#endif
	}
	else
	{
#if IO_FILES_DEBUG
		printf("The file '%s' was not opened successfully\n", fileName);
#endif
		return;
	}

	va_list lst;
	va_start(lst, counts);

	for (int i = 0; i < counts; ++i)
	{
		char str[STORE_SIZE_INT];
		int n = va_arg(lst, int);
		sprintf_s(str, STORE_SIZE_INT, "%d\n", n);

		fprintf_s(stream, str);
	}

	fclose(stream);
}


/*!
@brief	Save float data.

@param	fileName: path to the file (Provide with directory like -> "directoryName/.../fileName")

		mode: "w" -> destory the contents inside the file (if file exist)
			  and write new contents over it. If it doesn't exist, new file will be
			  created in the solution folder

			  "a" -> append new data at the new line to existing file. If file does
			  not exist, create a new file in the solution folder
*//*__________________________________________________________________________________________________________*/
void WriteFloat(const char* fileName, const char* mode, int counts, ...)
{
	FILE* stream;
	errno_t err;

	if (strcmp(mode, "w") && strcmp(mode, "a"))
	{
#if IO_FILES_DEBUG
		printf("Unable to WriteFloat.\nNo such command '%s'\n", mode);
#endif
		return;
	}
	else
	{
		err = fopen_s(&stream, fileName, mode);
	}

	if (!err)
	{
#if IO_FILES_DEBUG
		printf("The file '%s' was opened successfully\n", fileName);
#endif
	}
	else
	{
#if IO_FILES_DEBUG
		printf("The file '%s' was not opened successfully\n", fileName);
#endif
		return;
	}

	va_list lst;
	va_start(lst, counts);

	for (int i = 0; i < counts; ++i)
	{
		double n = va_arg(lst, double);
		fprintf_s(stream, "%f\n", n);
	}

	fclose(stream);
}

/*!
@brief	Save string data.

@param	fileName: path to the file (Provide with directory like -> "directoryName/.../fileName")

		mode: "w" -> destory the contents inside the file (if file exist)
			  and write new contents over it. If it doesn't exist, new file will be
			  created in the solution folder

			  "a" -> append new data at the new line to existing file. If file does
			  not exist, create a new file in the solution folder
*//*__________________________________________________________________________________________________________*/
void WriteString(const char* fileName, const char* mode, int counts, ...)
{
	FILE* stream;
	errno_t err;

	if (strcmp(mode, "w") && strcmp(mode, "a"))
	{
#if IO_FILES_DEBUG
		printf("Unable to WriteString.\nNo such command '%s'\n", mode);
#endif
		return;
	}
	else
	{
		err = fopen_s(&stream, fileName, mode);
	}

	if (!err)
	{
#if IO_FILES_DEBUG
		printf("The file '%s' was opened successfully\n", fileName);
#endif
	}
	else
	{
#if IO_FILES_DEBUG
		printf("The file '%s' was not opened successfully\n", fileName);
#endif
		return;
	}

	va_list lst;
	va_start(lst, counts);

	for (int i = 0; i < counts; ++i)
	{
		const char* n = va_arg(lst, const char*);
		fprintf_s(stream, "%s\n", n);
	}

	fclose(stream);
}

/*!
@breif	Central function to deallocate memory allocation when you try to read
		from a file
*//*________________________________________________________________________________________*/
void FreeInOutput(void)
{
	//// if collector is initialised, clear memory
	//if (collector)
	//{
	//	for (unsigned i = 0; i < collectorSize; ++i)
	//	{
	//		if (collector[i])
	//		{
	//			for (unsigned j = 0; j < collector[i]->rows + 1; ++j)
	//			{
	//				if (collector[i]->str[j])
	//				{
	//					free(collector[i]->str[j]);
	//					collector[i]->str[j] = NULL;
	//				}
	//			}

	//			free(collector[i]->str);
	//			collector[i]->str = NULL;

	//			free(collector[i]);
	//			collector[i] = NULL;
	//		}
	//	}
	//	free(collector);
	//}
	//collector = NULL;
	//collectorSize = 0;
}

void FreeFileData(FileData* fd)
{
	if (!(*fd))
		return;

	for (unsigned i = 0; i < (*fd)->rows; ++i)
	{
		if ((*fd)->str[i])
		{
			free((*fd)->str[i]);
			(*fd)->str[i] = NULL;
		}
	}

	free((*fd)->str);
	(*fd)->str = NULL;

	free((*fd));
	(*fd) = NULL;
}
