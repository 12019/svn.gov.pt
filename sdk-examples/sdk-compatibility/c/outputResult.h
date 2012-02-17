
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using std::cout;
using std::cerr;
using std::endl;


#ifdef TEST_OFICIAL_SDK
		std::string SDKVersion="TEST_OFICIAL_SDK";
#else
		std::string SDKVersion="TEST_NEW-VERION_SDK";
#endif
std::string TestedMethods="\nTESTED METHODS:\n";
std::string ReturnValues="";
std::string ErrorValues="";
std::string Log="\nLOG:\n";



//Various crap util-code that should go in a seperate file
//
struct HexCharStruct
{
	unsigned char c;
	HexCharStruct(unsigned char _c) : c(_c) { }
};

inline std::ostream& operator<<(std::ostream& o, const HexCharStruct& hs)
{
	o.width(2);
	return (o << std::setfill('0') << std::hex << (unsigned int)hs.c);
}

inline HexCharStruct hex(unsigned char _c)
{
	return HexCharStruct(_c);
}

void
printByteArray(std::ostream &stream, unsigned char * arr, unsigned int len)
{
	unsigned int j = 0;

	while ( j < len )
	{
		if (j % 20 == 0)
			stream << endl;
		stream << hex((unsigned char)arr[j]);
		j++;
	}
	stream << endl;
}




void
dumpBinary ( char * msg, unsigned char * data, unsigned int len )
{
	int i;
	char strLocal[1000];

	sprintf (strLocal, "%s\n\t", msg );
	Log.append(strLocal);
	for (i = 0; i < len; i++) {
		sprintf (strLocal, "%2.2x ", data[i] );
		Log.append(strLocal);
		if (i && i % 16 == 0){
			sprintf (strLocal, "\n\t" );
			Log.append(strLocal);
		}
	}
	if (i % 16 != 1){
		sprintf (strLocal, "\n" );
		Log.append(strLocal);
	}

	//sprintf (varOutput,  "pinType: %li\n", pin->pinType ); writeLog(varOutput); memset(varOutput,0,1000);
	Log.append(strLocal);
}




void
writeLog(std::string logLine){
	Log += logLine;
}

void
writeTestedMethod(std::string method){
	TestedMethods += method +"\n";
	writeLog("Testing Method:" + method + "\n");
	std::cout << TestedMethods ;
}

void
writeReturnValues(std::string method, long returnValue){


	//std::string

	std::string returnstr="";


	char value[10]="";
	sprintf (value, "%d", returnValue );

	ReturnValues += "Method " + method + " 		returns:" + value + "\n";
	writeLog("Method " + method + " 		returns:" + value + "\n");
	std::cout << "Method " + method + " 		returns:" + value + "\n";
	std::cout << returnValue;
}



void
writeToFile(){
	std::ofstream myfile;
	std::string fileName="";
	myfile.open ("SDK_TESTING");
	myfile << "******************";
	myfile << "TESTING " + SDKVersion;
	myfile << "******************";
	myfile << TestedMethods;
	myfile << Log;
	myfile.close();
}



void
writeByteArray(char * filename , unsigned char * arr, unsigned int len){


	//char filename[3]="12";

	std::ofstream file(filename);

	printByteArray(file, arr, len);



}
















/*
std::stringstream ss;
ss << "Hello, world, " << myInt << niceToSeeYouString;
std::string s = ss.str();
*/


