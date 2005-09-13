#ifdef WIN32
	#if defined(_MSC_VER) && (_MSC_VER < 1300)
	// Bug in MS Visual C++ 6.0. Fixed in Visual C++ .Net version.
	// Cannot print an __int64 number with cout without this overloading
		std::ostream& operator << (std::ostream& os, __int64 i)
		{
			char buf[32];

			sprintf( buf, "%I64d", i);

			os << buf;

			return os;
		}

		std::ostream& operator << (std::ostream& os, unsigned __int64 i)
		{
			char buf[32];

			sprintf(buf,"%I64u", i );

			os << buf;

			return os;
		}
	#endif
#endif
