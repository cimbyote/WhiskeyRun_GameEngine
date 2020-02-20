//-----------------------------------------------------------------------------
// Copyright Ed Keenan 2017
// Optimized C++
//----------------------------------------------------------------------------- 

#include <assert.h>

// Windows.h include
	// many warnings - need to wrap for Wall warnings
#pragma warning( push )
#pragma warning( disable : 4820 )
#pragma warning( disable : 4668 )
#include <Windows.h>
#pragma warning( pop ) 

#include "File.h"
//#include "Trace.h"
#define STUB_PLEASE_REPLACE(x) (x)

File::Error File::Open(File::Handle &fh, const char * const fileName, File::Mode mode)
{
	if (fileName == 0)
	{
		return File::Error::OPEN_FAIL;
	}
	else
	{

		if (mode == File::Mode::WRITE)
		{
			fh = CreateFile(fileName,		// pointer to name of the file 
				GENERIC_WRITE, 				// access (read-write) mode     
				0, 							// share mode 
				0, 							// pointer to security attributes  
				CREATE_ALWAYS, 				// how to create 
				FILE_ATTRIBUTE_NORMAL,		// file attributes 
				NULL);						// handle to file with attributes to copy 

			DWORD temp = GetLastError();
			if ((temp == 0x00) || (temp == 183))
			{
				return File::Error::SUCCESS;
			}
			else
			{
				return File::Error::OPEN_FAIL;
			}

		}
		else if (mode == File::Mode::READ)
		{
			fh = CreateFile(fileName,		// pointer to name of the file 
				GENERIC_READ, 				// access (read-write) mode     
				0, 							// share mode 
				0, 							// pointer to security attributes  
				OPEN_EXISTING, 				// how to create 
				FILE_ATTRIBUTE_READONLY,	// file attributes 
				NULL);						// handle to file with attributes to copy 

			DWORD temp = GetLastError();
			if (temp == 0x00)
			{
				return File::Error::SUCCESS;
			}
			else
			{
				return File::Error::OPEN_FAIL;
			}
		}
		else if (mode == File::Mode::READ_WRITE)
		{
			fh = CreateFile(fileName,   // pointer to name of the file 
				GENERIC_READ | GENERIC_WRITE, // access (read-write) mode     
				0, 			// share mode 
				0, 							// pointer to security attributes  
				OPEN_ALWAYS, 				// how to create 
				FILE_ATTRIBUTE_NORMAL,		// file attributes 
				NULL);						// handle to file with attributes to copy 

			DWORD temp = GetLastError();
			if ((temp == 0x00) || (temp == 183))
			{
				return File::Error::SUCCESS;
			}
			else
			{
				return File::Error::OPEN_FAIL;
			}
		}

		else
		{
			return File::Error::OPEN_FAIL;
		}
	}


}

File::Error File::Close(const File::Handle fh)
{

	BY_HANDLE_FILE_INFORMATION fileinfo;

	BOOL isHandleValid = GetFileInformationByHandle(fh, &fileinfo);

	if (isHandleValid)
	{

	BOOL didItWork = CloseHandle(fh);

	if (didItWork != 0)
	{
		return File::Error::SUCCESS;
	}
	else
	{
		//DWORD temp = GetLastError();
		//Trace::out("Close Failed, Error: %x\n", temp);
		return File::Error::CLOSE_FAIL;
	}
	}
	else
	{
		//assert(0);
		return File::Error::CLOSE_FAIL;
	}
}

File::Error File::Write(File::Handle fh, const void * const buffer, const size_t inSize)
{
	DWORD bytesWritten = 0;

	BOOL didItWork = WriteFile(
		fh,
		buffer,
		inSize,
		&bytesWritten,
		NULL
	);

	if (didItWork)
	{
		return File::Error::SUCCESS;

	}
	else
	{
		return File::Error::WRITE_FAIL;
	}
}

File::Error File::Read(File::Handle fh, void * const buffer, const size_t inSize)
{
	DWORD bytesRead = 0;

	BOOL didItWork = ReadFile(
		fh,
		buffer,
		inSize,
		&bytesRead,
		NULL
	);

	if (didItWork)
	{
		return File::Error::SUCCESS;
	}
	else
	{
		DWORD why = GetLastError();
		STUB_PLEASE_REPLACE(why);
		return File::Error::READ_FAIL;
	}
}

File::Error File::Seek(File::Handle fh, File::Location location, int offset)
{
	DWORD loc = 0;

	//have to do this because the enum isn't set to regular values.
	if (location == File::Location::BEGIN) {
		loc = FILE_BEGIN;
	}
	else if (location == File::Location::CURRENT) {
		loc = FILE_CURRENT;
	}
	else if (location == File::Location::END) {
		loc = FILE_END;
	}


	DWORD didItWork = SetFilePointer(
		fh,
		offset,
		NULL,
		loc
	);

	if ((GetLastError() != NO_ERROR) && (didItWork == INVALID_SET_FILE_POINTER))
	{
		return File::Error::SEEK_FAIL;
	}
	else
	{
		return File::Error::SUCCESS;
	}
}

File::Error File::Tell(File::Handle fh, unsigned int &offset)
{
	offset = SetFilePointer(
		fh,
		0,
		0,
		FILE_CURRENT
	);

	DWORD temp = GetLastError();
	if ((temp != 0x00) && (offset == INVALID_SET_FILE_POINTER))
	{
		return File::Error::TELL_FAIL;
	}
	else
	{
		return File::Error::SUCCESS;
	}
}

File::Error File::Flush(File::Handle fh)
{
	unsigned int size;

	File::Error isItValid = Tell(fh, size);

	if (isItValid == File::Error::SUCCESS)
	{
		Seek(fh, File::Location::BEGIN, 0);


		return File::Error::SUCCESS;
	}
	else
	{
		return File::Error::FLUSH_FAIL;
	}
}

// ---  End of File ---------------
